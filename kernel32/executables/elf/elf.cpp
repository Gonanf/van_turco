#include "./elf.hpp"
#include "pico/stdlib.h"

int elf::wrap(uint8_t* bytes, unsigned int size)
{
    /*The elf header is 52 in 32 bits, if is less or equal than that, it is not in a correct format or there is not code*/
    if (size == 0 || size <= 52){
        return -1; /*Not enought size for header*/
    }

    char elf_magic_id[4] = {0x7F,0x45,0x4c,0x46};

    unsigned int pos = 0;
    /*First 4 bytes are the elf id*/
    for (int i = 0; i < 4; i++){
        if (bytes[i] != elf_magic_id[i]){
            return -2; /*Not an ELF format*/
        }
    }

    /*Next byte determines 32 or 64 bits*/
    if (bytes[4] != 1){
        return -3; /*Not an 32 bits program*/
    }

    /*Next byte determines indianess*/
    if (bytes[5] != 1){
        return -4; /*Not an little-indian*/
    }

    /*Next byte 6 is elf version, skipping*/
    /*Next byte 7 is ABI ID, skipping (for now)*/
    /*Next byte 8 is ABI Version, skipping (for now)*/
    /*Next 7 bytes (15) are padding, skipping*/
    /*Next 2 bytes (17) are the object type, skipping (for now)*/

    /*Next byte is processor instruction set*/
    if (bytes[18] != 0x28){
        return -5; /*Not in ARM 32 architecture*/
    }

    /*Next byte 19 is the continuation of the ISA, skipping*/
    /*Next 4 bytes (23) are the e_version, skipping*/

    /*Next 4 bytes are the entry point memory address, it should be modified by bob_tail*/
    if ((int)*(bytes + 23) == 0){
        return -6; /*Invalid entry point*/
    }

    /*If the entry point expands certain offset (The flash limit for example), change into the device driver with the file system*/
    this->entry_point = (int)*(bytes + 23);
    KERNEL32::print("entry: %p",this->entry_point);

 return 0;


}

