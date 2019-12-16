#ifndef ANTI_DEBUG_H
#define ANTI_DEBUG_H
#include <sys/ptrace.h>
#include <exception>

class anti_debug
{
public:
    anti_debug();
    void checkDebugged();
};

#endif // ANTI_DEBUG_H
