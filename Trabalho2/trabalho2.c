#include "estoque.h"

int main() {
    // Abre o arquivo "entrada.txt" para leitura
    FILE* arq = fopen("entrada.txt", "r");

    // Abre o arquivo "saida.txt" para escrita (onde os resultados serão salvos)
    FILE* arqExit = fopen("saida.txt", "w+");

    // Declara um ponteiro para a árvore que armazenará os medicamentos
    Arvore *ar;

    // Variáveis que armazenarão os dados lidos do arquivo de entrada
    char funcao[50];    // Nome da função que será executada (como "MEDICAMENTO", "RETIRA", etc.)
    char nome[20];      // Nome do medicamento
    int codigo;         // Código do medicamento
    float valor;        // Valor (preço) do medicamento
    int data[3];        // Data de validade (dia, mês, ano) do medicamento

    // Inicializa a árvore como vazia
    ar = criaArvore();

    // Lê cada linha do arquivo de entrada até o final do arquivo
    while (fscanf(arq, "%s", funcao) != EOF) {
        // Verifica qual função foi lida e executa a ação correspondente

        // Se a função for "MEDICAMENTO", insere um novo medicamento na árvore
        if (strcmp(funcao, "MEDICAMENTO") == 0) {
            // Lê o nome, código, valor e data de validade do medicamento
            fscanf(arq, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);

            // Cria um novo medicamento com os dados lidos
            Medicamento *novoMedicamento = criaMedicamento(nome, codigo, valor, data);

            // Insere o novo medicamento na árvore
            ar = insereArvoreMedicamento(ar, novoMedicamento);

            // Escreve no arquivo de saída que o medicamento foi adicionado
            fprintf(arqExit, "MEDICAMENTO %s %d ADICIONADO!\n", nome, codigo);
        }

        // Se a função for "RETIRA", remove um medicamento da árvore
        else if (strcmp(funcao, "RETIRA") == 0) {
            // Lê o código do medicamento a ser removido
            fscanf(arq, "%d", &codigo);

            // Remove o medicamento da árvore pelo código
            ar = retiraArvoreMedicamento(ar, codigo);

            // Escreve no arquivo de saída que o medicamento foi retirado
            fprintf(arqExit, "MEDICAMENTO %d RETIRADO\n", codigo);
        }

        // Se a função for "IMPRIME_ARVORE", imprime todos os medicamentos da árvore
        else if (strcmp(funcao, "IMPRIME_ARVORE") == 0) {
            // Imprime a árvore de forma ordenada no arquivo de saída
            imprimeArvore(arqExit, ar);
        }

        // Se a função for "ATUALIZA_PRECO", atualiza o preço de um medicamento
        else if (strcmp(funcao, "ATUALIZA_PRECO") == 0) {
            // Lê o código do medicamento e o novo valor
            fscanf(arq, "%d %f", &codigo, &valor);

            // Atualiza o preço do medicamento na árvore
            atualizaPrecoMedicamento(ar, codigo, valor);

            // Escreve no arquivo de saída que o preço foi atualizado
            fprintf(arqExit, "PRECO ATUALIZADO %d %.1f\n", codigo, valor);
        }

        // Se a função for "VERIFICA_VALIDADE", verifica se algum medicamento está vencido
        else if (strcmp(funcao, "VERIFICA_VALIDADE") == 0) {
            // Lê a data de validade para a comparação (dia, mês, ano)
            fscanf(arq, "%d %d %d", &data[0], &data[1], &data[2]);

            // Verifica na árvore se algum medicamento está vencido
            int resultado = VerificaArvoreValidade(arqExit, ar, data);

            // Se nenhum medicamento estiver vencido, escreve no arquivo de saída
            if (resultado == 0) {
                fprintf(arqExit, "NENHUM MEDICAMENTO VENCIDO\n");
            }
        }

        // Se a função for "VERIFICA_ARVORE", verifica se um medicamento está presente na árvore
        else if (strcmp(funcao, "VERIFICA_ARVORE") == 0) {
            // Lê o código do medicamento a ser verificado
            fscanf(arq, "%d", &codigo);

            // Verifica se o medicamento está na árvore
            int encontrado = verificaArvoreMedicamento(ar, codigo);

            // Escreve no arquivo de saída se o medicamento foi encontrado ou não
            if (encontrado) {
                fprintf(arqExit, "MEDICAMENTO %d ENCONTRADO\n", codigo);
            } else {
                fprintf(arqExit, "MEDICAMENTO %d NAO ENCONTRADO NA ARVORE\n", codigo);
            }
        }
    }

    // Fecha os arquivos de entrada e saída
    fclose(arq);
    fclose(arqExit);

    // Libera toda a memória alocada para a árvore
    liberaArvore(ar);
    printf("Liberado a memoria alocada!\n");

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}
