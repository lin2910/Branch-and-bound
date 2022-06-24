#include "binaryHeap.h"

void insert(queueEl* queue, const size_t uCount, size_t& queueSize, queueEl elem, int& countOperation)
{
	countOperation += 2;
	queue[queueSize] = elem;
	
	if(queueSize >= uCount)
	{
		return;
	}

	countOperation++;
	queueSize++;
	shiftUp(queue, uCount, queueSize, queueSize-1, countOperation);
}

void print(queueEl* queue, const size_t uCount, const size_t queueSize) {
	size_t i = 0;
	size_t k = 1;
	while (i < queueSize) {
		while ((i < k) && (i < queueSize)) {
			std::cout << queue[i].weight << " list: ";
			print(queue[i].list);
			i++;
		}
		std::cout << std::endl;
		k = k * 2 + 1;
	}
}

void print(listArc* list)
{
	listArc* q = list;
	while (q) {
		std::cout << "( " << q->start << ", " << q->end << " ) =  " << q->weight << ' ';
		q = q->next;
	}
}

queueEl GetMin(queueEl* queue, int& countOperation)
{
	countOperation++;
	return queue[0];
}

void DelMin(queueEl* queue, const size_t uCount, size_t& queueSize, int& countOperation)
{
	countOperation += 2;
	deleteList(queue[0].list);
	if (queueSize == 0) {
		queue[0].weight = 0;
		return;
	}queueSize--;
	if (queueSize < 0) {
		queue[0].weight = 0;
		return;
	}
	
	queue[0].weight = queue[queueSize].weight;
	queue[0].list = copy(queue[queueSize].list);
	deleteList(queue[queueSize].list);
	shiftDown(queue, uCount, queueSize, 0, countOperation);
}


void shiftUp(queueEl* queue, const size_t uCount, const size_t queueSize, size_t index, int& countOperation)
{
	countOperation++;
	if (index == 0)  // вышли на вершину
		return;
	countOperation++;
	size_t parentIndex = index / 2;
	if (queue[parentIndex].weight > queue[index].weight) {
		countOperation += 3;
		queueEl temp = queue[parentIndex];
		queue[parentIndex] = queue[index];
		queue[index] = temp;
		shiftUp(queue, uCount, queueSize, parentIndex, countOperation);
	}
}

void shiftDown(queueEl* queue, const size_t uCount, const size_t queueSize, size_t index, int& countOperation) {
	countOperation += 2;
	size_t leftIndex = 2 * index;
	if (leftIndex > queueSize)		// даже левого потомка нет, конец
		return;
	countOperation += 2;
	size_t rightIndex = 2 * index + 1;
	size_t newIndex;
	if (rightIndex > queueSize) {	// Есть только левый потомок
		countOperation++;
		newIndex = leftIndex;
	}
	else {							// есть два индекса
		countOperation += 2;
		if (queue[rightIndex].weight > queue[leftIndex].weight)
			newIndex = leftIndex; else newIndex = rightIndex;
	}
	if (queue[newIndex].weight > queue[index].weight) {
		countOperation += 3;
		queueEl temp = queue[newIndex];
		queue[newIndex] = queue[index];
		queue[index] = temp;
		shiftDown(queue, uCount, queueSize, leftIndex, countOperation);
	}
}

void branchBoundWithQueue(int** matrix, const size_t size, listArc* list,
	const size_t uCount, int*& result, int& record, int& countOperation) 
{
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
	queueEl* queue = new queueEl[count];
	size_t queueSize = 0;

	countOperation += count;
	listArc* p = list;
	//проходим дуги
	for (size_t j = 0; j < count - 1; j++)	// Первая дуга в цикле -- начинается в вершине 1
											// не рассматриваем начало с последней дуги в списке, у которой начало в вершине 1
											// так как иначе не сможем вернуться в вершину 1 и завершить цикл
	{
		queueEl t;
		t.list = new listArc;
		addArcToList(t.list, p->start, p->end, p->weight);
		countOperation += 7;
		deleteFirstArc(t.list);

		t.weight = averageBoundary(matrix, t.list, list, size, countOperation);
		insert(queue, uCount, queueSize, t, countOperation);
		p = p->next;

	}

	std::cout << "First: " << std::endl;
	print(queue, uCount, queueSize);
	std::cout << std::endl;

	for (size_t i = 0; i < queueSize; i++)
	{
		listArc* copyList = copy(list);
		branchBoundWithQueue(matrix, copyList, GetMin(queue, countOperation).list, size, uCount, 1, result, record, countOperation);
		DelMin(queue, uCount, queueSize, countOperation);
	}
	delete[]queue;
}

void branchBoundWithQueue(int** matrix, listArc* list, listArc* resultList, const size_t size,
	const size_t uCount, const size_t countInResult, int*& result, int& record, int& countOperation)
{
	// разбиение на новые ветви
	listArc* q = resultList;
	size_t count = 0;
	while (q && q->next) {
		q = q->next;
		count++;
	}
	countOperation += 2*countInResult;
	int start = q->end; // вершина, для которой ищем, как добавить новые дуги
	int blok = q->start;

	countOperation++;
	if (blok != 1)
		deleteVertexFromList(list, blok);	// не рассматривать уже добавленную дугу

	countOperation += 2;
	if (countInResult == size && start == 1)  // Найден какой-то путь
	{
		// проверка, является ли найденный путь лучше
		checkRecord(resultList, result, record, countOperation);
		return;
	}
	countOperation++;
	if (start == 1) {  //найден частичный путь (слишком рано вернулись)
		return;
	}
	countOperation++;
	if (!list) {  // нет пути
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

	queueEl* queue = new queueEl[count];
	size_t queueSize = 0;

	// Добавлять новые ветки и менять имя дуги так, чтобы начало добавленной совпадало с концом предыдущей
	listArc* p = list;
	while (p) {
		if (p->start == start) {
			queueEl t;
			t.list = copy(resultList);
			//deleteFirstArc(t.list);
			addArcToList(t.list, p->start, p->end, p->weight);
			t.weight = averageBoundary(matrix, t.list, list, size, countOperation);
			//std::cout << "insert weight " << t.weight << std::endl;
			//printList(t.list);
			//std::cout << std::endl;
			insert(queue, uCount, queueSize, t, countOperation);
			q = p;
			p = p->next;

			countOperation++;

		}
		else
			p = p->next;
		countOperation++;
	}
	p = list;
	while (p) {
		if (p->end == start) {
			queueEl t;
			t.list = copy(resultList);
			//deleteFirstArc(t.list);
			addArcToList(t.list, p->end, p->start, p->weight);
			t.weight = averageBoundary(matrix, t.list, list, size, countOperation);
			insert(queue, uCount, queueSize, t, countOperation);
			q = p;
			p = p->next;
			countOperation++;
		}
		else
			p = p->next;
		countOperation++;
	}

	std::cout << "countInResult: " << countInResult << std::endl;
	print(queue, uCount, queueSize);
	std::cout << std::endl;

	// рекурсивный вызов очереди
	while (queueSize > 0)
	{
		listArc* copyList = copy(list); 
		deleteVertexFromList(copyList, q->start);
		branchBoundWithQueue(matrix, copyList, GetMin(queue, countOperation).list,
			size, uCount, countInResult + 1, result, record, countOperation);
		//deleteList(copyList); 
		DelMin(queue, uCount, queueSize, countOperation);
		countOperation += 2 * countInResult; 
	}
	//std::cout << "quelle" << std::endl;
	//	printList(quelle);
	//deleteList(quelle);

}
