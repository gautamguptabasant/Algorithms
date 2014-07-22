/*!
 *  @file
 *  \brief     Dijkstra Shortest Path Algorithm - Main Code.
 *  \details   In this program, we have implemented Dijkstra Shortest path algorithm
 *  		   to find out shortest path between a source and a destination node.
 *  \author    Gautam Kumar
 *  \version   1.3
 *  \date      20 August, 2013
 *  \pre       Expects the graph description and the inputs each in separate text files
 *  \copyright Open Source.
 */

/*! \mainpage
   The hiarchy of the function calls explained by graph:
   \dot
       digraph G {
              node [shape=record, fontname=Helvetica, fontsize=10];
              b [ label="main"];
              c [ label="PathTrace"];
              d [ label="Dijkstra"];
              b -> c [ arrowhead="open", style="solid" ];
              b -> d [ arrowhead="open", style="solid" ];
      }
   \enddot
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** Global variable declaration*/
#define uint_Inf RAND_MAX
unsigned int uint_NoOfNodes;
unsigned int **uint_ptr_DistMatrix;

/** Function prototype specified here*/
void Dijkstra(unsigned int *, unsigned int, unsigned int);
void PathTrace(unsigned int *, unsigned int *, unsigned int, unsigned int);

/**
   main() function.
   @param[out] code Code describing the termination status of program.
   @param[in] agrc The number of command line arguments.
   @param[in] argv The command line arguments.
 */
int main(int argc, int* argv[]) {
	unsigned int uint_SNode = 0;
	unsigned int uint_DNode = 0, uint_dist = 0;
	int int_ctrI, int_ctrJ, int_ctrK, int_ctrL;
	char char_IsDistMatSymmetric = 'y', str_temp[20];
	FILE *file_ptr, *file_ptw;
	unsigned int *uint_ptr_DistArray, *uint_ptr_ShortPath;

	/** Parsing the command line arguments*/
	if (argc > 5) {
		printf("\nToo many arguments!!! Aborting...\n");
		exit(0);

	}  else if (argc == 5) {
		uint_NoOfNodes = atoi(argv[1]);
		char_IsDistMatSymmetric = (char) argv[2];

		file_ptr = fopen(argv[3],"r");
		if (file_ptr == NULL) {
			printf("\nError in opening file: %s !!!Aborting...", argv[3]);
			exit(1);
		} else printf("\n%s opened for reading...", argv[3]);

		file_ptw = fopen(argv[4],"w");
		if (file_ptw == NULL) {
			printf("\nError in opening file: %s !!!Aborting...", argv[4]);
			exit(2);
		} else printf("\n%s opened for reading...", argv[4]);

	}  else if (argc == 4) {
		uint_NoOfNodes = atoi(argv[1]);
		char_IsDistMatSymmetric = (char) argv[2];
		file_ptr = fopen(argv[3],"r");
		if (file_ptr == NULL) {
			printf("\nError in opening file: %s !!!Aborting...", argv[3]);
			exit(1);
		} else printf("\n%s opened for reading...\n", argv[3]);

	} else if (argc == 3) {
		uint_NoOfNodes = atoi(argv[1]);
		char_IsDistMatSymmetric = argv[2];

	} else if (argc == 2) {
		uint_NoOfNodes = atoi(argv[1]);
		char_IsDistMatSymmetric = 'y';

	} else {
		uint_NoOfNodes = 7;
		char_IsDistMatSymmetric = 'y';
	}

	if (argc < 4) {
		file_ptr = fopen("distance.txt","r");
		if (file_ptr == NULL) {
			printf("\nError in opening file: 'distance.txt'!!! Aborting...\n");
		} else printf("\ndistance.txt opened for reading...");
	}

	if (argc < 5) {
		file_ptw = fopen("routes.txt","w");
		if (file_ptw == NULL) {
			printf("\nError in opening file: 'input.txt'!!! Aborting...\n");
		} else printf("\nroutes.txt opened for writing...\n");
	}


	/** Allocating memory for storing the distances from all nodes to all nodes*/
	uint_ptr_DistMatrix = malloc(sizeof(*uint_ptr_DistMatrix) * uint_NoOfNodes + 1);
	if (uint_ptr_DistMatrix) {
		for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
			uint_ptr_DistMatrix[int_ctrI] = malloc(sizeof(*uint_ptr_DistMatrix[int_ctrI]) * uint_NoOfNodes+ 1);
		}
	}


	/** Initializing the Distance Matrix to infinite value*/
	for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
		for (int_ctrJ = 0; int_ctrJ < uint_NoOfNodes; int_ctrJ++) {
			uint_ptr_DistMatrix[int_ctrI][int_ctrJ] = uint_Inf;
		}
	}


	/** Setting the diagonal elements to 0*/
	for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
		uint_ptr_DistMatrix[int_ctrI][int_ctrI] = 0;
	}


	/** Reading distances between nodes from file distance.txt*/
	while (!feof(file_ptr)) {
		fscanf(file_ptr, "%d\t%d\t%d", &uint_SNode, &uint_DNode, &uint_dist);
		if ((uint_SNode == 0) || (uint_DNode == 0) || (uint_dist == 0)) {
			printf("\nInvalid data in file distance.txt!!! Aborting...\n");
			exit(3);
		}
		uint_ptr_DistMatrix[uint_SNode-1][uint_DNode-1] = uint_dist;
	}


	/** Copying values in distance matrix if it is symmetric*/
	if (char_IsDistMatSymmetric == 'y') {
		for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
			for (int_ctrJ = 0; int_ctrJ < uint_NoOfNodes; int_ctrJ++) {
				if ((uint_ptr_DistMatrix[int_ctrI][int_ctrJ]) == uint_Inf) {
					uint_ptr_DistMatrix[int_ctrI][int_ctrJ] = uint_ptr_DistMatrix[int_ctrJ][int_ctrI];
				} else {
					uint_ptr_DistMatrix[int_ctrJ][int_ctrI] = uint_ptr_DistMatrix[int_ctrI][int_ctrJ];
				}
			}
		}
	}


	/** Getting memory for distance array to work on, corresponding to the source
	 * node entered by user
	 */
	uint_ptr_DistArray = malloc(sizeof(unsigned int) * uint_NoOfNodes + 1);
	uint_ptr_ShortPath = malloc(sizeof(unsigned int) * uint_NoOfNodes + 1);


	/** Generating all possible source destination pair*/
	for (int_ctrK = 0; int_ctrK < uint_NoOfNodes; int_ctrK++) {
		for (int_ctrL = int_ctrK + 1; int_ctrL < uint_NoOfNodes; int_ctrL++) {
			uint_SNode = int_ctrK + 1;
			uint_DNode = int_ctrL + 1;

			uint_ptr_DistArray = uint_ptr_DistMatrix[uint_SNode - 1];
			/** Calling Dijkstra function to calculate the minimum distance*/
			Dijkstra(uint_ptr_DistArray, uint_SNode, uint_DNode);

			/** Obtaining and printing the shortest path  */
			for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
				uint_ptr_ShortPath[int_ctrI] = 0;
			}

			/** Calling the path trace function*/
			PathTrace(uint_ptr_DistArray, uint_ptr_ShortPath, uint_SNode, uint_DNode);


			/** Printing the shortest path on terminal*/
			if (uint_SNode == 1) {
				fprintf(file_ptw, "Node %d - ", uint_SNode);
			}
			for (int_ctrI = uint_NoOfNodes - 1; int_ctrI > 0; int_ctrI--) {
				if (uint_ptr_ShortPath[int_ctrI] != 0){
					fprintf(file_ptw, "Node %d - ", uint_ptr_ShortPath[int_ctrI] + 1);
				}
			}
			fprintf(file_ptw, "Node %d\n", uint_ptr_ShortPath[0] + 1);
		}
	}


	/** Freeing the allocated memory*/
	for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
		free(uint_ptr_DistMatrix[int_ctrI]);
	}
	free (uint_ptr_DistMatrix);
	free(uint_ptr_DistArray);
	free(uint_ptr_ShortPath);

	fclose(file_ptr);
	fclose(file_ptw);
	return EXIT_SUCCESS;
}



/*!
 *  @file
 *  \brief     Dijkstra Shortest Path Algorithm - Minimum Distance Calculator.
 *  \details   In this program, implement the Dijkstra algorithm
 *  			to obtain the minimum distance between the specifiec nodes
 *  \author    Gautam Kumar
 *  \version   1.3
 *  \date      20 August, 2013
 *  \copyright Open Source.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define uint_Inf RAND_MAX
extern unsigned int uint_NoOfNodes;
extern unsigned int **uint_ptr_DistMatrix;
/**
   \brief Function to calculate the shortest path
   \details Implementing the Dijkstra's Algorithm to find shortest path between
            source and destination nodes
   @param[in] uint_ptr_DistArray Array containing the shortest
   	   	   	  distances from the specified source node to other nodes.
   @param[in] uint_SNode The source node.
   @param[in] uint_DNode The destination node.
 */

void Dijkstra(unsigned int *uint_ptr_DistArray, unsigned int uint_SNode, unsigned int uint_DNode) {
	unsigned int uint_CurrNode, int_ctrI;
	int int_minWeight;
	_Bool *boolarray_ptr_visited;
	_Bool bool_allVisitedFlag;

	/** Getting memory for visited array
	 * and then initializing it
	 */
	boolarray_ptr_visited = malloc(sizeof(_Bool) * uint_NoOfNodes + 1);
	for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
		boolarray_ptr_visited[int_ctrI] = 0;
	}

	uint_CurrNode = uint_SNode - 1;
	boolarray_ptr_visited[uint_CurrNode] = 1;
	while (1) {
		/** find smallest element in the array among those nodes
		 * which are marked unvisited
		 */
		int_minWeight = uint_Inf;
		for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
			if (!boolarray_ptr_visited[int_ctrI]) {
				if (int_minWeight > uint_ptr_DistArray[int_ctrI]) {
					int_minWeight = uint_ptr_DistArray[int_ctrI];
					uint_CurrNode = int_ctrI;
				}
			}
		}
		boolarray_ptr_visited[uint_CurrNode] = 1;

		/** Look into the Distance matrix for row corresponding to
		 * the smallest element node/current node for non infinite values and
		 * also only the once which are marked unvisited.
		 * Update those values.
		 */
		for (int_ctrI = 0; int_ctrI < uint_NoOfNodes; int_ctrI++) {
			if (uint_ptr_DistMatrix[uint_CurrNode][int_ctrI] != uint_Inf) {
				if (!boolarray_ptr_visited[int_ctrI]) {
					if ((uint_ptr_DistMatrix[uint_CurrNode][int_ctrI]+ uint_ptr_DistArray[uint_CurrNode]) < uint_ptr_DistArray[int_ctrI]) {
						uint_ptr_DistArray[int_ctrI] = uint_ptr_DistMatrix[uint_CurrNode][int_ctrI]+ uint_ptr_DistArray[uint_CurrNode];
					}
				}
			}
		}

		/** check for break conditions:
		 * 1. the destination node has been visited
		 */
		bool_allVisitedFlag = 0;
		for (int_ctrI = 0; ((int_ctrI < uint_NoOfNodes) && (int_ctrI != uint_DNode)); int_ctrI++) {
			if (boolarray_ptr_visited[uint_DNode - 1]){
				bool_allVisitedFlag = 1;
				break;
			}
		}
		if (bool_allVisitedFlag) {
			break;
		}
	}
}


