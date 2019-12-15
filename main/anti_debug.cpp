#include "anti_debug.h"

anti_debug::anti_debug()
{
    bool isDebugged = true;
    try
    {
        __asm(
            "pushfd"
            "or dword ptr[esp], 0x100" // set the Trap Flag
            "popfd"                    // Load the value into EFLAGS register
            "nop"
        );
    }
    catch (EXCEPTION_EXECUTE_HANDLER)
    {
        // If an exception has been raised – debugger is not present
        isDebugged = false;
    }
    if (isDebugged)
    {
        std::cout << "Stop debugging program!" << std::endl;
        exit(-1);
    }
}
