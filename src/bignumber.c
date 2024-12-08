#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

//Funcao para criar um no
BigNumber* criarNo(int digito)
{
	BigNumber* novoNo = (BigNumber*)malloc(sizeof(BigNumber));
	novoNo->digito = digito;
	novoNo->next = NULL;
	return novoNo;
}

//Funcao para adicionar no no final da fila
void adicionarNoFim(BigNumber **head, int digito) {
    BigNumber* novoNo = criarNo(digito);
    if (*head == NULL) {
        *head = novoNo;
        return;
    }
    BigNumber* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = novoNo;
}

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumber** head, int valor) {
    BigNumber* novoNo = criarNo(valor);
    novoNo->next = *head;
    *head = novoNo;
}

//Funcao para adicionar no no inicio da
void adicionarAntes(BigNumber **head, int numero, int novoDigito) {
    BigNumber* novoNo = criarNo(novoDigito);

    //Se a lista está vazia ou o primeiro nó já contém o número
    if (*head == NULL || (*head)->digito == numero) {
        novoNo->next = *head;
        *head = novoNo;
        return;
    }

    //Percorre até encontrar o nó antes do qual queremos adicionar
    BigNumber* temp = *head;
    while (temp->next != NULL && temp->next->digito != numero) {
        temp = temp->next;
    }

    //Se o número não foi encontrado
    if (temp->next == NULL) {
        printf("Número %d não encontrado na lista.\n", numero);
        free(novoNo);
        return;
    }

    //Atualiza os ponteiros para inserir o novo nó
    novoNo->next = temp->next;
    temp->next = novoNo;
}

//Função para adicionar um nó depois de um nó com um valor específico
void adicionarDepois(BigNumber* head, int valorDepois, int digito) {
    //Se a lista estiver vazia
    if (head == NULL) {
        printf("Lista vazia! Não é possível adicionar depois.\n");
        return;
    }

    //Percorre a lista para encontrar o nó com o valor 'valorDepois'
    BigNumber* temp = head;
    while (temp != NULL && temp->digito != valorDepois) {
        temp = temp->next;
    }

    //Se o valor não for encontrado, exibe uma mensagem e retorna
    if (temp == NULL) {
        printf("Número %d não encontrado na lista.\n", valorDepois);
        return;
    }

    //Cria o novo nó
    BigNumber* novoNo = criarNo(digito);

    //Atualiza os ponteiros
    novoNo->next = temp->next;
    temp->next = novoNo;
}

//Função para remover um nó com o número especificado
void removerNumero(BigNumber **head, int numero) {
    if (*head == NULL) {
        printf("Lista vazia! Não é possível remover o número.\n");
        return;
    }

    // Se o número a ser removido é o primeiro nó
    if ((*head)->digito == numero) {
        BigNumber* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    BigNumber* temp = *head;
    while (temp->next != NULL) {
        if (temp->next->digito == numero) {
            BigNumber* noRemover = temp->next;
            temp->next = temp->next->next;
            free(noRemover);
            return;
        }
        temp = temp->next;
    }

    printf("Número %d não encontrado na lista.\n", numero);
}

// Função para encontrar um número na lista
BigNumber* encontrarNumero(BigNumber *head, int numero) {
    BigNumber* temp = head;
    while (temp != NULL) {
        if (temp->digito == numero) {
            return temp;  // Número encontrado
        }
        temp = temp->next;
    }
    return NULL;  // Número não encontrado
}

//Função para contar o número de elementos na lista
int contarElementos(BigNumber *head) {
    int contador = 0;
    BigNumber* temp = head;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}

//funcao para imprimir a lista encadeada
void imprimirLista(BigNumber *head)
{
	BigNumber* temp = head;
	while(temp != NULL)
	{
		printf("%d ", temp->digito);
		temp = temp->next;
	}
	printf("\n");
}

//funcao para liberar a memoria da lista 
void liberaMemoria(BigNumber *head)
{
	BigNumber* temp;
	while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

