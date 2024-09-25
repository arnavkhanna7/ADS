#include "sorting.h"
#include <cmath>



namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort(vector<int>& arr, int left, int right)
	{
		if (left < right) {						//mindestens 2 elemente zu sortieren
			int q = Partition(arr, left, right);//Pivot
			QuickSort(arr, left, q - 1);
			QuickSort(arr, q + 1, right);
		}
	}

	int Partition(vector<int>& arr, int p, int r) {
		int x = arr[r];							//last number as pivot
		int i = p - 1;							//i is 1 less than 1st element	
		for (int j = p; j < r; j++) {			
			if (arr[j] <= x) {
				i++;							//increment i and swap j and i 
				swap(arr[j], arr[i]);			
			}
		}
		swap(arr[i + 1], arr[r]);				//finally, send pivot elmt to i+1 pos.

		return i + 1;							//return position of pivot element
	}


	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int leftEnd = pivot - 1, tmpPos = low , rightEnd = high;
		int n = high - low + 1;					//anzahl der elemente
		int leftPos = low, rightPos = pivot;

		while (leftPos <= leftEnd && rightPos <= rightEnd) {
			if (a[leftPos] <= a[rightPos]) {			//compare left and right subarrays 
				b[tmpPos] = a[leftPos];					//save element in b[tmpPos]
				leftPos++;
			}
			else {
				b[tmpPos] = a[rightPos];
				rightPos++;
			}
			tmpPos++;
		}
		while (leftPos <= leftEnd) {			//copy remainng elements
			b[tmpPos] = a[leftPos];
			tmpPos++;
			leftPos++;
		}
		while (rightPos <= rightEnd) {			//copy remaining elements 
			b[tmpPos] = a[rightPos];
			rightPos++;
			tmpPos++;
		}

		int i = 0;								//copy array B to array A
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}


	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if (low < high) {
			size_t m = size_t(floor((low+high)/2));				//assign middle elmt
			MergeSort(a, b, low, m);							
			MergeSort(a, b, m + 1, high);
			Merge(a, b, low, m + 1, high);
		}
	}

	void natMerge(vector<int> &a, vector<int> &b, int left, int middle, int right) 
	{
		int leftEnd = middle - 1, tmpPos = left, n = right - left + 1;
		int leftPos = left, rightPos = middle, rightEnd = right;
		while (leftPos <= leftEnd && rightPos <= rightEnd) {
			if (a[leftPos] <= a[rightPos]) {
				b[tmpPos] = a[leftPos];
				leftPos++;
			}
			else {
				b[tmpPos] = a[rightPos];
				rightPos++;
			}
			tmpPos++;
		}
		while (leftPos <= leftEnd) {
			b[tmpPos] = a[leftPos];
			tmpPos++;
			leftPos++;
		}
		while (rightPos <= rightEnd) {
			b[tmpPos] = a[rightPos];
			rightPos++;
			tmpPos++;
		}
		int i = 0;
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}

	void natMergeSort(vector<int> &a, vector<int> &b)
	{
		int run = 0;
		vector<int> end(a.size() + 1);

		for (int i = 1; i <= a.size(); i++) {
			if (i == a.size()) {
				run++;
				end[run] = i;
			}
			else if (a[i] < a[i - 1]) {			//Startpunkt einer bereits sortierten Teilfolge
				run++;
				end[run] = i;
			}
		}
		while (run > 1) {
			int newrun = 0;						//counter for newruns after mixing 
			for (int i = 0; i < run; i += 2) {		//take 2 runs at a time
				natMerge(a, b, end[i], end[i + 1], end[i + 2] - 1);			//merge the 2 subarrays(runs)
				end[newrun] = end[i];				 //start von gemischten runs ist gespeichert
				newrun++;							
			}
			end[newrun] = end[run];				//endposition of last mixed runs saved in vector
			run = newrun;						//anzahl der euns aktualisiert
			
		}
	}


	//************
	// Heapsort  *
	//************
	void heapify(vector<int> &a, int n, int i)
	{
		int child = i;
		int tmp = a[i];
		for (tmp = a[i]; leftChild(i) < n; i = child) {				//initialise tmp as i, and i as child
			child = leftChild(i);									//calculate child of i
			if (child != n - 1 && a[child] < a[child + 1]) {		//if left child smaller than right child
				child++;											//go to next child
			}
			if (tmp < a[child]) {									//if value to heapify is smaller than child
				a[i] = a[child];									//percolate the child upwards(maxheap)
			}
			else
				break;
		}
		a[i] = tmp;													//
	}

	int leftChild(int const i) {
		return 2 * i + 1;
	}

	void HeapSort(vector<int> &a, int n) 
	{
		for (int i = a.size() / 2; i >= 0; i--) {
			heapify(a, a.size(), i);							//start heapify from middle of array
		}
		for (int i = a.size() - 1; i > 0; i--) {				//decrement i
			swap(a[0], a[i]);									//swap root node(largest) with last node(smallest)
			heapify(a, i, 0);									//heapify again starting from 0 for array[0..n-1]
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	void ShellSort_2n(vector<int>& a, int n)
	{
		int h = 1;
		while (2 * h + 1 < n) //max hibbardabstand finden
		{
			h = 2 * h + 1; // hibbard folge(1,3,7,9)
		}
		while (h > 0)
		{
			int i = h;
			while (i < n)
			{
				int tmp = a[i];
				int j = i;
				while (j >= h &&  a[j - h] > tmp) //vergleich von tmp und zahl davor in array(mit folge) 
				{
					a[j] = a[j - h];
					j = j - h; //abstand zurück
				}
				a[j] = tmp;
				i = i + 1;
			}
			h = (h - 1) * 0.5; //nachst kleiner abstand bestimmen
		}
	}

	void ShellSort_3n(vector<int>& a, int n)
	{	
		double drittel = 1.0 / 3.0;
		int h = 1;
		while (3 * h + 1 < n)
		{
			h = 3 * h + 1; // maximale abstand finden
		}
		while (h > 0)
		{
			int i = h;
			while (i < n)
			{
				int tmp = a[i]; 	//save current element in tmp	
				int j = i;			//initialise j = i
				while (j >= h && tmp < a[j - h])		//compare tmp with element at j-h(according to sequence)
				{				
					a[j] = a[j - h];				//if tmp smaller, move it to j-h position
					j = j - h;						//redefine j = j-h to move iterator to currently changed elmt.
				}
				a[j] = tmp;						//after loop ends save tmp in a[j]
				i = i + 1;						//increase i and repeat the loop till n
			}
			h = (h - 1) * drittel;				//find new value of h and repeat the process
		}
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }



//insertion sort

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Verschiebe die Elemente von arr[0..i-1], die größer als key sind,
        // um eine Position nach rechts, um Platz für das Schlüssel-Element zu schaffen
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

}





