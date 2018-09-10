#include "packing.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){
	
	if (argc != 5){
		fprintf(stdout, "incorrect number of arguments\n");
		return EXIT_FAILURE;
	}

	char* input_fp = argv[1];
	char* output_1 = argv[2];
	char* output_2 = argv[3];
	char* output_3 = argv[4];

	TreeNode* tree;
	
	FILE* in_fp = fopen(input_fp, "r");
	if (in_fp == NULL){
		fprintf(stdout, "could not open input file\n");
		return EXIT_FAILURE;
	}
	tree = Load_Tree(in_fp);
	fclose(in_fp);

	FILE* out_1 = fopen(output_1, "w");
	if (out_1 == NULL){
		fprintf(stdout, "could not open output 1 file\n");
		return EXIT_FAILURE;
	}
	if (Print_Postorder(out_1, tree) != 1){
		fprintf(stdout, "could not print Postorder tree\n");
		return EXIT_FAILURE;
	}
	fclose(out_1);

	FILE* out_2 = fopen(output_2, "w");
	if (out_1 == NULL){
		fprintf(stdout, "could not open output 2 file\n");
		return EXIT_FAILURE;
	}
	Perf_Packing(tree);
	if (Print_Dimensions(out_2, tree) != 1){
		fprintf(stdout, "cannot print dimensions");
		return EXIT_FAILURE;
	}
	fclose(out_2);

	FILE* out_3 = fopen(output_3, "w");	
	if (out_1 == NULL){
		fprintf(stdout, "could not open output 3 file\n");
		return EXIT_FAILURE;
	}
	//tree->x = 0;
	//tree->y = 0;
 	Get_Coord(tree);
	if (Print_Coord(out_3, tree) != 1){
		fprintf(stdout, "cannot print dimensions");
		return EXIT_FAILURE;
	}
	fclose(out_3);



	destroy_tree(tree);
	
}
