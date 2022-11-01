#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "options.h"
#include "operation.h"
#include "productList.h"

int main(){
	Tree* root = NULL;
	root = loadTree(root);
	char opt;

	do{
		printf("\nMENU PRINCIPAL\n");
		printf("[1] NOVA OPERACAO\n");
		printf("[2] OPCOES\n");
		printf("[0] SAIR");
		opt = getch();

		switch(opt){
            case '1':{
				if(treeSize(root) == 0){
					printf("\n\nATENCAO: NAO NENHUM PRODUTO CADASTRADO, NAO E POSSIVEL REALIZAR VENDAS.\n");
					printf("PARA CADASTRAR PRODUTOS ACESSE AS OPCOES\n\n");
				}else{
					newOp(root);
				}
				break;
			}
			case '2':{
				root = options(root);
				break;
			}
			case '0':{
				deleteTree(root);
				printf("----------");
			    break;
			}
            default:{
                printf("\nOPCAO INVALIDA\n");
				break;
			}
		}
	}while(opt != '0');
return 0;
}
