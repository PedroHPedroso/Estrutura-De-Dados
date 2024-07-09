#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

//define a struct medicamento
typedef struct medicamento Medicamento;

//define os medicamentos dentro da struct
struct medicamento{
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};
//define a struct Lista
typedef struct lista Lista;

//struct lista com ponteiro struct medicamento e ponteiro struct lista
struct lista{
    Medicamento *m;
    Lista *prox;
};

//Cria a lista em um ponteiro vazio(do tipo struct Lista)
Lista *cria_lista(void);
//Funcao para criar os medicamentos
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade);
//Insere um medicamento na lista
Lista *InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *n);
//Retira um elemento pelo codigo da lista
Lista *RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento);
//Verifica se existe um medicamento vencido em uma determinada lista
int VerificaListaMedicamento(FILE *fp, Lista *p, int id_medicamento);
//Verifica a data de validade da mais perto de vencer para a mais longe de vencer
int VerificaListaValidade(FILE *fp, Lista *p, int *data);
//Imprime a lista de medicamentos
void ImprimeListaMedicamentos(FILE *fp, Lista *p);
//Ordena a lista por valor
Lista *OrdenaListaValor(Lista *p);
//Ordena a lista por data de vencimento
Lista *OrdenaListaVencimento(Lista *p);
//Funcao para liberar o espaco alocado
void Amnesia(Lista *l);

#endif // ESTOQUE_H_INCLUDED
