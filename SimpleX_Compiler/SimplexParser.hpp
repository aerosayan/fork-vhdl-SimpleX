#ifndef SIMPLEXPARDER_HPP
#define SIMPLEXPARDER_HPP

#include <map>
#include "Tokenizer.hpp"

class SimplexParser
{
public:
    SimplexParser();
    ~SimplexParser();

    void Parse(std::string programName);

    void PrintClassSymbolTable();

private:
  void PrintCurrentToken();

  bool consumeCalssToken();
  bool consumeIdentifierToken();
  bool consumeOpenBracesToken();
  bool consumeCloseBracesToken();
  bool consumeFieldOrStatic();
  bool consumeCommaToken();
  bool consumeSemicolonToken();
  bool consumeTypeToken();
  bool consumeVoidOrType();

  bool consumeLetToken();
  bool consumeEqualToken();

  bool consumeConstFunctionMethod();
  bool consumeOpenBracketsToken();
  bool consumeCloseBracketsToken();

  bool ConsumeParameterList();

  bool consumeStatements();
  bool ConsumeSubroutineBody();

  bool consumeLetStatement();
  bool consumeExpression();

  bool consumeReturnToken();
  bool consumeReturnStatement();

  bool consumeTerm();
  bool consumeOperation();

   bool consumeIfStatement();
   bool consumeIfToken();

   bool consumeWhileStatement();
   bool consumewhileToken();

  void PrintXml(std::string item, std::string value);
  void PrintOpenTag(std::string item);
  void PrintCloseTag(std::string item);

    private:
    Tokenizer tokenizer_;
    uint32_t token_index_;

    std::vector<Tokenizer::TokenVal> tokens_;

    uint32_t ident_;

   typedef struct 
   {
     std::string type;
     std::string kind;
     uint32_t    index;
   }Symbol;
   
    typedef std::map<std::string, Symbol> memberVariablesTable;
    memberVariablesTable classMemberVarTable;

    typedef std::map<std::string, Symbol> localVariablesTable;
    localVariablesTable localVarTable;

    std::string lastVarName_;
    std::string lastVarType_;

    uint32_t staticVarIndex_;
    uint32_t fieldVarIndex_;

    void AddStaticFieldVariables(std::string kind);
    bool AddToClassSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index);
    
};

#endif