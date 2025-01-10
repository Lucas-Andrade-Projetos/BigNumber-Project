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

/* src/client.c
#include <stdio.h>
#include "bignumber.h" // Inclui o cabeçalho com a estrutura BigNumber e funções relacionadas

int main() {
    // Teste simples para verificar se o método de Karatsuba está funcionando corretamente
    
    // Cria dois números grandes manualmente (substituir por valores relevantes para teste)
    BigNumberStruct* num1 = criarBigNumberDeNumero(123456);
    BigNumberStruct* num2 = criarBigNumberDeNumero(456);

    // Insira manualmente os valores para teste (exemplo: "12345" e "6789")
     // Atribui o valor 12345 ao primeiro número
      // Atribui o valor 6789 ao segundo número

    // Chama a função Karatsuba para realizar a multiplicação
    BigNumberStruct* resultado = multiplicarKaratsuba(num1, num2);

    // Imprime o resultado da multiplicação
    if (resultado != NULL) {
        printf("Resultado da multiplicação: ");
        imprimirNumero(resultado);
        printf("\n");
        liberaMemoria(resultado); // Libera memória do resultado
    } else {
        printf("Erro ao calcular a multiplicação usando Karatsuba.\n");
    }

    // Libera memória dos números de entrada
    liberaMemoria(num1);
    liberaMemoria(num2);

    return 0;
}*/
