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

    stack_elem_t elem_from_stack = NOT_AN_ELEMENT;

    err_t error = StackCtor (&stk, 5);
    PrintErrorStack (error, "StackCtor");
    error = Veryficator (&stk);
    PrintErrorStack (error, "Verificator after StackCtor");

    error = StackPush (&stk, 20);
    PrintErrorStack (error, "StackPush");
    error = Veryficator (&stk);
    PrintErrorStack (error, "Verificator after StackPush");

    error = StackPush (&stk, 30);
    PrintErrorStack (error, "StackPush");
    error = Veryficator (&stk);
    PrintErrorStack (error, "Verificator after StackPush");


    DBG printf ("Before StackPop: stk->size = %d\n", stk.size);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");


    DBG printf ("After StackPop: stk->size = %d\n", stk.size);
    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");
    error = Veryficator (&stk);
    PrintErrorStack (error, "Verificator after StackPop");

    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackDtor (&stk);
    PrintErrorStack (error, "StackDtor");

    printf ("#Stack is destroyed\n");

    printf ("#End of programm");
    return 0;
    }

// make stack..................................................................

err_t StackCtor (stack_t* stk, int startCapacity)
    {
    stk->DATA = (stack_elem_t*)calloc (startCapacity + 2, sizeof (stack_elem_t));
    if (stk->DATA == NULL)
        {
        return STK_CALLOC_FAILED;
        }
    DBG printf ("Start: stk->DATA   = <%p>\n", stk->DATA);

    stk->buffer = (stack_elem_t*)((char*)stk->DATA + 1 * sizeof (stack_elem_t));
    DBG printf ("Start: stk->buffer = <%p>\n", stk->buffer);

    stk->size = 0;
    DBG printf ("Start: stk->size = %d\n", stk->size);

    stk->capacity = startCapacity;
    DBG printf ("Start: stk->capacity = %d\n\n", stk->capacity);

    CookChicken (stk);                                                         // make canary (or chicken)
    err_t error = Veryficator (stk);
    if (error)
        return error;

    return STK_OK;
    }

//.............................................................................
[[nodiscard]]
err_t CookChicken (stack_t* stk)
    {
    stk->chicken_start_stk = ((uint64_t)(stk) ^ 0x0BEDDEDA0BEDDEDA);
    DBG printf ("(uint64_t)(&stk) = <%llu>\n", (uint64_t)(stk));
    DBG printf ("&stk = <%p>\n", stk);
    DBG printf ("stk.chicken_start_stk = <%llu>\n", stk->chicken_start_stk);

    stk->chicken_end_stk  = ((uint64_t)(stk) ^ 0xDEDDEDDEDDEDDEDD);
    DBG printf ("stk.chicken_end_stk = <%llu>\n\n", stk->chicken_start_stk);

    *(uint64_t*)(stk->DATA) = 0x0BEDDEDA0BEDDEDA;

    *((uint64_t*)(stk->DATA + stk->capacity)) = 0xDEDDEDDEDDEDDEDD;

    DBG printf ("&start chicken buffer = <%p>\n", stk->DATA);
    DBG printf (" start chicken buffer = <%llx>\n\n", *((uint64_t*)stk->DATA));
    DBG printf (" &end  chicken buffer = <%p>\n", stk->DATA + stk->capacity);
    DBG printf ("  end  chicken buffer = <%llx>\n\n", *((uint64_t*)stk->DATA + stk->capacity));
    err_t error = Veryficator (stk);
    if (error)
        return error;

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
    err_t error = Veryficator (stk);
    if (error)
        return error;
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->buffer[stk->size];

    error = Veryficator (stk);
    if (error)
        return error;
    return STK_OK;
    }

//Input all info about stack...................................................

err_t StackDump (stack_t* stk)
    {
    printf ("chicken_start_stk = <%llu>\n", stk->chicken_start_stk);
    printf ("chicken_end_stk   = <%llu>\n", stk->chicken_end_stk);

    printf ("&stk.DATA = <%p>\n", &stk->DATA);
    printf ("stk.DATA = <%p>\n", stk->DATA);

    printf ("&stk.buffer = <%p>\n", &stk->buffer);
    printf ("stk.buffer = <%p>\n", stk->buffer);
    // printf
    // printf
    // printf
    // printf;
    return STK_OK;
    }

//Destroy stack................................................................

err_t StackDtor (stack_t* stk)
    {
    free (stk->DATA);
    stk->DATA = NULL;
    stk->buffer = NULL;
    return STK_OK;
    }
