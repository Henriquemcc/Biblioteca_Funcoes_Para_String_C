#include "funcoesParaStrings.h"

void testSafeCalloc()
{
    int *ponteiro0 = (int*) safeCalloc(sizeof(int), 1);
    *ponteiro0 = 2000;
    printf("Endereco de memoria ponteiro 0: %p\n", ponteiro0);
    printf("Valor do ponteiro 0: %d\n", *ponteiro0);
}

void testSafeMalloc()
{
    int *ponteiro0 = (int*) safeMalloc(sizeof(int));
    *ponteiro0 = 2000;
    printf("Endereco de memoria ponteiro 0: %p\n", ponteiro0);
    printf("Valor do ponteiro 0: %d\n", *ponteiro0);
}

void testStrSubstring()
{
    char string[] = "ola mundo. testando um programa em C.";
    char *substring = strSubstring(strdup(string), 5, 8);
    printf("Valor da substring: %s\n", substring);
}

int main()
{
    testSafeCalloc();
    testSafeMalloc();
    testStrSubstring();
}