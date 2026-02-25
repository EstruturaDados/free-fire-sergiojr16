#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Biblioteca crucial para medir o tempo (clock)

#define MAX_COMP 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

Componente torre[MAX_COMP];
int totalComp = 0;

// ==========================================
// FUNÇÕES AUXILIARES DE ENTRADA/SAÍDA
// ==========================================

// Função para remover o 'Enter' (\n) deixado pelo fgets
void removerNovaLinha(char* string) {
    string[strcspn(string, "\n")] = 0;
}

void mostrarComponentes(Componente arr[], int n) {
    printf("\n--- COMPONENTES DA TORRE DE FUGA (%d/%d) ---\n", n, MAX_COMP);
    if (n == 0) printf("Nenhum componente registado ainda.\n");
    for (int i = 0; i < n; i++) {
        printf("%d. [%s] | Tipo: %s | Prioridade: %d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("--------------------------------------------\n");
}

void inserirComponente() {
    if (totalComp >= MAX_COMP) {
        printf("\nTorre cheia! Limite de componentes atingido.\n");
        return;
    }
    char buffer[50]; // Usado para ler os números com segurança

    printf("\n--- Novo Componente ---\n");
    printf("Nome (ex: chip central): ");
    fgets(torre[totalComp].nome, 30, stdin);
    removerNovaLinha(torre[totalComp].nome);

    printf("Tipo (ex: controle, propulsao): ");
    fgets(torre[totalComp].tipo, 20, stdin);
    removerNovaLinha(torre[totalComp].tipo);

    printf("Prioridade (1 a 10): ");
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d", &torre[totalComp].prioridade);

    totalComp++;
    printf("Componente anexado com sucesso!\n");
}


// Bubble Sort: Ordena por NOME
int bubbleSortNome(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort: Ordena por TIPO
int insertionSortTipo(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;

        // Move os elementos que são maiores que a chave uma posição para a frente
        while (j >= 0) {
            comparacoes++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break; // Se já está na ordem certa, para de procurar
            }
        }
        arr[j + 1] = chave;
    }
    return comparacoes;
}

// Selection Sort: Ordena por PRIORIDADE (decrescente: 10 até 1)
int selectionSortPrioridade(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int indiceMaior = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (arr[j].prioridade > arr[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        // Troca o maior encontrado com a primeira posição não ordenada
        Componente temp = arr[i];
        arr[i] = arr[indiceMaior];
        arr[indiceMaior] = temp;
    }
    return comparacoes;
}


// Função modular que recebe a função de ordenação como parâmetro!
void medirTempo(int (*algoritmo)(Componente[], int), Componente arr[], int n, const char* nomeOperacao) {
    clock_t inicio = clock();           // Dispara o cronómetro
    int comps = algoritmo(arr, n);      // Executa a ordenação escolhida
    clock_t fim = clock();              // Pára o cronómetro
    
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("\n=== RESULTADOS DE DESEMPENHO ===");
    printf("\nEstrategia: %s", nomeOperacao);
    printf("\nComparacoes realizadas: %d", comps);
    printf("\nTempo: %f segundos\n", tempoExecucao);
    printf("================================\n");
    
    mostrarComponentes(arr, n);
}

// Busca Binária por NOME (O vetor TEM de estar ordenado por nome)
void buscaBinariaPorNome(Componente arr[], int n, char alvo[]) {
    int inicio = 0, fim = n - 1, comps = 0;
    
    while (inicio <= fim) {
        comps++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(arr[meio].nome, alvo);
        
        if (resultado == 0) {
            printf("\n[SUCESSO] COMPONENTE CHAVE '%s' ENCONTRADO!\n", alvo);
            printf("Comparações feitas pela busca binária: %d\n", comps);
            printf("Torre ativada. INICIAR FUGA!\n");
            return;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\n[ALERTA] Componente '%s' nao encontrado ou a lista nao esta ordenada por Nome!\n", alvo);
}

int main() {
    char opcaoStr[10];
    int opcao;
    char chaveDeBusca[30];

    do {
        printf("\n=== TERMINAL DE MONTAGEM DA TORRE ===");
        printf("\n1. Cadastrar Componente");
        printf("\n2. Listar Componentes");
        printf("\n3. Ordenar por Nome (Bubble Sort)");
        printf("\n4. Ordenar por Tipo (Insertion Sort)");
        printf("\n5. Ordenar por Prioridade (Selection Sort)");
        printf("\n6. Inserir CHAVE DE ATIVACAO (Busca Binaria por Nome)");
        printf("\n0. Abortar Missao (Sair)");
        printf("\nComando: ");
        
        fgets(opcaoStr, 10, stdin);
        sscanf(opcaoStr, "%d", &opcao);

        switch(opcao) {
            case 1: inserirComponente(); break;
            case 2: mostrarComponentes(torre, totalComp); break;
            case 3: medirTempo(bubbleSortNome, torre, totalComp, "Bubble Sort (Nome)"); break;
            case 4: medirTempo(insertionSortTipo, torre, totalComp, "Insertion Sort (Tipo)"); break;
            case 5: medirTempo(selectionSortPrioridade, torre, totalComp, "Selection Sort (Prioridade)"); break;
            case 6:
                printf("\nDigite o nome do componente-chave para ativar a torre: ");
                fgets(chaveDeBusca, 30, stdin);
                removerNovaLinha(chaveDeBusca);
                buscaBinariaPorNome(torre, totalComp, chaveDeBusca);
                break;
            case 0: printf("\nMissao abortada. Fim de jogo...\n"); break;
            default: printf("\nComando nao reconhecido. Tenta novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}