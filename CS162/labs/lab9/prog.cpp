#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

int ask_for_size(int input) {
	cout << "===========================" << endl;
	cout << "Enter size of array: ";
	cin >> input;
	while (input < 0 || input > 21) {
		cout << "invalid input. Enter again: ";
		cin >> input;
	}
	return input;
}

void merge(int *arr, int l, int m, int r) {
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;

	int L[n1], R[n2];

	for (i=0; i<n1; i++)
		L[i] = arr[l+i];
	for (j=0; j<n2; j++)
		R[j] = arr[m+1+j];

	i=0;
	j=0;
	k=l;
	
	while(i < n1 && j < n2) {
		if(L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	
	while(i<n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j<n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort (int *arr, int l, int r) {
	if (l < r) {
		int m = l+(r-l)/2;
		//cout << l << " " << m << " " << r << endl;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr,l,m,r);
	}
}





int main() {
	srand(time(NULL));
	int size = ask_for_size(size);
	int *array;
	array = new int[size];

	for (int i = 0; i < size; i++) {
		array[i] = rand()%50 + 1;
	}

	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << "\n=============================" << endl;

	mergeSort(array, 0, size-1);
	for (int i = 0; i < size; i++) {
                cout << array[i] << " ";
        }
	cout << endl;


	delete [] array;
	return 0;
}
