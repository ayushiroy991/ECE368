#include "huffman.h"
#include <stdlib.h>
#include <string.h>

int read_header(FILE* fp, Header* h){
	
	int x = fread(&(h->t_comp), sizeof(h->t_comp), 1, fp);
	if (x!=1 || h->t_comp <= 0){
		return 1;
	}

	x = fread(&(h->t_top), sizeof(h->t_top), 1, fp);
	if (x!=1  ||h->t_top <= 0 ){
		return 1;
	}

	x = fread(&(h->t_orig), sizeof(h->t_orig), 1, fp);
	if (x!= 1  ||h->t_orig <= 0){
	  return 1;
	}

	h->topology = malloc(sizeof(*h->topology)*(h->t_top));
	/**	for(int i=0; i<(h->t_top-1); i++){
		h->topology[i] = fgetc(fp);
	}

	fgetc(fp);**/
	fread(h->topology, h->t_top, 1, fp);
	if (h->topology == NULL){
		return 1;
	}
	
	int num_code = h->t_comp - h->t_top - (3*sizeof(h->t_comp));
	h->code = malloc(num_code);
	/**	for (int a=0; a<num_code-1; a++){
	  h->code[a]= fgetc(fp);
	  }**/
	fread(h->code, num_code, 1, fp);
	if(h->code == NULL){
	  return 1;
	}
	return 0;

}
/**void read_header_bits(FILE* fp, Header* h){
        int x = fread(&(h->t_comp), sizeof(h->t_comp), 1, fp);
	if (x!=1){
		return 0;
	}

	x = fread(&(h->t_top), sizeof(h->t_top), 1, fp);
	if (x!=1){
		return 0;
	}




	x = fread(&(h->t_orig), sizeof(h->t_orig), 1, fp);
	if (x!= 1){
		return 0;
	}


  	h->topology = malloc(sizeof(*h->topology)*(h->t_top));
	fread(h->topology, h->t_top, 1, fp);
	if (h->topology == NULL){
		return 0;
     	}

	int count_bytes = 0;
	int count_bits = 7;
	char* temp_top = malloc(sizeof(*temp_top)*(h->t_top));
	while (count_bytes < h->t_top){
	  int byte = h->topology[count_bytes];
	  while (count_bits >= 0){
	    int bit = (byte >> count_bit) &1;
	   
	  }
	  }

	char* temp_top = malloc(sizeof(*temp_top)*(h->t_top)*8);
	for (int i = 0; i<(h->t_top); i++){
	  int byte= h->topology[i];
	  for (int x = 7; x>=0; x--){
	    int bit = ((byte >>x)&1);
	    temp_top[i*7+(7-x)] = bit;
	  }
	}

	int count_bits = 0;
	char* temp_top_2 = malloc(sizeof(*temp_top_2)*(h->t_top)*8);
	count append = 0;
	while(count_bits < (h->t_top)*8){
	  int t_bit = temp_top[count_bits]
	    if (t_bit = 1){
	      temp
	      for (int y = 0; y<8
	    


}
**/

void make_tree(Header* h, HuffNode** tree){
  int stack_count = 0;
  for (int i = 0; i<(h->t_top)-1; i++){
    if(h->topology[i] == '1'){
      stack_count++;
      HuffNode* new_1 = malloc(sizeof(*new_1));
      new_1->data = h->topology[++i];
      new_1->left = NULL;
      new_1->right = NULL;
      HuffNode* n = push(tree, new_1);
      if (n == NULL){
	break;
      }
    }
    else if(h->topology[i] == '0'){
      if (stack_count >1){
	HuffNode* right = pop(tree);
	stack_count--;
	HuffNode* left = pop(tree);
	stack_count--;

	HuffNode* non_leaf = malloc(sizeof(*non_leaf));
	non_leaf->data = -1;
	non_leaf->left = left;
	non_leaf->right = right;
	
	stack_count++;
	HuffNode* n = push(tree, non_leaf);
	if (n== NULL){
	  break;
	}
	}
    }
   
  }
  return;
}

HuffNode* push(HuffNode** pq, HuffNode* new){
  new->next = *pq;
  *pq = new;

  return new;
}

HuffNode* pop(HuffNode**pq){
  if (*pq == NULL){
    return NULL;
  }

  HuffNode* rem = *pq;
  *pq = (*pq)->next;
  rem->next = NULL;

  return rem;
}

void free_tree(HuffNode* tree){
  if (tree != NULL){
    if (tree->left != NULL){
      free_tree(tree->left);
    }
    if (tree->right != NULL){
      free_tree(tree->right);
    }
    free(tree);
  }
}


void huff_traverse(HuffNode *tree, int * path, int i, FILE *fp){
	int x = 0;	
	if (tree->left==NULL && tree->right == NULL){
		path[i] = 7;
		fprintf(fp, "%c:", tree->data);
		while (path[x] != 7){
			fprintf(fp, "%d", path[x]);
			x++;
		}
			fprintf(fp, "\n");

		//fprintf(fp, "%c:%d\n", tree->value, path[i]);
	}
	else{	
	if(tree->left !=NULL){
		path[i] = 0;
		
		huff_traverse(tree->left, path, i+1, fp);
	}
	if(tree->right != NULL){
		path[i] = 1;
		huff_traverse(tree->right, path, i+1, fp);
	}
	}


}

void decompress(Header* h, HuffNode* tree, FILE *fp){

  HuffNode* temp = tree;
  int count_byte = 0;

	int num_code = h->t_comp - h->t_top - (3*sizeof(h->t_comp));

	for (int i = 0; i<num_code; i++){
	  int byte= h->code[i];
	  for (int x = 7; x>=0; x--){
	    int bit = ((byte >>x)&1);
	    if (bit == 1){
		temp = temp->right;
	      }
	    if (bit == 0){
		temp = temp->left;
	      }
	   if(temp->data != -1){
	      fprintf(fp, "%c", temp->data);
	      count_byte++;
	      temp = tree;
	    }
	    if (count_byte == h->t_orig){ /*  */ 
	      return;
	    }
	  }
	}

	return;
} 

void make_tree_bits(Header *h, HuffNode **tree){
	
	

}

