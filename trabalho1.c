#include <stdio.h>
#include "estoque.h"

int main()
{
    FILE *arq;
    FILE *arqExit;

    arq = fopen("entrada.txt","r");

        if(arq == NULL){
            printf("Erro\n");
        }

    arqExit = fopen("saida.txt","w");

    //Instanciacao da struct lista
    Lista *med;
    //criacao da lista como nula(nao ha nada dentro dela)
    med = cria_lista();

    //criacao para escolha da funcao e atribuicao dos valores dos medicamentos
    char funcao[50];
    char name[20];
    int code;
    float value;
    int date[3];

    while(fscanf(arq, "%50s", funcao) != EOF){
        if(strcmp(funcao, "MEDICAMENTO")){
            //leitor do arquivo de entrada
            fscanf(arq,"%s %d %f %d %d %d", name, &code, &value, &date[0], &date[1], &date[2]);
            //criacao dos medicamentos passando para a funcao
            Medicamento* newMedicament = CriaMedicamento(name,code,value,date);
            //insere os valores na lista, com a funcao InsereListaMedicamento
            med = InsereListaMedicamento(arqExit,med,newMedicament);
        }

        else if(strcmp(funcao,"RETIRA")){
            fscanf(arq,"%d",&code);
            med = RetiraListaMedicamento(arqExit,med,code);
        }

        else if(strcmp(funcao,"IMPRIME_LISTA")){
            ImprimeListaMedicamentos(arqExit,med);
        }

        else if(strcmp(funcao,"ATUALIZA_PRECO")){
            fscanf(arq,"%d %f", &code,&value);
        }

        else if(strcmp(funcao,"VERIFICA_VALIDADE")){
            fscanf(arq,"%d %d %d", &date[0], &date[1], &date[2]);
            med = VerificaListaValidade(arqExit,med,date);
        }

        else if(strcmp(funcao,"VERIFICA_LISTA")){
            fscanf(arqExit,"%d",&code);
            VerificaListaMedicamento(arqExit,med,code);
        }

        else if(strcmp(funcao,"ORDENA_LISTA_VALIDADE")){
            med = OrdenaListaVencimento(med);
        }

        else if(strcmp(funcao,"ORDENA_LISTA_VALOR") ){
            med = OrdenaListaValor(med);
        }

        else if(strcmp(arq,"FIM")){
            break;
        }
    }
    fclose(arq);
    fclose(arqExit);
    return 0;
}
