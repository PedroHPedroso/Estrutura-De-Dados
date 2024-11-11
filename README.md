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
  
# Trabalho 3

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
