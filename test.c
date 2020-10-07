#include "funcoesParaStrings.h"
#include <assert.h>

void testSafeCalloc()
{
    unsigned short *ponteiro0 = (unsigned short*) safeCalloc(sizeof(unsigned short), 1);
    assert(ponteiro0 != NULL);
    free(ponteiro0);

    unsigned int *ponteiro1 = (unsigned int*) safeCalloc(sizeof(unsigned int), 1);
    assert(ponteiro1 != NULL);
    free(ponteiro1);

    unsigned long *ponteiro2 = (unsigned long*) safeCalloc(sizeof(unsigned long), 1);
    assert(ponteiro2 != NULL);
    free(ponteiro2);

    unsigned long long *ponteiro3 = (unsigned long long*) safeCalloc(sizeof(unsigned long long), 1);
    assert(ponteiro3 != NULL);
    free(ponteiro3);

    unsigned char *ponteiro4 = (unsigned char*) safeCalloc(sizeof(unsigned char), 1);
    assert(ponteiro4 != NULL);
    free(ponteiro4);

    short *ponteiro5 = (short*) safeCalloc(sizeof(short), 1);
    assert(ponteiro5 != NULL);
    free(ponteiro5);

    int *ponteiro6 = (int*) safeCalloc(sizeof(int), 1);
    assert(ponteiro6 != NULL);
    free(ponteiro6);

    long *ponteiro7 = (long*) safeCalloc(sizeof(long), 1);
    assert(ponteiro7 != NULL);
    free(ponteiro7);

    long long *ponteiro8 = (long long*) safeCalloc(sizeof(long long), 1);
    assert(ponteiro8 != NULL);
    free(ponteiro8);

    char *ponteiro9 = (char*) safeCalloc(sizeof(char), 1);
    assert(ponteiro9 != NULL);
    free(ponteiro9);

    float *ponteiro10 = (float*) safeCalloc(sizeof(float), 1);
    assert(ponteiro10 != NULL);
    free(ponteiro10);

    double *ponteiro11 = (double*) safeCalloc(sizeof(double), 1);
    assert(ponteiro11 != NULL);
    free(ponteiro11);

    long double *ponteiro12 = (long double*) safeCalloc(sizeof(long double), 1);
    assert(ponteiro12 != NULL);
    free(ponteiro12);
}

void testSafeMalloc()
{
    unsigned short *ponteiro0 = (unsigned short*) safeMalloc(sizeof(unsigned short));
    assert(ponteiro0 != NULL);
    free(ponteiro0);

    unsigned int *ponteiro1 = (unsigned int*) safeMalloc(sizeof(unsigned int));
    assert(ponteiro1 != NULL);
    free(ponteiro1);

    unsigned long *ponteiro2 = (unsigned long*) safeMalloc(sizeof(unsigned long));
    assert(ponteiro2 != NULL);
    free(ponteiro2);

    unsigned long long *ponteiro3 = (unsigned long long*) safeMalloc(sizeof(unsigned long long));
    assert(ponteiro3 != NULL);
    free(ponteiro3);

    unsigned char *ponteiro4 = (unsigned char*) safeMalloc(sizeof(unsigned char));
    assert(ponteiro4 != NULL);
    free(ponteiro4);

    short *ponteiro5 = (short*) safeMalloc(sizeof(short));
    assert(ponteiro5 != NULL);
    free(ponteiro5);

    int *ponteiro6 = (int*) safeMalloc(sizeof(int));
    assert(ponteiro6 != NULL);
    free(ponteiro6);

    long *ponteiro7 = (long*) safeMalloc(sizeof(long));
    assert(ponteiro7 != NULL);
    free(ponteiro7);

    long long *ponteiro8 = (long long*) safeMalloc(sizeof(long long));
    assert(ponteiro8 != NULL);
    free(ponteiro8);

    char *ponteiro9 = (char*) safeMalloc(sizeof(char));
    assert(ponteiro9 != NULL);
    free(ponteiro9);

    float *ponteiro10 = (float*) safeMalloc(sizeof(float));
    assert(ponteiro10 != NULL);
    free(ponteiro10);

    double *ponteiro11 = (double*) safeMalloc(sizeof(double));
    assert(ponteiro11 != NULL);
    free(ponteiro11);

    long double *ponteiro12 = (long double*) safeMalloc(sizeof(long double));
    assert(ponteiro12 != NULL);
    free(ponteiro12);
}

void testSafeFree()
{
    unsigned short *ponteiro0 = (unsigned short*) safeCalloc(sizeof(unsigned short), 1);
    *ponteiro0 = 99;
    safeFree(ponteiro0);
    assert(*ponteiro0 == 0);

    unsigned int *ponteiro1 = (unsigned int*) safeCalloc(sizeof(unsigned int), 1);
    *ponteiro1 = 200;
    safeFree(ponteiro1);
    assert(*ponteiro1 == 0);

    unsigned long *ponteiro2 = (unsigned long*) safeCalloc(sizeof(unsigned long), 1);
    *ponteiro2 = 9999;
    safeFree(ponteiro2);
    assert(*ponteiro2 == 0);

    unsigned long long *ponteiro3 = (unsigned long long*) safeCalloc(sizeof(unsigned long long), 1);
    *ponteiro3 = 2398;
    safeFree(ponteiro3);
    assert(*ponteiro3 == 0);

    unsigned char *ponteiro4 = (unsigned char*) safeCalloc(sizeof(unsigned char), 1);
    *ponteiro4 = 'a';
    safeFree(ponteiro4);
    assert(*ponteiro4 == '\0');

    short *ponteiro5 = (short*) safeCalloc(sizeof(short), 1);
    *ponteiro5 = 8;
    safeFree(ponteiro5);
    assert(*ponteiro5 == 0);

    int *ponteiro6 = (int*) safeCalloc(sizeof(int), 1);
    *ponteiro6 = 23;
    safeFree(ponteiro6);
    assert(*ponteiro6 == 0);

    long *ponteiro7 = (long*) safeCalloc(sizeof(long), 1);
    *ponteiro7 = 34299878;
    safeFree(ponteiro7);
    assert(*ponteiro7 == 0);

    long long *ponteiro8 = (long long*) safeCalloc(sizeof(long long), 1);
    *ponteiro8 = 123146546548;
    safeFree(ponteiro8);
    assert(*ponteiro8 == 0);

    char *ponteiro9 = (char*) safeCalloc(sizeof(char), 1);
    *ponteiro9 = 'c';
    safeFree(ponteiro9);
    assert(*ponteiro9 == 0);

    float *ponteiro10 = (float*) safeCalloc(sizeof(float), 1);
    *ponteiro10 = 3.145949;
    safeFree(ponteiro10);
    assert(*ponteiro10 == 0.000000);

    double *ponteiro11 = (double*) safeCalloc(sizeof(double), 1);
    *ponteiro11 = 123.234;
    safeFree(ponteiro11);
    assert(*ponteiro11 == 0.000000);

}

void testStrSubstring()
{
    char string[] = "ola mundo. testando um programa em C.";
    char *substring = strSubstring(strdup(string), 5, 8);
    assert(strcmp(substring, "und") == 0);
}

void testStrIndexOfBegin()
{
    char string[] = "pato rato gato";
    size_t posicao = strIndexOfBegin(strdup(string), strdup("ato"), 2);
    assert(posicao == 6);
}

int main()
{
    testSafeCalloc();
    testSafeMalloc();
    testSafeFree();
    testStrSubstring();
    testStrIndexOfBegin();
}