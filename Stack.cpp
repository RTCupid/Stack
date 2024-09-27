#include <stdio.h>
#include <stdlib.h>

typedef double stack_elem_t;

#define DBG if(1)

const double startElem = 10;

struct stack_t {stack_elem_t* data;
                int size;
                int capacity;};

int StackCtor (stack_t* stk, int startSize);

int main ()
    {
    struct stack_t stk = {NULL,
                          0,
                          0};

    StackCtor (&stk, 5);

    //StackPush (&stk, 20);

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
    DBG printf ("Start: stk->capacity = %d\n\n", stk->capacity);

    stk->data[0] = startElem;
    stk->size++;

    DBG printf ("stk->data[0] = %lf\n", stk->data[0]);

    return 1;
    }
