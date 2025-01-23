#include "std_testcase.h"

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    long * data;
    data = NULL; /* Initialize data */
    {
        /* FIX: data is allocated on the heap and deallocated in the BadSink */
        long * dataBuffer = (long *)malloc(100*sizeof(long));
        if (dataBuffer == NULL)
        {
            printLine("malloc() failed");
            exit(1);
        }
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                dataBuffer[i] = 5L;
            }
        }
        data = dataBuffer;
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_01_good()
{
    goodG2B();
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_01_good()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_01_good();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_01_good()");
    
    return 0;
}
