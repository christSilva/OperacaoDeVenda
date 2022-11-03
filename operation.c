#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "tree.h"
#include "productList.h"


void charUpperCase(char* c){
    if(*c >= 'a' && *c <= 'z')
        *c = *c - 32;
}
void newOp(Tree* root){
    List* guide = NULL;
    List* products = NULL;

    int key, i;
    int page = 0;
    float qtt;
    char opt;
    char pageMove = 'o';

    for(i = 1; i <= biggest(root); i++){
        if(findKey(root, i) == 1)
            guide = insertListNode(guide, i, getName(root, i), getPrice(root, i), 0);
    }
    alfaSort(guide);
    do{
        //system("cls");
        page = printByPages(guide, page, pageMove);
        printf("\n\nCOD   NOME                     PRECO  QTD  TOTAL\n");
        printList(products);
        printf("\n\n\n[A] INSERIR PRODUTO");
        printf("\n[D] EXCLUIR PRODUTO");
        printf("\n[F] FINALIZAR OPERACAO");
        printf("\n[O] OCULTAR/MOSTRAR GUIA\n");
        getc(stdin);
        //__fpurge(stdin);
        opt = getchar();
        charUpperCase(&opt);

        switch(opt){
            case 'A':{
                printf("\nCODIGO DO PRODUTO: ");
                scanf("%i", &key);
                fflush(stdin);
                if(findKey(root, key) == 1){
                    printf("\nQUANTIDADE (UTILIZE '.' PARA A PARTE DECIMAL): ");
                    scanf("%f", &qtt);
                    fflush(stdin);
                    products = insertListNode(products, key, getName(root, key), getPrice(root, key), qtt);
                }else{
                    printf("\nCODIGO INVALIDO\n");
                }
                break;
            }
            case 'D':{
                if(products){
                    printf("\nCODIGO DO PRODUTO: ");
                    scanf("%i", &key);
                    fflush(stdin);
                    
                    if(findKey(root, key) == 1)
                        products = deleteListNode(products, key);
                    else
                        printf("\nCODIGO INVALIDO\n");
                }
                break;
            }
            case 'F':{
                if(products){
                    printf("\n\nCOD   NOME                     PRECO  QTD  TOTAL\n");
                    printList(products);
                    printf("\n\nTOTAL A PAGAR                              R$%.2f\n", totalToPay(products));
                }
                break;
            }
            case 'Q':{
                pageMove = 'l';
                break;
            }
            case 'E':{
                pageMove = 'r';
                break;
            }
            case 'O':{
                if(pageMove == 'o')
                    pageMove = 'l';
                else
                    pageMove = 'o';
                    
                break;
            }
            default:{
                printf("OPCAO INVALIDA!\n");
                break;
            }
        }
    }while(opt != 'F');
    deleteList(guide);
    deleteList(products);
}