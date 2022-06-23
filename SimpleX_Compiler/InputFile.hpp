#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP
#include <string>
#include <stdio.h>
#include <vector>

class InputFile
{

public :
    InputFile();

    ~InputFile();

    bool OpenFile(std::string fileName);
    
    void CloseFile(std::string fileName);

    unsigned char GetCurrentCharacter();

    unsigned char GetNextCharacter();

    unsigned int GetCurrentCharacterLocation();
    
    void SetCurrentCharacterLocation(unsigned int position);

private:

   std::vector<char> inputBuffer_;

   unsigned int currentPosition_;

};

#endif
