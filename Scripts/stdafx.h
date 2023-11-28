// Precompiled header
#pragma once

#define PRINT_RANDOM_ARRAY 0 // Set to 1 if you want to print the randomized Array

#include <Windows.h>
#include <iostream>
#include <string>

#include <random>
#include <array>
#include <vector>

const UINT MaxRowCount = 20;

template <typename T> void PrintArray(T* arr, const UINT size, std::string arrType) {
	int newRow = 1;

	std::cout << arrType << "\n";

	for (UINT i = 0; i < size; i++) {	
		std::cout << " " << static_cast<int>(arr[i]) << " ";
		if (newRow == MaxRowCount) {
			printf("\n");
			newRow = 0;
		}

		newRow++;
	}	
}

template <typename T> void RandomizeArray(T* arr, const UINT size, std::mt19937& rng, std::uniform_int_distribution<std::mt19937::result_type>& dist) {	
	int newRow = 0;

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
