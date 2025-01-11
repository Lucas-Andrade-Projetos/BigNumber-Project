# BigNumber Project

## Informações dos Membros do Grupo
**Lucas Andrade** - **RA: 11202130442**  
*Todo o trabalho foi feito por mim, então todas as divisões como testes, organização e desenvolvimento foram realizadas por uma pessoa.*

## Descrição
O **BigNumber Project** é uma implementação de um tipo de dado que representa números inteiros extremamente grandes, utilizando uma lista duplamente encadeada para armazenar seus dígitos. O objetivo do projeto é criar uma estrutura de dados capaz de realizar operações aritméticas básicas (+, -, ×, ÷) em números inteiros de qualquer tamanho, sem perder precisão e alguns extras como resto da divisão e exponenciação(%, ^).  
Este projeto foi desenvolvido para lidar com números tão grandes quanto a memória do computador permitir, com foco em aplicabilidade em áreas como criptografia, simulações de grandes dados e outros campos que necessitam de manipulação precisa de grandes números inteiros.

## Explicação da Organização do Código
O código foi organizado em módulos separados para garantir a clareza e manutenção eficiente:

- **bignumber.h**: Este arquivo contém a interface pública do tipo BigNumber, com a definição das funções para manipulação dos números grandes.
- **bignumber.c**: Implementação da lógica e das operações básicas de manipulação de números inteiros grandes, como adição, subtração, multiplicação e divisão.
- **client.c**: Arquivo contendo a função `main()`, onde as operações do tipo BigNumber são testadas e demonstradas ao usuário.
- **makefile**: Arquivo de configuração para a construção e compilação do projeto utilizando o comando `make`.

## Funcionamento
O funcionamento se resume à entrada dos dados, sendo dois BigNumbers e uma operação ( + , - , * , /, %, ^). Em seguida, o método `executar_operacao` é chamado para realizar a regra de sinais e chamar a operação correta para cada passo.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Guia de funções e funcionamento:

### Função `BigNumberStruct* executarOperacao(char operacao, BigNumberStruct* numero1, BigNumberStruct* numero2)`
A função `executarOperacao` é projetada para realizar operações matemáticas ( + , - , * , /, %, ^) entre dois números grandes (`BigNumberStruct`) que podem incluir valores positivos ou negativos. Aqui está uma explicação passo a passo do fluxo da função:

1. **Parâmetros de entrada**
   - `char operacao`: Indica qual operação matemática será executada ( + , - , * , /, %, ^).
   - `BigNumberStruct* numero1`: Primeiro número grande.
   - `BigNumberStruct* numero2`: Segundo número grande.

2. **Variável de saída**
   - `BigNumberStruct* resultado`: Variável que armazenará o resultado da operação.

3. **Operação de adição ( + )**
   - **Ambos positivos**: Se `numero1->sinal == 1` e `numero2->sinal == 1`, a função chama `somaBigNumber` diretamente.
   - **numero1 positivo, numero2 negativo**: Muda o sinal de `numero2` para positivo temporariamente. Chama `subtrairBigNumbers` para calcular a diferença.
   - **numero1 negativo, numero2 positivo**: Muda o sinal de `numero1` para positivo temporariamente. Calcula a subtração invertendo os parâmetros.
   - **Ambos negativos**: Ambos os números são convertidos para positivos temporariamente. Soma os números. Define o sinal do resultado como negativo.

4. **Operação de subtração ( - )**
   - **Ambos positivos**: Chama `subtrairBigNumbers` diretamente.
   - **numero1 positivo, numero2 negativo**: Muda o sinal de `numero2` para positivo temporariamente. Chama `somaBigNumber`.
   - **numero1 negativo, numero2 positivo**: Muda o sinal de `numero1` para positivo temporariamente. Soma os números e define o resultado como negativo.
   - **Ambos negativos**: Ambos os números são convertidos para positivos temporariamente. Calcula a subtração invertendo os parâmetros (numero2 - numero1).

5. **Operação de multiplicação ( * )**
   - **Ambos positivos**: Chama `multiplicarBigNumbers` diretamente, mas reverte os números antes da operação (`reverterBigNumber`).
   - **numero1 positivo, numero2 negativo**: Converte `numero2` para positivo temporariamente. Realiza a multiplicação. Define o sinal do resultado como negativo.
   - **numero1 negativo, numero2 positivo**: Converte `numero1` para positivo temporariamente. Realiza a multiplicação. Define o sinal do resultado como negativo.
   - **Ambos negativos**: Converte ambos para positivos temporariamente. Realiza a multiplicação. O resultado permanece positivo.

6. **Operação de divisão ( / )**
   - **Ambos positivos**: Chama `dividirBigNumbers` diretamente.
   - **numero1 positivo, numero2 negativo**: Muda o sinal de `numero2` para positivo temporariamente. Realiza a divisão. Se o resultado não for zero (verificado pelo primeiro dígito da lista encadeada), define o sinal como negativo.
   - **numero1 negativo, numero2 positivo**: Converte `numero1` para positivo temporariamente. Realiza a divisão. Define o sinal como negativo, caso o resultado não seja zero.
   - **Ambos negativos**: Ambos os números são convertidos para positivos temporariamente. Realiza a divisão. O resultado permanece positivo.

7. **Operação de resto ( % )**
   - **O resultado é sempre positivo**: Chama `restoBigNumber` diretamente e retorna o valor esperado.

8. **Operação de divisão ( ^ )**
   - **Ambos positivos**: Chama `expRapida` diretamente.
   - **numero1 negativo, numero2 positivo entretanto com valor ímpar **: Converte ambos numeros para positivo e realiza o calculo setando por final o número como negativo;
   - **numero1 negativo, numero2 positivo entretanto com valor par **: Converte ambos numeros para positivo e realiza o calculo setando por final o número como positivo;

9. **Retorno do resultado**
   Após realizar a operação apropriada, o `BigNumberStruct* resultado` é retornado, contendo:
   - A lista de dígitos que representa o número calculado;
   - O sinal (1 para positivo, -1 para negativo).

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função `BigNumberStruct* somaBigNumber(BigNumberStruct* numero1, BigNumberStruct* numero2)`
A função `somaBigNumber` é projetada para realizar a soma de dois números grandes que podem incluir valores positivos ou negativos. Aqui está uma explicação passo a passo do fluxo da função:

1. **Parâmetros de entrada**
   - `BigNumberStruct* numero1`: Primeiro número grande.
   - `BigNumberStruct* numero2`: Segundo número grande.

2. **Verificação de sinais dos números**
   - Se os sinais de `numero1` e `numero2` são iguais (ou seja, ambos positivos ou ambos negativos):
     - Cria-se um novo `BigNumberStruct* resultado` para armazenar o valor da soma;
     - Os ponteiros `temp1` e `temp2` são inicializados para percorrer os dígitos de `numero1` e `numero2` a partir do final (último dígito);
     - Variáveis auxiliares `carry`, `digito1` e `digito2` são usadas para controlar a soma e o carry (vai-um).

   - **Loop de soma**:
     - Enquanto existirem dígitos ou um carry pendente, realiza-se a soma dos dígitos de `numero1` e `numero2` (levando em conta o carry);
     - Para cada dígito somado, o carry é calculado (soma / 10) e o dígito do resultado é obtido (soma % 10);
     - O dígito do resultado é adicionado no início da lista de resultado com a função `adicionarInicio`.

   - **Resultado final**:
     - O sinal de resultado é definido igual ao sinal dos números de entrada (`numero1->sinal`).

3. **Se os sinais de `numero1` e `numero2` são diferentes (um é positivo e o outro é negativo)**:
   - O próximo passo depende da comparação entre `numero1` e `numero2`.
   - A função `comparaBigNumbers(numero1, numero2)` é chamada para determinar qual número é maior (com base na magnitude).

   - **Caso `numero1` seja maior ou igual a `numero2`**:
     - A função chama `subtrairBigNumbers(numero1, numero2)` para realizar a subtração entre os números, com o sinal do resultado igual ao de `numero1`.

   - **Caso `numero2` seja maior que `numero1`**:
     - A função chama `subtrairBigNumbers(numero2, numero1)` para realizar a subtração invertida, com o sinal do resultado igual ao de `numero2`.

4. **Retorno do resultado**:
   A função retorna o `BigNumberStruct* resultado`, que contém:
   - A lista de dígitos representando o número calculado (a soma ou a subtração, conforme o caso);
   - O sinal, que pode ser o mesmo que `numero1->sinal` ou `numero2->sinal`, dependendo da operação realizada.
     
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função `BigNumberStruct* subtrairBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2)`

A função `subtrairBigNumbers` é projetada para realizar a subtração de dois números grandes que podem incluir valores positivos ou negativos. Aqui está uma explicação passo a passo do fluxo da função:

1. **Parâmetros de Entrada**
   - `BigNumberStruct* numero1`: Primeiro número grande.
   - `BigNumberStruct* numero2`: Segundo número grande.

2. **Comparação de Números**
A função chama `comparaBigNumbers(numero1, numero2)` para comparar os dois números e determinar qual é o maior.

- **Se `numero1` é maior ou igual a `numero2` (comparacao >= 0)**:
  - `numero1` será considerado o maior e `numero2` o menor.
  
- **Se `numero2` é maior que `numero1` (comparacao < 0)**:
  - `numero2` será considerado o maior e `numero1` o menor.

3. **Inicialização do Resultado**
   - Cria-se uma nova estrutura `BigNumberStruct* resultado` para armazenar o resultado da subtração.
   - Ponteiros `tempMaior` e `tempMenor` são usados para percorrer os dígitos de maior e menor respectivamente, começando do último dígito.

4. **Movimento dos Ponteiros para o Final das Listas**
   - Ambos os ponteiros, `tempMaior` e `tempMenor`, são movidos para o final das listas (últimos dígitos), para facilitar a subtração a partir do final.

5. **Subtração dos Dígitos**
   - Variáveis auxiliares `borrow` (para empréstimo), `digito1` (do maior número) e `digito2` (do menor número) são usadas para controlar a subtração.

### Loop de Subtração
Enquanto houver dígitos ou um empréstimo pendente, realiza-se a subtração.

Para cada dígito:
   - Se `tempMaior` ou `tempMenor` for `NULL`, o dígito correspondente é considerado `0`;
   - A subtração é feita considerando o empréstimo (`borrow`);
   - Se o resultado da subtração for negativo, o valor é ajustado para um número positivo e o empréstimo é marcado (`borrow = 1`);
   - Caso contrário, o empréstimo é resetado (`borrow = 0`);
   - O dígito do resultado é adicionado ao início da lista de resultado usando `adicionarInicio(resultado, subtracao)`.

### Movimento para o Dígito Anterior
Após cada operação, os ponteiros `tempMaior` e `tempMenor` são movidos para os dígitos anteriores.

6. **Definição do Sinal do Resultado**
O sinal de resultado é definido com base na comparação inicial entre os números:

- **Se `numero1` é maior ou igual a `numero2` (comparacao >= 0)**:
  - O sinal de resultado é igual ao de `numero1`.

- **Se `numero2` é maior que `numero1` (comparacao < 0)**:
  - Se `numero2` for positivo (`numero2->sinal == 1`), o sinal de resultado será negativo;
  - Caso contrário, o sinal de resultado será positivo.

7. **Remoção de Zeros à Esquerda**
Após calcular a subtração, `removerZeros(resultado)` é chamada para remover qualquer zero à esquerda do número, garantindo que o formato do número esteja correto.

8. **Retorno do Resultado**
A função retorna o `BigNumberStruct* resultado`, que contém:
   - A lista de dígitos representando o número calculado (a subtração de `numero1` e `numero2`);
   - O sinal do resultado, que é determinado pela comparação dos números de entrada.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função BigNumberStruct* multiplicarBigNumbers(BigNumberStruct* numero1, BigNumberStruct* numero2)

A função multiplicarBigNumbers é projetada para realizar a multiplicação de dois números grandes que podem incluir valores positivos ou negativos. Aqui está uma explicação passo a passo do fluxo da função:

1. **Parâmetros de Entrada**
   - `BigNumberStruct* numero1`: Primeiro número grande.
   - `BigNumberStruct* numero2`: Segundo número grande.

2. **Cálculo do Tamanho dos Números de Entrada**
   - A função começa obtendo o número de dígitos de numero1 e numero2 usando a função contarElementos(numero1) e contarElementos(numero2), respectivamente;
   - tamanho1 é o número de dígitos de numero1, e tamanho2 é o número de dígitos de numero2.

3. **Alocação do Vetor de Resultado**
   - O tamanho máximo do resultado da multiplicação é tamanho1 + tamanho2, pois a multiplicação de dois números com m e n dígitos pode resultar em um número com até m + n dígitos;
   - Um vetor de int chamado resultado é alocado com tamanho resultado_tamanho, e inicializado com zeros.

4. **Multiplicação dos Dígitos dos Números**
   - A função usa dois ponteiros temp1 e temp2 para percorrer os dígitos de numero1 e numero2, respectivamente;
   - A multiplicação é feita de forma semelhante à multiplicação manual.

### Primeiro Loop: Percorre os Dígitos de numero1

### Segundo Loop: Percorre os Dígitos de numero2

#### Multiplicação e Soma:
   - Multiplica o dígito atual de numero1 (temp1->digito) pelo dígito atual de numero2 (temp2->digito);
   - Adiciona o resultado da multiplicação, o valor no vetor resultado[i + j], e o carry (vai-um) do cálculo anterior;
   - O carry é calculado como a parte inteira da divisão por 10 (vai-um) e armazenado;
   - O dígito atual de resultado[i + j] é atualizado com o valor da multiplicação módulo 10;
   - O ponteiro temp2 é movido para o próximo dígito de numero2;
   - Após o segundo loop, o carry (vai-um) é adicionado ao próximo dígito de resultado[i + tamanho2];
   - O ponteiro temp1 é movido para o próximo dígito de numero1.

5. **Remoção de Zeros à Esquerda no Vetor de Resultado**
   - Após a multiplicação de todos os dígitos, a função remove os zeros à esquerda no vetor resultado. Isso é feito verificando se o último dígito do vetor é zero e ajustando o tamanho do resultado.

6. **Criação da Estrutura para o Resultado Final**
   - A função cria uma nova estrutura BigNumberStruct* resultadoStruct para armazenar o resultado da multiplicação;
   - A função percorre o vetor resultado de trás para frente (do último dígito para o primeiro) e adiciona cada dígito à estrutura resultadoStruct usando a função adicionarInicio(resultadoStruct, resultado[k]);
   - A adição é feita do final para o início para garantir que a ordem dos dígitos seja correta.

7. **Liberação da Memória do Vetor Intermediário**
   - Após transferir os dígitos para a estrutura resultadoStruct, o vetor resultado é liberado usando free(resultado).

8. **Reversão do Número e Retorno**
   - Finalmente, a função chama reverterBigNumber(resultadoStruct) para garantir que o número esteja na ordem correta (caso contrário, os dígitos seriam armazenados em ordem invertida);
   - O resultado final é retornado.

9. **Retorno do Resultado**
   A função retorna o BigNumberStruct* resultado, que contém:
   - A lista de dígitos representando o número calculado (a multiplicação de numero1 e numero2);
   - O sinal do resultado, que pode ser determinado com base na multiplicação de sinais dos números de entrada.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função BigNumberStruct* dividirBigNumbers(BigNumberStruct* dividendo, BigNumberStruct* divisor)
A função dividirBigNumbers é projetada para realizar a divisão de dois números grandes que podem incluir valores positivos ou negativos. Aqui está uma explicação passo a passo do fluxo da função:

1. **Parâmetros de Entrada**
   - `BigNumberStruct* dividendo`: O número que será dividido.
   - `BigNumberStruct* divisor`: O número que dividirá o dividendo.

2. **Verificação de Divisão por Zero**
   - A função começa verificando se o divisor é zero;
   - Se o divisor for zero (ou seja, se o primeiro dígito do divisor for 0 ou se a lista estiver vazia), a função imprime uma mensagem de erro e retorna NULL para indicar que a divisão não pode ser realizada.

3. **Criação das Estruturas para o Quociente e Resto**
   - `BigNumberStruct* quociente`: Uma nova estrutura é criada para armazenar o quociente da divisão;
   - `BigNumberStruct* resto`: Uma nova estrutura é criada para armazenar o resto da divisão.

4. **Inicialização do Ponteiro para o Dividendo**
   - Um ponteiro temp é inicializado apontando para o primeiro dígito do dividendo.

5. **Laço de Divisão**
   #### `Adição do Dígito ao Resto`
      - O dígito atual de temp (do dividendo) é adicionado ao resto usando a função adicionarNoFim(resto, temp->digito);
      - Em seguida, os zeros à esquerda são removidos no resto usando a função removerZeros(resto).

   #### `Contagem de Quantas Vezes o Divisor Cabe no Resto`
      - A função entra em um laço while (comparaBigNumbers(resto, divisor) >= 0), que verifica se o resto é maior ou igual ao divisor;
      - Enquanto o divisor couber no resto, o divisor é subtraído do resto usando a função subtrairBigNumbers(resto, divisor). O resto é atualizado com o resultado da subtração;
      - O contador count é incrementado a cada subtração, contando quantas vezes o divisor cabe no resto.

   #### `Adição do Resultado ao Quociente`
      - O valor do contador count (que representa o número de vezes que o divisor coube no resto) é adicionado ao quociente usando adicionarNoFim(quociente, count).

   #### `Movimento para o Próximo Dígito do Dividendo`
      - O ponteiro temp é movido para o próximo dígito do dividendo (i.e., temp = temp->next).

6. **Remoção de Zeros à Esquerda no Quociente**
   - Após o laço, removerZeros(quociente) é chamado para remover zeros à esquerda no quociente, garantindo que o número esteja no formato correto.

7. **Definição do Sinal do Quociente**
   - Se o quociente for zero (ou seja, se ele não contiver nenhum dígito ou tiver apenas um dígito zero), o sinal do quociente é definido como positivo.

8. **Liberação da Memória do Resto**
   - A memória usada pelo resto é liberada com a função liberaMemoria(resto).

9. **Retorno do Resultado**
A função retorna BigNumberStruct* quociente, que contém:
    - A lista de dígitos representando o quociente da divisão;
    - O sinal do quociente, que será ajustado dependendo do resultado da divisão (caso o quociente seja zero, o sinal será ajustado como positivo).

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função BigNumberStruct* restoBigNumber(BigNumberStruct* numero1, BigNumberStruct* divisor)
A função restoBigNumber é projetada para realizar a devolutiva do resto de uma divisão de dois bignumbers:

1. **Parâmetros de Entrada**
   - `BigNumberStruct* dividendo`: O número do qual será calculado o resto (dividendo).
   - `BigNumberStruct* divisor`: O número pelo qual numero1 será dividido (divisor).

2. **Inicialização**
   - Criar estrutura para o resultado do resto:
     - Inicializa um novo BigNumberStruct chamado resto usando a função criarBigNumber;
     - Este será o valor retornado ao final da função.  
   - Criar uma cópia do dividendo:
     - Cria um novo BigNumberStruct chamado dividendo usando criarBigNumber;
     - Copia todos os dígitos de numero1 para dividendo:
       - Itera pela lista de dígitos em numero1->head e adiciona cada dígito no final de dividendo usando adicionarNoFim.

3. **Loop de subtração**
   - A lógica aqui baseia-se em subtrair repetidamente o divisor do dividendo até que o dividendo se torne menor que o divisor.
   - Verificar se o dividendo é maior ou igual ao divisor:
     - A condição do while usa a função comparaBigNumbers para comparar os dois números;
     - comparaBigNumbers retorna um valor >= 0 se o dividendo for maior ou igual ao divisor.
   - Subtrair divisor do dividendo:
     - Chama subtrairBigNumbers(dividendo, divisor) para calcular a diferença;
     - Libera a memória do antigo dividendo para evitar vazamento de memória (liberaMemoria(dividendo));
     - Atualiza o dividendo com o resultado da subtração.

4. **Resto calculado**
   - Restante no dividendo é o resto:
    - O loop termina quando o dividendo for menor que o divisor;
    - Copia os dígitos restantes no dividendo para o resto:
     - Itera sobre a lista encadeada de dígitos em dividendo->head e adiciona cada dígito no final de resto usando adicionarNoFim.
   - Liberar memória do dividendo:
    - Após usar os valores restantes de dividendo, chama liberaMemoria(dividendo) para liberar a memória alocada.

5. **Retorno do Resultado**
   - Retorna o BigNumberStruct* resto, que contém o valor do resto da divisão de numero1 por divisor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Função BigNumberStruct* expRapida(BigNumberStruct* base, BigNumberStruct* exp)
A função expRapida é projetada para realizar a exponenciação de dois bignumbers sendo b >= 0:

1. **Parâmetros de Entrada**
   - `BigNumberStruct* base`: O número base a ser elevado à potência.
   - `BigNumberStruct* exp`: O expoente ao qual a base será elevada.

2. **Caso base (condição inicial)**
   - Verificar se o expoente é zero:
     - Se o expoente (exp) for 0, a função retorna imediatamente 1;
     - Cria um novo BigNumberStruct com o valor 1 usando criarBigNumberDeNumero(1).

3. **Inicialização**
   - Resultado inicializado como 1:
    - Um BigNumberStruct chamado resultado é criado com o valor inicial 1.
   - Copia os dígitos da base para baseAtual:
     - Um novo BigNumberStruct chamado baseAtual é criado;
     - Itera sobre os dígitos de base->head e os copia para baseAtual usando adicionarNoFim.
   - Cria os BigNumbers auxiliares:
     - zero é criado como BigNumberStruct com valor 0.
     - dois é criado como BigNumberStruct com valor 2.

4. **Loop principal**
   - O loop continua enquanto o expoente (exp) for maior que 0:
    - Verificar se o expoente é ímpar.
    - Usa a função restoBigNumber(exp, dois) para obter o resto.
    - Se o resto for 1 (expoente ímpar), multiplica o resultado atual pelo valor da base:
      - Chama multiplicarBigNumbers para calcular resultado * baseAtual;
      - Libera a memória do resultado antigo e atualiza-o com o novo valor.
   - Atualizar baseAtual:
    - Calcula o quadrado da base atual;
    - Usa multiplicarBigNumbers(baseAtual, baseAtual) para calcular baseAtual^2;
    - Libera a memória da base antiga e atualiza baseAtual com o novo valor.
   - Atualizar exp:
     - Divide o expoente por 2;
     - Usa dividirBigNumbers(exp, dois) para calcular exp / 2;
     - Libera a memória do expoente antigo e atualiza exp com o novo valor.
   - Libera a memória do resto calculado.

6. **Retorno do Resultado**
   - Libera a memória de baseAtual, zero, e dois e Retorna o BigNumberStruct* resultado, que contém o valor calculado de base^exp.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------