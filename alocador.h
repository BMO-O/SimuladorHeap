/*  Gabriel Rodrigues Marques Valim && Nuno Martins do Couto && Breno Machado de Oliveira
    Modularização para o Simulador Heap - Paradigmas de Programação 
*/

#ifndef ALOCADOR_H
#define ALOCADOR_H

#include <stdio.h>
#include <stdlib.h>

/* Estruturas de dados usadas */
typedef struct areas_vazias {   // Lista Encadeada de áreas vazias no heap
    int inicial;                // Índice inicial do espaço livre
    int quantidade;             // Quantidade de espaços livres
    struct areas_vazias* next;  // Próximo nó da lista encadeada
} areas_vazias;

typedef struct id {
    char id;                    // Identificador (ex.: A, B, C, etc.)
    int quantidade;             // Quantidade alocada
    int inicial;                // Índice inicial no heap
} id;

/* Enum para selecionar o método de alocação */
typedef enum {
    FIRST_FIT = 1,
    BEST_FIT,
    NEXT_FIT,
    WORST_FIT,
    DELETE_ID,
    SAIR
} Menu;

/* Protótipos das funções */
areas_vazias* new_node(areas_vazias* head, int endereco, int quantidade);
void fit(id identificador, int endereco, int quantidade, char* heap);
areas_vazias* pop_front(areas_vazias* head);
areas_vazias* remove_item(areas_vazias* head, int c);
areas_vazias* update_empty_memory(areas_vazias* head, int indice, int qtd);
void remove_from_heap(char* heap, int endereco, int quantidade);
void free_list(areas_vazias* head);
areas_vazias* insertion_sort(areas_vazias* head);
areas_vazias* aglutinacao(areas_vazias* head);
int maior_qtd_lista(areas_vazias* a);

#endif
