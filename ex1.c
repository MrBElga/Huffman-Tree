
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "tad.h"

void checarFreq(ListaR **ListaReg, char frase[], int *j)
{
    ListaR *aux;
    char palavra[100];
    int i, k = 0, l;
    l = strlen(frase);

    for (i = 0; i < l; i++)
    {
        if (isalpha(frase[i]) || isdigit(frase[i]))
        {
            palavra[k] = toupper(frase[i]);
            k++;
        }
        else if (k > 0)
        {
            palavra[k] = '\0';
            if (!SomaFreq(&*ListaReg, palavra))
            {
                insereListaR(&*ListaReg, 1, *j, palavra, NULL);
                (*j)++;
            }
            k = 0;
        }
    }

    if (k > 0)
    {
        palavra[k] = '\0';
        if (!SomaFreq(&*ListaReg, palavra))
        {
            insereListaR(&*ListaReg, 1, *j, palavra, NULL);
            (*j)++;
        }
    }

    insereListaR(&*ListaReg, 0, *j, " ", NULL);
    (*j)++;

    aux = *ListaReg;
    while (aux->prox != NULL)
        aux = aux->prox;

    for (i = 0; i < l; i++)
    {
        if (frase[i] == ' ')
            aux->freq++;
    }
}

void criaListaArv(ListaR *ListaReg, ListaA **ListaArv)
{
    while (ListaReg != NULL)
    {
        inserirListaA(&*ListaArv, ListaReg->simb, ListaReg->freq);
        ListaReg = ListaReg->prox;
    }
}

void criarArvore(ListaA **ListaArv)
{
    ListaA *ant, *aux;
    int freq;
    ant = *ListaArv;
    aux = ant->prox;
    while (aux != NULL)
    {
        freq = (aux->no->freq) + (ant->no->freq);
        inserirA(&*ListaArv, &aux, &ant, -1, freq);
        excluir(&*ListaArv, ant->no->simb);
        excluir(&*ListaArv, aux->no->simb);
        ant = *ListaArv;
        aux = ant->prox;
    }
}

void inserirCod(ListaR **Lista, char codigo[], int simbolo)
{
    ListaR *aux;
    aux = *Lista;
    while (aux != NULL && aux->simb != simbolo)
        aux = aux->prox;
    if (aux != NULL)
        strcpy(aux->codHuff, codigo);
}

void geraCodigoHuff(Tree *no, ListaR **Lista, char codigo[], int i, int tamanho)
{
    if (i == 1)
    {
        codigo[tamanho] = '1';
        tamanho++;
        codigo[tamanho] = '\0';
    }
    else if (i == 0)
    {
        codigo[tamanho] = '0';
        tamanho++;
        codigo[tamanho] = '\0';
    }
    if (no != NULL)
    {
        if (no->simb != -1)
        {
            inserirCod(&*Lista, codigo, no->simb);
        }
        geraCodigoHuff(no->esq, &*Lista, codigo, 0, tamanho);
        geraCodigoHuff(no->dir, &*Lista, codigo, 1, tamanho);
    }
}

void copiarArquivoParaFrase(char nomeArquivo[], char *frase)
{
    FILE *arquivo;
    // printf("%s",nomeArquivo);
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL)
    {
        fread(frase, sizeof(char), 500, arquivo);
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir o arquivo\n");
        strcpy(frase, "");
    }
}

void gravarRegistrosEmBinario(ListaR *Lista)
{
    FILE *arquivoBinario = fopen("Arquivos/Registro.dat", "wb+");
    ListaR *atual;
    if (arquivoBinario != NULL)
    {
        atual = Lista;
        while (atual != NULL)
        {
            fwrite(atual, sizeof(ListaR), 1, arquivoBinario);
            atual = atual->prox;
        }

        fclose(arquivoBinario);
    }
    else
    {
        printf("Erro ao abrir o arquivo bin\n");
    }
}

void gravarCodigosNoArquivo(ListaR *ListaRegistro, char frase[])
{
    FILE *arquivo = fopen("Arquivos/codigo.txt", "w+");
    ListaR *aux;
    int i = 0, k;

    if (arquivo != NULL)
    {
        int len = strlen(frase);
        int j = 0;
        char palavra[100];

        for (k = 0; k <= len; k++)
        {
            if (isalpha(frase[k]) || isdigit(frase[k]))
            {
                if (isalpha(frase[k]))
                {
                    palavra[j] = toupper(frase[k]);
                }
                else
                {
                    palavra[j] = frase[k];
                }
                j++;
            }
            else if (frase[k] == ' ' || frase[k] == '\0')
            {
                palavra[j] = '\0';

                if (j > 0)
                {
                    aux = buscaPorpalavra(&ListaRegistro, palavra);
                    if (aux != NULL)
                    {
                        fprintf(arquivo, "%s", aux->codHuff);
                        // printf("%s, %s\n", aux->codHuff, aux->palavra);
                        if (frase[k] == ' ')
                        {
                            aux = buscaPorpalavra(&ListaRegistro, " ");
                            fprintf(arquivo, "%s", aux->codHuff);
                        }
                    }
                    j = 0;
                }
            }
        }

        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir o arquivo txt.");
    }
}

int main()
{
    system("MODE con cols=200 lines=90");
    system("title arvore de huffman");
    system("cls");

    ListaR *ListaRegistro;
    ListaA *ListaArvore;

    int Tamanho, i, j;
    char frase[500], codigoHuff[900], nomeArq[20];

    // arquivos
    strcpy(nomeArq, "frases/teste.txt");
    // strcpy(nomeArq,"frases/frase1.txt");
    // strcpy(nomeArq,"frases/frase2.txt");
    // strcpy(nomeArq,"frases/frase3.txt");
    // strcpy(nomeArq,"frases/frase4.txt");
    // strcpy(nomeArq,"frases/frase5.txt");
    // strcpy(nomeArq,"frases/frase6.txt");

    copiarArquivoParaFrase(nomeArq, frase);

    initListaR(&ListaRegistro);
    initListaA(&ListaArvore);

    Tamanho = 0;
    j = 0;
    i = -1;

    // gerar as estruturas
    // pegando frequencia das palavras
    checarFreq(&ListaRegistro, frase, &j);
    // criando Lista
    criaListaArv(ListaRegistro, &ListaArvore);

    // criando arvore
    criarArvore(&ListaArvore);

    // gerando codigo de huffman
    geraCodigoHuff(ListaArvore->no, &ListaRegistro, codigoHuff, i, Tamanho);

    // gerar aqruivos e gravas
    // arqBin

    gravarRegistrosEmBinario(ListaRegistro);
    // arqTxt
    gravarCodigosNoArquivo(ListaRegistro, frase);

    // exibicoes
    printf("Lista de registros\n");
    exibeListaR(ListaRegistro);
    printf("\narvore\n");
    exibe(ListaArvore->no, 0);
    return 0;
}
