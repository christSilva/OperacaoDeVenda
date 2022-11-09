#include <stdio.h>
#include <stdlib.h>
//#include <ncurses.h>
#include <unistd.h>
#include "tree.h"
#include "options.h"
#include "operation.h"
#include "productList.h"

int main(){
	Tree* root = NULL;
	root = loadTree(root);
	char opt;

	do{
		system("clear");
		printf("MENU PRINCIPAL\n\n");
		printf("[1] NOVA OPERACAO\n");
		printf("[2] OPCOES\n");
		printf("[0] SAIR");
		
		opt = getchar();


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
				getc(stdin);
				root = options(root);
				break;
			}
			case '0':{
				deleteTree(root);
			    break;
			}
            default:{
                printf("\nOPCAO INVALIDA\n");
				sleep(2);			
				break;
			}
		}
	}while(opt != '0');
return 0;
}
