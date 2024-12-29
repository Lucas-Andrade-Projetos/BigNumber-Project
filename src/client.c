#include <stdio.h>
#include "bignumber.h"

int main() {
    int n;
    scanf("%d", &n); 
    getchar();  // Para consumir o '\n' após a leitura do número de casos

    for (int i = 0; i < n; i++) { 
        // Criando os BigNumbers
        BigNumberStruct* num1 = criarBigNumber();
        BigNumberStruct* num2 = criarBigNumber();
        
        lerNumeroComSinal(num1);
        lerNumeroComSinal(num2);

        // Lendo a operação
        char operacao;
        scanf("%c", &operacao);  
        getchar(); 

        // Imprimindo os números
        printf("Número 1: ");
        imprimirNumero(num1);
        printf("Número 2: ");
        imprimirNumero(num2);

        // Liberando a memória
        liberaMemoria(num1);
        liberaMemoria(num2);
    }

    return 0;
}
