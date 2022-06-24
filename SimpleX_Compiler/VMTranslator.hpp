#ifndef VM_TRANSLATOR_HPP
#define VM_TRANSLATOR_HPP
#include <string>
#include "Tokenizer.hpp"

#include <map>
#include <string.h>
#include <vector>

class VmTranslator
{
    public:

   typedef enum
   {
      unknownToken_,
      function_,
      dot_,
      identifier_,
      number_,
      push_,
      pop_,
      constantT_,
      argumentT_,
      localT_,
      staticT_,
      fieldT_,
      thisT_,
      thatT_,
      endOfLine_,
      endOfFile_,
      equ_,
      nequ_,
      gt_,
      lt_,
      and_,
      or_,
      not_,
      comma_,
      add_,
      sub_,
      mult_,
      div_,
      openBrackets_,
      closeBrackets_,
      comment_,
      return_,
      ifGoto_,
      goto_
   }Token;

   std::vector<std::string> tokenAsString =  {
      "unknownToken",
      "function",
      "dot",
      "identifier",
      "number",
      "push",
      "pop",
      "constant",
      "argument",
      "local",
      "static",
      "field",
      "this",
      "that",
      "endOfLine",
      "endOfFile",
      "equ",
      "nequ",
      "gt",
      "lt",
      "and",
      "or",
      "not",
      "comma",
      "add",
      "sub",
      "mult",
      "div",
      "openBrackets",
      "closeBrackets",
      "comment",
      "return",
      "ifGoto",
      "goto"
   };

    VmTranslator();
   ~VmTranslator();

    bool OpenVmFile(std::string vmfileIn);
    std::vector<VmTranslator::Token>  TokenizeFile(std::string vmfileIn);
    void PrintAllTokens();
   
    void InisialiseSegments(std::string outputAssemblyFile);
    bool Translate(std::string vmfileIn, std::string vmFileOut);
    VmTranslator::Token GetNextToken();

    private:
    uint32_t SP_;//0),
    uint32_t local_;//1),
    uint32_t argument_;//2),
    uint32_t this_;//3),
    uint32_t that_;//4),
    uint32_t temp_;//5),
    uint32_t static_;//6),
    
    uint32_t SP_pointer_;//10),
    uint32_t local_pointer_;//40),
    uint32_t argument_pointer_;//80),
    uint32_t this_pointer_;//400),
    uint32_t that_pointer_;//500),
    uint32_t temp_pointer_;//600),
    uint32_t static_pointer_;//700),
    uint32_t pointer_pointer_;//800)


    std::map<std::string, std::string> opcode_;
    std::map<std::string, std::string> registers_;

    std::vector<char> inputBuffer_;


    
    void  SkipWhiteSpace();
    bool isCharacter(char c);
    bool isNumber(char c);
    bool isUnderScore(char c);
    bool isDash(char c);
    bool isOpenBrackets(char c);
    bool isCloseBrackets(char c);
    bool isEndOfFile(char c);
    bool isEndOfLine(char c);
    bool isDot(char c);
    bool isForwordSlash(char c);

    VmTranslator::Token CheckToken();

    VmTranslator::Token currentToken_;
    std::vector<Token> tokens_;
    uint32_t currentIndex_;
    char  tokenString_[255];
    uint32_t lineNumber_;

};

#endif