#pragma once

template <typename T> void Heapify(T* arr, const UINT size, const UINT index) {
	UINT largest = index;

	int l = 2 * index + 1;

	int r = 2 * index + 2;

	if (l < size && arr[l] > arr[largest])
		largest = l;

	if (r < size && arr[r] > arr[largest])
		largest = r;

	if (largest != index) {
		const T value = arr[index];
		arr[index] = arr[largest];
		arr[largest] = value;

		Heapify(arr, size, largest);
	}
	
}

template <typename T> void HeapSort(T* arr, const UINT size) {
	for (int i = (size / 2) - 1; i >= 0; i--) {
		Heapify(arr, size, i);
	}

	for (int i = size - 1; i > 0; i--)
	{
		const T value = arr[0];
		arr[0] = arr[i];
		arr[i] = value;

		Heapify(arr, i, 0);
	}
	
}