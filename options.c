#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "tree.h"

Tree* options(Tree* root){
	char opt;
	int key;

	do{
		system("cls");
		printf("OPCOES\n\n");
		printf("[1] INSERIR PRODUTO\n");
		printf("[2] EXCLUIR PRODUTO\n");
		printf("[3] EDITAR DADOS DE UM PRODUTO\n");
		printf("[0] VOLTAR\n");
		printf("\n\n\n\n\n\n[4] OPCOES PARA DESENVOLVEDORES\n");
		opt = getch();
		system("cls");
		switch(opt){
			case '1':{
				printf("INSERIR PRODUTO\n\n");
				//verifica se a �rvore esta vazia
				if(treeSize(root) == 0)
					root = insertTreeNode(root, 1);
				else{
					root = insertTreeNode(root, biggest(root) + 1);
				}
				save(root);
				printf("OPERACAO REALIZADA COM SUCESSO!");
				break;
			}
			case '2':{
				printf("EXCLUIR PRODUTO\n\n");
				printSorted(root);
				printf("INFORME O CODIGO DO PRODUTO OU DIGITE [0] PARA CANCELAR ");
				scanf("%i", &key);
				fflush(stdin);

				if(key == 0)
					break;
				else{
					root = deleteTreeNode(root, key);
					save(root);
					break;
				}
				printf("OPERACAO REALIZADA COM SUCESSO!");
			}
			case '3':{
				printf("EDITAR PRODUTO\n\n");
				printf("INFORME O CODIGO DO PRODUTO OU DIGITE [0] PARA CANCELAR ");
				scanf("%i", &key);
				fflush(stdin);

				if(key == 0)
					break;
				else{
					root = editTree(root, key);
					save(root);
					break;
				}
				printf("OPERACAO REALIZADA COM SUCESSO!");
				break;
			}
			case '4':{
				devOptions(root);
				break;
			}
			default:{
				printf("\n\nOPCAO INVALIDA\n\n");
				break;
			}
		}
	}while(opt != '0');
return root;
}
void save(Tree* root){
	FILE* file = fopen("products.txt", "w");

	if(file){
		saveData(root, file);
		fprintf(file, "-1");
	}
	else{
		printf("\nERRO AO SALVAR ARQUIVO");
	}
	fclose(file);
}
void devOptions(Tree* root){
	char opt;

	printf("INFORMACOES PARA DESENVOLVEDORES\n\n");
	printf("QUANTIDADE DE ELEMENTOS DA ARVORE: %i\n", treeSize(root));
	printf("ALTURA DA ARVORE: %i\n", treeHeight(root));
	printf("\nELEMENTOS EM ORDEM CRESCENTE:\n\n");
	printSorted(root);
	printf("\n\nARVORE\n\n");
	printTree(root, 1);
	printf("\n\nOBS.: a arvore esta rotacionada para a esquerda. Logo, \n");
	printf("os elementos da parte superior sao os maiores, assim\n");
	printf("como os elementos da parte inferior sao os menores\n");
	printf("\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...");
	getch();
}

