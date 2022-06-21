#ifndef SIMPLEXPARDER_HPP
#define SIMPLEXPARDER_HPP

#include "Tokenizer.hpp"

class SimplexParser
{
public:
    SimplexParser();
    ~SimplexParser();

    void Parse(std::string programName);

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

  void PrintXml(std::string item, std::string value);
  void PrintOpenTag(std::string item);
  void PrintCloseTag(std::string item);

    private:
    Tokenizer tokenizer_;
    uint32_t token_index_;

    std::vector<Tokenizer::TokenVal> tokens_;

    uint32_t ident_;

};

#endif