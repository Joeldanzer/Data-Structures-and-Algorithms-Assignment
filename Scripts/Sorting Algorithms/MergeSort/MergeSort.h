#pragma once
#include <Windows.h>

template <typename T> void Merge(T* arr, const int left, const int mid, const int right) {
	int const arrayOne = mid - left + 1;
	int const arrayTwo = right - mid;

	T* leftArray  = new T[arrayOne];
	T* rightArray = new T[arrayTwo];
	//memcpy(leftArray, &arr[left], sizeof(T) * arrayOne); // Trying out if memcpy is a faster solution, probably isnt as we do multiple copies constantly in small chunks	
	//memcpy(rightArray, &arr[mid + 1], sizeof(T) * arrayTwo);

	//* Do this instead of memcpy if you dont understand it or is a faster option
	for (int i = 0; i < arrayOne; i++)
		leftArray[i] = arr[left + i];
	for (int i = 0; i < arrayTwo; i++)
		rightArray[i] = arr[mid + 1 + i];

	UINT indexArrayOne = 0;
	UINT indexArrayTwo = 0;
	UINT indexMergedArray = left;

	while(indexArrayOne < arrayOne && indexArrayTwo < arrayTwo){
		if (leftArray[indexArrayOne] <= rightArray[indexArrayTwo]) {
			arr[indexMergedArray] = leftArray[indexArrayOne];
			indexArrayOne++;
		}
		else {
			arr[indexMergedArray] = rightArray[indexArrayTwo];
			indexArrayTwo++;
		}

		indexMergedArray++;
	}
	
	while (indexArrayOne < arrayOne) {
		arr[indexMergedArray] = leftArray[indexArrayOne];
		indexArrayOne++;
		indexMergedArray++;
	}
	
	while (indexArrayTwo < arrayTwo) {
		arr[indexMergedArray] = rightArray[indexArrayTwo];
		indexArrayTwo++;
		indexMergedArray++;
	}

	// Delete the array of pointers
	delete[] rightArray; 
	delete[] leftArray;
}

template <typename T> void MergeSort(T* arr, const int begin, const int end) {
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	MergeSort(arr, begin, mid);
	MergeSort(arr, mid + 1, end);
	Merge(arr, begin, mid, end);
}