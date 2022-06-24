#pragma once

void add(int*& arr, size_t size, size_t& size_cover, int toAdd); 


void add(int*& arr, size_t size, size_t& size_cover, int toAdd, int& countOperation);

int* copy(const int* original, const size_t size);

// Общие функции

// Проверка является ли найденная последовательность вершин циклом в графе
bool isWay(int** matrix, const size_t size, int* inCover, int& countOperation);

//Функция нахождения длины найденного цикла и сравнения ее с рекордным значением тут же
void howLong(int** arr, const size_t size, int* way, int*& result, int& record, int& countOperation);

int* sort(int* arr, const size_t size);