#include "stdafx.h"

#include "BubbleSort/BubbleSort.h"
#include "InsertionSort/InsertionSort.h"
#include "QuickSort/QuickSort.h"

#include <iomanip>
#include <chrono>

const UINT MaxArrayCount = 1000;
const UINT NumberOfTests = 1;

const int MinNumber = 0;
const int MaxNumber = 100;

enum SORTING_ALGORITHMS {
	BUBBLE_SORT,
	INSERTION_SORT,
	QUICK_SORT,
};

template <typename T> float RunSortingAlgorithm(T* arr, const UINT size, SORTING_ALGORITHMS algorithm) {	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (UINT i = 0; i < NumberOfTests; i++)
	{
		switch (algorithm)
		{
		case BUBBLE_SORT:
			BubbleSort(arr, size);
			break;
		case INSERTION_SORT:
			InsertionSort(arr, size);
			break;
		case QUICK_SORT:
			QuickSort(arr, size, 0, size - 1);
			break;
		default:
			break;
		}
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

int main() {	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(MinNumber, MaxNumber);
	
	std::array<int, MaxArrayCount> sortArray = {};

	// Bubble Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);
		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, BUBBLE_SORT);

		std::cout << "\n \n";
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Bubble Sort: ");
		std::cout << "------------------------------------------------------------------------------------------------ \n";
		std::cout << "Time taken: " << std::fixed << std::setprecision(5) << timeTaken << "ms \n";
	}

	std::cout << "\n";

	// Insertion Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);
		
		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, INSERTION_SORT);
		std::cout << "\n \n";
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Insertion Sort: ");
		std::cout << "------------------------------------------------------------------------------------------------ \n";
		std::cout << "Time taken: " << std::fixed << std::setprecision(5) << timeTaken << "ms \n";
	}

	// Quick Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);

		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, QUICK_SORT);
		std::cout << "\n \n";
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Quick Sort: ");
		std::cout << "------------------------------------------------------------------------------------------------ \n";
		std::cout << "Time taken: " << std::fixed << std::setprecision(5) << timeTaken << "ms \n";
	}

	return 0;
}

