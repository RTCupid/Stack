#include "Stack.h"

int main ()
    {
    printf ("# Work with Stack\n");
    printf ("# (c) RTCupid, 2024\n\n");

    stack_t stk = {};
    StackCtor (&stk, 4);

    StackPush (&stk, 40);
    stack_elem_t a = 0;
    StackPop (&stk, &a);

    StackDtor (&stk);

    printf ("# End of programm");
    return 0;
    }
