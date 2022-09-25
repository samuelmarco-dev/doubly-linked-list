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
void showList(list *l);
int isIndexInvalid(list *l, int index);
int isListEmpty(list *l);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    list *l = newList();

    for (int i = 0; i < LENGTH; i++) {
        addNode(l, rand() % LIMIT, i);
    }
    showList(l);

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
        printf("The index passed does not exist in the list and cannot be created");
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

int length(list *l) {
    node *n = l->head;
    int size = 0;

    while (n != NULL) {
        size++;
        n = n->next;
    }

    return size;
}

int indexOf(list *l, int value) {}

void delNodeByIndex(list *l, int index) {}

void delNodeByValue(list *l, int value) {}

void showList(list *l) {
    node *n = l->head;
    if(isListEmpty(l)) {
        printf("Cannot show elements of an empty list");
        return;
    }

    printf("Show list:\n-> ");
    while (n != NULL) {
        printf("%d ", n->info);
        n = n->next;
    }
    printf("\n");
}

int isIndexInvalid(list *l, int index) {
    return index < 0 || index > length(l);
}

int isListEmpty(list *l) {
    return l->head == NULL && l->tail == NULL;
}
