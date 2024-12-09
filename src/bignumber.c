#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

//Funcao para criar um no
BigNumber* criarNo(int digito)
{
	BigNumber* novoNo = (BigNumber*)malloc(sizeof(BigNumber));
	if(!novoNo)
	{
		printf("Erro ao alocar memória!\n");
        exit(1);
	}

	novoNo->digito = digito;
	novoNo->next = NULL;
	novoNo->prev = NULL;
	return novoNo;
}

//Funcao para adicionar no no final da fila
void adicionarNoFim(BigNumber **head, int digito) {
    BigNumber* novoNo = criarNo(digito);
    if (*head == NULL) {
        *head = novoNo;
        return;
    }else{
    	BigNumber* temp = *head;
    	while (temp->next != NULL) {
        temp = temp->next;
    	}
		temp->next = novoNo;
		novoNo->prev = temp;//Define o anterior do novo nó
	}
}

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumber** head, int valor) {
    BigNumber* novoNo = criarNo(valor);
	if (*head == NULL) {
        *head = novoNo;
        return;
    }else{
		novoNo->next = *head;
		(*head)->prev = novoNo;//Define o anterior do antigo primeiro nó
    	*head = novoNo;
	}
}

//Funcao para adicionar no antes de um Valor
void adicionarAntes(BigNumber** head, int numero, int novoDigito) {
    BigNumber* temp = *head;
    while (temp != NULL && temp->digito != numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        BigNumber* novo = criarNo(novoDigito);
        novo->prev = temp->prev;
        novo->next = temp;
        if (temp->prev != NULL) {
            temp->prev->next = novo;
        }
        temp->prev = novo;
        if (temp == *head) {
            *head = novo;
        }
    }
}

//Função para adicionar um nó depois de um nó com um valor específico
void adicionarDepois(BigNumber* head, int valorDepois, int digito) {
    BigNumber* temp = head;
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

//Função para ler um número com seu sinal corretamente
BigNumber* lerNumeroComSinal(int* sinal) {
    BigNumber* numero = NULL;
    char c;

    
    *sinal = 1;  
    while (scanf("%c", &c) && c != '\n') {
        if (c == '+') {
            continue;  
        } else if (c == '-') {
            *sinal = -1;  
            continue;  
        }
        
        adicionarNoFim(&numero, c - '0');
    }

    return numero;
}

//Função para remover um nó com o número especificado
void removerNumero(BigNumber** head, int numero) {
    BigNumber* temp = *head;
    while (temp != NULL && temp->digito != numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        if (temp == *head) {
            *head = temp->next;
        }
        free(temp);
    }
}

//Funcao para encontrar número específico
BigNumber* encontrarNumero(BigNumber* head, int numero) {
    BigNumber* temp = head;
    while (temp != NULL && temp->digito != numero) {
        temp = temp->next;
    }
    return temp;  // Retorna NULL se não encontrar
}


//Função para contar o número de elementos na lista
int contarElementos(BigNumber* head) {
    int contador = 0;
    BigNumber* temp = head;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}


//funcao para imprimir a lista encadeada
void imprimirLista(BigNumber *head, int sinal) {
    if (sinal == -1) {
        printf("-");
    }
    BigNumber* temp = head;
    while (temp != NULL) {
        printf("%d", temp->digito);
        temp = temp->next;
    }
    printf("\n");
}

//funcao para liberar a memoria da lista 
void liberaMemoria(BigNumber* head) {
    while (head != NULL) {
        BigNumber* temp = head;
        head = head->next;
        free(temp);
    }
}

