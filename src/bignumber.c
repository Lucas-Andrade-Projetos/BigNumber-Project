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
    }

    BigNumber* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = novoNo;
	novoNo->prev = temp;//Define o anterior do novo nó
}

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumber** head, int valor) {
    BigNumber* novoNo = criarNo(valor);
	if (*head == NULL) {
        *head = novoNo;
        return;
    }

    novoNo->next = *head;
	(*head)->prev = novoNo; //Define o anterior do antigo primeiro nó
    *head = novoNo;
}

//Funcao para adicionar no antes de um Valor
void adicionarAntes(BigNumber **head, int numero, int novoDigito) {
	if (*head == NULL) {
        printf("Lista vazia! Não é possível adicionar antes.\n");
        return;
    }

	BigNumber* temp = *head;
    while (temp != NULL && temp->digito != numero) {
        temp = temp->next;
    }

   if (temp == NULL) {
        printf("Número %d não encontrado na lista.\n", numero);
        return;
    }

    BigNumber* novoNo = criarNo(novoDigito);
    novoNo->next = temp;
    novoNo->prev = temp->prev;

    if (temp->prev != NULL) { // Caso não seja o primeiro nó
        temp->prev->next = novoNo;
    } else { // Atualiza o head se for o primeiro nó
        *head = novoNo;
    }

    temp->prev = novoNo;
}

//Função para adicionar um nó depois de um nó com um valor específico
void adicionarDepois(BigNumber *head, int valorDepois, int digito) {
    if (head == NULL) {
        printf("Lista vazia! Não é possível adicionar depois.\n");
        return;
    }

    BigNumber* temp = head;
    while (temp != NULL && temp->digito != valorDepois) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Número %d não encontrado na lista.\n", valorDepois);
        return;
    }

    BigNumber* novoNo = criarNo(digito);
    novoNo->next = temp->next;
    novoNo->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = novoNo;
    }

    temp->next = novoNo;
}

//Função para remover um nó com o número especificado
void removerNumero(BigNumber **head, int numero) {
    if (*head == NULL) {
        printf("Lista vazia! Não é possível remover.\n");
        return;
    }

    BigNumber* temp = *head;
    while (temp != NULL && temp->digito != numero) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Número %d não encontrado na lista.\n", numero);
        return;
    }

    if (temp->prev != NULL) { // Caso não seja o primeiro nó
        temp->prev->next = temp->next;
    } else { // Atualiza o head se for o primeiro nó
        *head = temp->next;
    }

    if (temp->next != NULL) { // Caso não seja o último nó
        temp->next->prev = temp->prev;
    }

    free(temp);
}

BigNumber* encontrarNumero(BigNumber *head, int numero) {
    BigNumber* temp = head;
    
    while (temp != NULL) {
        if (temp->digito == numero) {
            return temp;//Número encontrado
        }
        temp = temp->next;//Avança para o próximo nó
    }
    
    return NULL;//Número não encontrado
}

//Função para contar o número de elementos na lista
int contarElementos(BigNumber *head) {
    int contador = 0;
    BigNumber* temp = head;
    
    while (temp != NULL) {
        contador++; //Incrementa o contador para cada nó
        temp = temp->next; //Avança para o próximo nó
    }
    
    return contador;
}

//funcao para imprimir a lista encadeada
void imprimirLista(BigNumber *head) {
    BigNumber* temp = head;
    printf("Lista: ");
    while (temp != NULL) {
        printf("%d ", temp->digito);
        temp = temp->next;
    }
    printf("\n");
}

//funcao para liberar a memoria da lista 
void liberaMemoria(BigNumber *head) {
    BigNumber *temp;
    while (head != NULL) {
        temp = head;        
        head = head->next;   
        free(temp);          
    }
}

