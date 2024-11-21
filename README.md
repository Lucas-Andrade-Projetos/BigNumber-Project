BigNumber Project

Informações dos Membros do Grupo
Lucas Andrade - RA: 11202130442

2. Descrição
O BigNumber Project é uma implementação de um tipo de dado que representa números inteiros extremamente grandes, utilizando uma lista duplamente encadeada para armazenar seus dígitos. O objetivo do projeto é criar uma estrutura de dados capaz de realizar operações aritméticas básicas (+, -, ×, ÷) em números inteiros de qualquer tamanho, sem perder precisão.
Este projeto foi desenvolvido para lidar com números tão grandes quanto a memória do computador permitir, com o foco em aplicabilidade em áreas como criptografia, simulações de grandes dados e outros campos que necessitam de manipulação precisa de grandes números inteiros.

3. Explicação da Organização do Código
O código foi organizado em módulos separados para garantir a clareza e manutenção eficiente:

bignumber.h: Este arquivo contém a interface pública do tipo BigNumber, com a definição das funções para manipulação dos números grandes.
bignumber.c: Implementação da lógica e das operações básicas de manipulação de números inteiros grandes, como adição, subtração, multiplicação e divisão.
client.c: Arquivo contendo a função main(), onde as operações do tipo BigNumber são testadas e demonstradas ao usuário.
makefile: Arquivo de configuração para a construção e compilação do projeto utilizando o comando make.

por enquanto é isso.