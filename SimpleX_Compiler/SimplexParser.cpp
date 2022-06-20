#include "SimplexParser.hpp"
#include <iostream>

 SimplexParser::SimplexParser()
 :token_index_(0)
 {}

 SimplexParser::~SimplexParser()
 {}

 bool SimplexParser::consumeCalssToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::class_)
    {
       printf("<keyword>class</keyword>\n");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected class keywork at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

  bool SimplexParser::consumeIdentifierToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
       printf("<identifier> %s </identifier>\n", tokens_.at(token_index_).tokenString.c_str());
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
       printf("<symbol> { </symbol>\n");
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
       printf("<symbol> } </symbol>\n");
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
       printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
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
       printf("<symbol> , </symbol>\n");
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
       printf("<symbol> ; </symbol>\n");
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
       printf("<symbol> ( </symbol>\n");
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
       printf("<symbol> ) </symbol>\n");
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
       printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
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
       printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
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
       printf("<keyword> %s </keyword>\n", tokens_.at(token_index_).tokenString.c_str());
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
    bool result = false;
    printf("<parameterList>\n"); 
    if (tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
         consumeTypeToken();
         consumeIdentifierToken();
         if (tokens_.at(token_index_).token == Tokenizer::comma_)
         {
           do
           {
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
      
    printf("</parameterList>\n");

    return result;
 }

  bool SimplexParser::consumeLetToken()
  {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::let_)
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

   bool SimplexParser::consumeEqualToken()
  {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::equal_)
    {
       printf("<keyword> = </keyword>\n");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a '=''definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
  }

  bool SimplexParser::consumeExpression()
  {
     consumeIdentifierToken();
     //if (tokens_.at(token_index_).token == Tokenizer::plus_ || tokens_.at(token_index_).token == Tokenizer::minus_ || )

     return true;
  }

 bool SimplexParser::consumeLetStatement()
 {
     bool parseErr = true;
     parseErr = parseErr && consumeLetToken();
     parseErr = parseErr && consumeIdentifierToken();
     parseErr = parseErr && consumeEqualToken();
     parseErr = parseErr && consumeExpression();

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
    if ((tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_ || tokens_.at(token_index_).token == Tokenizer::return_))
    {
       do
       {
          if(tokens_.at(token_index_).token == Tokenizer::let_)
          {
             parseErr = parseErr && consumeLetStatement();
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
    
    return parseErr;
 }


 bool SimplexParser::ConsumeSubroutineBody()
 {
    bool result = false;

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
       do
       {
        parseErr = parseErr && consumeFieldOrStatic();
        parseErr = parseErr && consumeTypeToken();
        parseErr = parseErr && consumeIdentifierToken();
        
        if (tokens_.at(token_index_).token == Tokenizer::comma_)
        {
           do
           {
               parseErr = parseErr && consumeCommaToken();
               parseErr = parseErr && consumeIdentifierToken();
           } while (tokens_.at(token_index_).token == Tokenizer::comma_);
        }
        parseErr = parseErr && consumeSemicolonToken();
        
       } while (tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_);
    }

    if (tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_)
    {
       printf("<%s>\n", tokens_.at(token_index_).tokenString.c_str());
       do
       {
         parseErr = parseErr && consumeConstFunctionMethod();
         parseErr = parseErr && consumeVoidOrType();
         parseErr = parseErr && consumeIdentifierToken();
         parseErr = parseErr && consumeOpenBracketsToken();
        
         parseErr = parseErr && ConsumeParameterList();
         
         parseErr = parseErr && consumeCloseBracketsToken();
         parseErr = parseErr && ConsumeSubroutineBody();
       } while (tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_);

    }

    parseErr = parseErr && consumeCloseBracesToken();

    int tokenInt = (int)tokens_.at(token_index_).token;
    std::cout << tokenizer_.tokenAsString[tokenInt] << "(" << tokens_.at(token_index_).lineNumber << ", " << tokens_.at(token_index_).value << ", " << tokens_.at(token_index_).tokenString << ")" << std::endl;
  
 }