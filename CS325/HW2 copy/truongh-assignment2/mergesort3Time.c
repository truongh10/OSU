#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void merge3(int * array, int start, int secondThirdStart, int lastThirdStart, int end) {
	int temp[end - start];	
	int k = 0;
	int a = start, b = secondThirdStart, c = lastThirdStart;
	// loop through the three thirds of array and
	// add smaller numbers to temp array
	//https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
	//I used this reference to find out the how to add the smallest
	//element to my temp array
	while (a < secondThirdStart && b < lastThirdStart && c < end) {
		if (array[a] < array[b]) {
			if (array[a] < array[c]) {
				temp[k] = array[a];
				a++;
			} else {
				temp[k] = array[c];
				c++;
			}
		}
		else {
			if (array[b] < array[c]) {
				temp[k] = array[b];
				b++;
			} else {
				temp[k] = array[c];
				c++;
			}
		} 
		k++;
/*		if (array[a] <= array[b] && array[a] <= array[c]) {
			temp[k] = array[a];
			a++;
		} else if (array[a] <= array[b] && array[a] > array[c]) {
			temp[k] = array[c];
			c++;
		} else if (array[b] <= array[a] && array[b] <= array[c]) {
			temp[k] = array[b];
			b++;
		} else if (array[b] <= array[a] && array[b] > array[c]) {
			temp[k] = array[c];
			c++;
		} else if (array[c] <= array[a] && array[c] <= array[b]) {
			temp[k] = array[c];
			c++;
		} else if (array[c] <= array[a] && array[c] > array[b]) {
			temp[k] = array[b];
			b++;
		}
		k++;*/
	}
	// first third and second third still have remaining elements
	while (a < secondThirdStart && b < lastThirdStart) {
		if (array[a] < array[b]) {
			temp[k] = array[a];
			a++;
		}
		else { 
			temp[k] = array[b];
			b++;
		}
		k++;
	}
	// first third and last third still have remaining elements
	while (a < secondThirdStart && c < end) {
                if (array[a] < array[c]) {
                        temp[k] = array[a];
			a++;
		}
                else {
			temp[k] = array[c];
			c++;
		}
		k++;
        }
	// second third and last third still have remaining elements
	while (b < lastThirdStart && c < end) {
                if (array[b] < array[c]) {
                        temp[k] = array[b];
			b++;
		}
                else {
			temp[k] = array[c];
			c++;
		}
		k++;
        }
	// add leftover numbers from first third to temp array
	while (a < secondThirdStart) {
		temp[k] = array[a];
		k++;
		a++;
	}
	// add leftover numbers from second third to temp array
	while (b < lastThirdStart) {
		temp[k] = array[b];
		k++;
		b++;
	}
	// add leftover numbers from last third to temp array
	while (c < end) {
		temp[k] = array[c];
		k++;
		c++;
	}
	//copy temp array to original array
	for (int i = start; i < end; i++) {
		array[i] = temp[i-start];
	}
	
}

// recursively split array into 3 parts and then merge them in increasing order
void mergeSort3(int* array, int start, int end) {
	if ((end-start)>=2) { // check if size of array is greater than 2
		int oneThird, twoThird;
		oneThird = start + ((end - start) / 3);
		if ((((end-start) / 3)%3) == 0) {
			twoThird = start+ (2*(end-start)/3); 
		} else {
			twoThird = start +(2*(end-start) / 3) +1;
		}

//		printf("\n hihihi \n");		

		mergeSort3(array, start, oneThird);
		mergeSort3(array,oneThird, twoThird);
		mergeSort3(array, twoThird, end);
		merge3(array, start, oneThird, twoThird, end);
	}
}


//https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
// I use this reference to find the time it takes for my mergeSort3 to run
int main() {
	srand(time(NULL));
	
	for (long int i = 100000; i <= 1000000; i += 100000) {
		int array[i];
		for (long int j = 0; j < i; j++) {
			array[j] = rand() % 10000 + 1;
		}
		clock_t t;
		t = clock();
		mergeSort3(array, 0, i);
		t = clock() - t;
		double time_taken = ((double)t)/CLOCKS_PER_SEC;
		printf("size = %d, time = %f\n", i, time_taken);
	}

	return 0;	
}









































