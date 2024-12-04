#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

typedef struct arvore{
    char *token;
    int numFilhos;
    struct arvore **filhos;
    int nivel;
}Arv;

typedef struct pilha{
    Arv *token;
    struct pilha *prox;
}Pilha;

// Descrição: Insere um novo elemento no topo da pilha.
// Entrada: ponteiro para a pilhae ponteiro para a árvore a ser inserida na pilha
// Retorno: ponteiro para a nova pilha
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o elemento a é inserido no topo da pilha
Pilha *push(Pilha* p, Arv *a);

// Descrição: Remove o elemento do topo da pilha.
// Entrada: ponteiro para a pilha
// Retorno: ponteiro para a nova pilha
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o elemento do topo da pilha é removido
Pilha *pop(Pilha* p);

// Descrição: Cria um novo nó para a árvore.
// Entrada: token do nó e o número de filhos do nó
// Retorno: ponteiro para o novo nó
// Pré-Condição: nenhum
// Pós-Condição: um novo nó é criado com o token e número de filhos especificados
Arv *criaNo(char *token, int numFilhos);

// Descrição: Insere um nó na pilha.
// Entrada: ponteiro para a pilha, token do nó a ser inserido e o número de filhos do nó
// Retorno: ponteiro para a nova pilha
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o nó é inserido na pilha
Pilha *insere(Pilha *p, char *token, int numFilhos);

// Descrição: Insere um número inteiro na pilha.
// Entrada: ponteiro para a pilha, número inteiro a ser inserido e o número de filhos do nó
// Retorno: ponteiro para a nova pilha
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o número inteiro é inserido na pilha
Pilha *insereInt(Pilha *p, int n, int numFilhos);

// Descrição: Insere um número real na pilha.
// Entrada: ponteiro para a pilha, número real a ser inserido e o número de filhos do nó
// Retorno: ponteiro para a nova pilha
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: o número real é inserido na pilha
Pilha *insereDouble(Pilha *p, double n, int numFilhos);

// Descrição: Imprime os elementos da pilha.
// Entrada: ponteiro para a pilha
//Retorno: nenhum
// Pré-Condição: p deve ser uma pilha válida
// Pós-Condição: os elementos da pilha são impressos na tela
void imprimirPilha(Pilha *p);

// Descrição: Imprime os nós da árvore por nível em um arquivo.
// Entrada: nome do arquivo de saída e ponteiro para a árvore
//Retorno: nenhum
// Pré-Condição: a deve ser uma árvore válida
// Pós-Condição: os nós da árvore são impressos por nível no arquivo
void imprimirPorNivel(char* nome_arq, Arv *a);

#endif