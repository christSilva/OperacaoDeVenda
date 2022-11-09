#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    char pageMove = 'l';

    for(i = 1; i <= biggest(root); i++){
        if(findKey(root, i) == 1)
            guide = insertListNode(guide, i, getName(root, i), getPrice(root, i), 0);
    }
    alfaSort(guide);
    do{
        getc(stdin);
        system("clear");
        page = printByPages(guide, page, pageMove);
        printf("\n\nCOD.  NOME                     KG/UN     QTD     TOTAL\n");
        printList(products);
        printf("\n\n\n[A] INSERIR PRODUTO");
        printf("\n[D] EXCLUIR PRODUTO");
        printf("\n[F] FINALIZAR OPERACAO");
        printf("\n[O] OCULTAR/MOSTRAR GUIA\n");

        opt = getchar();
        charUpperCase(&opt);

        switch(opt){
            case 'A':{
                printf("\nCOD.: ");
                scanf("%i", &key);
                getc(stdin);
                if(findKey(root, key) == 1){
                    printf("\nKG/UN (UTILIZE '.' PARA A PARTE DECIMAL): ");
                    scanf("%f", &qtt);
                    getc(stdin);
                    products = insertListNode(products, key, getName(root, key), getPrice(root, key), qtt);
                }else{
                    printf("\nCODIGO INVALIDO\n");
                    sleep(2);
                }
                break;
            }
            case 'D':{
                if(products){
                    printf("\nCODIGO DO PRODUTO: ");
                    scanf("%i", &key);
                    getc(stdin);
                    
                    if(findKey(root, key) == 1)
                        products = deleteListNode(products, key);
                    else
                        printf("\nCODIGO INVALIDO\n");
                        sleep(2);
                }
                break;
            }
            case 'F':{
                if(products){
                    //system("clear");
                    printf("\n\nCOD.  NOME                     KG/UN     QTD     TOTAL\n");
                    printList(products);
                    printf("\n__________________________________________________________");
                    printf("\n\nTOTAL A PAGAR                                    R$%.2f\n", totalToPay(products));
                    printf("\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR...");
                    getc(stdin);
                    getchar();
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
                printf("%c \n\nOPCAO INVALIDA!\n", opt);
                sleep(2);
                break;
            }
        }
    }while(opt != 'F');
    deleteList(guide);
    deleteList(products);
}