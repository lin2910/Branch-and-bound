#include "branchAndBound.h"


listArc* makeList(int** arr, const size_t size) {
	listArc* resultList = new listArc;
	listArc* p;
	listArc* q = resultList;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i+1; j < size; j++)
			if (arr[i][j] != 0) {
				p = new listArc;
				p->start = i + 1;
				p->end = j + 1;
				p->weight = arr[i][j];
				p->next = nullptr;
				q->next = p;
				q = q->next;
			}

	}
	deleteFirstArc(resultList);
	return resultList;
}

void printList(listArc* list) {
	listArc* q = list;
	while (q) {
		std::cout << "( " << q->start << ", " << q->end << " ) =  " << q->weight << std::endl;
		q = q->next;
	}

}

void deleteList(listArc* list) {
	listArc* p = list;
	listArc* q = list;
	while (q && p) {
		q = q->next;
		delete p;
		p = q;
	}
}

void deleteVertexFromList(listArc*& list, int vertex) {
	listArc* q;
	while (list && (list->start == vertex || list->end == vertex)) {
		q = list;
		list = list->next;
		delete q;
		
	}
	if (!list)
		return;
	listArc* p;
	listArc* t;

	p = list;
	q = list->next;

	while (q)
		if (q && q->start == vertex || q->end == vertex) {
			t = q;
			q = q->next;
			p->next = q;

			delete t;
		}
		else {
			q = q->next;
			p = p->next;
		}

}

void deleteFirstArc(listArc*& list)
{
	listArc* p = list;
	list = list->next;
	delete p;
}

void deleteArcFromList(listArc*& list, int start, int end)
{
	listArc* p = list;
	if (list && (list->start == start && list->end == end)) {
		list = list->next;
		delete p;
		return;
	}
	listArc* t;
	listArc* q = list->next;
	while (q)
		if (q && q->start == start && q->end == end) {
			t = q;
			q = q->next;
			p->next = q;
			delete t;
			return;
		}
		else {
			q = q->next;
			if (p->next)
				p = p->next;
		}
}

void addArcToList(listArc*& list, int start, int end, int weight) {
	if (list) {
		listArc* q = list;
		while (q && q->next)
			q = q->next;
		listArc* p = new listArc;

		p->start = start;
		p->end = end;
		p->weight = weight;
		p->next = nullptr;
		q->next = p;
		return;
	}

	list->start = start;
	list->end = end;
	list->weight = weight;
	list->next = nullptr;
	return;
	
}

listArc* copy(listArc* original) {
	listArc* copy = new listArc;
	listArc* p = original;
	listArc* q;
	copy->start = p->start;
	copy->end = p->end;
	copy->weight = p->weight;
	copy->next = nullptr;
	listArc* t = copy;
	p = p->next;
	while (p) {
		q = new listArc;
		q->start = p->start;
		q->end = p->end;
		q->weight = p->weight;
		t->next = q;
		p = p->next;
		t = t->next;
	}
	return copy;
}

int weightList(listArc*& list, int& countOperation) {
	int weight = 0;
	countOperation++;
	listArc* q = list;
	while (q) {
		weight += q->weight;
		countOperation++;
		q = q->next;
	}
	return weight;
}


void findSomeResult(int** matrix, const size_t size, int* inCover, int*& result, int& record, const size_t n, const size_t k, int& countOperation) {
	countOperation++;
	if (k == n - 1) {
		if (isWay(matrix, size, inCover, countOperation)) {
			howLong(matrix, size, inCover, result, record, countOperation);
			return;
		}
	}
	else {
		for (size_t i = k; i < n; i++)
		{
			countOperation++;
			if (inCover[i] == 1)
				continue;
			int t = inCover[k];
			inCover[k] = inCover[i];
			inCover[i] = t;
			findSomeResult(matrix, size, inCover, result, record, n, k + 1, countOperation);
			countOperation += 4;
			if (record < INT_MAX)
				return;
			t = inCover[k];
			inCover[k] = inCover[i];
			inCover[i] = t;
			countOperation += 3;
		}
	}
}

void branchBound(int** matrix, const size_t size, listArc* list, int*& result, int& record, int& countOperation) {
	//найти случайный цикл для оценки
	int* temp = new int[size];
	countOperation += size;
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = i + 1;
	}
	findSomeResult(matrix, size, temp, result, record, size, 0, countOperation);
	delete[]temp;

	size_t count = 0;
	countOperation++;
	while (count == 0) {
		size_t i = 0; count = 0;
		countOperation += 2;
		for (size_t j = 0; j < size; j++)
		{
			countOperation++;
			if (matrix[i][j] != 0)
				count++;
		}
	}
	countOperation += count;
	
	listArc* resultList = new listArc;
	//проходим дуги
	for (size_t j = 0; j < count-1; j++)	// Первая дуга в цикле -- начинается в вершине 1
											// не рассматриваем начало с последней дуги в списке, у которой начало в вершине 1
											// так как иначе не сможем вернуться в вершину 1 и завершить цикл
	{
		addArcToList(resultList, list->start, list->end, list->weight);
		countOperation += 7;
		deleteFirstArc(resultList);
		countOperation += 6;

		list = list->next;
		countOperation += 2;

		// рекурсивный вызов 
		listArc* copyList = copy(list);
		branchBound(matrix, copyList, resultList, size, 1, result, record, countOperation);
		deleteList(copyList);
		deleteList(resultList);
		resultList = new listArc;
	}
	deleteList(resultList);
}

void branchBound(int** matrix, listArc* list, listArc* resultList, const size_t size, const size_t countInResult, int*& result, int& record, int& countOperation) {
	//std::cout << std::endl << std::endl;
	//printList(resultList);
	
	// разбиение на новые ветви
	listArc* q = resultList;
	while (q && q->next)
		q = q->next;
	countOperation += countInResult;
	int start =  q->end; // вершина, для которой ищем, как добавить новые дуги
	int blok = q->start;
	
	countOperation++;
	if (blok != 1)
		deleteVertexFromList(list, blok);	// не рассматривать уже добавленную дугу
	//printList(list);

	countOperation += 2;
	if (countInResult == size && start == 1)  // Найден какой-то путь
	{
		//std::cout << std::endl << "Way: " << std::endl;
		//printList(resultList); std::cout << std::endl;

		// проверка на то, является ли найденный путь лучше
		checkRecord(resultList, result, record, countOperation);
		return;
	}
	countOperation++;
	if (start == 1) {  //найден частичный путь (слишком рано вернулись)
		//std::cout << std::endl << "Short way: " << std::endl;
		//printList(resultList); std::cout << std::endl;
		return;
	}
	countOperation++;
	if (!list) {  // нет пути
		//std::cout << std::endl << "No way: " << std::endl;
		//printList(resultList); std::cout << std::endl;
		return;
	}

	// сравнение
	countOperation += 2;
	if (countInResult < size / 3) {
		if (averageBoundary(matrix, resultList, list, size, countOperation) > record)
			return;

	}
	else {
		if (averageBoundary(resultList, list, size, countOperation) > record)
			return;
	}

	//listArc* quelle = new listArc;

	// Добавлять новые ветки и менять имя дуги так, чтобы начало добавленной совпадало с концом предыдущей
	listArc* p = list;
	while (p) {
		if (p->start == start) {

			listArc* copyResultList = copy(resultList);
			countOperation+= 6*countInResult - 1;

			addArcToList(copyResultList, p->start, p->end, p->weight);
			countOperation += countInResult + 4;
			q = p;
			p = p->next;
			countOperation++;
			listArc* copyList = copy(list); //??
			deleteVertexFromList(copyList, q->start);
			branchBound(matrix, copyList, copyResultList, size, countInResult + 1, result, record, countOperation);
			deleteList(copyList); //??
			deleteList(copyResultList);
			countOperation += 2 * countInResult;
		}
		else
			p = p->next;
		countOperation++;
	}
	p = list;
	while (p) {
		if (p->end == start) {
			listArc* copyResultList = copy(resultList);
			countOperation += 6 * countInResult - 1;
			addArcToList(copyResultList, p->end, p->start, p->weight);
			countOperation += countInResult + 4;
			q = p;
			p = p->next;
			countOperation++;
			listArc* copyList = copy(list);
			deleteVertexFromList(copyList, q->end);
			branchBound(matrix, copyList, copyResultList, size, countInResult + 1, result, record, countOperation);
			deleteList(copyList);
			deleteList(copyResultList);
			countOperation += 2 * countInResult;
		}
		else
			p = p->next;
		countOperation++;
	}

	// рекурсивный вызов очереди
	//std::cout << std::endl << "res" << std::endl;
	//printList(resultList);
	//std::cout << "quelle" << std::endl;
	//	printList(quelle);
	//deleteList(quelle);
}

int averageBoundary(int** matrix, listArc* resultList, listArc* list, const size_t size, int& countOperation)
{
	int* countOccurrences = new int[size];
	int* weightOccurrences = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		countOccurrences[i] = 0;
		weightOccurrences[i] = 0;
		countOperation += 2;
	}
	listArc* q = resultList;
	double weight = 0;
	while (q) {
		weightOccurrences[q->start - 1] += q->weight;
		weightOccurrences[q->end - 1] += q->weight;
		countOccurrences[q->start - 1]++;
		countOccurrences[q->end - 1]++;
		countOperation += 4;
		q = q->next;
	}

	for (size_t i = 0; i < size; i++)
	{
		countOperation++;
		if (countOccurrences[i] > 2) {
			//std::cout << "YOU BREAK EVERYTHING";
			return -200;
		}
		if (countOccurrences[i] == 2)
			continue;
		if (countOccurrences[i] == 1) {
			int t = -1;
			q = resultList;
			countOperation += 3;
			while (q) {
				if (q->start == i + 1) {
					t = q->end; 
					countOperation += 2;
					break;
				}
				else
					if (q->end == i + 1) {
						t = q->start;
						countOperation += 2;
						break;
					}
				q = q->next;
				countOperation++;
			}
			int min = INT_MAX;
			countOperation++;
			for (size_t j = 0; j < size; j++)
			{
				countOperation++;
				if (j == t - 1)
					continue;
				countOperation++;
				if (matrix[i][j] != 0 && matrix[i][j] < min) {
					min = matrix[i][j];
					countOperation++;
				}
			}
			weightOccurrences[i] += min;
			countOperation++;

		}
		else
		{
			int min1 = INT_MAX;
			int min2 = INT_MAX;
			countOperation += 2;
			for (size_t j = 0; j < size; j++)
			{
				countOperation++;
				if (matrix[i][j] == 0)
					continue;
				countOperation++;
				if (matrix[i][j] < min1) {
					min2 = min1;
					min1 = matrix[i][j];
					countOperation += 2;
				}
				else {
					countOperation++;
					if (matrix[i][j] < min2) {
						min2 = matrix[i][j];
						countOperation++;
					}
				}
			}
			weightOccurrences[i] += min1+ min2;
			countOperation++;
		}
	}
	for (size_t i = 0; i < size; i++)
		weight += weightOccurrences[i] / 2.0;
	countOperation += 2 * size;

	return (int)weight;
}

int averageBoundary(listArc* resultList, listArc* list, const size_t size, int& countOperation)
{
	listArc* q = resultList;
	int weight = 0;
	size_t s = 0;
	countOperation += 2;
	while (q) {
		weight += q->weight;
		s++;
		q = q->next;
		countOperation += 3;
	}
	int min = INT_MAX;
	q = list;
	countOperation += 2;
	while (q) {
		if (min > q->weight) {
			min = q->weight;
			countOperation++;
		}
		q = q->next;
		countOperation += 2;
	}
	weight += min * (size - s);
	countOperation++;
	return weight;
}

void checkRecord(listArc* resultList, int*& result, int& record, int& countOperation) {
	listArc* q = resultList;
	int weight = 0;
	countOperation++;

	while (q) {
		weight += q->weight;
		q = q->next;
		countOperation++;
	}
	countOperation++;
	if (weight < record) {
		record = weight;
		q = resultList; 
		size_t i = 0;
		countOperation += 3;
		while (q) {
			result[i] = q->start;
			i++;
			q = q->next;
			countOperation += 3;
		}
	}
}
