#include "Stack.h"

// make stack..................................................................
[[nodiscard]]
err_t StackCtor (stack_t* stk, size_t startCapacity)
    {
#ifdef USE_CANARIES
    stk->data = (stack_elem_t*)calloc (startCapacity + 2, sizeof (stack_elem_t));
                         // залить poison (est)
    if (stk->data == NULL)
    {
        return STK_CALLOC_FAILED;
    }
                         // check return value of std function (est)
    stk->buffer = (stack_elem_t*)((char*)stk->data + 1 * sizeof (stack_elem_t));
#else
    stk->buffer = (stack_elem_t*)calloc (startCapacity, sizeof (stack_elem_t));
    if (stk->buffer == NULL)
    {
        return STK_CALLOC_FAILED;
    }
#endif

    stk->size = 0;

    stk->capacity = startCapacity;

    MakePoison (stk);

#ifdef USE_CANARIES
    CookChicken (stk);                                           // make canary (or chicken)
#endif

#ifdef USE_HASH
    HashCount (stk);
#endif
                         // verify (est)
    StackAssert (stk, "StackAssert");

    return STK_OK;
    }

//.............................................................................

err_t CookChicken (stack_t* stk)
    {
    *(uint64_t*)(&stk->chicken_start_stk) = ((uint64_t)(stk) ^ HEX_SPEAK_FIRST);

    *(uint64_t*)(&stk->chicken_end_stk)  = ((uint64_t)(stk) ^ HEX_SPEAK_SECOND);

    *((uint64_t*)(stk->data)) = (uint64_t)(stk) ^ HEX_SPEAK_FIRST;

    *((uint64_t*)(stk->data + stk->capacity + 1)) = (uint64_t)(stk) ^ HEX_SPEAK_SECOND;

    return STK_OK;
    }

//function count hash stk and buf..............................................

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
        if (i < indexStartHashStk || i >= indexEndHashStk)
            hash = hash * 33 ^ (*((const char*)stk + i));
        }
    return hash;
    }

//Push elem to stack...........................................................
[[nodiscard]]
err_t StackPush (stack_t* stk, stack_elem_t elem)
    {
    StackAssert (stk, "StackPush");

    if (stk->size == stk->capacity)
        {
#ifdef USE_CANARIES
        stk->data = (stack_elem_t*)realloc (stk->data, (stk->capacity * SIZE_CHANGE_FACTOR + 2) * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->data == NULL)
            {
            return STK_REALLOC_FAILED;
            }

        stk->buffer = (stack_elem_t*)((char*)stk->data + 1 * sizeof (stack_elem_t));
#else
        stk->buffer = (stack_elem_t*)realloc (stk->buffer, (stk->capacity * SIZE_CHANGE_FACTOR) * sizeof (stack_elem_t));
#endif
        stk->capacity *= SIZE_CHANGE_FACTOR;

        MakePoison (stk);

#ifdef USE_CANARIES
        CookChicken (stk);                                           // make canary (or chicken)
#endif
        }

    stk->buffer[stk->size] = elem;

    stk->size++;

#ifdef USE_HASH
    HashCount (stk);
#endif

    StackAssert (stk, "StackPush");

    return STK_OK;
    }

//Pop elem from stack..........................................................
[[nodiscard]]
err_t StackPop (stack_t* stk, stack_elem_t* elem_from_stack)
    {
    StackAssert (stk, "StackPop");

    if (stk->size *  SIZE_CHANGE_FACTOR < stk->capacity)
        {
#ifdef USE_CANARIES
        stk->data = (stack_elem_t*)realloc (stk->data, (stk->capacity / SIZE_CHANGE_FACTOR + 2) * sizeof (stack_elem_t));   //sizeof (est)
        if (stk->data == NULL)
            {
            return STK_REALLOC_FAILED;
            }

        stk->buffer = (stack_elem_t*)((char*)stk->data + 1 * sizeof (stack_elem_t));
#else
        stk->buffer = (stack_elem_t*)realloc (stk->buffer, (stk->capacity / SIZE_CHANGE_FACTOR) * sizeof (stack_elem_t));
#endif

        stk->capacity /= SIZE_CHANGE_FACTOR;
        }

    stk->size--;
    *elem_from_stack = stk->buffer[stk->size];

#ifdef USE_CANARIES
        CookChicken (stk);                                           // make canary (or chicken)
#endif

#ifdef USE_HASH
    HashCount (stk);
#endif

    StackAssert (stk, "StackPop");

    return STK_OK;
    }

//Input all info about stack...................................................

err_t StackDump (stack_t* stk)
    {
                         //todo cool storage of errors
    // int errors = 0;
    // //000000001 = 1
    // //000000010 = 2
    // if ()
    // {
    //     errors = errors | 1;
    // }
    // //10101010
    // if(errors & 2)
    // {
    //     printf()
    // }

    printf ("Stack Dump:\n");
#ifdef USE_CANARIES
    printf ("  chicken_start_stk = <%llu>\n", stk->chicken_start_stk);
    printf ("  chicken_end_stk   = <%llu>\n\n", stk->chicken_end_stk);

    printf ("  &stk.DATA         = <%p>\n", &stk->data);
    printf ("  stk.DATA          = <%p>\n\n", stk->data);
#endif

    printf ("  &stk.buffer       = <%p>\n", &stk->buffer);
    printf ("  stk.buffer        = <%p>\n\n", stk->buffer);

    printf ("  size_t size       = <%lld>\n", stk->size);
    printf ("  size_t capacity   = <%lld>\n\n", stk->capacity);

#ifdef USE_HASH
    printf ("  hash_t hashBuf    = <%llu>\n", stk->hashBuf);
    printf ("  hash_t hashStk    = <%llu>\n\n", stk->hashStk);
#endif

    PrintSTK (stk);

    return STK_OK;
    }

//Print all elem of stack......................................................

err_t PrintSTK (stack_t* stk)
    {
    for (int i = (int)stk->capacity - 1; i >= 0; i--)
        {
        printf ("  buffer[%d] = <%lf> ", i, stk->buffer[i]);
        if (stk->buffer[i] == POISON)
            printf ("(POISON)");
        printf ("\n");
        }
                         // buffer[10] = 13979173918 (POISON) (est)
    printf ("\n");
    return STK_OK;
    }

//Destroy stack................................................................

err_t StackDtor (stack_t* stk)
    {
    //verify
    StackAssert (stk, "StackDtor");

    free (stk->data);
    stk->data = NULL;
    stk->buffer = NULL;
    printf ("# Stack Destroy\n");
    return STK_OK;
    }

// StackAssert.................................................................

err_t StackAssert (stack_t* stk, const char* namefnc)
    {
    err_t error = Veryficator (stk);
    if (error)
        {
        StackDump (stk);
        PrintErrorStack (error, namefnc);
        assert (0);
        }
    return STK_OK;
    }

//Make poison..................................................................

err_t MakePoison (stack_t* stk)
    {
    for (size_t i = stk->size; i < stk->capacity; i++)
        stk->buffer[i] = POISON;
    return STK_OK;
    }
