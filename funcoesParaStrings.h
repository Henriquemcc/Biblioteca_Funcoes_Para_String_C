#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//Define a quantidade maxima de erros seguidos que podem ocorrer dentro do looping das funcoes safeCalloc e safeMalloc.
short quantidadeMaximaErros = 100;

/**
 * Esta funcao serve para executar de forma segura a funcao calloc, evitando parametros menores ou iguais a zero e retorno igual a NULL.
 * @param nmemb Parametro nmemb que sera repassado para a funcao calloc.
 * @param size Parametro size que sera repassado para a funcao calloc.
 * @return Ponteiro diferente de null retornado da funcao calloc.
 */
void *safeCalloc(const size_t nmemb, const size_t size)
{
    if (nmemb <= 0)
    {
        perror("O valor do parametro nmemb nao pode ser menor ou igual a zero.\n");
        abort();
    }

    if (size <= 0)
    {
        perror("O valor do parametro size nao pode ser menor ou igual a zero.\n");
        abort();
    }

    void *ponteiro = NULL;

    bool erro = true;
    short quantidadeErros = 0;
    while(erro)
    {
        ponteiro = calloc(nmemb, size);

        if (ponteiro == NULL)
        {
            erro = true;
            perror("Erro ao realizar o calloc. O valor retornado eh NULL.\n");
            quantidadeErros++;
        }
        else erro = false;

        if (quantidadeErros >= quantidadeMaximaErros)
        {
            perror("Varios erros seguidos aconteceram ao tentar realizar o alocamento de memoria por meio da funcao calloc da linguagem C.\n");
            abort();
        }
    }

    return ponteiro;
}

/**
 * Esta funcao serve para executar de forma segura a funcao malloc, evitando parametros menores ou iguais a zero e retorno igual a NULL.
 * @param size Parametro size que sera repassado para a funcao malloc.
 * @return Ponteiro diferente de NULL retornado da funcao malloc.
 * */
void *safeMalloc(const size_t size)
{
    if (size <= 0)
    {
        perror("O valor do parametro size nao pode ser menor ou igual a zero.\n");
        abort();
    }

    void *ponteiro = NULL;

    bool erro = true;
    short quantidadeErros = 0;
    while(erro)
    {
        ponteiro = malloc(size);

        if (ponteiro == NULL)
        {
            erro = true;
            perror("Erro ao realizar o malloc. O valor retornado eh NULL.\n");
            quantidadeErros++;
        }
        else erro = false;

        if (quantidadeErros >= quantidadeMaximaErros)
        {
            perror("Varios erros seguidos aconteceram ao tentar realizar o alocamento de memoria por meio da funcao malloc da linguagem C.\n");
            abort();
        }
    }

    return ponteiro;
}

/**
 * Esta funcao serve para limpar a area de memoria apontada pelo ponteiro para depois liberar por meio da funcao nativa free() da linguagem C.
 * @param ptr Ponteiro para a regiao de memoria a ser limpada e liberada.
 */
void safeFree(void *ptr)
{
    if (ptr == NULL)
    {
        perror("O parametro ptr da funcao safeFree nao pode ser nulo.\n");
        abort();
    }

    memset(ptr, '\0', sizeof(ptr));
    free(ptr);
}

char *strClone(const char *srcString)
{
    char *clone = calloc(sizeof(char), strlen(srcString)+1);
    strcpy(clone, srcString);
    return clone;
}

/**
 * Esta funcao serve para obter um segmento de um arranjo de caracteres, informando onde que sera cortado.
 * @param *str Ponteiro apontando para o arranjo de caracteres original que sera cortado.
 * @param begin Indice de inicio.
 * @param length Indice de fim nao incluindo o elemento do fim.
 * @return Ponteiro apontando para o arranjo de caracteres resultante.
*/
char *strSubstring(const char *srcString, const size_t beginIndex, const size_t endIndex)
{
    if (beginIndex < 0)
    {
        perror("O valor do parametro beginIndex da funcao strSubstring nao pode ser inferior a zero.\n");
        abort();
    }

    if (endIndex <= 0)
    {
        perror("O valor do parametro endIndex da funcao strSubstring nao pode ser inferior ou igual a zero.\n");
        abort();
    }

    if (beginIndex >= strlen(srcString))
    {
        perror("O valor do parametro beginIndex da funcao strSubstring nao pode ser superior ou igual ao tamanho da srcString.\n");
        abort();
    }

    if (endIndex > strlen(srcString))
    {
        perror("O valor do parametro endIndex da funcao strSubstring nao pode ser superior ao tamanho da srcString.\n");
        abort();
    }

    size_t lenResult= endIndex - beginIndex + 1;
    char result[lenResult];
    size_t i, j;
    for(i=beginIndex, j=0; i < endIndex ; i++, j++)
    {
        result[j]=srcString[i];
    }
    result[j]='\0';
   
    return strdup(result);
}

/**
 * Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres que nele sera procurada por um segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres no arranjo de caracteres.
*/
size_t strIndexOf(const char *srcString, const char *str)
{
    if (srcString == NULL)
    {
        perror("O parametro srcString da funcao strIndexOf nao pode ser nulo.\n");
        abort();
    }

    if (str == NULL)
    {
        perror("O parametro str da funcao strIndexOf nao pode ser nulo.\n");
        abort();
    }

    if (strlen(str) > strlen(srcString))
    {
        perror("O tamanho do valor do parametro str nao pode ser maior que o tamanho do valor do parametro srcString na funcao strIndexOf.\n");
        abort();
    }

    size_t position = strlen(srcString);
    size_t headSrcString = 0;
    size_t headStr = 0;
    while(headSrcString < strlen(srcString))
    {
        //Comparando caractere por caractere
        size_t headSrcStringComp = headSrcString;
        while ((srcString[headSrcStringComp] == str[headStr]) && (headStr < strlen(str)) && (headSrcStringComp < strlen(srcString)))
        {
            headStr++;
            headSrcStringComp++;
        }

        //Caso seja igual os caracteres o valor de headRegex sera igual ao tamanho da string regex.
        if (headStr == strlen(str))
        {
            position = headSrcString;
            headSrcString = strlen(srcString); // <- finalizando o looping.
        }

        //Casos os caracteres nao sejam iguais o valor de headRegex sera menor que o tamanho da string regex.
        else if (headStr < strlen(str))
        {
            headStr = 0;
            headSrcString++;
        }

        //Erro inesperado
        else
        {
            perror("Erro inesperado na funcao strIndexOf.");
            abort();
        }
    }

    return position;
}

/**
 * Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera feita a busca pelo segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param begin Posicao limite a esquerda.
 * @return A menor posicao da primeira ocorrencia do segmento de arranjo de caracteres no arranjo de caracteres.
*/
size_t strIndexOfFromIndex(const char *srcString, const char *str, const size_t fromIndex)
{
    if (srcString == NULL)
    {
        perror("O parametro srcString da funcao strIndexOfFromIndex nao pode ser nulo\n");
        abort();
    }

    if (str == NULL)
    {
        perror("O parametro str da funcao strIndexOfFromIndex nao pode ser nulo.\n");
        abort();
    }

    if (fromIndex < 0)
    {
        perror("O valor do parametro fromIndex da funcao strIndexOfFromIndex nao pode ser inferior a zero.\n");
        abort();
    }

    if (fromIndex >= strlen(srcString))
    {
        perror("O valor do parametro fromIndex da funcao strIndexOfFromIndex nao pode ser superior ou igual ao tamanho da srcString.\n");
        abort();
    }

    char *cutSrcString = strSubstring(srcString, fromIndex, strlen(srcString));

    return strIndexOf(cutSrcString, str) + fromIndex;

}

/**
 * Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A maior posicao da primeira ocorrencia do segmento no arranjo de caracteres.
*/
size_t strLastIndexOf(const char *srcString, const char *str)
{
    if (srcString == NULL)
    {
        perror("O parametro srcString da funcao strLastIndexOf nao pode ser nulo.\n");
        abort();
    }

    if (str == NULL)
    {
        perror("O parametro str da funcao strLastIndexOf nao pode ser nulo.\n");
        abort();
    }

    if (strlen(str) > strlen(srcString))
    {
        perror("O tamanho do valor do parametro str nao pode ser maior que o tamanho do valor do parametro srcString na funcao strLastIndexOf.\n");
        abort();
    }

    size_t position= strlen(srcString);
    size_t headSrcString = strlen(srcString) -1;
    size_t headStr = strlen(str) -1;
    bool repetir0 = true;
    while (repetir0)
    {
        //Comparando caractere por caractere
        size_t headSrcStringComp = headSrcString;
        bool repetir1 = true;
        bool saoIguais = false;
        while (repetir1)
        {
            if (srcString[headSrcStringComp] != str[headStr])
            {
                repetir1 = false;
            }
            else if (headSrcStringComp == 0 || headStr == 0)
            {
                saoIguais = true;
                repetir1 = false;
            }
            else
            {
                headStr--;
                headSrcStringComp--;
            }
        }

        if (saoIguais)
        {
            position = headSrcStringComp;
            repetir0 = false;
        }

        else if (headSrcString == 0)
            repetir0 = false;

        else if (headSrcString > 0)
        {
            headStr = strlen(str) -1;
            headSrcString--;
        }

        else
        {
            perror("Erro inesperado na funcao strLastIndexOf.");
            abort();
        }

    }

    return position;
}

/**
 * Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de um arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param end Posicao limite a esquerda.
 * @return A maior posicao da primeira ocorrencia da substring na String.
*/
size_t strLastIndexOfFromIndex(const char *srcString, const char *str, const size_t fromIndex)
{
    if (srcString == NULL)
    {
        perror("O parametro srcString da funcao strLastIndexOfFromIndex nao pode ser nulo.\n");
        abort();
    }

    if (str == NULL)
    {
        perror("O parametro str da funcao strLastIndexOfFromIndex nao pode ser nulo.\n");
        abort();
    }

    if (fromIndex <= 0)
    {
        perror("O valor do parametro fromIndex da funcao strLastIndexOfFromIndex nao pode ser inferior ou igual a zero.\n");
        abort();
    }

    if (fromIndex > strlen(srcString))
    {
        perror("O valor do parametro fromIndex da funcao strLastIndexOfFromIndex nao pode ser superior ao tamanho da srcString.\n");
        abort();
    }

    char *cutSrcString = strSubstring(srcString, 0, fromIndex);

    return strLastIndexOf(cutSrcString, str);

}

/**
 * Esta funcao serve para realizar a substituicao de um segmento arranjo de caracteres contido dentro de outro arranjo de caracteres por outro segmento de arranjo de caracteres.
 * @param *original Ponteiro apontando para o arranjo de caracteres srcString que sera modificado, resultando no retorno.
 * @param *replace Ponteiro apontando para o arranjo de caracteres que sera removido.
 * @param *replacement Ponteiro apontando para o arranjo de caracteres que sera adicionado no lugar do segmento de arranjo de caracteres que foi removido.
 * @return Ponteiro apontando para o novo arranjo de caracteres gerado a partir da substituicao.
*/
char *strReplaceAll(const char *srcString, const char *regex, const char *replacement)
{
    if (srcString == NULL)
    {
        perror("O parametro srcString do metodo strReplaceAll nao pode ser nulo.\n");
        abort();
    }

    if (regex == NULL)
    {
        perror("O parametro regex do metodo strReplaceAll nao pode ser nulo.\n");
        abort();
    }

    if (replacement == NULL)
    {
        perror("O parametro replacement do metodo strReplaceAll nao pode ser nulo.\n");
        abort();
    }

    if (strlen(regex) > strlen(srcString))
    {
        perror("O tamanho do valor do parametro regex nao pode ser maior que o tamanho do valor do parametro srcString.\n");
        abort();
    }

    //Contando as ocorrencias do regex
    size_t numberReplacements = 0;
    size_t headCounterReplacements = 0;
    bool repetir = true;
    while (headCounterReplacements < strlen(srcString))
    {
        headCounterReplacements = strIndexOfFromIndex(srcString, regex, headCounterReplacements)+1;

        if (headCounterReplacements < strlen(srcString))
            numberReplacements++;

        else if (headCounterReplacements > strlen(srcString))
        {
            perror("Erro inesperado na funcao strReplaceAll.");
            abort();
        }
    }

    //Criando uma copia da string original
    char destString[strlen(srcString) + numberReplacements*(strlen(replacement) - strlen(regex))+1];

    size_t headSrcString = 0;
    size_t headDestString = 0;
    size_t headRegex = 0;
    size_t headReplacement = 0;

    //Executando o algoritmo da forca bruta
    while (headSrcString < strlen(srcString))
    {
        //Comparando caractere por caractere
        size_t headSrcStringComp = headSrcString;
        while ( (srcString[headSrcString] == regex[headRegex]) && (headRegex < strlen(regex)) && (headSrcString < strlen(srcString)) )
        {
            headRegex++;
            headSrcStringComp++;
        }

        //Caso seja igual os caracteres o valor de headRegex sera igual ao tamanho da string regex.
        if (headRegex == strlen(regex))
        {
            headRegex = 0;
            headReplacement = 0;
            while (headReplacement < strlen(replacement))
            {
                destString[headDestString++] = replacement[headReplacement++];
            }
            headSrcString++;

        }

        //Casos os caracteres nao sejam iguais o valor de headRegex sera menor que o tamanho da string regex.
        else if (headRegex < strlen(regex))
        {
            headRegex = 0;
            destString[headDestString++] = srcString[headSrcString++];
        }

        //Erro inesperado
        else
        {
            perror("Erro inesperado na funcao strReplaceAll.");
            abort();
        }
    }

    return strdup(destString);
}


/**
 * Esta funcao serve para verificar se um segmento de arranjo de caracteres esta contido em uma posicao do arranjo de arranjo de caracteres.
 * @param *str[] Um arranjo de ponteiros apontando para os arranjos de caracteres.
 * @param len_str Numero de elementos no arranjo de ponteiros str.
 * @param *key Ponteiro apontando para para o arranjo de caracteres chave da pesquisa.
 * @return Valor booleano indicando se o elemento procurado encontra-se no arranjo de arranjos de caracteres.
*/
bool strArrContains(const char **str, const size_t lenStr, const char *key)
{
    bool contains=false;
    size_t i=0;
    while(i < lenStr)
    {
        if(strcmp(str[i], key)==0)
        {
            contains=true;
            i=lenStr;
        }
        i++;
    }

    return contains;
}

/**
 * Esta funcao serve para converter um arranjo de caracteres para minusculo.
 * @param *string Ponteiro apontando para o arranjo de caracteres cujos caracteres serao convertidos para maiusculo.
 * @return Ponteiro apontando para o novo arranjo de caracteres resultante do processo de conversao para minusculo.
*/
char *strToLowerCase(const char *string)
{    
    char copyString[strlen(string)];
    strcpy(copyString, string);
    for(int i=0;i<strlen(string);i++)
    {
        copyString[i]= (char) tolower(copyString[i]);
    }

    return strdup(copyString);
}