#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "tad.h"

void LerCodigo(char *Codigo, FILE *arqTxt) {
    arqTxt = fopen("Arquivos/codigo.txt", "r");
    if (arqTxt != NULL) {
        fgets(Codigo, 300, arqTxt);
        fclose(arqTxt);
    } else {
        printf("\nerro ao abrir arquivo\n");
    }
}


void gerarListaReg(ListaR **Lista, FILE *ArqBin) {
    ListaR Reg;
    ArqBin = fopen("Arquivos/Registro.dat", "rb");

    if (ArqBin != NULL) {
        fseek(ArqBin, 0, 0);
        while (fread(&Reg, sizeof(ListaR), 1, ArqBin)) {
            insereListaR(&*Lista, Reg.freq, Reg.simb, Reg.palavra, Reg.codHuff);
        }
        fclose(ArqBin);
    } else {
        printf("\nerro ao abrir arquivo\n");
    }
}


void gerarListaArv(ListaR *ListaReg, ListaA **ListaArv)
{
    while (ListaReg != NULL)
    {
        inserirListaA(&*ListaArv, ListaReg->simb, ListaReg->freq);
        ListaReg = ListaReg->prox;
    }
}

void gerarArvore(ListaA **Lista)
{
	ListaA *ant,*aux;
	int freq;
	ant = *Lista;
	aux = ant->prox;
	while(aux!=NULL)
	{
		freq = (aux->no->freq)+(ant->no->freq);
		inserirA(&*Lista,&aux,&ant,-1,freq);
		excluir(&*Lista,ant->no->simb);
		excluir(&*Lista,aux->no->simb);
		ant = *Lista;
		aux = ant->prox;
	}
}

void gerarFrase(ListaR **Lista, Tree *raiz, char codigo[], char frase[])
{
	int i=0,j=0;
	Tree *aux = raiz;
	
	while(codigo[i]!='\0')
	{	
		if(aux->simb!=-1)
		{
			buscaPorSimbolo(&*Lista,aux->simb,frase,&j);
			aux = raiz;
		}
		if(codigo[i] == '0')
			aux = aux->esq;
		else if(codigo[i] == '1')
			aux = aux->dir;

		i++;
	}
}

int main()
{
	system("MODE con cols=200 lines=90");
	system("title arvore de huffman");
	system("cls");
	
    char frase[900], codigo[901];
    FILE *arqBin = NULL;
    FILE *arqTxt = NULL;

    ListaA *ListaArv;
    ListaR *ListaReg;

    initListaA(&ListaArv);
    initListaR(&ListaReg);

    // pegar o codigo do arquivo txt
     
    LerCodigo(codigo, arqTxt);
    printf("codigo: %s\n", codigo);

    //gerar lista de registro e exibir
    gerarListaReg(&ListaReg,arqBin);
	gerarListaArv(ListaReg,&ListaArv);
    exibeListaR(ListaReg);

    //gerar arvore e exibir
	gerarArvore(&ListaArv);
	exibe(ListaArv->no,0);

    //gerar frase e exibir
	gerarFrase(&ListaReg,ListaArv->no,codigo,frase);
	printf("\n%s",frase);
    return 0;
}

