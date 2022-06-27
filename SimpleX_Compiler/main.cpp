#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "SimplexParser.hpp"
#include "VMTranslator.hpp"
#include <filesystem>

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
   tokenizer->OpenFile("file.txt"); 
   std::vector<Tokenizer::TokenVal> tokens = tokenizer->ReadAllTokens();
   for (int i = 0; i < tokens.size(); i++)
   {
       int tokenInt = (int)tokens.at(i).token;
       std::cout << tokenizer->tokenAsString[tokenInt] << "(" << tokens.at(i).lineNumber << ", " << tokens.at(i).value << ", " << tokens.at(i).tokenString <<  ")" << std::endl;
   }
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
    SimplexParser simplxParser;

    std::vector<std::string> fileToCompile;
    for (int i = 1; i < argc; i++)
    {
        fileToCompile.push_back(argv[i]);
    }

    VmTranslator vt;
    
    for (int i = 0; i < fileToCompile.size(); i++)
    {
        bool err = simplxParser.Parse(fileToCompile.at(i), 1);
        
        if (err == false)
        {
            err = simplxParser.Parse(fileToCompile.at(i), 2);
            if (err == false)
            {
                std::string outFile = fileBaseName(fileToCompile.at(i)) + ".vm";
                simplxParser.GenerateVMCode(outFile);
                vt.Translate(outFile);
            }
        }
    }
   
   return 0;
}

