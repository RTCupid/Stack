#include "Stack.h"

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (c) RTCupid, 2024\n\n");

    struct stack_t stk = {0,
                          NULL,
                          0,
                          0,
                          0};

    CookChicken (&stk);                                                        // make canary (or chicken)

    stack_elem_t elem_from_stack = NOT_AN_ELEMENT;

    err_t error = StackCtor (&stk, 5);
    PrintErrorStack (error);
    error = Veryficator (stk);
    PrintErrorStack (error);

    error = StackPush (&stk, 20);
    PrintErrorStack (error);
    error = Veryficator (stk);
    PrintErrorStack (error);

    error = StackPush (&stk, 30);
    PrintErrorStack (error);
    error = Veryficator (stk);
    PrintErrorStack (error);


    DBG printf ("Before StackPop: stk->size = %d\n", stk.size);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error);
    error = Veryficator (stk);
    PrintErrorStack (error);

    DBG printf ("After StackPop: stk->size = %d\n", stk.size);
    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error);
    error = Veryficator (stk);
    PrintErrorStack (error);

    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackDtor (&stk);
    PrintErrorStack (error);

    printf ("#Stack is destroyed\n");

    printf ("#End of programm");
    return 0;
    }

// make stack..................................................................

err_t StackCtor (stack_t* stk, int startCapacity)
    {
    stk->buffer = (stack_elem_t*)calloc (startCapacity, sizeof (stack_elem_t));
    if (stk->buffer == NULL)
        {
        printf ("stk->data = NULL");
        return STK_CALLOC_FAILED;
        }
    DBG printf ("Start: stk->buffer = %p\n", stk->buffer);

    stk->size = 0;
    DBG printf ("Start: stk->size = %d\n", stk->size);

    stk->capacity = startCapacity;
    DBG printf ("Start: stk->capacity = %d\n", stk->capacity);

    return STK_OK;
    }

//Push elem to stack...........................................................

err_t StackPush (stack_t* stk, stack_elem_t elem)
    {
    DBG printf ("Push %lf to stack\n", elem);

    if (stk->size == stk->capacity)
        {
        stk->buffer = (stack_elem_t*)realloc (stk->buffer, stk->size * 2 * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->buffer == NULL)
            {
            printf ("ERROR: in StackPush realloc return 'NULL'\n");
            return STK_REALLOC_FAILED;
            }
        }

    stk->buffer[stk->size] = elem;

    DBG printf ("stk->buffer[%d] = %lf\n\n", stk->size, stk->buffer[stk->size]);

    stk->size++;

    return STK_OK;
    }

//Pop elem from stack..........................................................

err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack)
    {
    err_t error = Veryficator (*stk);
    if (error)
        return error;
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->buffer[stk->size];

    return STK_OK;
    }

//Destroy stack................................................................

err_t StackDtor (stack_t* stk)
    {
    free (stk->buffer);
    stk->buffer = NULL;
    return STK_OK;
    }

err_t CookChicken (stack_t* stk)
    {
    stk->chicken_start_stk = ((uint64_t)(stk) ^ 0x0BEDDEDA);
    printf ("(uint64_t)(&stk) = <%llu>\n", (uint64_t)(stk));
    printf ("stk.chicken_start_stk = <%llu>\n", stk->chicken_start_stk);

    stk->chicken_end_stk  = ((uint64_t)(stk) ^ 0xDEDDEDDED);
    printf ("stk.chicken_end_stk = <%llu>\n", stk->chicken_start_stk);

    return STK_OK;
    }
