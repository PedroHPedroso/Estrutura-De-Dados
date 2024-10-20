#include "estoque.h"

// Define a estrutura de um "medicamento"
struct medicamento {
    char nome[20];   // Armazena o nome do medicamento (máximo de 20 caracteres)
    int codigo;      // Armazena o código numérico do medicamento
    float valor;     // Armazena o valor (preço) do medicamento
    int data[3];     // Armazena a data de validade (dia, mês, ano) como um array de inteiros
};

// Define a estrutura de um nó da árvore (que armazena um medicamento)
struct arvore {
    Medicamento *m;      // Ponteiro para o medicamento armazenado nesse nó
    Arvore *esquerda;    // Ponteiro para o nó à esquerda (menores valores de código)
    Arvore *direita;     // Ponteiro para o nó à direita (maiores valores de código)
};

// Função que cria um novo medicamento
Medicamento *criaMedicamento(char* nome, int codigo, float valor, int *data_de_validade) {
    // Aloca memória para um novo medicamento
    Medicamento *novo = (Medicamento*)malloc(sizeof(Medicamento));

    // Copia o nome do medicamento para a estrutura
    strcpy(novo->nome, nome);

    // Atribui o código e o valor ao novo medicamento
    novo->codigo = codigo;
    novo->valor = valor;

    // Copia a data de validade para a estrutura
    for (int i = 0; i < 3; i++) {
        novo->data[i] = data_de_validade[i];
    }

    // Retorna o ponteiro para o novo medicamento criado
    return novo;
}

// Função que cria uma árvore vazia (ou seja, uma árvore nula)
Arvore *criaArvore() {
    return NULL;   // Retorna NULL, indicando que a árvore está inicialmente vazia
}

// Função que insere um novo medicamento na árvore de forma ordenada pelo código
Arvore *insereArvoreMedicamento(Arvore *a, Medicamento *m) {
    // Se a árvore estiver vazia (NULL), cria um novo nó
    if (a == NULL) {
        // Aloca memória para um novo nó da árvore
        Arvore *novo = (Arvore*)malloc(sizeof(Arvore));

        // Atribui o medicamento ao novo nó e inicializa os filhos (esquerda e direita) como NULL
        novo->m = m;
        novo->esquerda = NULL;
        novo->direita = NULL;

        // Retorna o novo nó criado
        return novo;
    }

    // Se o código do medicamento for menor que o código no nó atual, insere na subárvore esquerda
    if (m->codigo < a->m->codigo) {
        a->esquerda = insereArvoreMedicamento(a->esquerda, m);   // Chamada recursiva para a esquerda
    }
    // Se o código for maior ou igual, insere na subárvore direita
    else {
        a->direita = insereArvoreMedicamento(a->direita, m);     // Chamada recursiva para a direita
    }

    // Retorna a árvore atualizada
    return a;
}

// Função que remove um medicamento da árvore dado o seu código
Arvore *retiraArvoreMedicamento(Arvore *a, int id_medicamento) {
    // Se a árvore estiver vazia, retorna NULL (nada a ser removido)
    if (a == NULL)
        return NULL;

    // Se o código do nó atual for maior que o código do medicamento a ser removido, busca na esquerda
    else if (a->m->codigo > id_medicamento)
        a->esquerda = retiraArvoreMedicamento(a->esquerda, id_medicamento);

    // Se o código for menor, busca na direita
    else if (a->m->codigo < id_medicamento)
        a->direita = retiraArvoreMedicamento(a->direita, id_medicamento);

    // Se o código for igual, este é o nó a ser removido
    else {
        // Se o nó não tem filhos (é uma folha), libera a memória e retorna NULL
        if (a->esquerda == NULL && a->direita == NULL) {
            free(a);  // Libera a memória do nó
            a = NULL; // Define o nó como NULL (foi removido)
        }
        // Se só tem filho à direita, substitui o nó pelo filho direito
        else if (a->esquerda == NULL) {
            Arvore *t = a;           // Guarda o nó atual
            a = a->direita;          // Move para a direita
            free(t);                 // Libera o nó anterior
        }
        // Se só tem filho à esquerda, substitui o nó pelo filho esquerdo
        else if (a->direita == NULL) {
            Arvore *t = a;           // Guarda o nó atual
            a = a->esquerda;         // Move para a esquerda
            free(t);                 // Libera o nó anterior
        }
        // Se tem filhos em ambos os lados, encontra o maior nó da subárvore esquerda
        else {
            Arvore *f = a->esquerda;    // Encontra o maior nó da subárvore esquerda
            while (f->direita != NULL) {
                f = f->direita;
            }
            // Troca o código do nó atual pelo código do nó encontrado
            a->m->codigo = f->m->codigo;
            // Remove o nó da subárvore esquerda
            f->m->codigo = id_medicamento;
            a->esquerda = retiraArvoreMedicamento(a->esquerda, id_medicamento);
        }
    }
    return a;  // Retorna a árvore atualizada
}

// Função que verifica se um medicamento com determinado código está na árvore
int verificaArvoreMedicamento(Arvore *a, int id_medicamento) {
    // Se a árvore estiver vazia, retorna 0 (não encontrado)
    if (a == NULL)
        return 0;
    // Se o código for menor, busca na esquerda
    else if (a->m->codigo > id_medicamento)
        return verificaArvoreMedicamento(a->esquerda, id_medicamento);
    // Se o código for maior, busca na direita
    else if (a->m->codigo < id_medicamento)
        return verificaArvoreMedicamento(a->direita, id_medicamento);
    // Se o código for igual, encontrou o medicamento, retorna 1
    else
        return 1;
}

// Função que verifica se algum medicamento na árvore está vencido
int VerificaArvoreValidade(FILE* fp, Arvore *a, int *dataDeValidade) {
    int encontrado = 0;  // Variável para armazenar se algum medicamento foi encontrado como vencido

    // Percorre a árvore em ordem para verificar cada medicamento
    if (a != NULL) {
        // Verifica os nós à esquerda
        encontrado |= VerificaArvoreValidade(fp, a->esquerda, dataDeValidade);

        // Compara a data de validade do medicamento atual
        if (a->m->data[2] < dataDeValidade[2] ||
            (a->m->data[2] == dataDeValidade[2] && a->m->data[1] < dataDeValidade[1]) ||
            (a->m->data[2] == dataDeValidade[2] && a->m->data[1] == dataDeValidade[1] && a->m->data[0] < dataDeValidade[0])) {
            // Se vencido, escreve a mensagem no arquivo
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", a->m->nome, a->m->codigo);
            encontrado = 1;  // Marca como encontrado
        }

        // Verifica os nós à direita
        encontrado |= VerificaArvoreValidade(fp, a->direita, dataDeValidade);
    }

    // Retorna 1 se encontrou medicamentos vencidos, 0 caso contrário
    return encontrado;
}

// Função que imprime a árvore em ordem
void imprimeArvore(FILE *fp, Arvore *a) {
    if (a != NULL) {
        // Imprime a subárvore esquerda
        imprimeArvore(fp, a->esquerda);
        // Imprime o medicamento no nó atual
        fprintf(fp, "MEDICAMENTO %s %d R$%.2f %d %d %d\n", a->m->nome, a->m->codigo, a->m->valor, a->m->data[0], a->m->data[1], a->m->data[2]);
        // Imprime a subárvore direita
        imprimeArvore(fp, a->direita);
    }
}

// Função que atualiza o preço de um medicamento dado o código
void atualizaPrecoMedicamento(Arvore *a, int codigo, float novo_valor) {
    // Se a árvore estiver vazia, retorna
    if (a == NULL) return;

    // Se encontrou o medicamento, atualiza o preço
    if (a->m->codigo == codigo) {
        a->m->valor = novo_valor;
    }
    // Se o código for menor, busca na esquerda
    else if (codigo < a->m->codigo) {
        atualizaPrecoMedicamento(a->esquerda, codigo, novo_valor);
    }
    // Se o código for maior, busca na direita
    else {
        atualizaPrecoMedicamento(a->direita, codigo, novo_valor);
    }
}

// Função que libera toda a memória alocada pela árvore
void liberaArvore(Arvore *a) {
    if (a != NULL) {
        // Libera a subárvore esquerda
        liberaArvore(a->esquerda);
        // Libera a subárvore direita
        liberaArvore(a->direita);
        // Libera a memória do medicamento armazenado no nó atual
        free(a->m);
        // Libera o nó atual
        free(a);
    }
}
