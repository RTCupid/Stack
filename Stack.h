//#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cstdint>

#include "Config.h"

enum err_t
    {                                                                          // enum err_t
    STK_OK = 0,
    STK_CALLOC_FAILED = 1,
    STK_BUFFER_NOT_EXSIST,                                                     // not enough memory to create stack data
    STK_REALLOC_FAILED,
    STK_STACK_NOT_EXSIST,
    STK_CAPACITY_NOT_EXSIST,
    STK_SIZE_LARGER_CAPACITY,
    STK_EMPTY_STACK,
    STK_START_CHICK_STK_DIED,
    STK_END_CHICK_STK_DIED,
    STK_START_CHICK_BUF_DIED,
    STK_END_CHICK_BUF_DIED};

const stack_elem_t NOT_AN_ELEMENT = NAN;                                       // = NAN for stack_elem_t = double

const double startElem = 10;

struct stack_t {uint64_t chicken_start_stk;
                stack_elem_t* DATA;
                stack_elem_t* buffer;
                int size;
                int capacity;
                uint64_t chicken_end_stk;};

err_t CookChicken (stack_t* stk);

err_t StackCtor (stack_t* stk, int startSize);

err_t StackPush (stack_t* stk, stack_elem_t elem);

err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack);

err_t StackDtor (stack_t* stk);

err_t Veryficator (stack_t stk);

const char* StackErrorToString(err_t error);

int PrintErrorStack (err_t error);
