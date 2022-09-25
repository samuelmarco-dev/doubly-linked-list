#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define LENGTH 5
#define LIMIT 50

typedef struct nodeItem {
    int info;
    struct nodeItem *next;
    struct nodeItem *prev;
} node;

typedef struct {
    node *head; //first ou cabeça
    node *tail; //last ou calda
} list;

list *newList();
node *newNode(int value);
void addNode(list *l, int value, int index);
node *getNode(list *l, int index);
int length(list *l);
int indexOf(list *l, int value);
void delNodeByIndex(list *l, int index);
void delNodeByValue(list *l, int value);

void removeMultiples(list *l, int multiple);
void addAverageValue(list *l);

void showList(list *l, int order);
int isIndexInvalid(list *l, int index);
int isListEmpty(list *l);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    list *l = newList();

    for (int i = 0; i < LENGTH; i++) {
        addNode(l, rand() % LIMIT, i);
    }

    showList(l, 1);
    return 0;
}

list *newList() {
    list *l = (list *) malloc(sizeof (list));
    l->head = NULL;
    l->tail = NULL;

    return l;
}

node *newNode(int value) {
    node *n = (node *) malloc(sizeof (node));
    n->info = value;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

void addNode(list *l, int value, int index) {
    node *n = newNode(value);

    if(isIndexInvalid(l, index)) {
        printf("The index passed does not exist in the list and cannot be created!\n");
        exit(1);
    }
    if(isListEmpty(l)) {
        l->head = n;
        l->tail = n;
        return;
    }

    if(index == 0){
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    } else if(index == length(l)) {
        n->prev = l->tail;
        l->tail->next = n;
        l->tail = n;
    } else {
        node *aux = getNode(l, index-1);
        //aux->next é o próximo nó de aux, que precisa ser o sucessor do nó criado
        n->prev = aux;
        n->next = aux->next;
        aux->next->prev = n;
        aux->next = n;
    }
}

node *getNode(list *l, int index) {
    node *n = l->head;

    while (index > 0) {
        n = n->next;
        index--;
    }

    return n;
}

void addAverageValue(list *l) {
    node *new, *next;
    node *aux = l->head;

    if(isListEmpty(l) || length(l) < 2) {
        printf("It is not possible to enter the middle");
        return;
    }

    while (aux != NULL) {
        if(aux->next != NULL && aux->next->prev != NULL) {
            next = aux->next;
            new = newNode((aux->info + next->info)/2);

            new->prev = aux;
            new->next = next;
            next->prev = new;
            aux->next = new;
        }
        aux = aux->next;
    }
}

int length(list *l) {
    node *n = l->head;
    int size = 0;

    while (n != NULL) {
        size++;
        n = n->next;
    }

    return size;
}

int indexOf(list *l, int value) {
    int index = 0;
    node *n = l->head;

    if(isListEmpty(l)) {
        printf("Cannot find index in an empty list!\n");
        return -1;
    }

    while (n != NULL) {
        if(n->info == value) return index;
        index++;
        n = n->next;
    }

    return -1;
}

void delNodeByIndex(list *l, int index) {
    node *n;

    if(index < 0 || index >= length(l)) {
        printf("The index passed does not exist in the list!\n");
        return;
    }
    if(isListEmpty(l)) {
        printf("Unable to delete an element from an empty list!\n");
        return;
    }

    if(index == 0) {
        n = l->head;
        l->head = n->next;
        if(l->head != NULL) {
            l->head->prev = NULL;
        } else {
            l->tail = NULL;
        }
    } else if(index == length(l) - 1) {
        n = l->tail;
        l->tail = n->prev;
        l->tail->next = NULL;
    } else {
        n = getNode(l, index);
        if(n == NULL) return;
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    free(n);
}

void delNodeByValue(list *l, int value) {
    int indexNode = indexOf(l, value);

    while (indexNode != -1) {
        delNodeByIndex(l, indexNode);
        indexNode = indexOf(l, value);
    }
}

void removeMultiples(list *l, int multiple) {
    printf("\nList in removeMultiples:\n");
    showList(l, 1);
    node *n = l->head;
    int index;

    if(isListEmpty(l)) {
        printf("Unable to delete an multiples from an empty list!\n");
        return;
    }

    while(n != NULL) {
        if(n->info % multiple == 0) {
            delNodeByValue(l, n->info);
        }
        n = n->next;
    }
}

void showList(list *l, int order) {
    node *n;
    if(isListEmpty(l)) {
        printf("Cannot show elements of an empty list!\n");
        return;
    }
    printf("Show list:\n-> ");

    if(order != 0) {
        n = l->head;
        while (n != NULL) {
            printf("%d ", n->info);
            n = n->next;
        }
    } else {
        n = l->tail;
        while (n != NULL) {
            printf("%d ", n->info);
            n = n->prev;
        }
    }
    printf("\n");
}

int isIndexInvalid(list *l, int index) {
    return index < 0 || index > length(l);
}

int isListEmpty(list *l) {
    return l->head == NULL && l->tail == NULL;
}
