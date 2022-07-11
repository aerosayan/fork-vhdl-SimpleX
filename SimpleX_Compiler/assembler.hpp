#ifndef ASSEMBLER_HPP__
#define ASSEMBLER_HPP__

#include <map>
#include <vector>
#include <fstream>

class Assembler
{
public:

   Assembler();
   ~Assembler();
   std::vector<std::string> splitString(std::string text);
   void pass1(std::string assemblyFile);
   void assemble(std::string assemblyFile);
   void CreateHexFile();

   private:
   std::map<std::string, std::string> opcode_;
   std::map<std::string, std::string> registers_;

   std::map<std::string, uint32_t> labelTable_;

   std::ofstream asm_;
   
   std::vector<std::string> program_;

   std::vector<std::string> hexProgram_;

};


#endif