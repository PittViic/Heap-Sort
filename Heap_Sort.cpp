#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int numeros[MAX];
    int qtd;
} heap_struct;

heap_struct heap;

int pai_pos(int pos){
    return (pos - 1)/2;
}

void swap(int pos1, int pos2){
    int aux = heap.numeros[pos1];
    heap.numeros[pos1] = heap.numeros[pos2];
    heap.numeros[pos2] = aux;
}

int filho1_pos(int pos){
    int pos_filho1 = 2 * pos + 1;
    if(pos_filho1 >= heap.qtd){
        return -1;
    }
    return pos_filho1;
}

int filho2_pos(int pos){
    int pos_filho2 = 2 * pos + 2;
    if(pos_filho2 >= heap.qtd){
        return -1;
    }
    return pos_filho2;
}

void ordenar_pai(int indice){
    if(indice == 0){
        printf("Parar, esta na raiz!\n");
        return;
    }
    int indice_pai = pai_pos(indice);
    int filho = heap.numeros[indice];
    int pai = heap.numeros[indice_pai];
    if(filho <= pai){
        printf("Parar, filho menor que pai!\n");
        return;
    } else {
        swap(indice, indice_pai);
        ordenar_pai(indice_pai);
    }
}

void ordenar_filhos(int indice){
    int f1_indice = filho1_pos(indice);
    if(f1_indice > 0){
        if(heap.numeros[indice] < heap.numeros[f1_indice]){
            swap(indice, f1_indice);
            ordenar_filhos(f1_indice);
        }
    }
    int f2_indice = filho2_pos(indice);
    if(f2_indice > 0){
        if(heap.numeros[indice] < heap.numeros[f2_indice]){
            swap(indice, f2_indice);
            ordenar_filhos(f2_indice);
        }
    }
}

void inserir_heap(int num){
    if(heap.qtd >= MAX){
        printf("Heap cheio!\n");
        return;
    }
    heap.numeros[heap.qtd] = num;
    heap.qtd++;

    ordenar_pai(heap.qtd - 1);
}

void imprimir_heap(){
    printf("Quantidade: %d | ", heap.qtd);
    for(int i = 0; i < heap.qtd; i++){
        printf("%d - ", heap.numeros[i]);
    }
    printf("\n");
}

int remover_heap(){
    if(heap.qtd <= 0){
        printf("Heap vazia!");
        return -1;
    }
    int remover = heap.numeros[0];
    heap.qtd--;
    swap(0, heap.qtd);

    ordenar_filhos(0);

    return remover;
}

void menu(){
    printf("##############################\n");
    printf("# 1 - Adicionar              #\n");
    printf("# 2 - Remover                #\n");
    printf("# 3 - Imprimir               #\n");
    printf("# 0 - Sair                   #\n");
    printf("##############################\n");
    printf("Opcao Selecionada: ");
}

int main(){
    int option;
    int num;

    do{
        menu();
        scanf("%d", &option);

        switch(option){
            case 0:
                printf("Leaving...\n");
                break;
            case 1:
                printf("Numero a adiconar: ");
                scanf("%d", &num);

                inserir_heap(num);
                break;
            case 2:
                printf("Numero a remover: %d", remover_heap());
                break;
            case 3:
                imprimir_heap();
                break;
        }
    } while(option != 0);

    return 0;
}