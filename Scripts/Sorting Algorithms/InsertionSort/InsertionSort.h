#pragma once
#include <Windows.h>

template <typename T> void InsertionSort(T* arr, const UINT size) {
	T key;
	int j = 0;

	for (UINT i = 0; i < size; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}