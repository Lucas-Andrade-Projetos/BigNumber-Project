#ifndef BIGNUMBER_H
#define BIGNUMBER_H

//Definindo a estrutura BigNumber
typedef struct BigNumber {
	
	int digito; //dado armazenado
	struct BigNumber *next; //proximo no
	struct BigNumber *prev; //no anterior

} BigNumber;

//------------------------------------------------------------------------------------------------------Funcoes Principais
BigNumber* criarNo(int digito); //funcao para criar no com um digito
void adicionarNoFim(BigNumber **head, int digito);//funcao para adicionar no no fim da fila 
void adicionarInicio(BigNumber** head, int valor);//Função para adicionar um nó no início da lista
void adicionarAntes(BigNumber **head, int numero, int novoDigito);//Funcao para adicionar no no inicio da
void adicionarDepois(BigNumber* head, int valorDepois, int digito);//Função para adicionar um nó depois de um nó com um valor específico
BigNumber* lerNumeroComSinal(int* sinal); // Função para ler um número e armazená-lo na lista
void removerNumero(BigNumber **head, int numero);//Função para remover um nó com o número especificado
BigNumber* encontrarNumero(BigNumber *head, int numero);// Função para encontrar um número na lista
int contarElementos(BigNumber *head);//Função para contar o número de elementos na lista
void imprimirLista(BigNumber *head, int sinal);//funcao para imprimir a lista encadeada
void liberaMemoria(BigNumber *head);//funcao liberar memoria da lista

#endif