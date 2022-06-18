#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include "InputFile.hpp"

class Tokenizer
{

  

public :
   typedef enum
   {
      unknownToken_,/*0*/
      program_,/*1*/
      subroutine_,/*2*/
      endSubroutine_,/*3*/
      let_,/*4*/
      do_,/*5*/
      loop_,/*6*/
      for_,/*7*/
      while_,/*8*/
      if_,/*9*/
      then_,/*10*/
      elseif_,/*11*/
      endif_,/*12*/
      wend_,/*13*/
      else_,/*14*/
      sub_,/*15*/
      end_,/*16*/
      endOfFile_,/*17*/
      endOfLine_,/*18*/
      identifier_,/*19*/
      number_,/*20*/
      equal_,/*21*/
      notEqual_,/*22*/
      biggerThan_,/*23*/
      biggerThanEqual_,/*24*/
      smallerThan_,/*25*/
      smallerThanEqual_,/*26*/
      and_,/*27*/
      or_,/*28*/
      not_,/*29*/
      semiColon_,/*30*/
      dot_,/*31*/
      openSquareBracket_,/*32*/
      closeSquareBracket_,/*33*/
      openBrackets_,/*34*/
      closeBrackets_,/*35*/
      operation_,/*36*/
      comma_,/*37*/
      colon_,/*38*/
      plus_,/*39*/
      plusPlus_,/*40*/
      minus_,/*41*/
      minusMinus_,/*42*/
      plusEqual_,/*43*/
      minusEqual_,/*44*/
      starEqual_,/*45*/
      forwordSlashEqual_,/*46*/
      star_,/*47*/
      forwordSlash_,/*48*/
      dim_,/*49*/
      as_,/*50*/
      integer_,/*51*/
      string_,/*52*/
      boolean_,/*53*/
      true_,/*54*/
      false_,/*55*/
      stringLit_,/*56*/
      declare_,/*57*/
      const_,/*58*/
      enum_,/*59*/
      endEnum_,/*60*/
      struct_,/*61*/
      write_,/*62*/
      delay_,
      openBraces_,
      closeBraces_,
      function_,
      int_,
      class_
   }Token;

   std::vector<std::string> tokenAsString =  {
      "unknownToken",
      "program",
      "subroutine",
      "endSubroutine",
      "let",
      "do",
      "loop",
      "for",
      "while",
      "if",/*9*/
      "then",/*10*/
      "elseif",/*11*/
      "endif",/*12*/
      "wend",/*13*/
      "else",/*14*/
      "sub",/*15*/
      "end",/*16*/
      "endOfFile",/*17*/
      "endOfLine",/*18*/
      "identifier",/*19*/
      "number",/*20*/
      "equal",/*21*/
      "notEqual",/*22*/
      "biggerThan",/*23*/
      "biggerThanEqual",/*24*/
      "smallerThan",/*25*/
      "smallerThanEqual",/*26*/
      "and",/*27*/
      "or",/*28*/
      "not",/*29*/
      "semiColon",/*30*/
      "dot",/*31*/
      "openSquareBracket",/*32*/
      "closeSquareBracket",/*33*/
      "openBrackets",/*34*/
      "closeBrackets",/*35*/
      "operation",/*36*/
      "comma",/*37*/
      "colon",/*38*/
      "plus",/*39*/
      "plusPlus",/*40*/
      "minus",/*41*/
      "minusMinus",/*42*/
      "plusEqual",/*43*/
      "minusEqual",/*44*/
      "starEqual",/*45*/
      "forwordSlashEqual",/*46*/
      "star",/*47*/
      "forwordSlash",/*48*/
      "dim",/*49*/
      "as",/*50*/
      "integer",/*51*/
      "string",/*52*/
      "boolean",/*53*/
      "true",/*54*/
      "false",/*55*/
      "stringLit",/*56*/
      "declare",/*57*/
      "const",/*58*/
      "enum",/*59*/
      "endEnum",/*60*/
      "struct",/*61*/
      "write",/*62*/
      "delay",
      "openBraces",
      "closeBraces",
      "function",
      "int",
      "class"
   };
   
   Tokenizer();

   ~Tokenizer();

   std::vector<Tokenizer::Token> ReadAllTokens();

   Token GetNextToken();

   unsigned int GetLineNumber();

   std::string String();

   double GetValue();

   bool OpenFile(std::string fileName);

   void CloseFile(std::string fileName);

   unsigned int GetCurrentCharacterLocation();

   void SetCurrentCharacterLocation(unsigned int address);

   void SetLineNumber(unsigned int lineNumber);

private:

   Token CheckToken();

   bool isCharacter(char c);

   bool isNumber(char c);

   bool isUnderScore(char c);

   bool isColon(char c);

   bool isComma(char c);

   bool isPlus(char c);
   
   bool isMinus(char c);

   bool isStar(char c);
   
   bool isForwordSlash(char c);

   bool isSemiColon(char c);

   bool isDot(char c);

   bool isOpenSquareBracket(char c);

   bool isCloseSquareBracket(char c);

   bool isEqual(char c);

   bool isBiggerThan(char c);

   bool isSmallerThan(char c);

   bool isSingleQuote(char c);

   bool isOpenBrackets(char c);

   bool isCloseBrackets(char c);

   bool isOperation(char c);

   bool isOpenBraces(char c);

   bool isCloseBraces(char c);

   bool isQuotation(char c);

   bool isEndOfLine(char c);

   bool isEndOfFile(char c);

   void  SkipWhiteSpace();

private:

   Token currentToken_;

   unsigned int lineNumber_;
   
   char  tokenString_[255];
   
   unsigned int tokenLength_;
   
   double value_;
   
   InputFile inputFile_;

   std::vector<Tokenizer::Token> tokens_;
};
#endif