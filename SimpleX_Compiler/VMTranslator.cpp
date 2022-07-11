#include "VMTranslator.hpp"
#include <iostream>
#include <fstream>
#include <iostream>


VmTranslator::VmTranslator()
: SP_(0),
  local_(1),
  argument_(2),
  this_(3),
  that_(4),
  temp_(5),
  static_(6),
  SP_pointer_(10),
  local_pointer_(40),
  argument_pointer_(80),
  this_pointer_(400),
  that_pointer_(500),
  temp_pointer_(600),
  static_pointer_(700),
  pointer_pointer_(800),
  label_(0),
  retAddress_(0),
  repeat_(0)
{
    opcode_["nop"]= "000000";
    opcode_["lui"] = "000001";
    opcode_["li"] = "000010";
    opcode_["add"] = "000011";
    opcode_["sub"] = "100011"; 
    opcode_["not"] = "000100"; 
    opcode_["and"] = "000101";
    opcode_["or"] = "000110"; 
    opcode_["xor"] = "000111"; 
    opcode_["xnor"] = "001000";
    opcode_["nand"] = "001001";
    opcode_["nor"] = "001010";
    opcode_["shiftl"] = "001011";
    opcode_["shiftr"] = "001100";
    opcode_["Incr"] = "001101";
    opcode_["Decr"] = "001110";
    opcode_["load"] = "001111";
    opcode_["str"] = "010000";
    opcode_["jmp"] = "010001";
    opcode_["jeq"] = "010011";
    opcode_["jneq"] = "010101";
    opcode_["jg"] = "010111";
    opcode_["cmp"] = "011111";
           
   registers_["R0"]  = "00000"; 
   registers_["R1"]="00001";
   registers_["R2"]="00010";
   registers_["R3"]="00011";
   registers_["R4"]="00100";
   registers_["R5"]="00101";
   registers_["R6"]="00110";
   registers_["R7"]="00111";
   registers_["R8"]="01000";
   registers_["R9"]="01001";
   registers_["R10"]="01010";
   registers_["R11"]="01011"; 
   registers_["R12"]="01100";
   registers_["R13"]="01101";
   registers_["R14"]="01110";
   registers_["R15"]="01111";
   registers_["R16"]="10000";
   registers_["R17"]="10001";
   registers_["R18"]="10010";
   registers_["R19"]="10011";
   registers_["R20"]="10100";
   registers_["R21"]="10101";
   registers_["R22"]="10110";
   registers_["R23"]="10111";
   registers_["R24"]="11000";
   registers_["R25"]="11001";
   registers_["R26"]="11010";
   registers_["R27"]="11011";
   registers_["R28"]="11100";
   registers_["R29"]="11101";
   registers_["R30"]="11110";
   registers_["R31"]="11111";

}

VmTranslator::~VmTranslator()
{}

void VmTranslator::InisialiseSegments()
{
    asm_ << "//Initialise Segments\n" << std::endl;
    asm_ << "//===================\n" << std::endl;
    asm_ << "//(Initialise_SP)" << std::endl;
    asm_ << "    li R1,  " << SP_pointer_ <<  std::endl;
    asm_ << "    li R2, " << SP_ << std::endl;
    asm_ << "    str R1, R2" << std::endl;
    asm_ << "    " << std::endl;
    asm_ << "//(Initialise_local)" << std::endl;
    asm_ << "    li R3, " <<  local_pointer_  << std::endl;
    asm_ << "    li R4, " <<  local_ << std::endl;
    asm_ << "    str R3, R4" << std::endl;
    asm_ << "" << std::endl;
    asm_ << "//(Initialise_this)" << std::endl;
    asm_ << "    li R5, " <<  this_pointer_  << std::endl;
    asm_ << "    li R6, " <<  this_  << std::endl;
    asm_ << "    str R5, R6" << std::endl;
    asm_ << "" << std::endl;
    asm_ << "//(Initialise_that)" << std::endl;
    asm_ << "    li R7, " <<  that_pointer_  << std::endl;
    asm_ << "    li R8, " <<  that_  << std::endl;
    asm_ << "    str R7, R8" << std::endl;
    asm_ << "" << std::endl;
    asm_ << "//(Initialise_temp)" << std::endl;
    asm_ << "    li R9, " <<  temp_pointer_  << std::endl;
    asm_ << "    li R10, " <<  temp_  << std::endl;
    asm_ << "    str R9, R10" << std::endl;
    asm_ << "" << std::endl;
    asm_ << "//(Initialise_argument)" << std::endl;
    asm_ << "    li R11, " <<  argument_pointer_  << std::endl;
    asm_ << "    li R12, " <<  argument_  << std::endl;
    asm_ << "    str R11, R12" << std::endl;
    asm_ << "       " << std::endl;
    asm_ << "//(Initialise_static" << std::endl;
    asm_ << "    li R13, " <<  static_pointer_  << std::endl;
    asm_ << "    li R14, " <<  static_  << std::endl;
    asm_ << "    str R13, R14" << std::endl;
    asm_ << "       " << std::endl;
    asm_ << "//(Initialise_pointer" << std::endl;
    asm_ << "    li R13, " <<  pointer_pointer_  << std::endl;
    asm_ << "    li R14, 7" << std::endl;
    asm_ << "    str R13, R14" << std::endl;
    asm_ << std::endl;
}


std::vector<std::string> splitString(std::string text)
{
   std::vector<std::string> words{};
    size_t pos = 0;
    std::string space_delimiter = " ";
    while ((pos = text.find(space_delimiter)) != std::string::npos)
    {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + space_delimiter.length());
    }
    words.push_back(text);

    return words;
}

void VmTranslator::Translate(std::string vmFile)
{
   std::ifstream infile(vmFile);
   std::string line;
   asm_ = std::ofstream();
   asm_.open("assembly.asm");
  
   InisialiseSegments();
   while(std::getline(infile, line))
   {
      std::cout << line << std::endl;
      std::vector<std::string> tokens = splitString(line);
      Interpret(tokens, line);
   }

   asm_.close();

}

void VmTranslator::Interpret (std::vector<std::string> components, std::string line)
{
   if (line.rfind("(", 0) == 0)
   {
      asm_ << components[0] <<  "\n";
   }
   else if (components[0] == "push")
   {
      if (components[1] == "constant") 
      {
         asm_ << "//" <<  line <<  "\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n"; // 0 here is  the SP_ pointer which is RAM{0]
         asm_ << "     load R31, R1\n";
         asm_ << "\n";
         asm_ << "     li R2, " <<  components[2] <<  "\n";
         asm_ << "     str R2, R31\n";
         asm_ << "     Incr R31\n";
         asm_ << "     str R31, R1\n";
      }
      else if (components[1] == "local")
      {
         asm_ << "//" <<  line <<  "\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     load R31, R1\n";
         asm_ << "     li R1, " <<  local_ <<  "\n"; //1 here is the local pointer which is RAM{1]
         asm_ << "     load R3, R1\n";
         asm_ << "\n";
         asm_ << "     li R2, " <<  components[2] <<  "\n";
         asm_ << "     add R4, R3, R2\n";
         asm_ << "     load R30, R4\n";
         asm_ << "     str R30, R31\n";
         asm_ << "     Incr R31\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     str R31, R1\n";
      }
      else if (components[1] == "argument")
      {
         asm_ << "//" <<  line <<  "\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     load R31, R1\n";
         asm_ << "     li R1, " <<  argument_ <<  "\n";//  1 here is the argument pointer which is RAM{5]
         asm_ << "     load R3, R1\n";
         asm_ << "\n";
         asm_ << "     li R2, " <<  components[2] <<  "\n";
         asm_ << "     add R4, R3, R2\n";
         asm_ << "     load R30, R4\n";
         asm_ << "     str R30, R31\n";
         asm_ << "     Incr R31\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     str R31, R1\n";
      }
      else if (components[1] == "temp")
      {
         asm_ << "//" <<  line <<  "\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     load R31, R1\n";
         asm_ << "     li R1, " <<  temp_ <<  "\n";
         asm_ << "     load R3, R1\n";
         asm_ << "\n";
         asm_ << "     li R2, " <<  components[2] <<  "\n";
         asm_ << "     add R4, R3, R2\n";
         asm_ << "     load R30, R4\n";
         asm_ << "     str R30, R31\n";
         asm_ << "     Incr R31\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     str R31, R1\n";
      }
   }
   else if (components[0] == "pop")
   {
      if (components.size() == 1)
      {
         asm_ << "//" <<  line <<  "\n";
         asm_ << "// (pop_constant;\n";
         asm_ << "     li R1, " <<  SP_ <<  "\n";
         asm_ << "     load R31, R1\n";
         asm_ << "     Decr R31\n";
         asm_ << "     load R12, R31\n";
         asm_ << "     str R31, " <<  SP_ <<  "\n";
      }
      else
      {
         if(components.size()  == 3)
         {
            if (components[1] == "local")
            {
               asm_ << "//" <<  line <<  "\n";
               asm_ << "     li R1, " <<  SP_ <<  "\n";
               asm_ << "     load R31, R1\n";
               asm_ << "     Decr R31\n";
               asm_ << "     str R31, R1\n";
               asm_ << "     load R2, R31\n";
               asm_ << "     li R3, " <<  local_ <<  "\n";
               asm_ << "     load R4, R3\n";
               asm_ << "     li R5, " <<  components[2] <<  "\n";
               asm_ << "     add R7, R4, R5\n";
               asm_ << "     str R2, R7\n" ;
            }
            else if(components[1] == "argument")
            {
               asm_ << "//" <<  line <<  "\n";
               asm_ << "     li R1, " <<  SP_ <<  "\n";
               asm_ << "     load R31, R1\n";
               asm_ << "     Decr R31\n";
               asm_ << "     str R31, R1\n";
               asm_ << "     load R2, R31\n"; // R2 contains the popped value
               asm_ << "     li R3, " <<  argument_ <<  "\n"; //  5 here is the address of the argument segment
               asm_ << "     load R4, R3\n";
               asm_ << "     li R5, " <<  components[2] <<  "\n";
               asm_ << "     add R7, R4, R5\n";
               asm_ << "     str R2, R7\n";
            }
            else if(components[1] == "this")
            {
               asm_ << "//" <<  line <<  "\n";
               asm_ << "     li R1, " <<  SP_ <<  "\n";
               asm_ << "     load R31, R1\n";
               asm_ << "     Decr R31\n";
               asm_ << "     str R31, R1\n";
               asm_ << "     load R2, R31\n"; // R2 contains the popped value
               asm_ << "     li R3, " <<  this <<  "\n"; //  5 here is the address of the argument segment
               asm_ << "     load R4, R3\n";
               asm_ << "     li R5, " <<  components[2] <<  "\n";
               asm_ << "     add R7, R4, R5\n";
               asm_ << "     str R2, R7\n";
            }
            else if(components[1] == "that")
            {
                  asm_ << "//" <<  line <<  "\n";
                  asm_ << "     li R1, " <<  SP_ <<  "\n";
                  asm_ << "     load R31, R1\n";
                  asm_ << "     Decr R31\n";
                  asm_ << "     str R31, R1\n";
                  asm_ << "     load R2, R31\n"; // R2 contains the popped value
                  asm_ << "     li R3, " <<  that_ <<  "\n"; //  5 here is the address of the argument segment
                  asm_ << "     load R4, R3\n";
                  asm_ << "     li R5, " <<  components[2] <<  "\n";
                  asm_ << "     add R7, R4, R5\n";
                  asm_ << "     str R2, R7\n";
            }
            else if(components[1] == "temp")
            {
                  asm_ << "//" <<  line <<  "\n";
                  asm_ << "     li R1, " <<  SP_ <<  "\n";
                  asm_ << "     load R31, R1\n";
                  asm_ << "     Decr R31\n";
                  asm_ << "     str R31, R1\n";
                  asm_ << "     load R2, R31\n"; // R2 contains the popped value
                  asm_ << "     li R3, " <<  temp_ <<  "\n"; //  5 here is the address of the argument segment
                  asm_ << "     load R4, R3\n";
                  asm_ << "     li R5, " <<  components[2] <<  "\n";
                  asm_ << "     add R7, R4, R5\n";
                  asm_ << "     str R2, R7\n";
            }
            else if(components[1] == "pointer")
            {
                  asm_ << "//" <<  line <<  "\n";
                  asm_ << "     li R1, " <<  SP_ <<  "\n";
                  asm_ << "     load R31, R1\n";
                  asm_ << "     Decr R31\n";
                  asm_ << "     str R31, R1\n";
                  asm_ << "     load R2, R31\n"; // R2 contains the popped value\n";
                  uint32_t mthisTaht = this_;
                  if (components[2] == "0")
                     mthisTaht = this_;
                  else
                     mthisTaht = that_;
                  asm_ << "     li R3, " <<  mthisTaht <<  "\n";
                  asm_ << "     str R2, R3\n";
            }
        }
      }
   }
   else if  (components[0] == "add") 
   { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     add R14, R12, R13\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R14, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
   }
   else if  (components[0] == "sub") 
   { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     sub R14, R13, R12\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R14, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
   }
   else if  (components[0] == "and") 
   { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     and R14, R13, R12\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R14, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
   }
   else if  (components[0] == "or") 
   { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     or R14, R13, R12\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R14, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
   }
    else if  (components[0] == "incr") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     Incr R12\n";
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R12, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "equ") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R12, R13\n";
      asm_ << "     jeq label" << label_ << "\n";
      asm_ << "     cmp R12, R13\n";
      asm_ << "     jneq label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_+1)<<")\n";
      label_ += 2;
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "nequ") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R12, R13\n";
      asm_ << "     jneq label" << label_ << "\n";
      asm_ << "     cmp R12, R13\n";
      asm_ << "     jeq label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_ + 1)<<")\n";
      label_ += 2;
      // push the result
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "gt") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      // // asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jg label" << label_ << "\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jle label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_ + 1)<<")\n";
      label_ += 2;
      // push the result
      // // asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "gte") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      // // asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jge label" << label_ << "\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jl label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_ + 1)<<")\n";
      label_ += 2;
      // push the result
      // // asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "lt") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jl label" << label_ << "\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jge label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_ + 1)<<")\n";
      label_ += 2;
      // push the result
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "lte") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // pop first item
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R13, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li R15, 0\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jle label" << label_ << "\n";
      asm_ << "     cmp R13, R12\n";
      asm_ << "     jg label" << (label_ + 1) << "\n";
      asm_ << "  (label" << label_ <<")\n";
      asm_ << "     li R15, 1\n";
      asm_ << "  (label" << (label_ + 1)<<")\n";
      label_ += 2;
      // push the result
      asm_ << "     load R31, R1\n";
      asm_ << "     str R15, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      label_ += 2;
    }
    else if  (components[0] == "not") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     not R12, R12\n";
      // push the result
      asm_ << "     load R31, R1\n";
      asm_ << "     str R12, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "neg") 
    { 
      // pop second item
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n";
      asm_ << "     str R31, R1\n";
      // perform operation
      asm_ << "     li  R2, 0\n";
      asm_ << "     sub R12, R2, R12\n";
      // push the result
      // // asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R12, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
    }
    else if  (components[0] == "if-goto") 
    { 
      asm_ << "//" << line << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     Decr R31\n";
      asm_ << "     load R12, R31\n"; // pop the last value on stack
      asm_ << "     str R31, R1\n"; // save the stack pointer 
      // asm_ << "     li R1, 1\n";
      asm_ << "     li R1, 1\n";
      asm_ << "     cmp R12, R1\n";
      asm_ << "     jeq " << components[1] << "\n";
    }
    else if  (components[0] == "function") 
    { 
      asm_ << "//" << line << "\n";
      asm_ << "(" << components[1] << ")\n";
    }
   else if  (components[0] == "goto") 
   { 
      asm_ << "//" << line << "\n";
      asm_ << "     jmp " << components[1] << "\n";
   }
   else if  (components[0] == "call")
   { 
      // // !!!!!!!!!!!!! We need to push a bunch of things on the stack here !!!!!!!!!!!
      uint32_t numberOfLocalVariables = atoi(components[2].c_str());
      uint32_t numberOfArgs = atoi(components[3].c_str());
      asm_ << "//" << line << "\n";
      asm_ << "     // push return address given as a number\n";
      asm_ << "     li R1, 0\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     //replace the following li R2, return_address_\n";
      asm_ << "     li R2, _returnAddress" << retAddress_ <<"\n";
      asm_ << "     str R2, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n\n";
      asm_ << "     // push local\n";
      asm_ << "     li R10, " << local_ << "\n";
      asm_ << "     load R11, R10\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R11, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      asm_ << "     \n";
      asm_ << "     // push argument\n";
      asm_ << "     li R10, " << argument_ << "\n";
      asm_ << "     load R11, R10\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R11, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      asm_ << "     \n";
      asm_ << "     // push this\n";
      asm_ << "     li R10, " << this_ << "\n";
      asm_ << "     load R11, R10\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R11, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      asm_ << "     \n";
      asm_ << "     // push that\n";
      asm_ << "     li R10, " << that_ << "\n";
      asm_ << "     load R11, R10\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     str R11, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      asm_ << "     \n";
      asm_ << "     //New Arg = SP - 5 - nArgs -1\n"; 
      asm_ << "     li R2, " << argument_ << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     li R4, 5\n";
      asm_ << "     // R3 = SP - 5- nArgs\n";
      asm_ << "     sub R3, R31, R4\n";
      asm_ << "     //R6 = nArgs\n";
      asm_ << "     li R6, " << components[3] << "\n";
      asm_ << "     sub R7, R3, R6\n";
      asm_ << "     // new Arg = SP - 5 - nArgs\n";
      asm_ << "     str R7, R2\n";
      asm_ << "     \n";
      asm_ << "     li R2, " << local_ << "\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R3, R1\n";
      asm_ << "     str R3, R2\n";

      asm_ << "     //push number of local variables\n";
      asm_ << "     // R2 = num_of_local_Variables\n";
      asm_ << "     li R2, " << numberOfLocalVariables << "\n";
      asm_ << "     li R3, 0\n";
      asm_ << "     li R1, " << SP_ << "\n";
      asm_ << "     load R31, R1\n";
      asm_ << "     (repeat_" << repeat_ <<")\n";
      asm_ << "     str R3, R31\n";
      asm_ << "     Incr R31\n";
      asm_ << "     str R31, R1\n";
      asm_ << "     Decr R2\n";
      asm_ << "     li R4, 0\n";
      asm_ << "     cmp R2, R4\n";
      asm_ << "     jneq repeat_" << repeat_ <<"\n";
      repeat_ += 1;
      asm_ << "     jmp " << components[1] << "\n";
      asm_ << "(_returnAddress" << retAddress_ << ")\n";
      retAddress_ += 1;
   }
   else if  (components[0] == "return") 
   { 
      asm_ << "//" << line << "\n";
      asm_ << "    li R2, " << argument_ << "\n";
      asm_ << "    load R30, R2\n";
      asm_ << "    load R29, R2\n";
      asm_ << "    Incr R29\n"; // //  this is the SP_ value just before return (argumen0 + 1)
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    Decr R31\n";
      asm_ << "    str R31, R1\n";
      asm_ << "    load R20, R31\n";
      asm_ << "    str R20, R30\n";
      asm_ << "    //SP = local0\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, " << local_ << "\n";
      asm_ << "    load R31, R2\n";
      asm_ << "    str R31, R1\n";

      asm_ << "    //pop that(SP -1) 'that' pointer\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, 1\n";
      asm_ << "    sub R3, R31, R2\n";
      asm_ << "    load R4, R3\n";
      asm_ << "    li R5, " << that_ << "\n";
      asm_ << "    str R4, R5\n";

      asm_ << "    //pop that(SP -2) 'this' pointer\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, 2\n";
      asm_ << "    sub R3, R31, R2\n";
      asm_ << "    load R4, R3\n";
      asm_ << "    li R5, " << this_ << "\n";
      asm_ << "    str R4, R5\n";

      asm_ << "    //pop that(SP -3) 'argument' pointer\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, 3\n";
      asm_ << "    sub R3, R31, R2\n";
      asm_ << "    load R4, R3\n";
      asm_ << "    li R5, " << argument_ << "\n";
      asm_ << "    str R4, R5\n";

      asm_ << "    //pop that(SP -4) 'local' pointer\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, 4\n";
      asm_ << "    sub R3, R31, R2\n";
      asm_ << "    load R4, R3\n";
      asm_ << "    li R5, " << local_ << "\n";
      asm_ << "    str R4, R5\n";

      asm_ << "    //pop that(SP -5) 'return address'\n";
      asm_ << "    li R1, " << SP_ << "\n";
      asm_ << "    load R31, R1\n";
      asm_ << "    li R2, 5\n";
      asm_ << "    sub R3, R31, R2\n";
      asm_ << "    load R26, R3\n";
      asm_ << "    mov R31, R29\n";
      asm_ << "    str R31, R1\n";
      asm_ << "    return\n";
   }
}

