#include<stdio.h>


int main() {
	int **point;
	
	
	/* allocating space to store all the points */
	point = (int **) malloc(sizeof(int));
    point[0] = (int *) malloc(4 * sizeof(int));
    point[1] = (int *) malloc(4 * sizeof(int));
    
    point[0][0] = 1;
    point[0][1] = 2;
    point[0][2] = 3;
    point[0][3] = 4;
    
    point[1][0] = 5;
    point[1][1] = 6;
    point[1][3] = 8;
    point[1][4] = 9;
    
    printf("size of int: %ld\n", sizeof(int));
    printf("\nbase address: %ld\n", point);
   	int i = 0;
   	//for (i = 0; i< 8; i++) 
   		printf("%ld: %ld\n", *(*(point)+2), *(point)+2);
    return 0;
} 
	
