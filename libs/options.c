#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "options.h"
#include "tree.h"

Tree* options(Tree* root){
	char opt;
	int key;

	do{
		system("clear");
		printf("OPCOES\n\n");
		printf("[1] INSERIR PRODUTO\n");
		printf("[2] EXCLUIR PRODUTO\n");
		printf("[3] EDITAR DADOS DE UM PRODUTO\n");
		printf("[0] VOLTAR\n");
		printf("\n\n\n\n\n\n[4] OPCOES PARA DESENVOLVEDORES\n");
		
		opt = getchar();

		switch(opt){
			case '1':{
				getc(stdin);
				system("clear");
				printf("INSERIR PRODUTO");
				printf("\n\nDIGITE [0] PARA CANCELAR OU [1] PARA CONTINUAR");
				scanf("%i", &key);
				getc(stdin);

				if(key == 0)
					break;
				else{
					//verifica se a �rvore esta vazia
					if(!root || treeSize(root) == 0)
						root = insertTreeNode(root, 1);
					else{
						root = insertTreeNode(root, biggest(root) + 1);
					}
					save(root);
					break;
				}
			}
			case '2':{
				getc(stdin);
				system("clear");
				printf("EXCLUIR PRODUTO");
				printf("\n\nCOD   NOME                     KG/UN\n");
				printSorted(root);
				printf("\n\nINFORME O CODIGO DO PRODUTO OU DIGITE [0] PARA CANCELAR ");
				scanf("%i", &key);
				getc(stdin);

				if(key == 0)
					break;
				else{
					root = deleteTreeNode(root, key);
					save(root);
					break;
				}
			}
			case '3':{
				getc(stdin);
				system("clear");
				printf("EDITAR PRODUTO");
				printf("\n\nCOD   NOME                     KG/UN\n");
				printSorted(root);
				printf("\n\nINFORME O CODIGO DO PRODUTO OU DIGITE [0] PARA CANCELAR ");
				scanf("%i", &key);
				getc(stdin);

				if(key == 0)
					break;
				else{
					root = editTree(root, key);
					save(root);
					break;
				}
			}
			case '4':{
				system("clear");
				devOptions(root);
				break;
			}
			default:{
				if(opt != '0'){
					printf("\n\nOPCAO INVALIDA\n\n");
					sleep(2);	
				}
				break;
			}
		}
		if(opt != '0')
			getc(stdin);
			
	}while(opt != '0');
return root;
}
void save(Tree* root){
	FILE* file = fopen("data//products.txt", "w");

	if(file){
		saveData(root, file);
		fprintf(file, "-1");
		printf("OPERACAO REALIZADA COM SUCESSO!");
	}
	else{
		printf("\nERRO AO SALVAR ARQUIVO");
	}
	fclose(file);
}
void devOptions(Tree* root){

	printf("INFORMACOES PARA DESENVOLVEDORES\n\n\n");
	printf("QUANTIDADE DE ELEMENTOS DA ARVORE: %i\n\n", treeSize(root));
	printf("ALTURA DA ARVORE: %i\n\n", treeHeight(root));
	printf("ELEMENTOS EM ORDEM CRESCENTE:\n\n");
	printSorted(root);
	printf("\n\nARVORE\n\n");
	printTree(root, 1);
	printf("\n\nOBS.: a arvore esta rotacionada para a esquerda. Logo, \n");
	printf("os elementos da parte superior sao os maiores, assim\n");
	printf("como os elementos da parte inferior sao os menores\n");
	printf("\n\nPRESSIONE ENTER PARA VOLTAR AO MENU ANTERIOR...");

	getc(stdin);
}

