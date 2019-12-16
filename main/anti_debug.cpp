#include "anti_debug.h"
#include <QtWidgets>
#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#define DBG_PRINTEXCEPTION_WIDE_C 0x4001000A

anti_debug::anti_debug()
{
}
void checkDebugged()
{

    try
    {
        if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) //will check if the process is traced, which would equal to a debugger attached
        {

            throw new std::runtime_error("Debugger detected");
        }

    }
    catch (std::exception& e) //handle the sigterm or SigSegV
    {
        printf("Debugger NOT detected");
        exit(-1);
    }
}



