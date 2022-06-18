#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Tokenizer.hpp"

int main(int argc, char* argv[])
{


   Tokenizer *tokenizer = new Tokenizer();
   tokenizer->OpenFile("file.txt"); 
   std::vector<Tokenizer::TokenVal> tokens = tokenizer->ReadAllTokens();
   for (int i = 0; i < tokens.size(); i++)
   {
       int tokenInt = (int)tokens.at(i).token;
       //printf("%d\n", tokenInt);
       std::cout << tokenizer->tokenAsString[tokenInt] << "(" << tokens.at(i).lineNumber << ")" << std::endl;
   }
   return 0;
}

void UNIT_TEST_INPUTFILE()
{
    InputFile *inputFile = new InputFile();
    inputFile->OpenFile("file.txt");
    unsigned char c = inputFile->GetCurrentCharacter();
    printf("%c\n", c);
    c = inputFile->GetNextCharacter();
    printf("%c\n", c);
}