#include <stdio.h>
#include "bignumber.h"

int main() {
    //Loop infinito para processar as opereções de forma continua.
	while (1) {
        BigNumberStruct* num1 = criarBigNumber();
        BigNumberStruct* num2 = criarBigNumber();
		
		//Verifica se a leitura de qualquer um dos dois números falhou
        if (lerNumeroComSinal(num1) == -1 || lerNumeroComSinal(num2) == -1) { 
            //Libera memória alocada e encerra o programa
            liberaMemoria(num1);
            liberaMemoria(num2);
            break;
        }

        char operacao;
		//Lê a operação matemática a ser realizada(+, -, *, /)
        if (scanf(" %c", &operacao) == EOF) {
            liberaMemoria(num1);
            liberaMemoria(num2);
            break;
        }

		//Realiza a operação entre os dois números grandes com base nas variáveis coletadas
        BigNumberStruct* resultado = executarOperacao(operacao, num1, num2);


        //Se a operação for válida e um resultado for gerado
        if (resultado != NULL) {
            //Imprime o resultado do cálculo
            imprimirNumero(resultado); 
            fflush(stdout);//Garante que a saída seja mostrada (em casos de muitos resultados o terminal estava sendo cortado).
            liberaMemoria(resultado);//Libera memória alocada para o resultado
        }

        liberaMemoria(num1);
        liberaMemoria(num2);
    }
	printf("\n");//Adiciona uma linha em branco ao final do processo
    return 0;
}
