#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// 1. Definição da Struct
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis globais para facilitar o acesso na mochila
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para listar todos os itens (usada após cada operação)
void listarItens() {
    printf("\n--- CONTEUDO DA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }
    for (int i = 0; i < totalItens; i++) {
        printf("%d. [%s] Tipo: %s | Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------\n");
}

// Função para cadastrar um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nErro: Mochila cheia! Deite algo fora primeiro.\n");
        return;
    }

    printf("\nNome do item: ");
    scanf("%s", mochila[totalItens].nome);
    printf("Tipo (arma/municao/cura): ");
    scanf("%s", mochila[totalItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
    printf("\nItem adicionado com sucesso!");
    listarItens();
}

// Função de Busca Sequencial
int buscarItem() {
    char termo[30];
    printf("\nDigite o nome do item para procurar: ");
    scanf("%s", termo);

    for (int i = 0; i < totalItens; i++) {
        // strcmp compara duas strings; se retornar 0, elas são iguais
        if (strcmp(mochila[i].nome, termo) == 0) {
            printf("\nItem encontrado: [%s] | Tipo: %s | Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i; // Retorna a posição se encontrar
        }
    }
    printf("\nItem '%s' nao encontrado.\n", termo);
    return -1; // Retorna -1 se não encontrar
}

// Função para remover um item
void removerItem() {
    int posicao = buscarItem();

    if (posicao != -1) {
        // Para remover, "puxamos" todos os itens seguintes uma casa para trás
        for (int i = posicao; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\nItem removido com sucesso!");
        listarItens();
    }
}

// --- FLUXO PRINCIPAL ---
int main() {
    int opcao;

    do {
        printf("\n=== MENU DE INVENTARIO ===");
        printf("\n1. Adicionar Item");
        printf("\n2. Remover Item");
        printf("\n3. Procurar Item");
        printf("\n4. Listar Tudo");
        printf("\n0. Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: buscarItem(); break;
            case 4: listarItens(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}