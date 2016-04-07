/*
** ANT.C
** Code to accompany Dr Dobbs article, 'Using ant colonies to solve optimization
** problems', by Andrew Colin, 2005
**
** The sample data in this file comes from the EILON50 data set, a standard 
** benchmark for the Travelling Salesman problem. The shortest tour known for this
** dataset is 427.96.
**
** This and other datasets can be found in the TSPLIB archive at 
** http://www.iwr.uni-heidelberg.de/groups/comopt/software/TSPLIB95/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define N 15
#define START_NODE 0
#define RHO 0.5
#define N_GENERATIONS 100
#define ALPHA 1
#define BETA 2
#define BEST_SOLUTION 427.96
#define X_VAL 0
#define Y_VAL 1

#define randomize() (srand(time(0)))

double tau[N][N];
//double distance[N][N];

double distance[15][15] = {
        { 0    ,    29,        82,        46,        68,        52,        72,        42,        51,        55,        29,        74,        23,        72,        46},
        { 29   ,      0,        55,        46,        42,        43,        43,        23,        23,        31,        41,        51,        11,        52,        21},
        { 82,        55,         0,        68,        46,        55,        23,        43,        41,        29,        79,        21,        64,        31,        51},
        { 46,        46,        68,         0,        82,        15,        72,        31,        62,        42,        21,        51,        51,        43,        64},
        { 68,        42,        46,        82,         0,        74,        23,        52,        21,        46,        82,        58,        46,        65,        23},
        { 52,        43,        55,        15,        74,         0,        61,        23,        55,        31,        33,        37,        51,        29,        59},
        { 72,        43,        23,        72,        23,        61,         0,        42,        23,        31,        77,        37,        51,        46,        33},
        { 42,        23,        43,        31,        52,        23,        42,         0,        33,        15,        37,        33,        33,        31,        37},
        { 51,        23,        41,        62,        21,        55,        23,        33,         0,        29,        62,        46,        29,        51,        11},
        { 55,        31,        29,        42,        46,        31,        31,        15,        29,         0,        51,        21,        41,        23,        37},
        { 29,        41,        79,        21,        82,        33,        77,        37,        62,        51,         0,        65,        42,        59,        61},
        { 74,        51,        21,        51,        58,        37,        37,        33,        46,        21,        65,         0,        61,        11,        55},
        { 23,        11,        64,        51,        46,        51,        51,        33,        29,        41,        42,        61,         0,        62,        23},
        { 72,        52,        31,        43,        65,        29,        46,        31,        51,        23,        59,        11,        62,         0,        59},
        { 46,        21,        51,        64,        23,        59,        33,        37,        11,        37,        61,        55,        23,        59,         0}
};


/*
double distance[15][15] = {
    {0, 633, 257,  91, 412, 150,  80, 134, 259, 505, 353, 324,  70, 211, 268},
    {633, 0, 390, 661, 227, 488, 572, 530, 555, 289, 282, 638, 567, 466, 420},
    {257, 390, 0, 228, 169, 112, 196, 154, 372, 262, 110, 437, 191, 74,  53},
    {91, 661, 228, 0, 383, 120,  77, 105, 175, 476, 324, 240,  27, 182, 239},
    {412, 227, 169, 383, 0, 267, 351, 309, 338, 196,  61, 421, 346, 243, 199},
    {150, 488, 112, 120, 267, 0,  63,  34, 264, 360, 208, 329,  83, 105, 123},
    {80, 572, 196,  77, 351,  63, 0, 29, 232, 444, 292, 297,  47, 150, 207},
    {134, 530, 154, 105, 309,  34,  29,   0, 249, 402, 250, 314,  68, 108, 165},
    {259, 555, 372, 175, 338, 264, 232, 249,   0, 495, 352,  95, 189, 326, 383},
    {505, 289, 262, 476, 196, 360, 444, 402, 495,   0, 154, 578, 439, 336, 240},
    {353, 282, 110, 324,  61, 208, 292, 250, 352, 154,   0, 435, 287, 184, 140},
    {324, 638, 437, 240, 421, 329, 297, 314,  95, 578, 435,   0, 254, 391, 448},
    {70, 567, 191,  27, 346,  83,  47,  68, 189, 439, 287, 254,   0, 145, 202},
    {211, 466,  74, 182, 243, 105, 150, 108, 326, 336, 184, 391, 145,   0,  57},
    {268, 420,  53, 239, 199, 123, 207, 165, 383, 240, 140, 448, 202,  57,   0}
};
*/

/* double distance[17][17] = {
    {0, 633, 257,  91, 412, 150,  80, 134, 259, 505, 353, 324,  70, 211, 268, 246, 121},
    {633, 0, 390, 661, 227, 488, 572, 530, 555, 289, 282, 638, 567, 466, 420, 745, 518},
    {257, 390, 0, 228, 169, 112, 196, 154, 372, 262, 110, 437, 191, 74,  53, 472, 142},
    {91, 661, 228, 0, 383, 120,  77, 105, 175, 476, 324, 240,  27, 182, 239, 237,  84},
    {412, 227, 169, 383, 0, 267, 351, 309, 338, 196,  61, 421, 346, 243, 199, 528, 297},
    {150, 488, 112, 120, 267, 0,  63,  34, 264, 360, 208, 329,  83, 105, 123, 364,  35},
    {80, 572, 196,  77, 351,  63, 0, 29, 232, 444, 292, 297,  47, 150, 207, 332,  29},
    {134, 530, 154, 105, 309,  34,  29,   0, 249, 402, 250, 314,  68, 108, 165, 349,  36},
    {259, 555, 372, 175, 338, 264, 232, 249,   0, 495, 352,  95, 189, 326, 383, 202, 236},
    {505, 289, 262, 476, 196, 360, 444, 402, 495,   0, 154, 578, 439, 336, 240, 685, 390},
    {353, 282, 110, 324,  61, 208, 292, 250, 352, 154,   0, 435, 287, 184, 140, 542, 238},
    {324, 638, 437, 240, 421, 329, 297, 314,  95, 578, 435,   0, 254, 391, 448, 157, 301},
    {70, 567, 191,  27, 346,  83,  47,  68, 189, 439, 287, 254,   0, 145, 202, 289,  55},
    {211, 466,  74, 182, 243, 105, 150, 108, 326, 336, 184, 391, 145,   0,  57, 426,  96},
    {268, 420,  53, 239, 199, 123, 207, 165, 383, 240, 140, 448, 202,  57,   0, 483, 153},
    {246, 745, 472, 237, 528, 364, 332, 349, 202, 685, 542, 157, 289, 426, 483,   0, 336},
    {121, 518, 142,  84, 297,  35,  29,  36, 236, 390, 238, 301,  55,  96, 153, 336,   0}
};

*/

double coords[][2] = {
	{37, 52}, {49, 49}, {52, 64}, {20, 26}, {40, 30}, {21, 47},
	{17, 63}, {31, 62}, {52, 33}, {51, 21}, {42, 41}, {31, 32},
	{ 5, 25}, {12, 42}, {36, 16}, {52, 41}, {27, 23}, {17, 33},
	{13, 13}, {57, 58}, {62, 42}, {42, 57}, {16, 57}, { 8, 52},
	{ 7, 38}, {27, 68}, {30, 48}, {43, 67}, {58, 48}, {58, 27},
	{37, 69}, {38, 46}, {46, 10}, {61, 33}, {62, 63}, {63, 69},
	{32, 22}, {45, 35}, {59, 15}, { 5,  6}, {10, 17}, {21, 10},
	{ 5, 64}, {30, 15}, {39, 10}, {32, 39}, {25, 32}, {25, 55}, 
	{48, 28}, {56, 37}, {30, 40}
};

void calculate_city_distances (void);
double eval_tour (int *tour);
void adjust_pheremone (int *tour);
void evaporate_pheremone (void);

/*-----------------------------------------------------------------*/

/* Precalculate  matrix of city distances, using previously 
   supplied coordinates */

void calculate_city_distances(void)
{
	int i, j;
	
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			distance[i][j] = 0;
			distance[i][j] += (coords[i][X_VAL] - coords[j][X_VAL]) * 
				(coords[i][X_VAL] - coords[j][X_VAL]);
			distance[i][j] += (coords[i][Y_VAL] - coords[j][Y_VAL]) * 
				(coords[i][Y_VAL] - coords[j][Y_VAL]);
			distance[i][j] = sqrt(distance[i][j]);	
			distance[j][i] = distance[i][j];
		}
	}
}

/*-----------------------------------------------------------------*/

/* Using the matrix of city distances, calculate the length of an
   arbitrary tour */

double eval_tour (int *tour)
{
	int i, start, end;
	double d = 0;
	
	for (i=1; i<N; i++) {
		start = tour[i-1];
		end = tour[i];
		d += distance[start][end];	
	}

	d += distance[tour[N-1]][tour[0]];
	
	return d;
}

/*-----------------------------------------------------------------*/

/* Add pheremone to ant trails. The amount is inversely 
   proportional to the length of the tour, so shorter tours
   get more pheremone */

void adjust_pheremone (int *tour)
{
	int i;
	double d = eval_tour (tour);

	for (i=1; i<N; i++) {	
		tau[tour[i-1]][tour[i]] += (1/d);
		tau[tour[i]][tour[i-1]] += (1/d);
	}	
}

/*-----------------------------------------------------------------*/

/* Implement pheremone evaporation from all trails */

void evaporate_pheremone (void)
{
	int i, j;
	
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			tau[i][j] *= (1-RHO);
			tau[j][i] *= (1-RHO);
		}
	}
}

/*-----------------------------------------------------------------*/

int main()
{
	
	int tour[N], i, j, k, t, t1;
	double t_prob[N], strength[N+1], x, d;
	bool visited[N];
	int best_tour[N];
	double min_tour = 1000000;
	
	printf("\nWelcome to ACO");
	printf("\nLast compiled on %s, %s", __DATE__, __TIME__);
	printf("\n");

    randomize();
	
//	calculate_city_distances();
	
    /* Set up small, random amounts of pheremone to trails */
	for (i=0; i<N; i++)	{
		for (j=0; j<N; j++)
			tau[i][j] =  0.1 * rand() / (double)RAND_MAX;
	}
	
    /* Main loop starts here */
	for (t1=0; t1<N_GENERATIONS; t1++)
	{
		/* 1 ant for each city */
		for (t=0; t<N; t++)
		{					
			/* Initialise tour */
			for (i=0; i<N; i++) {
				visited[i] = false;
				tour[i] = -1;
			}
			
			/* Tour always starts at position 0 */
			tour[0] = 0;
			visited[0] = true;
			
			/* j marks where we are in constructing the tour, 
			   k is the next node to visit */
			for (j=1; j<N; j++) {

			/* Get transition probabilities - cannot choose a 
			   node that has previously been used */
				for (i=0; i<N; i++) {
					t_prob[i] = 0.0;
					if (visited[i] == false)											
						t_prob[i] = pow(tau[i][tour[j-1]], ALPHA) / 
							pow(distance[i][tour[j-1]], BETA);
					else
						t_prob[i] = 0.0;					
				}
				
				/* Roulette wheel selection - equivalent to probability-
			   	   based selection of next city. The index of the next 
				   city on the tour is given in k */
				strength[0] = 0;			
				for (i=0; i<N; i++)
					strength[i+1] = t_prob[i] + strength[i];

				long _rnd = rand();

				if (_rnd == 0)
					_rnd++;

				x = strength[N] * (double)_rnd / RAND_MAX;	
				
				k = 0;
				while (!((strength[k] <= x) && (x <= strength[k+1])))
					k++;
			

				tour[j] = k;				
				visited[k] = true;								
			}
					
			/* Save best tour so far */
			d = eval_tour(tour);
			if (d < min_tour)
			{
				min_tour = d;
				for (i=0; i<N; i++)
					best_tour[i] = tour[i];
			}

			adjust_pheremone (tour);		
		}
		
		evaporate_pheremone ();		

		printf("Shortest length found = %.2f\n", min_tour);
	}
	
	printf("\n");
	printf("Shortest tour found: \n");
	for (j=0; j<N; j++) 
		printf("%i|",best_tour[j]+1);
	printf("\n");
	printf("Length of shortest tour found: %.2f\n", eval_tour (best_tour));
	printf("This is %.2f%% longer than the best solution known\n", 
		100*((eval_tour(best_tour) / BEST_SOLUTION)-1));
	return 0;
						
}
