#pragma once

template<typename T> int Partition(T* arr, const int low, const int high) {
	T pivot = arr[high];
	int i = (low - 1);

	for (int j  = low; j <= high; j++)
	{
		if (arr[j] < pivot) {
			i++;

			const T value = arr[i];
			arr[i] = arr[j];
			arr[j] = value;
		}
	}

	const T value = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high]  = value;

	return (i + 1);
}

template <typename T> void QuickSort(T* arr, const UINT size, const int low, const int high) {
	if (low < high) {
		int pi = Partition(arr, low, high);

		QuickSort(arr, size, low, pi - 1);
		QuickSort(arr, size, pi + 1, high);
	}
}