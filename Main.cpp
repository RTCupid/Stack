#include "Stack.h"

int main ()
    {
    printf ("# Work with Stack\n");
    printf ("# (c) RTCupid, 2024\n\n");

    stack_t stk = {};

    stk.data = NULL;

    StackCtor (&stk, 4);

    stk.data = NULL;

    stack_elem_t elem = 0;
    StackPop (&stk, &elem);

    StackDump (&stk);

    printf ("# End of programm");
    return 0;
    }
