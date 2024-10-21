#include "funcoes.h"

int main() {
    Tree *t = criaArvore();
    int numEleitores, numChapas = 0, brancos = 0, nulos = 0;
    char opcao;

    printf("Digite o numero de eleitores: ");
    scanf("%d", &numEleitores);
    printf("\n");

    do {
        char nomePrefeito[50], nomeVice[50];
        int numPartido, dataNascimento[3];

        printf("Digite o nome do candidato: ");
        scanf(" %[^\n]", nomePrefeito);
        printf("Digite o nome do vice: ");
        scanf(" %[^\n]", nomeVice);
        printf("Digite o numero do partido: ");
        scanf("%d", &numPartido);
        printf("Digite a data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &dataNascimento[0], &dataNascimento[1], &dataNascimento[2]);
        printf("\n");

        Chapa *chapa = criaChapa(nomePrefeito, nomeVice, numPartido, dataNascimento);
        t = insereChapa(t, chapa);
        numChapas++;

        if (numChapas >= MAX_CHAPAS) {
            printf("Numero maximo de chapas atingido!\n");
            break;
        }

        printf("Deseja cadastrar outra chapa? (s/n): ");
        scanf(" %c", &opcao);
    } while (opcao == 's' || opcao == 'S');

    votacao(t, &brancos, &nulos, numEleitores);

    int votosValidos = totalVotosValidos(t);
    int maiorVotos = maiorNumeroDeVotos(t);

    salvaBoletim(t, brancos, nulos, numEleitores, "boletim_primeiro_turno.txt");

    if (calculaSegundoTurno(votosValidos, maiorVotos, numEleitores)) {
        printf("Havera segundo turno!\n");
        segundoTurno(t,numEleitores);
    } else {
        printf("Nao havera segundo turno!\n");
    }

    return 0;
}
