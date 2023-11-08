struct tree{
    int freq, simb;
    struct tree *dir, *esq;
};
typedef tree Tree;

struct listaReg
{
    struct listaReg *prox;
    int freq, simb;
    char cod[50], palav[50];
};
typedef struct listaReg ListaReg;

void initLista(ListaReg **L){
    *L == NULL; 
}


void criarListaTree(ListaReg *Lista,  Tree **arvore)
{
    while (Lista != NULL)
    {
        insereLArvore(&*arvore, Lista->simb, Lista->freq);
        Lista = Lista->prox;
    }
}

