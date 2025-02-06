#ifndef CONJUNTOS_H_INCLUDED
#define CONJUNTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct conju Conjunto;
struct conju{
    int elem;
    Conjunto *prox;
};

void add(Conjunto **s, int elem);
bool isEmpty(Conjunto *s);
int len(Conjunto *s);
bool isIn(Conjunto *s, int elem);
bool isNotIn(Conjunto *s, int elem);
bool isDisjoint(Conjunto *s1, Conjunto *s2);
void remove1(Conjunto **s, int elem);
int pop(Conjunto **s);
void clear1(Conjunto **s);
Conjunto *union1(Conjunto *s, Conjunto *s2);
Conjunto *intersection(Conjunto *s, Conjunto *s2);
Conjunto *difference(Conjunto *s, Conjunto *s2);
Conjunto *symmetric_difference(Conjunto *s, Conjunto *s2);
bool isSubSet(Conjunto *s, Conjunto *s2);
bool isSuperSet(Conjunto *s, Conjunto *s2);
void copy1(Conjunto *copiado, Conjunto **paste);
void print(Conjunto *s);

#endif // CONJUNTOS_H_INCLUDED
