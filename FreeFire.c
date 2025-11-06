#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais
Componente torre[MAX_COMPONENTES];
int total = 0;
int comparacoes = 0;

// Função para exibir os componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | Prioridade: %d\n", v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("----------------------------\n");
}

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        comparacoes++;
        v[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

// Busca binária por nome (após ordenação por nome)
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    int comp = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comp++;
        int cmp = strcmp(chave, v[meio].nome);
        if (cmp == 0) {
            printf("Componente encontrado: %s | %s | Prioridade: %d\n", v[meio].nome, v[meio].tipo, v[meio].prioridade);
            printf("Comparações na busca binária: %d\n", comp);
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    printf("Componente não encontrado. Comparações: %d\n", comp);
    return -1;
}

// Função para medir tempo de execução de um algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Comparações realizadas: %d\n", comparacoes);
}

// Função para cadastrar componentes
void cadastrarComponentes() {
    printf("Quantos componentes deseja cadastrar (máx %d)? ", MAX_COMPONENTES);
    scanf("%d", &total);
    getchar(); // limpar buffer
    if (total > MAX_COMPONENTES) total = MAX_COMPONENTES;

    for (int i = 0; i < total; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(torre[i].nome, 30, stdin);
        torre[i].nome[strcspn(torre[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(torre[i].tipo, 20, stdin);
        torre[i].tipo[strcspn(torre[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &torre[i].prioridade);
        getchar(); // limpar buffer
    }
}

// Menu principal
int main() {
    int opcao;
    char chave[30];

    cadastrarComponentes();

    do {
        printf("\n--- Menu de Estratégia ---\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente-chave (após ordenação por nome)\n");
        printf("5. Mostrar Componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 2:
                medirTempo(insertionSortTipo, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 3:
                medirTempo(selectionSortPrioridade, torre, total);
                mostrarComponentes(torre, total);
                break;
            case 4:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscaBinariaPorNome(torre, total, chave);
                break;
            case 5:
                mostrarComponentes(torre, total);
                break;
            case 0:
                printf("Encerrando missão...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}