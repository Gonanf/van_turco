#ifndef KERNEL32_EXTENSIONS_ELF
#define KERNEL32_EXTENSIONS_ELF

class elf
{
private:
    uint8_t entry_point;
public:
    int wrap(uint8_t* bytes, unsigned int size);
};


#include "./elf.cpp"


#endif