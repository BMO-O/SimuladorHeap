/*  Gabriel Rodrigues Marques Valim && Nuno Martins do Couto && Breno Machado de Oliveira
    Modularização para o Simulador Heap - Paradigmas de Programação 
*/

#include "alocador.h"

/* Cria um nó na lista encadeada */
areas_vazias* new_node(areas_vazias* head, int endereco, int quantidade) {
    areas_vazias* node = (areas_vazias*)malloc(sizeof(areas_vazias));
    node->inicial = endereco;
    node->quantidade = quantidade;
    node->next = head;
    return node;
}

/* Aloca no heap */
void fit(id identificador, int endereco, int quantidade, char* heap) {
    for (int i = endereco; i < endereco + quantidade; i++) {
        heap[i] = identificador.id;
    }
}

/* Remove o primeiro nó da lista */
areas_vazias* pop_front(areas_vazias* head) {
    if (head == NULL)
        return NULL;
    areas_vazias* new_head = head->next;
    free(head);
    return new_head;
}

/* Remove um nó específico da lista */
areas_vazias* remove_item(areas_vazias* head, int c) {
    if (head == NULL)
        return NULL;
    if (head->inicial == c)
        return pop_front(head);

    areas_vazias* p = head;
    areas_vazias* n = p->next;
    while (n != NULL && n->inicial != c) {
        p = n;
        n = n->next;
    }
    if (n != NULL) {
        p->next = n->next;
        free(n);
    }
    return head;
}

/* Atualiza a lista de áreas livres após uma alocação */
areas_vazias* update_empty_memory(areas_vazias* head, int indice, int qtd) {
    areas_vazias* aux = head;
    while (aux->inicial != indice) {
        aux = aux->next;
    }
    if (aux != NULL) {
        aux->quantidade -= qtd;
        if (aux->quantidade == 0) {
            head = remove_item(head, aux->inicial);
        } else {
            aux->inicial += qtd;
        }
    }
    return head;
}

/* Remove um ID do heap */
void remove_from_heap(char* heap, int endereco, int quantidade) {
    for (int i = endereco; i < endereco + quantidade; i++) {
        heap[i] = ' ';
    }
}

/* Libera a lista encadeada de áreas livres */
void free_list(areas_vazias* head) {
    if (head) {
        free_list(head->next);
        free(head);
    }
}

/* Ordena a lista de áreas livres por índice usando Insertion Sort */
areas_vazias* insertion_sort(areas_vazias* head) {
    if (head == NULL || head->next == NULL) {
        return head; // Lista vazia ou com um elemento, já está ordenada
    }
    areas_vazias* sorted = NULL; // Lista ordenada
    areas_vazias* current = head; // Nó atual da lista desordenada
    while (current != NULL) {
        areas_vazias* next = current->next; // Guarda o próximo nó
        areas_vazias* prev = NULL; // Nó anterior na lista ordenada
        areas_vazias* ptr = sorted; // Itera sobre a lista ordenada
        while (ptr != NULL && ptr->inicial < current->inicial) {
            prev = ptr;
            ptr = ptr->next;
        }
        // Insere o nó 'current' na posição correta na lista ordenada
        if (prev == NULL) {
            current->next = sorted;
            sorted = current;
        } else {
            current->next = ptr;
            prev->next = current;
        }
        current = next; // Avança para o próximo nó na lista desordenada
    }
    return sorted; // Retorna a lista ordenada
}

/* Junta áreas livres adjacentes na lista */
areas_vazias* aglutinacao(areas_vazias* head) {
    if (head == NULL || head->next == NULL)
        return head;

    areas_vazias* current = head;
    while (current->next != NULL) {
        if (current->inicial + current->quantidade == current->next->inicial) {
            current->quantidade += current->next->quantidade;
            areas_vazias* temp = current->next; // Guarde o próximo nó temporariamente
            current->next = temp->next; // Pule o nó que será liberado
            free(temp); // Liberar o nó que foi agrupado
        } else {
            current = current->next;
        }
    }
    return head;
}

/* Retorna a maior quantidade de um nó da lista */
int maior_qtd_lista(areas_vazias* a) {
    int maior = a->quantidade;
    while (a != NULL) {
        if (a->quantidade > maior)
            maior = a->quantidade;
        a = a->next;
    }
    return maior;
}
