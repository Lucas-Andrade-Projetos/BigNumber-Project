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
BigNumberStruct* criarBigNumberDeNumero(long long numero); //Função para criar um bignumber já com valor definido
void adicionarNoFim(BigNumberStruct* numero, int digito); //Função para adicionar nó no fim da lista
void adicionarInicio(BigNumberStruct* numero, int digito); //Função para adicionar nó no início da lista
void adicionarAntes(BigNumberStruct* numero, int valor, int novoDigito);//Função para adicionar antes de um valor
void adicionarDepois(BigNumberStruct* numero, int valorDepois, int digito);//Função para adicionar depois de um valor
void lerNumeroComSinal(BigNumberStruct* numero); //Função para ler um número com sinal e armazená-lo na lista
void removerNumero(BigNumberStruct* numero, int digito); //Função para remover um nó com o número especificado
BigNumber* encontrarNumero(BigNumberStruct* numero, int digito); //Função para encontrar um nó na lista
int contarElementos(BigNumberStruct* numero); //Função para contar o número de elementos na lista
int comparaBigNumbers(BigNumberStruct* num1, BigNumberStruct* num2); //Funçao que compara a magnetudo dos dígitos, ou seja vê qual é maior que o outro.
void removerInicio(BigNumberStruct* numero); //Função para remover numeros no inicio
void removerZeros(BigNumberStruct* numero); //Função que remove os zeros a esquerda.
BigNumberStruct* reverterBigNumber(BigNumberStruct* numero); //Função que reverte a lista(Usada na multiplicação)
void imprimirNumero(BigNumberStruct* numero); //Função para imprimir a lista encadeada
void liberaMemoria(BigNumberStruct* numero); //Função para liberar a memória da lista

void adicionarNoFinal(BigNumber** head, int digito);

//----------------------------------------------------------------Funções de Operações
BigNumberStruct* executarOperacao(char operacao, BigNumberStruct* num1, BigNumberStruct* num2); //Função para controlar a operação escolhida
BigNumberStruct* somaBigNumber(BigNumberStruct* num1, BigNumberStruct* num2); //Função para somar dois BigNumberStruct
BigNumberStruct* subtrairBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2); //Função para subtrair dois BigNumberStruct
BigNumberStruct* multiplicarBigNumbers(BigNumberStruct* num1, BigNumberStruct* num2); //Função para multiplicar dois BigNumberStruct
BigNumberStruct* dividirBigNumbers(BigNumberStruct* dividendo, BigNumberStruct* divisor); //Função para dividir dois BigNumberStruct com resultado inteiro.





#endif
