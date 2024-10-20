#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipo que define o medicamento
typedef struct medicamento Medicamento;
//Tipo que define arvore
typedef struct arvore Arvore;

//Cria um novo medicamento
Medicamento *criaMedicamento(char* nome, int codigo, float valor, int *data_de_validade);
//Cria uma arvore vazia;
Arvore *criaArvore();
//Insere um medicamento pelo codigo na arvore
Arvore *insereArvoreMedicamento(Arvore *a, Medicamento *m);
//Retira um medicamento de uma determinada arvore
Arvore *retiraArvoreMedicamento(Arvore *a, int id_medicamento);
//Verifica se um medicamento esta presente em uma determinada arvore
int verificaArvoreMedicamento(Arvore *a, int id_medicamento);
//Verifica se existe um medicamento vencido em uma determinada arvore
int verificaArvoreValidade(FILE *fp, Arvore *a, int *data);
//Imprime em ordem pelo codigo todos os medicamentos de uma arvore(em ordem)
void imprimeArvoreMedicamentos(Arvore *a);
//Atualiza o preco do medicamento com base no codigo e no valor novo
void atualizaPrecoMedicamento(Arvore *a, int id_medicamento, float value);
//Libera a memoria alocada pela arvore
void liberaArvore(Arvore *a);


#endif // ESTOQUE_H_INCLUDED
