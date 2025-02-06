#include "conjuntos.h"

void add(Conjunto **s, int elem){
    if(isIn(*s, elem))
        return;
    Conjunto *novo = (Conjunto*)malloc(sizeof(Conjunto));
    novo->elem = elem;
    novo->prox = *s;

    *s = novo;
}

bool isEmpty(Conjunto *s){
    return s == NULL;
}

int len(Conjunto *s){
    int count = 0;

    while(s != NULL){
        count++;
        s = s->prox;
    }
    return count;
}

bool isIn(Conjunto *s, int elem){
    while(s != NULL){
        if(s->elem == elem){
            return true;
        }
        s = s->prox;
    }
    return false;
}

bool isNotIn(Conjunto *s, int elem){
    return !isIn(s,elem);
}

bool isDisjoint(Conjunto *s,Conjunto *s2){
    while(s != NULL){
        if(isIn(s2, s->elem))
            return false;
        s = s->prox;
    }
    return true;
}

void remove1(Conjunto **s, int elem){
    Conjunto *prev = NULL;
    Conjunto *current = *s;
    while(current != NULL && current->elem != elem){
        prev = current;
        current = current->prox;
    }
    if(current == NULL)
        return;
    if(prev == NULL)
        *s = current->prox;
    else
        prev->prox = current->prox;
    free(current);
}

int pop(Conjunto **s){
    if(isEmpty(*s))
        return -1;
    Conjunto *temp = *s;
    int elem = temp->elem;
    *s = temp->prox;
    free(temp);
    return elem;
}

void clear1(Conjunto **s){
    while(!isEmpty(*s)){
        pop(s);
    }
}

Conjunto *union1(Conjunto *s, Conjunto *s2){
    Conjunto *result = NULL;
    while(s != NULL){
        add(&result, s->elem);
        s = s->prox;
    }
    while(s2 != NULL){
        add(&result, s2->elem);
        s2 = s2->prox;
    }

    return result;
}

Conjunto *intersection(Conjunto *s, Conjunto *s2){
    Conjunto *result = NULL;
    while(s != NULL){
        if(isIn(s2, s->elem)){
            add(&result, s->elem);
        }
        s = s->prox;
    }
    return result;
}

Conjunto *difference(Conjunto *s, Conjunto *s2){
    Conjunto *result = NULL;

    while(s != NULL){
        if(!isIn(s2, s->elem)){
            add(&result, s->elem);
        }
        s = s->prox;
    }

    return result;
}

Conjunto *symmetric_difference(Conjunto *s, Conjunto *s2){
    Conjunto *result = union1(difference(s,s2),difference(s2,s));
    return result;
}

bool isSubSet(Conjunto *s, Conjunto *s2){
    while(s != NULL){
        if(!isIn(s2, s->elem))
            return false;
        s = s->prox;
    }
    return true;
}

bool isSuperSet(Conjunto *s, Conjunto *s2){
    return isSubSet(s2, s);
}

void copy1(Conjunto *copiado, Conjunto **paste){
    clear1(paste);
    while(copiado != NULL){
        add(paste, copiado->elem);
        copiado = copiado->prox;
    }
}

void print(Conjunto *s){
    printf("{");
    while(s != NULL){
        printf("%d",s->elem);
         if(s->prox != NULL)
            printf(", ");
        s = s->prox;
    }
    printf("}\n");
}
