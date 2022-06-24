#include "VMTranslator.hpp"
#include <iostream>
#include <fstream>

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

  currentIndex_(0)
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

void VmTranslator::InisialiseSegments(std::string outputAssemblyFile)
{
    std::ofstream fileOut;
    remove(outputAssemblyFile.c_str());
    fileOut.open(outputAssemblyFile.c_str(), std::ios_base::app);
    
    fileOut << "//Initialise Segments\n" << std::endl;
    fileOut << "//===================\n" << std::endl;
    fileOut << "//(Initialise_SP)" << std::endl;
    fileOut << "    li R1,  " << SP_pointer_ <<  std::endl;
    fileOut << "    li R2, " + SP_ << std::endl;
    fileOut << "    str R1, R2" << std::endl;
    fileOut << "    " << std::endl;
    fileOut << "//(Initialise_local)" << std::endl;
    fileOut << "    li R3, " + local_pointer_  << std::endl;
    fileOut << "    li R4, " + local_ << std::endl;
    fileOut << "    str R3, R4" << std::endl;
    fileOut << "" << std::endl;
    fileOut << "//(Initialise_this)" << std::endl;
    fileOut << "    li R5, " + this_pointer_  << std::endl;
    fileOut << "    li R6, " + this_  << std::endl;
    fileOut << "    str R5, R6" << std::endl;
    fileOut << "" << std::endl;
    fileOut << "//(Initialise_that)" << std::endl;
    fileOut << "    li R7, " + that_pointer_  << std::endl;
    fileOut << "    li R8, " + that_  << std::endl;
    fileOut << "    str R7, R8" << std::endl;
    fileOut << "" << std::endl;
    fileOut << "//(Initialise_temp)" << std::endl;
    fileOut << "    li R9, " + temp_pointer_  << std::endl;
    fileOut << "    li R10, " + temp_  << std::endl;
    fileOut << "    str R9, R10" << std::endl;
    fileOut << "" << std::endl;
    fileOut << "//(Initialise_argument)" << std::endl;
    fileOut << "    li R11, " + argument_pointer_  << std::endl;
    fileOut << "    li R12, " + argument_  << std::endl;
    fileOut << "    str R11, R12" << std::endl;
    fileOut << "       " << std::endl;
    fileOut << "//(Initialise_static" << std::endl;
    fileOut << "    li R13, " + static_pointer_  << std::endl;
    fileOut << "    li R14, " + static_  << std::endl;
    fileOut << "    str R13, R14" << std::endl;
    fileOut << "       " << std::endl;
    fileOut << "//(Initialise_pointer" << std::endl;
    fileOut << "    li R13, " + pointer_pointer_  << std::endl;
    fileOut << "    li R14, 7" << std::endl;
    fileOut << "    str R13, R14" << std::endl;
    fileOut << std::endl;
}

bool VmTranslator::OpenVmFile(std::string vmfileIn)
{
    FILE* fp = fopen(vmfileIn.c_str(), "rb");
   if (!fp)
   {
      printf("Error:%s file not found\n\n", vmfileIn.c_str());
      exit(1);
   }

   fseek(fp, 0L, SEEK_END);
   uint32_t lSize = ftell( fp );
   rewind( fp );

   unsigned char* buffer = new unsigned char[lSize];
   fread( buffer , lSize, 1 , fp);

   for (int i = 0; i < lSize; i++)
   {
      inputBuffer_.push_back(buffer[i]);
   }
   inputBuffer_.push_back(0xEF); // push an end of file at the end
   fclose(fp);
   
   return true;
}

bool VmTranslator::Translate(std::string vmfileIn, std::string vmFileOut)
{
   OpenVmFile(vmfileIn);
   TokenizeFile(vmfileIn);

   return true;
}

std::vector<VmTranslator::Token> VmTranslator::TokenizeFile(std::string vmfileIn)
{
   OpenVmFile(vmfileIn);
   currentToken_ = unknownToken_;
   while(currentToken_ != VmTranslator::endOfFile_)
   {
      GetNextToken();
      if (currentToken_ != endOfLine_ && currentToken_ != comment_  && currentToken_ != endOfFile_)
      {
         tokens_.push_back(currentToken_);
      }
   }

   return tokens_;
}

VmTranslator::Token VmTranslator::GetNextToken()
{
   currentToken_ = VmTranslator::endOfFile_;
  
   char c;
start:
   SkipWhiteSpace();
  
   c = inputBuffer_[currentIndex_];
   
   if(isCharacter(c))
   {
      int tokenLength = 0;
      while (isCharacter(c) || isNumber(c) || isUnderScore(c) || isDash(c))
      {
         tokenString_[tokenLength++] = c;
         c = inputBuffer_[++currentIndex_];
      }
      tokenString_[tokenLength] = 0;
      currentToken_ = identifier_;
   }

   else if(isNumber(c))
   {
      float value = 0;
      unsigned int decimal = 0;
      while (isNumber(c))
      {
         value = (value * 10) + (c - '0');
         c = inputBuffer_[++currentIndex_];
      }
      currentToken_ = number_;
   }

   else if(isOpenBrackets(c))
   {
      currentToken_ = openBrackets_;
      c = inputBuffer_[++currentIndex_];
   }

   else if(isCloseBrackets(c))
   {
      currentToken_ = closeBrackets_;
      c = inputBuffer_[++currentIndex_];
   }

   else if(isDot(c))
   {
      currentToken_ = dot_;
      c = inputBuffer_[++currentIndex_];
   }

   else if(isEndOfLine(c))
   {
      currentToken_ = endOfLine_;
      c = inputBuffer_[++currentIndex_];
      lineNumber_++;
   }
   else if (isEndOfFile(c))
   {
      currentToken_ = endOfFile_;
      c = inputBuffer_[++currentIndex_];
   }

   else if(isForwordSlash(c))
   {
      c = inputBuffer_[++currentIndex_];
     
      if (isForwordSlash(c))
      {
         //consume all characters till the end of line
         while(!isEndOfLine(c))
         {
            c = inputBuffer_[++currentIndex_];
         }
         currentToken_ = comment_;
      }
   }

   if (currentToken_ == VmTranslator::identifier_)
   {
      currentToken_ = CheckToken();  
   }
    
   return currentToken_;
}

VmTranslator::Token VmTranslator::CheckToken()
{
   std::string token = tokenString_;
   VmTranslator::Token thisToken = VmTranslator::identifier_;

   if (token == "function")
   {
      thisToken = VmTranslator::function_;
   }
   else if (token == "push" )
   {
      thisToken = VmTranslator::push_;
   }
   else if (token == "pop" )
   {
      thisToken = VmTranslator::pop_;
   }
   else if (token == "constant")
   {
      thisToken = VmTranslator::constantT_;
   }
   else if (token == "argument")
   {
      thisToken = VmTranslator::argumentT_;
   }
   else if (token == "local")
   {
      thisToken = VmTranslator::localT_;
   }
    else if (token == "static")
   {
      thisToken = VmTranslator::staticT_;
   }
   else if (token == "field")
   {
      thisToken = VmTranslator::fieldT_;
   }
   else if (token == "this")
   {
      thisToken = VmTranslator::thisT_;
   }
   else if (token == "that")
   {
      thisToken = VmTranslator::thatT_;
   }
   else if (token == "equ")
   {
      thisToken = VmTranslator::equ_;
   }
   else if (token == "nequ")
   {
      thisToken = VmTranslator::nequ_;
   }
   else if (token == "gt")
   {
      thisToken = VmTranslator::gt_;
   }
   else if (token == "lt")
   {
      thisToken = VmTranslator::lt_;
   }
   else if (token == "and")
   {
      thisToken = VmTranslator::and_;
   }
   else if (token == "or")
   {
      thisToken = VmTranslator::or_;
   }
   else if (token == "not")
   {
      thisToken = VmTranslator::not_;
   }
   else if (token == "add")
   {
      thisToken = VmTranslator::add_;
   }
   else if (token == "sub")
   {
      thisToken = VmTranslator::sub_;
   }
   else if (token == "mult")
   {
      thisToken = VmTranslator::mult_;
   }
   else if (token == "div")
   {
      thisToken = VmTranslator::div_;
   }
   else if (token == "return")
   {
      thisToken = VmTranslator::return_;
   }
   else if (token == "if-goto")
   {
      thisToken = VmTranslator::ifGoto_;
   }
   else if (token == "goto")
   {
      thisToken = VmTranslator::goto_;
   }

   return thisToken;
}


bool VmTranslator::isCharacter(char c)
{
   return ((c >= 'a' && c <='z') || (c >= 'A' && c <='Z'));
}

bool VmTranslator::isNumber(char c)
{
   return (c >= '0' && c <='9');
}

bool VmTranslator::isUnderScore(char c)
{
   return (c == '_');
}

bool VmTranslator::isDash(char c)
{
   return (c == '-');
}

bool VmTranslator::isOpenBrackets(char c)
{
   return (c == '(');
}

bool VmTranslator::isCloseBrackets(char c)
{
   return (c == ')');
}

bool VmTranslator::isDot(char c)
{
   return (c == '.');
}


bool VmTranslator::isEndOfLine(char c)
{
   bool retVal = false;
   if (c == '\n' || c == 10 || c == 13)
   {
      retVal = true;
   }
   return retVal;
}

bool VmTranslator::isForwordSlash(char c)
{
   return (c == '/');
}


bool VmTranslator::isEndOfFile(char c)
{
   return (c == 0xEF);
}

void  VmTranslator::SkipWhiteSpace()
{
   char c;
   c = inputBuffer_.at(currentIndex_);
   while ((c == ' ') || /*(c == 10) || (c == '\n') ||*/ (c =='\t') /*|| (c == 13)||(c == -51)*/)
   {
       c = inputBuffer_.at(++currentIndex_);
   }
}


void VmTranslator::PrintAllTokens()
{
   for (int i = 0; i < tokens_.size(); i++)
   {
       std::cout << tokenAsString[tokens_.at(i)] << std::endl;
   }
}

