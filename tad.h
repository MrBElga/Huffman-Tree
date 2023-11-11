struct tree
{
    int freq, simb;
    struct tree *dir, *esq;
};
typedef struct tree Tree;

struct listaA
{
    struct tree *no;
    struct listaA *prox;
};
typedef struct listaA ListaA;

struct ListaR
{
    struct ListaR *prox;
    int freq, simb;
    char codHuff[50], palavra[50];
};
typedef struct ListaR ListaR;

// funcoes  para arvore
void initListaA(ListaA **Lista)
{
    *Lista = NULL;
}

Tree *CriaNo(int simbolo, int frequencia)
{
    Tree *no = (Tree *)malloc(sizeof(Tree));
    no->dir = no->esq = NULL;
    no->simb = simbolo;
    no->freq = frequencia;
    return no;
}

void inserirListaA(ListaA **Lista, int simbolo, int frequencia)
{
    ListaA *ant, *aux, *novo;
    novo = (ListaA *)malloc(sizeof(ListaA));
    novo->no = NULL;
    novo->prox = NULL;
    if ((*Lista) == NULL)
        *Lista = novo;
    else
    {
        ant = aux = *Lista;
        while (aux != NULL && aux->no->freq <= frequencia)
        {
            ant = aux;
            aux = aux->prox;
        }
        if (aux == NULL)
            ant->prox = novo;
        else
        {
            if (aux == ant)
            {
                novo->prox = aux;
                *Lista = novo;
            }
            else
            {
                novo->prox = aux;
                ant->prox = novo;
            }
        }
    }
    novo->no = CriaNo(simbolo, frequencia);
}

void inserirA(ListaA **ListaArv, ListaA **auxP, ListaA **antP, int simbolo, int frequencia)
{
    ListaA *ant, *aux, *novo;
    novo = (ListaA *)malloc(sizeof(ListaA));
    novo->no = NULL;
    novo->prox = NULL;
    if ((*ListaArv) == NULL)
        *ListaArv = novo;
    else
    {
        ant = aux = *ListaArv;
        while (aux != NULL && aux->no->freq <= frequencia)
        {
            ant = aux;
            aux = aux->prox;
        }
        if (aux == NULL)
            ant->prox = novo;
        else
        {
            if (aux == ant)
            {
                novo->prox = aux;
                *ListaArv = novo;
            }
            else
            {
                novo->prox = aux;
                ant->prox = novo;
            }
        }
    }
    novo->no = CriaNo(simbolo, frequencia);
    novo->no->esq = (*antP)->no;
    novo->no->dir = (*auxP)->no;
}

void excluir(ListaA **Lista, int simbolo)
{
    ListaA *aux, *ant;
    ant = aux = *Lista;
    while (aux != NULL && aux->no->simb != simbolo)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL)
        printf("Simbolo nao encontrado");
    else
    {
        if (aux == ant)
            *Lista = aux->prox;
        else
            ant->prox = aux->prox;
        free(aux);
    }
}

// funcoes lista de registros
void initListaR(ListaR **Lista)
{
    *Lista = NULL;
}

void buscaPorSimbolo(ListaR **Lista, int simb, char frase[], int *j)
{
    char palv[50];
    int i = 0;
    ListaR *aux;
    aux = *Lista;
    while (aux != NULL && aux->simb != simb)
        aux = aux->prox;
    if (aux != NULL)
    {
        while (aux->palavra[i] != '\0')
        {
            strcpy(palv, aux->palavra);
            frase[*j] = palv[i];
            i++;
            (*j)++;
        }
    }
    frase[*j] = '\0';
}

ListaR *buscaPorpalavra(ListaR **Lista, char palavra[])
{
    ListaR *aux = *Lista;
    int i;
    char palavraAux[50], palavraLista[50];
    while (aux != NULL)
    {

        strcpy(palavraAux, palavra);
        strcpy(palavraLista, aux->palavra);
        for (i = 0; palavraAux[i]; i++)
        {
            palavraAux[i] = toupper(palavraAux[i]);
        }

        for (i = 0; palavraLista[i]; i++)
        {
            palavraLista[i] = toupper(palavraLista[i]);
        }

        if (strcmp(palavraAux, palavraLista) == 0)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void insereListaR(ListaR **Lista, int freq, int simb, char palavra[], char codHuff[])
{
    ListaR *aux, *novo = (ListaR *)malloc(sizeof(ListaR));
    novo->prox = NULL;
    strcpy(novo->palavra, palavra);
    novo->freq = freq;
    novo->simb = simb;
    if (codHuff != NULL)
        strcpy(novo->codHuff, codHuff);
    if (*Lista == NULL)
        *Lista = novo;
    else
    {
        aux = *Lista;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

char SomaFreq(ListaR **Lista, char palavra[])
{
    ListaR *aux;
    aux = *Lista;
    while (aux != NULL && strcmp(aux->palavra, palavra) != 0)
        aux = aux->prox;
    if (aux != NULL)
    {
        aux->freq++;
        return 1;
    }
    return 0;
}

// exibe
// arvore
void exibe(Tree *raiz, int nivel)
{
    int i = 0;
    if (raiz != NULL)
    {
        exibe(raiz->dir, nivel + 1);

        for (i = 0; i < nivel; i++)
        {
            printf("         ");
        }

        if (nivel > 0)
        {
            printf("<-- ");
        }

        printf("(%d, %d)\n", raiz->simb, raiz->freq);

        exibe(raiz->esq, nivel + 1);
    }
}

// listas
void exibeListaR(ListaR *Lista)
{
    // system("cls");
    printf("=====================================================================\n");
    printf("| Palavra\t | Frequencia\t  | Simbolo\t   | Codigo\t    |\n");
    printf("=====================================================================\n");

    while (Lista != NULL)
    {
        printf("| %-15s| %-15d| %-15d| %-15s|\n", Lista->palavra, Lista->freq, Lista->simb, Lista->codHuff);
        Lista = Lista->prox;
    }

    printf("=====================================================================\n");
    getch();
}
