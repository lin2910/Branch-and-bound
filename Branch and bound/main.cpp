#include <string>
#include <iostream>

#include "work_with_file.h"
#include "branchAndBound.h"
#include "binaryHeap.h"
#include "permutations.h"
#include "arrays.h"
#include "crtdynmem.h"


using namespace std;

int main(int argc, const char* argv[]) {
	if (argc == 5) {
		try {
			const char* InputFile = argv[1];
			const char* OutputFile_r = argv[2];
			const char* OutputFile_v = argv[3];
			const char* OutputFile_t = argv[4];
			size_t size;
			size_t uCount;

			int** arr = get_array(InputFile, size, uCount);

			//Создание списка смежности
			size_t* power = new size_t[size];
			for (size_t i = 0; i < size; i++) {
				power[i] = 0;
			}

			int** list = new int* [size];
			for (size_t i = 0; i < size; i++)
			{
				int* isArc = new int[size];
				for (size_t j = 0; j < size; j++) {
					if (arr[i][j] != 0) {
						add(isArc, size, power[i], j + 1);
					}

				}
				list[i] = copy(isArc, power[i]);
				delete[]isArc;
			}

			// Перебор обобщенных строк
			bool* isPath = new bool[size];
			int* temp = new int[size];
			for (size_t i = 0; i < size; i++)
			{
				temp[i] = 0;
			}
			int* result = new int[size];
			for (size_t i = 0; i < size - 1; i++) {
				isPath[i] = true;
				result[i] = 0;
			}
			isPath[size - 1] = false;
			temp[size - 1] = size;
			int record = INT_MAX;
			int countOperation = 0;

			clock_t start, stop;

			//начало отсчета времени
			start = clock();

			generateGeneralizedStrings(arr, list, power, size, isPath, temp, result, record, size - 1, countOperation);
			// конец отсчета времени
			stop = clock();

			// количество секунд
			double secondsGeneralizedStrings = double(stop - start) / CLOCKS_PER_SEC;

			put_array(OutputFile_r, sort(result, size), size);
			put_number(OutputFile_v, record);
			put_number(OutputFile_t, secondsGeneralizedStrings, countOperation);


			delete[]result;
			delete[]isPath;
			delete[]temp;
			for (size_t i = 0; i < size; i++)
				delete[]list[i];
			delete[]list;

			// Перебор перестановок
			isPath = new bool[size];
			temp = new int[size];
			for (size_t i = 0; i < size; i++)
			{
				temp[i] = i + 1;
			}
			result = new int[size];
			for (size_t i = 0; i < size; i++) {
				isPath[i] = true;
				result[i] = 0;
			}
			isPath[size - 1] = false;
			record = INT_MAX;
			countOperation = 0;

			for (size_t i = 0; i < size; i++)
			{
				temp[i] = i + 1;
			}

			for (size_t i = 0; i < size; i++) {
				isPath[i] = true;
				result[i] = 0;
			}
			isPath[size - 1] = false;
			record = INT_MAX;
			countOperation = 0;

			//начало отсчета времени
			start = clock();

			generatePermutations(arr, size, temp, result, record, size, 0, countOperation);

			// конец отсчета времени
			stop = clock();

			// количество секунд
			double secondsPermutations = double(stop - start) / CLOCKS_PER_SEC;

			put_array_in_end(OutputFile_r, sort(result, size), size);
			put_number_in_end(OutputFile_v, record);
			put_number_in_end(OutputFile_t, secondsPermutations, countOperation);

			delete[]result;
			delete[]isPath;
			delete[]temp;

			// Метод ветвей и границ
			result = new int[size];
			for (size_t i = 0; i < size; i++) {
				result[i] = 0;
			}
			record = INT_MAX;

			listArc* listForBAB = makeList(arr, size);
			listArc* p = listForBAB;
			countOperation = 0;
			//начало отсчета времени
			start = clock();

			branchBound(arr, size, listForBAB, result, record, countOperation);

			// конец отсчета времени
			stop = clock();

			// количество секунд
			double secondsBranchBound = double(stop - start) / CLOCKS_PER_SEC;

			put_array_in_end(OutputFile_r, sort(result, size), size);
			put_number_in_end(OutputFile_v, record);
			put_number_in_end(OutputFile_t, secondsBranchBound, countOperation);

			deleteList(listForBAB);
			delete[]result;


			// Метод ветвей и границ + очередь
			result = new int[size];
			for (size_t i = 0; i < size; i++) {
				result[i] = 0;
			}
			record = INT_MAX;

			listForBAB = makeList(arr, size);
			countOperation = 0;
			//начало отсчета времени
			start = clock();

			branchBoundWithQueue(arr, size, listForBAB, uCount, result, record, countOperation);

			// конец отсчета времени
			stop = clock();

			// количество секунд
			double secondsBranchBoundWithQueue = double(stop - start) / CLOCKS_PER_SEC;

			put_array_in_end(OutputFile_r, sort(result, size), size);
			put_number_in_end(OutputFile_v, record);
			put_number_in_end(OutputFile_t, secondsBranchBoundWithQueue, countOperation);

			deleteList(listForBAB);

			for (size_t i = 0; i < size; i++)
				delete[]arr[i];
			delete[]arr;
			delete[]power;
			delete[]result;
			for (size_t i = 0; i < size; i++)
				delete[]list[i];
			delete[]list;
		}
		catch (const std::exception& e) {
			cout << "Exeption: " << e.what() << endl;
		}
		//system("pause");
		return 0;
	}

	cout << "Invalid count of arguments" << endl;
	
	const char* InputFile = "TSP1_permut.txt";//"TSP1_permut.txt";
	const char* OutputFile_r = "TSP1_r.txt";
	const char* OutputFile_v = "TSP1_v.txt";
	const char* OutputFile_t = "TSP1_t.txt";
	
	size_t size;
	size_t uCount;

	int** arr = get_array(InputFile, size, uCount);

	//Создание списка смежности
	size_t* power = new size_t[size];
	for (size_t i = 0; i < size; i++) {
		power[i] = 0;
	}

	int** list = new int* [size];
	for (size_t i = 0; i < size; i++)
	{
		int* isArc = new int[size];
		for (size_t j = 0; j < size; j++) {
			if (arr[i][j] != 0) {
				add(isArc, size, power[i], j + 1);
			}

		}
		list[i] = copy(isArc, power[i]);
		delete[]isArc;
	}

	// Перебор обобщенных строк
	bool* isPath = new bool[size];
	int* temp = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = 0;
	}
	int* result = new int[size];
	for (size_t i = 0; i < size - 1; i++) {
		isPath[i] = true;
		result[i] = 0;
	}
	isPath[size - 1] = false;
	temp[size - 1] = size;
	int record = INT_MAX;
	int countOperation = 0;

	clock_t start, stop;

	//начало отсчета времени
	start = clock();

	generateGeneralizedStrings(arr, list, power, size, isPath, temp, result, record, size - 1, countOperation);
	// конец отсчета времени
	stop = clock();

	// количество секунд
	double secondsGeneralizedStrings = double(stop - start) / CLOCKS_PER_SEC;

	put_array(OutputFile_r, sort(result, size), size);
	put_number(OutputFile_v, record);
	put_number(OutputFile_t, secondsGeneralizedStrings, countOperation);


	delete[]result;
	delete[]isPath;
	delete[]temp;

	// Перебор перестановок
	isPath = new bool[size];
	temp = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = i + 1;
	}
	result = new int[size];
	for (size_t i = 0; i < size; i++) {
		isPath[i] = true;
		result[i] = 0;
	}
	isPath[size - 1] = false;
	record = INT_MAX;
	countOperation = 0;

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = i + 1;
	}

	for (size_t i = 0; i < size; i++) {
		isPath[i] = true;
		result[i] = 0;
	}
	isPath[size - 1] = false;
	record = INT_MAX;
	countOperation = 0;

	//начало отсчета времени
	start = clock();

	generatePermutations(arr, size, temp, result, record, size, 0, countOperation);

	// конец отсчета времени
	stop = clock();

	// количество секунд
	double secondsPermutations = double(stop - start) / CLOCKS_PER_SEC;

	put_array_in_end(OutputFile_r, sort(result, size), size);
	put_number_in_end(OutputFile_v, record);
	put_number_in_end(OutputFile_t, secondsPermutations, countOperation);

	delete[]result;
	delete[]isPath;
	delete[]temp;

	// Метод ветвей и границ
	result = new int[size];
	for (size_t i = 0; i < size; i++) {
		result[i] = 0;
	}
	record = INT_MAX;

	listArc* listForBAB = makeList(arr, size);
	countOperation = 0;
	//начало отсчета времени
	start = clock();

	branchBound(arr, size, listForBAB, result, record, countOperation);

	// конец отсчета времени
	stop = clock();

	// количество секунд
	double secondsBranchBound = double(stop - start) / CLOCKS_PER_SEC;

	put_array_in_end(OutputFile_r, sort(result, size), size);
	put_number_in_end(OutputFile_v, record);
	put_number_in_end(OutputFile_t, secondsBranchBound, countOperation);

	deleteList(listForBAB);
	delete[]result;


	// Метод ветвей и границ + очередь
	result = new int[size];
	for (size_t i = 0; i < size; i++) {
		result[i] = 0;
	}
	record = INT_MAX;

	listForBAB = makeList(arr, size);
	countOperation = 0;
	//начало отсчета времени
	start = clock();

	branchBoundWithQueue(arr, size, listForBAB, uCount, result, record, countOperation);

	// конец отсчета времени
	stop = clock();

	// количество секунд
	double secondsBranchBoundWithQueue = double(stop - start) / CLOCKS_PER_SEC;


	cout << "time: " << secondsBranchBoundWithQueue << endl;
	cout << "result: " << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << result[i] << ' ';
	}
	cout << endl;
	cout << "record: " << record << endl;
	cout << endl;

	put_array_in_end(OutputFile_r, sort(result, size), size);
	put_number_in_end(OutputFile_v, record);
	put_number_in_end(OutputFile_t, secondsBranchBoundWithQueue, countOperation);

	deleteList(listForBAB);

	for (size_t i = 0; i < size; i++)
		delete[]arr[i];
	delete[]arr;
	delete[]power;
	delete[]result;

	_CrtDumpMemoryLeaks();
	//*/
	system("pause");
	return 0;
}
