#include "Stack.h"

int main ()
    {
    printf ("# Work with Stack\n");
    printf ("# (c) RTCupid, 2024\n\n");

    stack_t stk = {};

    err_t error = StackCtor (&stk, 4);
    PrintErrorStack (error, "StackCtor");

    printf ("# End of programm");
    return 0;
    }
