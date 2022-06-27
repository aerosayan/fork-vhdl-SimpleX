#ifndef VM_TRANSLATOR_HPP
#define VM_TRANSLATOR_HPP
#include <string>
#include "Tokenizer.hpp"

#include <map>
#include <string.h>
#include <vector>
#include <fstream>

class VmTranslator
{
   public:
    VmTranslator();
   ~VmTranslator();

    bool OpenVmFile(std::string vmfileIn);
  
    void Translate(std::string vmFile);
    void Interpret (std::vector<std::string> components, std::string line);
    void InisialiseSegments();

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
   
    std::ofstream asm_;

    uint32_t label_;
    uint32_t retAddress_;
    uint32_t repeat_;

};

#endif