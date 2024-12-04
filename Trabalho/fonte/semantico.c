#include "semantico.h"

extern int linha;

// Descrição: Atribui o valor de item2 para item1 conforme o tipo de item1.
// Entrada: Dois ponteiros para estruturas do tipo Item, item1 e item2.
// Retorno: Nenhum.
// Pré-Condição: item1 e item2 não devem ser NULL e devem ter um tipo válido.
// Pós-Condição: O valor de item1 é alocado e atribuído com base no valor de item2.
void atribuiValorId(Item *item1, Item *item2) {
    // Verifica o tipo de item1 para realizar a atribuição correspondente
    switch (item1->tipo) {
        case 0:
            // Caso o tipo seja 0, exibe um erro e finaliza a execução
            printf("Error: '%s' nao declarada na linha %d\n", item1->nome, linha);
            exit(EXIT_FAILURE);
        break;
        case 1:
            // Caso o tipo seja char, aloca memória e copia o valor de item2 para item1
            item1->valor = malloc(sizeof(char));
            *(char*)item1->valor = *(char*)item2->valor;
        break;
        case 2:
            // Caso o tipo seja int, aloca memória e copia o valor de item2 para item1
            item1->valor = malloc(sizeof(int));
            *(int*)item1->valor = *(int*)item2->valor;
        break;
        case 3:
            // Caso o tipo seja float, aloca memória e copia o valor de item2 para item1
            item1->valor = malloc(sizeof(float));
            *(float*)item1->valor = *(float*)item2->valor;
        break;
        case 4:
            // Caso o tipo seja double, aloca memória e copia o valor de item2 para item1
            item1->valor = malloc(sizeof(double));
            *(double*)item1->valor = *(double*)item2->valor;
        break;
    }
}

// Descrição: Atribui um valor a item1 conforme seu tipo, convertendo o valor da string 'valor'.
// Entrada: Um ponteiro para a estrutura do tipo Item, item1, e uma string 'valor'.
// Retorno: Nenhum.
// Pré-Condição: item1 não deve ser NULL e deve ter um tipo válido; 'valor' deve ser uma string válida que pode ser convertida para o tipo de item1.
// Pós-Condição: O valor de item1 é alocado e atribuído com base no valor convertido da string 'valor'.
void atribuiSomaId(Item *item1, char *valor) {
    // Verifica o tipo de item1 para realizar a atribuição correspondente
    switch (item1->tipo) {
        case 0:
            // Caso o tipo seja 0, exibe um erro e finaliza a execução
            printf("Error: '%s' nao declarada na linha %d\n", item1->nome, linha);
            exit(EXIT_FAILURE);
        break;
        case 1:
            // Caso o tipo seja char, aloca memória e atribui o valor da string 'valor' a item1
            item1->valor = malloc(sizeof(char));
            *(char*)item1->valor = *valor;
        break;
        case 2:
            // Caso o tipo seja int, aloca memória e converte a string 'valor' para int, atribuindo a item1
            item1->valor = malloc(sizeof(int));
            *(int*)item1->valor = atoi(valor);
        break;
        case 3:
            // Caso o tipo seja float, aloca memória e converte a string 'valor' para float, atribuindo a item1
            item1->valor = malloc(sizeof(float));
            *(float*)item1->valor = atof(valor);
        break;
        case 4:
            // Caso o tipo seja double, aloca memória e converte a string 'valor' para double, atribuindo a item1
            item1->valor = malloc(sizeof(double));
            *(double*)item1->valor = atof(valor);
        break;
    }
}

// Descrição: Atribui um valor a um item na tabela hash com base no identificador e no sinal de operação fornecidos.
// Entrada: Ponteiro para a estrutura Hash h, strings id1 e id2 que representam os identificadores dos itens, e string sinal que representa a operação de atribuição.
// Retorno: Nenhum.
// Pré-Condição: Os itens referenciados por id1 e id2 devem existir na tabela hash h.
// Pós-Condição: O valor do item referenciado por id1 é atualizado com base no valor do item referenciado por id2 ou pelo valor da string id2.
void setValorId(Hash *h, char *id1, char *sinal, char* id2) {
    // Calcula a chave hash para id1 e busca o item correspondente na tabela hash
    int key1 = hashing(h, id1);
    Item *item1 = busca(h->vet[key1], id1);

    // Calcula a chave hash para id2 e busca o item correspondente na tabela hash
    int key2 = hashing(h, id2);
    Item *item2 = busca(h->vet[key2], id2);

    // Verifica se item2 não é nulo (existe na tabela hash)
    if (item2 != NULL) {
        // Verifica se os tipos dos itens são iguais
        if (item1->tipo == item2->tipo) {
            // Se o sinal é de atribuição '=', chama a função para atribuir o valor de item2 a item1
            if (strcmp(sinal, "=") == 0) {
                atribuiValorId(item1, item2);
            }
        } else {
            // Se os tipos são diferentes, exibe uma mensagem de erro e finaliza a execução
            printf("Error: tipo de '%s' incompativel com '%s' na linha %d\n", item1->nome, item2->nome, linha);
            exit(EXIT_FAILURE);
        }
    } else {
        // Se item2 não existe na tabela hash e o sinal é de atribuição '=', chama a função para atribuir o valor da string id2 a item1
        if (strcmp(sinal, "=") == 0) {
            atribuiSomaId(item1, id2);
        }
    }
}

// Descrição: Incrementa ou decrementa o valor de um item na tabela hash com base no identificador e no sinal de operação fornecidos.
// Entrada: Ponteiro para a estrutura Hash h, string id que representa o identificador do item, e string sinal que representa a operação de incremento ou decremento.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e seu valor deve ser um inteiro.
// Pós-Condição: O valor do item referenciado por id é incrementado ou decrementado em 1, dependendo do sinal fornecido.
void incDec(Hash* h, char *id, char *sinal){
    // Calcula a chave hash para id e busca o item correspondente na tabela hash
    int key = hashing(h, id);
    Item *item = busca(h->vet[key], id);
    
    // Verifica se o sinal é de incremento '++'
    if(strcmp(sinal, "++") == 0){
        // Incrementa o valor do item em 1
        *(int*)item->valor += 1;
    } else if(strcmp(sinal, "--") == 0){
        // Verifica se o sinal é de decremento '--'
        // Decrementa o valor do item em 1
        *(int*)item->valor -= 1;
    }
}

// Descrição: Define o tipo de um item na tabela hash baseado no identificador fornecido.
// Entrada: Ponteiro para a estrutura Hash h, inteiro tipo que representa o novo tipo do item, e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h.
// Pós-Condição: Se o tipo do item for 0, ele é atualizado para o novo tipo fornecido. Se o tipo não for 0, é exibida uma mensagem de erro e o programa é encerrado.
void setTipoId(Hash *h, int tipo, char *id){
    // Calcula a chave hash para id e busca o item correspondente na tabela hash
    int key = hashing(h, id);
    Item *item = busca(h->vet[key], id);
    
    // Verifica se o item existe
    if(item != NULL){
        // Verifica se o tipo atual do item é 0
        if (item->tipo == 0){
            // Atualiza o tipo do item
            item->tipo = tipo;
        }else{
            // Exibe uma mensagem de erro e encerra o programa se os tipos forem conflitantes
            printf("Error: tipos conflitantes para '%s' na linha %d\n", id, linha);
            exit(EXIT_FAILURE);
        }
    }
}

// Descrição: Define a categoria de um item na tabela hash baseado no identificador fornecido.
// Entrada: Ponteiro para a estrutura Hash h, inteiro categoria que representa a nova categoria do item, e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h.
// Pós-Condição: A categoria do item referenciado por id é atualizada para o novo valor fornecido.
void setCategoriaId(Hash *h, int categoria, char *id){
    // Calcula a chave hash para id e busca o item correspondente na tabela hash
    int key = hashing(h, id);
    Item *item = busca(h->vet[key], id);
    // Atualiza a categoria do item
    item->categoria = categoria;
}

// Descrição: Inicializa o valor de um item na tabela hash para zero, baseado no tipo do item.
// Entrada: Ponteiro para a estrutura Hash h e string id que representa o identificador do item.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e ter um tipo válido.
// Pós-Condição: O valor do item referenciado por id é inicializado para zero se for do tipo inteiro ou double.
void inicializaId(Hash *h, char* id){
    // Calcula a chave hash para id e busca o item correspondente na tabela hash
    int key = hashing(h, id);
    Item *item = busca(h->vet[key], id);

    // Inicializa o valor do item baseado no seu tipo
    switch (item->tipo){
        case 2:
            // Aloca memória para um inteiro e inicializa com zero
            item->valor = malloc(sizeof(int));
            *(int*)item->valor = 0;
        break;
        case 4:
            // Aloca memória para um double e inicializa com zero
            item->valor = malloc(sizeof(double));
            *(double*)item->valor = 0.0;
        break;
    }
}

// Descrição: Inicializa o valor de um item na tabela hash para um número convertido a partir de uma string, baseado no tipo do item.
// Entrada: Ponteiro para a estrutura Hash h e string id que representa o identificador do item e o valor a ser inicializado.
// Retorno: Nenhum.
// Pré-Condição: O item referenciado por id deve existir na tabela hash h e ter um tipo válido.
// Pós-Condição: O valor do item referenciado por id é inicializado com o valor numérico convertido da string id, se for do tipo inteiro ou double.
void inicializaNum(Hash *h, char* id){
    // Calcula a chave hash para id e busca o item correspondente na tabela hash
    int key = hashing(h, id);
    Item *item = busca(h->vet[key], id);

    // Inicializa o valor do item baseado no seu tipo
    switch (item->tipo){
        case 2:
            // Aloca memória para um inteiro e inicializa com o valor convertido da string id
            item->valor = malloc(sizeof(int));
            *(int*)item->valor = atoi(id);
        break;
        case 4:
            // Aloca memória para um double e inicializa com o valor convertido da string id
            item->valor = malloc(sizeof(double));
            *(double*)item->valor = atof(id);
        break;
    }
}

// Descrição: Realiza a soma ou subtração entre dois valores, identificados pelos identificadores id1 e id2, na tabela hash h, com base no sinal fornecido (sinal), e armazena o resultado em str.
// Entrada: Ponteiro para a estrutura Hash h, strings id1, id2 e sinal que representam os identificadores e o sinal da operação, respectivamente, e string str para armazenar o resultado.
// Retorno: String str contendo o resultado da operação.
// Pré-Condição: Os identificadores id1 e id2 devem existir na tabela hash h. O sinal deve ser '+' para soma e '-' para subtração.
// Pós-Condição: O resultado da operação é armazenado em str.
char *soma(Hash *h, char *id1, char *sinal, char *id2, char *str){
    // Calcula a chave hash para id1 e busca o item correspondente na tabela hash
    int key1 = hashing(h, id1);
    Item *item1 = busca(h->vet[key1], id1);

    // Calcula a chave hash para id2 e busca o item correspondente na tabela hash
    int key2 = hashing(h, id2);
    Item *item2 = busca(h->vet[key2], id2);

    int i; double d; 
    // Verifica se id2 não existe na tabela hash
    if(item2 == NULL){
        switch (item1->tipo){
            case 2:
                // Realiza a soma ou subtração com base no sinal e armazena o resultado em i
                if(*sinal == '+'){
                    i = *(int*)item1->valor + atoi(id2);
                }else if(*sinal == '-'){
                    i = *(int*)item1->valor - atoi(id2);
                }
                // Converte o resultado para string e armazena em str
                sprintf(str, "%d", i);
            break;
            case 4:
                // Realiza a soma ou subtração com base no sinal e armazena o resultado em d
                if(*sinal == '+'){
                    d = *(double*)item1->valor + atof(id2);
                }else if(*sinal == '-'){
                    d = *(double*)item1->valor - atof(id2);
                }
                // Converte o resultado para string e armazena em str
                sprintf(str, "%lf", d);
            break;
        }

    }else if(item1->tipo == item2->tipo){
        // Realiza a soma ou subtração com base no sinal e armazena o resultado em i ou d, dependendo do tipo
        switch (item1->tipo){
            case 2:
                if(*sinal == '+'){
                    i = *(int*)item1->valor + *(int*)item2->valor;
                }else if(*sinal == '-'){
                    i = *(int*)item1->valor - *(int*)item2->valor;
                }
                // Converte o resultado para string e armazena em str
                sprintf(str, "%d", i);
            break;
            case 4:
                if(*sinal == '+'){
                    d = *(double*)item1->valor + *(double*)item2->valor;
                }else if(*sinal == '-'){
                    d = *(double*)item1->valor - *(double*)item2->valor;
                }
                // Converte o resultado para string e armazena em str
                sprintf(str, "%lf", d);
            break;
        }
    }else if(item2->tipo == 0){
        // Exibe uma mensagem de erro e encerra o programa se id2 não estiver declarado
        printf("Error: '%s' nao declarada na linha %d\n", item2->nome, linha);
        exit(EXIT_FAILURE);
    }
    return str;
}

// Descrição: Realiza a multiplicação ou divisão entre dois valores, identificados pelos identificadores id1 e id2, na tabela hash h, com base no sinal fornecido (sinal), e armazena o resultado em str.
// Entrada: Ponteiro para a estrutura Hash h, strings id1, id2 e sinal que representam os identificadores e o sinal da operação, respectivamente, e string str para armazenar o resultado.
// Retorno: String str contendo o resultado da operação.
// Pré-Condição: Os identificadores id1 e id2 devem existir na tabela hash h. O sinal deve ser '*' para multiplicação e '/' para divisão.
// Pós-Condição: O resultado da operação é armazenado em str.
char *mult(Hash *h, char *id1, char *sinal, char *id2, char *str){
    // Calcula a chave hash para id1 e busca o item correspondente na tabela hash
    int key1 = hashing(h, id1);
    Item *item1 = busca(h->vet[key1], id1);

    // Calcula a chave hash para id2 e busca o item correspondente na tabela hash
    int key2 = hashing(h, id2);
    Item *item2 = busca(h->vet[key2], id2);

    int i; double d; 
    // Verifica se id2 não existe na tabela hash
    if(item2 == NULL){
        switch (item1->tipo){
            case 2:
                // Realiza a multiplicação ou divisão com base no sinal e armazena o resultado em i
                if(*sinal == '*'){
                    i = *(int*)item1->valor * atoi(id2);
                }else if(*sinal == '/'){
                    // Verifica se o divisor é diferente de zero antes de realizar a divisão
                    if(*id2 != '0'){
                        i = *(int*)item1->valor / atoi(id2);
                    }else{
                        printf("Error: divisao por 0(zero) na linha %d\n", linha);
                        exit(EXIT_FAILURE);
                    } 
                }
                sprintf(str, "%d", i); // Converte o resultado para string e armazena em str
            break;
            case 4:
                // Realiza a multiplicação ou divisão com base no sinal e armazena o resultado em d
                if(*sinal == '*'){
                    d = *(double*)item1->valor * atof(id2);
                }else if(*sinal == '/'){
                    // Verifica se o divisor é diferente de zero antes de realizar a divisão
                    if(atof(id2) != 0){
                        d = *(double*)item1->valor / atof(id2);
                    }else{
                        printf("Error: divisao por 0(zero) na linha %d\n", linha);
                        exit(EXIT_FAILURE);
                    }
                }
                // Converte o resultado para string e armazena em str
                sprintf(str, "%lf", d);
            break;
        }

    }else if(item1->tipo == item2->tipo){
        // Realiza a multiplicação ou divisão com base no sinal e armazena o resultado em i ou d, dependendo do tipo
        switch (item1->tipo){
            case 2:
                if(*sinal == '*'){
                    i = *(int*)item1->valor * *(int*)item2->valor;
                }else if(*sinal == '/'){
                    // Verifica se o divisor é diferente de zero antes de realizar a divisão
                    if(*(int*)item2->valor != 0){
                        i = *(int*)item1->valor / *(int*)item2->valor;
                    }else{
                        printf("Error: divisao por 0(zero) na linha %d\n", linha);
                        exit(EXIT_FAILURE);
                    }
                }
                sprintf(str, "%d", i); // Converte o resultado para string e armazena em str
            break;
            case 4:
                if(*sinal == '*'){
                    d = *(double*)item1->valor * *(double*)item2->valor;
                }else if(*sinal == '/'){
                    // Verifica se o divisor é diferente de zero antes de realizar a divisão
                    if(*(double*)item2->valor != 0){
                        d = *(double*)item1->valor / *(double*)item2->valor;
                    }else{
                        printf("Error: divisao por 0(zero) na linha %d\n", linha);
                        exit(EXIT_FAILURE);
                    }
                }
                sprintf(str, "%lf", d); // Converte o resultado para string e armazena em str
            break;
        }
    }
    return str;
}

// Descrição: Realiza uma comparação entre dois itens da hash e retorna "1" se a condição for verdadeira e "0" caso contrário.
// Entrada: Ponteiro para a estrutura Hash h, string id1 (identificador do primeiro item), string sinal (operador de comparação), string id2 (identificador do segundo item).
// Retorno: "1" se a condição for verdadeira, "0" caso contrário.
// Pré-Condição: A estrutura Hash h deve estar inicializada e conter os itens identificados por id1 e id2.
// Pós-Condição: Nenhuma alteração é feita na estrutura Hash h.
char *comparacao(Hash *h, char *id1, char *sinal, char *id2){
    int key1 = hashing(h, id1);
    Item *item1 = busca(h->vet[key1], id1);

    int key2 = hashing(h, id2);
    Item *item2 = busca(h->vet[key2], id2);

    if(item2 != NULL){
        if(item1->tipo == item2->tipo){
            switch (item1->tipo){
                case 2:
                    if(strcmp(sinal, "<") == 0){
                        return (*(int*)item1->valor < *(int*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "==") == 0){
                        return (*(int*)item1->valor == *(int*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, ">") == 0){
                        return (*(int*)item1->valor > *(int*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "<=") == 0){
                        return (*(int*)item1->valor <= *(int*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, ">=") == 0){
                        return (*(int*)item1->valor >= *(int*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "!=") == 0){
                        return (*(int*)item1->valor != *(int*)item2->valor) ?  "1" : "0";
                    }
                break;
                case 4:
                    if(strcmp(sinal, "<") == 0){
                        return (*(double*)item1->valor < *(double*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "==") == 0){
                        return (*(double*)item1->valor == *(double*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, ">") == 0){
                        return (*(double*)item1->valor > *(double*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "<=") == 0){
                        return (*(double*)item1->valor <= *(double*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, ">=") == 0){
                        return (*(double*)item1->valor >= *(double*)item2->valor) ?  "1" : "0";
                    }
                    if(strcmp(sinal, "!=") == 0){
                        return (*(double*)item1->valor != *(double*)item2->valor) ?  "1" : "0";
                    }
                break;
            }
        }
    }
    // Caso nenhum dos casos anteriores seja satisfeito, retorna "0"
    return "0";
}

// Descrição: Realiza operações lógicas entre dois itens da hash e retorna "1" se a condição for verdadeira e "0" caso contrário.
// Entrada: Ponteiro para a estrutura Hash h, string id1 (identificador do primeiro item), string sinal (operador lógico), string id2 (identificador do segundo item).
// Retorno: "1" se a condição for verdadeira, "0" caso contrário.
// Pré-Condição: A estrutura Hash h deve estar inicializada e conter os itens identificados por id1 e id2.
// Pós-Condição: Nenhuma alteração é feita na estrutura Hash h.
char *logica(Hash *h, char *id1, char *sinal, char *id2){
    int key1 = hashing(h, id1);
    Item *item1 = busca(h->vet[key1], id1);

    int key2 = hashing(h, id2);
    Item *item2 = busca(h->vet[key2], id2);

    if(item2 != NULL){
        if(item1->tipo == item2->tipo){
            switch (item1->tipo){
                case 2:
                    if(strcmp(sinal, "&&") == 0){
                        return (*(int*)item1->valor && *(int*)item2->valor) ? "1" : "0";
                    }
                    if(strcmp(sinal, "||") == 0){
                        return (*(int*)item1->valor || *(int*)item2->valor) ? "1" : "0";
                    }
                    if(strcmp(sinal, ">>") == 0){
                        return (*(int*)item1->valor >> *(int*)item2->valor) ? "1" : "0";
                    }
                    if(strcmp(sinal, "<<") == 0){
                        return (*(int*)item1->valor << *(int*)item2->valor) ? "1" : "0";
                    }
                break;
                case 4:
                    if(strcmp(sinal, "&&") == 0){
                        return (*(double*)item1->valor && *(double*)item2->valor) ? "1" : "0";
                    }
                    if(strcmp(sinal, "||") == 0){
                        return (*(double*)item1->valor || *(double*)item2->valor) ? "1" : "0";
                    }
                break;
            }
        }
    }
    // Se nenhum dos casos anteriores for satisfeito, retorna "0"
    return "0";
}