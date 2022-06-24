void add(int*& arr, size_t size, size_t& size_cover, int toAdd) {
	for (size_t i = 0; i < size_cover; i++)
		if (arr[i] == toAdd)
			return;
		else
			if (arr[i] > toAdd) {
				int t, tt = toAdd;
				size_cover++;
				for (size_t j = i; j < size_cover; j++) {
					t = arr[j];
					arr[j] = tt;
					tt = t;
				}
				return;
			}
	if (size_cover < size)
		arr[size_cover++] = toAdd;
}

void add(int*& arr, size_t size, size_t& size_cover, int toAdd, int& countOperation) {
	for (size_t i = 0; i < size_cover; i++)
		if (arr[i] == toAdd) {
			countOperation++;
			return;
		}
		else
			if (arr[i] > toAdd) {
				countOperation++;
				int t, tt = toAdd;
				size_cover++;
				for (size_t j = i; j < size_cover; j++) {
					t = arr[j];
					arr[j] = tt;
					tt = t;
					countOperation += 2;
				}
				return;
			}
	if (size_cover < size) {
		arr[size_cover++] = toAdd;
		countOperation += 2;
	}
}

int* copy(const int* original, const size_t size) {
	int* copy = new int[size];
	for (size_t i = 0; i < size; i++)
		copy[i] = original[i];
	return copy;
}




void howLong(int** arr, const size_t size, int* way, int*& result, int& record, int& countOperation) {
	int weight = 0;
	weight += arr[way[size - 1] - 1][way[0] - 1];
	for (size_t i = 0; i < size - 1; i++)
	{
		weight += arr[way[i] - 1][way[i + 1] - 1];
	}
	if (weight < record) {
		record = weight;
		delete[]result;
		result = copy(way, size);
		countOperation += size;
	}
}

bool isWay(int** matrix, const size_t size, int* inCover, int& countOperation) {

	countOperation++;
	if (matrix[inCover[0] - 1][inCover[size - 1] - 1] == 0)
		return false;
	for (size_t i = 0; i < size - 1; i++)
	{
		countOperation++;
		if (matrix[inCover[i] - 1][inCover[i + 1] - 1] == 0)
			return false;
	}
	return true;
}


int* sort(int* arr, const size_t size) {

	int* sortArr = new int[size];
	size_t start = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == 1) {
			start = i;
			break;
		}
	}
	size_t j = 0;
	for (size_t i = start; i < size; i++) 
	{
		sortArr[j] = arr[i];
		j++;
	}
	for (size_t i = 0; i < start ; i++) 
	{
		sortArr[j] = arr[i];
		j++;
	}
	return sortArr;
}