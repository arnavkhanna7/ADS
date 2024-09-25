#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>
#include <chrono>
#include "sorting.h"

using namespace std;

//benchmark functions
void benchmark_quicksort();
void benchmark_mergesort();
void benchmark_heapsort();
void benchmark_shellsort_2n();

void benchmark_insertionsort();
void benchmark_quicksort2();

int main(int argc, char** argv) {

  Catch::Session().run();

  std::cout << "\nPress Enter to run measurement" << std::endl;
  std::cin.get();

  benchmark_quicksort();
  benchmark_mergesort();
  benchmark_heapsort();
  benchmark_shellsort_2n();
  
//   benchmark_insertionsort();
//   benchmark_quicksort2();
  
  system("pause");
  return 0;
}


//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime; 
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    //dtime = omp_get_wtime();
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    
	//execzute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto dtime = chrono::duration<double>(end - begin).count();
    //dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

void benchmark_mergesort()
{
	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	//double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;
	vector<int> temp_array;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Mergesort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		//dtime = omp_get_wtime();
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

		//execzute sorting algorithm
		temp_array.resize(V.size());
		sorting::MergeSort(V, temp_array, 0, V.size() - 1);

		//stop time
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    	auto dtime = chrono::duration<double>(end - begin).count();
		//dtime = omp_get_wtime() - dtime;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	mergesort_measurement.close();


}

void benchmark_heapsort()
{
	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	//double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Heapsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		//dtime = omp_get_wtime();
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

		//execute sorting algorithm
		sorting::HeapSort(V, V.size());

		//stop time
		//dtime = omp_get_wtime() - dtime;
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    	auto dtime = chrono::duration<double>(end - begin).count();
		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	heapsort_measurement.close();


}

void benchmark_shellsort_2n()
{
	//file stream
	ofstream shellsort_measurement;
	shellsort_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	//double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Shellsort_2n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		//dtime = omp_get_wtime();
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

		//execute sorting algorithm
		sorting::ShellSort_2n(V, V.size());

		//stop time
		//dtime = omp_get_wtime() - dtime;
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    	auto dtime = chrono::duration<double>(end - begin).count();

		//write to file
		shellsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_measurement.close();
}





void benchmark_quicksort2() {
	 // File stream
    ofstream quicksort_measurement;
    quicksort_measurement.open("quicksort2.txt", ios::out | ios::app);

    // Benchmark parameters / variables
    int n_start = 1;
    int n_step = 1;
    int n_end = 500;

    vector<int> V;

    // Actual benchmark loop
    for (int n = n_start; n <= n_end; n += n_step) {
        // "Progress bar"
        cout << "Running Quicksort with n: " << n << endl;

        // Generate n random integers
        sorting::randomizeVector(V, n);

        // Measure multiple times and average
        const int repetitions = 1000;
        double total_time = 0.0;

        for (int i = 0; i < repetitions; ++i) {
            vector<int> temp = V; // Kopieren Sie das Originalarray

            // Start measurement
            auto start = chrono::high_resolution_clock::now();

            // Execute sorting algorithm
            sorting::QuickSort(temp,0,V.size()-1);

            // Stop time
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();            
            auto duration = chrono::duration<double>(end - start).count();
            total_time += duration;
        }

        // Average time
        double avg_time = total_time / 1000.0;

        // Write to file
        quicksort_measurement << n << "\t" << setprecision(10) << scientific << avg_time << endl;
    }

    // Close file handle
    quicksort_measurement.close();
}



void benchmark_insertionsort(){
	 // File stream
    ofstream insertionsort_measurement;
    insertionsort_measurement.open("insertionsort2.txt", ios::out | ios::app);

    // Benchmark parameters / variables
    int n_start = 1;
    int n_step = 1;
    int n_end = 500;

    vector<int> V;

    // Actual benchmark loop
    for (int n = n_start; n <= n_end; n += n_step) {
        // "Progress bar"
        cout << "Running Insertionsort with n: " << n << endl;

        // Generate n random integers
        sorting::randomizeVector(V, n);

        // Measure multiple times and average
        const int repetitions = 1000;
        double total_time = 0.0;

        for (int i = 0; i < repetitions; ++i) {
            vector<int> temp = V; // Kopieren Sie das Originalarray

            // Start measurement
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            // Execute sorting algorithm
            sorting::insertionSort(temp);

            // Stop time
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double>(end - start).count();
            total_time += duration;
        }

        // Average time
        double avg_time = total_time / 1000.0;

        // Write to file
        insertionsort_measurement << n << "\t" << setprecision(10) << scientific << avg_time << endl;
    }

    // Close file handle
    insertionsort_measurement.close();
}