#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CHAPAS 99
#define MIN_ELEITORES_SEGUNDO_TURNO 10

typedef struct Chapa {
    char nomePrefeito[50];
    char nomeVice[50];
    int dataNascimento[3];
    int numPartido;
    int votos;
} Chapa;

typedef struct Tree {
    Chapa *chapa;
    struct Tree *esquerda;
    struct Tree *direita;
} Tree;

Chapa* criaChapa(char* nomePrefeito, char* nomeVice, int numPartido, int* data);
Tree* criaArvore();
Tree* insereChapa(Tree *t, Chapa *ch);
void exibeChapas(Tree *t);
Chapa* buscaChapa(Tree *t, int numPartido);
void votacao(Tree *t, int *brancos, int *nulos, int numEleitores);
int totalVotosValidos(Tree *t);
void salvaBoletim(Tree *t, int brancos, int nulos, int totalEleitores, const char* nomeArquivo);
int maiorNumeroDeVotos(Tree *t);
int calculaSegundoTurno(int votosValidos, int maiorVotos, int numEleitores);
void limpaTela();
void segundoTurno(Tree *t,int numEleitores);

#endif
