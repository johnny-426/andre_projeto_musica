#include <stdio.h>
#include "pss.h"

#define ARQUIVO_MUSICAS "musica.txt"
#define ARQUIVO_TEMPORARIO "novo.txt"

typedef struct {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    float duracao;
} Musica;

static int lerMusica(FILE *arquivo, Musica *musica) {
    return fscanf(
        arquivo,
        "%d;%49[^;];%49[^;];%29[^;];%f\n",
        &musica->id,
        musica->titulo,
        musica->artista,
        musica->genero,
        &musica->duracao
    ) == 5;
}

static void gravarMusica(FILE *arquivo, const Musica *musica) {
    fprintf(
        arquivo,
        "%d;%s;%s;%s;%.2f\n",
        musica->id,
        musica->titulo,
        musica->artista,
        musica->genero,
        musica->duracao
    );
}

static int idExistente(int idBuscado) {
    Musica musica;
    FILE *arquivo = fopen(ARQUIVO_MUSICAS, "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (lerMusica(arquivo, &musica)) {
        if (musica.id == idBuscado) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

static void cadastrar(void) {
    Musica novaMusica;

    printf("\n--- Cadastro de nova musica ---\n");
    novaMusica.id = input_d("Digite o ID que deseja atribuir a musica: ");

    if (idExistente(novaMusica.id)) {
        printf("Ja existe uma musica com esse ID.\n");
        return;
    }

    input_s("Digite o nome da musica: ", novaMusica.titulo, sizeof(novaMusica.titulo));
    input_s("Digite o artista: ", novaMusica.artista, sizeof(novaMusica.artista));
    input_s("Digite o genero: ", novaMusica.genero, sizeof(novaMusica.genero));
    novaMusica.duracao = input_f("Digite a duracao da musica: ");

    FILE *arquivo = fopen(ARQUIVO_MUSICAS, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de musicas.\n");
        return;
    }

    gravarMusica(arquivo, &novaMusica);
    fclose(arquivo);

    printf("Musica cadastrada com sucesso.\n");
}

static void consultar(void) {
    Musica musica;
    FILE *arquivo = fopen(ARQUIVO_MUSICAS, "r");

    if (arquivo == NULL) {
        printf("Nenhuma musica cadastrada.\n");
        return;
    }

    printf("\n--- Musicas cadastradas ---\n");

    int encontrou = 0;
    while (lerMusica(arquivo, &musica)) {
        encontrou = 1;
        printf(
            "ID: %d | Musica: %s | Artista: %s | Genero: %s | Duracao: %.2f\n",
            musica.id,
            musica.titulo,
            musica.artista,
            musica.genero,
            musica.duracao
        );
    }

    if (!encontrou) {
        printf("Nenhuma musica cadastrada.\n");
    }

    fclose(arquivo);
}

static void alterar(void) {
    Musica musica;
    int buscaID = input_d("\nDigite o ID da musica que deseja alterar: ");
    int encontrou = 0;

    FILE *arquivo = fopen(ARQUIVO_MUSICAS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma musica cadastrada.\n");
        return;
    }

    FILE *temporario = fopen(ARQUIVO_TEMPORARIO, "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    while (lerMusica(arquivo, &musica)) {
        if (musica.id == buscaID) {
            encontrou = 1;
            printf("Musica encontrada: %s\n", musica.titulo);

            input_s("Digite o novo nome da musica: ", musica.titulo, sizeof(musica.titulo));
            input_s("Digite o novo artista: ", musica.artista, sizeof(musica.artista));
            input_s("Digite o novo genero: ", musica.genero, sizeof(musica.genero));
            musica.duracao = input_f("Digite a nova duracao da musica: ");
        }

        gravarMusica(temporario, &musica);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove(ARQUIVO_TEMPORARIO);
        printf("Musica nao encontrada.\n");
        return;
    }

    if (remove(ARQUIVO_MUSICAS) != 0 || rename(ARQUIVO_TEMPORARIO, ARQUIVO_MUSICAS) != 0) {
        printf("Erro ao atualizar o arquivo de musicas.\n");
        return;
    }

    printf("Musica alterada com sucesso.\n");
}

static void excluir(void) {
    Musica musica;
    int buscaID = input_d("\nDigite o ID da musica que deseja excluir: ");
    int encontrou = 0;

    FILE *arquivo = fopen(ARQUIVO_MUSICAS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma musica cadastrada.\n");
        return;
    }

    FILE *temporario = fopen(ARQUIVO_TEMPORARIO, "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    while (lerMusica(arquivo, &musica)) {
        if (musica.id == buscaID) {
            encontrou = 1;
            printf("Musica '%s' selecionada para exclusao.\n", musica.titulo);
            continue;
        }

        gravarMusica(temporario, &musica);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove(ARQUIVO_TEMPORARIO);
        printf("Musica nao encontrada.\n");
        return;
    }

    if (remove(ARQUIVO_MUSICAS) != 0 || rename(ARQUIVO_TEMPORARIO, ARQUIVO_MUSICAS) != 0) {
        printf("Erro ao atualizar o arquivo de musicas.\n");
        return;
    }

    printf("Musica excluida com sucesso.\n");
}

int main(void) {
    int opcao;

    do {
        printf(
            "\n=== Biblioteca de Musicas ===\n"
            "1 - Cadastrar\n"
            "2 - Consultar\n"
            "3 - Alterar\n"
            "4 - Excluir\n"
            "5 - Sair\n"
        );

        opcao = input_d("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                consultar();
                break;
            case 3:
                alterar();
                break;
            case 4:
                excluir();
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}
