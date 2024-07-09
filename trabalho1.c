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

    // Abrindo o arquivo de saída "saida.txt" para escrita
    arqExit = fopen("saida.txt", "w");

    // Instanciação da struct lista
    Lista *med;
    // Criação da lista como nula (não há nada dentro dela inicialmente)
    med = cria_lista();

    // Variáveis para a escolha da função e atribuição dos valores dos medicamentos
    char funcao[50];
    char name[20];
    int code;
    float value;
    int date[3];

    // Loop para ler o arquivo de entrada até o final
    while (fscanf(arq, "%s", funcao) != EOF) {
        // Se a função lida for "MEDICAMENTO"
        if (strcmp(funcao, "MEDICAMENTO") == 0) {
            // Leitura dos valores do medicamento do arquivo de entrada
            fscanf(arq, "%s %d %f %d %d %d", name, &code, &value, &date[0], &date[1], &date[2]);
            // Criação de um novo medicamento passando os valores lidos para a função
            Medicamento* newMedicament = CriaMedicamento(name, code, value, date);
            // Inserção dos valores na lista com a função InsereListaMedicamento
            med = InsereListaMedicamento(arqExit, med, newMedicament);
        }
        // Se a função lida for "RETIRA"
        else if (strcmp(funcao, "RETIRA") == 0) {
            // Leitura do código do medicamento a ser retirado
            fscanf(arq, "%d", &code);
            // Retirada do medicamento da lista
            med = RetiraListaMedicamento(arqExit, med, code);
        }
        // Se a função lida for "IMPRIME_LISTA"
        else if (strcmp(funcao, "IMPRIME_LISTA") == 0) {
            // Impressão da lista de medicamentos
            ImprimeListaMedicamentos(arqExit, med);
        }
        // Se a função lida for "VERIFICA_VALIDADE"
        else if (strcmp(funcao, "VERIFICA_VALIDADE") == 0) {
            // Leitura da data para verificação de validade
            fscanf(arq, "%d %d %d", &date[0], &date[1], &date[2]);
            // Verificação da validade dos medicamentos na lista
            VerificaListaValidade(arqExit, med, date);
        }
        // Se a função lida for "VERIFICA_LISTA"
        else if (strcmp(funcao, "VERIFICA_LISTA") == 0) {
            // Leitura do código do medicamento a ser verificado
            fscanf(arq, "%d", &code);
            // Verificação da presença do medicamento na lista
            VerificaListaMedicamento(arqExit, med, code);
        }
        // Se a função lida for "ORDENA_LISTA_VALIDADE"
        else if (strcmp(funcao, "ORDENA_LISTA_VALIDADE") == 0) {
            // Ordenação da lista de medicamentos por data de validade
            med = OrdenaListaVencimento(med);
        }
        // Se a função lida for "ORDENA_LISTA_VALOR"
        else if (strcmp(funcao, "ORDENA_LISTA_VALOR") == 0) {
            // Ordenação da lista de medicamentos por valor
            med = OrdenaListaValor(med);
        }
    }

    // Liberação da memória alocada para a lista
    Amnesia(med);

    // Fechando os arquivos de entrada e saída
    fclose(arq);
    fclose(arqExit);

    return 0;
}
