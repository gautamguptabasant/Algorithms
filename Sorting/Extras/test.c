#include<stdio.h>


int main() {
	int **point;
	
	
	/* allocating space to store all the points */
	point = (long int **) malloc(2 * sizeof(long int));
    point[0] = (long int *) malloc(4 * sizeof(long int));
    point[1] = (long int *) malloc(4 * sizeof(long int));
    
    point[0][0] = 1;
    point[0][1] = 2;
    point[0][2] = 3;
    point[0][3] = 4;
    
    point[1][0] = 5;
    point[1][1] = 6;
    point[1][3] = 8;
    point[1][4] = 9;
    
    printf("base address: %ld", point);
    printf("my add: %ld", point+2);
    return 0;
} 
	
