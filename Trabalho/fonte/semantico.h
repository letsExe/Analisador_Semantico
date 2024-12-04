#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "arvore.h"
#include "hash.h"

// Descrição: Atribui o valor de item2 para item1 conforme o tipo de item1.
// Entrada: Dois ponteiros para estruturas do tipo Item, item1 e item2.
// Retorno: Nenhum.
// Pré-Condição: item1 e item2 não devem ser NULL e devem ter um tipo válido.
// Pós-Condição: O valor de item1 é alocado e atribuído com base no valor de item2.
void atribuiValorId(Item *item1, Item *item2);

// Descrição: Atribui um valor a item1 conforme seu tipo, convertendo o valor da string 'valor'.
// Entrada: Um ponteiro para a estrutura do tipo Item, item1, e uma string 'valor'.
// Retorno: Nenhum.
// Pré-Condição: item1 não deve ser NULL e deve ter um tipo válido; 'valor' deve ser uma string válida que pode ser convertida para o tipo de item1.
// Pós-Condição: O valor de item1 é alocado e atribuído com base no valor convertido da string 'valor'.
void atribuiSomaId(Item *item1, char *valor);

// Descrição: Atribui um valor a um item na tabela hash com base no identificador e no sinal de operação fornecidos.
// Entrada: Ponteiro para a estrutura Hash h, strings id1 e id2 que representam os identificadores dos itens, e string sinal que representa a operação de atribuição.
// Retorno: Nenhum.
// Pré-Condição: Os itens referenciados por id1 e id2 devem existir na tabela hash h.
// Pós-Condição: O valor do item referenciado por id1 é atualizado com base no valor do item referenciado por id2 ou pelo valor da string id2.
void setValorId(Hash *h, char *id1, char *sinal, char* id2);

// Descrição: Incrementa ou decrementa o valor de um item na tabela hash com base no identificador e no sinal de operação fornecidos.
// Entrada: Ponteiro para a estrutura Hash h, string id que representa o identificador do item, e string sinal que representa a operação de incremento ou decremento.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e seu valor deve ser um inteiro.
// Pós-Condição: O valor do item referenciado por id é incrementado ou decrementado em 1, dependendo do sinal fornecido.
void incDec(Hash* h, char *id, char *sinal);

// Descrição: Define o tipo de um item na tabela hash baseado no identificador fornecido.
// Entrada: Ponteiro para a estrutura Hash h, inteiro tipo que representa o novo tipo do item, e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h.
// Pós-Condição: Se o tipo do item for 0, ele é atualizado para o novo tipo fornecido. Se o tipo não for 0, é exibida uma mensagem de erro e o programa é encerrado.
void setTipoId(Hash *h, int tipo, char *id);

// Descrição: Define a categoria de um item na tabela hash baseado no identificador fornecido.
// Entrada: Ponteiro para a estrutura Hash h, inteiro categoria que representa a nova categoria do item, e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h.
// Pós-Condição: A categoria do item referenciado por id é atualizada para o novo valor fornecido.
void setCategoriaId(Hash *h, int categoria, char *id);

// Descrição: Inicializa o valor de um item na tabela hash para zero, baseado no tipo do item.
// Entrada: Ponteiro para a estrutura Hash h e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e ter um tipo válido.
// Pós-Condição: O valor do item referenciado por id é inicializado para zero se for do tipo inteiro ou double.
void inicializaId(Hash *h, char* id);

// Descrição: Inicializa o valor de um item na tabela hash para um número convertido a partir de uma string, baseado no tipo do item.
// Entrada: Ponteiro para a estrutura Hash h e string id que representa o identificador do item e o valor a ser inicializado.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e ter um tipo válido.
// Pós-Condição: O valor do item referenciado por id é inicializado com o valor numérico convertido da string id, se for do tipo inteiro ou double.
void inicializaNum(Hash *h, char* id);

// Descrição: Realiza a soma ou subtração entre dois valores, identificados pelos identificadores id1 e id2, na tabela hash h, com base no sinal fornecido (sinal), e armazena o resultado em str.
// Entrada: Ponteiro para a estrutura Hash h, strings id1, id2 e sinal que representam os identificadores e o sinal da operação, respectivamente, e string str para armazenar o resultado.
// Retorno: String str contendo o resultado da operação.
// Pré-Condição: Os identificadores id1 e id2 devem existir na tabela hash h. O sinal deve ser '+' para soma e '-' para subtração.
// Pós-Condição: O resultado da operação é armazenado em str.
char *soma(Hash *h, char *id1, char *sinal, char *id2, char *str);
// Descrição: Realiza a multiplicação ou divisão entre dois valores, identificados pelos identificadores id1 e id2, na tabela hash h, com base no sinal fornecido (sinal), e armazena o resultado em str.
// Entrada: Ponteiro para a estrutura Hash h, strings id1, id2 e sinal que representam os identificadores e o sinal da operação, respectivamente, e string str para armazenar o resultado.
// Retorno: String str contendo o resultado da operação.
// Pré-Condição: Os identificadores id1 e id2 devem existir na tabela hash h. O sinal deve ser '*' para multiplicação e '/' para divisão.
// Pós-Condição: O resultado da operação é armazenado em str.
char *mult(Hash *h, char *id1, char *sinal, char *id2, char *str);

// Descrição: Realiza uma comparação entre dois itens da hash e retorna "1" se a condição for verdadeira e "0" caso contrário.
// Entrada: Ponteiro para a estrutura Hash h, string id1 (identificador do primeiro item), string sinal (operador de comparação), string id2 (identificador do segundo item).
// Retorno: "1" se a condição for verdadeira, "0" caso contrário.
// Pré-Condição: A estrutura Hash h deve estar inicializada e conter os itens identificados por id1 e id2.
// Pós-Condição: Nenhuma alteração é feita na estrutura Hash h.
char *comparacao(Hash *h, char *id1, char *sinal, char *id2);

// Descrição: Realiza operações lógicas entre dois itens da hash e retorna "1" se a condição for verdadeira e "0" caso contrário.
// Entrada: Ponteiro para a estrutura Hash h, string id1 (identificador do primeiro item), string sinal (operador lógico), string id2 (identificador do segundo item).
// Retorno: "1" se a condição for verdadeira, "0" caso contrário.
// Pré-Condição: A estrutura Hash h deve estar inicializada e conter os itens identificados por id1 e id2.
// Pós-Condição: Nenhuma alteração é feita na estrutura Hash h.
char *logica(Hash *h, char *id1, char *sinal, char *id2);

#endif
