#include <stdio.h>
#include "estoque.h"

Lista *cria_lista(void){
    return NULL;
}
//------------------------------------------------------------------------------------------------//
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade){
    Medicamento *novo =(Medicamento*)malloc(sizeof(Medicamento));

    strcpy(novo->nome,nome);
    novo->codigo = codigo;
    novo->valor = valor;

    for(int i = 0; i < 3; i++){
        novo->data[i] = data_de_validade[i];
    }

    return novo;
}
//--------------------------------------------------------------//
Lista *InsereListaMedicamento(FILE *fp,Lista *l,Medicamento *n){
    Lista *lst = (Lista*)malloc(sizeof(Lista));

    lst->m = n;
    lst->prox = l;
    fprintf(fp,"Medicamento %s com o codigo %d adicionado a lista.\n",n->nome,n->codigo);

    return lst;
}
//------------------------------------------------------------------//
Lista *RetiraListaMedicamento(FILE *fp,Lista *l,int id_medicamento){
    Lista *ant = NULL;
    Lista *p = l;

    while (p != NULL && p->m->codigo != 0){
        ant = p;
        p = p->prox->m;
    }
    if(p == NULL){
        fprintf(fp,"\nCODIGO DO MEDICAMENTO INVALIDO OU NAO ENCONTRADO\n");
        return l->m;
    }
    if(ant == NULL){
        l = p->prox->m;
        fprintf(fp,"MEDICAMENTO %s REMOVIDO\n",l->m->nome);
    }
    else{
        ant->prox->m = p->prox->m;
        fprintf(fp,"MEDICAMENTO %s REMOVIDO\n",l->m->nome);
    }
    free(p->m);
    free(p);
    return l;
}
//-----------------------------------------------------------------//
void ImprimeListaMedicamentos(FILE *fp, Lista *p){
    Lista *lst = p;
    if(p == NULL){
        fprintf(fp,"NAO HA MEDICAMENTOS NA LISTA.\n");
    }
    while(lst != NULL){
        fprintf(fp,"%s\t%d\tR$ %.2f\tVALIDADE:%d/%d/%d\n",lst->m->nome,lst->m->codigo,lst->m->valor,lst->m->data[0],lst->m->data[1],lst->m->data[2]);
        lst = lst->prox;
    }
}
//----------------------------------------------------------------//
int VerificaListaMedicamento(FILE *fp,Lista *p,int id_medicamento){
    while(p != NULL){
        if(p->prox->m->codigo == id_medicamento){
            fprintf(fp,"MEDICAMENTO %s CORRESPONDENTE AO CODIGO %d ENCONTRADO NA LISTA\n",p->m->nome,p->m->codigo);
            return 1;
        }
        p = p->prox;
    }
    fprintf(fp,"MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
    return 0;
}
//---------------------------------------------------------//
int VerificaListaValidade(FILE *fp,Lista *p, int *dataDeValidade){
    Lista *l = p;

    while(l != NULL){
        if(l->m->data[2] < dataDeValidade[2] ||
           (l->m->data[2] == dataDeValidade[2] && l->m->data[1] < dataDeValidade[1]) ||
           (l->m->data[2] == dataDeValidade[2] && l->m->data[1] == dataDeValidade[1] && l->m->data[0] < dataDeValidade[0])){
            fprintf(fp,"MEDICAMENTO %s %d VENCIDO\n",l ->m->nome,l->m->codigo);
            return NULL;
        }
        l = l->prox;
    }
    if(l = NULL){
        fprintf(fp,"MEDICAMENTO VENCIDO NAO ENCONTRADO NA LISTA\n");
    }
    return p;
}
//--------------------------------//
Lista *OrdenaListaValor(Lista *p){
    Lista *lst = p;
    Medicamento *temp = p->m;

    while(lst->prox != NULL){
        Lista *mV = lst;
        Lista *i = lst->prox;

        while(i != NULL){
            if(i->m->valor < mV->m->valor){
                mV = i;
            }
            i = i->prox;
        }
        lst->m = mV->m;
        mV->m = temp;

        lst = lst->prox;
    }
    return p;
}
//-------------------------------------//
Lista *OrdenaListaVencimento(Lista *p){
Lista* lst = p;
Medicamento* temp = lst->m;

    while(lst->prox != NULL){
        Lista *menorData = lst;
        Lista *temporario = lst->prox;

        while(temporario != NULL){
            if(temporario->m->data[2]<menorData->m->data[2] ||
               (temporario->m->data[2] == menorData->m->data[2] && temporario->m->data[1] < menorData->m->data[1]) ||
               (temporario->m->data[2] == menorData->m->data[2] && temporario->m->data[1] == menorData->m->data[1] && temporario->m->data[0] < menorData->m->data[0])){
                menorData = temporario;
               }
               temporario = temporario->prox;
        }
        lst->m = menorData->m;
        lst->m = temp;

        lst = lst->prox;
    }
    return p;
}
