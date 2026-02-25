#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct base para o Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct do Nó para a Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;



// ==========================================
// VARIÁVEIS GLOBAIS E CONTADORES
// ==========================================

// Variáveis do Vetor
Item vetorMochila[MAX_ITENS];
int totalVetor = 0;

// Ponteiro inicial da Lista Encadeada
No* listaMochila = NULL;

// Contadores de desempenho
int compSeqVetor = 0;
int compBinVetor = 0;
int compSeqLista = 0;

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("\n[Vetor] Mochila cheia!\n");
        return;
    }
    printf("\n--- Novo Item (Vetor) ---\n");
    printf("Nome: "); scanf("%29s", vetorMochila[totalVetor].nome);
    printf("Tipo: "); scanf("%19s", vetorMochila[totalVetor].tipo);
    printf("Qtd: "); scanf("%d", &vetorMochila[totalVetor].quantidade);
    totalVetor++;
    printf("Item adicionado no vetor!\n");
}

void listarVetor() {
    printf("\n--- ITENS NO VETOR (%d/%d) ---\n", totalVetor, MAX_ITENS);
    for (int i = 0; i < totalVetor; i++) {
        printf("%d. [%s] Tipo: %s | Qtd: %d\n", i+1, vetorMochila[i].nome, vetorMochila[i].tipo, vetorMochila[i].quantidade);
    }
}

int buscarSequencialVetor(char* alvo) {
    compSeqVetor = 0; // Reset ao contador
    for (int i = 0; i < totalVetor; i++) {
        compSeqVetor++;
        if (strcmp(vetorMochila[i].nome, alvo) == 0) {
            return i; // Retorna a posição
        }
    }
    return -1; // Não encontrado
}

void removerItemVetor() {
    char alvo[30];
    printf("\nNome do item a remover do Vetor: ");
    scanf("%29s", alvo);
    
    int pos = buscarSequencialVetor(alvo);
    if (pos != -1) {
        for (int i = pos; i < totalVetor - 1; i++) {
            vetorMochila[i] = vetorMochila[i + 1];
        }
        totalVetor--;
        printf("Item '%s' removido do vetor!\n", alvo);
    } else {
        printf("Item nao encontrado.\n");
    }
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(vetorMochila[j].nome, vetorMochila[j+1].nome) > 0) {
                Item temp = vetorMochila[j];
                vetorMochila[j] = vetorMochila[j+1];
                vetorMochila[j+1] = temp;
            }
        }
    }
    printf("\nVetor ordenado com sucesso (Bubble Sort)!\n");
}

int buscarBinariaVetor(char* alvo) {
    compBinVetor = 0;
    int inicio = 0, fim = totalVetor - 1;
    
    while (inicio <= fim) {
        compBinVetor++;
        int meio = (inicio + fim) / 2;
        int comp = strcmp(vetorMochila[meio].nome, alvo);
        
        if (comp == 0) return meio;
        else if (comp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void inserirItemLista() {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro de alocacao de memoria!\n");
        return;
    }
    
    printf("\n--- Novo Item (Lista Encadeada) ---\n");
    printf("Nome: "); scanf("%29s", novoNo->dados.nome);
    printf("Tipo: "); scanf("%19s", novoNo->dados.tipo);
    printf("Qtd: "); scanf("%d", &novoNo->dados.quantidade);
    novoNo->proximo = NULL;

    // Inserir no final da lista
    if (listaMochila == NULL) {
        listaMochila = novoNo;
    } else {
        No* atual = listaMochila;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    printf("Item adicionado na lista encadeada!\n");
}

void listarLista() {
    printf("\n--- ITENS NA LISTA ENCADEADA ---\n");
    No* atual = listaMochila;
    int i = 1;
    if (atual == NULL) printf("Vazia.\n");
    while (atual != NULL) {
        printf("%d. [%s] Tipo: %s | Qtd: %d\n", i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char* alvo) {
    compSeqLista = 0;
    No* atual = listaMochila;
    while (atual != NULL) {
        compSeqLista++;
        if (strcmp(atual->dados.nome, alvo) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void removerItemLista() {
    char alvo[30];
    printf("\nNome do item a remover da Lista: ");
    scanf("%29s", alvo);

    No* atual = listaMochila;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, alvo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na lista.\n");
        return;
    }

    // Se for o primeiro nó a ser removido
    if (anterior == NULL) {
        listaMochila = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual); // Liberta a memória RAM
    printf("Item '%s' removido da lista!\n", alvo);
}

int main() {
    int opcao;
    char busca[30];

    do {
        printf("\n=== ZONA DE PERIGO: GESTAO DE INVENTARIO ===");
        printf("\n[ VETOR ] 1. Inserir | 2. Remover | 3. Listar | 4. Ordenar | 5. Busca Sequencial | 6. Busca Binaria");
        printf("\n[ LISTA ] 7. Inserir | 8. Remover | 9. Listar | 10. Busca Sequencial");
        printf("\n0. Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            // Operações Vetor
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: 
                printf("Procurar no Vetor: "); scanf("%29s", busca);
                if (buscarSequencialVetor(busca) != -1) 
                    printf("Encontrado! Comparações feitas: %d\n", compSeqVetor);
                else 
                    printf("Nao encontrado. Comparações: %d\n", compSeqVetor);
                break;
            case 6:
                printf("Procurar (Binaria) no Vetor (Certifica-te que esta ordenado!): "); scanf("%29s", busca);
                if (buscarBinariaVetor(busca) != -1)
                    printf("Encontrado! Comparações feitas: %d\n", compBinVetor);
                else
                    printf("Nao encontrado. Comparações: %d\n", compBinVetor);
                break;
            
            // Operações Lista Encadeada
            case 7: inserirItemLista(); break;
            case 8: removerItemLista(); break;
            case 9: listarLista(); break;
            case 10:
                printf("Procurar na Lista: "); scanf("%29s", busca);
                if (buscarSequencialLista(busca) != NULL)
                    printf("Encontrado! Comparações feitas: %d\n", compSeqLista);
                else
                    printf("Nao encontrado. Comparações: %d\n", compSeqLista);
                break;
            case 0: printf("A fechar o inventario...\n"); break;
            default: printf("Comando invalido!\n");
        }
    } while (opcao != 0);

    return 0;
}