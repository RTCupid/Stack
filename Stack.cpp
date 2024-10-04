#include "Stack.h"

int main ()
    {
    printf ("# Program for Solve Square Equation\n");
    printf ("# (c) RTCupid, 2024\n\n");

    struct stack_t stk = {0,
                          NULL,
                          NULL,
                          0,
                          0,
                          0,
                          0,
                          0};

    stack_elem_t elem_from_stack = NOT_AN_ELEMENT;

    err_t error = StackCtor (&stk, 5);
    PrintErrorStack (error, "StackCtor");

    error = StackPush (&stk, 10);
    PrintErrorStack (error, "StackPush");

    error = StackPush (&stk, 20);
    PrintErrorStack (error, "StackPush");

    stk.buffer = (stack_elem_t*)27447835384;

    error = StackPush (&stk, 30);
    PrintErrorStack (error, "StackPush");

    error = StackPush (&stk, 40);
    PrintErrorStack (error, "StackPush");

    StackDump (&stk);

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");

    error = StackPop (&stk, &elem_from_stack);
    PrintErrorStack (error, "StackPop");

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
    err_t error = STK_OK;
#ifdef USE_CANARIES
    stk->DATA = (stack_elem_t*)calloc (startCapacity + 2, sizeof (stack_elem_t));
    if (stk->DATA == NULL)
        {
        return STK_CALLOC_FAILED;
        }

    stk->buffer = (stack_elem_t*)((char*)stk->DATA + 1 * sizeof (stack_elem_t));
#else
    stk->buffer = (stack_elem_t*)calloc (startCapacity, sizeof (stack_elem_t));
#endif

    stk->size = 0;

    stk->capacity = startCapacity;

#ifdef USE_CANARIES
    error = CookChicken (stk);                                           // make canary (or chicken)
    if (error)
        return error;
#endif

#ifdef USE_HASH
    error = HashCount (stk);
    if (error)
        return error;
#endif

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

    *(uint64_t*)(&stk->chicken_end_stk)  = ((uint64_t)(stk) ^ HexSpeakSecond);

    *((uint64_t*)(stk->DATA)) = (uint64_t)(stk) ^ HexSpeakFirst;

    *((uint64_t*)(stk->DATA + stk->capacity + 1)) = (uint64_t)(stk) ^ HexSpeakSecond;

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
[[nodiscard]]
hash_t HashCounterBuf (const char* buffer, size_t size)
    {
    hash_t hash = 5381;
    for (size_t i = 0; i < size; i++)
        {
        hash = hash * 33 ^ buffer[i];
        }
    return hash;
    }

//function to calculate the hash of struct stack...............................
[[nodiscard]]
hash_t HashCounterStk (const char* stk)
    {
    hash_t hash = 5381;
    for (size_t i = 0; i < SIZE_STK; i++)
        {
        if (i != indexHashStk)
            hash = hash * 33 ^ stk[i];
        }
    return hash;
    }

//Push elem to stack...........................................................
[[nodiscard]]
err_t StackPush (stack_t* stk, stack_elem_t elem)
    {
    err_t error = Veryficator (stk);
    if (error)
        return error;

    if (stk->size == stk->capacity)
        {
        stk->DATA = (stack_elem_t*)realloc (stk->DATA, (stk->capacity * 2 + 2) * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->DATA == NULL)
            {
            return STK_REALLOC_FAILED;
            }
        stk->capacity *= 2;

#ifdef USE_CANARIES
        error = CookChicken (stk);                                           // make canary (or chicken)
        if (error)
            return error;
#endif
        }

    stk->buffer[stk->size] = elem;

    stk->size++;

#ifdef USE_HASH
    error = HashCount (stk);
    if (error)
        return error;
#endif

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

#ifdef USE_HASH
    error = HashCount (stk);
    if (error)
        return error;
#endif

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

    printf ("Stack Dump:\n");
#ifdef USE_CANARIES
    printf ("  chicken_start_stk = <%llu>\n", stk->chicken_start_stk);
    printf ("  chicken_end_stk   = <%llu>\n\n", stk->chicken_end_stk);

    printf ("  &stk.DATA         = <%p>\n", &stk->DATA);
    printf ("  stk.DATA          = <%p>\n\n", stk->DATA);
#endif

    printf ("  &stk.buffer       = <%p>\n", &stk->buffer);
    printf ("  stk.buffer        = <%p>\n\n", stk->buffer);

    printf ("  size_t size       = <%lld>\n", stk->size);
    printf ("  size_t capacity   = <%lld>\n\n", stk->capacity);

#ifdef USE_HASH
    printf ("  hash_t hashBuf    = <%llu>\n", stk->hashBuf);
    printf ("  hash_t hashStk    = <%llu>\n\n", stk->hashStk);
#endif

    error = PrintSTK (stk);
    if (error)
        return error;

    error = Veryficator (stk);
    if (error)
        return error;
    return STK_OK;
    }

//Print all elem of stack......................................................

err_t PrintSTK (stack_t* stk)
    {
    for (int i = (int)stk->size - 1; i >= 0; i--)
        printf ("  buffer[%d] = <%lf>\n", i, stk->buffer[i]);
    printf ("\n");
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
