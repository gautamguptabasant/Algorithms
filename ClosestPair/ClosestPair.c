/*
Author		:	Gautam Kumar
Date		:	Thursday 03 July 2014 05:35:25 PM IST 
Program		:	A C program to find the closest pair among a given set of pair 
				of points in a 2D plane
Arguments	:	
				1) filename containing the set of points in 2D plane
				2) Number of pairs in the file
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <math.h>
/* global variables and constants */
#define ascending 1

/* function prototypes */
void mergeSort(int *arr, int *arrY, 
			unsigned int no_of_records);
int ** closestPair(int** points_sorted_onX, 
			int** points_sorted_onY, unsigned int no_of_records);

int main(int argc, char *argv[]){
	FILE *fp_r_inputSet;
    unsigned int record_count = 0, running_count = 0;
    _Bool record_count_specified = false;
 	int **points, **points_sorted_onX, **points_sorted_onY;
    char usage[] = "usage: ./ClosestPair \
[Input_file_name No_of_points]";

	int **closest_points;

    switch (argc) {
        case 1:
            fp_r_inputSet = fopen("InputPointSet.txt", "r");
            break;
        case 2:
            fp_r_inputSet = fopen(argv[1], "r");
            break;
        case 3:
            fp_r_inputSet = fopen(argv[1], "r");
            record_count = atoi(argv[2]);
            record_count_specified = true;
            break;
        default:
            printf("Invalid arguments.\n%s\n", usage);
    }

    if (fp_r_inputSet == NULL) {
        printf("Input file doesn't exist. Exiting\n");
        exit(-1);
    }

    /* see one note chapter on Trics in notebook- C Programming for details */
    if (!record_count_specified) {
        while (EOF != (fscanf(fp_r_inputSet, "%*[^\n]"), 
        		fscanf(fp_r_inputSet, "%*c")))
            ++record_count;
    }
    rewind(fp_r_inputSet);
    printf("Number of pairs: %d\n", record_count);
    if (record_count == 0) {
    	printf("Exiting! 0 records found!\n");
    	exit(-1);
    }
    
   	/* allocating space to store all the points */
    points = (int **) malloc(2 * sizeof(int));
    points[0] = (int *) malloc(record_count * sizeof(int));
    points[1] = (int *) malloc(record_count * sizeof(int));
    
    closest_points = (int **) malloc(2 * sizeof(int));
    closest_points[0] = (int *) malloc(record_count * sizeof(int));
    closest_points[1] = (int *) malloc(record_count * sizeof(int));
    
    /*Creating copies of points sorted based on x and y coordinates
    	arr_sorted_onX
    	arr_sorted_onY, respectively
    */
   	//alocating space
   	points_sorted_onX = (int **) malloc(2 * sizeof(int));
    points_sorted_onX[0] = (int *) malloc(record_count * sizeof(int));
    points_sorted_onX[1] = (int *) malloc(record_count * sizeof(int));
    points_sorted_onY = (int **) malloc(2 * sizeof(int));
    points_sorted_onY[0] = (int *) malloc(record_count * sizeof(int));
    points_sorted_onY[1] = (int *) malloc(record_count * sizeof(int));

    /* reading all the records in array */
    for(running_count = 0; running_count < record_count; running_count++) {
        fscanf(fp_r_inputSet, "%d\t%d", &points[0][running_count], 
        		&points[1][running_count]);
		points_sorted_onX[0][running_count] = points[0][running_count];
		points_sorted_onX[1][running_count] = points[1][running_count];
		points_sorted_onY[0][running_count] = points[0][running_count];
		points_sorted_onY[1][running_count] = points[1][running_count];
    }
    
    printf("printing pair of points\n"); 
    for(running_count = 0; running_count < record_count; running_count++) {
        printf("%d\t%d\n", points[0][running_count], 
        		points[1][running_count]);
    }

    
    //calling merge sort on these one  by one
    mergeSort(points_sorted_onX[0], points_sorted_onX[1], record_count);
    mergeSort(points_sorted_onY[1], points_sorted_onY[0], record_count);
    
    printf("printing pair of points\n"); 
    for(running_count = 0; running_count < record_count; running_count++) {
        printf("%d\t%d\n", points_sorted_onX[0][running_count], 
        		points_sorted_onX[1][running_count]);
    }

    printf("printing pair of points\n"); 
    for(running_count = 0; running_count < record_count; running_count++) {
        printf("%d\t%d\n", points_sorted_onY[0][running_count], 
        		points_sorted_onY[1][running_count]);
    }
   

	//calling function to calculate closest pair
	closest_points = closestPair(points_sorted_onX, points_sorted_onY, 
						record_count);
	
	printf("=================== Printing closest pair =====================\n");
	printf("(%d, %d) and (%d, %d)\n", closest_points[0][0], closest_points[1][0],
										closest_points[0][1], closest_points[1][1]);
/*    free(points[0]);
    free(points[1]);
    free(points);
    free(points_sorted_onX[0]);
    free(points_sorted_onX[1]);
    free(points_sorted_onY[0]);
    free(points_sorted_onY[1]);
    free(points_sorted_onX);
    free(points_sorted_onY);
*/    

	return EXIT_SUCCESS;
} 


int ** closestPair(int** points_sorted_onX, 
			int** points_sorted_onY, unsigned int no_of_records){
	
	int **left_half_pointsX, **left_half_pointsY;
	int **right_half_pointsX, **right_half_pointsY;
	
	int ** closest_pair_in_left_half;
	int ** closest_pair_in_right_half;
	
	double min_dist_of_lt_and_rt = 0.0;
	
	int ** min_closest_pair;
	
	int x_bar = 0;
	
	int** s_Y;
	int i = 0;
	printf("=================== Printing input pairs =====================\n");
	for (i = 0; i < no_of_records; i++) {
		printf("(%d, %d)\n", points_sorted_onX[0][i], points_sorted_onX[1][i]);
	}
	printf("=================== **********************====================\n");
	
	left_half_pointsX = (int **) malloc(2 * sizeof(int));
	right_half_pointsX = (int **) malloc(2 * sizeof(int));
	left_half_pointsY = (int **) malloc(2 * sizeof(int));
	right_half_pointsY = (int **) malloc(2 * sizeof(int));
	
	closest_pair_in_left_half = (int **) malloc(2 * sizeof(int));
	closest_pair_in_right_half = (int **) malloc(2 * sizeof(int));
	closest_pair_in_left_half[0] = (int *) malloc(2 * sizeof(int));
	closest_pair_in_left_half[1] = (int *) malloc(2 * sizeof(int));
	closest_pair_in_right_half[0] = (int *) malloc(2 * sizeof(int));
	closest_pair_in_right_half[1] = (int *) malloc(2 * sizeof(int));
	
	min_closest_pair = (int **) malloc(2 * sizeof(int));
	min_closest_pair[0] = (int *) malloc(2 * sizeof(int));
	min_closest_pair[1] = (int *) malloc(2 * sizeof(int));
	
	s_Y = (int **) malloc(2 * sizeof(int));
	s_Y[0] = (int *) malloc(no_of_records * sizeof(int));
	s_Y[1] = (int *) malloc(no_of_records * sizeof(int));
	
	//q_x = left half of p_x
	left_half_pointsX[0] = points_sorted_onX[0];
	left_half_pointsX[1] = points_sorted_onX[1];
	
	//q_y = left half of p_y
	left_half_pointsY[0] = points_sorted_onY[0];
	left_half_pointsY[1] = points_sorted_onY[1];
	
	//r_x = right half of p_x
	right_half_pointsX[0] = points_sorted_onX[0] + no_of_records/2;
	right_half_pointsX[1] = points_sorted_onX[1] + no_of_records/2;
	
	//r_y = right half of p_y
	right_half_pointsY[0] = points_sorted_onY[0] + no_of_records/2;
	right_half_pointsY[1] = points_sorted_onY[1] + no_of_records/2;
	
	//implementing the base cases
	if (no_of_records == 2) {
		min_closest_pair[0][0] = points_sorted_onX[0][0];
		min_closest_pair[1][0] = points_sorted_onX[1][0];
		min_closest_pair[0][1] = points_sorted_onX[0][1];
		min_closest_pair[1][1] = points_sorted_onX[1][1];
	} else if (no_of_records == 3) {
		float d1, d2, d3;
		d1 = sqrt(pow(points_sorted_onX[0][0]-points_sorted_onX[0][1],2) +
					pow(points_sorted_onX[1][0]-points_sorted_onX[1][1],2));
		d2 = sqrt(pow(points_sorted_onX[0][0]-points_sorted_onX[0][2],2) +
					pow(points_sorted_onX[1][0]-points_sorted_onX[1][2],2));
		d3 = sqrt(pow(points_sorted_onX[0][2]-points_sorted_onX[0][1],2) +
					pow(points_sorted_onX[1][2]-points_sorted_onX[1][1],2));
	
		if (d1 < d2) { // d1 smaller
			if (d1 < d3) { // d1 smallest
				min_closest_pair[0][0] = points_sorted_onX[0][0];
				min_closest_pair[1][0] = points_sorted_onX[1][0];
				min_closest_pair[0][1] = points_sorted_onX[0][1];
				min_closest_pair[1][1] = points_sorted_onX[1][1];
			} else { // d3 smallest
				min_closest_pair[0][0] = points_sorted_onX[0][2];
				min_closest_pair[1][0] = points_sorted_onX[1][2];
				min_closest_pair[0][1] = points_sorted_onX[0][1];
				min_closest_pair[1][1] = points_sorted_onX[1][1];
			}
		} else { //d2 smaller than d1
			if (d2 < d3) { // d2 smallest
				min_closest_pair[0][0] = points_sorted_onX[0][0];
				min_closest_pair[1][0] = points_sorted_onX[1][0];
				min_closest_pair[0][1] = points_sorted_onX[0][2];
				min_closest_pair[1][1] = points_sorted_onX[1][2];
			} else { // d3 smallest
				min_closest_pair[0][0] = points_sorted_onX[0][2];
				min_closest_pair[1][0] = points_sorted_onX[1][2];
				min_closest_pair[0][1] = points_sorted_onX[0][1];
				min_closest_pair[1][1] = points_sorted_onX[1][1];
			}
		}
	} else {
		//making the recursive calls
		printf("calling left half\n");
		closest_pair_in_left_half = closestPair(left_half_pointsX, 
						left_half_pointsY, no_of_records/2);
		printf("calling right half\n");
		closest_pair_in_right_half = closestPair(right_half_pointsX, 
						right_half_pointsY, no_of_records - no_of_records/2);

		//finding the min of left and rt half shortest points
		double temp_dist_left = 0.0;
		double temp_dist_right = 0.0;

		temp_dist_left = sqrt(pow(closest_pair_in_left_half[0][0] - closest_pair_in_left_half[0][1],2)
						+pow(closest_pair_in_left_half[1][0] - closest_pair_in_left_half[1][1],2));

		temp_dist_right = sqrt(pow(closest_pair_in_right_half[0][0] - closest_pair_in_right_half[0][1],2)
						+pow(closest_pair_in_right_half[1][0] - closest_pair_in_right_half[1][1],2));
		printf("dist left: %f\ndist rt: %f\n", temp_dist_left, temp_dist_right);
		
		if (temp_dist_left < temp_dist_right) {
			min_closest_pair[0][0] = closest_pair_in_left_half[0][0];
			min_closest_pair[1][0] = closest_pair_in_left_half[1][0];
			min_closest_pair[0][1] = closest_pair_in_left_half[0][1];
			min_closest_pair[1][1] = closest_pair_in_left_half[1][1];
			min_dist_of_lt_and_rt = temp_dist_left;
		} else {
			min_closest_pair[0][0] = closest_pair_in_right_half[0][0];
			min_closest_pair[1][0] = closest_pair_in_right_half[1][0];
			min_closest_pair[0][1] = closest_pair_in_right_half[0][1];
			min_closest_pair[1][1] = closest_pair_in_right_half[1][1];
			min_dist_of_lt_and_rt = temp_dist_right;
		}
		
		/*	
		min_closest_pair = closestSplitPair(left_half_pointsX, right_half_pointsX, 
											left_half_pointsY, right_half_pointsY, 
											min_dist_of_lt_and_rt, no_of_records/2);
		*/	
		//biggest x-coordinate in left half of P
		x_bar = right_half_pointsX[0][no_of_records/2 - 1] ;
		printf("xbar: %d\n", x_bar);
		
		int ctr2 = 0, ctr = 0; 
		for (ctr = 0; ctr < no_of_records/2; ctr++) {
			if (abs(x_bar) - abs(left_half_pointsY[0][ctr]) < min_dist_of_lt_and_rt) {
				s_Y[0][ctr2] = left_half_pointsY[0][ctr];
				s_Y[1][ctr2] = left_half_pointsY[1][ctr];
				//printf("(%d, %d)\n", s_Y[0][ctr2], s_Y[1][ctr2]);
				ctr2++;
			}
		}
		for (ctr = 0; ctr < no_of_records/2; ctr++) {
			if (abs(x_bar) - abs(right_half_pointsY[0][ctr]) < min_dist_of_lt_and_rt) {
				s_Y[0][ctr2] = right_half_pointsY[0][ctr];
				s_Y[1][ctr2] = right_half_pointsY[1][ctr];
				//printf("(%d, %d)\n", s_Y[0][ctr2], s_Y[1][ctr2]);
				ctr2++;
			}
		}
		
		printf("------------printing the elements of s_y-------------------\n");
		for (ctr = 0; ctr < ctr2; ctr++) {
			printf("(%d, %d)\n", s_Y[0][ctr], s_Y[1][ctr]);
		}
		printf("\n");
		
		double best = min_dist_of_lt_and_rt;
		//min_closest_pair[0] = NULL;
		//min_closest_pair[1] = NULL;
		int ctr3;
		for (ctr = 0; ctr < ctr2 - 1; ctr++) {
			int temp;
			temp = (7 < ctr2 - ctr) ? 7 : ctr2 - ctr;		
			for (ctr3 = 1; ctr3 < temp; ctr3++) {
				double d = 0.0;
				d = sqrt(pow(s_Y[0][ctr]-s_Y[0][ctr+ctr3],2) + 
						pow(s_Y[1][ctr]-s_Y[1][ctr+ctr3],2));
				printf("dis bet (%d, %d) and (%d, %d) is %f\n", s_Y[0][ctr],
						 s_Y[1][ctr], s_Y[0][ctr+ctr3], s_Y[1][ctr+ctr3], d);
				if (d < best) {
					min_closest_pair[0][0] = s_Y[0][ctr];
					min_closest_pair[1][0] = s_Y[1][ctr];
					min_closest_pair[0][1] = s_Y[0][ctr+ctr3];
					min_closest_pair[1][1] = s_Y[1][ctr+ctr3];
					best = sqrt(pow(min_closest_pair[0][0]-min_closest_pair[0][1],2) +
								pow(min_closest_pair[1][0]-min_closest_pair[1][1],2));
				}
			}
		}
	}
/*	
	free(left_half_pointsX);
	free(right_half_pointsX);
	free(left_half_pointsY);
	free(right_half_pointsY);
	free(closest_pair_in_left_half[0]);
	free(closest_pair_in_left_half[1]);
	free(closest_pair_in_right_half[1]);
	free(closest_pair_in_right_half[0]);
	free(closest_pair_in_left_half);
	free(closest_pair_in_right_half);
*/	
	printf("=================== Printing closest pair =====================\n");
	printf("(%d, %d) and (%d, %d)\n", min_closest_pair[0][0], min_closest_pair[1][0],
										min_closest_pair[0][1], min_closest_pair[1][1]);
 
	return min_closest_pair;
}




void mergeSort(int *arr, int *arrY, unsigned int no_of_records) {
	int sorted_arr[no_of_records];
	int sorted_arrY[no_of_records];

/*	{
		unsigned int i = 0;
		for (i = 0; i < no_of_records; i++) {
			printf("(%d, %d)\t", arr[i], arrY[i]);
		}
		printf("\nUnsorted array\n");
	};
*/
	if (no_of_records == 1) {
		sorted_arr[0] = arr[0];
		sorted_arrY[0] = arrY[0];
	} else if (no_of_records == 2) {
		if (ascending) {
			if (arr[0] > arr[1]) {
				sorted_arr[0] = arr[1];
				sorted_arr[1] = arr[0];
				sorted_arrY[0] = arrY[1];
				sorted_arrY[1] = arrY[0];
			} else {
				sorted_arr[0] = arr[0];
				sorted_arr[1] = arr[1];
				sorted_arrY[0] = arrY[0];
				sorted_arrY[1] = arrY[1];
			}
		} else {
			if (arr[0] > arr[1]) {
				sorted_arr[0] = arr[0];
				sorted_arr[1] = arr[1];
				sorted_arrY[0] = arrY[0];
				sorted_arrY[1] = arrY[1];
			} else {
				sorted_arr[0] = arr[1];
				sorted_arr[1] = arr[0];
				sorted_arrY[0] = arrY[1];
				sorted_arrY[1] = arrY[0];
			}
		}
	} else {
		mergeSort(arr, arrY, no_of_records/2);
		mergeSort(arr + no_of_records/2,  arrY + no_of_records/2, 
					no_of_records - no_of_records/2);

		unsigned int i = 0, j = 0, k = 0;
		while((i < no_of_records/2) && (j < (no_of_records - no_of_records/2))){
			if (ascending) {
				if (arr[i] > arr[no_of_records/2 + j]) {
					sorted_arr[k] = arr[no_of_records/2 + j];
					sorted_arrY[k] = arrY[no_of_records/2 + j];
					k++; j++;
				} else {
					sorted_arr[k] = arr[i];
					sorted_arrY[k] = arrY[i];
					k++;i++;
				}
			} else {
				if (arr[i] > arr[no_of_records/2 + j]) {
					sorted_arr[k] = arr[i];
					sorted_arrY[k] = arrY[i];
					k++; i++;
				} else {
					sorted_arr[k] = arr[no_of_records/2 + j];
					sorted_arrY[k] = arrY[no_of_records/2 + j];
					k++; j++;
				}
			}
		}

		while (i < no_of_records/2) {
			sorted_arr[k] = arr[i];
			sorted_arrY[k] = arrY[i];
			k++; i++;
		}

		while (j < no_of_records - no_of_records/2) {
			sorted_arr[k] = arr[no_of_records/2 + j];
			sorted_arrY[k] = arrY[no_of_records/2 + j];
			k++; j++;
		}
	}

	{
		unsigned int i = 0;
		for (i = 0; i < no_of_records; i++) {
			arr[i] = sorted_arr[i];
			arrY[i] = sorted_arrY[i];
//			printf("(%d, %d)\t", arr[i], arrY[i]);
		}
//		printf("\nsorted_arr\n");
	}
}


