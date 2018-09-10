#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "seqpair.h"

Rectangle* Read_Input(int* size, int** seq1, int** seq2, FILE* fp){

	fscanf(fp, "%i", size);
    fscanf(fp, "\n");

	Rectangle* RectArr = malloc(sizeof(Rectangle)*(*size));

	int count = 0;

	while (count < *size){
		int label;
		double w; 
		double h;
		if (!fscanf(fp, "%d(%le,%le)", &label, &w, &h)){
			fprintf(stdout, "can't read file\n");
			return RectArr;
		}

		RectArr[count] = new_Rectangle(label, w, h);

		fscanf(fp, "\n");
		count++;

	}

	*seq1 = malloc(sizeof(int)*(*size));
	for (int i=0; i<*size; i++){
		fscanf(fp, "%d", &((*seq1)[i]));
	}

	fscanf(fp, "\n");

	*seq2 = malloc(sizeof(int)*(*size));
	for (int i=0; i<*size; i++){
		fscanf(fp, "%d", &((*seq2)[i]));
	}

	return RectArr;

}

ListNode* new_Node(int label){
	ListNode* temp = malloc(sizeof(ListNode));

	temp->label = label;
	temp->next = NULL;

	return temp;
}


Rectangle new_Rectangle(int label, double width, double height){
	Rectangle temp;

	temp.label = label;
	temp.width = width;
	temp.height = height;

	temp.x= 0;
	temp.y=0;

	temp.h_head = NULL;
	temp.v_head = NULL;

	return temp;

}



void destroy_list(ListNode* list){
	
//	if (list != NULL){
		if (list->next != NULL){
			destroy_list(list->next);
		}
	
		free(list);
//	}

	return;

}

Rectangle* Build_Graph(Rectangle* rArr, int size, int* S1, int* S2){

	
/*********BUILD HORIZ GRAPH *********************/
	//horiz[0] = no
//	(rArr[S1[0]-1].h_head) = new_Node(S1[0]);

	//horiz[size-1] = last node
//	(rArr[S2[0]-1].h_head) = new_Node(S2[0]);


	for (int i=1; i< size; i++){
		int x1 = S1[i];
		int y1 = S2[i];
		int a = i+1;
		if (a < size){
			while (S1[a] == x1 || S1[a] == y1 || S2[a] == x1 || S2[a] == y1 ){
				a++;
			}
		}
		else a--;
		int x2 = S1[a];
		int y2 = S2[a];

		if (x2 == S2[0] && y2 == S1[0]){
		//	rArr[x1-1].h_head = new_Node(x1);
		//	rArr[y1-1].h_head = new_Node(y1);
		}

		if ((rArr[x1-1].h_head) == NULL || (rArr[y1-1].h_head) == NULL){
			(rArr[x1-1].h_head) = new_Node(x1);
			(rArr[x1-1].h_head)->next = new_Node(x2);
			ListNode* curr1 = (rArr[x1-1].h_head)->next;
			curr1->next = new_Node(y2);

			(rArr[y1-1].h_head) = new_Node(y1);
			(rArr[y1-1].h_head)->next = new_Node(y2);
			ListNode* curr2 = (rArr[y1-1].h_head)->next;
			curr2->next = new_Node(x2);

		}
	}

	/****************8UILD VERT GRAPH********************/

	(rArr[S1[0]-1].v_head) = new_Node(S1[0]);
	(rArr[S2[0]-1].v_head) = new_Node(S2[0]);
	ListNode* currB = (rArr[S2[0]-1].v_head);

	for (int i=1; i<size; i++){
		int x1 = S1[i];
		int y1 = S2[i];	
	
		if ((rArr[x1-1].v_head) == NULL || (rArr[y1-1].v_head) == NULL){
			(rArr[x1-1].v_head) = new_Node(x1);
			(rArr[x1-1].v_head)->next = new_Node(S1[0]);

			(rArr[y1-1].v_head) = new_Node(y1);
			(rArr[y1-1].v_head)->next = new_Node(x1);
			currB->next = new_Node(y1);
			currB = currB->next;
		}
	}

	return rArr;
    
}

double max_d(double a, double b){
	if (a >= b){
		return a;
	}

	else{
		return b;
	}

}

Rectangle* get_Coord(Rectangle* rArr, int size, int* S1, int* S2){
/**	rArr[S1[0]-1].x = 0;
	rArr[S2[0]-1].x = 0;
	rArr[S1[1]-1].x = 0;
	rArr[S2[1]-1].x = 0;
	rArr[S2[0]-1].y = 0;



	for (int i = 2; i < size; i++){
		if (rArr[S1[i]-1].x<0 && rArr[S2[i]-1].x<0){
			int x = i;
			double count = 0;
			while (x > 1){
				double w1 = rArr[S1[x-1]-1].width;
				double w2 = rArr[S2[x-1]-1].width;
				double max_w = max_d(w1, w2);
				count = count + max_w;
				x--;
			}
			rArr[S1[i]-1].x = count/2.0;
			rArr[S2[i]-1].x = count/2.0;
		}
	}

**/
	for (int i = 0; i<size; i++){
		int val = S2[i];
		int x = 0;
		//fprintf(stdout, "val: %d\n", val);
		while (S1[x] != val && x<size){
			if (S1[x] > 0 && rArr[S1[x]-1].y <= rArr[val-1].y) {
				rArr[S1[x]-1].y = rArr[S1[x]-1].y + rArr[val-1].height;
			//	fprintf(stdout, "val: %d  y: %le\n", S1[x], rArr[S1[x]-1].y );
			}
			x++;
		}
		if (S1[x] == val){
			S1[x] = S1[x]*-1;
		}
		x++;
		while (x<size){
			if (S1[x] > 0 && (rArr[S1[x]-1].x < (rArr[val-1].x + rArr[val-1].width))){
				rArr[S1[x]-1].x = rArr[S1[x]-1].x + rArr[val-1].width;
				if (rArr[S1[x]-1].x > (rArr[val-1].x + rArr[val-1].width)){
					rArr[S1[x]-1].x =  (rArr[val-1].x + rArr[val-1].width);
				}
			//	fprintf(stdout, "val: %d  x: %le\n", S1[x], rArr[S1[x]-1].x );
			}
			x++;
		}
	}

	return rArr;



/********GET DEGREE**********/
	for (int i=0; i<size; i++){
		ListNode* crawl = (rArr[i].h_head);
		int count = 0;
		while (crawl->next){
		 	count++;
			crawl = crawl->next;
		}
		rArr[i].degree_h = count;
	}
		
	for (int i=0; i<size; i++){
		ListNode* crawl = (rArr[i].v_head);
		int count = 0;
			while (crawl->next){
				count++;
				crawl = crawl->next;
			}
			rArr[i].degree_v = count;
	}



}

