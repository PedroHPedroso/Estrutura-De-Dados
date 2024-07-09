#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main() {
    FILE *arq;
    FILE *arqExit;

    // Abrindo o arquivo de entrada "entrada.txt" para leitura
    arq = fopen("entrada.txt", "r");
    if (arq == NULL) {
        printf("Erro\n");
        return 1;
    }

    // Abrindo o arquivo de sa�da "saida.txt" para escrita
    arqExit = fopen("saida.txt", "w");

    // Instancia��o da struct lista
    Lista *med;
    // Cria��o da lista como nula (n�o h� nada dentro dela inicialmente)
    med = cria_lista();

    // Vari�veis para a escolha da fun��o e atribui��o dos valores dos medicamentos
    char funcao[50];
    char name[20];
    int code;
    float value;
    int date[3];

    // Loop para ler o arquivo de entrada at� o final
    while (fscanf(arq, "%s", funcao) != EOF) {
        // Se a fun��o lida for "MEDICAMENTO"
        if (strcmp(funcao, "MEDICAMENTO") == 0) {
            // Leitura dos valores do medicamento do arquivo de entrada
            fscanf(arq, "%s %d %f %d %d %d", name, &code, &value, &date[0], &date[1], &date[2]);
            // Cria��o de um novo medicamento passando os valores lidos para a fun��o
            Medicamento* newMedicament = CriaMedicamento(name, code, value, date);
            // Inser��o dos valores na lista com a fun��o InsereListaMedicamento
            med = InsereListaMedicamento(arqExit, med, newMedicament);
        }
        // Se a fun��o lida for "RETIRA"
        else if (strcmp(funcao, "RETIRA") == 0) {
            // Leitura do c�digo do medicamento a ser retirado
            fscanf(arq, "%d", &code);
            // Retirada do medicamento da lista
            med = RetiraListaMedicamento(arqExit, med, code);
        }
        // Se a fun��o lida for "IMPRIME_LISTA"
        else if (strcmp(funcao, "IMPRIME_LISTA") == 0) {
            // Impress�o da lista de medicamentos
            ImprimeListaMedicamentos(arqExit, med);
        }
        // Se a fun��o lida for "VERIFICA_VALIDADE"
        else if (strcmp(funcao, "VERIFICA_VALIDADE") == 0) {
            // Leitura da data para verifica��o de validade
            fscanf(arq, "%d %d %d", &date[0], &date[1], &date[2]);
            // Verifica��o da validade dos medicamentos na lista
            VerificaListaValidade(arqExit, med, date);
        }
        // Se a fun��o lida for "VERIFICA_LISTA"
        else if (strcmp(funcao, "VERIFICA_LISTA") == 0) {
            // Leitura do c�digo do medicamento a ser verificado
            fscanf(arq, "%d", &code);
            // Verifica��o da presen�a do medicamento na lista
            VerificaListaMedicamento(arqExit, med, code);
        }
        // Se a fun��o lida for "ORDENA_LISTA_VALIDADE"
        else if (strcmp(funcao, "ORDENA_LISTA_VALIDADE") == 0) {
            // Ordena��o da lista de medicamentos por data de validade
            med = OrdenaListaVencimento(med);
        }
        // Se a fun��o lida for "ORDENA_LISTA_VALOR"
        else if (strcmp(funcao, "ORDENA_LISTA_VALOR") == 0) {
            // Ordena��o da lista de medicamentos por valor
            med = OrdenaListaValor(med);
        }
    }

    // Libera��o da mem�ria alocada para a lista
    Amnesia(med);

    // Fechando os arquivos de entrada e sa�da
    fclose(arq);
    fclose(arqExit);

    return 0;
}
