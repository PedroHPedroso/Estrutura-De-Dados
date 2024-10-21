#include "funcoes.h"

Chapa* criaChapa(char* nomePrefeito, char* nomeVice, int numPartido, int* data) {
    Chapa *novo = (Chapa*)malloc(sizeof(Chapa));

    strcpy(novo->nomePrefeito, nomePrefeito);
    strcpy(novo->nomeVice, nomeVice);
    novo->numPartido = numPartido;
    for (int i = 0; i < 3; i++) {
        novo->dataNascimento[i] = data[i];
    }
    novo->votos = 0;

    return novo;
}

Tree* criaArvore() {
    return NULL;
}

Tree* insereChapa(Tree *t, Chapa *ch) {
    if (t == NULL) {
        Tree *novo = (Tree*)malloc(sizeof(Tree));
        novo->chapa = ch;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (ch->numPartido < t->chapa->numPartido) {
        t->esquerda = insereChapa(t->esquerda, ch);
    } else {
        t->direita = insereChapa(t->direita, ch);
    }

    return t;
}

void exibeChapas(Tree *t) {
    if (t != NULL) {
        exibeChapas(t->esquerda);
        printf("Candidato: %s com Vice: %s - Numero: %d\n", t->chapa->nomePrefeito, t->chapa->nomeVice, t->chapa->numPartido);
        exibeChapas(t->direita);
    }
}

Chapa* buscaChapa(Tree *t, int numPartido) {
    if (t == NULL) return NULL;
    if (numPartido == t->chapa->numPartido) return t->chapa;
    if (numPartido < t->chapa->numPartido) return buscaChapa(t->esquerda, numPartido);
    return buscaChapa(t->direita, numPartido);
}

void votacao(Tree *t, int *brancos, int *nulos, int numEleitores) {
    int voto;
    for (int i = 0; i < numEleitores; i++) {
        printf("\n----- Votacao -----\n");
        exibeChapas(t);
        printf("Digite o numero do candidato (0 para branco): ");
        scanf("%d", &voto);

        if (voto == 0) {
            (*brancos)++;
            printf("Voto em branco confirmado!\n");
        } else {
            Chapa *chapa = buscaChapa(t, voto);
            if (chapa != NULL) {
                chapa->votos++;
                printf("Seu voto em %s com Vice %s foi confirmado!\n", chapa->nomePrefeito, chapa->nomeVice);
            } else {
                (*nulos)++;
                printf("Voto nulo confirmado!\n");
            }
        }
        sleep(2);
        limpaTela();
    }

    if (numEleitores < 10) {
        Chapa *chapa1 = NULL, *chapa2 = NULL;
        void encontraDuasMaisVotadas(Tree *t) {
            if (t == NULL) return;
            encontraDuasMaisVotadas(t->esquerda);

            if (chapa1 == NULL || t->chapa->votos > chapa1->votos) {
                chapa2 = chapa1;
                chapa1 = t->chapa;
            } else if (chapa2 == NULL || t->chapa->votos > chapa2->votos) {
                chapa2 = t->chapa;
            }

            encontraDuasMaisVotadas(t->direita);
        }
        encontraDuasMaisVotadas(t);

        if (chapa1 != NULL && chapa2 != NULL && chapa1->votos == chapa2->votos) {
            if (chapa1->dataNascimento[2] < chapa2->dataNascimento[2] ||
               (chapa1->dataNascimento[2] == chapa2->dataNascimento[2] && chapa1->dataNascimento[1] < chapa2->dataNascimento[1]) ||
               (chapa1->dataNascimento[2] == chapa2->dataNascimento[2] && chapa1->dataNascimento[1] == chapa2->dataNascimento[1] && chapa1->dataNascimento[0] < chapa2->dataNascimento[0])) {
                printf("Empate! O candidato %s eh mais velho e vence a eleicao.\n", chapa1->nomePrefeito);
            } else {
                printf("Empate! O candidato %s eh mais velho e vence a eleicao.\n", chapa2->nomePrefeito);
            }
        }
    }
}


int totalVotosValidos(Tree *t) {
    if (t == NULL) return 0;
    return t->chapa->votos + totalVotosValidos(t->esquerda) + totalVotosValidos(t->direita);
}

void salvaBoletim(Tree *t, int brancos, int nulos, int totalEleitores, const char* nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL) {
        printf("Erro ao salvar o boletim de urna.\n");
        return;
    }

    int validos = totalVotosValidos(t);
    int totalVotos = validos + brancos + nulos;

    fprintf(f, "Boletim de Urna - Primeiro Turno\n");
    fprintf(f, "--------------------------------\n");
    fprintf(f, "Total de eleitores: %d\n", totalEleitores);
    fprintf(f, "Votos validos: %d (%.2f%%)\n", validos, (validos * 100.0) / totalVotos);
    fprintf(f, "Votos brancos: %d (%.2f%%)\n", brancos, (brancos * 100.0) / totalVotos);
    fprintf(f, "Votos nulos: %d (%.2f%%)\n", nulos, (nulos * 100.0) / totalVotos);

    void salvaChapas(Tree *t, FILE *f) {
        if (t == NULL) return;
        salvaChapas(t->esquerda, f);
        fprintf(f, "%s com Vice %s: %d votos (%.2f%% do total)\n",
                t->chapa->nomePrefeito, t->chapa->nomeVice, t->chapa->votos,
                (t->chapa->votos * 100.0) / totalVotos);
        salvaChapas(t->direita, f);
    }

    salvaChapas(t, f);

    fclose(f);
    printf("Boletim de urna salvo em %s.\n", nomeArquivo);
}

int maiorNumeroDeVotos(Tree *t) {
    if (t == NULL) return 0;

    int maiorEsquerda = maiorNumeroDeVotos(t->esquerda);
    int maiorDireita = maiorNumeroDeVotos(t->direita);

    int maior = t->chapa->votos;
    if (maiorEsquerda > maior) maior = maiorEsquerda;
    if (maiorDireita > maior) maior = maiorDireita;

    return maior;
}

int calculaSegundoTurno(int votosValidos, int maiorVotos, int numEleitores) {
    if (numEleitores >= MIN_ELEITORES_SEGUNDO_TURNO && maiorVotos < (votosValidos / 2 + 1)) {
        return 1;
    }
    return 0;
}

void limpaTela() {
    system("cls");
}

void segundoTurno(Tree *t, int numEleitores) {
    Chapa *chapa1 = NULL;
    Chapa *chapa2 = NULL;

    void encontraDuasMaisVotadas(Tree *t) {
        if (t == NULL) return;
        encontraDuasMaisVotadas(t->esquerda);

        if (chapa1 == NULL || t->chapa->votos > chapa1->votos) {
            chapa2 = chapa1;
            chapa1 = t->chapa;
        } else if (chapa2 == NULL || t->chapa->votos > chapa2->votos) {
            chapa2 = t->chapa;
        }

        encontraDuasMaisVotadas(t->direita);
    }

    encontraDuasMaisVotadas(t);

    if (chapa1 == NULL || chapa2 == NULL) {
        printf("Erro: Não há candidatas suficientes para o segundo turno.\n");
        return;
    }

    printf("Iniciando segundo turno entre: %s (numero %d) e %s (numero %d)\n",
            chapa1->nomePrefeito, chapa1->numPartido, chapa2->nomePrefeito, chapa2->numPartido);

    int votosChapa1 = 0, votosChapa2 = 0, brancos = 0, nulos = 0;
    int voto;
    for (int i = 0; i < numEleitores; i++) {  // Usar o número correto de eleitores
        printf("Digite o numero do candidato (%d para %s, %d para %s, ou 0 para branco): ",
               chapa1->numPartido, chapa1->nomePrefeito, chapa2->numPartido, chapa2->nomePrefeito);
        scanf("%d", &voto);

        if (voto == 0) {
            brancos++;
        } else if (voto == chapa1->numPartido) {
            votosChapa1++;
        } else if (voto == chapa2->numPartido) {
            votosChapa2++;
        } else {
            nulos++;
        }
    }

    printf("Resultado do segundo turno:\n");
    printf("%s com Vice %s: %d votos\n", chapa1->nomePrefeito, chapa1->nomeVice, votosChapa1);
    printf("%s com Vice %s: %d votos\n", chapa2->nomePrefeito, chapa2->nomeVice, votosChapa2);
    printf("Votos brancos: %d\n", brancos);
    printf("Votos nulos: %d\n", nulos);

    // Desempate por idade simplificado
    if (votosChapa1 == votosChapa2) {
        if (chapa1->dataNascimento[2] < chapa2->dataNascimento[2] ||
           (chapa1->dataNascimento[2] == chapa2->dataNascimento[2] && chapa1->dataNascimento[1] < chapa2->dataNascimento[1]) ||
           (chapa1->dataNascimento[2] == chapa2->dataNascimento[2] && chapa1->dataNascimento[1] == chapa2->dataNascimento[1] && chapa1->dataNascimento[0] < chapa2->dataNascimento[0])) {
            printf("Empate! O candidato %s eh mais velho e vence a eleicao.\n", chapa1->nomePrefeito);
        } else {
            printf("Empate! O candidato %s eh mais velho e vence a eleicao.\n", chapa2->nomePrefeito);
        }
    } else if (votosChapa1 > votosChapa2) {
        printf("O candidato %s venceu a eleicao!\n", chapa1->nomePrefeito);
    } else {
        printf("O candidato %s venceu a eleicao!\n", chapa2->nomePrefeito);
    }
}
