#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char nome[100];
    char token [100];
    int tipo;       // 0 = eh um token, 1 = char, 2 = int, 3 = float, 4 = double, 5 = void;
    int categoria;  // 0 = eh um token, 1 = variavel, 2 = procedimento, 3 = numero;
    void *valor;    // null = eh um token, ponteiro generico para valor (pode ser qualquer um dos tipos acima)
    int linha;
    struct no *prox;
}Item;

typedef struct tokens{
    int tam;
    Item **vet;
}Hash;

#include "hash.h"

// Menu
// Entrada: Nenhuma
// Retorno: Nenhuma
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
void menu();

// Função para verificar se a lista é vazia
// Entrada: Lista
// Retorno: 1 se a lista é vaiza, 0 caso contrário
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int vazia(Item *item);

// Descrição: Calcula o valor hash de uma string.
// Entrada: h - ponteiro para a tabela hash, nome - string para calcular o hash
// Retorno: valor hash calculado
// Pré-Condição: h deve ser um ponteiro válido, nome deve ser uma string válida
// Pós-Condição: retorna o valor hash calculado
int hashing(Hash *h, char *nome);

// Descrição: Cria uma nova tabela hash.
// Entrada: tam - tamanho da tabela hash
// Retorno: ponteiro para a nova tabela hash
// Pré-Condição: tam deve ser um valor válido
// Pós-Condição: retorna a nova tabela hash criada
Hash *criarHash(int tam);

// Descrição: Insere um novo item na tabela hash.
// Entrada: Ponteiro para o primeiro item da lista (Item *item), nome do novo item (char *nome), 
//          token do novo item (char *token), valor do novo item (void* valor), tipo do novo item (int tipo), 
//          categoria do novo item (int categoria).
// Retorno: Nenhum.
// Pré-Condição: A tabela hash 'h' deve ter sido corretamente inicializada.
// Pós-Condição: O item é inserido na tabela hash 'h'.
void inserirHash(Hash *h, char *nome, char *token, void* valor, int tipo, int categoria);

// Descrição: Insere um novo item na lista encadeada, se o nome ainda não existir nela.
// Entrada: Ponteiro para o primeiro item da lista (Item *item), nome do novo item (char *nome), 
//          token do novo item (char *token), valor do novo item (void* valor), tipo do novo item (int tipo), 
//          categoria do novo item (int categoria).
// Retorno: Ponteiro para o primeiro item da lista, podendo ser o item original ou o novo item inserido.
// Pré-Condição: A lista deve estar corretamente inicializada e o ponteiro item deve apontar para o início da lista.
// Pós-Condição: O item é inserido na lista se o nome ainda não existir nela; caso contrário, a lista permanece inalterada.
Item *inserir(Item *item, char *nome, char *token, void* valor, int tipo, int categoria);

// Descrição: Imprime os itens da lista encadeada.
// Entrada: item - ponteiro para o item da lista
// Retorno: nenhum
// Pré-Condição: item deve ser um ponteiro válido
// Pós-Condição: imprime os itens da lista encadeada
void imprimir(Item *item);

// Descrição: Imprime os itens da tabela hash.
// Entrada: ponteiro para a tabela hash
// Retorno: nenhum
// Pré-Condição: h deve ser um ponteiro válido
// Pós-Condição: imprime os itens da tabela hash
void imprimirHash(Hash *h);

// Descrição: Busca um item na lista encadeada.
// Entrada: ponteiro para o item da lista, string a ser buscada
// Retorno: ponteiro para o item encontrado ou NULL se não encontrado
// Pré-Condição: item deve ser um ponteiro válido, str deve ser uma string válida
// Pós-Condição: retorna o item encontrado ou NULL se não encontrado
Item *busca (Item *item, char* str);

// Descrição: Verifica se uma string contém caracteres inválidos.
// Entrada: string a ser verificada, número da linha onde ocorreu a verificação
// Retorno: 0 se não há erro, a posição do primeiro caractere inválido caso contrário
// Pré-Condição: str deve ser uma string válida, linha deve ser um número válido
// Pós-Condição: retorna a posição do primeiro caractere inválido ou 0 se não há erro
int verificaErro(char* str, int linha);

// Descrição: Libera a memória ocupada pela lista encadeada.
// Entrada: item - ponteiro para o item da lista
// Retorno: NULL
// Pré-Condição: item deve ser um ponteiro válido
// Pós-Condição: libera a memória ocupada pela lista encadeada
Item *limpa(Item *item);

// Descrição: Libera a memória ocupada pela tabela hash.
// Entrada: h - ponteiro para a tabela hash
// Retorno: NULL
// Pré-Condição: h deve ser um ponteiro válido
// Pós-Condição: libera a memória ocupada pela tabela hash
Hash *limpaHash(Hash *h);

#endif