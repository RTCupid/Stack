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
    STK_REALLOC_FAILED,
    STK_STACK_NOT_EXSIST,
    STK_CAPACITY_NOT_EXSIST,
    STK_SIZE_LARGER_CAPACITY,
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

int PrintErrorStack (err_t error);
