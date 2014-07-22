/*******************************************************************************
*	Author		:		Gautam Kumar										   *
*	Date		:		Sunday 06 July 2014 06:15:51 PM IST 				   *
*	Program		:		Wrapper for quick sort function						   *
*	Input		:															   *
*	Output		:															   *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*********************** global variables and constants ***********************/

/*--------------------------------- END --------------------------------------*/


/*************************** function prototypes ******************************/
long int ChoosePivot(unsigned int no_of_records);
void Partition(long int *arr, unsigned int pivot_index, _Bool ascending);
/*--------------------------------- END --------------------------------------*/


void QuickSort(long int *arr, unsigned int no_of_records, _Bool ascending) {
	long int pivot_index = 0;
	
	/*********************** base case implementation *************************/
	if (no_of_records == 1) {
		//do nothing
	/*--------------------------------- END ----------------------------------*/
	
	
	/********************** general case implementation ***********************/
	} else {
		pivot_index = ChoosePivot(no_of_records);
		printf("pivot index: %ld\n", pivot_index);

		//swapping the first element with pivot
		long int swap_Space = 0;
		swap_Space = arr[pivot_index];
		arr[pivot_index] = arr[0];
		arr[0] = swap_Space;
		
		//calling partiotion function on the array
		Partition(arr, no_of_records, ascending);
		
		/******************** making the recursive calls **********************/
		//sorting first part
		QuickSort(arr, pivot_index, ascending);
		//sorting second part
		QuickSort(arr+pivot_index+1, no_of_records-pivot_index-1, ascending);
		/*------------------------------ END ---------------------------------*/
	}
	
	/*--------------------------------- END ----------------------------------*/
}



long int ChoosePivot(unsigned int no_of_records) {
	time_t t;
	long int pivot_index = 0, pivot = 0;
	
	//intializes random number generator
	srand((unsigned) time(&t));
	
	//generating random pivot in 0 to no_of_records
	pivot_index = ((double)rand() / (double)RAND_MAX) * no_of_records;
		
	return pivot_index;
}

void Partition(long int *arr, unsigned int no_of_records, _Bool ascending) {
	unsigned int i, j;
	long int pivot;
	
	pivot = arr[0];
	i = 1;
	for (j = 1; j < no_of_records; j++) {
		if (arr[j] < pivot) {
			long int temp;
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	
	//putting pivot in its rightful position
	long int temp;
	temp = arr[0];
	arr[0] = arr[i-1];
	arr[i-1] = temp;
}
