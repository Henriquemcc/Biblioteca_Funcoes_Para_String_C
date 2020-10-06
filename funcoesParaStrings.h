#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//Define a quantidade maxima de erros seguidos que podem ocorrer dentro do looping das funcoes safeCalloc e safeMalloc.
short quantidadeMaximaErros = 10;

/**
 * Esta funcao serve para executar de forma segura a funcao calloc, evitando parametros menores ou iguais a zero e retorno igual a NULL.
 * @param nmemb Parametro nmemb que sera repassado para a funcao calloc.
 * @param size Parametro size que sera repassado para a funcao calloc.
 * @return Ponteiro diferente de null retornado da funcao calloc.
 */
void *safeCalloc(size_t nmemb, size_t size)
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
void *safeMalloc(size_t size)
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
 * Funcao da Funcao: Esta funcao serve para obter um segmento de um arranjo de caracteres, informando onde que sera cortado.
 * @param *str Ponteiro apontando para o arranjo de caracteres original que sera cortado.
 * @param begin Indice de inicio.
 * @param length Indice de fim nao incluindo o elemento do fim.
 * @return Ponteiro apontando para o arranjo de caracteres resultante.
*/
char *strSubstring(const char *str, int begin, size_t length)
{
    size_t lenResult= length - begin + 1;
    char result[lenResult];
    int i, j;
    for(i=begin, j=0; i<length ; i++, j++)
    {
        result[j]=str[i];
    }
    result[j]='\0';
   
    return strdup(result);
}//fim da funcao strSubstring

/**
 * Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres que nele sera procurada por um segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres no arranjo de caracteres.
*/
size_t strIndexOf(char *string, char *key)
{    
    size_t position= (size_t) -1;
    int i=0;
    while(i<strlen(string))
    {
        if(string[i]==key[0])
        {
            int j=1;
            i++;
            while(string[i]==key[j] && j<strlen(key) && i<strlen(string))
            {
                i++;
                j++;
            }
            if(j==strlen(key))
            {
                position=i-strlen(key);
                i= (int) strlen(string);//<-finalizando o looping
            }
        }
        else
            i++;
    }

    //Colocando NULL para todos os ponteiros

    return position;
}//fim da funcao strIndexOf

/**
 * Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera feita a busca pelo segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param begin Posicao limite a esquerda.
 * @return A menor posicao da primeira ocorrencia do segmento de arranjo de caracteres no arranjo de caracteres.
*/
size_t strIndexOfBegin(char *string, char *key, int begin)
{
    char *copyString=(char*)safeCalloc(1 + strlen(string), sizeof(char));
    strcpy(copyString, string);
    strcpy(copyString, strSubstring(copyString, begin, strlen(copyString)));

    size_t resp= strIndexOf(copyString, key) + begin;

    return resp;
}//fim do metodo strIndexOfBegin

/**
 * Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A maior posicao da primeira ocorrencia do segmento no arranjo de caracteres.
*/
size_t strLastIndexOf(char *string, char *key)
{
    const size_t lenString=strlen(string);
    const size_t  lenKey= (const int) strlen(key);
    size_t position= (size_t) -1;
    size_t i= lenString - 1;
    while(i>=0)
    {
        if(string[i]==key[lenKey - 1])
        {
            size_t j= lenKey - 2;
            i--;
            while(string[i]==key[j] && j>=0 && i>=0)
            {
                i--;
                j--;
            }
            if(j==-1)
            {
                position= (size_t) (i + 1);
                i= (size_t) -1;//<-finalizando o looping
            }
        }
        else
            i--;
    }

    //Colocando NULL para todos os ponteiros

    return position;
}//fim da funcao strLastIndexOf

/**
 * Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de um arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param end Posicao limite a esquerda.
 * @return A maior posicao da primeira ocorrencia da substring na String.
*/
size_t strLastIndexOfEnd(char *string, char *key, int end)
{
    char *copyString=(char*)safeCalloc(1 + strlen(string), sizeof(char));
    strcpy(copyString, string);
    copyString= strSubstring(copyString, 0, (size_t) (end + 1));

    //Colocando NULL para todos os ponteiros exceto copy_String e key

    size_t resp= strLastIndexOf(copyString, key);

    return resp;
}//fim da funcao strLastIndexOfEnd

/**
 * Esta funcao serve para realizar a substituicao de um segmento arranjo de caracteres contido dentro de outro arranjo de caracteres por outro segmento de arranjo de caracteres.
 * @param *original Ponteiro apontando para o arranjo de caracteres original que sera modificado, resultando no retorno.
 * @param *replace Ponteiro apontando para o arranjo de caracteres que sera removido.
 * @param *replacement Ponteiro apontando para o arranjo de caracteres que sera adicionado no lugar do segmento de arranjo de caracteres que foi removido.
 * @return Ponteiro apontando para o novo arranjo de caracteres gerado a partir da substituicao.
*/
char *strReplaceAll(char *original, char *replace, char *replacement)
{
    char *copiaOriginal=(char*)safeCalloc(1 + strlen(original), sizeof(char));
    strcpy(copiaOriginal, original);
    bool retornoNulo=false;
    char *result = NULL;//A String resultante
    char *ins;//O proximo ponto de insercao
    char *tmp;//Variavel temporaria
    int lenReplace;//tamanho de replace (String a ser removida)
    int lenReplacement;//tamanho de replacement(String a ser colocada no lugar de replace)
    int lenFront;//distancia entre o inicio e o fim de replace
    int count;//numero de substituicoes

    //Chacando se eh possivel inicializar a substituicao
    if(copiaOriginal && replace)
    {
        lenReplace= (int) strlen(replace);
        if(lenReplace != 0)
        {
            if(!replacement)
            {
                replacement=(char*)safeCalloc(1, sizeof(char));
                strcpy(replacement, "");
            }

            lenReplacement= (int) strlen(replacement);

            //Contando o numero de substituicoes que deverao ser realizadas
            ins=copiaOriginal;
            for(count=0;tmp=strstr(ins, replace); count++)
                ins= tmp + lenReplace;

            tmp=result=(char*)safeCalloc(1 + strlen(copiaOriginal) + (lenReplacement - lenReplace) * count + 1, sizeof(char));

            if(result)
            {
                while(count--)
                {
                    ins=strstr(copiaOriginal, replace);
                    lenFront= (int) (ins - copiaOriginal);
                    tmp= strncpy(tmp, copiaOriginal, (size_t) lenFront) + lenFront;
                    tmp= strcpy(tmp, replacement) + lenReplacement;
                    copiaOriginal+= lenFront + lenReplace;
                }
                strcpy(tmp, copiaOriginal);
            }
            else retornoNulo=true;
        }
        else retornoNulo=true;

    }
    else retornoNulo=true;

    char *retorno=result;
    if(retornoNulo)
    {
        *retorno=*copiaOriginal;
    }

    //Colocando NULL em todos os ponteiros exceto retorno

    return retorno;
}//fim da funcao strReplaceAll


/**
 * Esta funcao serve para verificar se um segmento de arranjo de caracteres esta contido em uma posicao do arranjo de arranjo de caracteres.
 * @param *str[] Um arranjo de ponteiros apontando para os arranjos de caracteres.
 * @param len_str Numero de elementos no arranjo de ponteiros str.
 * @param *key Ponteiro apontando para para o arranjo de caracteres chave da pesquisa.
 * @return Valor booleano indicando se o elemento procurado encontra-se no arranjo de arranjos de caracteres.
*/
bool strArrContains(char **str, int lenStr, char *key)
{
    bool contains=false;
    int i=0;
    while(i < lenStr)
    {
        if(strcmp(str[i], key)==0)
        {
            contains=true;
            i=lenStr;
        }
        i++;
    }

    //Colocando NULL em todos os ponteiros

    return contains;
}//fim da funcao strArrContains

/**
 * Esta funcao serve para converter um arranjo de caracteres para minusculo.
 * @param *string Ponteiro apontando para o arranjo de caracteres cujos caracteres serao convertidos para maiusculo.
 * @return Ponteiro apontando para o novo arranjo de caracteres resultante do processo de conversao para minusculo.
*/
char *strToLowerCase(char *string)
{    
    char copyString[strlen(string)];
    strcpy(copyString, string);
    for(int i=0;i<strlen(string);i++)
    {
        copyString[i]= (char) tolower(copyString[i]);
    }

    return strdup(copyString);
}//fim da funcao strToLowerCase