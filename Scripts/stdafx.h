// Precompiled header
#pragma once

#define PRINT_RANDOM_ARRAY 0 // 0 to disable random output to console, 1 to outout random to console
#define PRINT_ARRAY_RESULT 0 // 0 to disable result output to console, 1 to output results to console

#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <random>
#include <array>
#include <vector>

#include <fstream>
#include <sstream>

const UINT MaxArrayCount = 10000;
const UINT NumberOfTests = 1;

const UINT GraphWidth  = 20;
const UINT GraphHeight = 20;

const int MinNumber = 0;
const int MaxNumber = 100;

const UINT MaxRowPrintCount = 20; // How many roes each list will print

//* Sorting Algorithms helper functions
template <typename T> void PrintArray(T* arr, const UINT size, std::string arrType, float duration) {
	std::cout << arrType << "\n";

#if PRINT_ARRAY_RESULT
	int newRow = 1;
	for (UINT i = 0; i < size; i++) {	
		std::cout << " " << static_cast<int>(arr[i]) << " ";
		if (newRow == MaxRowCount) {
			printf("\n");
			newRow = 0;
		}

		newRow++;
	}	
#endif
	std::cout << "------------------------------------------------------------------------------------------------ \n";
	std::cout << "Time taken: " << std::fixed << std::setprecision(3) << duration << "ms with Size " << MaxArrayCount << " & " << NumberOfTests << " Number of tests \n \n \n";
	
}

template <typename T> void RandomizeArray(T* arr, const UINT size, std::mt19937& rng, std::uniform_int_distribution<std::mt19937::result_type>& dist) {	
#if PRINT_RANDOM_ARRAY
	int newRow = 0;
#endif

	for (UINT i = 0; i < size; i++) {
		arr[i] = dist(rng);	
#if PRINT_RANDOM_ARRAY
		std::cout << " " << static_cast<int>(arr[i]) << " ";
		if (newRow == MaxRowCount) {
			printf("\n");
			newRow = 0;
		}
		newRow++;
#endif 
	}
}

//* Graph helper functions
struct Node {
	UINT m_x = 0;
	UINT m_y = 0;

	std::vector<UINT> m_neighbours;

	int  m_parent = -1;
	int  m_valid = -1;
	bool m_checked = false;

	// Used specifically for Astar
	float m_f = FLT_MAX; 
	float m_g = FLT_MAX; 
};

inline void DrawPath(const std::vector<Node>& nodes, const UINT start, const UINT end) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Node currentNode = nodes[end];

	std::vector<UINT> backTrack;

	//m_nodes[start].m_parent = -1;

	while (currentNode.m_parent != start && currentNode.m_parent != -1) {
		backTrack.emplace_back(currentNode.m_parent);
		currentNode = nodes[currentNode.m_parent];
	}

	UINT x = 0;
	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (i == start) {
			SetConsoleTextAttribute(console, 10);
			std::cout << " S ";
		}
		else if (i == end) {
			SetConsoleTextAttribute(console, 10);
			std::cout << " G ";
		}
		else {
			bool isBackTracked = false;
			for (UINT j = 0; j < backTrack.size(); j++)
				if (i == backTrack[j])
					isBackTracked = true;

			if (isBackTracked)
				SetConsoleTextAttribute(console, 11);
			else if (nodes[i].m_checked)
				SetConsoleTextAttribute(console, 12);
			else
				SetConsoleTextAttribute(console, 15);

			if (nodes[i].m_valid == -1)
				std::cout << " X ";
			else
				std::cout << " o ";

		}

		x++;
		if (x > GraphWidth - 1) {
			x = 0;
			std::cout << "\n";
		}

	}

}

inline UINT PositionToArray(const UINT x, const UINT y) {
	return y * GraphWidth + x;
}

inline std::vector<UINT> GetNodeNeighbours(const UINT x, const UINT y, const char* charNodes) {
	std::vector<UINT> neighbours;
	const UINT index = y * GraphWidth + x;

	if (x > 0)
		if (charNodes[index - 1] != 'X')
			neighbours.emplace_back(index - 1);

	if (x < GraphWidth - 1)
		if (charNodes[index + 1] != 'X')
			neighbours.emplace_back(index + 1);

	if (y > 0)
		if (charNodes[index - (GraphHeight)] != 'X')
			neighbours.emplace_back(index - (GraphHeight));

	if (y < GraphHeight - 1)
		if (charNodes[index + (GraphHeight)] != 'X')
			neighbours.emplace_back(index + (GraphHeight));

	return neighbours;
}

inline void ConstructGraph(const char* arr, UINT& start, UINT& end, std::vector<Node>& output) {
	
	for (UINT y = 0; y < GraphHeight; y++)
	{
		for (UINT x = 0; x < GraphWidth; x++)
		{
			Node node = { x, y, {} };
			const char c = arr[y * GraphWidth + x];
			if (c == 'o' || c == 'S' || c == 'G') { // Will return start and goal node 
				node.m_valid = 1;
				node.m_neighbours = GetNodeNeighbours(x, y, &arr[0]);
				output.emplace_back(node);

				if (c == 'S')
					start = y * GraphWidth + x;
				if (c == 'G')
					end   = y * GraphWidth + x;
			}
			else {
				output.emplace_back(node);
			}
		}
	}
}