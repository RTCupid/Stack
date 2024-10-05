#include "Stack.h"

int main ()
    {
    printf ("# Work with Stack\n");
    printf ("# (c) RTCupid, 2024\n\n");

    stack_t stk = {};
    StackCtor (&stk, 4);


    StackPush (&stk, 1);


    err_t error = StackDump (nullptr);
    PrintErrorStack (error, "StackDump");

    printf ("# End of programm");
    return 0;
    }
