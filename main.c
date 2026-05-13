#include <stdio.h>
#include "pss.h"

typedef struct {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    float duracao;
} Musica;

int idExistente(int idBuscado) {
    Musica musicaLida;
    FILE *file = fopen("musica.txt", "r");
    if (file == NULL) {
        printf("Erro na abertura do musica.txt\n");
        return 0;
    }
    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%f\n",
        &musicaLida.id,
        musicaLida.titulo,
        musicaLida.artista,
        musicaLida.genero,
        &musicaLida.duracao) == 5) {

        if (musicaLida.id == idBuscado) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void cadastrar() {
    Musica novaMusica;
    FILE *file = fopen("musica.txt", "a");
    if (file == NULL) {
        printf("Erro na abertura do musica.txt");
        return;
    }
    printf("---Cadastro de nova musica---\n");
    novaMusica.id = input_d("\nDigite o id que deseja atribuir a musica\n");

    if (idExistente(novaMusica.id)) {
        printf("Ja existe uma musica com esse ID.\n");
        fclose(file);
        return;
    }
    input_s("\nDigite o nome da musica:\n", novaMusica.titulo, 50);
    input_s("\nDigite o artista:\n", novaMusica.artista, 50);
    input_s("\nDigite o genero:\n", novaMusica.genero, 30);
    novaMusica.duracao = input_f("\nDigite a duracao da musica:\n");

    fprintf(file, "%d;%s;%s;%s;%.2f\n",
    novaMusica.id, novaMusica.titulo, novaMusica.artista, novaMusica.genero, novaMusica.duracao);
    fclose(file);

}

void consultar() {
    Musica musicaLida;
    FILE *file = fopen("musica.txt", "r");
    if (file == NULL) {
        printf("Erro na abertura do musica.txt");
        return;
    }
    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%f\n",
                  &musicaLida.id,
                  musicaLida.titulo,
                  musicaLida.artista,
                  musicaLida.genero,
                  &musicaLida.duracao) == 5) {
        printf("| Id: %d | Musica: %s | Artista: %s | Genero: %s | Duracao:%.2f |\n",
            musicaLida.id,
            musicaLida.titulo,
            musicaLida.artista,
            musicaLida.genero,
            musicaLida.duracao);
    }
    fclose(file);
}

void alterar() {
    Musica musicaLida;
    int buscaID;
    int encontrou = 0;
    FILE *file = fopen("musica.txt", "r");
    if (file == NULL) {
        printf("Erro na abertura do musica.txt\n");
        return;
    }
    FILE *file2 = fopen("novo.txt", "w");
    if (file2 == NULL) {
        printf("Erro na abertura do novo.txt\n");
        fclose(file);
        return;
    }
    buscaID = input_d("\nDigite o id da musica que deseja alterar:\n");

    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%f\n",
                  &musicaLida.id,
                  musicaLida.titulo,
                  musicaLida.artista,
                  musicaLida.genero,
                  &musicaLida.duracao) == 5) {
        if (musicaLida.id == buscaID) {
            encontrou = 1;
            printf("Musica encontrada.");
            input_s("\nDigite o novo nome da musica:\n", musicaLida.titulo, 50);
            input_s("\nDigite o novo artista:\n", musicaLida.artista, 50);
            input_s("\nDigite o novo genero:\n", musicaLida.genero, 30);
            musicaLida.duracao = input_f("\nDigite a nova duracao da musica:\n");
        }
        fprintf(file2, "%d;%s;%s;%s;%.2f\n",
                musicaLida.id, musicaLida.titulo, musicaLida.artista, musicaLida.genero, musicaLida.duracao);
    }
    fclose(file);
    fclose(file2);
    if (encontrou == 1) {
        remove("musica.txt");
        rename("novo.txt", "musica.txt");
        printf("Musica alterada.");
    } else {
        remove("novo.txt");
        printf("Musica nao encontrada.");
    }
}

void excluir() {
    Musica musicaLida;
    int buscaID;
    int encontrou = 0;
    FILE *file = fopen("musica.txt", "r");
    FILE *file2 = fopen("novo.txt", "w");
    if (file == NULL || file2 == NULL) {
        printf("Erro na abertura do musica.txt");
        return;
    }
    buscaID = input_d("\nDigite o id da musica que deseja excluir:\n");

    while (fscanf(file, "%d;%[^;];%[^;];%[^;];%f\n",
                  &musicaLida.id,
                  musicaLida.titulo,
                  musicaLida.artista,
                  musicaLida.genero,
                  &musicaLida.duracao) == 5) {
        if (musicaLida.id == buscaID) {
            encontrou = 1;
            printf("Musica '%s' excluida.", musicaLida.titulo);
        }else{
            fprintf(file2, "%d;%s;%s;%s;%.2f\n",
                    musicaLida.id, musicaLida.titulo, musicaLida.artista, musicaLida.genero, musicaLida.duracao);
        }
    }
    fclose(file);
    fclose(file2);

    if (encontrou == 1) {
        remove("musica.txt");
        rename("novo.txt", "musica.txt");
        printf("Musica excluida.");
    } else {
        remove("novo.txt");
        printf("Musica nao encontrada.");
    }
}

int main() {
    int opcao = 0;

    do {
        printf("\n1 - Cadastrar\n2 - Consultar\n3 - Alterar\n4 - Excluir\n5 - Sair\n");
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
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 5);

    return 0;
}
