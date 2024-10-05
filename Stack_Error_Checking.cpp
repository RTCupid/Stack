#include "Stack.h"

// return name of error as const char*.........................................

const char* StackErrorToString(err_t error)
    {
    switch (error)
        {
        case STK_OK:                   return "OK";
        case STK_CALLOC_FAILED:        return "in StackCtor calloc return 'NULL'";              //make alignment (est)
        case STK_REALLOC_FAILED:       return "in StackPush realloc return 'NULL'";
        case STK_BUFFER_NOT_EXSIST:    return "BUFFER NOT EXSIST";
        case STK_CAPACITY_NOT_EXSIST:  return "CAPACITY NOT EXSIST";
        case STK_SIZE_LARGER_CAPACITY: return "SIZE LARGER THAN CAPACITY";
        case STK_EMPTY_STACK:          return "EMPTY STACK";
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

    if (stk->buffer == NULL)
        return STK_BUFFER_NOT_EXSIST;
    if (stk->capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;
    if (stk->size > stk->capacity)
        return STK_SIZE_LARGER_CAPACITY;
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
