/*  Gabriel Rodrigues Marques Valim && Nuno Martins do Couto && Breno Machado de Oliveira
    Simulador de Heap - Paradigmas de Programação 
*/

#include "alocador.h"

/*-------------------------------------------------------------------*/
//TERMINAR DE COMENTAR O CÓDIGO
/*-------------------------------------------------------------------*/

                             /* Início da main() */
int main() {
    /*Declaração de variáveis */
    char* heap = calloc(10, sizeof(char));  // Criando um heap
    areas_vazias* head = NULL;
    head = new_node(head, 0, 10);  // Iniciando a lista de espaços livres

    id A[10];  // Identificadores
    for (int g = 0; g < 10; g++) {
        A[g].id = ' ';  // Inicializa todos os IDs como vazios, representados por espaços
    }

    Menu opcao = 0;
    int qtd;
    char identificador;
    int i, j;
    int last_indice = 0; //Utilizado para o Next Fit
    int indice;
    areas_vazias* auxiliar, * auxiliar1;

    const char* nomes[] = {
        "Inválido", "First Fit", "Best Fit", "Next Fit", "Worst Fit", "Delete", "Sair"
    };
    /*Fim da declaração de variáveis*/


    while (opcao != SAIR) {
        // Imprime o estado atual do heap
        for (int z = 0; z < 10; z++) {
            printf("[%c] ", heap[z]);
        }

        printf("\n\n");

        // Leitura do teclado & Menu
        for (int i = FIRST_FIT; i <= SAIR; i++) {
            printf("%d - %s\n", i, nomes[i]);
        }
        //Validação da entrada
        do {
            scanf("%d", (int*)&opcao);

            // Se a entrada estiver fora do intervalo, pede novamente
            if (opcao < FIRST_FIT || opcao > SAIR) {
                printf("\nOpção inválida. Digite novamente:\n");
            }

            while (getchar() != '\n'); // Limpa qualquer lixo que sobrar no buffer

        } while (opcao < FIRST_FIT || opcao > SAIR);

        if (opcao == SAIR) // Finaliza o Código
            break;

        // Entrada de dados caso não seja uma remoção
        if (opcao != DELETE_ID) {
            if (head == NULL) {
                printf("\n\nMemória Lotada, remova um espaço antes de alocar!\n\n");
                opcao = DELETE_ID;
            } else {
                puts("Digite a quantidade de memória que quer alocar:");
                scanf("%d", &qtd);

                if (qtd <= maior_qtd_lista(head)) {
                    puts("Digite o ID:");
                    scanf(" %c", &identificador);
                   
                    // Procurando espaço vazio no vetor de IDs
                    for (j = 0; j < 10;/*Numeros de IDs do vetor Struct*/ j++) {
                        if (A[j].id == ' ') {
                            A[j].id = identificador;
                            A[j].quantidade = qtd;
                            break;
                        }
                    }
                } else {
                    puts("\nVocê quer alocar mais que a quantidade disponível!");
                    printf("\n");
                }
            }
        }

        // Escolha do método de alocação ou remoção
        switch (opcao) {
            case FIRST_FIT:
                auxiliar = head;
                while (auxiliar != NULL) {
                    if (auxiliar->quantidade >= qtd) {
                        A[j].inicial = auxiliar->inicial; // Guardando a posição do heap que o ID está
                        fit(A[j], auxiliar->inicial, qtd, heap);
                        last_indice = auxiliar->inicial;
                        head = update_empty_memory(head, auxiliar->inicial, qtd);
                        break;
                    } else
                        auxiliar = auxiliar->next;
                }
                break;

            case BEST_FIT:
                auxiliar1 = head;
                int menor = auxiliar1->quantidade;
                indice = auxiliar1->inicial;
                while (auxiliar1 != NULL) {
                    if (auxiliar1->quantidade >= qtd && auxiliar1->quantidade <= menor) {
                        indice = auxiliar1->inicial;
                        menor = auxiliar1->quantidade;
                    }
                    auxiliar1 = auxiliar1->next;
                }
                A[j].inicial = indice;
                fit(A[j], indice, qtd, heap);
                last_indice = indice;
                head = update_empty_memory(head, indice, qtd);
                break;

            case NEXT_FIT:
                auxiliar = head;
                while (auxiliar != NULL && auxiliar->inicial < last_indice) {
                    auxiliar = auxiliar->next;
                }

                if (auxiliar == NULL)
                    auxiliar = head;

                areas_vazias* start = auxiliar;
                do {
                    if (auxiliar->quantidade >= qtd) {
                        A[j].inicial = auxiliar->inicial;
                        fit(A[j], auxiliar->inicial, qtd, heap);
                        last_indice = auxiliar->inicial;
                        head = update_empty_memory(head, auxiliar->inicial, qtd);
                        break;
                    }
                    auxiliar = auxiliar->next;
                    if (auxiliar == NULL)
                        auxiliar = head;

                } while (auxiliar != start);

                if (auxiliar == start && start->quantidade < qtd) {
                    printf("Sem espaço pro next fit\n");
                }
                break;

            case WORST_FIT:
                auxiliar1 = head;
                int maior = auxiliar1->quantidade;
                indice = auxiliar1->inicial;
                while (auxiliar1 != NULL) {
                    if (auxiliar1->quantidade >= qtd && auxiliar1->quantidade >= maior) {
                        indice = auxiliar1->inicial;
                        maior = auxiliar1->quantidade;
                    }
                    auxiliar1 = auxiliar1->next;
                }
                A[j].inicial = indice;
                fit(A[j], indice, qtd, heap);
                last_indice = indice;
                head = update_empty_memory(head, indice, qtd);
                break;

            case DELETE_ID:
                puts("Qual ID quer remover?");
                char aux3;
                scanf(" %c", &aux3);
                for (int k = 0; k < 10; k++) {
                    if (A[k].id == aux3) {
                        remove_from_heap(heap, A[k].inicial, A[k].quantidade);
                        A[k].id = ' ';
                        head = new_node(head, A[k].inicial, A[k].quantidade);
                    }
                }
                // Ordena e aglutina áreas livres após remoção
                head = insertion_sort(head);
                head = aglutinacao(head);
                break;

            default:
                break;
        }
    }

    puts("");
    areas_vazias* aux5 = head;
    while (aux5 != NULL) {
        printf("Quantidade disponível[%d] indíce[%d]\n", aux5->quantidade, aux5->inicial);
        aux5 = aux5->next;
    }

    // Liberação de memória antes de encerrar
    free_list(head);
    free(heap);
    return 0;
}
