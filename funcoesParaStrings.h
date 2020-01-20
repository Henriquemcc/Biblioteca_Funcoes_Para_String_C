#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define boolean short
#define true 1
#define false 0

/**
 * Funcao da Funcao: Esta funcao serve para obter um segmento de um arranjo de caracteres, informando onde que sera cortado.
 * @param *str Ponteiro apontando para o arranjo de caracteres original que sera cortado.
 * @param begin Indice de inicio.
 * @param length Indice de fim nao incluindo o elemento do fim.
 * @return Ponteiro apontando para o arranjo de caracteres resultante.
*/
char *str_substring(char *str, int begin, int length)
{
    int len_result=length-begin+1;
    char result[len_result];
    int i, j;
    for(i=begin, j=0; i<length ; i++, j++)
    {
        result[j]=str[i];
    }
    result[j]='\0';
   
    return strdup(result);
}//fim da funcao str_substring

/**
 * Funcao da Funcao: Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres que nele sera procurada por um segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres no arranjo de caracteres.
*/
int str_indexOf(char *string, char *key)
{    
    int position=-1;
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
                i=strlen(string);//<-finalizando o looping
            }
        }
        else
            i++;
    }

    //Colocando NULL para todos os ponteiros
    string=NULL;
    key=NULL;

    return position;
}//fim da funcao str_indexOf

/**
 * Funcao da Funcao: Esta funcao serve para obter a menor posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera feita a busca pelo segmento.
 * @param *key Ponteiro apontando para um segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param begin Posicao limite a esquerda.
 * @return A menor posicao da primeira ocorrencia do segmento de arranjo de caracteres no arranjo de caracteres.
*/
int str_indexOfBegin(char *string, char *key, int begin)
{
    char *copy_string=(char*)calloc(1+strlen(string), sizeof(char));
    strcpy(copy_string, string);
    strcpy(copy_string, str_substring(copy_string, begin, strlen(copy_string)));

    int resp=str_indexOf(copy_string, key)+begin;

    return resp;
}//fim do metodo str_indexOfBegin

/**
 * Funcao da Funcao: Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @return A maior posicao da primeira ocorrencia do segmento no arranjo de caracteres.
*/
int str_lastIndexOf(char *string, char *key)
{
    const int len_string=strlen(string);
    const int len_key=strlen(key);
    int position=-1;
    int i=len_string-1;
    while(i>=0)
    {
        if(string[i]==key[len_key-1])
        {
            int j=len_key-2;
            i--;
            while(string[i]==key[j] && j>=0 && i>=0)
            {
                i--;
                j--;
            }
            if(j==-1)
            {
                position=i+1;
                i=-1;//<-finalizando o looping
            }
        }
        else
            i--;
    }

    //Colocando NULL para todos os ponteiros
    string=NULL;
    key=NULL;

    return position;
}//fim da funcao str_lastIndexOf

/**
 * Funcao da Funcao: Esta funcao serve para obter a maior posicao da primeira ocorrencia de um segmento de um arranjo de caracteres em um arranjo de caracteres.
 * @param *string Ponteiro apontando para um arranjo de caracteres no qual sera realizado a busca pelo segmento.
 * @param *key Ponteiro apontando para o segmento de um arranjo de caracteres que sera procurado no arranjo de caracteres.
 * @param end Posicao limite a esquerda.
 * @return A maior posicao da primeira ocorrencia da substring na String.
*/
int str_lastIndexOfEnd(char *string, char *key, int end)
{
    char *copy_string=(char*)calloc(1+strlen(string), sizeof(char));
    strcpy(copy_string, string);
    copy_string=str_substring(copy_string, 0, end+1);

    //Colocando NULL para todos os ponteiros exceto copy_String e key
    string=NULL;

    int resp=str_lastIndexOf(copy_string, key);

    return resp;
}//fim da funcao str_lastIndexOfEnd

/**
 * Funcao da funcao: Esta funcao serve para realizar a substituicao de um segmento arranjo de caracteres contido dentro de outro arranjo de caracteres por outro segmento de arranjo de caracteres.
 * @param *original Ponteiro apontando para o arranjo de caracteres original que sera modificado, resultando no retorno.
 * @param *replace Ponteiro apontando para o arranjo de caracteres que sera removido.
 * @param *replacement Ponteiro apontando para o arranjo de caracteres que sera adicionado no lugar do segmento de arranjo de caracteres que foi removido.
 * @return Ponteiro apontando para o novo arranjo de caracteres gerado a partir da substituicao.
*/
char *str_replaceAll(char *original, char *replace, char *replacement)
{
    char *copia_original=(char*)calloc(1+strlen(original), sizeof(char));
    strcpy(copia_original, original);
    bool retornoNulo=false;
    char *result;//A String resultante
    char *ins;//O proximo ponto de insercao
    char *tmp;//Variavel temporaria
    int len_replace;//tamanho de replace (String a ser removida)
    int len_replacement;//tamanho de replacement(String a ser colocada no lugar de replace)
    int len_front;//distancia entre o inicio e o fim de replace
    int count;//numero de substituicoes

    //Chacando se eh possivel inicializar a substituicao
    if(copia_original && replace)
    {
        len_replace=strlen(replace);
        if(len_replace!=0)
        {
            if(!replacement)
            {
                replacement=(char*)calloc(1, sizeof(char));
                strcpy(replacement, "");
            }

            len_replacement=strlen(replacement);

            //Contando o numero de substituicoes que deverao ser realizadas
            ins=copia_original;
            for(count=0;tmp=strstr(ins, replace); count++)
                ins=tmp+len_replace;

            tmp=result=(char*)calloc(1+strlen(copia_original)+(len_replacement-len_replace)*count+1, sizeof(char));

            if(result)
            {
                while(count--)
                {
                    ins=strstr(copia_original, replace);
                    len_front=ins-copia_original;
                    tmp=strncpy(tmp, copia_original, len_front)+len_front;
                    tmp=strcpy(tmp, replacement)+len_replacement;
                    copia_original+=len_front+len_replace;
                }
                strcpy(tmp, copia_original);
            }
            else retornoNulo=true;
        }
        else retornoNulo=true;

    }
    else retornoNulo=true;

    char *retorno=result;
    if(retornoNulo)
    {
        *retorno=*copia_original;
        copia_original=NULL;
    }

    //Colocando NULL em todos os ponteiros exceto retorno
    replace=NULL;
    replacement=NULL;
    copia_original=NULL;
    result=NULL;
    ins=NULL;
    tmp=NULL;

    return retorno;
}//fim da funcao str_replaceAll


/**
 * Funcao da funcao: Esta funcao serve para verificar se um segmento de arranjo de caracteres esta contido em uma posicao do arranjo de arranjo de caracteres.
 * @param *str[] Um arranjo de ponteiros apontando para os arranjos de caracteres.
 * @param len_str Numero de elementos no arranjo de ponteiros str.
 * @param *key Ponteiro apontando para para o arranjo de caracteres chave da pesquisa.
 * @return Valor booleano indicando se o elemento procurado encontra-se no arranjo de arranjos de caracteres.
*/
bool str_arr_contains(char *str[], int len_str, char *key)
{
    bool contains=false;
    int i=0;
    while(i<len_str)
    {
        if(strcmp(str[i], key)==0)
        {
            contains=true;
            i=len_str;
        }
        i++;
    }

    //Colocando NULL em todos os ponteiros
    str=NULL;
    key=NULL;

    return contains;
}//fim da funcao str_arr_contains

/**
 * Funcao da funcao: Esta funcao serve para converter um arranjo de caracteres para minusculo.
 * @param *string Ponteiro apontando para o arranjo de caracteres cujos caracteres serao convertidos para maiusculo.
 * @return Ponteiro apontando para o novo arranjo de caracteres resultante do processo de conversao para minusculo.
*/
char *str_toLowerCase(char *string)
{    
    char copy_string[strlen(string)];
    strcpy(copy_string, string);
    for(int i=0;i<strlen(string);i++)
    {
        copy_string[i]=tolower(copy_string[i]);
    }

    return strdup(copy_string);
}//fim da funcao str_toLowerCase