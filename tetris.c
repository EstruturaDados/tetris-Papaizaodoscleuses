#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5

typedef struct {
    int id;
    char tipo[2];
} Peca;

typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

Peca gerarPeca(int id) {
    Peca nova;
    nova.id = id;
    char tipos[7][2] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(nova.tipo, tipos[rand() % 7]);
    return nova;
}

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->pecas[f->fim] = gerarPeca(i + 1);
        f->fim = (f->fim + 1) % TAM_FILA;
        f->quantidade++;
    }
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

Peca dequeue(Fila *f) {
    Peca removida = {0, ""};
    if (filaVazia(f)) return removida;
    removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) return;
    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return;
    }
    printf("\nFila de peças:\n");
    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        printf("Peça %s (ID %d)\n", f->pecas[i].tipo, f->pecas[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);
    int opcao, idCont = TAM_FILA;

    do {
        printf("\n1 - Jogar peça\n2 - Inserir nova peça\n3 - Mostrar fila\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            if (strlen(jogada.tipo) > 0)
                printf("Jogou peça %s (ID %d)\n", jogada.tipo, jogada.id);
            idCont++;
            enqueue(&fila, gerarPeca(idCont));
        } 
        else if (opcao == 2) {
            idCont++;
            enqueue(&fila, gerarPeca(idCont));
        } 
        else if (opcao == 3) {
            mostrarFila(&fila);
        }

    } while (opcao != 0);

    return 0;
}
