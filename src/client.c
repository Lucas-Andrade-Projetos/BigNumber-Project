#include <stdio.h>
#include "bignumber.h"

int main() {
    while (1) {
        BigNumberStruct* num1 = criarBigNumber();
        BigNumberStruct* num2 = criarBigNumber();

        if (lerNumeroComSinal(num1) == -1) { 
            liberaMemoria(num1);
            liberaMemoria(num2);
            break;
        }
        if (lerNumeroComSinal(num2) == -1) { 
            liberaMemoria(num1);
            liberaMemoria(num2);
            break;
        }
        char operacao;
        if (scanf(" %c", &operacao) == EOF) {
            liberaMemoria(num1);
            liberaMemoria(num2);
            break;
        }
		//printf("-----------------------------------\n");
		//printf("print ai\n");
		//imprimirNumero(num1);
		//printf("\n");
		//imprimirNumero(num2);
		//printf("\n");
		//printf("-----------------------------------\n");
        BigNumberStruct* resultado = executarOperacao(operacao, num1, num2);

		//teste com print 
		//printf("print ai\n");
		//imprimirNumero(num1);
		//printf("\n");
		//imprimirNumero(num2);
		//printf("\n");
		//printf("-----------------------------------\n");
        if (resultado != NULL) {
            imprimirNumero(resultado); 
            fflush(stdout);  
			//printf("\n");
            liberaMemoria(resultado);
        }

        liberaMemoria(num1);
        liberaMemoria(num2);
    }
	printf("\n");
    return 0;
}
