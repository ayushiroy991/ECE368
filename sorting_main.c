#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static long *Load_Into_Array(char*fname, int*size){
	FILE* fp = fopen(fname, "r");
	if (fp== NULL){
		fprintf(stdout, "input file cannot be opened");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	int n_bytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	//*size = n_bytes/(sizeof(long));

	long *list = malloc((n_bytes+1)*sizeof(char));
	*size = fread(list, sizeof(long), n_bytes+1, fp);
	fclose(fp);

	return list;

}

static int Save_From_Array(char* fname, long* arr, int size){

	FILE* fp = fopen(fname, "w");
	if (fp == NULL){
		fprintf(stdout, "cannot open output file");
		return '\0';
	}
	
	int count = 0;

	/**for (int i =0; i<(size); i++){
		fprintf(fp, "%li", arr[i]);
		count++;
	}**/

	count = fwrite(arr, sizeof(long), size, fp);

	fclose(fp);
	
	return count;

}

int main(int argc, char* argv[]){
	if (argc != 4){
		fprintf(stdout, "incorrect number of arguments");
		return EXIT_FAILURE;
	}
	
	if (strcmp(argv[1], "-q") == 0){
	  clock_t start_io = clock();
		char* input_fp = argv[2];
		char* output_fp = argv[3];

        int* size = malloc(sizeof(int));
		long* list = Load_Into_Array(input_fp, size);
		if (list == NULL){
			fprintf(stdout, "could not load into list");
			return EXIT_FAILURE;
		}

		
		clock_t start_t = clock();
		Quick_Sort(list, *size);
		clock_t end_t = clock();
		double total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;

		int print_count;
		print_count = Save_From_Array(output_fp, list, *size);
		print_count = print_count;

		/**	for (int i = 0; i<*size; i++){
			fprintf(stdout, "%ld\n", list[i]);
			}**/
	       
		clock_t end_io = clock();

		double total_io = (double)(end_io-start_io)/CLOCKS_PER_SEC;
		
		fprintf(stdout, "I/O time: %le", total_io);
		fprintf(stdout, "\nSorting time: %le", total_t);
		//fprintf(stdout, "\nNumber of comparisons: %le", *n_cmp);
		//fprintf(stdout, "\n%d", print_count);

		free(list);
		free(size);
		return EXIT_SUCCESS;
	}

	else if (strcmp(argv[1], "-m") == 0){
	  clock_t start_io = clock();
		char* input_fp = argv[2];
		char* output_fp = argv[3];
		
		int* size = malloc(sizeof(int));
		long* list = Load_Into_Array(input_fp, size);
		if (list == NULL){
			fprintf(stdout, "could not load into list");
			return EXIT_FAILURE;
		}

		/**	for (int i = 0; i<*size; i++){
			fprintf(stdout, "~%ld\n", list[i]);
			}**/
		
		clock_t start_t = clock();
		Merge_Sort(list, *size);
		clock_t end_t = clock();
		double total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;

		int print_count;
		print_count = Save_From_Array(output_fp, list, *size);
		print_count = print_count;
	       
		/**	for (int i = 0; i<*size; i++){
			fprintf(stdout, "%ld\n", list[i]);
			}**/

		clock_t end_io = clock();

		double total_io = (double)(end_io-start_io)/CLOCKS_PER_SEC;
		
		fprintf(stdout, "I/O time: %le", total_io);
		fprintf(stdout, "\nSorting time: %le", total_t);
		//fprintf(stdout, "\nNumber of comparisons: %le", *n_cmp);
		//fprintf(stdout, "\n%d", print_count);

		free(list);
		free(size);
	}

	return EXIT_FAILURE;
}
