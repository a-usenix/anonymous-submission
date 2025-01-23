#include "std_testcase.h"

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    char * data;
    /* Initialize data */
    data = NULL;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    printf("%p\n", data);
    free(data);
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    char * data;
    /* Initialize data */
    data = NULL;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    printf("%p\n", data);
    free(data);
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

void CWE415_Double_Free__malloc_free_char_01_good()
{
    goodG2B();
    goodB2G();
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE415_Double_Free__malloc_free_char_01_good()...");
    CWE415_Double_Free__malloc_free_char_01_good();
    printLine("Finished CWE415_Double_Free__malloc_free_char_01_good()");

    
    return 0;
}
