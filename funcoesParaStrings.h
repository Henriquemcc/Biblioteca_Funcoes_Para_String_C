#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//Define a quantidade maxima de erros seguidos que podem ocorrer dentro do looping das funcoes safeCalloc e safeMalloc.
short quantidadeMaximaErros = 100;

/**
 * Serve para executar de forma segura a funcao calloc, evitando parametros menores ou iguais a zero e retorno igual a NULL.
 * @param nmemb Parametro nmemb que sera repassado para a funcao calloc.
 * @param size Parametro size que sera repassado para a funcao calloc.
 * @return Ponteiro diferente de null retornado da funcao calloc.
 * @attention O programa ira abortar caso um dos valores passados por parametros seja inferior ou igual a zero.
 * @attention O programa ira abortar caso apos o calloc retorne null por quantidadeMaximaErros tentativas consecutivas.
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
 * Serve para executar de forma segura a funcao malloc, evitando parametros menores ou iguais a zero e retorno igual a NULL.
 * @param size Parametro size que sera repassado para a funcao malloc.
 * @return Ponteiro diferente de NULL retornado da funcao malloc.
 * @attention O programa ira abortar caso o valor passado por parametro seja inferior ou igual a zero.
 * @attention O programa ira abortar caso apos o malloc retorne null por quantidadeMaximaErros tentativas consecutivas.
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
 * Serve para limpar a area de memoria apontada pelo ponteiro para depois liberar por meio da funcao nativa free() da linguagem C.
 * @param ptr Ponteiro para a regiao de memoria a ser limpada e liberada.
 * @attention O programa ira abortar caso o parametro ptr seja nulo.
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

/**
 * Serve para criar uma copia de uma String.
 * @param srcString Ponteiro da String que sera copiada.
 * @return Ponteiro da copia da String.
 * */
char *strClone(const char *srcString)
{
    char *clone = safeCalloc(sizeof(char), strlen(srcString)+1);
    strncpy(clone, srcString, strlen(srcString)+1);
    return clone;
}

/**
 * Serve para obter uma fatia de uma String.
 * @param srcString Ponteiro para a String original.
 * @param beginIndex Indice esquerdo do corte. O caractere na posicao deste indice sera incluido na string resultante.
 * @param endIndex Indice direito do corte. O caractere na posicao deste indice nao sera incluido na string resultante.
 * @return Nova string resultante do corte da string de entrada.
 * @attention O programa ira abortar caso o beginIndex seja menor que zero ou maior ou igual ao tamanho da string de origem.
 * @attention O programa ira abortar caso o endIndex seja menor ou igual a zero ou maior que o tamanho da string de origem.
 * */
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
 * Serve para obter a primeira ocorrencia de uma substring em uma string.
 * @param srcString Ponteiro para a String original.
 * @param str Ponteiro para a substring que sera procurada na string de origem.
 * @return Posicao da primeira ocorrencia da substring na string.
 * @attention Caso nao seja encontrado a substring na string sera retornado o tamanho da string de origem.
 * @attention Caso um dos parametros seja nulo o programa ira abortar.
 * @attention Caso o tamanho da string str seja maior que o tamanho da srcString, o programa ira abortar.
 * */
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
 * Serve para obter a primeira ocorrencia de uma substring em uma string com um indice esquerdo delimitador.
 * @param srcString Ponteiro para a String original.
 * @param str Ponteiro para a substring que sera procurada na string de origem.
 * @param fromIndex Indice esquerdo delimitador. O caractere na posicao do indice sera incluido na area de busca.
 * @return Posicao da primeira ocorrencia da substring na string.
 * @attention Caso um dos parametros srcString ou str seja nulo, o programa sera abortado.
 * @attention Caso o valor de fromIndex seja inferior a zero ou superior ou igual ao tamanho da srcString, o programa sera abortado.
 * */
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
 * Serve para obter posica da ultima ocorrencia de uma substring em uma string.
 * @param srcString Ponteiro para a String original.
 * @param str Ponteiro para a substring que sera procurada
 * @return Posicao da ultima ocorrencia da substring na string.
 * @attention Caso um dos parametros srcString ou str seja nulo, o programa sera abortado.
 * @attention Caso o tamanho de str seja maior que o tamanho de srcString, o programa sera abortado.
 * */
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
 * Serve para obter a ultima ocorrencia de uma substring em uma string com indice direito delimitador.
 * @param srcString Ponteiro para a String original.
 * @param str Ponteiro para a substring a ser procurada.
 * @param fromIndex Indice direito delimitador. O caractere na posicao do indice nao sera incluido na area de busca.
 * @return Posicao da ultima ocorrencia da substring na string.
 * @attention Caso um dos parametros srcString ou str seja nulo, o programa sera abortado.
 * @attention Caso o valor de fromIndex seja menor ou igual a zero ou maior o tamanho da srcString, o programa sera abortado.
 * */
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
 * Serve para substituir todas as ocorrencias das substrings na string de origem pela string de substituicao.
 * @param srcString Ponteiro para a String de origem.
 * @param regex Ponteiro para a substring a ser substituida todas as suas ocorrencias.
 * @param replacement Ponteiro para a string que ira substituir a string de substituicao.
 * @return Ponteiro para a String resultante da substituicao.
 * @attention Caso um dos parametros srcString, regex ou replacement seja nulo, o programa ira abortar.
 * @attention Caso o tamanho de regex seja maior que o tamanho da srcString, o programa ira abortar.
 * */
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
 * Serve para verificar se um arranjo de string contem uma string.
 * @param str Ponteiro para o Arranjo de strings.
 * @param lenStr Tamanho do arranjo de strings.
 * @param key Ponteiro para a string procurada.
 * @return Valor booleano indicando se a string foi encontrada no arranjo.
 * */
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
 * Serve para converter as letras maiusculas uma string para minusculos.
 * @param string Ponteiro para a string de origem.
 * @return Ponteiro para a string resultante.
 * */
char *strToLowerCase(const char *string)
{    
    char *copyString = strClone(string);
    for(int i=0;i<strlen(string);i++)
    {
        copyString[i]= (char) tolower(copyString[i]);
    }

    return copyString;
}