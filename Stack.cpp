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


    error = StackPush (&stk, 20);
    PrintErrorStack (error, "StackPush");

    error = StackPush (&stk, 30);
    PrintErrorStack (error, "StackPush");

    DBG printf ("Before StackPop: stk->size = %lld\n", stk.size);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");


    DBG printf ("After StackPop: stk->size = %lld\n", stk.size);
    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");

    DBG printf ("elemFromStack = %lf\n\n", elem_from_stack);

    error = StackDtor (&stk);
    PrintErrorStack (error, "StackDtor");

    printf ("#Stack is destroyed\n");

    printf ("#End of programm");
    return 0;
    }

// make stack..................................................................
[[nodiscard]]
err_t StackCtor (stack_t* stk, size_t startCapacity)
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
    DBG printf ("Start: stk->size = %lld\n", stk->size);

    stk->capacity = startCapacity;
    DBG printf ("Start: stk->capacity = %lld\n\n", stk->capacity);

    err_t error = CookChicken (stk);                                           // make canary (or chicken)
    if (error)
        return error;

    error = HashCount (stk);
    if (error)
        return error;

    error = Veryficator (stk);
    if (error)
        return error;

    return STK_OK;
    }

//.............................................................................
[[nodiscard]]
err_t CookChicken (stack_t* stk)
    {
    *(uint64_t*)(&stk->chicken_start_stk) = ((uint64_t)(stk) ^ HexSpeakFirst);
    DBG printf ("(uint64_t)(&stk) = <%llu>\n", (uint64_t)(stk));
    DBG printf ("&stk = <%p>\n", stk);
    DBG printf ("stk.chicken_start_stk = <%llu>\n", stk->chicken_start_stk);

    *(uint64_t*)(&stk->chicken_end_stk)  = ((uint64_t)(stk) ^ HexSpeakSecond);
    DBG printf ("stk.chicken_end_stk = <%llu>\n\n", stk->chicken_start_stk);

    *((uint64_t*)(stk->DATA)) = (uint64_t)(stk) ^ HexSpeakFirst;

    *((uint64_t*)(stk->DATA + stk->capacity + 1)) = (uint64_t)(stk) ^ HexSpeakSecond;

    DBG printf ("&start chicken buffer = <%p>\n", stk->DATA);
    DBG printf (" start chicken buffer = <%llx>\n\n", *((uint64_t*)(stk->DATA)));
    DBG printf (" &end  chicken buffer = <%p>\n", stk->DATA + stk->capacity + 1);
    DBG printf ("  end  chicken buffer = <%llx>\n\n", *((uint64_t*)stk->DATA + stk->capacity + 1));
    err_t error = Veryficator (stk);
    if (error)
        return error;

    return STK_OK;
    }

//function count hash stk and buf..............................................
[[nodiscard]]
err_t HashCount (stack_t* stk)
    {
    stk->hashBuf = HashCounterBuf ((const char*)(stk->buffer), stk->size);
    stk->hashStk = HashCounterStk ((const char*)(stk));
    return STK_OK;
    }

//function to calculate the hash of buffer.....................................

hash_t HashCounterBuf (const char* buffer, size_t size)
    {
    hash_t hash = 0;
    for (size_t i = 0; i < size; i++)
        {
        hash += buffer[i];
        }
    return hash;
    }

//function to calculate the hash of struct stack...............................

hash_t HashCounterStk (const char* stk)
    {
    hash_t hash = 0;
    for (size_t i = 0; i < nElemStructStk; i++)
        {
        if (i != indexHashStk)
            hash += stk[i];
        }
    return hash;
    }

/*err_t HashChek (const stack_t* stk)
    {
    if (stk->hashStk != HashCounterStk (stk
    }*/

//Push elem to stack...........................................................
[[nodiscard]]
err_t StackPush (stack_t* stk, stack_elem_t elem)
    {
    err_t error = Veryficator (stk);
    if (error)
        return error;

    DBG printf ("Push %lf to stack\n", elem);

    if (stk->size == stk->capacity)
        {
        stk->DATA = (stack_elem_t*)realloc (stk->DATA, (stk->capacity * 2 + 2) * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->DATA == NULL)
            {
            return STK_REALLOC_FAILED;
            }
        stk->capacity *= 2;

        error = CookChicken (stk);                                           // make canary (or chicken)
        if (error)
            return error;
        }

    stk->buffer[stk->size] = elem;

    DBG printf ("stk->buffer[%lld] = %lf\n\n", stk->size, stk->buffer[stk->size]);

    stk->size++;

    error = HashCount (stk);
    if (error)
        return error;

    error = Veryficator (stk);
    if (error)
        return error;

    return STK_OK;
    }

//Pop elem from stack..........................................................
[[nodiscard]]
err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack)
    {
    err_t error = Veryficator (stk);
    if (error)
        return error;
    if (stk->size == 0)
        return STK_EMPTY_STACK;

    stk->size--;
    *elem_from_stack = stk->buffer[stk->size];

    stk->hashStk = HashCounterStk ((const char*)(&stk));
    stk->hashBuf = HashCounterBuf ((const char*)(stk->buffer), stk->size);

    error = HashCount (stk);
    if (error)
        return error;

    error = Veryficator (stk);
    if (error)
        return error;
    return STK_OK;
    }

//Input all info about stack...................................................

err_t StackDump (stack_t* stk)
    {

    err_t error = Veryficator (stk);
    if (error)
        return error;

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
    error = Veryficator (stk);
    if (error)
        return error;
    return STK_OK;
    }

//Destroy stack................................................................

err_t StackDtor (stack_t* stk)
    {
    err_t error = Veryficator (stk);
    if (error)
        return error;

    free (stk->DATA);
    stk->DATA = NULL;
    stk->buffer = NULL;
    return STK_OK;
    }
