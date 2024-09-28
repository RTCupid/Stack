#include "Stack.h"

// return name of error as const char*.........................................

const char* StackErrorToString(err_t error)
    {
    switch (error)
        {
        case STK_OK: return "OK";
            break;
        case STK_OUT_OF_MEMORY: return "STK OUT OF MEMORY";
            break;
        case STK_REALLOC_FAILED: return "REALLOC FAILED";
            break;
        case STK_STACK_NOT_EXSIST: return "STACK NOT EXSIST";
            break;
        case STK_CAPACITY_NOT_EXSIST: return "CAPACITY NOT EXSIST";
            break;
        case STK_SIZE_LARGER_CAPACITY: return "SIZE LARGER THAN CAPACITY";
            break;
        case STK_EMPTY_STACK: return "EMPTY STACK";
            break;
        default: return "UNCNOWN ERROR";
        }
    }

// function veryfication stack.................................................

err_t Veryficator (stack_t stk)
    {
    if (&stk == NULL)
        return STK_STACK_NOT_EXSIST;
    else if (stk.data == NULL)
        return STK_OUT_OF_MEMORY;
    else if (stk.capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;
    else if (stk.size > stk.capacity)
        return STK_SIZE_LARGER_CAPACITY;
    else
        return STK_OK;
    }

// print error to consol.......................................................

int PrintErrorStack (err_t error)
    {
    if (error)
        {
        printf("Stack error: %s\n", StackErrorToString(error));
        }
    return 1;
    }
