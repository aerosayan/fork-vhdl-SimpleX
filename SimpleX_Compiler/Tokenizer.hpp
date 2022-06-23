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
      let_,/*4*/
      do_,/*5*/
      while_,/*8*/
      if_,/*9*/
      elseif_,/*11*/
      endif_,/*12*/
      wend_,/*13*/
      else_,/*14*/
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
      mul_,/*47*/
      forwordSlash_,/*48*/
      integer_,/*51*/
      string_,/*52*/
      boolean_,/*53*/
      true_,/*54*/
      false_,/*55*/
      stringLit_,/*56*/
      const_,/*58*/
      enum_,/*59*/
      endEnum_,/*60*/
      struct_,/*61*/
      openBraces_,
      closeBraces_,
      function_,
      int_,
      void_,
      char_,
      class_,
      comment_,
      return_,
      constructor_,
      method_,
      field_,
      static_,
      null_,
      this_,
      stringConstant_
   }Token;

   std::vector<std::string> tokenAsString =  {
      "unknownToken", /*0*/
      "let", /*4*/
      "do", /*5*/
      "while", /*8*/
      "if", /*9*/
      "elseif", /*11*/
      "endif", /*12*/
      "wend", /*13*/
      "else", /*14*/
      "endOfFile", /*17*/
      "endOfLine", /*18*/
      "identifier", /*19*/
      "number", /*20*/
      "equal", /*21*/
      "notEqual", /*22*/
      "biggerThan", /*23*/
      "biggerThanEqual", /*24*/
      "smallerThan", /*25*/
      "smallerThanEqual", /*26*/
      "and", /*27*/
      "or", /*28*/
      "not", /*29*/
      "semiColon", /*30*/
      "dot", /*31*/
      "openSquareBracket", /*32*/
      "closeSquareBracket", /*33*/
      "openBrackets", /*34*/
      "closeBrackets", /*35*/
      "operation", /*36*/
      "comma", /*37*/
      "colon", /*38*/
      "plus", /*39*/
      "plusPlus", /*40*/
      "minus", /*41*/
      "minusMinus", /*42*/
      "plusEqual", /*43*/
      "minusEqual", /*44*/
      "starEqual", /*45*/
      "forwordSlashEqual", /*46*/
      "mul", /*47*/
      "forwordSlash", /*48*/
      "integer", /*51*/
      "string", /*52*/
      "boolean", /*53*/
      "true", /*54*/
      "false", /*55*/
      "stringLit", /*56*/
      "const", /*58*/
      "enum", /*59*/
      "endEnum", /*60*/
      "struct", /*61*/
      "openBraces", 
      "closeBraces", 
      "function", 
      "int", 
      "void",
      "char",
      "class", 
      "comment", 
      "return", 
      "constructor", 
      "method", 
      "field", 
      "static", 
      "null", 
      "this",
      "stringConstant"
   };

   
   typedef struct 
   {
      Token       token;
      uint32_t    lineNumber;
      std::string tokenString;
      double      value;
   }TokenVal;
   TokenVal tokenVal_;

   std::vector<Tokenizer::TokenVal> tokens_;
   
   Tokenizer();

   ~Tokenizer();

   std::vector<Tokenizer::TokenVal> ReadAllTokens();

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

   bool isDoubleQuote(char c);

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

   bool isAnd(char c);

   bool isOr(char c);

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
  

};
#endif