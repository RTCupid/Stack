#include "Stack.h"

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (c) RTCupid, 2024\n\n");
//TODO: typedef for struct
    struct stack_t stk = {0,
                          NULL,
                          NULL,
                          0,
                          0,
                          0,
                          0,
                          0};//TODO: = {} init all 0

    stack_elem_t elem_from_stack = NOT_AN_ELEMENT;

    err_t error = StackCtor (&stk, 5);
    PrintErrorStack (error, "StackCtor");

    StackDump (&stk);

    error = StackPush (&stk, 10);
    PrintErrorStack (error, "StackPush");

    error = StackPush (&stk, 20);
    PrintErrorStack (error, "StackPush");


    error = StackPush (&stk, 30);
    PrintErrorStack (error, "StackPush");

    error = StackPush (&stk, 40);
    PrintErrorStack (error, "StackPush");

    StackDump (&stk);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");

    error = StackDtor (&stk);
    PrintErrorStack (error, "StackDtor");

    printf ("#Stack is destroyed\n");

    printf ("#End of programm");
    return 0;
    }
