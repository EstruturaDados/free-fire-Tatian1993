#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// Struct base para os itens
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor de itens
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Lista encadeada
No* inicioLista = NULL;

// Contadores de comparação
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funções para vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: "); scanf(" %[^\n]", novo.nome);
    printf("Tipo: "); scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);
    mochilaVetor[totalVetor++] = novo;
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item a remover: "); scanf(" %[^\n]", nome);
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalVetor--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void listarItensVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < totalVetor; i++)
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("Itens ordenados por nome.\n");
}

void buscarSequencialVetor() {
    char nome[30];
    comparacoesSequencial = 0;
    printf("Nome do item a buscar: "); scanf(" %[^\n]", nome);
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado: %s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    char nome[30];
    comparacoesBinaria = 0;
    printf("Nome do item a buscar (binária): "); scanf(" %[^\n]", nome);
    int inicio = 0, fim = totalVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) {
            printf("Item encontrado: %s | %s | %d\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoesBinaria);
}

// Funções para lista encadeada
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: "); scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: "); scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicioLista;
    inicioLista = novo;
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover: "); scanf(" %[^\n]", nome);
    No *atual = inicioLista, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicioLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}

void listarItensLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = inicioLista;
    while (atual != NULL) {
        printf("%s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nome[30];
    comparacoesSequencial = 0;
    printf("Nome do item a buscar: "); scanf(" %[^\n]", nome);
    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s | %s | %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado. Comparações: %d\n", comparacoesSequencial);
}

// Menu principal
int main() {
    int estrutura, opcao;
    printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n> ");
    scanf("%d", &estrutura);

    do {
        printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Sequencial\n");
        if (estrutura == 1) printf("5. Ordenar\n6. Buscar Binária\n");
        printf("0. Sair\n> ");
        scanf("%d", &opcao);

        if (estrutura == 1) {
            switch (opcao) {
                case 1: inserirItemVetor(); break;
                case 2: removerItemVetor(); break;
                case 3: listarItensVetor(); break;
                case 4: buscarSequencialVetor(); break;
                case 5: ordenarVetor(); break;
                case 6: buscarBinariaVetor(); break;
            }
        } else {
            switch (opcao) {
                case 1: inserirItemLista(); break;
                case 2: removerItemLista(); break;
                case 3: listarItensLista(); break;
                case 4: buscarSequencialLista(); break;
            }
        }
    } while (opcao != 0);

    return 0;
}