#include "stdafx.h"

#include "Sorting Algorithms/BubbleSort/BubbleSort.h"
#include "Sorting Algorithms/InsertionSort/InsertionSort.h"
#include "Sorting Algorithms/QuickSort/QuickSort.h"
#include "Sorting Algorithms/MergeSort/MergeSort.h"
#include "Sorting Algorithms/HeapSort/HeapSort.h"

#include "BreadthFirst.h"

#include <chrono>

enum SORTING_ALGORITHMS {
	//* Simple
	BUBBLE_SORT,
	INSERTION_SORT,
	QUICK_SORT,

	//* Advanced
	MERGE_SORT,
	HEAP_SORT,
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
		case MERGE_SORT:
			MergeSort(arr, 0, size - 1);
			break;
		case HEAP_SORT:
			HeapSort(arr, size);
		}
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

//* Moved up here so that memory is initialized on the heap instead of the stack
std::array<int, MaxArrayCount> sortArray = {};
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(MinNumber, MaxNumber);

void SortingAlgorithms() {
	// Bubble Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);
		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, BUBBLE_SORT);

		PrintArray<int>(&sortArray[0], MaxArrayCount, "Bubble Sort: ", timeTaken);
	}

	// Insertion Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);

		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, INSERTION_SORT);
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Insertion Sort: ", timeTaken);
	}

	// Quick Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);

		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, QUICK_SORT);
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Quick Sort: ", timeTaken);
	}

	// Merge Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);

		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, MERGE_SORT);
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Merge Sort: ", timeTaken);
	}

	// Heap Sort
	{
		RandomizeArray<int>(&sortArray[0], MaxArrayCount, rng, dist);

		float timeTaken = RunSortingAlgorithm(&sortArray[0], MaxArrayCount, HEAP_SORT);
		PrintArray<int>(&sortArray[0], MaxArrayCount, "Heap Sort: ", timeTaken);
	}
}

void GetArrayFromFile(char* arr, std::string fileName) {
	std::ifstream file(fileName);
	if (file.is_open()) {
		std::string line;

		UINT i = 0;
		while (std::getline(file, line)) { // Fetch all char from file
			if (line.find_first_of("L") != std::string::npos) // exit if we get to a letter that is not on the graph
				break;

			for (UINT j = 0; j < line.size(); j++)
			{
				arr[i] = line[j];
				i++;
			}
		}

	}
	else
		std::cout << "Failed to open file! \n";

	file.close();
}

int main() {	
	SortingAlgorithms();

	BreadthFirst breadth;

	std::array<char, 400> charNodes;
	GetArrayFromFile(&charNodes[0], "Nodes.txt");
	const std::array<UINT, 2> startEnd = breadth.ConstrucGraph(&charNodes[0], 400);
	if(breadth.FindPath(startEnd[0], startEnd[1]))
		breadth.PrintPath(startEnd[0], startEnd[1]);

	return 0;
}

