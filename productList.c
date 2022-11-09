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
        while(strlen(list->name) < 24)
            strcat(list->name, "-");
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
        int i;
        
        printf("\n%.4i  %s R$%2.2f", list->key, list->name, list->price);
        if(list->price < 10)
            printf(" ");
        printf("   %.3f", list->qtt);
        if(list->qtt < 10)
            printf(" ");
        printf("  R$%.2f", list->total);
           
        printList(list->next);
    }
}
int printByPages(List* list, int page, char side){
    //ocultar guia
    if(side == 'o')
        return page;
    else{
        int i;
        List* printer = list;
            int lastPage = listSize(list)/10;

        if(side == 'l'){
            if(page > 0)
                page--;
        }else{
            if(page < lastPage)
                page++;
        }
        if(listSize(list)%10 == 0)
            printf("PAGINA %i DE %i", page + 1, lastPage);
        else
            printf("PAGINA %i DE %i", page + 1, lastPage + 1);
        printf("\n[Q][E] PARA NAVEGAR ENTRE AS PAGINAS");
        printf("\n\nCOD   NOME                     KG/UN\n");
        for(i = 0; i < page * 10; i++)
            printer = printer->next;

        for(i = 0; i < 10; i++){
            if(!printer){
               printf("\n");
            }else{
                printf("\n%.4i  %s R$%3.2f", printer->key, printer->name, printer->price);
                printer = printer->next;
            }
        }
        printf("\n");
        for(i = 0; i < 37; i++)
            printf("_");

        return page;
    }
}
void deleteList(List* list){
    List* aux = list;
    while(list){
        aux = list;
        list = list->next;
        free(aux);
    }
}
int listSize(List* list){
    if(list)
        return 1 + listSize(list->next);
    return 0;     
}
void alfaSort(List* list){
    List* aux = list;
    List* iter;
    char nameAux[25];
    float priceAux;
    int keyAux;

    while(aux->next){
        iter = aux->next;
        while(iter){
            if(strcmp(aux->name, iter->name) > 0){
               
                strcpy(nameAux, aux->name);
                strcpy(aux->name, iter->name);
                strcpy(iter->name, nameAux);

                keyAux = aux->key;
                aux->key = iter->key;
                iter->key = keyAux;

                priceAux = aux->price;
                aux->price = iter->price;
                iter->price = priceAux;
            }
            iter = iter->next;
        }
        aux = aux->next;
    }
}
float totalToPay(List* list){
    if(list)
        return list->total + totalToPay(list->next);
    return 0;
}