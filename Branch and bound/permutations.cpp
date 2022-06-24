#include "permutations.h"

void generateGeneralizedStrings(int** arr, int** list, const size_t* power, const size_t size, bool* isPath, int* tempArr, int*& result, int& record, const size_t n, int& countOperation) {
	if (n == 0) {
		countOperation++;
		if (isWay(arr, size, tempArr, countOperation)) {
			for (size_t i = 0; i < size; i++)
			{
				if (isPath[i] == 1)
					return;
			}
			// вызов функции которая считает мощность и запоминает рекорд.
			howLong(arr, size, tempArr, result, record, countOperation);
		}
	}
	else {
		for (size_t i = 0; i < power[tempArr[n] - 1]; i++)
		{
			//н список смежности
			// D  -- степень итой вершины
			int m = list[tempArr[n]-1][i] - 1; // Итая вершина смежная с н 
			countOperation++;
			if (isPath[m]) {
				isPath[m] = false;
				tempArr[n-1] = m + 1;
				countOperation += 2;
				generateGeneralizedStrings(arr, list, power, size, isPath, tempArr, result, record, n - 1, countOperation);
				isPath[m] = true;
				countOperation++;
			}
		}
	}
}

// Перестановки
void generate(int* arr, const size_t size, size_t n, size_t k) {
	if (k == n - 1) {
		for (size_t i = 0; i < size; i++)
			std::cout << arr[i] << ' ';
		std::cout << std::endl;
	}
	else {
		for (size_t i = k; i < n; i++)
		{
			if (arr[i] == 1)
				continue;
			int t = arr[k];
			arr[k] = arr[i];
			arr[i] = t;
			generate(arr, size, n, k + 1);
			t = arr[k];
			arr[k] = arr[i];
			arr[i] = t;
		}
	}
}

void generatePermutations(int** matrix, const size_t size, int* inCover, int*& result, int& record, const size_t n, const size_t k, int& countOperation) {
	if (k == n - 1) {
		if (isWay(matrix, size, inCover, countOperation)) {
			howLong(matrix, size, inCover, result, record, countOperation);
		}
	}
	else {
		for (size_t i = k; i < n; i++)
		{
			if (inCover[i] == 1)
				continue;
			int t = inCover[k];
			inCover[k] = inCover[i];
			inCover[i] = t;
			generatePermutations(matrix, size, inCover, result, record, n, k + 1, countOperation);
			t = inCover[k];
			inCover[k] = inCover[i];
			inCover[i] = t;
		}
	}
}
