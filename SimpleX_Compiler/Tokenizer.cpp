#include "Tokenizer.hpp"
#include <math.h>




Tokenizer::Tokenizer()
: inputFile_(),
tokenLength_(0),
lineNumber_(1)
{
}


Tokenizer::~Tokenizer()
{

}

bool Tokenizer::OpenFile(std::string fileName)
{
   lineNumber_ = 1;

   return inputFile_.OpenFile(fileName);
}


void Tokenizer::CloseFile(std::string fileName)
{
   inputFile_.CloseFile(fileName);
}


unsigned int Tokenizer::GetLineNumber()
{
   return lineNumber_;
}

std::string Tokenizer::String()
{
   return tokenString_;
}

double Tokenizer::GetValue()
{
   return value_;
}

Tokenizer::Token Tokenizer::GetNextToken()
{
  
   currentToken_ = Tokenizer::endOfFile_;
  
   char c;
start:   
   SkipWhiteSpace();

   c = inputFile_.GetCurrentCharacter();

   tokenVal_.token       = unknownToken_;
   tokenVal_.lineNumber  = -1;
   tokenVal_.tokenString = " ";
   tokenVal_.value       = -1;
   
   if(isCharacter(c))
   {
      tokenLength_ = 0;
      while (isCharacter(c) || isNumber(c) || isUnderScore(c))
      {
         tokenString_[tokenLength_++] = c;
         c = inputFile_.GetNextCharacter();
      }
      tokenString_[tokenLength_] = 0;
      currentToken_ = identifier_;
   }

   else if(isNumber(c))
   {
      value_ = 0;
      unsigned int decimal = 0;
      while (isNumber(c))
      {
         value_ = (value_ * 10) + (c - '0');
         c = inputFile_.GetNextCharacter();
      }
      if (isDot(c))
      {
         c = inputFile_.GetNextCharacter();
         while (isNumber(c))
         {
            value_ = (value_ * 10) + (c - '0');
            decimal++;
            c = inputFile_.GetNextCharacter();
         }
         value_ /= powf(10, decimal);
      }
      // else if (isCharacter(c) && c == 'x')
      // {
      //    std::string hex;
      //    c = inputFile_.GetNextCharacter();
      //    while (isNumber(c))
      //    {
      //       hex = hex + c;
      //       c = inputFile_.GetNextCharacter();
      //    }
      //    bool ok = false;
      //    value_= atoi(hex.c_str());
      // }
      currentToken_ = number_;
   }
   else if(isSingleQuote(c))
   {
      tokenLength_ = 0;
      c = inputFile_.GetNextCharacter();
      while (isSingleQuote(c)  == false)
      {
          tokenString_[tokenLength_++] = c;
          c = inputFile_.GetNextCharacter();
      }
      c = inputFile_.GetNextCharacter();
      tokenString_[tokenLength_] = 0;
      currentToken_ = stringConstant_;
   }
   else if(isColon(c))
   {
      currentToken_ = colon_;
      c = inputFile_.GetNextCharacter();
   }

   else if(isDoubleQuote(c))
   {
      tokenLength_ = 0;
      c = inputFile_.GetNextCharacter();
      while (isDoubleQuote(c)  == false)
      {
          tokenString_[tokenLength_++] = c;
          c = inputFile_.GetNextCharacter();
      }
      c = inputFile_.GetNextCharacter();
      tokenString_[tokenLength_] = 0;
      currentToken_ = stringConstant_;
   }

   else if(isComma(c))
   {
      currentToken_ = comma_;
      c = inputFile_.GetNextCharacter();
   }

   else if(isDot(c))
   {
      currentToken_ = dot_;
      c = inputFile_.GetNextCharacter();
   }
   else if(isPlus(c))
   {
      currentToken_ = add_;
      c = inputFile_.GetNextCharacter();
      if (isPlus(c))
      {
         currentToken_ = plusPlus_;
         c = inputFile_.GetNextCharacter();
      }
      if (isEqual(c))
      {
         currentToken_ = plusEqual_;
         c = inputFile_.GetNextCharacter();
      }
   }
   else if(isMinus(c))
   {
      currentToken_ = sub_;
      c = inputFile_.GetNextCharacter();
      if (isMinus(c))
      {
         currentToken_ = minusMinus_;
         c = inputFile_.GetNextCharacter();
      }
      if (isEqual(c))
      {
         currentToken_ = minusEqual_;
         c = inputFile_.GetNextCharacter();
      }
   }
   else if(isNot(c))
   {
      currentToken_ = not_;
      c = inputFile_.GetNextCharacter();
      if (isEqual(c))
      {
         currentToken_ = nequ_;
         c = inputFile_.GetNextCharacter();
      }
   }
   else if(isStar(c))
   {
      currentToken_ = mul_;
      c = inputFile_.GetNextCharacter();
      if (isEqual(c))
      {
         currentToken_ = starEqual_;
         c = inputFile_.GetNextCharacter();
      }
   }
   else if(isForwordSlash(c))
   {
      currentToken_ = forwordSlash_;
      c = inputFile_.GetNextCharacter();
      if (isEqual(c))
      {
         currentToken_ = forwordSlashEqual_;
         c = inputFile_.GetNextCharacter();
      }
      if (isForwordSlash(c))
      {
         //consume all characters till the end of line
         while(!isEndOfLine(c))
         {
            c = inputFile_.GetNextCharacter();
         }
         currentToken_ = comment_;
      }
   }


   else if(isSemiColon(c))
   {
      currentToken_ = semiColon_;
      c = inputFile_.GetNextCharacter();
   }

   else if(isEqual(c))
   {
      currentToken_ = equ_;
      c = inputFile_.GetNextCharacter();
   }

   else if (isBiggerThan(c))
   {
      currentToken_ = gt_;
      c = inputFile_.GetNextCharacter();
      if (isEqual(c))
      {
         currentToken_ = gte_;
         c = inputFile_.GetNextCharacter();
      }
   }

   else if (isSmallerThan(c))
   {
      currentToken_ = lt_;
      c = inputFile_.GetNextCharacter();
      if (isEqual(c))
      {
         currentToken_ = lte_;
         c = inputFile_.GetNextCharacter();
      }
      if (isBiggerThan(c))
      {
         currentToken_ = nequ_;
         c = inputFile_.GetNextCharacter();
      }
   }

   else if(isOpenSquareBracket(c))
   {
      currentToken_ = openSquareBracket_;
      c = inputFile_.GetNextCharacter();
   }

   else if(isCloseSquareBracket(c))
   {
      currentToken_ = closeSquareBracket_;
      c = inputFile_.GetNextCharacter();
   }
   else if(isOpenBrackets(c))
   {
      currentToken_ = openBrackets_;
      c = inputFile_.GetNextCharacter();
   }
   else if(isCloseBrackets(c))
   {
      currentToken_ = closeBrackets_;
      c = inputFile_.GetNextCharacter();
   }
   else if(isOperation(c))
   {
      currentToken_ = operation_;
      c = inputFile_.GetNextCharacter();
   }
   else if(isQuotation(c))
   {
      currentToken_ = stringLit_;
      c = inputFile_.GetNextCharacter();
      
      tokenLength_ = 0;
      while (!isQuotation(c) && (!isEndOfLine(c)))
      {
         tokenString_[tokenLength_++] = c;
         c = inputFile_.GetNextCharacter();
      }
      if (isEndOfLine(c))
      {
         currentToken_ = unknownToken_;
      }
      else
      {
         tokenString_[tokenLength_] = 0;
         currentToken_ = stringLit_;
      }

      c = inputFile_.GetNextCharacter();
   }

   else if (isAnd(c))
   {
      currentToken_ = and_;
      c = inputFile_.GetNextCharacter();
   }

   else if (isOr(c))
   {
      currentToken_ = or_;
      c = inputFile_.GetNextCharacter();
   }

   else if (isOpenBraces(c))
   {
      currentToken_ = openBraces_;
      c = inputFile_.GetNextCharacter();
   }

    else if (isCloseBraces(c))
   {
      currentToken_ = closeBraces_;
      c = inputFile_.GetNextCharacter();
   }


   else if(isEndOfLine(c))
   {
      currentToken_ = endOfLine_;
      c = inputFile_.GetNextCharacter();
      lineNumber_++;
   }
   else if (isEndOfFile(c))
   {
      currentToken_ = endOfFile_;
      c = inputFile_.GetNextCharacter();
   }

   if (currentToken_ == Tokenizer::identifier_)
   {
      currentToken_ = CheckToken();  
   }
    
   tokenVal_.token       = currentToken_;
   tokenVal_.lineNumber  = lineNumber_;
   tokenVal_.tokenString = std::string(tokenString_);
   tokenVal_.value       = value_;
  
   return currentToken_;
}

Tokenizer::Token Tokenizer::CheckToken()
{
   std::string token = String();
   Token thisToken = Tokenizer::identifier_;
   if (token == "IF"|| token == "if"  || token == "If")
   {
      thisToken = Tokenizer::if_;
   }
   else if (token == "ELSEIF" || token == "elseif"  || token == "Elseif")
   {
      thisToken = Tokenizer::elseif_;
   }
   else if (token == "ELSE" || token == "else"  || token == "Else")
   {
      thisToken = Tokenizer::else_;
   }
  
   else if (token == "DO" || token == "do"  || token == "Do")
   {
      thisToken = Tokenizer::do_;
   }
   else if (token == "WHILE" || token == "while" || token == "While")
   {
      thisToken = Tokenizer::while_;
   }
 
   else if (token == "LET" || token == "let"  || token == "Let")
   {
      thisToken = Tokenizer::let_;
   }
   
   else if (token == "AND" || token == "and" || token == "And")
   {
      thisToken = Tokenizer::and_;
   }
   else if (token == "NOT" || token == "not" || token == "Not")
   {
      thisToken = Tokenizer::not_;
   }
   else if (token == "OR" || token == "or" || token == "Or")
   {
      thisToken = Tokenizer::or_;
   }
 
   else if (token == "STRING" || token == "string" || token == "String")
   {
      thisToken = Tokenizer::string_;
   }
   else if (token == "BOOLEAN" || token == "boolean" || token == "Boolean")
   {
      thisToken = Tokenizer::boolean_;
   }
   else if (token == "TRUE" || token == "true" || token == "True")
   {
      thisToken = Tokenizer::true_;
   }
   else if (token == "FALSE" || token == "false" || token == "False")
   {
      thisToken = Tokenizer::false_;
   }

   else if (token == "NULL" || token == "null" || token == "Null")
   {
      thisToken = Tokenizer::null_;
   }

   else if (token == "THIS" || token == "this" || token == "This")
   {
      thisToken = Tokenizer::this_;
   }
  
   else if (token == "CONST" || token == "const" || token == "Const")
   {
      thisToken = Tokenizer::const_;
   }
  
   else if (token == "STRUCTURE" || token == "structure" || token == "Structure")
   {
      thisToken = Tokenizer::struct_;
   }

   else if (token == "FUNCTION"|| token == "function"  || token == "Function")
   {
      thisToken = Tokenizer::function_;
   }

   else if (token == "INT"|| token == "int"  || token == "Int")
   {
      thisToken = Tokenizer::int_;
   }

   else if (token == "CHAR"|| token == "char"  || token == "Char")
   {
      thisToken = Tokenizer::char_;
   }

   // else if (token == "ARRAY"|| token == "array"  || token == "Array")
   // {
   //    thisToken = Tokenizer::array_;
   // }

   else if (token == "CLASS"|| token == "class"  || token == "Class")
   {
      thisToken = Tokenizer::class_;
   }

   else if (token == "RETURN"|| token == "return"  || token == "Return")
   {
      thisToken = Tokenizer::return_;
   }

   else if (token == "CONSTRUCTOR"|| token == "constructor"  || token == "Constructor")
   {
      thisToken = Tokenizer::constructor_;
   }

   else if (token == "METHOD"|| token == "method"  || token == "Method")
   {
      thisToken = Tokenizer::method_;
   }

   else if (token == "FIELD"|| token == "field"  || token == "Field")
   {
      thisToken = Tokenizer::field_;
   }  

   else if (token == "STATIC"|| token == "static"  || token == "Static")
   {
      thisToken = Tokenizer::static_;
   }
  
   return thisToken;
}


bool Tokenizer::isCharacter(char c)
{
   return ((c >= 'a' && c <='z') || (c >= 'A' && c <='Z'));
}


bool Tokenizer::isNumber(char c)
{
   return (c >= '0' && c <='9');
}


bool Tokenizer::isUnderScore(char c)
{
   return (c == '_');
}

bool Tokenizer::isColon(char c)
{
   return (c == ':');
}

bool Tokenizer::isDoubleQuote(char c)
{
   return (c == '"');
}

bool Tokenizer::isComma(char c)
{
   return (c == ',');
}

bool Tokenizer::isPlus(char c)
{
   return (c =='+');
}

bool Tokenizer::isMinus(char c)
{
   return (c =='-');
}

bool Tokenizer::isStar(char c)
{
   return (c == '*');
}

bool Tokenizer::isNot(char c)
{
   return (c == '!');
}

bool Tokenizer::isForwordSlash(char c)
{
   return (c == '/');
}

bool Tokenizer::isSemiColon(char c)
{
   return (c == ';');
}

bool Tokenizer::isDot(char c)
{
   return (c == '.');
}

bool Tokenizer::isOpenSquareBracket(char c)
{
   return (c == '[');
}

bool Tokenizer::isCloseSquareBracket(char c)
{
   return (c == ']');
}

bool Tokenizer::isEqual(char c)
{
   return (c == '=');
}

bool Tokenizer::isBiggerThan(char c)
{
   return (c == '>');
}

bool Tokenizer::isSmallerThan(char c)
{
   return (c == '<');
}

bool Tokenizer::isSingleQuote(char c)
{
   return (c == '\'');
}

bool Tokenizer::isEndOfLine(char c)
{
   bool retVal = false;
   if (c == '\n' || c == 10 || c == 13)
   {
      retVal = true;
   }
   return retVal;
}

bool Tokenizer::isEndOfFile(char c)
{
   return (c == 0xEF);
}

bool Tokenizer::isOpenBrackets(char c)
{
   return (c == '(');
}

bool Tokenizer::isCloseBrackets(char c)
{
   return (c == ')');
}

bool Tokenizer::isOperation(char c)
{
   return (c == '+'  || c == '-' || c == '*' || c == '/');
}

bool Tokenizer::isOpenBraces(char c)
{
   return (c == '{' );
}

bool Tokenizer::isCloseBraces(char c)
{
   return (c == '}' );
}

bool Tokenizer::isQuotation(char c)
{
   return (c =='\"');
}

bool Tokenizer::isAnd(char c)
{
   return (c =='&');
}

bool Tokenizer::isOr(char c)
{
   return (c =='|');
}

void  Tokenizer::SkipWhiteSpace()
{
   char c;
  
   c = inputFile_.GetCurrentCharacter();
   
   while ((c == ' ') || /*(c == 10) || (c == '\n') ||*/ (c =='\t') /*|| (c == 13)||(c == -51)*/)
   {
       c = inputFile_.GetNextCharacter();
   }
}

unsigned int Tokenizer::GetCurrentCharacterLocation()
{
    return inputFile_.GetCurrentCharacterLocation();
}

void Tokenizer::SetCurrentCharacterLocation(unsigned int address)
{
   inputFile_.SetCurrentCharacterLocation(address);
}

void Tokenizer::SetLineNumber(unsigned int lineNumber)
{
   lineNumber_ = lineNumber;
}


std::vector<Tokenizer::TokenVal> Tokenizer::ReadAllTokens()
{
   currentToken_ = unknownToken_;
   tokens_.clear();
   while(currentToken_ != endOfFile_)
   {
      GetNextToken();
      if (currentToken_ != endOfLine_ && currentToken_ != comment_  && currentToken_ != endOfFile_)
      {
          
         tokens_.push_back(tokenVal_);
      }
   }
  

   return tokens_;
}

