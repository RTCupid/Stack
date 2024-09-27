#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
//#include "TXLib.h"

typedef double stack_elem_t;

#define DBG if(1)

const double startElem = 10;

struct stack_t {stack_elem_t* data;
                int size;
                int capacity;};

int StackCtor (stack_t* stk, int startSize);

int StackPush (stack_t* stk, stack_elem_t elem);

stack_elem_t StackPop (stack_t* stk);

int StackDtor (stack_t* stk);

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (c) RTCupid, 2024\n\n");

    struct stack_t stk = {NULL,
                          0,
                          0};

    StackCtor (&stk, 5);

    StackPush (&stk, 20);

    StackPush (&stk, 30);

    double elemFromStack = 0;

    DBG printf ("Before StackPop: stk->size = %d\n", stk.size);

    elemFromStack = StackPop (&stk);

    DBG printf ("After StackPop: stk->size = %d\n", stk.size);
    DBG printf ("elemFromStack = %lf\n\n", elemFromStack);

    StackDtor (&stk);

    assert (stk.data == NULL);
    DBG printf ("Stack is destroyed\n\n");

    printf ("#End of programm");
    return 0;
    }

// make stack..................................................................

int StackCtor (stack_t* stk, int startCapacity)
    {
    stk->data = (stack_elem_t*)calloc (startCapacity, sizeof (stack_elem_t));
    if (stk->data == NULL)
        {
        printf ("stk->data = NULL");
        return 0;
        }
    DBG printf ("Start: stk->data = %p\n", stk->data);

    stk->size = 0;
    DBG printf ("Start: stk->size = %d\n", stk->size);

    stk->capacity = startCapacity;
    DBG printf ("Start: stk->capacity = %d\n", stk->capacity);

    stk->data[0] = startElem;
    stk->size++;

    DBG printf ("Start: stk->data[0] = %lf\n\n", stk->data[0]);

    return 1;
    }

//Push elem to stack...........................................................

int StackPush (stack_t* stk, stack_elem_t elem)
    {
    DBG printf ("Push %lf to stack\n", elem);

    if (stk->size == stk->capacity)
        {
        stk->data = (stack_elem_t*)realloc (stk->data, stk->size);
        if (stk->data == NULL)
            {
            printf ("ERROR: in StackPush realloc return 'NULL'\n");
            return 0;
            }
        }

    stk->data[stk->size] = elem;

    stk->size++;

    return 1;
    }

//Pop elem from stack..........................................................

stack_elem_t StackPop (stack_t* stk)
    {
    stk->size--;
    return stk->data[stk->size];
    }

//Destroy stack................................................................

int StackDtor (stack_t* stk)
    {
    free (stk->data);
    stk->data = NULL;
    return 0;
    }
