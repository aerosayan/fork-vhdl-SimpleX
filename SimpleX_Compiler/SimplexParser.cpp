#include "SimplexParser.hpp"
#include <iostream>

 SimplexParser::SimplexParser()
 :token_index_(0),
  ident_(0)
 {}

 SimplexParser::~SimplexParser()
 {}

 bool SimplexParser::consumeCalssToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::class_)
    {
       PrintXml("keywod", "class");
       ident_++;
       //printf("<keyword>class</keyword>\n");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected class keyword at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

  bool SimplexParser::consumeIdentifierToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
       PrintXml("identifier", tokens_.at(token_index_).tokenString);
       //ident_++;
       //printf("<identifier> %s </identifier>\n", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected identifier at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeOpenBracesToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::openBraces_)
    {
       PrintXml("symbol", "{");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected '{' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeCloseBracesToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::closeBraces_)
    {
       PrintXml("symbol", "}");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected '}' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeFieldOrStatic()
 {
    bool result = true;
    if (tokens_.at(token_index_).token == Tokenizer::field_ || tokens_.at(token_index_).token == Tokenizer::static_)
    {
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       token_index_++;
       result = true;
    }

    return result;
 }

  bool SimplexParser::consumeCommaToken()
 {
    bool result = true;
    if (tokens_.at(token_index_).token == Tokenizer::comma_)
    {
       PrintXml("symbol", ",");
       token_index_++;
       result = true;
    }

    return result;
 }

  bool SimplexParser::consumeSemicolonToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::semiColon_)
    {
       PrintXml("symbol", ";");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected ';' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

  bool SimplexParser::consumeOpenBracketsToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::openBrackets_)
    {
       PrintXml("symbol", "(");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected '(' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

   bool SimplexParser::consumeCloseBracketsToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::closeBrackets_)
    {
       PrintXml("symbol", ")");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected ')' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeTypeToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a type definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeVoidOrType()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::void_ || tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a void/type definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeConstFunctionMethod()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_)
    {
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       ident_++;
       //printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a void/type definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::ConsumeParameterList()
 {
    int parameterCount = 0;
    bool result = true;
    printf("<parameterList>\n"); 
    if (tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
         parameterCount++;
         consumeTypeToken();
         consumeIdentifierToken();
         if (tokens_.at(token_index_).token == Tokenizer::comma_)
         {
           do
           {
               parameterCount++;
               consumeCommaToken();
               consumeTypeToken();
               consumeIdentifierToken();
           } while (tokens_.at(token_index_).token == Tokenizer::comma_);
        }
   
    }
    else
    {
       result = true;
    }
      
    printf("</parameterList>(%d)\n", parameterCount);

    return result;
 }

  bool SimplexParser::consumeLetToken()
  {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::let_)
    {
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected 'let' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
  }

   bool SimplexParser::consumeEqualToken()
  {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::equal_)
    {
       PrintXml("keyword", "=");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a '=''definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
  }

  bool SimplexParser::consumeTerm()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::identifier_) 
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         token_index_++;
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::number_)
     {
         PrintXml("number",  std::to_string(tokens_.at(token_index_).value));
         token_index_++;
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::openBrackets_)
     {
        consumeOpenBracketsToken();
        consumeExpression();
        result = consumeCloseBracketsToken();
     }
     else
     {
        std::cout << "Expected an expression at Line : " << tokens_.at(token_index_).lineNumber << "\n";
     }
     return result;
  }

  bool SimplexParser::consumeOperation()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::plus_ || tokens_.at(token_index_).token == Tokenizer::minus_ ||
         tokens_.at(token_index_).token == Tokenizer::star_ || tokens_.at(token_index_).token == Tokenizer::forwordSlash_ ||
         tokens_.at(token_index_).token == Tokenizer::biggerThan_ || tokens_.at(token_index_).token == Tokenizer::smallerThan_)
         {
            token_index_++;
            result = true;
         }

   return result;
  }

  bool SimplexParser::consumeExpression()
  {
     consumeTerm();
     while (tokens_.at(token_index_).token == Tokenizer::plus_ || tokens_.at(token_index_).token == Tokenizer::minus_ ||
            tokens_.at(token_index_).token == Tokenizer::star_ || tokens_.at(token_index_).token == Tokenizer::forwordSlash_ ||
            tokens_.at(token_index_).token == Tokenizer::biggerThan_ || tokens_.at(token_index_).token == Tokenizer::smallerThan_)
      {
         int tokenInt = (int)tokens_.at(token_index_).token;
         PrintXml("operation",  tokenizer_.tokenAsString[tokenInt]);  
         consumeOperation();
         consumeTerm();
      }

     return true;
  }

 bool SimplexParser::consumeLetStatement()
 {
     bool parseErr = true;
     parseErr = parseErr && consumeLetToken();
     parseErr = parseErr && consumeIdentifierToken();
     parseErr = parseErr && consumeEqualToken();
     parseErr = parseErr && consumeExpression();
     parseErr = parseErr && consumeSemicolonToken();
     
     return parseErr;
 }

 bool SimplexParser::consumeReturnToken()
 {
     bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::return_)
    {
       printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected 'let' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

  bool SimplexParser::consumeReturnStatement()
 {
     bool parseErr = true;
     parseErr = parseErr && consumeReturnToken();
     if (tokens_.at(token_index_).token == Tokenizer::identifier_)
     {
        consumeIdentifierToken();
     }

     consumeSemicolonToken();

     return parseErr;
 }

 bool SimplexParser::consumeStatements()
 {
    bool parseErr = true;
    while ((tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_ || tokens_.at(token_index_).token == Tokenizer::return_))
    {
    
    if ((tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_ || tokens_.at(token_index_).token == Tokenizer::return_))
    {
       do
       {
          if(tokens_.at(token_index_).token == Tokenizer::let_)
          {
             consumeLetStatement();
          }
          else if (tokens_.at(token_index_).token == Tokenizer::while_)
          {
             //parseErr = parseErr && consumeWhileStatement(token);
          }
          else if (tokens_.at(token_index_).token == Tokenizer::if_)
          {
             //parseErr = parseErr && consumeIfStatement(token);
          }
          else if (tokens_.at(token_index_).token == Tokenizer::return_)
          {
             parseErr = parseErr && consumeReturnStatement();
          }

       } while (tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_|| tokens_.at(token_index_).token == Tokenizer::return_);
    }
    }
    
    return parseErr;
 }


 bool SimplexParser::ConsumeSubroutineBody()
 {
    bool result = true;

    printf("<subroutineBody>\n");

    consumeOpenBracesToken();
    consumeStatements();
    consumeCloseBracesToken();
   
    printf("</subroutineBody>\n");
    return result;
 }

 void SimplexParser::Parse(std::string programName)
 {
    token_index_ = 0;
    tokenizer_.OpenFile(programName);

    tokens_ = tokenizer_.ReadAllTokens();

    bool parseErr = true;
    parseErr = parseErr && consumeCalssToken();
    parseErr = parseErr && consumeIdentifierToken();
    parseErr = parseErr && consumeOpenBracesToken();
    
    if (tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_)
    {
       int localCount = 0;
       do
       {
        parseErr = parseErr && consumeFieldOrStatic();
        parseErr = parseErr && consumeTypeToken();
        parseErr = parseErr && consumeIdentifierToken();
        localCount++;
        if (tokens_.at(token_index_).token == Tokenizer::comma_)
        {
           do
           {
               parseErr = parseErr && consumeCommaToken();
               parseErr = parseErr && consumeIdentifierToken();
               localCount++;
           } while (tokens_.at(token_index_).token == Tokenizer::comma_);
        }
        parseErr = parseErr && consumeSemicolonToken();
        
       } while (tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_);
    }

    if (tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_)
    {
       do
       {
         std::string funcMethodConstr = tokens_.at(token_index_).tokenString;
         printf("<%s>\n", funcMethodConstr.c_str());

         parseErr = parseErr && consumeConstFunctionMethod();
         parseErr = parseErr && consumeVoidOrType();
         parseErr = parseErr && consumeIdentifierToken();
         parseErr = parseErr && consumeOpenBracketsToken();
        
         ConsumeParameterList();
         
         consumeCloseBracketsToken();
         
         ConsumeSubroutineBody();
         printf("</%s>\n", funcMethodConstr.c_str());
         //PrintCurrentToken();
       } while (tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_);
       
    }

    parseErr = parseErr && consumeCloseBracesToken();

 }

  void SimplexParser::PrintXml(std::string item, std::string value)
  {
     for(int i = 0; i < (ident_*3) ; i++)
     {
        printf(" ");
     }
     printf("<%s> %s </%s>\n", item.c_str(), value.c_str(), item.c_str());
  }

 void SimplexParser::PrintCurrentToken()
 {
    int tokenInt = (int)tokens_.at(token_index_).token;
    std::cout << "====== " << tokenizer_.tokenAsString[tokenInt] << "=======" << std::endl;
 }