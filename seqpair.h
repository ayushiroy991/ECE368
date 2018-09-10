#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _listNode{
	int label;
	struct _listNode* next;
}ListNode;

typedef struct _rectangle{
	int label;
	double width;
	double height;
	double x;
	double y;
	int degree_v;
	int degree_h;
	ListNode* h_head;
	ListNode* v_head;
}Rectangle;

Rectangle* Read_Input(int* size,int** seq1, int** seq2, FILE *fp);
Rectangle new_Rectangle(int label, double w, double h);
ListNode* new_Node(int label);
void destroy_list(ListNode* list);
double max_d(double a, double b);
Rectangle* Build_Graph(Rectangle* rArr, int size, int* S1, int* S2);
Rectangle* get_Coord(Rectangle* rArr, int size, int* S1, int* S2);
