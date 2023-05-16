#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void null_pointer (List*);

typedef struct node Node;
struct node {
    Node* next;
    int data;
    Node* prev;
};


struct list {
    Node* head;
    Node* tail;
    int lenght;
};


List* list_create (void){
    List* new_list = (List*)malloc(sizeof(List));
    new_list->head = NULL;
    new_list->lenght = 0;
    new_list-> tail = NULL;
    return new_list;
}

void list_free(List *list){
    Node *aux;
    while (list->head!= NULL) {
        aux = list->head;
        list->head = list->head->next;
        free (aux);
    }
    free(list);
}


void list_add(List *list, int value){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->data = value;
    new_node->prev = NULL;


    if (list->head == NULL){
        list->lenght++;
        list->head = new_node;
        list->tail = new_node;
        return;
    }
    list->tail->next = new_node;
    new_node->prev = list->tail;
    list->tail = new_node;
    list->lenght++;
}

void list_display(List *list){
    if (list->lenght == 0){
        printf("ERRO EMPTY LIST\n");
        null_pointer(list);
        return;
    }
    Node *current = list->head;
    printf("[");
    while (current != NULL) {
        if (current == list->tail){
             printf("%i", current->data);
             break;
        }
        printf("%i,", current->data);
        current = current->next;
    }
    printf("]\n");
    printf("Lenght -> %d\n", list->lenght);
}

void  list_display_reverse(List *list){
    if (list->lenght == 0){
        printf("ERRO EMPTY LIST\n");
        null_pointer(list);
        return;
    }    
    Node *current = list->tail;
    if (list->lenght == 0){
        printf("[]\n");
        printf("Lenght -> %d\n", list->lenght);
        return;
    }
    printf("[");
    while (current != NULL) {
        if (current == list->head){
            printf("%i", current->data);
            break;
        }
        printf("%i,", current->data);
        current = current->prev;
    }
    printf("]\n");
    printf("Lenght -> %d\n", list->lenght);
}


int list_get(List* list, int index){
    if (list->lenght == 0){
        printf("ERRO EMPTY LIST\n");
        null_pointer(list);
        return -1;
    }
    Node *current = list->head;
    if (index == 0){
        return current->data;
    }
    int count = 0;
    while (current != NULL){
        if (index == count){
            return current->data;
        }
        count++;
        current = current->next;
    }
    printf("ERRO!Invalid index\n");
    return -1;
}

int list_remove (List* list, int index){
    if ((list->head == NULL) || (list->lenght == 0)){
        printf("Erro!Empty list\n");
        null_pointer(list);
        return -1;
    }

    Node *current = list->head;
    int value_returned;
    if (index == 0){
        list->head = list->head->next;
        value_returned = current->data;
        free(current);
        list->lenght--;
        return value_returned;
    }

    if (index == list->lenght-1){
        value_returned = list->tail->data;
        current = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(current);
        list->lenght--;
        return value_returned;
    }


    int count = 0;
    while (current != NULL) {
        if (index == count){
            value_returned = current->data;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            list->lenght--;
            return value_returned;

        }
        count++;
        current = current->next;
    }
    printf("Erro!Invalid index\n");
    return -1;
}

//deixa nulo todos os ponteiros da lista para casos em que o list lenght = 0 (ou seja n tem nd na lista)
void null_pointer (List* list){
    list->head = NULL;
    list->tail = NULL;
}



void list_insert(List* list, int index, int value){
    if (list->lenght == 0){
        list_add(list, value);
        return;
    }


    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    if (index == 0){
        new_node->prev = NULL;
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        list->lenght++;
        return;
    }

    Node *current = list->head;
    int count = 0;
    while (current != NULL) {
        if (index == count){
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            list->lenght++;
            return;
        }
        count++;
        current = current->next;
    }
    printf("ERRO!Invalid index\n");
    return;

}


void list_set(List* list, int index, int value){
    if (list->lenght == 0){
        printf("ERRO EMPTY LIST\n");
        null_pointer(list);
        return;
    }

    if (index == 0){
        list->head->data = value;
        return;
    }

    Node *current = list->head;
    int count = 0;
    while (current!= NULL) {
        if (count == index){
            current->data = value;
            return;
        }
        count++;
        current = current->next;
    }
    printf("ERRO!Invalid index");
    return;
}