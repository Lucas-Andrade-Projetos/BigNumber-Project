#ifndef BIGNUMBER_H
#define BIGNUMBER_H

//Definindo a estrutura BigNumber
typedef struct BigNumber {
    int digito; //Dado armazenado (dígito do número)
    struct BigNumber* next; //Próximo nó
    struct BigNumber* prev; //Nó anterior
} BigNumber;

//Estrutura que representa um número completo
typedef struct {
    int sinal; //Sinal do número (+1 ou -1)
    BigNumber* head;
} BigNumberStruct;

//----------------------------------------------------------------Funções de Controle e Teste
BigNumber* criarNo(int digito); //Função para criar nó com um dígito
BigNumberStruct* criarBigNumber(); //Função para inicializar um BigNumber com sinal
void adicionarNoFim(BigNumberStruct* numero, int digito); //Função para adicionar nó no fim da lista
void adicionarInicio(BigNumberStruct* numero, int digito); //Função para adicionar nó no início da lista
void adicionarAntes(BigNumberStruct* numero, int valor, int novoDigito);//Função para adicionar antes de um valor
void adicionarDepois(BigNumberStruct* numero, int valorDepois, int digito);//Função para adicionar depois de um valor
void lerNumeroComSinal(BigNumberStruct* numero); //Função para ler um número com sinal e armazená-lo na lista
void removerNumero(BigNumberStruct* numero, int digito); //Função para remover um nó com o número especificado
BigNumber* encontrarNumero(BigNumberStruct* numero, int digito); //Função para encontrar um nó na lista
int contarElementos(BigNumberStruct* numero); //Função para contar o número de elementos na lista
int comparaBigNumbers(BigNumberStruct* num1, BigNumberStruct* num2);
void imprimirNumero(BigNumberStruct* numero); //Função para imprimir a lista encadeada
void liberaMemoria(BigNumberStruct* numero); //Função para liberar a memória da lista


//----------------------------------------------------------------Funções de Operações
BigNumberStruct* executarOperacao(char operacao, BigNumberStruct* num1, BigNumberStruct* num2);
BigNumberStruct* somaBigNumber(BigNumberStruct* num1, BigNumberStruct* num2);
BigNumberStruct* subtrairBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2);



#endif
