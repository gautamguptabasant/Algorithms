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

#include "QuickSort.h"

/*********************** global variables and constants ***********************/
/* order of sorting
   set 1 for ascending
   	   0 for descending
*/
static _Bool ascending = 1;
/*--------------------------------- END --------------------------------------*/


/*************************** function prototypes ******************************/

/*--------------------------------- END --------------------------------------*/


int main(int argc, char *argv[]) {
	FILE *fp_r_unsorted, *fp_w_sorted;
	long int *arr_ptr;
	unsigned long int record_count = 0, running_count = 0;
	_Bool record_count_specified = false;
	_Bool output_required_in_file = true;
	char usage[] = "usage: ./QuickSort \
[unsorted_file_name sorted_file_name No_of_records]";
	
	/*************** parsing input arguments and validating *******************/
	switch (argc) {
        case 1:
            fp_r_unsorted = fopen("unsorted.txt", "r");
            fp_w_sorted = fopen("sorted.txt", "w");
            break;
        case 2:
            fp_r_unsorted = fopen(argv[1], "r");
            fp_w_sorted = fopen("sorted.txt", "w");
            break;
        case 3:
            fp_r_unsorted = fopen(argv[1], "r");
            fp_w_sorted = fopen(argv[2], "w");
            break;
        case 4:
            fp_r_unsorted = fopen(argv[1], "r");
            fp_w_sorted = fopen(argv[2], "w");
            record_count = atoi(argv[3]);
            record_count_specified = true;
            break;
        default:
            printf("Invalid arguments.\n%s\n", usage);
    }
	
	if (fp_r_unsorted == NULL) {
        printf("Input file doesn't exist. Exiting\n");
        exit(-1);
    }

    if (fp_w_sorted == NULL) {
        printf("Output file doesn't exist or couldn't be created. Exiting\n");
        exit(-1);
    }
    
	/*------------------------------- END ------------------------------------*/
	
	
	/********** reading unsorted integer from the input file ******************/
	//getting number of records
	// see one note chapter on Trics in notebook- C Programming for details 
    if (!record_count_specified) {
        while (EOF != (fscanf(fp_r_unsorted, "%*[^\n]"), 
        	fscanf(fp_r_unsorted, "%*c")))
            ++record_count;
    }
    rewind(fp_r_unsorted);
    printf("Input record count: %ld\n", record_count);
    
    //allocating space to store all the records
    arr_ptr = (long int *) malloc(record_count * sizeof(long int));

	//reading all the records in array
    for(running_count = 0; running_count < record_count; running_count++) {
        fscanf(fp_r_unsorted, "%ld", &arr_ptr[running_count]);
    }
    
    /* 
    //printing the records read from file
    for(running_count = 0; running_count < record_count; running_count++) {
		printf("%d\n", arr_ptr[running_count]);
	}
	*/
	/*------------------------------- END ------------------------------------*/


	/************************* calling quick sort *****************************/
	QuickSort(arr_ptr, record_count, ascending);
	/*------------------------------- END ------------------------------------*/

	
	/******************* writting sorted records in output file ***************/
	for(running_count = 0; running_count < record_count; running_count++) {
        fprintf(fp_w_sorted, "%ld\n", arr_ptr[running_count]);
    }
	/*------------------------------- END ------------------------------------*/
	
	fclose(fp_r_unsorted);
	fclose(fp_w_sorted);
	return EXIT_SUCCESS;
}


