#include "estoque.h"

// Define a estrutura de um "medicamento"
struct medicamento {
    char nome[20];   // Armazena o nome do medicamento (m�ximo de 20 caracteres)
    int codigo;      // Armazena o c�digo num�rico do medicamento
    float valor;     // Armazena o valor (pre�o) do medicamento
    int data[3];     // Armazena a data de validade (dia, m�s, ano) como um array de inteiros
};

// Define a estrutura de um n� da �rvore (que armazena um medicamento)
struct arvore {
    Medicamento *m;      // Ponteiro para o medicamento armazenado nesse n�
    Arvore *esquerda;    // Ponteiro para o n� � esquerda (menores valores de c�digo)
    Arvore *direita;     // Ponteiro para o n� � direita (maiores valores de c�digo)
};

// Fun��o que cria um novo medicamento
Medicamento *criaMedicamento(char* nome, int codigo, float valor, int *data_de_validade) {
    // Aloca mem�ria para um novo medicamento
    Medicamento *novo = (Medicamento*)malloc(sizeof(Medicamento));

    // Copia o nome do medicamento para a estrutura
    strcpy(novo->nome, nome);

    // Atribui o c�digo e o valor ao novo medicamento
    novo->codigo = codigo;
    novo->valor = valor;

    // Copia a data de validade para a estrutura
    for (int i = 0; i < 3; i++) {
        novo->data[i] = data_de_validade[i];
    }

    // Retorna o ponteiro para o novo medicamento criado
    return novo;
}

// Fun��o que cria uma �rvore vazia (ou seja, uma �rvore nula)
Arvore *criaArvore() {
    return NULL;   // Retorna NULL, indicando que a �rvore est� inicialmente vazia
}

// Fun��o que insere um novo medicamento na �rvore de forma ordenada pelo c�digo
Arvore *insereArvoreMedicamento(Arvore *a, Medicamento *m) {
    // Se a �rvore estiver vazia (NULL), cria um novo n�
    if (a == NULL) {
        // Aloca mem�ria para um novo n� da �rvore
        Arvore *novo = (Arvore*)malloc(sizeof(Arvore));

        // Atribui o medicamento ao novo n� e inicializa os filhos (esquerda e direita) como NULL
        novo->m = m;
        novo->esquerda = NULL;
        novo->direita = NULL;

        // Retorna o novo n� criado
        return novo;
    }

    // Se o c�digo do medicamento for menor que o c�digo no n� atual, insere na sub�rvore esquerda
    if (m->codigo < a->m->codigo) {
        a->esquerda = insereArvoreMedicamento(a->esquerda, m);   // Chamada recursiva para a esquerda
    }
    // Se o c�digo for maior ou igual, insere na sub�rvore direita
    else {
        a->direita = insereArvoreMedicamento(a->direita, m);     // Chamada recursiva para a direita
    }

    // Retorna a �rvore atualizada
    return a;
}

// Fun��o que remove um medicamento da �rvore dado o seu c�digo
Arvore *retiraArvoreMedicamento(Arvore *a, int id_medicamento) {
    // Se a �rvore estiver vazia, retorna NULL (nada a ser removido)
    if (a == NULL)
        return NULL;

    // Se o c�digo do n� atual for maior que o c�digo do medicamento a ser removido, busca na esquerda
    else if (a->m->codigo > id_medicamento)
        a->esquerda = retiraArvoreMedicamento(a->esquerda, id_medicamento);

    // Se o c�digo for menor, busca na direita
    else if (a->m->codigo < id_medicamento)
        a->direita = retiraArvoreMedicamento(a->direita, id_medicamento);

    // Se o c�digo for igual, este � o n� a ser removido
    else {
        // Se o n� n�o tem filhos (� uma folha), libera a mem�ria e retorna NULL
        if (a->esquerda == NULL && a->direita == NULL) {
            free(a);  // Libera a mem�ria do n�
            a = NULL; // Define o n� como NULL (foi removido)
        }
        // Se s� tem filho � direita, substitui o n� pelo filho direito
        else if (a->esquerda == NULL) {
            Arvore *t = a;           // Guarda o n� atual
            a = a->direita;          // Move para a direita
            free(t);                 // Libera o n� anterior
        }
        // Se s� tem filho � esquerda, substitui o n� pelo filho esquerdo
        else if (a->direita == NULL) {
            Arvore *t = a;           // Guarda o n� atual
            a = a->esquerda;         // Move para a esquerda
            free(t);                 // Libera o n� anterior
        }
        // Se tem filhos em ambos os lados, encontra o maior n� da sub�rvore esquerda
        else {
            Arvore *f = a->esquerda;    // Encontra o maior n� da sub�rvore esquerda
            while (f->direita != NULL) {
                f = f->direita;
            }
            // Troca o c�digo do n� atual pelo c�digo do n� encontrado
            a->m->codigo = f->m->codigo;
            // Remove o n� da sub�rvore esquerda
            f->m->codigo = id_medicamento;
            a->esquerda = retiraArvoreMedicamento(a->esquerda, id_medicamento);
        }
    }
    return a;  // Retorna a �rvore atualizada
}

// Fun��o que verifica se um medicamento com determinado c�digo est� na �rvore
int verificaArvoreMedicamento(Arvore *a, int id_medicamento) {
    // Se a �rvore estiver vazia, retorna 0 (n�o encontrado)
    if (a == NULL)
        return 0;
    // Se o c�digo for menor, busca na esquerda
    else if (a->m->codigo > id_medicamento)
        return verificaArvoreMedicamento(a->esquerda, id_medicamento);
    // Se o c�digo for maior, busca na direita
    else if (a->m->codigo < id_medicamento)
        return verificaArvoreMedicamento(a->direita, id_medicamento);
    // Se o c�digo for igual, encontrou o medicamento, retorna 1
    else
        return 1;
}

// Fun��o que verifica se algum medicamento na �rvore est� vencido
int VerificaArvoreValidade(FILE* fp, Arvore *a, int *dataDeValidade) {
    int encontrado = 0;  // Vari�vel para armazenar se algum medicamento foi encontrado como vencido

    // Percorre a �rvore em ordem para verificar cada medicamento
    if (a != NULL) {
        // Verifica os n�s � esquerda
        encontrado |= VerificaArvoreValidade(fp, a->esquerda, dataDeValidade);

        // Compara a data de validade do medicamento atual
        if (a->m->data[2] < dataDeValidade[2] ||
            (a->m->data[2] == dataDeValidade[2] && a->m->data[1] < dataDeValidade[1]) ||
            (a->m->data[2] == dataDeValidade[2] && a->m->data[1] == dataDeValidade[1] && a->m->data[0] < dataDeValidade[0])) {
            // Se vencido, escreve a mensagem no arquivo
            fprintf(fp, "MEDICAMENTO %s %d VENCIDO\n", a->m->nome, a->m->codigo);
            encontrado = 1;  // Marca como encontrado
        }

        // Verifica os n�s � direita
        encontrado |= VerificaArvoreValidade(fp, a->direita, dataDeValidade);
    }

    // Retorna 1 se encontrou medicamentos vencidos, 0 caso contr�rio
    return encontrado;
}

// Fun��o que imprime a �rvore em ordem
void imprimeArvore(FILE *fp, Arvore *a) {
    if (a != NULL) {
        // Imprime a sub�rvore esquerda
        imprimeArvore(fp, a->esquerda);
        // Imprime o medicamento no n� atual
        fprintf(fp, "MEDICAMENTO %s %d R$%.2f %d %d %d\n", a->m->nome, a->m->codigo, a->m->valor, a->m->data[0], a->m->data[1], a->m->data[2]);
        // Imprime a sub�rvore direita
        imprimeArvore(fp, a->direita);
    }
}

// Fun��o que atualiza o pre�o de um medicamento dado o c�digo
void atualizaPrecoMedicamento(Arvore *a, int codigo, float novo_valor) {
    // Se a �rvore estiver vazia, retorna
    if (a == NULL) return;

    // Se encontrou o medicamento, atualiza o pre�o
    if (a->m->codigo == codigo) {
        a->m->valor = novo_valor;
    }
    // Se o c�digo for menor, busca na esquerda
    else if (codigo < a->m->codigo) {
        atualizaPrecoMedicamento(a->esquerda, codigo, novo_valor);
    }
    // Se o c�digo for maior, busca na direita
    else {
        atualizaPrecoMedicamento(a->direita, codigo, novo_valor);
    }
}

// Fun��o que libera toda a mem�ria alocada pela �rvore
void liberaArvore(Arvore *a) {
    if (a != NULL) {
        // Libera a sub�rvore esquerda
        liberaArvore(a->esquerda);
        // Libera a sub�rvore direita
        liberaArvore(a->direita);
        // Libera a mem�ria do medicamento armazenado no n� atual
        free(a->m);
        // Libera o n� atual
        free(a);
    }
}
