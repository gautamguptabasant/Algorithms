
/* Output: prints the sorted output, one per line,
    1. Either in a file sorted.txt
    2. or in the file specified as second command line argument
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* order of sorting
   set 1 for ascending
   	   0 for descending
*/
#define ascending 1
static const char invOutFile[] = "Inverions.txt";
unsigned long int no_of_inversions = 0;
FILE *fp_inv_w;

void mergeSort_and_count(int *arr, unsigned int no_of_records);

int main(int argc, char *argv[]){
    FILE *fp_r, *fp_w;
    int *arr_ptr;
    unsigned int record_count = 0, running_count = 0;
    _Bool record_count_specified = false;
    char usage[] = "usage: bubbleSort.exe \
    [unsorted_file_name sorted_file_name No_of_records]";

	fp_inv_w = fopen(invOutFile, "w");
	
    switch (argc) {
        case 1:
            fp_r = fopen("unsorted.txt", "r");
            fp_w = fopen("sorted.txt", "w");
            break;
        case 2:
            fp_r = fopen(argv[1], "r");
            fp_w = fopen("sorted.txt", "w");
            break;
        case 3:
            fp_r = fopen(argv[1], "r");
            fp_w = fopen(argv[2], "w");
            break;
        case 4:
            fp_r = fopen(argv[1], "r");
            fp_w = fopen(argv[2], "w");
            record_count_specified = true;
            break;
        default:
            printf("Invalid arguments.\n%s\n", usage);
    }

    if (fp_r == NULL) {
        printf("Input file doesn't exist. Exiting\n");
        exit(-1);
    }

    if (fp_w == NULL) {
        printf("Output file doesn't exist or couldn't be created. Exiting\n");
        exit(-1);
    }

    /* see one note chapter on Trics in notebook- C Programming for details */
    if (!record_count_specified) {
        while (EOF != (fscanf(fp_r, "%*[^\n]"), fscanf(fp_r, "%*c")))
            ++record_count;
    }
    rewind(fp_r);
    printf("count: %d\n", record_count);

    /* allocating space to store all the records */
    arr_ptr = (int *) malloc(record_count * sizeof(int));

    /* reading all the records in array */
    for(running_count = 0; running_count < record_count; running_count++) {
        fscanf(fp_r, "%d", &arr_ptr[running_count]);
    }

//    for(running_count = 0; running_count < record_count; running_count++) {
//        printf("%d\n", arr_ptr[running_count]);
//    }

	/* code for merge sort follows */
	mergeSort_and_count(arr_ptr, record_count);

	/* writing all the records in the output file
    for(running_count = 0; running_count < record_count; running_count++) {
        fprintf(fp_w, "%d\n", arr_ptr[running_count]);
    }
 	*/
	printf("\nNo of Inversions: %ld\n", no_of_inversions);
	fclose(fp_w);
	return 0;
}




void mergeSort_and_count(int *arr, unsigned int no_of_records) {
	int sorted_arr[no_of_records];

//	{
//		unsigned int i = 0;
//		for (i = 0; i < no_of_records; i++) {
//			printf("%d\t", arr[i]);
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
				no_of_inversions++;
				//fprintf(fp_inv_w, "%d\t%d\n", arr[1], arr[0]);
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
				no_of_inversions++;
				//fprintf(fp_inv_w, "%d\t%d\n", arr[1], arr[0]);
			}
		}
	} else {
		mergeSort_and_count(arr, no_of_records/2);
		mergeSort_and_count(arr + no_of_records/2, no_of_records - no_of_records/2);

		unsigned int i = 0, j = 0, k = 0;
		while((i < no_of_records/2) && (j < (no_of_records - no_of_records/2))){
			if (ascending) {
				if (arr[i] > arr[no_of_records/2 + j]) {
					sorted_arr[k] = arr[no_of_records/2 + j];
					{
						unsigned int l = 0;
						for (l = i; l < no_of_records/2; l++) {
							//fprintf(fp_inv_w, "%d\t%d\n", arr[l], arr[no_of_records/2 + j]);
							no_of_inversions++;
						}							
					}
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
					{
						unsigned int l = 0;
						for (l = i; l < no_of_records/2; l++) {
							//fprintf(fp_inv_w, "%d\t%d\n", arr[l], arr[no_of_records/2 + j]);
							no_of_inversions++;
						}							
					}
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

	//arr = sorted_arr;
	{
		unsigned int i = 0;
		for (i = 0; i < no_of_records; i++) {
			arr[i] = sorted_arr[i];
//			printf("%d\t", arr[i]);
		}
//		printf("\nsorted_arr\n");
	}
	//return arr;
}



