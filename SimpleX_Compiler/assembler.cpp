#include "assembler.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

Assembler::Assembler()
{
    opcode_["nop"]    = "000000";
    opcode_["lui"]    = "000001";
    opcode_["li"]     = "000010";
    opcode_["add"]    = "000011";
    opcode_["sub"]    = "100011"; 
    opcode_["not"]    = "000100"; 
    opcode_["and"]    = "000101";
    opcode_["or"]     = "000110"; 
    opcode_["xor"]    = "000111"; 
    opcode_["xnor"]   = "001000";
    opcode_["nand"]   = "001001";
    opcode_["nor"]    = "001010";
    opcode_["shiftl"] = "001011";
    opcode_["shiftr"] = "001100";
    opcode_["Incr"]   = "001101";
    opcode_["Decr"]   = "001110";
    opcode_["load"]   = "001111";
    opcode_["str"]    = "010000";
    opcode_["jmp"]    = "010001";
    opcode_["jeq"]    = "010011";
    opcode_["jneq"]   = "010101";
    opcode_["jg"]     = "010111";
    opcode_["jge"]    = "011001";
    opcode_["jl"]     = "011011";
    opcode_["jle"]    = "011101";
    opcode_["cmp"]    = "011111";
    opcode_["call"]   = "100000";
    opcode_["return"] = "100001";  
    opcode_["mov"]    = "100010";
    opcode_["jmpa"]   = "010100";
    opcode_["mul"]    = "100100";
           
    registers_["R0"] = "00000"; 
    registers_["R1"] = "00001";
    registers_["R2"] = "00010";
    registers_["R3"] = "00011";
    registers_["R4"] = "00100";
    registers_["R5"] = "00101";
    registers_["R6"] = "00110";
    registers_["R7"] = "00111";
    registers_["R8"] = "01000";
    registers_["R9"] = "01001";
    registers_["R10"] = "01010";
    registers_["R11"] = "01011"; 
    registers_["R12"] = "01100";
    registers_["R13"] = "01101";
    registers_["R14"] = "01110";
    registers_["R15"] = "01111";
    registers_["R16"] = "10000";
    registers_["R17"] = "10001";
    registers_["R18"] = "10010";
    registers_["R19"] = "10011";
    registers_["R20"] = "10100";
    registers_["R21"] = "10101";
    registers_["R22"] = "10110";
    registers_["R23"] = "10111";
    registers_["R24"] = "11000";
    registers_["R25"] = "11001";
    registers_["R26"] = "11010";
    registers_["R27"] = "11011";
    registers_["R28"] = "11100";
    registers_["R29"] = "11101";
    registers_["R30"] = "11110";
    registers_["R31"] = "11111";
}

Assembler::~Assembler()
{}


std::vector<std::string> Assembler::splitString(std::string text)
{
   std::vector<std::string> words{};
   size_t pos = 0;
   std::string space_delimiter = " ";
   while ((pos = text.find(space_delimiter)) != std::string::npos || (pos = text.find(',')) != std::string::npos)
   {
    if (text.substr(0, pos) != "")
    {
       std::replace(text.begin(), text.end(), ',', ' '); 
       words.push_back(text.substr(0, pos));
    }
    text.erase(0, pos + space_delimiter.length());
   }
   words.push_back(text);

   return words;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) 
{
    return rtrim(ltrim(s));
}


void Assembler::pass1(std::string assemblyFile) 
{
   uint32_t pc = 0;

   std::ifstream infile(assemblyFile);
   std::string line;
   asm_ = std::ofstream();
   asm_.open("memory.list");
  
   while(std::getline(infile, line))
   {
      line = trim(line);
      if (line != "" && line.rfind("/", 0) != 0)
      {
         std::vector<std::string> components = splitString(line);
         if (line.rfind("(", 0) == 0)
         {
             line.erase(remove(line.begin(), line.end(), '('), line.end()); 
             line.erase(remove(line.begin(), line.end(), ')'), line.end()); 
             labelTable_[line] = pc;
         }
         else if (components[0] == "li" && is_number(components[2]))
         {
             pc = pc + 2;
         }
         else if (components[0] == "li" && (is_number(components[2]) == false))
         {
             pc = pc + 2;
         }
         else
         {
             pc = pc + 1;
         }
      }
   }
}

std::string stringToBinary(std::string decimal, uint8_t numOfbits) 
{
    std::string binaryString;
    uint32_t decimalInt = atoi(decimal.c_str());
    for (int i = 0; i < numOfbits; i++)
    {
         if ((decimalInt % 2) == 0)
         {
            binaryString.push_back('0');
         }
         else
         {
            binaryString.push_back('1');
         }
         decimalInt = decimalInt / 2;
    }

    std::reverse(binaryString.begin(), binaryString.end()); 

    return binaryString;
}

void Assembler::CreateHexFile()
{
    hexProgram_.clear();
    for(size_t i = 0; i < program_.size() ; i++)
    {
        std::string binToHex, tmp = "0000";
        for (size_t j = 0; j < program_.at(i).size(); j += 4)
        {
            if (program_.at(i).rfind("-", 0) != 0)
            {
                tmp = program_.at(i).substr(j, 4);
                if  (!tmp.compare("0000")) 
                    binToHex += "0";
                else if (!tmp.compare("0001"))
                    binToHex += "1";
                else if (!tmp.compare("0010")) 
                    binToHex += "2";
                else if (!tmp.compare("0011")) 
                    binToHex += "3";
                else if (!tmp.compare("0100"))
                     binToHex += "4";
                else if (!tmp.compare("0101")) 
                    binToHex += "5";
                else if (!tmp.compare("0110")) 
                    binToHex += "6";
                else if (!tmp.compare("0111")) 
                    binToHex += "7";
                else if (!tmp.compare("1000")) 
                    binToHex += "8";
                else if (!tmp.compare("1001")) 
                    binToHex += "9";
                else if (!tmp.compare("1010")) 
                    binToHex += "a";
                else if (!tmp.compare("1011")) 
                    binToHex += "b";
                else if (!tmp.compare("1100")) 
                    binToHex += "c";
                else if (!tmp.compare("1101")) 
                    binToHex += "d";
                else if (!tmp.compare("1110")) 
                    binToHex += "e";
                else if (!tmp.compare("1111")) 
                    binToHex += "f";
                else continue;
            }
        }
        if (binToHex != "")
        {
            hexProgram_.push_back(binToHex);
        }
    }

    std::ofstream fileOut;
    remove("memory.list");
    fileOut.open("memory.list");
    for (int i = 0; i < hexProgram_.size(); i++)
    {
       fileOut << hexProgram_.at(i) << std::endl;
    }
}


void Assembler::assemble(std::string assemblyFile)
{
   std::ifstream infile(assemblyFile);
   std::string line;
   
   while(std::getline(infile, line))
   {
      line = trim(line);
      if (line.rfind("#", 0) != 0 && line != "" && line.rfind("/", 0) != 0 && line.rfind("(", 0) != 0 )
      {
           std::vector<std::string> components = splitString(line);
        
            //no operation
            if (components[0] == "nop")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_["nop"] + "00000000000000000000000000");
            }
            if (components[0] == "call")
            {
                if (is_number(components[1]))
                {
                    std::string hexBinary = stringToBinary(components[1], 26);
                    program_.push_back("--" + line);
                    program_.push_back(opcode_["call"] + hexBinary);
                }
                else
                {
                    uint32_t addressInt = (labelTable_[components[1]]);
                    std::string address = std::to_string(addressInt);
                    std::string hexBinary = stringToBinary(address, 26);//bin(int(address, 10))[2:].zfill(26)
                    program_.push_back("--" + line);
                    program_.push_back(opcode_["call"] + hexBinary);
                }
            }
            if (components[0] == "return")
            {
                program_.push_back("--" + line );
                program_.push_back(opcode_["return"] + "00000000000000000000000000");
            }
            //lui or li operation
            else if (components[0] == "li")
            {
                if (components[2].rfind("_", 0) != 0)
                {
                    std::string literalVal = components[2];
                    literalVal = stringToBinary(literalVal, 32);
                    std::string upperHex = "00000" + literalVal.substr(0, 16);
                    std::string lowerHex = "00000" + literalVal.substr(16, 16);
                    program_.push_back("--" + line);
                    program_.push_back(opcode_["lui"] + registers_[components[1]] + upperHex);
                    program_.push_back(opcode_["li"] + registers_[components[1]] + lowerHex);
                }
                else
                {
                    uint32_t literalValInt = labelTable_[components[2]];
                    std::string literalVal = std::to_string(literalValInt);
                    literalVal = stringToBinary(literalVal, 32);
                    std::string upperHex = "00000" + literalVal.substr(0, 16);//[0:4]
                    std::string lowerHex = "00000" + literalVal.substr(16, 16);//[4:9] 
    
                    program_.push_back("--" + line);
                    program_.push_back(opcode_["lui"] + registers_[components[1]] + upperHex);
                    program_.push_back(opcode_["li"] + registers_[components[1]] + lowerHex);
                }
            }
            if(components[0] == "jmp" or components[0] == "jeq" or components[0] == "jneq" or components[0] == "jg" or components[0] == "jge" or components[0] == "jl" or components[0] == "jle")
            {
                if (is_number(components[1]))
                {
                    std::string hexBinary = stringToBinary(components[1], 26);//bin(int(components[1], 10))[2:].zfill(26)
                    program_.push_back("--" + line);
                    program_.push_back(opcode_[components[0]] + hexBinary);
                }
                else
                {
                    uint32_t literalValInt = labelTable_[components[1]];
                    std::string address = std::to_string(literalValInt);
                    std::string hexBinary = stringToBinary(address, 26);//[2:].zfill(26)
                    program_.push_back("--" + line);
                    program_.push_back(opcode_[components[0]] + hexBinary);
                }
            }
            if(components[0] == "add" or components[0] == "sub" or components[0] == "and" or components[0] == "or" or components[0] == "xor" or components[0] == "xnor" or components[0] == "nand" or components[0] == "nor" or components[0] == "mul")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_[components[0]] + registers_[components[1]] + registers_[components[2]] +  registers_[components[3]] + "00000000000");
            }
            if(components[0] == "shiftl" or components[0] == "shiftr")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_[components[0]] + registers_[components[1]] + registers_[components[2]] + "0000000000000000");
            }
            if(components[0] == "Incr" or components[0] == "Decr")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_[components[0]] + registers_[components[1]] + "000000000000000000000");
            }
            if(components[0] == "not")
            {
                 program_.push_back("--" + line);
                 program_.push_back(opcode_[components[0]] + registers_[components[1]] + registers_[components[2]] + "0000000000000000");
            }
            if(components[0] == "load" or components[0] == "str" or components[0] == "cmp")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_[components[0]] + registers_[components[1]] + registers_[components[2]] + "0000000000000000");
            }
            if(components[0] == "mov")
            {
                program_.push_back("--" + line);
                program_.push_back(opcode_[components[0]] + registers_[components[1]] + registers_[components[2]] + "0000000000000000");
            }
            if(components[0] == "jmpa")
            {
                 program_.push_back("--" + line);
                 program_.push_back(opcode_[components[0]] + registers_[components[1]] + "000000000000000000000");
            }
      }
   }
   infile.close();

   CreateHexFile();
}
