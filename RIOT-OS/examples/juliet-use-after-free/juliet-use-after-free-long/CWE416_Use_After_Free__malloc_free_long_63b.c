/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__malloc_free_long_63b.c
Label Definition File: CWE416_Use_After_Free__malloc_free.label.xml
Template File: sources-sinks-63b.tmpl.c
*/
/*
 * @description
 * CWE: 416 Use After Free
 * BadSource:  Allocate data using malloc(), initialize memory block, and Deallocate data using free()
 * GoodSource: Allocate data using malloc() and initialize memory block
 * Sinks:
 *    GoodSink: Do nothing
 *    BadSink : Use data
 * Flow Variant: 63 Data flow: pointer to data passed from one function to another in different source files
 *
 * */

#include "std_testcase.h"

#include <wchar.h>

void CWE416_Use_After_Free__malloc_free_long_63b_badSink(long * * dataPtr)
{
    long * data = *dataPtr;
    /* POTENTIAL FLAW: Use of data that may have been freed */
    printLongLine(data[0]);
    /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
}

/* goodG2B uses the GoodSource with the BadSink */
void CWE416_Use_After_Free__malloc_free_long_63b_goodG2BSink(long * * dataPtr)
{
    long * data = *dataPtr;
    /* POTENTIAL FLAW: Use of data that may have been freed */
    printLongLine(data[0]);
    /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE416_Use_After_Free__malloc_free_long_63b_goodB2GSink(long * * dataPtr)
{
    long * data = *dataPtr;
    /* FIX: Don't use data that may have been freed already */
    /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
    /* do nothing */
    ; /* empty statement needed for some flow variants */
}