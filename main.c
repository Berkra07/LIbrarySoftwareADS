#include <stdio.h>      // Biblioteca padrão de entrada/saída (printf, scanf, fgets)
#include <string.h>     // Biblioteca para funções de manipulação de strings (strcspn)

/*
 * Define o tamanho máximo do acervo.
 * O programa trabalhará com no máximo 20 livros.
 */
#define TAMANHO_ACERVO 20

/*
 * Estrutura que representa um livro.
 * Cada campo corresponde a um atributo que o bibliotecário irá cadastrar.
 */
struct Livro {
    int codigo;          // Identificador único do livro
    char titulo[50];     // Título do livro
    char autor[30];      // Nome do autor
    char area[30];       // Área temática (ex: Ficção, Ciência, História)
    int ano;             // Ano de publicação
    char editora[30];    // Nome da editora
};

/*
 * Variável global para controlar quantos livros já foram cadastrados.
 * Ela é atualizada na função cadastrarLivros e usada pelas outras.
 */
int quantidadeCadastrada = 0;

/*
 * Função para limpar o buffer de entrada.
 * Necessário após usar scanf, pois o '\n' fica no buffer e estraga o próximo fgets.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Declaração das funções usadas no programa */
void cadastrarLivros(struct Livro acervo[], int tamanho);
void imprimirLivros(struct Livro acervo[], int tamanho);
void pesquisarLivro(struct Livro acervo[], int tamanho);
void ordenarLivros(struct Livro acervo[], int tamanho);

/*
 * Função principal: exibe um menu e chama as funções do sistema.
 * Repete até o usuário escolher a opção "5 — Sair".
 */
int main() {
    struct Livro acervo[TAMANHO_ACERVO];   // Vetor que armazena todos os livros
    int opcao;                             // Armazena a opção escolhida pelo usuário

    // Loop principal (menu repetitivo)
    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE LIVROS =====\n");
        printf("1 - Cadastrar livros\n");
        printf("2 - Imprimir todos os livros\n");
        printf("3 - Pesquisar livro por codigo\n");
        printf("4 - Ordenar livros por ano\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();                    // Limpa o \n deixado no buffer

        /*
         * O switch chama uma função diferente dependendo da escolha do usuário.
         */
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
                printf("Opcao invalida!\n");  // Caso o usuário digite uma opção inexistente
        }

    } while(opcao != 5);   // Continua até que o usuário digite 5

    return 0;
}

/*
 * Cadastra vários livros no vetor acervo.
 * Lê os dados de entrada usando scanf e fgets, garantindo que textos com espaço sejam aceitos.
 */
void cadastrarLivros(struct Livro acervo[], int tamanho) {
    int quantidade;

    printf("\nQuantos livros deseja cadastrar? (max %d): ", tamanho);
    scanf("%d", &quantidade);
    limparBuffer();

    // Verifica se a quantidade é válida
    if (quantidade < 1 || quantidade > tamanho) {
        printf("Quantidade invalida!\n");
        return;
    }

    quantidadeCadastrada = quantidade;   // Salva quantos livros foram cadastrados

    printf("\n=== Cadastro de Livros ===\n");

    // Loop para cadastrar cada livro individualmente
    for(int i = 0; i < quantidade; i++) {
        printf("\n--- Livro %d ---\n", i + 1);

        printf("Codigo: ");
        scanf("%d", &acervo[i].codigo);
        limparBuffer(); // Limpa o buffer para permitir os fgets seguintes

        // Leitura do título do livro usando fgets (aceita espaços)
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

/*
 * Imprime todos os livros cadastrados até o momento.
 * Recebe "tamanho" para saber quantos livros existem no acervo.
 */
void imprimirLivros(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado ainda!\n");
        return;
    }

    printf("\n=== Lista de Livros ===\n");

    // Loop que imprime cada campo de cada livro
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

/*
 * Pesquisa um livro pelo código.
 * Faz busca linear no vetor e imprime o livro encontrado.
 */
void pesquisarLivro(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado para pesquisar!\n");
        return;
    }

    int codigoBusca;
    int encontrado = 0;  // Flag que indica se o livro foi encontrado

    printf("\nDigite o codigo do livro para pesquisar: ");
    scanf("%d", &codigoBusca);
    limparBuffer();

    // Busca sequencial pelo código
    for(int i = 0; i < tamanho; i++) {
        if(acervo[i].codigo == codigoBusca) {
            printf("\n=== Livro encontrado ===\n");
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1;
            break;  // Sai do loop após encontrar
        }
    }

    if(!encontrado) {
        printf("\nLivro nao encontrado!\n");
    }
}

/*
 * Ordena os livros cadastrados usando Bubble Sort.
 * Critério de ordenação: ano de publicação (do menor para o maior).
 * Bubble Sort é suficiente aqui porque o acervo tem no máximo 20 itens.
 */
void ordenarLivros(struct Livro acervo[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum livro cadastrado para ordenar!\n");
        return;
    }

    struct Livro temp;  // Variável auxiliar para troca

    // Algoritmo Bubble Sort
    for(int i = 0; i < tamanho - 1; i++) {
        for(int j = 0; j < tamanho - 1 - i; j++) {
            if(acervo[j].ano > acervo[j + 1].ano) {
                // Troca de posições
                temp = acervo[j];
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = temp;
            }
        }
    }

    printf("\nLivros ordenados por ano com sucesso!\n");
}
