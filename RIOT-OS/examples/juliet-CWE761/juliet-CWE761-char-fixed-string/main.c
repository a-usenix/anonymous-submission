#include "std_testcase.h"

#define BAD_SOURCE_FIXED_STRING "Fixed String" /* MAINTENANCE NOTE: This string must contain the SEARCH_CHAR */

#define SEARCH_CHAR 'S'

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_01_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_02_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(1)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_03_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(5==5)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

static const int STATIC_CONST_TRUE = 1; /* true */
static const int STATIC_CONST_FALSE = 0; /* false */

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_04_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(STATIC_CONST_TRUE)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

static int staticTrue = 1; /* true */
static int staticFalse = 0; /* false */

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_05_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(staticTrue)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

static const int STATIC_CONST_FIVE = 5;

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_06_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(STATIC_CONST_FIVE==5)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

static int staticFive = 5;

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_07_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(staticFive==5)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
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

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_08_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(staticReturnsTrue())
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_09_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(GLOBAL_CONST_TRUE)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_10_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(globalTrue)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_11_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(globalReturnsTrue())
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_12_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(globalReturnsTrueOrFalse())
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
    else
    {
        {
            size_t i;
            /* FIX: Use a loop variable to traverse through the string pointed to by data */
            for (i=0; i < strlen(data); i++)
            {
                if (data[i] == SEARCH_CHAR)
                {
                    printLine("We have a match!");
                    break;
                }
            }
            free(data);
        }
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_13_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(GLOBAL_CONST_FIVE==5)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_14_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    if(globalFive==5)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_15_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    switch(6)
    {
    case 6:
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
        break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_16_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    while(1)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
        break;
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_17_bad()
{
    int j;
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    for(j = 0; j < 1; j++)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_18_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    goto sink;
sink:
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

static int badStatic = 0;

static void badSink(char * data)
{
    if(badStatic)
    {
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_21_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    badStatic = 1; /* true */
    badSink(data);
}

int CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_badGlobal = 0;

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_badSink(char * data);

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_badGlobal = 1; /* true */
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_badSink(data);
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_31_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    {
        char * dataCopy = data;
        char * data = dataCopy;
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_32_bad()
{
    char * data;
    char * *dataPtr1 = &data;
    char * *dataPtr2 = &data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    {
        char * data = *dataPtr1;
        /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
        strcpy(data, BAD_SOURCE_FIXED_STRING);
        *dataPtr1 = data;
    }
    {
        char * data = *dataPtr2;
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

typedef union
{
    char * unionFirst;
    char * unionSecond;
} CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_unionType;

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_bad()
{
    char * data;
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_unionType myUnion;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    myUnion.unionFirst = data;
    {
        char * data = myUnion.unionSecond;
        /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
         * memory block not at the start of the buffer */
        for (; *data != '\0'; data++)
        {
            if (*data == SEARCH_CHAR)
            {
                printLine("We have a match!");
                break;
            }
        }
        free(data);
    }
}

static void badSink_41(char * data)
{
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_41_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    badSink_41(data);
}

static char * badSource_42(char * data)
{
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    return data;
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_42_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    data = badSource_42(data);
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

static void badSink_44(char * data)
{
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_44_bad()
{
    char * data;
    /* define a function pointer */
    void (*funcPtr) (char *) = badSink_44;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    /* use the function pointer */
    funcPtr(data);
}

static char * CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_badData;

static void badSink_45()
{
    char * data = CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_badData;
    /* FLAW: We are incrementing the pointer in the loop - this will cause us to free the
     * memory block not at the start of the buffer */
    for (; *data != '\0'; data++)
    {
        if (*data == SEARCH_CHAR)
        {
            printLine("We have a match!");
            break;
        }
    }
    free(data);
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_badData = data;
    badSink_45();
}

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51b_badSink(char * data);

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51b_badSink(data);
}

/* bad function declaration */
void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52b_badSink(char * data);

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52b_badSink(data);
}


/* bad function declaration */
void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53b_badSink(char * data);

void CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53_bad()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    /* POTENTIAL FLAW: Initialize data to be a fixed string that contains the search character in the sinks */
    strcpy(data, BAD_SOURCE_FIXED_STRING);
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53b_badSink(data);
}


/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(void)
{   
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_01_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_01_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_01_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_02_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_02_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_02_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_03_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_03_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_03_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_04_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_04_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_04_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_05_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_05_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_05_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_06_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_06_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_06_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_07_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_07_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_07_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_08_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_08_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_08_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_09_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_09_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_09_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_10_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_10_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_10_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_11_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_11_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_11_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_12_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_12_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_12_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_13_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_13_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_13_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_14_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_14_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_14_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_15_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_15_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_15_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_16_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_16_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_16_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_17_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_17_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_17_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_18_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_18_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_18_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_21_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_21_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_21_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_22_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_31_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_31_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_31_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_32_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_32_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_32_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_34_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_41_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_41_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_41_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_42_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_42_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_42_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_44_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_44_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_44_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_45_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_51_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_52_bad()");
    
    printLine("Calling CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53_bad()...");
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53_bad();
    printLine("Finished CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_fixed_string_53_bad()");
    
    return 0;
}
