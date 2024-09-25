#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting {
  
  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);
  int Partition(vector<int>& arr, int p, int r);

  //************
  // MergeSort *
  //************
  void Merge(vector<int> &a, vector<int> &b,int low, int pivot, int high);
  void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

  //************************
  // Natuerliche Mergesort *
  //************************
  void natMerge(vector<int>& a, vector<int>& b, int low, int pivot, int high);
  void natMergeSort(vector<int> &a, vector<int> &b);

  //************
  // Heapsort  *
  //************
  void heapify(vector<int> &a, int n, int i);
  void HeapSort(vector<int> &a, int n);
  int leftChild(int const i);
  //************
  // Shellsort *
  //************
  void ShellSort_2n(vector<int> &a, int n);
  void ShellSort_3n(vector<int>& a, int n);


  //*******************
  // Helper functions *
  //*******************
  void randomizeVector(vector<int> &array, int n);
  

  //insertion sort
  void insertionSort(vector<int>& arr);
 }
#endif 
