#include "SimplexParser.hpp"
#include <iostream>

 SimplexParser::SimplexParser()
 :token_index_(0),
  ident_(0),
  staticVarIndex_(0),
  fieldVarIndex_(0)
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
       lastVarName_ = tokens_.at(token_index_).tokenString;
       PrintXml("identifier", tokens_.at(token_index_).tokenString);
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
       lastVarType_ = tokens_.at(token_index_).tokenString;
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
    uint32_t argumentIndex = 0;
    PrintOpenTag("parameterList");
    if (tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
         parameterCount++;
         consumeTypeToken();
         consumeIdentifierToken();
         AddToLocalSymbolTable(lastVarName_, lastVarType_, "argument", argumentIndex++);
         if (tokens_.at(token_index_).token == Tokenizer::comma_)
         {
           do
           {
               parameterCount++;
               consumeCommaToken();
               consumeTypeToken();
               consumeIdentifierToken();
               AddToLocalSymbolTable(lastVarName_, lastVarType_, "argument", argumentIndex++);
           } while (tokens_.at(token_index_).token == Tokenizer::comma_);
        }
   
    }
    else
    {
       result = true;
    }
    PrintCloseTag("parameterList");  

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

  bool SimplexParser::consumeOpenSquareBracketsToken()
  {
     bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::openSquareBracket_)
    {
       PrintXml("keyword", "[");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a '[''definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
  }

  bool SimplexParser::consumeCloseSquareBracketsToken()
  {
     bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::closeSquareBracket_)
    {
       PrintXml("keyword", "[");
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected a ']' definition token at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
  }

   bool SimplexParser::consumeExpressionList()
   {
      bool result = false;
      consumeExpression();
      while(tokens_.at(token_index_).token == Tokenizer::comma_)
      {
         consumeCommaToken();
         consumeExpression();
      }

      return result;
   }

  bool SimplexParser::cosumeSubroutineCall()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openBrackets_))
     {
         consumeIdentifierToken();
         consumeOpenBracketsToken();
         consumeExpressionList();
         consumeCloseBracketsToken();
         result = true;
     }

     return result;
  }

  bool SimplexParser::consumeTerm()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openSquareBracket_) )
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         token_index_++;
         consumeOpenSquareBracketsToken();
         consumeExpression();
         consumeCloseSquareBracketsToken();
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openBrackets_) )
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         
         cosumeSubroutineCall();
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::identifier_) 
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
            tokens_.at(token_index_).token == Tokenizer::biggerThan_ || tokens_.at(token_index_).token == Tokenizer::smallerThan_|| 
            tokens_.at(token_index_).token == Tokenizer::and_ || tokens_.at(token_index_).token == Tokenizer::or_ || tokens_.at(token_index_).token == Tokenizer::equal_)
         {
            token_index_++;
            result = true;
         }

   return result;
  }

  bool SimplexParser::consumeExpression()
  {
     ident_++;
     consumeTerm();
     while (tokens_.at(token_index_).token == Tokenizer::plus_ || tokens_.at(token_index_).token == Tokenizer::minus_ ||
            tokens_.at(token_index_).token == Tokenizer::star_ || tokens_.at(token_index_).token == Tokenizer::forwordSlash_ ||
            tokens_.at(token_index_).token == Tokenizer::biggerThan_ || tokens_.at(token_index_).token == Tokenizer::smallerThan_|| 
            tokens_.at(token_index_).token == Tokenizer::and_ || tokens_.at(token_index_).token == Tokenizer::or_ || tokens_.at(token_index_).token == Tokenizer::equal_)
      {
         int tokenInt = (int)tokens_.at(token_index_).token;
         PrintXml("operation",  tokenizer_.tokenAsString[tokenInt]);  
         consumeOperation();
         consumeTerm();
      }
      ident_--;

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
       PrintXml("keyword", tokens_.at(token_index_).tokenString.c_str());
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

 bool SimplexParser::consumeIfToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::if_)
    {
       PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected 'let' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeIfStatement()
 {
    bool parseErr = true;
    parseErr = parseErr && consumeIfToken();
    parseErr = parseErr && consumeOpenBracketsToken();
    parseErr = parseErr && consumeExpression();
    parseErr = parseErr && consumeCloseBracketsToken();
    parseErr = parseErr && consumeOpenBracesToken();
    ident_++;
    parseErr = parseErr && consumeStatements();
    ident_--;
    parseErr = parseErr && consumeCloseBracesToken();

    return parseErr;
 }

//   bool SimplexParser::consumeDoStatement()
//   {
//      bool parseErr = true;
//      parseErr = parseErr && consumeDoToken();
//      parseErr = parseErr && consumeIdentifierToken();

//   }

 bool SimplexParser::consumewhileToken()
 {
     bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::while_)
    {
       PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       std::cout << "Expected 'while' at Line : " << tokens_.at(token_index_).lineNumber << "\n";
    }

    return result;
 }

 bool SimplexParser::consumeWhileStatement()
 {
    bool parseErr = true;
    parseErr = parseErr && consumewhileToken();
    parseErr = parseErr && consumeOpenBracketsToken();
    parseErr = parseErr && consumeExpression();
    parseErr = parseErr && consumeCloseBracketsToken();
    parseErr = parseErr && consumeOpenBracesToken();
    ident_++;
    parseErr = parseErr && consumeStatements();
    ident_--;
    parseErr = parseErr && consumeCloseBracesToken();

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
             parseErr = parseErr && consumeWhileStatement();
          }
          else if (tokens_.at(token_index_).token == Tokenizer::if_)
          {
             parseErr = parseErr && consumeIfStatement();
          }
          else if (tokens_.at(token_index_).token == Tokenizer::do_)
          {
             //parseErr = parseErr && consumeDoStatement();
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
    bool parseErr = true;
    uint32_t localIndex = 0;

    localVarTable.clear(); //clear the local scope of the method/function
    PrintOpenTag("subroutineBody");
    ident_++;
    parseErr = parseErr && consumeOpenBracesToken();
    while((tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::identifier_)  && (parseErr == true))
    {
       parseErr = parseErr && consumeTypeToken();
       parseErr = parseErr && consumeIdentifierToken();
       AddToLocalSymbolTable(lastVarName_, lastVarType_, "local", localIndex++);
       while ((tokens_.at(token_index_).token == Tokenizer::comma_) && (parseErr == true))
       {
           parseErr = parseErr && consumeCommaToken();
           parseErr = parseErr && consumeIdentifierToken();
           AddToLocalSymbolTable(lastVarName_, lastVarType_, "local", localIndex++);
       }
       consumeSemicolonToken();
    }
    parseErr = parseErr && consumeStatements();
    parseErr = parseErr && consumeCloseBracesToken();
    ident_--;
    
    PrintCloseTag("subroutineBody");

    return parseErr;
 }

 void SimplexParser::Parse(std::string programName)
 {
    token_index_ = 0;
    tokenizer_.OpenFile(programName);

    tokens_ = tokenizer_.ReadAllTokens();

    bool parseErr = true;
    parseErr = parseErr && consumeCalssToken();
    parseErr = parseErr && consumeIdentifierToken();
    AddToClassSymbolTable("this", lastVarName_, "argument", 0);
    
    parseErr = parseErr && consumeOpenBracesToken();
   
    if (tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_)
    {
       int localCount = 0;
       do
       {
        std::string kind = (tokens_.at(token_index_).token == Tokenizer::static_) ? "static": "field";
       
        parseErr = parseErr && consumeFieldOrStatic();
        parseErr = parseErr && consumeTypeToken();
        parseErr = parseErr && consumeIdentifierToken();

        AddStaticFieldVariables(kind);
      
        localCount++;
        if (tokens_.at(token_index_).token == Tokenizer::comma_)
        {
           do
           {
               parseErr = parseErr && consumeCommaToken();
               parseErr = parseErr && consumeIdentifierToken();
               
               AddStaticFieldVariables(kind);
               
               localCount++;
           } while (tokens_.at(token_index_).token == Tokenizer::comma_);
        }
        parseErr = parseErr && consumeSemicolonToken();
       } while ((tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_) && (parseErr == true));
    }
    //printf("I am here parseError = %s\n", (parseErr) ? "true": "false");
    while((tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_) && (parseErr == true))
    {
        std::string funcMethodConstr = tokens_.at(token_index_).tokenString;
         PrintOpenTag(funcMethodConstr);
 
         parseErr = parseErr && consumeConstFunctionMethod();
         parseErr = parseErr && consumeVoidOrType();
         parseErr = parseErr && consumeIdentifierToken();
         parseErr = parseErr && consumeOpenBracketsToken();
   
         parseErr = parseErr && ConsumeParameterList();        
         parseErr = parseErr && consumeCloseBracketsToken();
         
         parseErr = parseErr && ConsumeSubroutineBody();
         
         PrintOpenTag(funcMethodConstr);
         ident_--;
    }

    parseErr = parseErr && consumeCloseBracesToken();

 }

void SimplexParser::AddStaticFieldVariables(std::string kind)
{
   if (kind == "static")
   {
      AddToClassSymbolTable(lastVarName_, lastVarType_, kind, staticVarIndex_++);
   }
   else if(kind == "field")
   {
      AddToClassSymbolTable(lastVarName_, lastVarType_, kind, fieldVarIndex_++);
   }
}

 bool SimplexParser::AddToClassSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index)
 {
    bool result = false;
    if (classMemberVarTable.count(symbolName) == 0)
    {
       Symbol symbol = {.type= type, .kind = kind, .index = index};
       classMemberVarTable[symbolName] = symbol;
       result = true;
    }
    else
    {
       printf("Error:: The %s %s already defined in the current scope\n", type.c_str(), symbolName.c_str());
       exit(0);
    }

    return result;
 }

 bool SimplexParser::AddToLocalSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index)
 {
    bool result = false;
    if (localVarTable.count(symbolName) == 0)
    {
       Symbol symbol = {.type= type, .kind = kind, .index = index};
       localVarTable[symbolName] = symbol;
       result = true;
    }
    else
    {
       printf("Error:: The %s %s already defined in the current scope\n", type.c_str(), symbolName.c_str());
       exit(0);
    }

    return result;
 }

  void SimplexParser::PrintXml(std::string item, std::string value)
  {
     #ifdef XML_DEBUG
     for(int i = 0; i < (ident_*3) ; i++)
     {
        printf(" ");
     }
     printf("<%s> %s </%s>\n", item.c_str(), value.c_str(), item.c_str());
     #endif
  }

  void SimplexParser::PrintOpenTag(std::string item)
  {
     #ifdef XML_DEBUG
     for(int i = 0; i < (ident_*3) ; i++)
     {
        printf(" ");
     }
     printf("<%s>\n", item.c_str());
     #endif
  }

  void SimplexParser::PrintCloseTag(std::string item)
  {
     #ifdef XML_DEBUG
     for(int i = 0; i < (ident_*3) ; i++)
     {
        printf(" ");
     }
     printf("</%s>\n", item.c_str());
     #endif
  }

 void SimplexParser::PrintCurrentToken()
 {
    int tokenInt = (int)tokens_.at(token_index_).token;
    std::cout << "====== " << tokenizer_.tokenAsString[tokenInt] << "=======" << std::endl;
 }

  void SimplexParser::PrintClassSymbolTable()
  {
     std::map<std::string, Symbol>::iterator it;

     for (it = classMemberVarTable.begin(); it != classMemberVarTable.end(); it++)
     {
         std::cout << it->first << "\t\t|" << it->second.type << "\t\t|" << it->second.kind << "\t\t|" << it->second.index << std::endl;       
     }
  }

  void SimplexParser::PrintLocalSymbolTable()
  {
     std::map<std::string, Symbol>::iterator it;

     for (it = localVarTable.begin(); it != localVarTable.end(); it++)
     {
         std::cout << it->first << "\t\t|" << it->second.type << "\t\t|" << it->second.kind << "\t\t|" << it->second.index << std::endl;       
     }
  }