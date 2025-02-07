#include"./messages.hpp"
#include"pico/stdlib.h"
int messages::push(_queque_message msg){
        if (this->end >= MAX_QUEQUE){
            return -1;
        }
        KERNEL32::print("END: %d / ",this->end);
        this->queque[this->end++] = msg;
        KERNEL32::print("%d (%d/%d)\n",this->end,this->queque[this->end-1].type,this->queque[this->end-1].data);
        return this->end;
    }

_queque_message messages::pop(){
        _queque_message msg = this->queque[--this->end];
        KERNEL32::print("POP: %d/%d\n",msg.type,msg.data);
        return msg;
    }
