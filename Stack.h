//#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cstdint>
#include "Config.h"

enum err_t {                                                                          // enum err_t
    STK_OK = 0,
    STK_CALLOC_FAILED = 1,
    STK_NOT_EXSIST,
    STK_DATA_NOT_EXSIST,
    STK_BUFFER_NOT_EXSIST,                                                     // not enough memory to create stack data
    STK_REALLOC_FAILED,
    STK_CAPACITY_NOT_EXSIST,
    STK_SIZE_LARGER_CAPACITY,
    STK_EMPTY_STACK,
    STK_START_CHICK_STK_DIED,
    STK_END_CHICK_STK_DIED,
    STK_START_CHICK_BUF_DIED,
    STK_END_CHICK_BUF_DIED,
    STK_HASH_OF_STK_BROKEN,
    STK_HASH_OF_BUF_BROKEN,
    INVALID_POINTER,
    STK_STACKCTOR_AGAIN
};

const stack_elem_t NOT_AN_ELEMENT = NAN;                                       // = NAN for stack_elem_t = double

const double startElem = 10;

const stack_elem_t POISON = -666667.766666;//0x0

const uint64_t HEX_SPEAK_FIRST  = 0x0BEDDEDA0BEDDEDA;

const uint64_t HEX_SPEAK_SECOND = 0xDEDDEDDEDDEDDEDD;

const size_t SIZE_CHANGE_FACTOR = 2;

const size_t SIZE_STK = 2 * sizeof (uint64_t) + 2 * sizeof (hash_t) + 2 * sizeof (size_t) + 2 * sizeof (stack_elem_t*);


const size_t indexStartHashStk = sizeof (uint64_t) + 2 * sizeof (stack_elem_t*) + 2 * sizeof (size_t) + sizeof (hash_t);
const size_t indexEndHashStk   = sizeof (uint64_t) + 2 * sizeof (stack_elem_t*) + 2 * sizeof (size_t) + sizeof (hash_t) * 2;

                         //struct  typedef "stack_t" (est) K&R read
typedef struct {
    uint64_t chicken_start_stk;
    stack_elem_t* data;
    stack_elem_t* buffer;
    size_t size;
    size_t capacity;
    hash_t hashBuf;
    hash_t hashStk;
    uint64_t chicken_end_stk;
} stack_t;

                        //typedef struct abc {...} abc_t; (est)
err_t CookChicken (stack_t* stk);

err_t StackCtor (stack_t* stk, size_t startCapacity);

err_t StackPush (stack_t* stk, stack_elem_t elem);

err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack);

err_t StackDtor (stack_t* stk);

err_t Veryficator (const stack_t* stk);

const char* StackErrorToString(err_t error);

int PrintErrorStack (err_t error, const char* namefnc);

err_t HashCount (stack_t* stk);

hash_t HashCounterBuf (const char* buffer, size_t size);

hash_t HashCounterStk (const char* Stk);

err_t StackDump (stack_t* stk);

err_t PrintSTK (stack_t* stk);

err_t StackAssert (stack_t* stk, const char* namefnc);

err_t MakePoison (stack_t* stk);
