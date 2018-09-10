#include "sorting.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void swap(long *arr, int loc1, int loc2){
  if (loc1 == loc2){
    return;
  }
  
  long temp = arr[loc1];
  arr[loc1] = arr[loc2];
  arr[loc2] = temp;
  return;
}

static int  med_of_three(long *arr, int left, int right){
  int middle = (right+left)/2;
  //middle = middle+left-1;

  if (arr[left] < arr[middle]){
  	if (arr[middle] < arr[right]){
	  //left, middle, right
	  return middle;
	  }
	else if (arr[left] < arr[right]){
	    //first, right, middle
		//swap(arr, right, middle);
	  return right;
	}
  	//right, left, middle`
	//swap(arr, left, right);
	//swap(arr, middle, right);
	return left;
  }

  else if (arr[right] < arr[middle]){
    //right middle, left
	//swap(arr, left, right);
  	return middle;
	}
  else if (arr[right] < arr[left]){
  	//middle, right, left
	//swap(arr, left, middle);
	//swap(arr, middle, right);
	return right;
  }
  
  //right, middle, left
  //swap(arr, left, right);
  return left; 

 /**if (arr[left] > arr[right]){
  	swap(arr, left, right);
  }

  if (arr[left] > arr[middle]){
    swap(arr, left, right);
}

  if (arr[middle] > arr[right]){
    swap(arr, middle, right);
	}
  
  swap(arr, middle, right-1);
  return arr[right-1];**/

}


static void three_sort(long*arr, int lb, int ub){

int size = ub - lb + 1;
    if (size <= 1)
	    return;
	if (size == 2) {
		if (arr[lb] > arr[ub]){
			swap(arr, lb, ub);
		}
		return;
	 }
	 else 
	 {
		if (arr[lb]>arr[ub-1]){
			//left > middle
			swap(arr,lb, ub-1);
		}
		if (arr[lb] > arr[ub]){
			//left > right
			swap(arr, lb, ub);
		}
		if (arr[ub-1] > arr[ub]){
			//middle >right
			swap(arr, ub-1, ub);
		}
	}
	}

static int partition(long* arr, int lb, int ub){
  int pivot_loc = med_of_three(arr, lb, ub);
  long pivot = arr[pivot_loc];
  swap(arr, pivot_loc, lb);
  int left = lb;
  int right = ub;


  while(left < right) {
    	while ( (left < ub) && (arr[left] <= pivot)){
		left++;
	}
	while (arr[right] > pivot){
	    right--;
	}

	if (left < right){
		swap(arr, left, right);
	}
  }

  arr[lb] = arr[right];
  arr[right] = pivot;
 	return right;
	

}
static void rec_Quick_Sort(long *Array, int lb, int ub){

      int size = ub - lb + 1;
    if (size <= 3){
    three_sort(Array, lb, ub);
    }

  if (lb >= ub){
  	return;
	}

  int pivot = partition(Array, lb, ub);

   //swap(Array, 0, pivot);

 // int loc = partition(Array, lb, u

  rec_Quick_Sort(Array, lb, pivot-1);

  rec_Quick_Sort(Array, pivot+1, ub );
  return;

        
}

void Quick_Sort(long* Array, int Size){
  rec_Quick_Sort(Array, 0, Size-1);
  //return;
}

static void merge(long *arr, long *temp,  int lb, int mid,  int ub){
  /**	 for (int k = lb; k<=ub; k++){
		temp[k] = arr[k];
		}**/

  memcpy(&temp[lb], &arr[lb], (mid-lb+1)*sizeof(long));
  memcpy(&temp[mid+1], &arr[mid+1], (ub-mid)*sizeof(long));

	int l = lb; //index of left
	int r = mid +1; //index of right

	for (int i = lb; i <= ub; i++){
		if (l>mid){
			arr[i] = temp[r++];
		}
		else if ( r> ub){
			arr[i] = temp[l++];
		}
		else if (temp[r] < temp[l]){
			arr[i] = temp[r++];
		}
		else {
			arr[i] = temp[l++];
		}

	}

	return;

}

static void rec_Merge_Sort(long *Array, long *temp, int lb, int ub){
	if (lb >= ub){
		return;
	}


 	
	int mid = (ub+lb)/2;

	rec_Merge_Sort(Array, temp, lb, mid);
        rec_Merge_Sort(Array, temp,  mid+1, ub);
		
	//if (Array[mid] > Array[mid+1]){
	    merge(Array,temp, lb, mid,ub);

	    //}

	return;
}

/**static int cmp_min(int a, int b){
  if (a <= b){
    return a;
  }
  else if (b < a){
    return b;
  }
  return b;
 
  }**/

void Merge_Sort(long *Array, int Size){
	long *temp = malloc((Size)*sizeof(long));
	 if (temp == NULL){
		fprintf(stdout, "cannot make merge temp array");
		return;
	  }

	 // memcpy(&temp[lb], &arr[lb], (mid-lb+1)*sizeof(long));
	 
	 /**	int s = 1;

	  while (s < Size){
	    int i = 0;
	    while (i <Size-s){
	      
		merge(Array, temp, i, i+s-1, cmp_min((i+2*s-1), Size-1));
		
	        i = i + 2*s;
	    }
	     s = 2*s;
	 } **/

	 rec_Merge_Sort(Array, temp, 0, Size-1);

	  free(temp);
  

}

