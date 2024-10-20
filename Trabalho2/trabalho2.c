#include "estoque.h"

int main() {
    // Abre o arquivo "entrada.txt" para leitura
    FILE* arq = fopen("entrada.txt", "r");

    // Abre o arquivo "saida.txt" para escrita (onde os resultados ser�o salvos)
    FILE* arqExit = fopen("saida.txt", "w+");

    // Declara um ponteiro para a �rvore que armazenar� os medicamentos
    Arvore *ar;

    // Vari�veis que armazenar�o os dados lidos do arquivo de entrada
    char funcao[50];    // Nome da fun��o que ser� executada (como "MEDICAMENTO", "RETIRA", etc.)
    char nome[20];      // Nome do medicamento
    int codigo;         // C�digo do medicamento
    float valor;        // Valor (pre�o) do medicamento
    int data[3];        // Data de validade (dia, m�s, ano) do medicamento

    // Inicializa a �rvore como vazia
    ar = criaArvore();

    // L� cada linha do arquivo de entrada at� o final do arquivo
    while (fscanf(arq, "%s", funcao) != EOF) {
        // Verifica qual fun��o foi lida e executa a a��o correspondente

        // Se a fun��o for "MEDICAMENTO", insere um novo medicamento na �rvore
        if (strcmp(funcao, "MEDICAMENTO") == 0) {
            // L� o nome, c�digo, valor e data de validade do medicamento
            fscanf(arq, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);

            // Cria um novo medicamento com os dados lidos
            Medicamento *novoMedicamento = criaMedicamento(nome, codigo, valor, data);

            // Insere o novo medicamento na �rvore
            ar = insereArvoreMedicamento(ar, novoMedicamento);

            // Escreve no arquivo de sa�da que o medicamento foi adicionado
            fprintf(arqExit, "MEDICAMENTO %s %d ADICIONADO!\n", nome, codigo);
        }

        // Se a fun��o for "RETIRA", remove um medicamento da �rvore
        else if (strcmp(funcao, "RETIRA") == 0) {
            // L� o c�digo do medicamento a ser removido
            fscanf(arq, "%d", &codigo);

            // Remove o medicamento da �rvore pelo c�digo
            ar = retiraArvoreMedicamento(ar, codigo);

            // Escreve no arquivo de sa�da que o medicamento foi retirado
            fprintf(arqExit, "MEDICAMENTO %d RETIRADO\n", codigo);
        }

        // Se a fun��o for "IMPRIME_ARVORE", imprime todos os medicamentos da �rvore
        else if (strcmp(funcao, "IMPRIME_ARVORE") == 0) {
            // Imprime a �rvore de forma ordenada no arquivo de sa�da
            imprimeArvore(arqExit, ar);
        }

        // Se a fun��o for "ATUALIZA_PRECO", atualiza o pre�o de um medicamento
        else if (strcmp(funcao, "ATUALIZA_PRECO") == 0) {
            // L� o c�digo do medicamento e o novo valor
            fscanf(arq, "%d %f", &codigo, &valor);

            // Atualiza o pre�o do medicamento na �rvore
            atualizaPrecoMedicamento(ar, codigo, valor);

            // Escreve no arquivo de sa�da que o pre�o foi atualizado
            fprintf(arqExit, "PRECO ATUALIZADO %d %.1f\n", codigo, valor);
        }

        // Se a fun��o for "VERIFICA_VALIDADE", verifica se algum medicamento est� vencido
        else if (strcmp(funcao, "VERIFICA_VALIDADE") == 0) {
            // L� a data de validade para a compara��o (dia, m�s, ano)
            fscanf(arq, "%d %d %d", &data[0], &data[1], &data[2]);

            // Verifica na �rvore se algum medicamento est� vencido
            int resultado = VerificaArvoreValidade(arqExit, ar, data);

            // Se nenhum medicamento estiver vencido, escreve no arquivo de sa�da
            if (resultado == 0) {
                fprintf(arqExit, "NENHUM MEDICAMENTO VENCIDO\n");
            }
        }

        // Se a fun��o for "VERIFICA_ARVORE", verifica se um medicamento est� presente na �rvore
        else if (strcmp(funcao, "VERIFICA_ARVORE") == 0) {
            // L� o c�digo do medicamento a ser verificado
            fscanf(arq, "%d", &codigo);

            // Verifica se o medicamento est� na �rvore
            int encontrado = verificaArvoreMedicamento(ar, codigo);

            // Escreve no arquivo de sa�da se o medicamento foi encontrado ou n�o
            if (encontrado) {
                fprintf(arqExit, "MEDICAMENTO %d ENCONTRADO\n", codigo);
            } else {
                fprintf(arqExit, "MEDICAMENTO %d NAO ENCONTRADO NA ARVORE\n", codigo);
            }
        }
    }

    // Fecha os arquivos de entrada e sa�da
    fclose(arq);
    fclose(arqExit);

    // Libera toda a mem�ria alocada para a �rvore
    liberaArvore(ar);
    printf("Liberado a memoria alocada!\n");

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}
