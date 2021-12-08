#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Knapsack using DP algorithm
int DPalgo(int n, int wt[], int v[], int W, int item[]) {
	int V[n+1][W+1];
//	int itemNum = 0;

	// initialize the first row to 0
	for (int w = 0; w <= W; w++)	// for each column
		V[0][w] = 0;	// initialize the first row of column i to 0

		

	for (int i = 1; i <= n; i++) {	// for each row staring from
		V[i][0] = 0;	// initialize the first column of row i to 0


		for (int w = 1; w <= W; w++) {
			if (wt[i-1] <= w) {	// item can be part of solution
				if ((v[i-1] + V[i-1][w-wt[i-1]]) > V[i-1][w])
					V[i][w] = v[i-1] + V[i-1][w-wt[i-1]];
				else V[i][w] = V[i-1][w];
			}
			else V[i][w] = V[i-1][w];	// w[i] > w item i is too big
		}
	}

	// https://www.tutorialspoint.com/printing-items-in-0-1-knapsack-in-cplusplus
	// I referred to this website to store the chosen items in an array
	int res = V[n][W];
	int w = W;
	int k = 0;
	for (int i = n; i > 0 && res > 0; i--) {
		if (res == V[i-1][w])
			continue;
		else {
			item[k++] = i;
			res = res - v[i-1];
			w = w - wt[i-1];
		}
	}
//	printf("\n\n=====================Items==================\n");
//			for (int m = 0; m < n; m++) {
//				printf("%d ", item[m]);
//			}	
//	printf("\n=============================================\n\n");		
/*	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= W; j++) {
			printf("%d ", V[i][j]);
		}
		printf("\n");
	}

	printf("\n=====================\n");*/
	return V[n][W];
}









int main () {

	int T = 0;	// stores the number of test cases

	// open data.txt file
	FILE *dataFile = fopen("shopping.txt", "r");
	// first line is number of test cases
	fscanf(dataFile, "%d", &T);

//		printf("T = %d\n", T);
	for (int t = 0; t < T; t++) {	
		int N = 0;	// stores number of items
		int M = 0;	// stores the maximum weight a person can carry
		int F = 0;	// stores numbers of people in a family
		int maxPrice = 0;	// stores max value each person can achieve	
		// next line the the number of items
		fscanf(dataFile, "%d", &N);
		int p[N];	// stores price for each item
		int wt[N];	// stores weight of each item
		int item[N];	// stores items each person can carry, assuming one can't carry more than N items

		//read and store price and weight of each item into arrays
		for (int i = 0; i < N; i++) {
			int tmp;
			fscanf(dataFile, "%d", &tmp);
			p[i] = tmp;
			fscanf(dataFile, "%d", &tmp);
			wt[i] = tmp;
		}

		// read number of people in the family
		fscanf(dataFile, "%d", &F);

		int itemsPerPerson[F][N];
		// initialize array
		for (int k = 0; k < F; k++) {
			for (int m = 0; m < N; m++) {
				itemsPerPerson[k][m] = 0;
			}
		}
		printf("Test Case %d\n", t+1);	
		// read maximum weight each person can carry
		for (int k = 0; k < F; k++) {
			//initialize item array to 0
			for (int m = 0; m < N; m++) {
				item[m] = 0;
			}			

			int n = 0;
			fscanf(dataFile, "%d", &M);	// stores max weight a person can carry in M
			int temp = DPalgo(N,wt,p,M,item);	// call DPalgo and store max value in temp
			// store chosen items into itemsPerPerson array
			for (int t = (int)sizeof(item)/sizeof(item[0])-1; t >= 0; t--) {
				itemsPerPerson[k][n++] = item[t];
			}
			maxPrice += temp;	// sum up the maximum value each person can achieve
		}
		printf("Total Price %d\n", maxPrice);
		printf("Member Items\n");
		// print the chosen items
		for (int k = 0; k < F; k++) {	
			printf("%d: ", k+1);
			for (int t = 0; t < N; t++) {
				if (itemsPerPerson[k][t] != 0)
					printf("%d ",itemsPerPerson[k][t]);
			}
			printf("\n");
		}	
		printf("\n");	
	}
	fclose(dataFile);
	return 0;
}


















