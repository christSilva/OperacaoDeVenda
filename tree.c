#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "tree.h"

struct Tree{
	int key;
	char name[25];
	float price;
	Tree* left;
	Tree* right;
};
Tree* insertTreeNode(Tree* root, int key){
	//achou a posi��o correta
	if(!root){
	/*	root = (Tree*) malloc(sizeof(Tree));
		root->key = key;
		root->left = NULL;
		root->right = NULL;

		printf("DIGITE O NOME DO PRODUTO: ");
			scanf("%24[^\n]", root->name);
			fflush(stdin);
			upperCase(root->name);
		printf("DIGITE O PRE�O R$ ");
			scanf("%f", &root->price);
			fflush(stdin);
	*/
		root = fillTree(root, key);
	}
	//novo n� � menor que o n� atual
	else if(root->key > key){
		root->left = insertTreeNode(root->left, key);
	//novo n� � maior que o n� atual
	}else{
		root->right = insertTreeNode(root->right, key);
	}

	root = balanceTree(root);
	return root;
}
Tree* fillTree(Tree* node, int key){
	node = (Tree*) malloc(sizeof(Tree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	printf("DIGITE O NOME DO PRODUTO: ");
		scanf("%24[^\n]", node->name);
		fflush(stdin);
		upperCase(node->name);
	printf("DIGITE O PRECO R$ ");
		scanf("%f", &node->price);
		fflush(stdin);
	return node;
}
void upperCase(char name[]){
	int i = 0;

	while(name[i] != '\0'){
		if(name[i] >= 'a' && name[i] <= 'z')
			name[i] = name[i] - 32;
		i++;
	}
}
Tree* editTree(Tree* root, int key){
	if(!root){
		printf("PRODUTO NAO ENCONTRADO!\n");
		return NULL;
	}else if(root->key == key){
		char opt;
		do{
			printf("[1] EDITAR NOME\n");
			printf("[2] EDITAR PRECO\n");
			printf("[3] EDITAR AMBOS\n");
			opt = getchar();

			switch(opt){
				case '1':{
					printf("DIGITE O NOVO NOME: ");
					scanf("%24[^\n]", root->name);
					break;
				}
				case '2':{
					printf("DIGITE O NOVO PRECO R$ ");
					scanf("%f", &root->price);
					break;
				}
				case '3':{
					printf("DIGITE O NOVO NOME: ");
					scanf("%24[^\n]", root->name);
					printf("DIGITE O NOVO PRECO: R$ ");
					scanf("%f", &root->price);
					break;
				}
				case '0':{
					break;
				}
				default:{
					printf("OPCAO INVALIDA!");
					break;
				}
			}
			//getc(stdin);
		}while(opt < '0' || opt > '3');
	}else{
		if(root->key > key)
			root = editTree(root->left, key);
		else
			root = editTree(root->right, key);
	}
	return root;
}
Tree* deleteTreeNode(Tree* root, int key){
	if(!root){
		printf("\nPRODUTO NAO ENCONTRADO!\n");
		return NULL;
	}
	//achou
	else if(root->key == key){
		//n�o possui filhos
		if(!root->left && !root->right){
			root = NULL;
			free(root);
			return NULL;
		}
		//possui dois filhos
		else if(root->left && root->right){
			Tree* iter = root->left;
			while(iter)
				iter = iter->right;
			root->key = iter->key;
			strcpy(root->name, iter->name);
			root->price = iter->price;
			iter->key = key;
			root->left = deleteTreeNode(root->left, key);
			return root;
		}
		else{
			Tree* aux;
			//possui um filho na direita
			if(!root->left)
				aux = root->right;
			//possui um filho na esquerda
			else
				aux = root->left;
			free(root);
			return aux;
		}
	}
	else{
		if(root->key > key)
			root->left = deleteTreeNode(root->left, key);
		else
			root->right = deleteTreeNode(root->right, key);
	}
	root = balanceTree(root);
	return root;
}
void deleteTree(Tree* root){
    int i;
    int n = biggest(root);

    for(i = 1; i <= n; i++){
        if(findKey(root, i) == 1)
        	root = deleteTreeNode(root, i);
    }
}
Tree* balanceTree(Tree* root){
	int difference = hDifference(root);

	//rota��o esquerda
	if(difference < -1 && hDifference(root->right) <= 0){
		return rotationL(root);
	}
	//rota��o direita esquerda
	else if(difference < -1 && hDifference(root->right) > 0){
		root->right = rotationR(root->right);
		return rotationL(root);
	}
	//rota��o direita
	else if(difference > 1 && hDifference(root->left) >= 0){
		return rotationR(root);
	}
	//rota��o esquerda direita
	else if(difference > 1 && hDifference(root->left) < 0){
		root->left = rotationL(root->left);
		return rotationR(root);
	}
	return root;
}
int hDifference(Tree* root){
	return treeHeight(root->left) - treeHeight(root->right);
}
Tree* rotationL(Tree* root){
	Tree* son = root->right;
	Tree* grandSon = son->left;

	son->left = root;
	root->right = grandSon;

	return son;
}
Tree* rotationR(Tree* root){
	Tree* son = root->left;
	Tree* grandSon = son->right;

	son->right = root;
	root->left = grandSon;

	return son;
}
int	treeHeight(Tree* root){
	if(root){
		int left = treeHeight(root->left);
		int right = treeHeight(root->right);
		if(left > right)
			return left+1;
		else
			return right+1;
	}else{
		return -1;
	}
}
int treeSize(Tree* root){
	if(root){
		return 1 + treeSize(root->left) + treeSize(root->right);
	}
	return 0;
}
void printTree(Tree* root, int tabs){
	if(root){
		int i;

		printTree(root->right, tabs+1);
		printf("\n");

		for(i = 0; i < tabs; i++)
			printf("\t");
        printf(" ________\n");
		for(i = 0; i < tabs; i++)
			printf("\t");
		printf("|%i\n", root->key);
		for(i = 0; i < tabs; i++)
			printf("\t");
		printf("|%.8s\n", root->name);
		for(i = 0; i < tabs; i++)
			printf("\t");
		printf("|R$ %.2f\n", root->price);
		printTree(root->left, tabs+1);
	}
}
void printSorted(Tree* root){
	if(root){
		printSorted(root->left);
		printf("[%2i] %s\n", root->key, root->name);
		printSorted(root->right);
	}
}
int biggest(Tree* root){
	if(!root->right)
		return root->key;
	else
		return biggest(root->right);
}
void saveData(Tree* root, FILE* file){
	if(root){
		fprintf(file, "%i\n", root->key);
		fprintf(file, "%s\n", root->name);
		fprintf(file, "%.2f\n", root->price);

		saveData(root->right, file);
		saveData(root->left, file);
	}
}
Tree* loadTree(Tree* root){
	int key;
	FILE* file = fopen("products.txt", "r");

	if(!file){
		printf("ERRO AO CARREGAR DADOS OU NAO HA DADOS ARMAZENADOS.\n");
		printf("INSIRA PRODUTOS ACESSANDO AS OPCOES\n\n");
		fclose(file);
		return NULL;
	}
	do{
		fscanf(file, "%i\n", &key);
		root = loadNode(root, file, key);
	}while(key != -1);
	fclose(file);
	root = deleteTreeNode(root, -1);
	return root;
}
Tree* loadNode(Tree* root, FILE* file, int key){
	//achou a posi��o correta
	if(!root){
		root = (Tree*) malloc(sizeof(Tree));
		root->key = key;
		root->left = NULL;
		root->right = NULL;
		fscanf(file, "%24[^\n]", root->name);
		fscanf(file, "%f", &root->price);
	}
	//novo n� � menor que o n� atual
	else if(root->key > key)
		root->left = loadNode(root->left, file, key);
	//novo n� � maior que o n� atual
	else
		root->right = loadNode(root->right, file, key);

	root = balanceTree(root);
	return root;
}
int findKey(Tree* root, int key){
	Tree* iter = root;
	while(iter){
		if(iter->key == key){
			return 1;
		}else{
			if(iter->key > key)
				iter = iter->left;
			else
				iter = iter->right;
		}
	}
	return -1;
}
char* getName(Tree* root, int key){
	if(root->key == key)
		return root->name;
	else if(root->key > key)
		return getName(root->left, key);
	else
		return getName(root->right, key);
}
float getPrice(Tree* root, int key){
	if(root->key == key)
		return root->price;
	else if(root->key > key)
		return getPrice(root->left, key);
	else
		return getPrice(root->right, key);
}