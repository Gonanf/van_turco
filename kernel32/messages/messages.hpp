#ifndef KERNEL32_MESSAGES
#define KERNEL32_MESSAGES

typedef void (*func)(void);
struct _queque_message{
    unsigned int type;
    unsigned int data;
    unsigned int from;
};

class messages{
    private:
    _queque_message queque[MAX_QUEQUE];

    public:
    unsigned int end = 0;
    _queque_message current_message;

    int push(_queque_message msg);

    _queque_message pop();
};


#include"./messages.cpp"

#endif