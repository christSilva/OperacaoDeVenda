#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "productList.h"

void newOp(Tree* root){
    List* guide = NULL;
    List* products = NULL;

    int i;
    
    for(i = 1; i <= biggest(root); i++){
        if(findKey(root, i) == -1)
            continue;
        guide = insertListNode(guide, i, getName(root, i), getPrice(root, i), 0);
    }
    printList(guide);
    deleteList(guide, root);
}