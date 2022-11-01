#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "productList.h"

struct List{
    int key;
    char name[25];
    float price;
    float qtt;
    float total;
    List* next;
};
List* insertListNode(List* list, int key, char name[], float price, float qtt){
    if(!list){
        list = (List*) malloc(sizeof(List));
        list->key = key;
        strcpy(list->name, name);
        list->price = price;
        list->qtt = qtt;
        list->total = price * qtt;
        list->next = NULL;
    }
    //o produto ja esta na lista
    else if(key == list->key){
        list->qtt += qtt;
        list->total += qtt * price;
    }
    else{
        list->next = insertListNode(list->next, key, name, price, qtt);
    }
    return list;
}
List* deleteListNode(List* list, int key){
    List* aux;
    
    if(list->key == key){
        aux = list->next;
        free(list);
        return aux;

    }else if(list->next->key == key){
        aux = list->next;
        list->next = aux->next;
        free(aux);
    }else{
        list->next = deleteListNode(list->next, key);
    }
    return list;
}
void printList(List* list){
    if(list){
        printf("\n[%2i] %.8s %.2f %.3f %.2f\n", list->key, list->name, list->price, list->qtt, list->total);
        printList(list->next);
    }
}
void deleteList(List* list, Tree* root){
    int i;
    int n = biggest(root);

    for(i = 1; i <= n; i++){
        if(findKey(root, i) == 1)
            list = deleteListNode(list, i);
    }
}