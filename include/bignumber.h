#ifndef BIGNUMBER_H
#define BIGNUMBER_H

//Definindo a estrutura BigNumber
typedef struct BigNumber {
	
	int digito; //dado armazenado
	struct BigNumber *next; //proximo no
	struct BigNumber *prev; //no anterior

} BigNumber;

//funcco para criar no com um digito
BigNumber* criarNo(int digito);

//funcao para adicionar no no fim da fila 
void adicionarNoFim(BigNumber **head, int digito);

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumber** head, int valor);

//Funcao para adicionar no no inicio da
void adicionarAntes(BigNumber **head, int numero, int novoDigito);

//Função para adicionar um nó depois de um nó com um valor específico
void adicionarDepois(BigNumber* head, int valorDepois, int digito);

//Função para remover um nó com o número especificado
void removerNumero(BigNumber **head, int numero);

// Função para encontrar um número na lista
BigNumber* encontrarNumero(BigNumber *head, int numero);

//Função para contar o número de elementos na lista
int contarElementos(BigNumber *head);

//funcao para imprimir a lista encadeada
void imprimirLista(BigNumber *head);

//funcao liberar memoria da lista
void liberaMemoria(BigNumber *head);

#endif