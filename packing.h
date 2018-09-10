#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _treeNode{
	int data;
	double width;
	double height;
	double x;
	double y;
	struct _treeNode *right;
	struct _treeNode *left;

}TreeNode;

TreeNode* Load_Tree(FILE* fp);
int Print_Postorder(FILE* fp, TreeNode* tree);
void destroy_tree(TreeNode* tree);
TreeNode* new_node(int data, double width, double height);
void Perf_Packing(TreeNode* tree);
int Print_Dimensions(FILE* fp, TreeNode* tree);
int max_int(int a, int b);
void Get_Coord(TreeNode* tree);
int Print_Coord(FILE* fp, TreeNode* tree);
