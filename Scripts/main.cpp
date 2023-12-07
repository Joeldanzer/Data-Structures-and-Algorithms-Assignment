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

enum SEARCH_ALGORITHMS {
	BREADTH_SEARCH,
	DEPTH_SEARCH,
	ASTAR
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
	return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}

std::array<Graph*, 3> graphs; //Needs to be pointers since it's an abstract class

float RunSearchAlgorithms(char* arr, SEARCH_ALGORITHMS algorithm) {	
	if (!graphs[algorithm]) {
		switch (algorithm)
		{
		case BREADTH_SEARCH:
			graphs[algorithm] = new BreadthFirst();
			break;
		case DEPTH_SEARCH:
			graphs[algorithm] = new DepthFirst();
			break;
		case ASTAR:
			graphs[algorithm] = new Astar();
			break;
		}
	}
	
	UINT startNode = 0;
	UINT endNode   = 0;

	ConstructGraph(arr, startNode, endNode, graphs[algorithm]->GetGraph());	
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	bool found = graphs[algorithm]->FindPath(startNode, endNode);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	if (found)
		DrawPath(graphs[algorithm]->GetGraph(), startNode, endNode);

	return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
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
		std::cout << "Breadth Search: \n";
		float duration = RunSearchAlgorithms(&charNodes[0], BREADTH_SEARCH);
		std::cout << "Time taken for search: " << duration << "ms \n";
	}
	std::cout << "\n";

	// Depth First Search
	{
		std::cout << "Deoth Search: \n";
		float duration = RunSearchAlgorithms(&charNodes[0], DEPTH_SEARCH);
		std::cout << "Time taken for search: " << duration << "ms \n";
	}

	std::cout << "\n";

	// Astar search
	{
		std::cout << "Astar Search: \n";
		float duration = RunSearchAlgorithms(&charNodes[0], ASTAR);
		std::cout << "Time taken for search: " << duration << "ms \n";
	}

	std::cout << "Graph Search Algorithms End: \n \n";

	return 0;
}

