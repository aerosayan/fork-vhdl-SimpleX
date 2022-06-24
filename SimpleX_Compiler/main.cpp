#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "SimplexParser.hpp"

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

int main(int argc, char* argv[])
{
    SimplexParser simplxParser;
    bool err = simplxParser.Parse("file.txt", 1);
    
    if (err == false)
    {
        err = simplxParser.Parse("file.txt", 2);
        if (err == false)
        {
            simplxParser.PrintGeneratedCode();
        }
    }
    //simplxParser.PrintClassSymbolTable();
    //simplxParser.PrintLocalArgumentNumbers();
    printf("\n\n");
    //UNIT_TEST_TOKENIZER();
   
   return 0;
}

