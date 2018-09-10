#include "seqpair.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]){
	
	if (argc != 3){
		fprintf(stdout, "incorrect number of arguments\n");
		return EXIT_FAILURE;
	}

	char* input_fp = argv[1];
	char* output_fp = argv[2];

         clock_t start_io = clock();
	
	Rectangle* arrRect;
	int size;// = malloc(sizeof(int));;
	int* seq1;
	int* seq2;

	FILE* in_fp = fopen(input_fp,"r");
	if (in_fp == NULL){
		fprintf(stdout, "could not open input file\n");
		return EXIT_FAILURE;
	}
	arrRect = Read_Input(&size, &seq1, &seq2, in_fp);
	fclose(in_fp);
//TEST INPUT
/****

	fprintf(stdout, "%d\n", size);
	for (int i=0; i<size; i++){
		fprintf(stdout, "%d(%le,%le)\n", arrRect[i].label, arrRect[i].width, arrRect[i].height);
	}
    
	fprintf(stdout, "%d", seq1[0]);
	for (int x=1; x<size; x++){
		fprintf(stdout, " %d", (seq1)[x]);
	}
	fprintf(stdout, "\n");
    
	fprintf(stdout, "%d", seq2[0]);
	for (int y=1; y<size; y++){
		fprintf(stdout, " %d", (seq2)[y]);
	}
	fprintf(stdout, "\n");
//END TEST INPUT***/

//	GraphNode* HCG;
	Build_Graph(arrRect, size, seq1, seq2);

	get_Coord(arrRect, size, seq1, seq2);

/**	for (int i=0; i<size; i++){
		ListNode* crawl = (arrRect[i].h_head);
		fprintf(stdout, "%d", (arrRect[i].h_head)->label);
		while (crawl->next){
			fprintf(stdout, "-> %d", (crawl->next)->label);
			crawl = crawl->next;
		}
		fprintf(stdout, "\n");
	}
		fprintf(stdout, "\n");
		
	for (int i=0; i<size; i++){
		ListNode* crawl = (arrRect[i].v_head);
		fprintf(stdout, "%d", (arrRect[i].v_head)->label);
		while (crawl->next){
			fprintf(stdout, "-> %d", (crawl->next)->label);
			crawl = crawl->next;
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
***/

	FILE* out_fp = fopen(output_fp,"w");
	if (in_fp == NULL){
		fprintf(stdout, "could not open output file\n");
		return EXIT_FAILURE;
	}
	//fprintf(out_fp, "%d\n", size);
	for (int i=0; i<size; i++){
		fprintf(out_fp, "%d(%le,%le)\n", arrRect[i].label, arrRect[i].x, arrRect[i].y);
	}
	fclose(out_fp);


	for (int i=0; i<size; i++){
		destroy_list(arrRect[i].h_head);
		destroy_list(arrRect[i].v_head);
	}

	free(arrRect);
	free(seq1);
	free(seq2);

	clock_t end_io = clock();
	        double total_io = (double)(end_io-start_io)/CLOCKS_PER_SEC;
		
		fprintf(stdout, "I/O time: %le", total_io);	
	//fclose(in_fp);
}
