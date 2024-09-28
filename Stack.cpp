//#include "TXLib.h"

#include "Stack.h"


int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (c) RTCupid, 2024\n\n");

    struct stack_t stk = {NULL,
                          0,
                          0};

    stack_elem_t elem_from_stack = NOT_AN_ELEMENT;

    err_t error = StackCtor (&stk, 5);
    if (error)
        {
        printf("Stack error: %s\n", StackErrorToString(error));
        }

    StackPush (&stk, 20);

    StackPush (&stk, 30);


    DBG printf ("Before StackPop: stk->size = %d\n", stk.size);

    StackPop (&stk, &elem_from_stack);

    DBG printf ("After StackPop: stk->size = %d\n", stk.size);
    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    StackDtor (&stk);

    DBG printf ("#Stack is destroyed\n");

    printf ("#End of programm");
    return 0;
    }

// make stack..................................................................

err_t StackCtor (stack_t* stk, int startCapacity)
    {
    stk->data = (stack_elem_t*)calloc (startCapacity, sizeof (stack_elem_t));
    if (stk->data == NULL)
        {
        printf ("stk->data = NULL");
        return STK_OUT_OF_MEMORY;
        }
    DBG printf ("Start: stk->data = %p\n", stk->data);

    stk->size = 0;
    DBG printf ("Start: stk->size = %d\n", stk->size);

    stk->capacity = startCapacity;
    DBG printf ("Start: stk->capacity = %d\n", stk->capacity);

    stk->data[0] = startElem;
    stk->size++;

    DBG printf ("Start: stk->data[0] = %lf\n\n", stk->data[0]);

    return STK_OK;
    }

//Push elem to stack...........................................................

err_t StackPush (stack_t* stk, stack_elem_t elem)
    {
    DBG printf ("Push %lf to stack\n", elem);

    if (stk->size == stk->capacity)
        {
        stk->data = (stack_elem_t*)realloc (stk->data, stk->size * 2 * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->data == NULL)
            {
            printf ("ERROR: in StackPush realloc return 'NULL'\n");
            return STK_REALLOC_FAILED;
            }
        }

    stk->data[stk->size] = elem;

    DBG printf ("stk->data[%d] = %lf\n\n", stk->size, stk->data[stk->size]);

    stk->size++;

    return STK_OK;
    }

//Pop elem from stack..........................................................

err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack)
    {
    err_t error = Veryficator (stk);
    if (error)
        return error;
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->data[stk->size];

    return STK_OK;
    }

//Destroy stack................................................................

err_t StackDtor (stack_t* stk)
    {
    free (stk->data);
    stk->data = NULL;
    return STK_OK;
    }

const char* StackErrorToString(err_t error)
    {
    switch (error)
        {
        case STK_OK: return "OK";
            break;
        case STK_OUT_OF_MEMORY: return "STK OUT OF MEMORY";
            break;
        case STK_BAD_STACK: return "BAD STACK";
            break;
        case STK_BAD_STACK_DATA: return "BAD STACK DATA";
            break;
        case STK_REALLOC_FAILED: return "REALLOC FAILED";
            break;
        case STK_STACK_NOT_EXSIST: return "STACK NOT EXSIST";
            break;
        case STK_CAPACITY_NOT_EXSIST: return "CAPACITY NOT EXSIST";
            break;
        case STK_SIZE_LARGER_CAPACITY: return "SIZE LARGER THAN CAPACITY";
            break;
        case STK_EMPTY_STACK: return "EMPTY STACK";
            break;
        default: return "UNCNOWN ERROR";
        }
    }

err_t Veryficator (stack_t* stk)
    {
    if (stk == NULL)
        return STK_STACK_NOT_EXSIST;
    else if (stk->data == NULL)
        return STK_OUT_OF_MEMORY;
    else if (stk->capacity == 0)
        return STK_CAPACITY_NOT_EXSIST;
    else if (stk->size > stk->capacity)
        return STK_SIZE_LARGER_CAPACITY;
    else
        return STK_OK;
    }

