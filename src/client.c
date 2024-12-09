#include <stdio.h>
#include "bignumber.h"

int main() {
    int n;
    scanf("%d", &n); 
    getchar();

    for (int i = 0; i < n; i++) {
        int sinal1, sinal2;
        
        BigNumber* num1 = lerNumeroComSinal(&sinal1);
        BigNumber* num2 = lerNumeroComSinal(&sinal2);
        
        char operacao;
        scanf("%c", &operacao);
        getchar();  
        
        printf("Número 1: ");
        imprimirLista(num1, sinal1);
        printf("Número 2: ");
        imprimirLista(num2, sinal2);
        
        liberaMemoria(num1);
        liberaMemoria(num2);
    }

    return 0;
}