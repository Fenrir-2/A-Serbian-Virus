#ifndef OBFUSCATION_H
#define OBFUSCATION_H
#include "anti_debug.h"
#include "crypto.h"
#include "anti_reverse.h"


class Obfuscation : public anti_debug, public crypto,  public anti_reverse
{
public:
    Obfuscation();
};

#endif // OBFUSCATION_H
