#include "std_testcase.h"

void CWE415_Double_Free__malloc_free_struct_01_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
    printf("%p\n", data);
}

void CWE415_Double_Free__malloc_free_struct_02_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(1)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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


void CWE415_Double_Free__malloc_free_struct_03_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(5==5)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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

void CWE415_Double_Free__malloc_free_struct_04_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_TRUE)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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

void CWE415_Double_Free__malloc_free_struct_05_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(staticTrue)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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

void CWE415_Double_Free__malloc_free_struct_06_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(STATIC_CONST_FIVE==5)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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

void CWE415_Double_Free__malloc_free_struct_07_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(staticFive==5)
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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

void CWE415_Double_Free__malloc_free_struct_08_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    if(staticReturnsTrue())
    {
        data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
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


void CWE415_Double_Free__malloc_free_struct_31_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    {
        twoIntsStruct * dataCopy = data;
        twoIntsStruct * data = dataCopy;
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        free(data);
        printf("%p\n", data);
    }
}

static void badSink(twoIntsStruct * data)
{
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
}

void CWE415_Double_Free__malloc_free_struct_41_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    badSink(data);
    printf("%p\n", data);
}

/* bad function declaration */
void CWE415_Double_Free__malloc_free_struct_51b_badSink(twoIntsStruct * data);

void CWE415_Double_Free__malloc_free_struct_51_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)malloc(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    free(data);
    CWE415_Double_Free__malloc_free_struct_51b_badSink(data);
    printf("%p\n", data);
}

/* bad function declaration */
twoIntsStruct * CWE415_Double_Free__malloc_free_struct_61b_badSource(twoIntsStruct * data);

void CWE415_Double_Free__malloc_free_struct_61_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = CWE415_Double_Free__malloc_free_struct_61b_badSource(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    free(data);
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE415_Double_Free__malloc_free_struct_01_bad()...");
    CWE415_Double_Free__malloc_free_struct_01_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_01_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_02_bad()...");
    CWE415_Double_Free__malloc_free_struct_02_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_02_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_03_bad()...");
    CWE415_Double_Free__malloc_free_struct_03_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_03_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_04_bad()...");
    CWE415_Double_Free__malloc_free_struct_04_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_04_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_05_bad()...");
    CWE415_Double_Free__malloc_free_struct_05_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_05_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_06_bad()...");
    CWE415_Double_Free__malloc_free_struct_06_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_06_bad()");

    printLine("Calling CWE415_Double_Free__malloc_free_struct_07_bad()...");
    CWE415_Double_Free__malloc_free_struct_07_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_07_bad()");

    printLine("Calling CWE415_Double_Free__malloc_free_struct_08_bad()...");
    CWE415_Double_Free__malloc_free_struct_08_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_08_bad()");

    printLine("Calling CWE415_Double_Free__malloc_free_struct_31_bad()...");
    CWE415_Double_Free__malloc_free_struct_31_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_31_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_41_bad()...");
    CWE415_Double_Free__malloc_free_struct_41_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_41_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_51_bad()...");
    CWE415_Double_Free__malloc_free_struct_51_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_51_bad()");
    
    printLine("Calling CWE415_Double_Free__malloc_free_struct_61_bad()...");
    CWE415_Double_Free__malloc_free_struct_61_bad();
    printLine("Finished CWE415_Double_Free__malloc_free_struct_61_bad()");

    
    return 0;
}
