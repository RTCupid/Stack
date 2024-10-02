#include "Stack.h"

// return name of error as const char*.........................................

const char* StackErrorToString(err_t error)
    {
    switch (error)
        {
        case STK_OK: return "OK";
            break;
        case STK_CALLOC_FAILED: return "in StackCtor calloc return 'NULL'";
            break;
        case STK_REALLOC_FAILED: return "in StackPush realloc return 'NULL'";
            break;
        case STK_STACK_NOT_EXSIST: return "STACK NOT EXSIST";
            break;
        case STK_BUFFER_NOT_EXSIST: return "BUFFER NOT EXSIST";
            break;
        case STK_CAPACITY_NOT_EXSIST: return "CAPACITY NOT EXSIST";
            break;
        case STK_SIZE_LARGER_CAPACITY: return "SIZE LARGER THAN CAPACITY";
            break;
        case STK_EMPTY_STACK: return "EMPTY STACK";
            break;
        case STK_START_CHICK_STK_DIED: return "start chicken stk is died";                //dump is many printfs with absolutely inf of stack
            break;                                                                        //and addr of all and
        case STK_END_CHICK_STK_DIED: return "end chicken stk is died";                    //two HASHs, if hash error, printf error
            break;
        case STK_START_CHICK_BUF_DIED: return "start chicken buf is died";
            break;
        case STK_END_CHICK_BUF_DIED: return "end chicken buf is died";
            break;
        default: return "UNKNOWN ERROR";
        }
    }

// function veryfication stack.................................................

err_t Veryficator (stack_t stk)
    {
    if (&stk == NULL)
        return STK_STACK_NOT_EXSIST;
    else if (stk.buffer == NULL)
        return STK_BUFFER_NOT_EXSIST;
    else if (stk.capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;
    else if (stk.size > stk.capacity)
        return STK_SIZE_LARGER_CAPACITY;
    else if(stk.chicken_start_stk != ((uint64_t)(&stk) ^ 0x0BEDDEDA))
        return STK_START_CHICK_STK_DIED;
    else if(stk.chicken_end_stk  != ((uint64_t)(&stk) ^ 0xDEDDEDDED))
        return STK_END_CHICK_STK_DIED;
    else if (*(stk.DATA) != 0x0BEDDEDA)
        return STK_START_CHICK_BUF_DIED;
    else if (*(stk->DATA + stk->capacity) = 0xDEDDEDDED)
        return STK_END_CHICK_BUF_DIED;
    else
        return STK_OK;
    }

// print error to consol.......................................................

int PrintErrorStack (err_t error)
    {
    if (error)
        {
        printf("STACK ERROR: %s\n", StackErrorToString(error));
        }
    return 1;
    }
