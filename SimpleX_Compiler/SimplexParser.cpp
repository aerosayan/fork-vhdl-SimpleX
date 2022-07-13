#include "SimplexParser.hpp"
#include <iostream>
#include <fstream>
//#define XML_DEBUG

 SimplexParser::SimplexParser()
 :token_index_(0),
  ident_(0),

  parseError_(false),

  staticVarIndex_(0),
  fieldVarIndex_(0),

  ifStatementStartIndex_(0),
  ifStatementTrueIndex_(0),
  ifStatementFalseIndex_(0),
  ifStatementEndIndex_(0),

  whileStatementStart_(0),
  whileStatementTrue_(0),
  whileStatementFalse_(0),

  passNumber_(1),
  assignedAddress_(500)
 {}

 SimplexParser::~SimplexParser()
 {}

 bool SimplexParser::consumeClassToken()
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
       ErrorMsg("Expected class keyword at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

  bool SimplexParser::consumeDotToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::dot_)
    {
       PrintXml("<symbol>", ".");
       token_index_++;
       result = true;
    }
    else
    {
        ErrorMsg("Expected '.' at Line :" + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected identifier at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected '{' at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected '}' at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected ';' at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected '(' at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected ')' at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

 bool SimplexParser::consumeTypeToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::array_ || tokens_.at(token_index_).token == Tokenizer::identifier_)
    {
       lastVarType_ = tokens_.at(token_index_).tokenString;
       PrintXml("keyword", tokens_.at(token_index_).tokenString);
       token_index_++;
       result = true;
    }
    else
    {
       ErrorMsg("Expected a type definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected a void/type definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected a static/field definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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

         localArgumentNumbers args = {.numOfLocals = 0, .numOfArguments = 0};
         AddToLocalSymbolTable(lastVarName_, lastVarType_, "argument", argumentIndex++, 0);
         currentMethodNumArguments_++;
         if (tokens_.at(token_index_).token == Tokenizer::comma_)
         {
           do
           {
               parameterCount++;
               consumeCommaToken();
               consumeTypeToken();
               consumeIdentifierToken();
               AddToLocalSymbolTable(lastVarName_, lastVarType_, "argument", argumentIndex++, 0);
               currentMethodNumArguments_++;
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
        ErrorMsg("Expected a 'let'  at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
  }

   bool SimplexParser::consumeEqualToken()
  {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::equ_)
    {
       PrintXml("keyword", "=");
       token_index_++;
       result = true;
    }
    else
    {
        ErrorMsg("Expected a '=''  at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected a '[''definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
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
       ErrorMsg("Expected a ']''definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
  }

   bool SimplexParser::consumeExpressionList()
   {
      bool result = false;
      if (tokens_.at(token_index_).token != Tokenizer::closeBrackets_)
      {
         consumeExpression();
         while(tokens_.at(token_index_).token == Tokenizer::comma_)
         {
            consumeCommaToken();
            consumeExpression();
         }
      }

      return result;
   }

  bool SimplexParser::cosumeSubroutineCall()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openBrackets_))
     {
         consumeIdentifierToken();
         std::string callFunction = currentClass_ + "." + lastVarName_;
         consumeOpenBracketsToken();
         consumeExpressionList();
         EmitCode("call " + callFunction + " " + std::to_string(localArgumenNumbers_[callFunction].numOfLocals) + " " + std::to_string(localArgumenNumbers_[callFunction].numOfArguments));
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
         consumeIdentifierToken();
         std::string arrayName = lastVarName_;
         CheckVariableExists(lastVarName_);
         consumeOpenSquareBracketsToken();
         bool exists;
         Symbol sym = GetSymbol(arrayName, exists);
         EmitCode("push constant " + std::to_string(sym.address));
         consumeExpression();
         EmitCode("add");
         EmitCode("pop pointer 1");
         EmitCode("push that 0");
         consumeCloseSquareBracketsToken();
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openBrackets_) )
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         
         cosumeSubroutineCall();
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::dot_) )
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         consumeIdentifierToken();
         currentClass_ = lastVarName_;
         consumeDotToken();
         cosumeSubroutineCall();
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::identifier_) 
     {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         consumeIdentifierToken();
         CheckVariableExists(lastVarName_);
         bool exists;
         Symbol sym = GetSymbol(lastVarName_, exists);
         EmitCode("push " + sym.kind + " " + std::to_string(sym.index));
         result = true;
     }
     else if (tokens_.at(token_index_).token == Tokenizer::number_)
     {
         PrintXml("number",  std::to_string(tokens_.at(token_index_).value));
         EmitCode("push constant " + std::to_string((int)(tokens_.at(token_index_).value)));
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
        ErrorMsg("Expected an expression at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
     }
     return result;
  }

  bool SimplexParser::consumeOperation()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::add_ || tokens_.at(token_index_).token == Tokenizer::sub_ ||
            tokens_.at(token_index_).token == Tokenizer::mul_ || tokens_.at(token_index_).token == Tokenizer::forwordSlash_ ||
            tokens_.at(token_index_).token == Tokenizer::gt_ || tokens_.at(token_index_).token == Tokenizer::lt_|| 
            tokens_.at(token_index_).token == Tokenizer::gte_ || tokens_.at(token_index_).token == Tokenizer::lte_|| 
            tokens_.at(token_index_).token == Tokenizer::and_ || tokens_.at(token_index_).token == Tokenizer::or_ || tokens_.at(token_index_).token == Tokenizer::equ_ || tokens_.at(token_index_).token == Tokenizer::nequ_)
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
     while (tokens_.at(token_index_).token == Tokenizer::add_ || tokens_.at(token_index_).token == Tokenizer::sub_ ||
            tokens_.at(token_index_).token == Tokenizer::mul_ || tokens_.at(token_index_).token == Tokenizer::forwordSlash_ ||
            tokens_.at(token_index_).token == Tokenizer::gt_ || tokens_.at(token_index_).token == Tokenizer::lt_|| 
            tokens_.at(token_index_).token == Tokenizer::gte_ || tokens_.at(token_index_).token == Tokenizer::lte_||
            tokens_.at(token_index_).token == Tokenizer::and_ || tokens_.at(token_index_).token == Tokenizer::or_ || tokens_.at(token_index_).token == Tokenizer::equ_ || tokens_.at(token_index_).token == Tokenizer::nequ_)
      {
         int tokenInt = (int)tokens_.at(token_index_).token;
         PrintXml("operation",  tokenizer_.tokenAsString[tokenInt]);  
         lastOperation_ = tokens_.at(token_index_).token;
         tokenInt = (int)tokens_.at(token_index_).token;
         std::string op = tokenizer_.tokenAsString[tokenInt];
        
         consumeOperation();
         consumeTerm();
         EmitCode(op);
      }
      ident_--;

     return true;
  }

 bool SimplexParser::consumeLetStatement()
 {
     bool parseErr = true;
     parseErr = parseErr && consumeLetToken();
     if (tokens_.at(token_index_).token == Tokenizer::identifier_ && tokens_.at(token_index_ + 1).token == Tokenizer::openSquareBracket_)
     {
         // its like an arr[index]
         parseErr = parseErr && consumeIdentifierToken();
         std::string arrayName = lastVarName_;
         bool exists;
         Symbol destSym = GetSymbol(arrayName, exists);
                 
         consumeOpenSquareBrackets();
         EmitCode("push constant " + std::to_string(destSym.address));
         consumeExpression();
         EmitCode("add");
        
         parseErr = parseErr && consumeCloseSquareBrackets();
         parseErr = parseErr && consumeEqualToken();
         parseErr = parseErr && consumeExpression();
      
         EmitCode("pop temp 0");
         EmitCode("pop pointer 1");
         EmitCode("push temp 0");
         EmitCode("pop that 0");
         parseErr = parseErr && consumeSemicolonToken();
     }
     else
     {
         parseErr = parseErr && consumeIdentifierToken();
         CheckVariableExists(lastVarName_);
         bool exists;
         Symbol sym = GetSymbol(lastVarName_, exists);
         parseErr = parseErr && consumeEqualToken();
         parseErr = parseErr && consumeExpression();
         parseErr = parseErr && consumeSemicolonToken();
        
         EmitCode("pop " + sym.kind + " " + std::to_string(sym.index));
     }
     
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
       ErrorMsg("Expected a 'return' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

  bool SimplexParser::consumeReturnStatement()
 {
     bool parseErr = true;
     parseErr = parseErr && consumeReturnToken();
     if (tokens_.at(token_index_).token != Tokenizer::semiColon_)
     {
        consumeExpression();
      //   consumeIdentifierToken();
      //   bool exists;
      //   Symbol sym = GetSymbol(lastVarName_, exists);
      //   EmitCode("push " + sym.kind + " " + std::to_string(sym.index));
     }
     EmitCode("return");

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
       ErrorMsg("Expected a 'if''definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

 bool SimplexParser::consumeElseToken()
 {
    bool result = false;
    if (tokens_.at(token_index_).token == Tokenizer::else_)
    {
       PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
       token_index_++;
       result = true;
    }
    else
    {
       ErrorMsg("Expected a 'else' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }


 bool SimplexParser::consumeIfStatement()
 {
    bool parseErr = true;
    parseErr = parseErr && consumeIfToken();
    parseErr = parseErr && consumeOpenBracketsToken();
    parseErr = parseErr && consumeExpression();

    uint32_t ifTrue  = ifStatementTrueIndex_++;
    uint32_t ifFalse = ifStatementFalseIndex_++;
    uint32_t ifEnd   = ifStatementEndIndex_++;
    
    EmitCode("if-goto ifTrueStatement_" + std::to_string(ifTrue));
    EmitCode("goto ifFalseStatement_" + std::to_string(ifFalse));
    EmitLabel("ifTrueStatement_" , ifTrue);

    parseErr = parseErr && consumeCloseBracketsToken();
    parseErr = parseErr && consumeOpenBracesToken();
    ident_++;
    
    parseErr = parseErr && consumeStatements();
    EmitCode("goto ifEndStatement_" + std::to_string(ifEnd));
    EmitLabel("ifFalseStatement_" , ifFalse);
    ident_--;
    parseErr = parseErr && consumeCloseBracesToken();
   
    if (tokens_.at(token_index_).token == Tokenizer::else_)
    {
       parseErr = parseErr && consumeElseToken();
       parseErr = parseErr && consumeOpenBracesToken();
       parseErr = parseErr && consumeStatements();
       parseErr = parseErr && consumeCloseBracesToken();
    }
    EmitLabel("ifEndStatement_", ifEnd);
    return parseErr;
 }

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
       ErrorMsg("Expected a 'while' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

 bool SimplexParser::consumeWhileStatement()
 {
    bool parseErr = true;
    uint32_t whileStart = whileStatementStart_++;
    uint32_t whileTrue  = whileStatementTrue_++;
    uint32_t whileFalse = whileStatementFalse_++;
   
    parseErr = parseErr && consumewhileToken();
    parseErr = parseErr && consumeOpenBracketsToken();
    EmitLabel("whileStatementStart_", whileStart);
    parseErr = parseErr && consumeExpression();
    EmitCode("if-goto whileTrueStatement_" + std::to_string(whileTrue));
    EmitCode("goto whileEndStatement_" + std::to_string(whileFalse));
    EmitLabel("whileTrueStatement_", whileTrue);
    parseErr = parseErr && consumeCloseBracketsToken();
    parseErr = parseErr && consumeOpenBracesToken();
    ident_++;
    parseErr = parseErr && consumeStatements();
    ident_--;
    EmitCode("goto whileStatementStart_" + std::to_string(whileStart));
    parseErr = parseErr && consumeCloseBracesToken();
    EmitLabel("whileEndStatement_", whileFalse);
    return parseErr;
 }

  bool SimplexParser::consumeDoStatement()
  {
      bool parseErr = true;
      parseErr = parseErr && consumeDoToken();      
      if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::openBrackets_) )
      {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         
         cosumeSubroutineCall();
         consumeSemicolonToken();
         parseErr = true;
      }
      else if (tokens_.at(token_index_).token == Tokenizer::identifier_ && (tokens_.at(token_index_ + 1).token == Tokenizer::dot_) )
      {
         PrintXml("identifier", tokens_.at(token_index_).tokenString);
         consumeIdentifierToken();
         consumeDotToken();
         cosumeSubroutineCall();
         consumeSemicolonToken();
         parseErr = true;
      }

      return parseErr;
  }

  bool SimplexParser::consumeDoToken()
  {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::do_)
     {
        PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
        token_index_++;
        result = true;
    }
    else
    {
       ErrorMsg("Expected a '.' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
  }

 bool SimplexParser::consumeStatements()
 {
    bool parseErr = true;
    while ((tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_ || tokens_.at(token_index_).token == Tokenizer::return_))
    {
    
    if ((tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_ || tokens_.at(token_index_).token == Tokenizer::return_|| tokens_.at(token_index_).token ==Tokenizer::do_))
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
             parseErr = parseErr && consumeDoStatement();
          }
          else if (tokens_.at(token_index_).token == Tokenizer::return_)
          {
             parseErr = parseErr && consumeReturnStatement();
          }

       } while (tokens_.at(token_index_).token == Tokenizer::let_ || tokens_.at(token_index_).token == Tokenizer::while_ || tokens_.at(token_index_).token == Tokenizer::if_|| tokens_.at(token_index_).token == Tokenizer::return_ ||  tokens_.at(token_index_).token ==Tokenizer::do_);
    }
    }
    
    return parseErr;
 }


 bool SimplexParser::ConsumeSubroutineBody()
 {
    bool parseErr = true;
    uint32_t localIndex = 0;
    
    PrintOpenTag("subroutineBody");
    ident_++;
    parseErr = parseErr && consumeOpenBracesToken();
    while((tokens_.at(token_index_).token == Tokenizer::int_ || tokens_.at(token_index_).token == Tokenizer::boolean_ || tokens_.at(token_index_).token == Tokenizer::char_ || tokens_.at(token_index_).token == Tokenizer::array_ || tokens_.at(token_index_).token == Tokenizer::identifier_)  && (parseErr == true))
    {
       parseErr = parseErr && consumeTypeToken();
       parseErr = parseErr && consumeIdentifierToken();
       AddToLocalSymbolTable(lastVarName_, lastVarType_, "local", localIndex++, 0);
       currentMethodNumLocals_++;
       while ((tokens_.at(token_index_).token == Tokenizer::comma_) && (parseErr == true))
       {
           parseErr = parseErr && consumeCommaToken();
           parseErr = parseErr && consumeIdentifierToken();
           AddToLocalSymbolTable(lastVarName_, lastVarType_, "local", localIndex++, 0);
           currentMethodNumLocals_++;
       }
       consumeSemicolonToken();
    }
    parseErr = parseErr && consumeStatements();
    parseErr = parseErr && consumeCloseBracesToken();
    ident_--;
    EmitCode("\n");
    PrintCloseTag("subroutineBody");

    return parseErr;
 }

 bool SimplexParser::consumeArrayToken()
 {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::array_)
     {
        PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
        token_index_++;
        result = true;
    }
    else
    {
       ErrorMsg("Expected a 'Array' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }
 
 bool SimplexParser::consumeOpenSquareBrackets()
 {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::openSquareBracket_)
     {
        PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
        token_index_++;
        result = true;
    }
    else
    {
       ErrorMsg("Expected a '[' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }
 
 bool SimplexParser::consumeNumber()
 {
     bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::number_)
     {
        PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
        lastVarValue_ = tokens_.at(token_index_).value;
        token_index_++;
         
        result = true;
    }
    else
    {
       ErrorMsg("Expected a '.' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }
 
 bool SimplexParser::consumeCloseSquareBrackets()
 {
    bool result = false;
     if (tokens_.at(token_index_).token == Tokenizer::closeSquareBracket_)
     {
        PrintXml("<keyword>", tokens_.at(token_index_).tokenString.c_str());
        token_index_++;
        result = true;
    }
    else
    {
       ErrorMsg("Expected a ']' definition token at Line : " + std::to_string(tokens_.at(token_index_).lineNumber));
    }

    return result;
 }

 std::vector<std::string> ReadSourceFile(std::string programName)
 {
   std::vector<std::string> prog;
   std::ifstream infile(programName.c_str());
   std::string line;
   while(std::getline(infile, line))
   {
      prog.push_back(line);
   }
   
   return prog;
 }
 

 bool SimplexParser::Parse(std::string programName, uint32_t passNum)
 {
    token_index_ = 0;
    passNumber_ = passNum;
    classMemberVarTable.clear();
    localVarTable.clear();
    sourceCode_.clear();
    sourceCode_ = ReadSourceFile(programName);

    tokenizer_.OpenFile(programName);
    tokens_ = tokenizer_.ReadAllTokens();
    
    bool parseErr = true;
    parseErr = parseErr && consumeClassToken();
    parseErr = parseErr && consumeIdentifierToken();
    currentClass_ = lastVarName_;
    localVarTable.clear();
    AddToClassSymbolTable("this", currentClass_, "argument", 0, 0);
    
    parseErr = parseErr && consumeOpenBracesToken();
   
    if (tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_)
    {
       do
       {
        std::string kind = (tokens_.at(token_index_).token == Tokenizer::static_) ? "static": "field";
       
        parseErr = parseErr && consumeFieldOrStatic();
        if (tokens_.at(token_index_).token == Tokenizer::array_)
        {
            consumeArrayToken();
            consumeIdentifierToken();
            std::string arrayName = lastVarName_;
            consumeOpenSquareBrackets();
            consumeNumber();
            consumeCloseSquareBrackets();
            AddStaticFieldVariables(kind, AllocateAddress());
        }
        else 
        {
            parseErr = parseErr && consumeTypeToken();
            parseErr = parseErr && consumeIdentifierToken();

            AddStaticFieldVariables(kind, 0);
            
            if (tokens_.at(token_index_).token == Tokenizer::comma_)
            {
               do
               {
                     parseErr = parseErr && consumeCommaToken();
                     parseErr = parseErr && consumeIdentifierToken();
                     
                     AddStaticFieldVariables(kind, 0);
                     
               } while (tokens_.at(token_index_).token == Tokenizer::comma_);
            }
        }
        parseErr = parseErr && consumeSemicolonToken();
       } while ((tokens_.at(token_index_).token == Tokenizer::static_ || tokens_.at(token_index_).token == Tokenizer::field_) && (parseErr == true));
    }
   
    while((tokens_.at(token_index_).token == Tokenizer::constructor_ || tokens_.at(token_index_).token == Tokenizer::function_ || tokens_.at(token_index_).token == Tokenizer::method_) && (parseErr == true))
    {
         std::string funcMethodConstr = tokens_.at(token_index_).tokenString;
         PrintOpenTag(funcMethodConstr);
         localVarTable.clear();
         currentMethodNumLocals_ = 0;
         currentMethodNumArguments_ = 0;
         parseErr = parseErr && consumeConstFunctionMethod();
         parseErr = parseErr && consumeVoidOrType();
         
         parseErr = parseErr && consumeIdentifierToken();
         std::string methodName = currentClass_ + "." +  lastVarName_; 
         EmitFunctionLocalAndArgumentNum(methodName);
         parseErr = parseErr && consumeOpenBracketsToken();
   
         parseErr = parseErr && ConsumeParameterList();        
         parseErr = parseErr && consumeCloseBracketsToken();
         
         parseErr = parseErr && ConsumeSubroutineBody();
         localArgumenNumbers_[methodName] = {.numOfLocals =currentMethodNumLocals_, .numOfArguments = currentMethodNumArguments_};
         PrintOpenTag(funcMethodConstr);
         ident_--;
    }

    parseErr = parseErr && consumeCloseBracesToken();
    tokenizer_.CloseFile(programName);
   
   return parseError_;
 }

 uint32_t SimplexParser::AllocateAddress()
 {
    uint32_t address;
    if (passNumber_ == 2)
    {
        address = assignedAddress_ ;
        assignedAddress_ += lastVarValue_;
    }

    return address;
 }

void SimplexParser::AddStaticFieldVariables(std::string kind, uint32_t address)
{
   if (passNumber_ == 2)
   {
      if (kind == "static")
      {
         AddToClassSymbolTable(lastVarName_, lastVarType_, kind, staticVarIndex_++, address);  
      }
      else if(kind == "field")
      {
         AddToClassSymbolTable(lastVarName_, lastVarType_, kind, fieldVarIndex_++, address);
      }
   }
}

 bool SimplexParser::AddToClassSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index, uint32_t address)
 {
    bool result = false;
    
    if (classMemberVarTable.count(symbolName) == 0)
    {
       Symbol symbol = {.type= type, .kind = kind, .index = index, .address = address};
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

 bool SimplexParser::AddToLocalSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index,  uint32_t address)
 {
    bool result = false;
    if (localVarTable.count(symbolName) == 0)
    {
       Symbol symbol = {.type= type, .kind = kind, .index = index, .address = address};
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

  bool SimplexParser::CheckVariableExists(std::string var)
  {
      bool exists = true;
      if (passNumber_ == 2)
      {
         exists = (localVarTable.count(var) == 1) ? true : false;
         if (!exists)
         {
            exists = (classMemberVarTable.count(var) == 1) ? true : false;
         }

         if (!exists)
         {
            ErrorMsg("variable '" + var + "' is not defined at line : " + std::to_string(tokens_.at(token_index_).lineNumber));
            exit(0);
         }
      }
      
      return exists;
  }

  SimplexParser::Symbol SimplexParser::GetSymbol(std::string name, bool& exists)
  {
     exists = false;
     SimplexParser::Symbol sym;
     if (CheckVariableExists(name) == true)
     {
         exists = true;
         bool localyExists = (localVarTable.count(name) == 1) ? true : false;
         if (localVarTable.count(name) == 1)
         {
            sym = localVarTable[name];
           
         }
         else if (classMemberVarTable.count(name) == 1)
         {
             sym = classMemberVarTable[name];
         }
     }

     return sym;
  }

  void SimplexParser::EmitCode(std::string code)
  {
     if (passNumber_ == 2)
     {
        vmCode_.push_back(code + "\n");
     }
  }

  void SimplexParser::EmitLabel(std::string label, uint32_t index)
  {
     if (passNumber_ == 2)
     {
        vmCode_.push_back("(" + label + std::to_string(index) + ")\n");
     }
  }

  void SimplexParser::EmitFunctionLocalAndArgumentNum(std::string methodName)
  {
     if (passNumber_ == 2)
     {
        vmCode_.push_back("function " + methodName + " " + std::to_string(localArgumenNumbers_[methodName].numOfLocals) + " " + std::to_string(localArgumenNumbers_[methodName].numOfArguments) + "\n");
     }
  }
  
  void SimplexParser::GenerateVMCode(std::string outputFile)
  {
    std::ofstream fileOut;
    fileOut.open(outputFile.c_str(), std::ios_base::app);
    for (int i = 0; i < vmCode_.size(); i++)
    {
       fileOut << vmCode_.at(i);
    }
    vmCode_.clear();
    fileOut.close();
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
          std::cout << it->first << "\t\t|" << it->second.type << "\t\t|" << it->second.kind << "\t\t|" << it->second.index << "\t\t|" << it->second.address << std::endl;       
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

  void SimplexParser::PrintLocalArgumentNumbers()
  {
     std::map<std::string, localArgumentNumbers>::iterator it;

     for (it = localArgumenNumbers_.begin(); it != localArgumenNumbers_.end(); it++)
     {
         std::cout << it->first << "\t\t|" << it->second.numOfLocals << "\t\t|" << it->second.numOfArguments << std::endl;       
     }
     
  }


void SimplexParser::PrintGeneratedCode()
{
   for (int i = 0; i < vmCode_.size(); i++)
   {
      std::cout << vmCode_.at(i);
   }
}


void SimplexParser::ErrorMsg(std::string err)
{
   printf("\033[0;31m");
   printf("%s\n", err.c_str()); 
   uint32_t lineNum = tokens_.at(token_index_).lineNumber;
   printf("%d)%s\n", lineNum, sourceCode_.at(lineNum).c_str());
   printf("\033[0m");
   parseError_ = true;
}
  