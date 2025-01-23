#include "std_testcase.h"

void CWE590_Free_Memory_Not_on_Heap__free_long_static_01_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    {
        /* FLAW: data is allocated on the stack and deallocated in the BadSink */
        static long dataBuffer[100];
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

void CWE590_Free_Memory_Not_on_Heap__free_long_static_02_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(1)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_03_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(5==5)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

static const int STATIC_CONST_TRUE = 1; /* true */
static const int STATIC_CONST_FALSE = 0; /* false */

void CWE590_Free_Memory_Not_on_Heap__free_long_static_04_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(STATIC_CONST_TRUE)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

static int staticTrue = 1; /* true */
static int staticFalse = 0; /* false */

void CWE590_Free_Memory_Not_on_Heap__free_long_static_05_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(staticTrue)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

static const int STATIC_CONST_FIVE = 5;

void CWE590_Free_Memory_Not_on_Heap__free_long_static_06_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(STATIC_CONST_FIVE==5)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

static int staticFive = 5;

void CWE590_Free_Memory_Not_on_Heap__free_long_static_07_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(staticFive==5)
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

static int staticReturnsTrue()
{
    return 1;
}

static int staticReturnsFalse()
{
    return 0;
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_08_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    if(staticReturnsTrue())
    {
        {
            /* FLAW: data is allocated on the stack and deallocated in the BadSink */
            static long dataBuffer[100];
            {
                size_t i;
                for (i = 0; i < 100; i++)
                {
                    dataBuffer[i] = 5L;
                }
            }
            data = dataBuffer;
        }
    }
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_31_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    {
        /* FLAW: data is allocated on the stack and deallocated in the BadSink */
        static long dataBuffer[100];
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                dataBuffer[i] = 5L;
            }
        }
        data = dataBuffer;
    }
    {
        long * dataCopy = data;
        long * data = dataCopy;
        printLongLine(data[0]);
        /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
        free(data);
    }
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_41_badSink(long * data)
{
    printLongLine(data[0]);
    /* POTENTIAL FLAW: Possibly deallocating memory allocated on the stack */
    free(data);
}

void CWE590_Free_Memory_Not_on_Heap__free_long_static_41_bad()
{
    long * data;
    data = NULL; /* Initialize data */
    {
        /* FLAW: data is allocated on the stack and deallocated in the BadSink */
        static long dataBuffer[100];
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                dataBuffer[i] = 5L;
            }
        }
        data = dataBuffer;
    }
    CWE590_Free_Memory_Not_on_Heap__free_long_static_41_badSink(data);
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_01_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_01_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_01_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_02_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_02_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_02_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_03_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_03_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_03_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_04_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_04_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_04_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_05_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_05_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_05_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_06_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_06_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_06_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_07_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_07_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_07_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_08_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_08_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_08_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_31_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_31_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_31_bad()");
    
    printLine("Calling CWE590_Free_Memory_Not_on_Heap__free_long_static_41_bad()...");
    CWE590_Free_Memory_Not_on_Heap__free_long_static_41_bad();
    printLine("Finished CWE590_Free_Memory_Not_on_Heap__free_long_static_41_bad()");
    
    return 0;
}
