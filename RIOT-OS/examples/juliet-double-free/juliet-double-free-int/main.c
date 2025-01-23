#include "std_testcase.h"

void CWE415_Double_Free__malloc_free_int_01_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
    printf("%p\n", data);
}

void CWE415_Double_Free__malloc_free_int_02_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(1)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(1)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}


void CWE415_Double_Free__malloc_free_int_03_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(5==5)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(5==5)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}

static const int STATIC_CONST_TRUE = 1; /* true */
static const int STATIC_CONST_FALSE = 0; /* false */

void CWE415_Double_Free__malloc_free_int_04_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_TRUE)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(STATIC_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}

static int staticTrue = 1; /* true */
static int staticFalse = 0; /* false */

void CWE415_Double_Free__malloc_free_int_05_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(staticTrue)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(staticTrue)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}

static const int STATIC_CONST_FIVE = 5;

void CWE415_Double_Free__malloc_free_int_06_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_FIVE==5)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(STATIC_CONST_FIVE==5)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}

static int staticFive = 5;

void CWE415_Double_Free__malloc_free_int_07_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(staticFive==5)
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(staticFive==5)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}

static int staticReturnsTrue()
{
    return 1;
}

static int staticReturnsFalse()
{
    return 0;
}

void CWE415_Double_Free__malloc_free_int_08_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    if(staticReturnsTrue())
    {
        data = (int *)malloc(100*sizeof(int));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        free(data);
    }
    if(staticReturnsTrue())
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
    }
    printf("%p\n", data);
}


void CWE415_Double_Free__malloc_free_int_31_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    {
        int * dataCopy = data;
        int * data = dataCopy;
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
        printf("%p\n", data);
    }
}

static void badSink(int * data)
{
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
}

void CWE415_Double_Free__malloc_free_int_41_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    badSink(data);
    printf("%p\n", data);
}

/* bad function declaration */
void CWE415_Double_Free__malloc_free_int_51b_badSink(int * data);

void CWE415_Double_Free__malloc_free_int_51_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    CWE415_Double_Free__malloc_free_int_51b_badSink(data);
    printf("%p\n", data);
}

/* bad function declaration */
int * CWE415_Double_Free__malloc_free_int_61b_badSource(int * data);

void CWE415_Double_Free__malloc_free_int_61_bad()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = CWE415_Double_Free__malloc_free_int_61b_badSource(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE415_Double_Free__malloc_free_int_01_bad()...");
    CWE415_Double_Free__malloc_free_int_01_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_01_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_02_bad()...");
    CWE415_Double_Free__malloc_free_int_02_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_02_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_03_bad()...");
    CWE415_Double_Free__malloc_free_int_03_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_03_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_04_bad()...");
    CWE415_Double_Free__malloc_free_int_04_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_04_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_05_bad()...");
    CWE415_Double_Free__malloc_free_int_05_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_05_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_06_bad()...");
    CWE415_Double_Free__malloc_free_int_06_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_06_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_07_bad()...");
    CWE415_Double_Free__malloc_free_int_07_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_07_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_08_bad()...");
    CWE415_Double_Free__malloc_free_int_08_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_08_bad()");

    printLine("Calling CWE415_Double_Free__malloc_free_int_31_bad()...");
    CWE415_Double_Free__malloc_free_int_31_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_31_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_41_bad()...");
    CWE415_Double_Free__malloc_free_int_41_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_41_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_51_bad()...");
    CWE415_Double_Free__malloc_free_int_51_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_51_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_int_61_bad()...");
    CWE415_Double_Free__malloc_free_int_61_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_int_61_bad()");

    
    return 0;
}
