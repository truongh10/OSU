#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int activityNum = 0;

typedef struct Activity {
	int index;
	int begin;
	int end;
}Activity;

void merge3(Activity * array, int start, int secondThirdStart, int lastThirdStart, int end) {
	Activity temp[end - start];	
	int k = 0;
	int a = start, b = secondThirdStart, c = lastThirdStart;
	// loop through the three thirds of array and
	// add smaller numbers to temp array
	while (a < secondThirdStart && b < lastThirdStart && c < end) {
		if (array[a].end < array[b].end) {
			if (array[a].end < array[c].end) {
				temp[k] = array[a];
				a++;
			} else {
				temp[k] = array[c];
				c++;
			}
		}
		else {
			if (array[b].end < array[c].end) {
				temp[k] = array[b];
				b++;
			} else {
				temp[k] = array[c];
				c++;
			}
		} 
		k++;
	}
	// first third and second third still have remaining elements
	while (a < secondThirdStart && b < lastThirdStart) {
		if (array[a].end < array[b].end) {
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
                if (array[a].end < array[c].end) {
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
                if (array[b].end < array[c].end) {
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
void mergeSort3(Activity* array, int start, int end) {
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

void lastToFirst(Activity activity[], Activity selectedAct[], int start, int n) {
	mergeSort3(activity, start, n);

//	for (int k = 0; k < n; k++) {
//		printf("%d ", activity[k].index);
//	}
	printf("Activities: ");

	

	int i = 0;
	selectedAct[0] = activity[0];
	printf("%d", selectedAct[0]);
	activityNum++;
	for (int j = 1; j < n; j++) {
		if (activity[j].begin >= activity[i].end) {
			selectedAct[j] = activity[j];
			printf(" %d", selectedAct[j].index);
			activityNum++;
			i = j;
		}
	}
	printf("\n");


}


int main() {
	// open act.txt file
	FILE *dataFile = fopen("act.txt", "r");
	int temp;
	int actNum;	// number of activities

	int a = 0;

	//read the file number by number
	while (fscanf(dataFile, "%d", &temp) != EOF) {
		actNum = temp;	// store number of activites



		Activity act[actNum];	// create act array with size actNum
		Activity selectedAct[actNum];

		for (int i = 0; i < actNum; i ++) {
			fscanf(dataFile, "%d", &temp);
			act[i].index = temp;
			fscanf(dataFile, "%d", &temp);
			act[i].begin = temp;
			fscanf(dataFile, "%d", &temp);
			act[i].end = temp;
		}
//		for (int j = 0; j < actNum; j++) {
//			printf("%d %d %d\n", act[j].index,act[j].begin,act[j].end);
//		}
		printf("Set %d\n", ++a);

		lastToFirst(act,selectedAct, 0, actNum);
		printf("Number of activities selected = %d\n", activityNum);	

		activityNum = 0;
	}
//	for (int j = 0; j < activityNum; i++) {
//		printf ()
//	}

	fclose(dataFile);
	return 0;
}







































