#pragma once
#include <iostream>
#include "arrays.h"

//перебор слов в заданном алфавите

void generateGeneralizedStrings(int** arr, int** list, const size_t* power, const size_t size, bool* isPath, int* tempArr, int*& result, int& record, const size_t n, int& countOperation);


// перебор перестановок
void generatePermutations(int** matrix, const size_t size, int* inCover, int*& result, int& record, const size_t n, const size_t k, int& countOperation);

void generate(int* arr, const size_t size, size_t n, size_t k = 0);