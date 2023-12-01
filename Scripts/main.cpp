#include "stdafx.h"

#include "Sorting Algorithms/BubbleSort/BubbleSort.h"
#include "Sorting Algorithms/InsertionSort/InsertionSort.h"
#include "Sorting Algorithms/QuickSort/QuickSort.h"
#include "Sorting Algorithms/MergeSort/MergeSort.h"
#include "Sorting Algorithms/HeapSort/HeapSort.h"

#include "BreadthFirst.h"
#include "DepthFirst.h"
#include "Astar.h"

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
	std::cout << "Sorting Algorithms Start: \n \n";
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
	std::cout << "Sorting Algorithms End: \n \n";
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

	std::cout << "Graph Search Algorithms Start: \n \n";
	std::array<char, 400> charNodes;
	GetArrayFromFile(&charNodes[0], "Nodes.txt");

	UINT start = 0;
	UINT end   = 0;

	// Breadth First Search
	{
		BreadthFirst breadth;
		ConstructGraph(&charNodes[0], start, end, breadth.GetGraph());
		if(breadth.FindPath(start, end))
		   DrawPath(breadth.GetGraph(), start, end);

		std::cout << "\n";
	}

	// Depth First Search
	{
		DepthFirst depth;
		ConstructGraph(&charNodes[0], start, end, depth.GetGraph());;
		if (depth.FindPath(start, end))
			DrawPath(depth.GetGraph(), start, end);	
	}

	std::cout << "\n";

	// Astar search
	{
		Astar astar;
		ConstructGraph(&charNodes[0], start, end, astar.GetGraph());
		if (astar.FindPath(start, end))
			DrawPath(astar.GetGraph(), start, end);	
	}

	std::cout << "Graph Search Algorithms End: \n \n";

	return 0;
}

