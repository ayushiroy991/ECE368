#include <stdlib.h>
#include <stdio.h>

typedef struct _huffNode{
	int data;
	struct _huffNode *left;
	struct _huffNode *right;
	struct _huffNode *next;
}HuffNode;

typedef struct Header_comp{
	long int t_comp; //total char in compressed file
	long int t_top; //total char in topology/header
	long int t_orig; //total char in original
	char* topology; 
        char* code; //encoding of tree
}Header;

int read_header(FILE* fp, Header* h);
void make_tree(Header* h, HuffNode** tree);
HuffNode* push(HuffNode** pq, HuffNode* new);
HuffNode* pop(HuffNode**pq);
void free_tree(HuffNode* tree);
void huff_traverse(HuffNode *tree, int* path, int i, FILE *fp);
void decompress(Header* h, HuffNode* tree, FILE *fp);  

