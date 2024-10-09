#include "Stack.h"

// StackAssert.................................................................

err_t StackAssert (stack_t* stk, const char* namefnc)
    {
    err_t error = Veryficator (stk);
    if (error)
        {
        StackDump (stk);
        PrintErrorStack (error, namefnc);
        assert (0);
        }
    return STK_OK;
    }

//Input all info about stack...................................................

err_t StackDump (stack_t* stk)
    {
                         //todo cool storage of errors
    // int errors = 0;
    // //000000001 = 1
    // //000000010 = 2
    // if ()
    // {
    //     errors = errors | 1;
    // }
    // //10101010
    // if(errors & 2)
    // {
    //     printf()
    // }
    if (stk == NULL)
        return INVALID_POINTER;

    printf ("Stack Dump:\n");
#ifdef USE_CANARIES
    printf ("  chicken_start_stk = <%llu>\n", stk->chicken_start_stk);
    printf ("  chicken_end_stk   = <%llu>\n\n", stk->chicken_end_stk);

    printf ("  &stk.DATA         = <%p>\n", &stk->data);
    printf ("  stk.DATA          = <%p>\n\n", stk->data);
#endif

    printf ("  &stk.buffer       = <%p>\n", &stk->buffer);
    printf ("  stk.buffer        = <%p>\n\n", stk->buffer);

    printf ("  size_t size       = <%lld>\n", stk->size);
    printf ("  size_t capacity   = <%lld>\n\n", stk->capacity);

#ifdef USE_HASH
    printf ("  hash_t hashBuf    = <%llu>\n", stk->hashBuf);
    printf ("  hash_t hashStk    = <%llu>\n\n", stk->hashStk);
#endif

    PrintSTK (stk);

    return STK_OK;
    }

// return name of error as const char*.........................................

const char* StackErrorToString(err_t error)
    {
    switch (error)
        {
        case STK_OK:                   return "OK";
        case STK_NOT_EXSIST:           return "Stack not exsist";
        case STK_DATA_NOT_EXSIST:      return "data of stack not exsist";
        case STK_BUFFER_NOT_EXSIST:    return "buffer of stack not exsist";
        case STK_CALLOC_FAILED:        return "in StackCtor calloc return 'NULL'";              //make alignment (est)
        case STK_STACKCTOR_AGAIN:      return "Stack is already construction";
        case STK_REALLOC_FAILED:       return "in StackPush realloc return 'NULL'";
        case STK_CAPACITY_NOT_EXSIST:  return "Capacity not Exsist";
        case STK_SIZE_LARGER_CAPACITY: return "Size Larger than Capacity";
        case STK_EMPTY_STACK:          return "Empty Stack";
        case INVALID_POINTER:          return "Invalid Pointer";
        case STK_START_CHICK_STK_DIED: return "start chicken stk is died";     //dump is many printfs with absolutely inf of stack                                                                       //and addr of all and
        case STK_END_CHICK_STK_DIED:   return "end chicken stk is died";       //two HASHs, if hash error, printf error
        case STK_START_CHICK_BUF_DIED: return "start chicken buf is died";
        case STK_END_CHICK_BUF_DIED:   return "end chicken buf is died";
        case STK_HASH_OF_STK_BROKEN:   return "hash of struct stack is broken";
        case STK_HASH_OF_BUF_BROKEN:   return "hash of buffer is broken";
        default:                       return "UNKNOWN ERROR";
        }
    }

// function veryfication stack.................................................

err_t Veryficator (const stack_t* stk)
    {
    if (stk == NULL)
        return STK_NOT_EXSIST;
    if (stk->data == NULL)
        return STK_DATA_NOT_EXSIST;
    if (stk->buffer == NULL)
        return STK_BUFFER_NOT_EXSIST;
    if (stk->capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;
    if (stk->size > stk->capacity)
        return STK_SIZE_LARGER_CAPACITY;
#ifdef USE_HASH
    if (stk->hashStk != HashCounterStk ((const char*)(stk)))
        return STK_HASH_OF_STK_BROKEN;
    if (stk->hashBuf != HashCounterBuf ((const char*)(stk->buffer), stk->size))
        return STK_HASH_OF_BUF_BROKEN;
#endif

#ifdef USE_CANARIES
    if(stk->chicken_start_stk != ((uint64_t)(stk) ^ HEX_SPEAK_FIRST))
        return STK_START_CHICK_STK_DIED;
    if(stk->chicken_end_stk  != ((uint64_t)(stk) ^ HEX_SPEAK_SECOND))
        return STK_END_CHICK_STK_DIED;
    if (*((uint64_t*)(stk->data)) != ((uint64_t)(stk) ^ HEX_SPEAK_FIRST))
        return STK_START_CHICK_BUF_DIED;
    if (*((uint64_t*)(stk->data + stk->capacity + 1)) != ((uint64_t)(stk) ^ HEX_SPEAK_SECOND))
        return STK_END_CHICK_BUF_DIED;
#endif
    return STK_OK;
    }

// print error to consol.......................................................

int PrintErrorStack (err_t error, const char* namefnc)
    {
    if (error)
        {
        printf("STACK ERROR: in function %s error: %s\n", namefnc, StackErrorToString(error));
        }
    return 1;
    }

//Print all elem of stack......................................................

err_t PrintSTK (stack_t* stk)
    {
    for (int i = (int)stk->capacity - 1; i >= 0; i--)
        {
        printf ("  buffer[%d] = <%lf> ", i, stk->buffer[i]);
        if (stk->buffer[i] == POISON)
            printf ("(POISON)");
        printf ("\n");
        }
                         // buffer[10] = 13979173918 (POISON) (est)
    printf ("\n");
    return STK_OK;
    }
