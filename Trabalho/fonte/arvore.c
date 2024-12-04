#include "arvore.h"

// Descrição: Insere um novo elemento no topo da pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o elemento a é inserido no topo da pilha
Pilha *push(Pilha* p, Arv *a){
    Pilha *no = (Pilha*)malloc(sizeof(Pilha));
    no->token = a;
    no->prox = p;
    return no;
}

// Descrição: Remove o elemento do topo da pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o elemento do topo da pilha é removido
Pilha *pop(Pilha* p){
    Pilha *no = p->prox;
    free(p);
    return no;
}

// Descrição: Cria um novo nó para a árvore.
// Pré-Condição: nenhum
// Pós-Condição: um novo nó é criado com o token e número de filhos especificados
Arv *criaNo(char *token, int numFilhos){
    Arv *no = (Arv*)malloc(sizeof(Arv));
    no->token = strdup(token);
    no->numFilhos = numFilhos;
    if(numFilhos == 0){ no->filhos = NULL; }else{
        no->filhos = (Arv**) malloc(numFilhos*sizeof(Arv*));
    }
    return no;
}

// Descrição: Insere um número inteiro na pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o número inteiro é inserido na pilha
Pilha *insereInt(Pilha *p, int n, int numFilhos){
    char token[100];
    sprintf(token, "%d", n);
    p = insere(p, token, numFilhos);
    return p;
}

// Descrição: Insere um número real na pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o número real é inserido na pilha
Pilha *insereDouble(Pilha *p, double n, int numFilhos){
    char token[100];
    sprintf(token, "%lf", n);
    p = insere(p, token, numFilhos);
    return p;
}

// Descrição: Insere um nó na pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o nó é inserido na pilha
Pilha *insere(Pilha *p, char *token, int numFilhos){
    Arv *no = criaNo(token, numFilhos);
    for(int i = 0; i < numFilhos; i++){
        (no->filhos)[i] = p->token;
        p = pop(p);
    }
    p = push(p, no);
    return p;
}

// Descrição: Imprime os elementos da pilha.
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: os elementos da pilha são impressos na tela
void imprimirPilha(Pilha *p){
    if(p!=NULL){
        printf("%s\n", p->token->token);
        imprimirPilha(p->prox);
    }
}

// Descrição: Insere um nó em uma lista de acordo com o nível.
// Pré-Condição: nenhum
// Pós-Condição: o nó a é inserido na lista de forma ordenada por nível
Pilha *insereLista(Pilha* l, Arv* a){
    if(l==NULL || l->token->nivel>=a->nivel){
        Pilha* aux = (Pilha*) malloc(sizeof(Pilha));
        aux->token = a;
        aux->prox = l;
        return aux;
    }
    l->prox = insereLista(l->prox, a);
    return l;
}

// Descrição: Ordena os nós por nível na lista.
// Pré-Condição: l deve ser uma lista válida, a deve ser um nó válido, nivel deve ser o nível inicial
// Pós-Condição: os nós são ordenados por nível na lista
void ordenaPorNivel(Pilha** l, Arv *a, int nivel){
    a->nivel = nivel;
    *l = insereLista(*l, a);
    for(int i = 0; i < a->numFilhos; i++){
        ordenaPorNivel(l, a->filhos[i], nivel+1);
    }
}

// Descrição: Imprime os nós da árvore por nível em um arquivo.
// Pré-Condição: a deve ser uma árvore válida
// Pós-Condição: os nós da árvore são impressos por nível no arquivo
void imprimirPorNivel(char* nome_arq, Arv* a){
    FILE* arq = fopen(nome_arq, "w");
    if(arq==NULL) return;
    Pilha* l = NULL, *aux;
    int nivel=0;
    ordenaPorNivel(&l, a, 1);
    aux = l;
    while(l!=NULL){
        if(l->token->nivel>nivel){
            if(nivel)fprintf(arq, "\n");
            fprintf(arq, "Nivel %02d-> ", nivel);
            nivel=l->token->nivel;
        }
        aux = l->prox;
        fprintf(arq, "%-10s\t", l->token->token);
        free(l);
        l = aux;
    }
    fclose(arq);
}