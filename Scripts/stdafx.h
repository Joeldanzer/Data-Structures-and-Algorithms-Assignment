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

const UINT MaxArrayCount = 10000;
const UINT NumberOfTests = 1;

const int MinNumber = 0;
const int MaxNumber = 100;

const UINT MaxRowCount = 20;

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
