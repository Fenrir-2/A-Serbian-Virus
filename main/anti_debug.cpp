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
void anti_debug::checkDebugged()
{

    try
    {
        if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) //will check if the process is traced, which would equal to a debugger attached
        {
            qDebug() << "I was there";

            throw new std::runtime_error("Debugger detected");
        }
        qDebug() << "Did not enter";
        return;

    }
    catch (std::exception& e) //handle the sigterm or SigSegV
    {

        qDebug() << "Debugger NOT detected";
        exit(-1);
    }
}



