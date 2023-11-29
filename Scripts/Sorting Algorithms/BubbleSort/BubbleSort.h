#pragma once
#include <iostream>
#include <Windows.h>

// * Simple sorting algorithm
template <typename T> void BubbleSort(T* arr, UINT size) {
	UINT n = size;

	for (UINT i = 0; i < n - 1; i++)
	{
		for (UINT j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1]) {
				const T value = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = value;
			}	
		}
	}
}


