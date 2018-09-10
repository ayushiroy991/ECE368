#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	if ((strcmp(argv[1], "-c") == 0) && argc == 5){
		char* input = argv[2];
		Header* header_char = malloc(sizeof(*header_char));
		FILE* fp_in  = fopen(input, "r");
		if (fp_in == NULL){
		  free(header_char);
		  printf("couldn't open input file");
		  return EXIT_FAILURE;
		}
		int read = read_header(fp_in, header_char);
		fclose(fp_in);
		if (read == 1){
		  //free(header_char);
			printf("couldn't read header");
			return EXIT_FAILURE;
		}
	 
		//printf("numchars comp: %ld", header_char->t_comp);
		//printf("\nnumchars header: %ld", header_char->t_top);
		//printf("\nnumchars orig: %ld", header_char->t_orig);
		//intf("\ntopology: %s", header_char->topology); 
		//printf("\ncode: %s", header_char->code);

		HuffNode* tree = NULL;
		make_tree(header_char, &tree);
		
		FILE* fp_out_1 = fopen(argv[3], "w");
		if (fp_out_1 == NULL){
		   printf("can't open first output file");
		  return EXIT_FAILURE;
		}
		int path[256] = {0};
		huff_traverse(tree, path, 0, fp_out_1);
		fclose(fp_out_1);
		
		FILE* fp_out_2 = fopen(argv[4], "w");
		if (fp_out_2 == NULL){
		   printf("can't open second output file");
		  return EXIT_FAILURE;
		}
		decompress(header_char, tree, fp_out_2);
		fclose(fp_out_2);

		free(header_char->code);
		free(header_char->topology);
		free(header_char);
		free_tree(tree);
	 

		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}

}


