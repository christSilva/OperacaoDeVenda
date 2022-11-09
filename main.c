#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libs//tree.h"
#include "libs//options.h"
#include "libs//operation.h"

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
				getc(stdin);
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
                printf("\n\nMAIN==OPCAO INVALIDA\n\n");
				sleep(2);			
				break;
			}
		}
		getc(stdin);
	}while(opt != '0');
return 0;
}
