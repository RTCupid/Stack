#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef double stack_elem_t;                                                   // type elements in stack

#define DBG if(1)

enum err_t
    {                                                                          // enum err_t
    STK_OK = 0,
    STK_OUT_OF_MEMORY = 1,                                                     // not enough memory to create stack data
    STK_BAD_STACK = 2,
    STK_BAD_STACK_DATA = 3,
    STK_REALLOC_FAILED = 4,
    STK_STACK_NOT_EXSIST = 5,
    STK_CAPACITY_NOT_EXSIST = 6,
    STK_SIZE_LARGER_CAPACITY = 7,
    STK_EMPTY_STACK};

const stack_elem_t NOT_AN_ELEMENT = NAN;                                       // = NAN for stack_elem_t = double

const double startElem = 10;

struct stack_t {stack_elem_t* data;
                int size;
                int capacity;};

err_t StackCtor (stack_t* stk, int startSize);

err_t StackPush (stack_t* stk, stack_elem_t elem);

err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack);

err_t StackDtor (stack_t* stk);

err_t Veryficator (stack_t* stk);

const char* StackErrorToString(err_t error);
