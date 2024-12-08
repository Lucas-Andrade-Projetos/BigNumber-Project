#include <stdio.h>
#include "bignumber.h"

//deixei os prints para conseguir visualizar mais fácil
int main() {
    BigNumber* lista = NULL;

    //Testando adicionar no início
    adicionarInicio(&lista, 3);
    adicionarInicio(&lista, 2);
    adicionarInicio(&lista, 1);
    printf("Lista após adicionar no início: ");
    imprimirLista(lista);

    //Testando adicionar no fim
    adicionarNoFim(&lista, 4);
    adicionarNoFim(&lista, 5);
    printf("Lista após adicionar no fim: ");
    imprimirLista(lista);

    //Testando adicionar antes de um número
    adicionarAntes(&lista, 3, 0);
    printf("Lista após adicionar 0 antes de 3: ");
    imprimirLista(lista);

    //Testando adicionar depois de um número
    adicionarDepois(lista, 3, 7);
    printf("Lista após adicionar 7 depois de 3: ");
    imprimirLista(lista);

    //Testando encontrar um número
    BigNumber* encontrado = encontrarNumero(lista, 7);
    if (encontrado) {
        printf("Número 7 encontrado: %d\n", encontrado->digito);
    } else {
        printf("Número 7 não encontrado.\n");
    }

    //Testando remover um número
    removerNumero(&lista, 7);
    printf("Lista após remover 7: ");
    imprimirLista(lista);

    //Testando contar elementos
    int count = contarElementos(lista);
    printf("Número de elementos na lista: %d\n", count);

    //Liberando memória
    liberaMemoria(lista);
    printf("Memória liberada.\n");

    return 0;
}
