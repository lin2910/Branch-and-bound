#include "work_with_file.h"

int get_number(const char* filename) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";
	int n;
	fin >> n;
	fin.close();

	return n;
}

int* get_array(const char* filename) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";

	int* arr = new int[100];
	int k;
	int n = 0;
	fin >> k;
	arr[n] = k;

	while (fin >> k) {
		n++;
		arr[n] = k;
	}
	fin.close();
	return arr;
}

int* get_array(const char* filename, size_t& size) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";

	int* arr = new int[100];
	int k;
	int n = 0;

	while (fin >> k) {
		arr[n] = k;
		n++;
	}

	fin.close();
	cout << endl;
	size = n;
	return arr;
}

int** get_array(const char* filename, size_t& size, size_t& uCount)
{
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";

	fin >> size >> uCount;

	int** arr = new int* [size];
	for (size_t i = 0; i < size; i++) {
		arr[i] = new int[size];
		for (size_t j = 0; j < size; j++)
			arr[i][j] = 0;
	}

	int x, y, price;
	while (fin >> x >> y >> price) {
		arr[x - 1][y - 1] = price;
		arr[y - 1][x - 1] = price;
	}

	return arr;
}

void put_number(const char* filename, const int number) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << number << endl;
	fout.close();
}

void put_number(const char* filename, const double time) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << time << endl;
	fout.close();
}

void put_number(const char* filename, const double time, const int number) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << time << ' ';
	fout << number << endl;
	fout.close();
}

void put_array(const char* filename, const int* array, const size_t size) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	for (size_t i = 0; i < size; i++)
		fout << array[i] << ' ';
	fout << endl;
	fout.close();
}

void put_number_in_end(const char* filename, const double time, const int number)
{
	assert(filename);
	ofstream fout(filename, ios::app);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << time << ' ';
	fout << number << endl;
	fout.close();

}
void put_number_in_end(const char* filename, const int number)
{
	assert(filename);
	ofstream fout(filename, ios::app);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << number << endl;
	fout.close();

}

void put_array_in_end(const char* filename, const int* array, const size_t size)
{
	assert(filename);
	ofstream fout(filename, ios::app);
	if (!fout.is_open())
		throw "Couldn't open file!";
	for (size_t i = 0; i < size; i++)
		fout << array[i] << ' ';
	fout << endl;
	fout.close();
}
