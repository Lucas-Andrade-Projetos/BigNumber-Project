#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

//Função para criar um nó
BigNumber* criarNo(int digito) {
     BigNumber* novoNo = (BigNumber*)malloc(sizeof(BigNumber));
    if (!novoNo) {
        printf("Erro ao alocar memória!\n");
        return NULL; 
    }
    novoNo->digito = digito;
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

//Função para inicializar um BigNumberStruct
BigNumberStruct* criarBigNumber() {
    BigNumberStruct* numero = (BigNumberStruct*)malloc(sizeof(BigNumberStruct));
    if (!numero) {
        printf("Erro ao alocar memória para BigNumberStruct!\n");
        return NULL; 
    }
    numero->sinal = 1; 
    numero->head = NULL;
    return numero;
}

//Função para adicionar nó no final da lista
void adicionarNoFim(BigNumberStruct* numero, int digito) {
    BigNumber* novoNo = criarNo(digito);
    if (numero->head == NULL) {
        numero->head = novoNo;
    } else {
        BigNumber* temp = numero->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNo;
        novoNo->prev = temp;
    }
}

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumberStruct* numero, int digito) {
    BigNumber* novoNo = criarNo(digito);
    if (numero->head == NULL) {
        numero->head = novoNo;
    } else {
        novoNo->next = numero->head;
        numero->head->prev = novoNo;
        numero->head = novoNo;
    }
}

//Função para adicionar antes de um valor
void adicionarAntes(BigNumberStruct* numero, int valor, int novoDigito) {
    BigNumber* temp = numero->head;
    while (temp != NULL && temp->digito != valor) {
        temp = temp->next;
    }
    if (temp != NULL) {
        BigNumber* novo = criarNo(novoDigito);
        novo->prev = temp->prev;
        novo->next = temp;
        if (temp->prev != NULL) {
            temp->prev->next = novo;
        } else {
            numero->head = novo;
        }
        temp->prev = novo;
    }
}

//Função para adicionar depois de um valor
void adicionarDepois(BigNumberStruct* numero, int valorDepois, int digito) {
    BigNumber* temp = numero->head;
    while (temp != NULL && temp->digito != valorDepois) {
        temp = temp->next;
    }
    if (temp != NULL) {
        BigNumber* novo = criarNo(digito);
        novo->next = temp->next;
        novo->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = novo;
        }
        temp->next = novo;
    }
}

//Função para ler um número com sinal
void lerNumeroComSinal(BigNumberStruct* numero) {
    char c;
    while (scanf("%c", &c) && c != '\n') {
        if (c == '+') {
            numero->sinal = 1; 
            continue;
        } else if (c == '-') {
            numero->sinal = -1;  
            continue;
        }
        
        if (c >= '0' && c <= '9') {
            adicionarNoFim(numero, c - '0');  
        }
    }
}

//Função para remover um nó com o número especificado
void removerNumero(BigNumberStruct* numero, int valor) {
    BigNumber* temp = numero->head;
    while (temp != NULL && temp->digito != valor) {
        temp = temp->next;
    }

    if (temp != NULL) {
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            numero->head = temp->next; 
        }

        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }

        free(temp);  
    }
}
//Função para encontrar um número específico
BigNumber* encontrarNumero(BigNumberStruct* numero, int valor) {
    BigNumber* temp = numero->head;
    while (temp != NULL && temp->digito != valor) {
        temp = temp->next;
    }
    return temp;
}

//Função para contar o número de elementos na lista
int contarElementos(BigNumberStruct* numero) {
    int contador = 0;
    BigNumber* temp = numero->head;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}

//Função para imprimir o BigNumber
void imprimirNumero(BigNumberStruct* numero) {
    if (numero == NULL || numero->head == NULL) {
        printf("Número inválido ou vazio\n");
        return;
    }

    if (numero->sinal == -1) {
        printf("-");
    }

    BigNumber* temp = numero->head;
    while (temp != NULL) {
        printf("%d", temp->digito);
        temp = temp->next;
    }
    printf("\n");
}


//Função para liberar a memória do BigNumber
void liberaMemoria(BigNumberStruct* numero) {
    BigNumber* temp = numero->head;
    while (temp != NULL) {
        BigNumber* proximo = temp->next;
        free(temp);
        temp = proximo;
    }
    free(numero);
}
