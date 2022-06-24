#pragma once
#include "branchAndBound.h"

struct queueEl {
	listArc *list;
	int weight;  // ключ - высчитываемая граница
};

void insert(queueEl* queue, const size_t uCount, size_t &queueSize, queueEl elem, int& countOperation);

void print(queueEl* queue, const size_t uCount, const size_t queueSize);

void print(listArc* list);

queueEl GetMin(queueEl* queue, int& countOperation);

void DelMin(queueEl* queue, const size_t uCount, size_t &queueSize,  int& countOperation);

void shiftUp(queueEl* queue, const size_t uCount, const size_t queueSize, size_t index, int& countOperation);

void shiftDown(queueEl* queue, const size_t uCount, const size_t queueSize, size_t index, int& countOperation);

void branchBoundWithQueue(int** matrix, const size_t size, listArc* list,
	const size_t uCount, int*& result, int& record, int& countOperation);

void branchBoundWithQueue(int** matrix, listArc* list, listArc* resultList, const size_t size, const size_t uCount,
	const size_t countInResult, int*& result, int& record, int& countOperation);