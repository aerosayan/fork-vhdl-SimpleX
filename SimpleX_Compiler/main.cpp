#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "SimplexParser.hpp"
#include "VMTranslator.hpp"
#include <filesystem>
#include "assembler.hpp"

void UNIT_TEST_INPUTFILE()
{
    InputFile *inputFile = new InputFile();
    inputFile->OpenFile("file.txt");
    unsigned char c = inputFile->GetCurrentCharacter();
    printf("%c\n", c);
    c = inputFile->GetNextCharacter();
    printf("%c\n", c);
}

void UNIT_TEST_TOKENIZER()
{
   Tokenizer *tokenizer = new Tokenizer();
   tokenizer->OpenFile("file.sx"); 
   std::vector<Tokenizer::TokenVal> tokens = tokenizer->ReadAllTokens();
   for (int i = 0; i < tokens.size(); i++)
   {
       int tokenInt = (int)tokens.at(i).token;
       std::cout << tokenizer->tokenAsString[tokenInt] << "(" << tokens.at(i).lineNumber << ", " << tokens.at(i).value << ", " << tokens.at(i).tokenString <<  ")" << std::endl;
   }
   printf("\n\n");
   tokenizer->CloseFile("file.sx");
   tokenizer->OpenFile("file2.sx"); 
   tokens = tokenizer->ReadAllTokens();
   for (int i = 0; i < tokens.size(); i++)
   {
       int tokenInt = (int)tokens.at(i).token;
       std::cout << tokenizer->tokenAsString[tokenInt] << "(" << tokens.at(i).lineNumber << ", " << tokens.at(i).value << ", " << tokens.at(i).tokenString <<  ")" << std::endl;
   }
   tokenizer->CloseFile("file2.sx");
}

std::string fileBaseName(std::string path)
{
    size_t sep = path.find_last_of("\\/");
    std::string name = path;
    std::string ext;
    if (sep != std::string::npos)
        path = path.substr(sep + 1, path.size() - sep - 1);

    size_t dot = path.find_last_of(".");
    if (dot != std::string::npos)
    {
        name = path.substr(0, dot);
        ext  = path.substr(dot, path.size() - dot);
    }
    else
    {
        name = path;
        ext  = "";
    }

   return name;
}

int main(int argc, char* argv[])
{
    //UNIT_TEST_TOKENIZER();
    SimplexParser simplxParser;
    VmTranslator vt;
    Assembler assemble;

    std::vector<std::string> fileToCompile;
    for (int i = 1; i < argc; i++)
    {
        fileToCompile.push_back(argv[i]);
    }
    std::string outFile = "Output.vm";
    remove(outFile.c_str());
    
    for (int i = 0; i < fileToCompile.size(); i++)
    {
        std::string currentFileToCompile = fileToCompile.at(i);
        bool err = simplxParser.Parse(currentFileToCompile, 1);
        
        if (err == false)
        {
            err = simplxParser.Parse(currentFileToCompile, 2);
            if (err == false)
            {
                simplxParser.GenerateVMCode(outFile);
            }
        }
    }
    
    vt.Translate(outFile);
    assemble.pass1("assembly.asm");
    assemble.assemble("assembly.asm");    
   
   return 0;
}

