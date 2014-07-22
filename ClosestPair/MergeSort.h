/*
Author		:Gautam Kumar
Program		:A function to sort an array using merge sort
Arguments	:	
	1) Pointer to the array to be sorted
	2) Number of elements in the array
*/

#include<stdio.h>
#define ascending 0

void mergeSort(long int *arr, unsigned long long int no_of_records) {
	long int sorted_arr[no_of_records];

//	{
//		unsigned long long int i = 0;
//		for (i = 0; i < no_of_records; i++) {
//			printf("%ld\t", arr[i]);
//		}
//		printf("\nUnsorted array\n");
//	};

	if (no_of_records == 1) {
		sorted_arr[0] = arr[0];
	} else if (no_of_records == 2) {
		if (ascending) {
			if (arr[0] > arr[1]) {
				sorted_arr[0] = arr[1];
				sorted_arr[1] = arr[0];
			} else {
				sorted_arr[0] = arr[0];
				sorted_arr[1] = arr[1];
			}
		} else {
			if (arr[0] > arr[1]) {
				sorted_arr[0] = arr[0];
				sorted_arr[1] = arr[1];
			} else {
				sorted_arr[0] = arr[1];
				sorted_arr[1] = arr[0];
			}
		}
	} else {
		mergeSort(arr, no_of_records/2);
		mergeSort(arr + no_of_records/2, no_of_records - no_of_records/2);

		unsigned long long int i = 0, j = 0, k = 0;
		while((i < no_of_records/2) && (j < (no_of_records - no_of_records/2))){
			if (ascending) {
				if (arr[i] > arr[no_of_records/2 + j]) {
					sorted_arr[k] = arr[no_of_records/2 + j];
					k++; j++;
				} else {
					sorted_arr[k] = arr[i];
					k++;i++;
				}
			} else {
				if (arr[i] > arr[no_of_records/2 + j]) {
					sorted_arr[k] = arr[i];
					k++; i++;
				} else {
					sorted_arr[k] = arr[no_of_records/2 + j];
					k++; j++;
				}
			}
		}

		while (i < no_of_records/2) {
			sorted_arr[k] = arr[i];
			k++; i++;
		}

		while (j < no_of_records - no_of_records/2) {
			sorted_arr[k] = arr[no_of_records/2 + j];
			k++; j++;
		}
	}
	
	{
		unsigned long long int i = 0;
		for (i = 0; i < no_of_records; i++) {
			arr[i] = sorted_arr[i];
//			printf("%ld\t", arr[i]);
		}
//		printf("\nsorted_arr\n");
	}
}


