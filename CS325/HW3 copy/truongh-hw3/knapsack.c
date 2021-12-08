#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// this function compares 2 numbers and returns a bigger one
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

// Knapsack using recursive algorithm
int recursiveAlgo(int W, int w[], int v[], int n) {
	// Base Case
	if (n == 0 || W == 0)	// in case there is no items or no capacity in knapsack
		return 0;
	if (w[n] > W)	// weight of item at index n is greater than capacity
		return recursiveAlgo(W,w,v,n-1);	// call itself with size n-1
	else	// weight of item at index n < capacity
		// return the max value in knapsack
		return max(v[n] + recursiveAlgo(W-w[n], w, v, n-1), recursiveAlgo(W, w, v, n-1));
}

// Knapsack using DP algorithm
int DPalgo(int n, int wt[], int v[], int W) {
	int V[n+1][W+1];
	// initialize the first row to 0
	for (int w = 0; w <= W; w++)	// for each column
		V[0][w] = 0;	// initialize the first row of column i to 0

		

	for (int i = 1; i <= n; i++) {	// for each row staring from
		V[i][0] = 0;	// initialize the first column of row i to 0


		for (int w = 1; w <= W; w++) {
			if (wt[i] <= w) {	// item can be part of solution
				if ((v[i] + V[i-1][w-wt[i]]) > V[i-1][w])
					V[i][w] = v[i] + V[i-1][w-wt[i]];
				else V[i][w] = V[i-1][w];
			}
			else V[i][w] = V[i-1][w];	// w[i] > w item i is too big
		}
	}
	return V[n][W];
}


int main() {
	srand(time(NULL));	// gives different seed at every execution
	int weight;	// holds generated weight from 1 to 20
	int value;	// holds generated value from 1 to 1000
	int W = 100;	// weight capacity of knapsack
	int recMax;	// holds maximum value in knapsack
	int dpMax;
	for (int i = 20; i <= 41 ; i = i+3) {	
		int wt[i], v[i];	// array for weights and array for values
		for (int j = 0; j < i; j++) {	// loop through both arrays
			weight = (rand() % 20) + 1;	// generates random number from 1 to 20
			value = (rand() % 1000) + 1; 	// generates random number from 1 to 1000
			wt[j] = weight;	// initializes w array at j to weight
			v[j] = value;	// initializes v array at j to weight
		}
		// Measuring running time for recursiveAlgo
		clock_t t;
                t = clock();
		recMax = recursiveAlgo(W, wt, v, i);
                t = clock() - t;
                double recTime = ((double)t)/(CLOCKS_PER_SEC/1000);

		// Measuring running time for DPalgo
		clock_t t2;
                t2 = clock();
		dpMax = DPalgo(i,wt,v,W);
                t2 = clock() - t2;
                double dpTime = ((double)t2)/(CLOCKS_PER_SEC/1000);
		
		printf("\nN = %d, W = %d, Rec time = %f, DP time = %f, max Rec = %d, max DP = %d\n", i, W, recTime, dpTime, recMax, dpMax);		
	}

	printf("\n\nMeasuring running time for DPalgo...\n");
	W = 500;
	for (int i = 1000; i <= 4000 ; i = i+500) {	
		int wt[i], v[i];	// array for weights and array for values
		for (int j = 0; j < i; j++) {	// loop through both arrays
			weight = (rand() % 20) + 1;	// generates random number from 1 to 20
			value = (rand() % 1000) + 1; 	// generates random number from 1 to 1000
			wt[j] = weight;	// initializes w array at j to weight
			v[j] = value;	// initializes v array at j to weight
		}
		// Measuring running time for recursiveAlgo
		clock_t t3;
                t3 = clock();
		long d = DPalgo(W, wt, v, i);
                t3 = clock() - t3;
                double DPTime = ((double)t3)/(CLOCKS_PER_SEC/1000);
		printf("\nN = %d, W = %d, DP time = %f\n", i, W, DPTime);	
	}
	return 0;
}



































