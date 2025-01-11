#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------Funções de Controle e Teste

//Função para criar um nó
BigNumber* criarNo(int digito) {
    
	BigNumber* novoNo = (BigNumber*)malloc(sizeof(BigNumber)); //Aloca memória para um novo nó
    if (!novoNo) { //Verifica se a alocação falhou
        return NULL; //Retorna NULL em caso de erro
    }

    novoNo->digito = digito; //Define o dígito no nó
    novoNo->next = NULL;     //Inicializa o ponteiro para o próximo nó como NULL
    novoNo->prev = NULL;     //Inicializa o ponteiro para o nó anterior como NULL
    
	return novoNo; //Retorna o ponteiro para o nó recém-criado
}

//Função para inicializar um BigNumberStruct (Essa função eu uso para guardar o sinal do bignumber, foi muito útil para verificações e aloocações futuras)
BigNumberStruct* criarBigNumber() {
   
    BigNumberStruct* numero = (BigNumberStruct*)malloc(sizeof(BigNumberStruct)); //Aloca memória para a estrutura
    if (!numero) { //Verifica se a alocação falhou
        return NULL; //Retorna NULL em caso de erro
    }

    numero->sinal = 1; //Inicializa o sinal como positivo (1)
    numero->head = NULL; //Define o ponteiro para a cabeça da lista como NULL

    return numero; //Retorna o ponteiro para a estrutura recém-criada
}

//Função para criar um bignumber já com valor definido (Usado apenas para debugs no terminal).
BigNumberStruct* criarBigNumberDeNumero(long long numero) {
    
	BigNumberStruct* novoBigNumber = criarBigNumber(); //Cria uma estrutura inicializada

    if (numero < 0) { //Verifica se o número é negativo
        novoBigNumber->sinal = -1; //Define o sinal como negativo
        numero = -numero; //Converte o número para positivo
    } else {
        novoBigNumber->sinal = 1; //Define o sinal como positivo
    }

    //Divide o número em dígitos e os adiciona no início da lista
    do {
        int digito = numero % 10; //Obtém o último dígito
        adicionarInicio(novoBigNumber, digito); //Adiciona o dígito à lista
        numero /= 10; //Remove o último dígito do número
    } while (numero > 0); //Repete até que todos os dígitos sejam processados

    return novoBigNumber; //Retorna o ponteiro para o BigNumberStruct criado
}

//Função para adicionar nó no final da lista
void adicionarNoFim(BigNumberStruct* numero, int digito) {
    
	BigNumber* novoNo = criarNo(digito); //Cria um novo nó com o dígito fornecido
    if (numero->head == NULL) { //Verifica se a lista está vazia
        numero->head = novoNo; //Define o nó como o primeiro da lista
    } else {
        BigNumber* temp = numero->head; //Inicializa um ponteiro temporário na cabeça da lista
        while (temp->next != NULL) { //Percorre a lista até o último nó
            temp = temp->next;
        }
        temp->next = novoNo; //Conecta o novo nó ao final da lista
        novoNo->prev = temp; //Define o nó anterior do novo nó
    }
}

//Função para adicionar um nó no início da lista
void adicionarInicio(BigNumberStruct* numero, int digito) {
	
	BigNumber* novoNo = criarNo(digito); //Cria um novo nó com o dígito fornecido
    
	if (numero->head == NULL) { //Verifica se a lista está vazia
        numero->head = novoNo; //Define o nó como o primeiro da lista
    } else {
        novoNo->next = numero->head; //Conecta o novo nó ao início da lista
        numero->head->prev = novoNo; //Define o novo nó como o anterior ao nó atual
        numero->head = novoNo; //Atualiza a cabeça da lista para o novo nó
    }
}

//Função para adicionar antes de um valor
void adicionarAntes(BigNumberStruct* numero, int valor, int novoDigito) {
    
	BigNumber* temp = numero->head; //Inicia a busca na cabeça da lista
    
	while (temp != NULL && temp->digito != valor) { //Procura o nó com o valor desejado
        temp = temp->next;
    }
    
	if (temp != NULL) { //Verifica se o valor foi encontrado
        BigNumber* novo = criarNo(novoDigito); //Cria o novo nó
        novo->prev = temp->prev; //Conecta o nó anterior ao novo nó
        novo->next = temp; //Conecta o novo nó ao nó atual
        if (temp->prev != NULL) { //Atualiza o próximo do nó anterior, se existir
            temp->prev->next = novo;
        } else { //Se o nó atual era a cabeça, redefine a cabeça
            numero->head = novo;
        }
        temp->prev = novo; //Atualiza o anterior do nó atual
    }
}

//Função para adicionar depois de um valor
void adicionarDepois(BigNumberStruct* numero, int valorDepois, int digito) {
    
	BigNumber* temp = numero->head; // Inicia a busca na cabeça da lista
    
	while (temp != NULL && temp->digito != valorDepois) { // Procura o nó com o valor desejado
        temp = temp->next;
    }
    
	if (temp != NULL) { //Verifica se o valor foi encontrado
        BigNumber* novo = criarNo(digito); // Cria o novo nó
        novo->next = temp->next; //Conecta o novo nó ao próximo do nó atual
        novo->prev = temp; //Conecta o novo nó ao nó atual
        if (temp->next != NULL) { //Atualiza o anterior do próximo nó, se existir
            temp->next->prev = novo;
        }
        temp->next = novo; //Atualiza o próximo do nó atual
    }
}

//Função para ler um número com sinal (+ ou -) e o armazena na lista.
int lerNumeroComSinal(BigNumberStruct* num) {
    
	char c;

    if (scanf(" %c", &c) == EOF) {
        return -1; //Retorna -1 se chegar ao fim da entrada
    }

    if (c == '+' || c == '-') { //Verifica se há um sinal explícito 
		if (c == '-') { 
			num->sinal = -1; // Define o sinal como negativo  
		} else { 
			num->sinal = 1; // Define o sinal como positivo 
		} 
	} else { //Se não houver sinal explícito, assume positivo 
		num->sinal = 1; 
		ungetc(c, stdin); //Devolve o caractere lido ao buffer de entrada }
	}
    //Lê cada caractere do número e adiciona à lista
    while (scanf("%c", &c) == 1 && c != '\n') {
        if (c >= '0' && c <= '9') { //Verifica se o caractere é um dígito
            adicionarNoFim(num, c - '0'); //Adiciona o dígito ao final da lista
        }
    }

    return 0; //Retorna 0 indicando sucesso
}

//Função para remover um nó com o número especificado (Usada apenas para debug, não utilizada nas operações)
void removerNumero(BigNumberStruct* numero, int valor) {
    BigNumber* temp = numero->head; //Inicia a busca na cabeça da lista
    while (temp != NULL && temp->digito != valor) { //Procura o nó com o valor desejado
        temp = temp->next;
    }

    if (temp != NULL) { //Verifica se o valor foi encontrado
        if (temp->prev != NULL) { //Atualiza o próximo do nó anterior
            temp->prev->next = temp->next;
        } else { //Se o nó atual era a cabeça, redefine a cabeça
            numero->head = temp->next;
        }

        if (temp->next != NULL) { //Atualiza o anterior do próximo nó
            temp->next->prev = temp->prev;
        }

        free(temp);//Libera a memória do nó removido
    }
}

//Função para encontrar um número específico (Usada apenas para debug, não utilizada nas operações)
BigNumber* encontrarNumero(BigNumberStruct* numero, int valor) {
    
	BigNumber* temp = numero->head; //Inicia a busca na cabeça da lista
    
	while (temp != NULL && temp->digito != valor) { //Procura o nó com o valor desejado
        temp = temp->next;
    }

	return temp; //Retorna o ponteiro para o nó encontrado ou NULL
}

//Função para contar o número de elementos na lista (Usada em algumas operações sendo elas *, / e em outras funçções de apoio)
int contarElementos(BigNumberStruct* numero) {
    
	int contador = 0;
    
	BigNumber* temp = numero->head; // Inicia na cabeça da lista
    
	while (temp != NULL) { //Percorre a lista
        contador++;
        temp = temp->next;
    }
	
    return contador; //Retorna o número de nós
}

//Funçao de apoio que compara a magnetudo dos dígitos, ou seja vê qual é maior que o outro (usada em operações como + e -).
int comparaBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    
	int digitos1 = contarElementos(numero1); //Conta os dígitos do primeiro número
    int digitos2 = contarElementos(numero2); //Conta os dígitos do segundo número

    if (digitos1 > digitos2) { //Compara o número de dígitos
        return 1;  
    } else if (digitos1 < digitos2) {
        return -1;  
    }

    BigNumber* temp1 = numero1->head;
    BigNumber* temp2 = numero2->head;

    while (temp1 != NULL) { //Compara os dígitos um a um
        if (temp1->digito > temp2->digito) {
            return 1;  
        } else if (temp1->digito < temp2->digito) {
            return -1; 
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0; //Retorna 0 se os números são iguais
}

//Função que verifica se o bignumber é impar ou par.
int isImpar(BigNumberStruct* numero) {
    if (numero == NULL || numero->head == NULL) {
        return 0; //Considera zero como par
    }

    BigNumber* temp = numero->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    //Verifica o último dígito
    if (temp->digito % 2 != 0) {
        return 1; //Ímpar
    } else {
        return 0; //Par
    }
}

//Função para remover numeros no inicio (Usada de apoio na função de remover zeros --foi algo que eu resolvi modular para caso fosse usado em outras partes)
void removerInicio(BigNumberStruct* numero) {
    
	if (numero->head == NULL) {
        return; //Se a lista estiver vazia, não há nada para remover.
    }

    BigNumber* temp = numero->head;       //Guarda o nó inicial.
    numero->head = numero->head->next;    //Atualiza o início da lista para o próximo nó.

    if (numero->head != NULL) {
        numero->head->prev = NULL;        //Remove o link para o nó removido.
    }

    free(temp); //Libera a memória do nó removido.
}

//Função para remover zeros à esquerda (Usada de apoio para ajeitar os bignumbers)
void removerZeros(BigNumberStruct* numero) {
	
	//Enquanto o primeiro dígito for zero e houver outros dígitos, remove o zero.
    while (numero->head != NULL && numero->head->digito == 0 && numero->head->next != NULL) {
        removerInicio(numero);
    }

    //Se a lista ficar vazia após a remoção, adiciona um único zero para representar o número 0.
    if (numero->head == NULL) {
        adicionarInicio(numero, 0);
    }
}

//Função usada para fazer um bignumber ficar de trás para frente, para facilitar a multiplicação.
BigNumberStruct* reverterBigNumber(BigNumberStruct* numero) {
    BigNumberStruct* numeroInvertido = criarBigNumber();  //Cria uma nova estrutura para o número invertido.
    BigNumber* temp = numero->head;

    //Adiciona cada dígito do número original no início do novo número.
    while (temp != NULL) {
        adicionarInicio(numeroInvertido, temp->digito);
        temp = temp->next;
    }

    numeroInvertido->sinal = numero->sinal;  //Copia o sinal do número original.

    return numeroInvertido;  //Retorna a estrutura do número invertido.
}

//Função divide o bignumber em sub-bignumbers de acordo com o indice da divisão(usado extritamente no metodo do karatsuba)
void dividirBigNumber(BigNumberStruct* numero, BigNumberStruct** parteAlta, BigNumberStruct** parteBaixa, int indiceDivisao) {
    BigNumber* atual = numero->head;
    int contagem = 0;

    *parteAlta = criarBigNumber();
    *parteBaixa = criarBigNumber();

    //Itera pelos elementos da lista original e divide nas duas partes
    while (atual != NULL) {
        if (contagem < indiceDivisao) {
            //Adiciona ao número alto
            adicionarNoFim(*parteAlta, atual->digito);
        } else {
            //Adiciona ao número baixo
            adicionarNoFim(*parteBaixa, atual->digito);
        }
        contagem++;
        atual = atual->next;
    }

    //Remover zeros à esquerda das partes
    if (numero->head != NULL && numero->head->digito == 0) {
        // Se o número original começa com zero, remove os zeros das partes
        removerZeros(*parteAlta);
        removerZeros(*parteBaixa);
    }
}

//Função que faz as exponenciações de 10 no metodo do karatsuba (usado extritamente no metodo do karatsuba)
BigNumberStruct* deslocarBigNumber(BigNumberStruct* numero, int expoente) {
    BigNumberStruct* resultado = criarBigNumber();

    BigNumber* atual = numero->head;
    while (atual != NULL) {
        adicionarNoFim(resultado, atual->digito);  //Adicionar dígitos originais ao resultado
        atual = atual->next;
    }

    //Adicionar os zeros à direita após os dígitos originais
    for (int i = 0; i < expoente; i++) {
        adicionarNoFim(resultado, 0);  //Adiciona um zero a cada deslocamento
    }

    return resultado;
}

//Função para padronizar o tamanho dos números (preenchendo com zeros à esquerda) - (usado extritamente no metodo do karatsuba)
BigNumberStruct* padronizarTamanho(BigNumberStruct* numero, int tamanho) {
    BigNumberStruct* numeroPadronizado = criarBigNumber();
    int len = contarElementos(numero);

    //Adiciona zeros à esquerda até o número ter o tamanho correto
    for (int i = 0; i < (tamanho - len); i++) {
        adicionarNoFim(numeroPadronizado, 0);  // Adiciona zero à esquerda
    }

    //Adiciona os dígitos do número original
    BigNumber* atual = numero->head;
    while (atual != NULL) {
        adicionarNoFim(numeroPadronizado, atual->digito);
        atual = atual->next;
    }

    return numeroPadronizado;
}


//Função para imprimir o BigNumber
void imprimirNumero(BigNumberStruct* numero) {
    
	if (numero == NULL || numero->head == NULL) {
        return; //Evita erros se o número for inválido.
    }

    if (numero->sinal == -1) {
        printf("-"); //Adiciona o sinal negativo, se necessário.
    }

    BigNumber* temp = numero->head;

    //Itera pelos dígitos do número, imprimindo-os em sequência.
    while (temp != NULL) {
        printf("%d", temp->digito);
        temp = temp->next;
    }


    printf("\n"); //Finaliza a impressão.
}


//Função para liberar a memória do BigNumber
void liberaMemoria(BigNumberStruct* numero) {
    
	BigNumber* temp = numero->head;

    //Itera por todos os nós da lista, liberando a memória de cada um.
    while (temp != NULL) {
        BigNumber* proximo = temp->next; //Armazena o próximo nó antes de liberar o atual.
        free(temp);
        temp = proximo;
    }

    free(numero); //Libera a memória da estrutura principal.
}


//----------------------------------------------------------------Funções de Operações 

//Função para controlar as operações
BigNumberStruct* executarOperacao(char operacao, BigNumberStruct* numero1, BigNumberStruct* numero2) {
    BigNumberStruct* resultado = NULL;

	//soma
    if (operacao == '+') {
        //sinais iguais.
        if (numero1->sinal == 1 && numero2->sinal == 1) {
            resultado = somaBigNumber(numero1, numero2);
        } else if (numero1->sinal == 1 && numero2->sinal == -1) {
            //a positivo e b negativo
            numero2->sinal = 1;
            resultado = subtrairBigNumbers(numero1, numero2);
        } else if (numero1->sinal == -1 && numero2->sinal == 1) {
            //caso de a negativo e b positivo
            numero1->sinal = 1;
            resultado = subtrairBigNumbers(numero2, numero1);
        } else {
            //caso de ambos numeros negativos
            numero1->sinal = 1; 
            numero2->sinal = 1; 
            resultado = somaBigNumber(numero1, numero2);
            resultado->sinal = -1;  //Resultado negativo
        }
    } 

	//subtração
    if (operacao == '-') {
        if (numero1->sinal == 1 && numero2->sinal == 1) {
            // a e b positivo
            resultado = subtrairBigNumbers(numero1, numero2);
        } else if (numero1->sinal == 1 && numero2->sinal == -1) {
            //a positivo e b negativo
            numero2->sinal = 1; 
            resultado = somaBigNumber(numero1, numero2);
        } else if (numero1->sinal == -1 && numero2->sinal == 1) {
            // a positivo e b negativo
            numero1->sinal = 1;
            resultado = somaBigNumber(numero1, numero2);
            resultado->sinal = -1;  // Resultado sempre negativo
        } else {
            //com ambos numeros negativos, inverte sinais
            numero1->sinal = 1; 
            numero2->sinal = 1; 
            resultado = subtrairBigNumbers(numero2, numero1);
        }
    }

	//multiplicação normal
    if (operacao == '@') {
        if (numero1->sinal == 1 && numero2->sinal == 1) {
            // a e b positivo
            resultado = multiplicarBigNumbers(reverterBigNumber(numero1), reverterBigNumber(numero2));
        } else if (numero1->sinal == 1 && numero2->sinal == -1) {
            // a positivo e b com negativos
            numero2->sinal = 1; 
            resultado = multiplicarBigNumbers(reverterBigNumber(numero1), reverterBigNumber(numero2));
            resultado->sinal = -1;
        } else if (numero1->sinal == -1 && numero2->sinal == 1) {
            // a negativo e b positivo
            numero1->sinal = 1; 
            resultado = multiplicarBigNumbers(reverterBigNumber(numero1), reverterBigNumber(numero2));
            resultado->sinal = -1;
        } else {
            //com ambos numeros negativos, vira positivo
            numero1->sinal = 1; 
            numero2->sinal = 1; 
            resultado = multiplicarBigNumbers(reverterBigNumber(numero1), reverterBigNumber(numero2));
        }
    }

	//multiplicação Karatsuba
	if (operacao == '*') {
        if (numero1->sinal == 1 && numero2->sinal == 1) {
            // a e b positivo
            resultado = multiplicarKaratsuba(numero1, numero2);
        } else if (numero1->sinal == 1 && numero2->sinal == -1) {
            // a positivo e b com negativos
            numero2->sinal = 1; 
            resultado = multiplicarKaratsuba(numero1, numero2);
            resultado->sinal = -1;
        } else if (numero1->sinal == -1 && numero2->sinal == 1) {
            // a negativo e b positivo
            numero1->sinal = 1; 
            resultado = multiplicarKaratsuba(numero1, numero2);
            resultado->sinal = -1;
        } else {
            //com ambos numeros negativos, vira positivo 
            resultado = multiplicarKaratsuba(numero1, numero2);
			resultado->sinal = 1;
        }
    }

	//divisão
	if(operacao == '/'){
		if (numero1->sinal == 1 && numero2->sinal == 1) {
            // a e b positivo
            resultado = dividirBigNumbers(numero1, numero2);
        } else if (numero1->sinal == 1 && numero2->sinal == -1) {
    		// a negativo e b positivo
   			numero1->sinal = 1; 
    		resultado = dividirBigNumbers(numero1, numero2);
    
    		// Se o resultado não for zero, define o sinal como negativo
   			 if (resultado->head != NULL && resultado->head->digito != 0) {
       		 resultado->sinal = -1;
    		}
        } else if (numero1->sinal == -1 && numero2->sinal == 1) {
    		// a negativo e b positivo
   			numero1->sinal = 1; 
    		resultado = dividirBigNumbers(numero1, numero2);
    
    		// Se o resultado não for zero, define o sinal como negativo
   			 if (resultado->head != NULL && resultado->head->digito != 0) {
       		 resultado->sinal = -1;
    		}
        } else {
            //com ambos numeros negativos, vira positivo
            numero1->sinal = 1; 
            numero2->sinal = 1; 
            resultado = dividirBigNumbers(numero1, numero2);
        }

	}

	//modulo
	if(operacao == '%'){
        resultado = restoBigNumber(numero1, numero2);
	}

	//exponenciação rapida
	if (operacao == '^') {
    	if (numero1->sinal == 1 && numero2->sinal == 1) {
        	// Ambos os números são positivos
        	resultado = expRapida(numero1, numero2);
    	} else if (numero1->sinal == -1 && numero2->sinal == 1) {
        	// Base negativa e expoente positivo
        	// Verificar a paridade do expoente
        	if (!isImpar(numero2)) {
            	// Expoente par
            	numero1->sinal = 1; 
           		numero2->sinal = 1; 
            	resultado = expRapida(numero1, numero2);
            	resultado->sinal = 1;  // Resultado positivo
        	} else {
            	// Expoente ímpar
            	numero1->sinal = 1; 
            	numero2->sinal = 1; 
            	resultado = expRapida(numero1, numero2);
            	resultado->sinal = -1;// Resultado negativo
        	}
    	}
	}

	//retorna resultado
    return resultado;
}

/*Função para somar dois BigNumberStruct
Funcionamento:
 1.Compara os sinais dos números. Se forem iguais, procede com a soma direta. Caso contrário, converte o problema em subtração;
 2.Move os ponteiros temp1 e temp2 para o final das listas encadeadas dos números;
 3.Percorre as listas de trás para frente, somando os dígitos correspondentes e o carry (vai-um);
 4.Se algum dos números acabar antes, considera 0 para os dígitos faltantes;
 5.Calcula o carry para o próximo dígito;
 6.Adiciona cada dígito calculado ao início da lista do resultado;
 7.Por fim adiciona o sinal correto. --isso poderia ser retirado devido as mudanças no método operações, mas decidi manter, pois foi algo que achei 
   resolver as regras de sinais sem antes pensar nas regras para cada grupo.
*/
BigNumberStruct* somaBigNumber(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    
	// Verifica se os sinais dos números são iguais
    if (numero1->sinal == numero2->sinal) {
        BigNumberStruct* resultado = criarBigNumber(); //Cria uma nova estrutura para armazenar o resultado
        BigNumber* temp1 = numero1->head; //Ponteiro para percorrer os dígitos de numero1
        BigNumber* temp2 = numero2->head; //Ponteiro para percorrer os dígitos de numero2

        //Move os ponteiros para o final das listas (últimos dígitos)
        while (temp1 != NULL && temp1->next != NULL) {
            temp1 = temp1->next;
        }
        while (temp2 != NULL && temp2->next != NULL) {
            temp2 = temp2->next;
        }

        int carry = 0; //Variável para armazenar o vai-um
        int digito1 = 0, digito2 = 0;

        //Realiza a soma enquanto houver dígitos ou carry pendente
        while (temp1 != NULL || temp2 != NULL || carry != 0) {
            
			if (temp1 != NULL) {
                digito1 = temp1->digito;
                temp1 = temp1->prev; //Move para o dígito anterior
            }
            if (temp2 != NULL) {
                digito2 = temp2->digito;
                temp2 = temp2->prev; //Move para o dígito anterior
            }

            int soma = digito1 + digito2 + carry; //Soma os dígitos e o carry
            carry = soma / 10; //Calcula o vai-um
            int digitoResultado = soma % 10; //Calcula o dígito do resultado

            adicionarInicio(resultado, digitoResultado); //Adiciona o dígito ao início do resultado

			//Reseta os dígitos para evitar somas acumuladas
            digito1 = 0; 
            digito2 = 0;
        }

        resultado->sinal = numero1->sinal; //O sinal do resultado será igual ao dos números de entrada
        return resultado;
    }

    //Caso os sinais sejam diferentes
    else {
        //Determina qual número será subtraído e ajusta o sinal do resultado
        if (comparaBigNumbers(numero1, numero2) >= 0) {
            BigNumberStruct* resultado = subtrairBigNumbers(numero1, numero2);
            resultado->sinal = numero1->sinal;
            return resultado;
        } else {
            BigNumberStruct* resultado = subtrairBigNumbers(numero2, numero1);
            resultado->sinal = numero2->sinal;
            return resultado;
        }
    }
}


/*Função para subtrair dois BigNumberStruct
Funcionamento:
 1.Compara os números para decidir qual será o maior (minuendo) e qual será o menor (subtraendo);
 2.Move os ponteiros para o final das listas dos números;
 3.Percorre os dígitos do maior número de trás para frente, subtraindo os dígitos correspondentes do menor
   Se o resultado de uma subtração for negativo, realiza um "empréstimo" (borrow);
 4.Adiciona cada dígito calculado ao início da lista do resultado;
 5.Ajusta o sinal do resultado com base na comparação inicial;
 6.Remove quaisquer zeros desnecessários no início da lista do resultado;
 7.Retorna a estrutura com o número resultante.
*/
BigNumberStruct* subtrairBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    
	//Compara os números para determinar qual é maior
    int comparacao = comparaBigNumbers(numero1, numero2);
    
    BigNumberStruct* maior;
    BigNumberStruct* menor;
    
    //Define qual será o número maior e o menor para evitar resultados negativos inesperados
    if (comparacao >= 0) {
        maior = numero1;
        menor = numero2;
    } else {
        maior = numero2;
        menor = numero1;
    }

    BigNumberStruct* resultado = criarBigNumber(); //Cria a estrutura para o resultado
    BigNumber* tempMaior = maior->head; //Ponteiro para percorrer os dígitos do maior número
    BigNumber* tempMenor = menor->head; //Ponteiro para percorrer os dígitos do menor número

    //Move os ponteiros para o final das listas (últimos dígitos)
    while (tempMaior != NULL && tempMaior->next != NULL) {
        tempMaior = tempMaior->next;
    }
    while (tempMenor != NULL && tempMenor->next != NULL) {
        tempMenor = tempMenor->next;
    }

    int borrow = 0; //Variável para controlar o empréstimo
    int digito1 = 0, digito2 = 0;

    //Realiza a subtração enquanto houver dígitos ou empréstimos pendentes
    while (tempMaior != NULL || borrow != 0) {
        if (tempMaior != NULL) {
            digito1 = tempMaior->digito;
        } else {
            digito1 = 0;
        }

        if (tempMenor != NULL) {
            digito2 = tempMenor->digito;
        } else {
            digito2 = 0;
        }

        int subtracao = digito1 - digito2 - borrow; //Realiza a subtração considerando o empréstimo
        if (subtracao < 0) {
            subtracao += 10; //Ajusta o valor se for negativo
            borrow = 1; //Marca o empréstimo
        } else {
            borrow = 0;
        }

        adicionarInicio(resultado, subtracao); //Adiciona o dígito ao início do resultado

        if (tempMaior != NULL) tempMaior = tempMaior->prev; //Move para o dígito anterior
        if (tempMenor != NULL) tempMenor = tempMenor->prev; //Move para o dígito anterior
    }

    //Define o sinal do resultado baseado na comparação inicial
    if (comparacao >= 0) {
        resultado->sinal = numero1->sinal;
    } else {
        if (numero2->sinal == 1) {
            resultado->sinal = -1;
        } else {
            resultado->sinal = 1;
        }
    }

    //Remove zeros à esquerda para manter a consistência do número
    removerZeros(resultado);

    return resultado;
}

/*Função para multiplicar dois BigNumberStruct
-Essa função para garantir o funcionamento recebe o numero de trás para frente.
A multiplicação inverte os números antes de realizar a operação porque os dígitos são representados em listas encadeadas e, nesse formato, o início da lista (o "head") 
corresponde ao primeiro dígito, enquanto o último dígito está no final da lista. Para facilitar os cálculos de multiplicação, que geralmente começam pelos dígitos menos 
significativos (à direita), é mais eficiente trabalhar diretamente com os números invertidos. 
Isso evita percorrer as listas repetidamente para acessar os dígitos corretos.

Resumindo:
 Os números são representados como listas encadeadas em ordem natural. logo, invertê-los permite acessar rapidamente os dígitos menos significativos, 
 necessários para iniciar a multiplicação (de trás para frente). Dessa forma, Após o cálculo, o resultado é reordenado na sequência original para 
 ser interpretado corretamente.

Exemplo:
 Suponha que você queira multiplicar 123 por 45. Representando em listas: 
	Normal: 1 -> 2 -> 3 e 4 -> 5
	Invertido: 3 -> 2 -> 1 e 5 -> 4
 Multiplicação com listas invertidas:
	Multiplica-se 3 × 5, 3 × 4, e assim por diante, acumulando os resultados diretamente no vetor intermediário.
 Essa abordagem simplifica o código e reduz o número de operações necessárias.

Funcionamento:
 1.Determina o tamanho máximo possível do resultado como a soma dos números de dígitos dos dois operandos
   Aloca memória para armazenar os valores intermediários;
 2.Realiza multiplicações cruzadas entre os dígitos dos dois números
   Adiciona os produtos ao vetor intermediário, levando em conta o vai-um (carry);
 3.Remove zeros desnecessários à esquerda no vetor intermediário.
 4.Converte o vetor intermediário em uma lista encadeada representando o número final.
 5.Retorna a estrutura final.
*/
BigNumberStruct* multiplicarBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    
	int tamanho1 = contarElementos(numero1); //Obtém o número de dígitos do primeiro número
    int tamanho2 = contarElementos(numero2); //Obtém o número de dígitos do segundo número
    
    int resultado_tamanho = tamanho1 + tamanho2; //Tamanho máximo possível do resultado
    int* resultado = (int*)calloc(resultado_tamanho, sizeof(int)); //Vetor para armazenar o resultado intermediário

    BigNumber* temp1 = numero1->head; //Ponteiro para percorrer os dígitos do primeiro número
    for (int i = 0; i < tamanho1; i++) {
        int carry = 0; //Variável para armazenar o vai-um durante a multiplicação
        BigNumber* temp2 = numero2->head; //Ponteiro para percorrer os dígitos do segundo número
        for (int j = 0; j < tamanho2; j++) {
            int sum = temp1->digito * temp2->digito + resultado[i + j] + carry; //Multiplica os dígitos e adiciona o valor atual e o carry
            carry = sum / 10; //Calcula o vai-um
            resultado[i + j] = sum % 10; //Atualiza o dígito atual
            temp2 = temp2->next; //Move para o próximo dígito do segundo número
        }
        resultado[i + tamanho2] += carry; // Adiciona o vai-um ao próximo dígito
        temp1 = temp1->next; //Move para o próximo dígito do primeiro número
    }

    //Remove zeros à esquerda no resultado final
    while (resultado_tamanho > 1 && resultado[resultado_tamanho - 1] == 0) {
        resultado_tamanho--;
    }

    BigNumberStruct* resultadoStruct = criarBigNumber(); //Cria a estrutura para o resultado final
    for (int k = resultado_tamanho - 1; k >= 0; k--) {
        if (resultado[k] != 0 || resultadoStruct->head != NULL) {
            adicionarInicio(resultadoStruct, resultado[k]); //Adiciona os dígitos ao resultado final
        }
    }
    free(resultado); //Libera a memória do vetor intermediário

    return reverterBigNumber(resultadoStruct); //Reverte o número para a ordem correta e retorna
}

/*Função para dividir dois BigNumberStruct com resultado inteiro
Funcionamento:
 1.Verifica se o divisor é zero e, se for, exibe um erro;
 2.Cria estruturas para armazenar o quociente e o resto;
 3.Para cada dígito do dividendo:
   Adiciona o dígito ao resto, remove zeros à esquerda no resto, subtrai repetidamente o divisor do resto enquanto ele for maior ou igual ao divisor, 
   contando o número de subtrações e adiciona o número de subtrações ao quociente;
 4.Adiciona o número de subtrações ao quociente e define o sinal do quociente como positivo se for zero;
 5.Libera a memória usada pelo resto e retorna o quociente.
*/
BigNumberStruct* dividirBigNumbers(BigNumberStruct* dividendo, BigNumberStruct* divisor) {
    //Verifica se o divisor é zero, pois divisão por zero não é permitida
    if (divisor->head == NULL || (contarElementos(divisor) == 1 && divisor->head->digito == 0)) {
        printf("Erro: Divisão por zero.\n");
        return NULL;
    }

    BigNumberStruct* quociente = criarBigNumber(); //Estrutura para armazenar o quociente
    BigNumberStruct* resto = criarBigNumber(); //Estrutura para armazenar o resto da divisão

    BigNumber* temp = dividendo->head; //Ponteiro para percorrer os dígitos do dividendo

    while (temp != NULL) {
        //Adiciona o dígito atual ao resto
        adicionarNoFim(resto, temp->digito);
        removerZeros(resto); //Remove zeros à esquerda no resto

        //Conta quantas vezes o divisor cabe no resto
        int count = 0;
        while (comparaBigNumbers(resto, divisor) >= 0) {
            BigNumberStruct* subtracao = subtrairBigNumbers(resto, divisor); //Subtrai o divisor do resto
            liberaMemoria(resto);  //Libera a memória do resto anterior
            resto = subtracao; //Atualiza o resto
            count++; //Incrementa o contador
        }

        adicionarNoFim(quociente, count); //Adiciona o valor do contador ao quociente
        temp = temp->next; //Move para o próximo dígito do dividendo
    }

    removerZeros(quociente); //Remove zeros à esquerda no quociente

    //Define o sinal do quociente como positivo caso seja zero
    if (quociente->head == NULL || (quociente->head->digito == 0 && quociente->head->next == NULL)) {
        quociente->sinal = 1;
    }

    liberaMemoria(resto); //Libera a memória do resto

    return quociente; //Retorna o quociente
}

/*Função para calcular o resto da divisão
Funcionamento:
 1.Inicializa resto e dividendo;
 2.Copia os dígitos de numero1 para dividendo;
 3.Subtrai repetidamente divisor de dividendo enquanto este for maior ou igual ao divisor;
 4.O que sobra em dividendo é copiado para resto;
 5.Libera a memória usada para o cálculo intermediário e retorna o resto.
*/
BigNumberStruct* restoBigNumber(BigNumberStruct* numero1, BigNumberStruct* divisor) {
    //Cria um BigNumberStruct para armazenar o resultado do resto
    BigNumberStruct* resto = criarBigNumber();

    //Cria uma cópia de numero1 que será usada para o cálculo da divisão
    BigNumberStruct* dividendo = criarBigNumber();

    //Copiar os números de numero1 para dividendo
    BigNumber* temp = numero1->head;
    while (temp != NULL) {
        adicionarNoFim(dividendo, temp->digito);
        temp = temp->next;
    }

    //Subtrai o divisor do dividendo até que o dividendo seja menor que o divisor
    int iteracao = 0;
    while (comparaBigNumbers(dividendo, divisor) >= 0) {
        BigNumberStruct* tempDividendo = subtrairBigNumbers(dividendo, divisor);
        liberaMemoria(dividendo); //Libera a memória do dividendo anterior
        dividendo = tempDividendo; //Atualiza o dividendo com o resultado da subtração
        iteracao++;
    }

    //O que sobrar no dividendo é o resto
    temp = dividendo->head;
    while (temp != NULL) {
        adicionarNoFim(resto, temp->digito);
        temp = temp->next;
    }

    //Libera a memória usada pelo dividendo
    liberaMemoria(dividendo);

    //Retorna o resto calculado
    return resto;
}

/*Função para calcular exponenciação rapida
Funcionamento:
 1.Trata o caso base (exp = 0) e retorna 1;
 2.Inicializa resultado como 1, baseAtual como uma cópia de base, e cria zero e dois para operações;
 3.Entra no loop principal:
	-Se exp for ímpar, atualiza resultado multiplicando-o por baseAtual;
	-Atualiza baseAtual calculando seu quadrado;
	-Atualiza exp dividindo-o por 2.
 4.Após o loop, libera a memória auxiliar e retorna o resultado final.
*/
BigNumberStruct* expRapida(BigNumberStruct* base, BigNumberStruct* exp) {
    // Caso base: base^0 = 1
    if (exp->head->digito == 0 && exp->head->next == NULL) {
        return criarBigNumberDeNumero(1);
    }

    // Inicializa resultado como 1
    BigNumberStruct* resultado = criarBigNumberDeNumero(1);

    // Copia a base para baseAtual
    BigNumberStruct* baseAtual = criarBigNumber();
    BigNumber* temp = base->head;
    while (temp != NULL) {
        adicionarNoFim(baseAtual, temp->digito);
        temp = temp->next;
    }

    // Declarações para zero e dois
    BigNumberStruct* zero = criarBigNumberDeNumero(0);
    BigNumberStruct* dois = criarBigNumberDeNumero(2);

    // Loop principal para cálculo da exponenciação rápida
    while (comparaBigNumbers(exp, zero) > 0) {
        BigNumberStruct* resto = restoBigNumber(exp, dois);

        if (resto->head->digito == 1 && resto->head->next == NULL) { // Se o expoente for ímpar
            BigNumberStruct* tempResultado = multiplicarBigNumbers(reverterBigNumber(resultado), reverterBigNumber(baseAtual));
            liberaMemoria(resultado);
            resultado = tempResultado;
        }

        // Atualiza baseAtual (baseAtual = baseAtual^2)
        BigNumberStruct* tempBase = multiplicarBigNumbers(reverterBigNumber(baseAtual), reverterBigNumber(baseAtual));
        liberaMemoria(baseAtual);
        baseAtual = tempBase;

        // Atualiza exp (exp = exp / 2)
        BigNumberStruct* tempExp = dividirBigNumbers(exp, dois);
        liberaMemoria(exp);
        exp = tempExp;

        liberaMemoria(resto);
    }

    // Libera os BigNumbers auxiliares
    liberaMemoria(baseAtual);
    liberaMemoria(zero);
    liberaMemoria(dois);

    return resultado;
}

/*Função de multiplicação Karatsuba
Funcionamento e fluxo das operações:
 1.Entrada: Números num1 e num2.
 2.Remoção de zeros à esquerda de ambos os numeros
 3.Padronização de tamanho.
 4.Divisão dos números em duas partes.
 5.Multiplicação recursiva de partes.
 6.Ajuste de valores intermediários e somas.
 7.Deslocamento das partes para a ordem correta.
 8.Soma final.
 9.Remoção de zeros à esquerda do resultado.
 10.Liberação de memória.
*/
BigNumberStruct* multiplicarKaratsuba(BigNumberStruct* num1, BigNumberStruct* num2) {
    
    removerZeros(num1);  // Remover zeros à esquerda de num1
    removerZeros(num2);  // Remover zeros à esquerda de num2
    

    int tamanho1 = contarElementos(num1);
    int tamanho2 = contarElementos(num2);

    int tamanhoMaximo = (tamanho1 > tamanho2) ? tamanho1 : tamanho2;

    num1 = padronizarTamanho(num1, tamanhoMaximo);
    num2 = padronizarTamanho(num2, tamanhoMaximo);

    // Agora num1 e num2 têm o mesmo tamanho, podemos prosseguir com a multiplicação
    if (tamanho1 == 1 || tamanho2 == 1) {
        return multiplicarBigNumbers(reverterBigNumber(num1), reverterBigNumber(num2));
    }

    int medio = (tamanhoMaximo + 1) / 2;

    BigNumberStruct *num1_0, *num1_1, *num2_0, *num2_1;
    
    dividirBigNumber(num1, &num1_1, &num1_0, medio);
    dividirBigNumber(num2, &num2_1, &num2_0, medio);


    BigNumberStruct *z0 = multiplicarBigNumbers(reverterBigNumber(num1_0), reverterBigNumber(num2_0));
    BigNumberStruct *z2 = multiplicarBigNumbers(reverterBigNumber(num1_1), reverterBigNumber(num2_1));


    BigNumberStruct *somaA = somaBigNumber(num1_0, num1_1);
    BigNumberStruct *somaB = somaBigNumber(num2_0, num2_1);


    BigNumberStruct *z1 = multiplicarBigNumbers(reverterBigNumber(somaA), reverterBigNumber(somaB));
    

    BigNumberStruct *temp = somaBigNumber(z0, z2);

    z1 = subtrairBigNumbers(z1, temp);


    // Declaração das variáveis fora do bloco condicional
    BigNumberStruct *z2elevada;
    BigNumberStruct *z1elevada;

	//ajuste de bug com numeros onde tamanho maximo era ímpar exemplo 931/2 = 465,5 onde medio ficaria = 466 e o correto seria 465 nessa operação
    if(tamanhoMaximo % 2 == 0){
        z2elevada = deslocarBigNumber(z2, 2 * medio);
        z1elevada = deslocarBigNumber(z1, medio);
    }else{
        z2elevada = deslocarBigNumber(z2, 2 * (medio - 1));
        z1elevada = deslocarBigNumber(z1, medio - 1);
    }

    BigNumberStruct *resultado = somaBigNumber(z2elevada, z1elevada);
    resultado = somaBigNumber(resultado, z0);

    removerZeros(resultado);  // Remover zeros à esquerda do resultado final

    liberaMemoria(num1_0);
    liberaMemoria(num1_1);
    liberaMemoria(num2_0);
    liberaMemoria(num2_1);
    liberaMemoria(z0);
    liberaMemoria(z1);
    liberaMemoria(z2);
    liberaMemoria(temp);
    liberaMemoria(z2elevada);
    liberaMemoria(z1elevada);
    liberaMemoria(somaA);
    liberaMemoria(somaB);

    return resultado;
}

