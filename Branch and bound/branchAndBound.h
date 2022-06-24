#pragma once
#include <iostream>
#include "arrays.h"

// ����� ������ � ������

struct listArc
{
	int start = 0;
	int end = 0;
	int weight = 0;
	listArc *next = nullptr;
};

// �������� ������ ��� � ����� ��� ������ � ������ ������ � ������
listArc* makeList(int** arr, const size_t size);

void printList(listArc* list);

void deleteList(listArc* list);

// ������� �� ������ ��� ��� ����, � ������� ������ ������� � ������� vertex
// ����� ������ ��������� � �������
void deleteVertexFromList(listArc *& list, int vertex);

// ������� �� ������ ������ ����
void deleteFirstArc(listArc*& list);

// ������� �� ������ ��� ���� (start, end)
void deleteArcFromList(listArc*& list, int start, int end);

// �������� ���� � ����� ������
void addArcToList(listArc*& list, int start, int end, int weight);

// �������� ����� ������ ���
listArc* copy(listArc* original);

// ������� ���� ���� �� ����� � ������
int weightList(listArc*& list, int& countOperation);

// ���������� ������-������ ����������� ������� �� �����
// ����� ������������
void findSomeResult(int** matrix, const size_t size, int* inCover, int*& result, int& record, const size_t n, const size_t k, int& countOperation);

void branchBound(int** matrix, const size_t size, listArc* list, int*& result, int& record, int& countOperation);

void branchBound(int** matrix, listArc* list, listArc* resultList, const size_t size, const size_t countInResult, int*& result, int& record, int& countOperation);

int averageBoundary(int** matrix, listArc* resultList, listArc* list, const size_t size, int& countOperation);

int averageBoundary(listArc* resultList, listArc* list, const size_t size, int& countOperation);

void checkRecord(listArc* resultList, int*& result, int& record, int& countOperation);
