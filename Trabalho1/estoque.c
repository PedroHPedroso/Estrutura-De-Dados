#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

Lista *cria_lista(void) {
    return NULL;
}
//------------------------------------------------------------------------------------------------//
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade) {
    // Criação dos medicamentos através do ponteiro novo(struct medicamento), onde deve apontar para os valores a serem atribuídos
    Medicamento *novo = (Medicamento *)malloc(sizeof(Medicamento));
    // Copiando o nome do medicamento para o campo nome da struct medicamento
    strcpy(novo->nome, nome);
    // Atribuindo os valores para os campos código e valor
    novo->codigo = codigo;
    novo->valor = valor;
    // Passando as datas no sentido DD/MM/AA
    for (int i = 0; i < 3; i++) {
        novo->data[i] = data_de_validade[i];
    }

    // Retorna os valores com a struct preenchida
    return novo;
}
//--------------------------------------------------------------//
Lista *InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *n) {
    // Criação de um ponteiro para a struct lista para fazer a atribuição na lista
    Lista *lst = (Lista *)malloc(sizeof(Lista));
    // Ponteiro lista apontando para a variável do tipo medicamento dentro da struct lista e atribuindo a lista recebida como parâmetro
    lst->m = n;
    // Setando o próximo elemento a ser preenchido
    lst->prox = l;
    fprintf(fp, "MEDICAMENTO %s  %d ADICIONADO.\n", n->nome, n->codigo);

    // Retornando a lista de medicamento preenchida
    return lst;
}
//------------------------------------------------------------------//
Lista *RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento) {
    // Variável para armazenar o ponteiro anterior na lista
    Lista *ant = NULL;
    // Variável para percorrer a lista
    Lista *p = l;

    fprintf(fp, "\n");
    // Percorrendo a lista até encontrar o medicamento com o código especificado
    while (p != NULL && p->m->codigo != id_medicamento) {
        ant = p;
        p = p->prox;
    }

    // Se não encontrou o medicamento
    if (p == NULL) {
        fprintf(fp, "CODIGO DO MEDICAMENTO INVALIDO OU NAO ENCONTRADO\n");
        return l;
    }

    // Se o medicamento a ser removido é o primeiro da lista
    if (ant == NULL) {
        l = p->prox;
    } else {
        // Se o medicamento a ser removido não é o primeiro
        ant->prox = p->prox;
    }

    fprintf(fp, "MEDICAMENTO %s REMOVIDO\n", p->m->nome);
    // Liberando a memória do medicamento e do nó da lista
    free(p->m);
    free(p);
    return l;
}

//-----------------------------------------------------------------//
void ImprimeListaMedicamentos(FILE *fp, Lista *p) {
    Lista *lst = p;
    if (p == NULL) {
        fprintf(fp, "NAO HA MEDICAMENTOS NA LISTA.\n");
    }
    fprintf(fp, "\n");
    // Percorrendo a lista e imprimindo os medicamentos
    while (lst != NULL) {
        fprintf(fp, "%s\t%d\tR$ %.2f\tVALIDADE:%d/%d/%d\n", lst->m->nome, lst->m->codigo, lst->m->valor, lst->m->data[0], lst->m->data[1], lst->m->data[2]);
        lst = lst->prox;
    }
}
//----------------------------------------------------------------//
int VerificaListaMedicamento(FILE *fp, Lista *p, int id_medicamento) {
    Lista *aux = p;

    fprintf(fp, "\n");

    // Percorrendo a lista para verificar se o medicamento está presente
    while (aux != NULL) {
        if (aux->m->codigo == id_medicamento) {
            fprintf(fp, "MEDICAMENTO %s ENCONTRADO.\n", aux->m->nome);
            return 1;  // Medicamento encontrado
        }
        aux = aux->prox;
    }
    fprintf(fp, "MEDICAMENTO DO CODIGO %d NAO ENCONTRADO.\n", id_medicamento);
    return 0;  // Medicamento não encontrado
}
//---------------------------------------------------------//
int VerificaListaValidade(FILE *fp, Lista *p, int *dataDeValidade) {
    Lista *l = p;
    int encontrado = 0;

    fprintf(fp, "\n");
    // Percorrendo a lista para verificar medicamentos vencidos
    while (l != NULL) {
        // Comparando as datas de validade
        if (l->m->data[2] < dataDeValidade[2] ||
            (l->m->data[2] == dataDeValidade[2] && l->m->data[1] < dataDeValidade[1]) ||
            (l->m->data[2] == dataDeValidade[2] && l->m->data[1] == dataDeValidade[1] && l->m->data[0] < dataDeValidade[0])) {
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", l->m->nome, l->m->codigo);
            encontrado = 1;
        }
        l = l->prox;
    }

    if (!encontrado) {
        fprintf(fp, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA LISTA\n");
    }

    return encontrado;
}
//--------------------------------//
Lista *OrdenaListaValor(Lista *p) {
    Lista *lst = p;
    // Loop para percorrer a lista
    while (lst != NULL) {
        Lista *mV = lst;
        Lista *i = lst->prox;

        // Loop interno para encontrar o menor valor na lista
        while (i != NULL) {
            if (i->m->valor < mV->m->valor) {
                mV = i;
            }
            i = i->prox;
        }

        // Troca de medicamentos
        if (mV != lst) {
            Medicamento *temp = lst->m;
            lst->m = mV->m;
            mV->m = temp;
        }

        lst = lst->prox;
    }
    return p;
}
//-------------------------------------//
Lista *OrdenaListaVencimento(Lista *p) {
    Lista *lst = p;

    // Loop para percorrer a lista
    while (lst != NULL) {
        Lista *menorData = lst;
        Lista *temporario = lst->prox;

        // Loop interno para encontrar a menor data de vencimento na lista
        while (temporario != NULL) {
            if (temporario->m->data[2] < menorData->m->data[2] ||
                (temporario->m->data[2] == menorData->m->data[2] && temporario->m->data[1] < menorData->m->data[1]) ||
                (temporario->m->data[2] == menorData->m->data[2] && temporario->m->data[1] == menorData->m->data[1] && temporario->m->data[0] < menorData->m->data[0])) {
                menorData = temporario;
            }
            temporario = temporario->prox;
        }

        // Troca de medicamentos
        if (menorData != lst) {
            Medicamento *temp = lst->m;
            lst->m = menorData->m;
            menorData->m = temp;
        }

        lst = lst->prox;
    }
    return p;
}
//--------------------------------------//
void Amnesia(Lista *l) {
    Lista *p = l;
    // Percorrendo a lista e liberando a memória de cada nó
    while (p != NULL) {
        Lista *t = p->prox;
        free(p->m);
        free(p);
        p = t;
    }
    printf("FOI LIMPO\n");
}
