#include "conjuntos.h"

int main() {
    Conjunto *set1 = NULL;
    Conjunto *set2 = NULL;

    add(&set1, 1);
    add(&set1, 2);
    add(&set1, 3);
    add(&set1, 4);
    add(&set1, 5);
    add(&set1, 6);
    printf("Conjunto 1: ");
    print(set1);

    add(&set2, 3);
    add(&set2, 4);
    add(&set2, 5);
    add(&set2, 6);
    printf("Conjunto 2: ");
    print(set2);
    printf("\n");

    printf("Conjunto 1 esta vazio? %s\n", isEmpty(set1) ? "Sim" : "Nao");
    printf("Conjunto 2 esta vazio? %s\n", isEmpty(set2) ? "Sim" : "Nao");
    printf("\n");

    printf("Tamanho do Conjunto 1: %d\n", len(set1));
    printf("Tamanho do Conjunto 2: %d\n", len(set2));
    printf("\n");

    printf("Elemento 2 esta no Conjunto 1? %s\n", isIn(set1, 2) ? "Sim" : "Nao");
    printf("Elemento 4 esta no Conjunto 1? %s\n", isNotIn(set1, 4) ? "Nao" : "Sim");
    printf("\n");

    /*printf("Elemento 3 esta no conjunto 2? %s\n",isIn(set2, 3) ? "Sim" : "Nao");
    printf("Elemento nao 4 esta no Conjunto 2? %s\n", isNotIn(set2, 4) ? "Nao" : "Sim");
    printf("\n");*/

    printf("Conjuntos 1 e 2 sao disjuntos? %s\n", isDisjoint(set1, set2) ? "Sim" : "Nao");
    printf("\n");

    /*printf("Removendo 2 do Conjunto 1...\n");
    remove1(&set1, 2);
    printf("Conjunto 1 apos remocao: ");
    print(set1);
    printf("\n");

    printf("Removendo um elemento arbitrario do Conjunto 1: %d\n", pop(&set1));
    printf("Conjunto 1 apos pop: ");
    print(set1);
    printf("\n");*/

    /*printf("Limpando o Conjunto 2...\n");
    clear1(&set2);
    printf("Conjunto 2 apos limpar: ");
    print(set2);
    printf("\n");*/


    Conjunto *ConjuntoUniao = union1(set1, set2);
    printf("Uniao do Conjunto 1 e Conjunto 2: ");
    print(ConjuntoUniao);
    printf("\n");


    Conjunto *ConjuntoIntersecao = intersection(set1, set2);
    printf("Intersecao do Conjunto 1 e Conjunto 2: ");
    print(ConjuntoIntersecao);
    printf("\n");

    //alterar set1 e set2 de posicao
    Conjunto *ConjuntoDiferenca = difference(set1, set2);
    printf("Diferenca do Conjunto 1 e Conjunto 2: ");
    print(ConjuntoDiferenca);
    printf("\n");

    Conjunto *ConjuntoDiferencaSimetric = symmetric_difference(set1, set2);
    printf("Diferenca simetrica do Conjunto 1 e Conjunto 2: ");
    print(ConjuntoDiferencaSimetric);
    printf("\n");


    printf("Conjunto 2 eh subconjunto do Conjunto 1? %s\n", isSubSet(set2, set1) ? "Sim" : "Nao");
    printf("Conjunto 1 eh superconjunto do Conjunto 2? %s\n", isSuperSet(set1, set2) ? "Sim" : "Nao");
    printf("\n");


    Conjunto *ConjuntoCopiado = NULL;
    copy1(set1, &ConjuntoCopiado);
    printf("Copia do Conjunto 1: ");
    print(ConjuntoCopiado);
    printf("\n");

    clear1(&set1);
    printf("Conjunto 1 Limpo: ");
    print(set1);
    printf("\n");

    clear1(&set2);
    printf("Conjunto 2 Limpo: ");
    print(set2);
    printf("\n");

    /*
    clear1(&ConjuntoUniao);
    clear1(&ConjuntoIntersecao);
    clear1(&ConjuntoDiferenca);
    clear1(&ConjuntoDiferencaSimetric);
    clear1(&ConjuntoCopiado);
    */

    return 0;
}
