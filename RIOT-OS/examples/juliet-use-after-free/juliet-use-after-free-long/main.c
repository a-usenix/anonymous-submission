#include "std_testcase.h"

void CWE416_Use_After_Free__malloc_free_long_01_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    data = (long *)malloc(100*sizeof(long));
    if (data == NULL) {exit(-1);}
    {
        size_t i;
        for(i = 0; i < 100; i++)
        {
            data[i] = 5L;
        }
    }
    /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
    free(data);
    /* POTENTIAL FLAW: Use of data that may have been freed */
    printLongLine(data[0]);
    /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
}

void CWE416_Use_After_Free__malloc_free_long_02_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(1)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(1)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

void CWE416_Use_After_Free__malloc_free_long_03_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(5==5)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(5==5)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

static const int STATIC_CONST_TRUE = 1; /* true */
static const int STATIC_CONST_FALSE = 0; /* false */

void CWE416_Use_After_Free__malloc_free_long_04_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_TRUE)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(STATIC_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

static int staticTrue = 1; /* true */
static int staticFalse = 0; /* false */

void CWE416_Use_After_Free__malloc_free_long_05_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(staticTrue)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(staticTrue)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

static const int STATIC_CONST_FIVE = 5;

void CWE416_Use_After_Free__malloc_free_long_06_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_FIVE==5)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(STATIC_CONST_FIVE==5)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

static int staticFive = 5;

void CWE416_Use_After_Free__malloc_free_long_07_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(staticFive==5)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(staticFive==5)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

static int staticReturnsTrue()
{
    return 1;
}

static int staticReturnsFalse()
{
    return 0;
}

void CWE416_Use_After_Free__malloc_free_long_08_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(staticReturnsTrue())
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(staticReturnsTrue())
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

void CWE416_Use_After_Free__malloc_free_long_09_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

void CWE416_Use_After_Free__malloc_free_long_10_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(globalTrue)
    {
        data = (long *)malloc(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5L;
            }
        }
        /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
        free(data);
    }
    if(globalTrue)
    {
        /* POTENTIAL FLAW: Use of data that may have been freed */
        printLongLine(data[0]);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    }
}

/* bad function declaration */
void CWE416_Use_After_Free__malloc_free_long_63b_badSink(long * * dataPtr);

void CWE416_Use_After_Free__malloc_free_long_63_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    data = (long *)malloc(100*sizeof(long));
    if (data == NULL) {exit(-1);}
    {
        size_t i;
        for(i = 0; i < 100; i++)
        {
            data[i] = 5L;
        }
    }
    /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
    free(data);
    CWE416_Use_After_Free__malloc_free_long_63b_badSink(&data);
}

/* bad function declaration */
void CWE416_Use_After_Free__malloc_free_long_64b_badSink(void * dataVoidPtr);

void CWE416_Use_After_Free__malloc_free_long_64_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    data = (long *)malloc(100*sizeof(long));
    if (data == NULL) {exit(-1);}
    {
        size_t i;
        for(i = 0; i < 100; i++)
        {
            data[i] = 5L;
        }
    }
    /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
    free(data);
    CWE416_Use_After_Free__malloc_free_long_64b_badSink(&data);
}


/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_01_bad()...");
    CWE416_Use_After_Free__malloc_free_long_01_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_01_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_02_bad()...");
    CWE416_Use_After_Free__malloc_free_long_02_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_02_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_03_bad()...");
    CWE416_Use_After_Free__malloc_free_long_03_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_03_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_04_bad()...");
    CWE416_Use_After_Free__malloc_free_long_04_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_04_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_05_bad()...");
    CWE416_Use_After_Free__malloc_free_long_05_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_05_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_06_bad()...");
    CWE416_Use_After_Free__malloc_free_long_06_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_06_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_07_bad()...");
    CWE416_Use_After_Free__malloc_free_long_07_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_07_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_08_bad()...");
    CWE416_Use_After_Free__malloc_free_long_08_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_08_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_09_bad()...");
    CWE416_Use_After_Free__malloc_free_long_09_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_09_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_10_bad()...");
    CWE416_Use_After_Free__malloc_free_long_10_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_10_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_63_bad()...");
    CWE416_Use_After_Free__malloc_free_long_63_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_63_bad()");
    
    printLine("Calling CWE416_Use_After_Free__malloc_free_long_64_bad()...");
    CWE416_Use_After_Free__malloc_free_long_64_bad();
    printLine("Finished CWE416_Use_After_Free__malloc_free_long_64_bad()");

    return 0;
}
