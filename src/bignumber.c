#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------Funções de Controle e Teste

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
void lerNumeroComSinal(BigNumberStruct* num) {
    char c;
    scanf(" %c", &c);  // Lê o sinal ou o primeiro caractere

    if (c == '+' || c == '-') {
        num->sinal = (c == '-') ? -1 : 1;  // Define o sinal do número
    } else {
        num->sinal = 1;  // Se não houver sinal, o número é positivo por padrão
        ungetc(c, stdin);  // Coloca o caractere de volta no buffer para que o número seja lido corretamente
    }

    // Lê o número e o adiciona à lista
    while (scanf("%c", &c) && c != '\n') {
        if (c >= '0' && c <= '9') {
            adicionarNoFim(num, c - '0');
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

//Funçao que compara a magnetudo dos dígitos
int comparaBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    //Compara o número de dígitos(As funções operacionais são úteis);
    int digitos1 = contarElementos(numero1);
    int digitos2 = contarElementos(numero2);

    if (digitos1 > digitos2) {
        return 1;  
    } else if (digitos1 < digitos2) {
        return -1;  
    }

    BigNumber* temp1 = numero1->head;
    BigNumber* temp2 = numero2->head;

    while (temp1 != NULL) {
        if (temp1->digito > temp2->digito) {
            return 1;  
        } else if (temp1->digito < temp2->digito) {
            return -1; 
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;//Os números são iguais
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

//----------------------------------------------------------------Funções de Operações 

//Função para controlar as operações
BigNumberStruct* executarOperacao(char operacao, BigNumberStruct* numero1, BigNumberStruct* numero2) {
    BigNumberStruct* resultado = NULL;

    if (operacao == '+') {
        resultado = somaBigNumber(numero1, numero2);
    }else{
        printf("Cooming soon...");
    }

    return resultado;
}

//Função para somar dois BigNumberStruct
BigNumberStruct* somaBigNumber(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    
    //sinais iguais------------------------------
    if (numero1->sinal == numero2->sinal) {
        BigNumberStruct* resultado = criarBigNumber();
        BigNumber* temp1 = numero1->head;
        BigNumber* temp2 = numero2->head;

        while (temp1 != NULL && temp1->next != NULL) {
            temp1 = temp1->next;
        }
        while (temp2 != NULL && temp2->next != NULL) {
            temp2 = temp2->next;
        }

        int carry = 0; 
        int digito1 = 0, digito2 = 0;

        while (temp1 != NULL || temp2 != NULL || carry != 0) {
            if (temp1 != NULL) {
                digito1 = temp1->digito;
                temp1 = temp1->prev;
            }

            if (temp2 != NULL) {
                digito2 = temp2->digito;
                temp2 = temp2->prev; 
            }

            int soma = digito1 + digito2 + carry;
            carry = soma / 10; 
            int digitoResultado = soma % 10;  

            adicionarInicio(resultado, digitoResultado);

            digito1 = 0;
            digito2 = 0;
        }

        resultado->sinal = numero1->sinal;
        return resultado;
    }

    //sinais diferentes------------------------------
    else {
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

//Função para subtrair dois BigNumberStruct --- incompleta
BigNumberStruct* subtrairBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2) {
    BigNumberStruct* resultado = criarBigNumber();
    BigNumber* temp1 = numero1->head;
    BigNumber* temp2 = numero2->head;

    while (temp1 != NULL && temp1->next != NULL) {
        temp1 = temp1->next;
    }
    while (temp2 != NULL && temp2->next != NULL) {
        temp2 = temp2->next;
    }

    int borrow = 0; 
    int digito1 = 0, digito2 = 0;

    while (temp1 != NULL || temp2 != NULL || borrow != 0) {
        if (temp1 != NULL) {
            digito1 = temp1->digito;
            temp1 = temp1->prev; 
        }

        if (temp2 != NULL) {
            digito2 = temp2->digito;
            temp2 = temp2->prev;  
        }

        int subtracao = digito1 - digito2 - borrow;
        if (subtracao < 0) {
            subtracao += 10; 
            borrow = 1; 
        } else {
            borrow = 0; 
        }

        adicionarInicio(resultado, subtracao);

        digito1 = 0;
        digito2 = 0;
    }

    if (comparaBigNumbers(numero1, numero2) < 0) {
        resultado->sinal = numero2->sinal;
    } else {
        resultado->sinal = numero1->sinal;
    }
    return resultado;
}





