#ifndef SIMPLEXPARDER_HPP
#define SIMPLEXPARDER_HPP

#include <map>
#include "Tokenizer.hpp"

class SimplexParser
{
public:
    SimplexParser();
    ~SimplexParser();

    bool Parse(std::string programName, uint32_t passNum);

    void PrintClassSymbolTable();
    void PrintLocalSymbolTable();
    void PrintLocalArgumentNumbers();

    void PrintGeneratedCode();

private:
  void PrintCurrentToken();

  bool consumeClassToken();
  bool consumeIdentifierToken();
  bool consumeOpenBracesToken();
  bool consumeCloseBracesToken();
  bool consumeFieldOrStatic();
  
  bool consumeTypeToken();
  bool consumeVoidOrType();
  bool consumeCommaToken();
  bool consumeSemicolonToken();

  bool consumeConstFunctionMethod();
  bool consumeOpenBracketsToken();
  bool ConsumeParameterList();
  bool consumeCloseBracketsToken();
  bool ConsumeSubroutineBody();

  bool consumeOpenSquareBracketsToken();
  bool consumeCloseSquareBracketsToken();

  bool consumeStatements();
 
  bool consumeLetStatement();
  bool consumeLetToken();
  bool consumeEqualToken();
  bool consumeExpression();

  bool consumeReturnStatement();
  bool consumeReturnToken();
  
  bool consumeTerm();
  bool consumeOperation();

  bool consumeIfStatement();
  bool consumeIfToken();
  bool consumeElseToken();

  bool consumeWhileStatement();
  bool consumewhileToken();

  bool consumeDoStatement();
  bool consumeDoToken();

  bool cosumeSubroutineCall();
  bool consumeExpressionList();
  bool consumeDotToken();
  
  void PrintXml(std::string item, std::string value);
  void PrintOpenTag(std::string item);
  void PrintCloseTag(std::string item);

  void EmitCode(std::string code);
  void EmitLabel(std::string label, uint32_t index);
  void EmitFunctionLocalAndArgumentNum(std::string methodName);

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

   typedef struct 
   {
     uint32_t numOfLocals;
     uint32_t numOfArguments;
   }localArgumentNumbers;
   
   
    typedef std::map<std::string, Symbol> memberVariablesTable;
    memberVariablesTable classMemberVarTable;

    typedef std::map<std::string, Symbol> localVariablesTable;
    localVariablesTable localVarTable;

    typedef std::map<std::string, localArgumentNumbers> LocalArgumenNumbers;
    LocalArgumenNumbers localArgumenNumbers_;

    uint32_t currentMethodNumArguments_;
    uint32_t currentMethodNumLocals_;

    std::string lastVarName_;
    std::string lastVarType_;
    Tokenizer::Token lastOperation_;

    uint32_t staticVarIndex_;
    uint32_t fieldVarIndex_;

    uint32_t ifStatementStartIndex_;
    uint32_t ifStatementTrueIndex_;
    uint32_t ifStatementFalseIndex_;
    uint32_t ifStatementEndIndex_;

    uint32_t whileStatementStart_;
    uint32_t whileStatementTrue_;
    uint32_t whileStatementFalse_;

    void AddStaticFieldVariables(std::string kind);
    bool AddToClassSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index);
    bool AddToLocalSymbolTable(std::string symbolName, std::string type, std::string kind, uint32_t index);
    bool CheckVariableExists(std::string var);
    SimplexParser::Symbol GetSymbol(std::string name, bool& exists);
    void ErrorMsg(std::string err);

    std::vector<std::string> vmCode_;

    bool parseError_;
    std::string currentClass_;

    uint32_t passNumber_;
    
};

#endif