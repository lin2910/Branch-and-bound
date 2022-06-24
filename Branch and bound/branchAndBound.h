#pragma once
#include <iostream>
#include "arrays.h"

// Метод ветвей и границ

struct listArc
{
	int start = 0;
	int end = 0;
	int weight = 0;
	listArc *next = nullptr;
};

// Создание списка дуг в графе для работы в методе ветвей и границ
listArc* makeList(int** arr, const size_t size);

void printList(listArc* list);

void deleteList(listArc* list);

// Удалить из списка дуг все дуги, в которые входит вершина с номером vertex
// Номер вершин считается с единицы
void deleteVertexFromList(listArc *& list, int vertex);

// Удалить из списка первую дугу
void deleteFirstArc(listArc*& list);

// Удалить из списка дуг дугу (start, end)
void deleteArcFromList(listArc*& list, int start, int end);

// Добавить дугу в конец списка
void addArcToList(listArc*& list, int start, int end, int weight);

// Создание копии списка дуг
listArc* copy(listArc* original);

// Рассчет веса пути по дугам в списке
int weightList(listArc*& list, int& countOperation);

// Нахождение какого-нибудь допустимого решения на графе
// Через перестановки
void findSomeResult(int** matrix, const size_t size, int* inCover, int*& result, int& record, const size_t n, const size_t k, int& countOperation);

void branchBound(int** matrix, const size_t size, listArc* list, int*& result, int& record, int& countOperation);

void branchBound(int** matrix, listArc* list, listArc* resultList, const size_t size, const size_t countInResult, int*& result, int& record, int& countOperation);

int averageBoundary(int** matrix, listArc* resultList, listArc* list, const size_t size, int& countOperation);

int averageBoundary(listArc* resultList, listArc* list, const size_t size, int& countOperation);

void checkRecord(listArc* resultList, int*& result, int& record, int& countOperation);
