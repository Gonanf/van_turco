#include "./logs.hpp"
#include"pico/stdlib.h"

template<typename ... Args>
int print(const char *format, Args... args){
    #ifdef __DEBUG
    return printf(format,args);
    #else
    return 0;
    #endif
}