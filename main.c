#include <stdio.h>
#include <string.h>

#define TAMANHO_ACERVO 20

struct Livro {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
};

int quantidadeCadastrada = 0; // <-- NOVO

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarLivros(struct Livro acervo[], int tamanho);
void imprimirLivros(struct Livro acervo[], int tamanho);
void pesquisarLivro(struct Livro acervo[], int tamanho);
void ordenarLivros(struct Livro acervo[], int tamanho);

int main() {
    struct Livro acervo[TAMANHO_ACERVO];
    int opcao;

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE LIVROS =====\n");
        printf("1 - Cadastrar livros\n");
        printf("2 - Imprimir todos os livros\n");
        printf("3 - Pesquisar livro por codigo\n");
        printf("4 - Ordenar livros por ano (Bubble Sort)\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarLivros(acervo, TAMANHO_ACERVO);
                break;
            case 2:
                imprimirLivros(acervo, quantidadeCadastrada);
                break;
            case 3:
                pesquisarLivro(acervo, quantidadeCadastrada);
                break;
            case 4:
                ordenarLivros(acervo, quantidadeCadastrada);
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 5);

    return 0;
}

void cadastrarLivros(struct Livro acervo[], int tamanho) {
    int quantidade;

    printf("\nQuantos livros deseja cadastrar? (max %d): ", tamanho);
    scanf("%d", &quantidade);
    limparBuffer();

    if (quantidade < 1 || quantidade > tamanho) {
        printf("Quantidade invalida!\n");
        return;
    }

    quantidadeCadastrada = quantidade; // <-- Salva quantos foram cadastrados

    printf("\n=== Cadastro de Livros ===\n");

    for(int i = 0; i < quantidade; i++) {
        printf("\n--- Livro %d ---\n", i + 1);

        printf("Codigo: ");
        scanf("%d", &acervo[i].codigo);
        limparBuffer();

        printf("Titulo: ");
        fgets(acervo[i].titulo, 50, stdin);
        acervo[i].titulo[strcspn(acervo[i].titulo, "\n")] = 0;

        printf("Autor: ");
        fgets(acervo[i].autor, 30, stdin);
        acervo[i].autor[strcspn(acervo[i].autor, "\n")] = 0;

        printf("Area: ");
        fgets(acervo[i].area, 30, stdin);
        acervo[i].area[strcspn(acervo[i].area, "\n")] = 0;

        printf("Ano: ");
        scanf("%d", &acervo[i].ano);
        limparBuffer();

        printf("Editora: ");
        fgets(acervo[i].editora, 30, stdin);
        acervo[i].editora[strcspn(acervo[i].editora, "\n")] = 0;
    }

    printf("\nCadastro concluido!\n");
}

void imprimirLivros(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado ainda!\n");
        return;
    }

    printf("\n=== Lista de Livros ===\n");

    for(int i = 0; i < tamanho; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Codigo: %d\n", acervo[i].codigo);
        printf("Titulo: %s\n", acervo[i].titulo);
        printf("Autor: %s\n", acervo[i].autor);
        printf("Area: %s\n", acervo[i].area);
        printf("Ano: %d\n", acervo[i].ano);
        printf("Editora: %s\n", acervo[i].editora);
    }
}

void pesquisarLivro(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado para pesquisar!\n");
        return;
    }

    int codigoBusca;
    int encontrado = 0;

    printf("\nDigite o codigo do livro para pesquisar: ");
    scanf("%d", &codigoBusca);
    limparBuffer();

    for(int i = 0; i < tamanho; i++) {
        if(acervo[i].codigo == codigoBusca) {
            printf("\n=== Livro encontrado ===\n");
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\nLivro nao encontrado!\n");
    }
}

void ordenarLivros(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado para ordenar!\n");
        return;
    }

    struct Livro temp;

    for(int i = 0; i < tamanho - 1; i++) {
        for(int j = 0; j < tamanho - 1 - i; j++) {
            if(acervo[j].ano > acervo[j + 1].ano) {
                temp = acervo[j];
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = temp;
            }
        }
    }

    printf("\nLivros ordenados por ano com sucesso!\n");
}