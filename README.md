# Trabalhos da matéria de Estrutura de Dados

# 1º  Trabalho:

**Objetivo:** 
Implementar a logistica de um simples registrador de medicamentos sendo utilizado a estrutura lista para fazer o armazenamento.
Os dados são armazenados através de um arquivo de entrada txt em que as funções são nomeadas no codigo e escritas para serem lidas diretamente
no arquivo, após isso os dados são reproduzidos em um arquivo de saida também do tipo txt

## *FUNÇÕES*
* `MEDICAMENTO` "NOME" "CODIGO" "VALOR" "DATA""

* `IMPRIME_LISTA`

* `VERIFICA_VALIDADE` "CODIGO"

* `VERIFICA_LISTA` "CODIGO"

* `ORDENA_LISTA_VALIDADE`

* `ORDENA_LISTA_VALOR`

**Descrição das funções:**

**Essas são as funções a serem passadas para o arquivo de entrada e aquelas que possuem itens entre aspas duplas, são aqueles que devem ser passados para que ocorra a leitura de forma
correta para serem registrado na lista**

# 2º Trabalho:

**Objetivo:**
Fazer a implementação do mesmo tema do trabalho 1, no caso de um registrador de medicamentos, porém é necessário fazer a utilização da estrutura de dados árvore binaria, já que a mesma possui um boa complexidade de algoritmo comparada a outros tipos de algoritmo e tipos de estruturas, além da necessidade de aprendizagem desse tipo de estrutura.

## *FUNÇÕES*
**Observação:** As funções utilizadas em ambos os trabalhos 1 & 2 seguem a mesma lógica, porém o trabalho 2 não utiliza de uma função específica de ordenação, já que a mesma ordena os vetores na entrada dos dados, logo não há necessidade de ordenação e se por algum acaso ter a necessidade de ordenar por outro fator/valor, basta implementar a lógica diretamente na função de inserção dos vetores.

* `MEDICAMENTO` "NOME" "CODIGO" "VALOR" "DATA""

* `IMPRIME_ARVORE`

* `RETIRA` "CODIGO"

* `ATUALIZA_PRECO` "CODIGO" "VALOR"

* `VERIFICA_VALIDADE` "DATA"

* `VERIFICA_ARVORE` "CODIGO"

Como descrito no trabalho 1, essas são as funções a serem utilizadas no arquivo de entrada (**entrada.txt**) para fazer o manuseio dos medicamentos no sistema criado
  
# 3º Trabalho

**Objetivo**: Simular uma eleição para o cargo de prefeito, implementada em C, com duas etapas de votação. Este trabalho utiliza conceitos de estruturas de dados para armazenar e manipular informações de eleitores, chapas e votos, e exibir os resultados em um boletim de urna.

## *ESTRUTURA DO PROJETO*
O projeto é organizado em três arquivos principais:

* **`main.c`**: Contém a função principal que executa o fluxo da eleição.
* **`funcoes.c`** e **`funcoes.h`**: Implementam as funções auxiliares para cadastrar chapas, registrar votos, calcular resultados, e exibir o boletim de urna.
* **`boletim_primeiro_turno.txt`**: Arquivo que armazena o boletim de urna do primeiro turno, exibindo informações sobre o total de eleitores, percentuais de votos válidos, brancos, nulos e a contagem de votos para cada chapa.
* **Exemplo de Saída** - Boletim de Urna (Primeiro Turno)
  
O **boletim** de urna para o **primeiro turno** apresenta:

Total de eleitores: 10

Votos válidos: 8 (80.00%)

Votos brancos: 1 (10.00%)

Votos nulos: 1 (10.00%)

Resultados por Chapa:

Chapa A com Vice a: 3 votos (30.00%)

Chapa B com Vice b: 2 votos (20.00%)

Chapa C com Vice c: 3 votos (30.00%)
#
O código está preparado para executar um segundo turno caso nenhuma chapa obtenha mais de 50% dos votos válidos, proporcionando um sistema de votação realista e funcional para fins acadêmicos.

# 4º Trabalho 

## **Objetivo**
O objetivo deste trabalho é a implementação do tipo de dado **conjunto** utilizando a linguagem **C**. Para isso, são fornecidas diversas operações sobre conjuntos, como adição e remoção de elementos, verificação de pertinência, interseção, união, diferença e cópia. O trabalho visa consolidar o conhecimento sobre manipulação de estruturas encadeadas, operações sobre conjuntos e complexidade de algoritmos.

## **Estrutura do Projeto**
O projeto é organizado em três arquivos principais:

- **`main.c`**: Contém a função principal, onde os conjuntos são criados e manipulados utilizando as funções implementadas.
- **`funcoes.c`**: Implementa as funções responsáveis por operar sobre os conjuntos, como inserção, remoção, união, interseção e diferença.
- **`conjuntos.h`**: Arquivo de cabeçalho contendo a estrutura de dados e as assinaturas das funções disponíveis para manipulação de conjuntos.

## **Definição da Estrutura**
A estrutura de dados utilizada é uma **lista encadeada**, onde cada nó contém um elemento do conjunto e um ponteiro para o próximo elemento. A definição da estrutura está no arquivo `conjuntos.h`:

```
struct conju{
    int elem;
    Conjunto *prox;
};
```
Essa estrutura permite a manipulação dinâmica dos conjuntos, otimizando o uso de memória e permitindo operações eficientes sobre os elementos armazenados.

## **Funções Implementadas**
O código fornece diversas operações para manipulação de conjuntos. Abaixo, a descrição das principais funções:

- **`add(Conjunto **s, int elem)`** - Adiciona um elemento ao conjunto, garantindo que ele não seja duplicado.
- **`isEmpty(Conjunto *s)`** - Verifica se um conjunto está vazio.
- **`len(Conjunto *s)`** - Retorna o número de elementos no conjunto.
- **`isIn(Conjunto *s, int elem)`** - Verifica se um elemento pertence ao conjunto.
- **`isNotIn(Conjunto *s, int elem)`** - Verifica se um elemento não pertence ao conjunto.
- **`isDisjoint(Conjunto *s1, Conjunto *s2)`** - Verifica se dois conjuntos são disjuntos.
- **`remove1(Conjunto **s, int elem)`** - Remove um elemento do conjunto, caso ele exista.
- **`pop(Conjunto **s)`** - Remove e retorna um elemento arbitrário do conjunto.
- **`clear1(Conjunto **s)`** - Remove todos os elementos do conjunto.
- **`union1(Conjunto *s, Conjunto *s2)`** - Retorna a união de dois conjuntos.
- **`intersection(Conjunto *s, Conjunto *s2)`** - Retorna a interseção de dois conjuntos.
- **`difference(Conjunto *s, Conjunto *s2)`** - Retorna a diferença entre dois conjuntos.
- **`symmetric_difference(Conjunto *s, Conjunto *s2)`** - Retorna a diferença simétrica entre dois conjuntos.
- **`isSubSet(Conjunto *s, Conjunto *s2)`** - Verifica se um conjunto é subconjunto de outro.
- **`isSuperSet(Conjunto *s, Conjunto *s2)`** - Verifica se um conjunto é superconjunto de outro.
- **`copy1(Conjunto *copiado, Conjunto **paste)`** - Copia os elementos de um conjunto para outro.
- **`print(Conjunto *s)`** - Imprime os elementos do conjunto na tela.

## **Exemplo de Execução**
No arquivo `main.c`, são criados dois conjuntos de exemplo, `set1` e `set2`, para demonstrar a utilização das funções implementadas.
```
Conjunto *set1 = NULL;
Conjunto *set2 = NULL;

add(&set1, 1);
add(&set1, 2);
add(&set1, 3);
add(&set1, 4);
add(&set1, 5);
add(&set1, 6);
printf("Conjunto 1: ");
print(set1);

add(&set2, 3);
add(&set2, 4);
add(&set2, 5);
add(&set2, 6);
printf("Conjunto 2: ");
print(set2);
```

## **Saída Esperada:**
```
Conjunto 1: {1, 2, 3, 4, 5, 6}
Conjunto 2: {3, 4, 5, 6}
```
Outras operações, como união, interseção e diferença, também são demonstradas no código.

## **Conclusão**
O trabalho permitiu a implementação de uma estrutura de dados dinâmica para manipulação de conjuntos, utilizando listas encadeadas. Com isso, foi possível reforçar o conhecimento sobre operações em conjuntos, alocação dinâmica de memória e manipulação de ponteiros. O código implementado oferece uma interface eficiente para lidar com conjuntos, garantindo funcionalidade e flexibilidade no manuseio de elementos.

A abordagem baseada em listas encadeadas possibilitou um uso eficiente da memória e das operações sobre conjuntos, tornando a implementação uma solução robusta para o problema proposto
