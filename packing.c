#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include "packing.h"

TreeNode* Load_Tree(FILE* fp){

	int data = fgetc(fp);

	TreeNode* root = NULL;// = new_node(data, '\0', '\0');
	//temp = tree;
	//temp->left = NULL;
	//temp->right = NULL;

	//temp->data = fgetc(fp);
	

	if ((data)== 'V' || (data) == 'H'){
		root = new_node(data, '\0', '\0');
		fscanf(fp, "\n");
		root->left = Load_Tree(fp);
		root->right = Load_Tree(fp);
	}

	else {
		double w;
		double h;
		//data = data-48;i
		fseek(fp, -1, SEEK_CUR);
		if (!fscanf(fp, "%d(%le,%le)", &data, &w, &h)){
			fprintf(stdout, "can't read file\n");
			return root;
		}
		
		root = new_node(data, w, h);

		fscanf(fp, "\n");

	}
	//fscanf(fp, "\n");
	//Load_Tree(fp, tree->left);
	//Load_Tree(fp, tree->right);

	//tree = root;
	return root;

}

int Print_Postorder(FILE* fp, TreeNode* tree){

	if (tree == NULL){
		fprintf(stdout, "can't read empty tree\n");
		return 0;
	}

	if (tree != NULL){
		if (tree->left != NULL){
			Print_Postorder(fp, tree->left);
		}
		if (tree->right != NULL){
			Print_Postorder(fp, tree->right);
		}
		if ((tree->width) != '\0' && (tree->height) != '\0'){
			fprintf(fp, "%d(%le,%le)\n", (tree->data) , tree->width, tree->height);
		}
		else {
			fprintf(fp,"%c\n", (tree->data));
		}

	}
	
	return 1;

}

void destroy_tree(TreeNode* tree){
	
	if (tree != NULL){
		if (tree->left != NULL){
			destroy_tree(tree->left);
		}
		if (tree->right != NULL){
			destroy_tree(tree->right);
		}

		free(tree);
	}

	return;

}


TreeNode* new_node(int data, double width, double height){
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));

	temp->data = data;
	temp->width = width;
	temp->height = height;

	temp->x = 0;
	temp->y = 0;

	temp->right = NULL;
	temp->left = NULL;

	return temp;

}

void Perf_Packing(TreeNode *tree){

	if (tree == NULL){
		fprintf(stdout, "cannot pack tree, tree empty");
		return;
	}

	if (tree != NULL){
		if (tree->left != NULL){
			Perf_Packing(tree->left);
		}
		if (tree->right != NULL){
			Perf_Packing(tree->right);
		}
		if ((tree->width) != '\0' && (tree->height) != '\0'){
			return;
		}

		if (tree->data == 'V'){
			tree->width = (tree->left)->width + (tree->right)->width;
			tree->height = max_int((tree->left)->height, (tree->right)->height);
			
		}

		if (tree->data == 'H'){
			tree->height = (tree->left)->height + (tree->right)->height;
			tree->width = max_int((tree->left)->width, (tree->right)->width);	
		}
		
	}

	return;
}

int Print_Dimensions(FILE* fp, TreeNode* tree){

	if (tree == NULL){
		fprintf(stdout, "can't read empty tree for printing dimensions\n");
		return 0;
	}

	if (tree != NULL){
		if (tree->left == NULL && tree->right == NULL){
			fprintf(fp, "%d(%le,%le)\n", (tree->data), tree->width, tree->height);
		}
		else {
			fprintf(fp,"%c(%le,%le)\n", (tree->data), tree->width, tree->height);
		}	
		if (tree->left != NULL){
			Print_Dimensions(fp, tree->left);
		}
		if (tree->right != NULL){
			Print_Dimensions(fp, tree->right);
		}

	}
	
	return 1;

}

int max_int(int a, int b){
	if (a >= b){
		return a;
	}

	else{
		return b;
	}

}
	

void Get_Coord(TreeNode* tree){

	if (tree != NULL){
		if (tree->data == 'H'){
			if (tree->left != NULL){
				(tree->left)->x = tree->x;
				(tree->left)->y = tree->y + (tree->right)->height;
				Get_Coord(tree->left);
			}

			if (tree->right != NULL){
				(tree->right)->x = tree->x;
				(tree->right)->y = tree->y;
				Get_Coord(tree->right);
			}
		}



		if (tree->data == 'V'){
			if (tree->left != NULL){
				(tree->left)->x = tree->x;
				(tree->left)->y = tree->y;
				Get_Coord(tree->left);
			}

			if (tree->right != NULL){
				(tree->right)->x = tree->x + (tree->left)->width;
				(tree->right)->y = tree->y;
				Get_Coord(tree->right);
			}
			
		}


	}
	
	return;

}

int Print_Coord(FILE* fp, TreeNode* tree){
	if (tree == NULL){
		fprintf(stdout, "can't read empty tree for printing coord\n");
		return 0;
	}

	if (tree != NULL){
		if ((tree->left) == NULL && (tree->right) == NULL){
			fprintf(fp, "%d(%le,%le)\n", (tree->data), tree->x, tree->y);
		}

		if (tree->left != NULL){
			Print_Coord(fp, tree->left);
		}
		if (tree->right != NULL){
			Print_Coord(fp, tree->right);
		}

	}
	
	return 1;
}

