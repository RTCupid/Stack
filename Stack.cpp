#include <stdio.h>
#include <stdlib.h>

typedef double stack_elem_t;

#define DBG if(1)

const double startElem = 10;

struct stack_t {stack_elem_t* data;
                int size;
                int capacity;};

int StackCtor (stack_t* stk, int startSize);

int StackPush (stack_t* stk, stack_elem_t elem);

int main ()
    {
    struct stack_t stk = {NULL,
                          0,
                          0};

    if (!StackCtor (&stk, 5))
        {
        printf ("ERROR: Error of stack construction");
        return -1;
        }

    if (!StackPush (&stk, 20))
        {
        printf ("ERROR: Error of push to stack");
        return -1;
        }

    if (!StackPush (&stk, 30))
        {
        printf ("ERROR: Error of push to stack");
        return -1;
        }

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

    DBG printf ("stk->data[%d] = %lf\n", stk->size, stk->data[stk->size]);

    stk->size++;

    return 1;
    }
