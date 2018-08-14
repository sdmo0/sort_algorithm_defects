#include <vector>
#include <iostream>

#include <stdlib.h>
#include <time.h>

#define MAX_TEST 10

// Counting Sort
std::vector<int> CountingSort(std::vector<int> V) {
	//std::vector<int> counting_array(V.size() + 10, 0);
	std::vector<int> counting_array(101, 0); // fixed
	for (int i = 0; i < static_cast<int>(V.size()); ++i) {
		++counting_array[V[i]];
	}

	std::vector<int> sorted_array;
	for (int i = 0; i < static_cast<int>(counting_array.size()); ++i) {
		for (int j = 0; j < counting_array[i]; ++j) {
			sorted_array.push_back(i);
		}
	}

	return sorted_array;
}

// Insertion Sort
std::vector<int> InsertionSort(std::vector<int> V) {
	bool is_array_sorted = true;
	for (int i = 0; i < static_cast<int>(V.size()) - 1; ++i) {
		if (V[i] > V[i + 1]) {
			is_array_sorted = false;
			break;
		}
	}

	if (is_array_sorted) {
		return V;
	}

	for (int i = 0; i < static_cast<int>(V.size()) - 1; ++i) {
		//int min_index = 0;
		int min_index = i; //fixed
		for (int j = i; j < static_cast<int>(V.size()); ++j) {
			if (V[min_index] > V[j]) {
				min_index = j;
			}
		}
		int temp = V[min_index];
		V[min_index] = V[i];
		V[i] = temp;
	}

	return V;
}

// Quick Sort
std::vector<int> FilterLessThan(std::vector<int> V, int pivot) {
	std::vector<int> result;

	for (int elem : V) {
		if (elem < pivot) {
			result.push_back(elem);
		}
	}

	return result;
}

std::vector<int> FilterGreaterThan(std::vector<int> V, int pivot) {
	std::vector<int> result;

	for (int elem : V) {
		//if (elem > pivot) {
		if (elem >= pivot) { // fixed
			result.push_back(elem);
		}
	}
	return result;
}

std::vector<int> QuickSort(std::vector<int> V) {
	if (static_cast<int>(V.size()) <= 1) {
		return V;
	}

	int pivot = V.back();
	V.pop_back();

	std::vector<int> result;
	for (int elem : QuickSort(FilterLessThan(V, pivot))) {
		result.push_back(elem);
	}
	result.push_back(pivot);
	for (int elem : QuickSort(FilterGreaterThan(V, pivot))) {
		result.push_back(elem);
	}

	return result;
}

///////////////////////////////////////////////////////////

void print_vector(std::vector<int> V)
{
	for (int i = 0; i < static_cast<int>(V.size()); i++)
		std::cout << V[i] << ' ';
	std::cout << std::endl;
}

bool compare_vector(std::vector<int> a, std::vector<int> b)
{
	if (a.size() != b.size()) return false;

	for (int i = 0; i < static_cast<int>(a.size()); i++) {
		if (a[i] != b[i]) return false;
	}

	return true;
}

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int positive_rand(void)
{
	int rand_num = rand();
	rand_num = rand_num >= 0 ? rand_num % 101 : (-rand_num) % 101;

	return rand_num;
}

void main(void)
{
	std::vector<int> v1;
	std::vector<int> v2;

	std::vector<int> ans1;
	std::vector<int> ans2;

	int fail_count = 0;
	bool success = false;

	srand(time(NULL));

	for (int i = 0; i < MAX_TEST; i++) {

		int num_count1 = positive_rand();
		int num_count2 = positive_rand();

		for (int i = 0; i < num_count1; i++) {
			int temp = rand();
			temp = temp >= 0 ? temp % 101 : (-temp) % 101;
			v1.push_back(temp);
			ans1.push_back(temp);
		}

		for (int i = 0; i < num_count2; i++) {
			int temp = rand();
			temp = temp >= 0 ? temp % 101 : (-temp) % 101;
			v2.push_back(temp);
			ans2.push_back(temp);
		}

		qsort(ans1.data(), ans1.size(), sizeof(int), compare);
		qsort(ans2.data(), ans2.size(), sizeof(int), compare);

		std::string str;

		printf("##############################################################\n");
		printf("## Test case No. %3d: (v1: %3d numbers, v2: %3d numbers)    ##\n", i, num_count1, num_count2);
		printf("##############################################################\n");
		
		// CountingSort
		std::vector<int>result = CountingSort(v1);
		success = compare_vector(ans1, result);
		if (!success) fail_count++;
		printf("CountSort(v1): %s\n", success ? "succeed" : "fail");

		result = CountingSort(v2);
		success = compare_vector(ans2, result);
		if (!success) fail_count++;
		printf("CountSort(v2): %s\n", success ? "succeed" : "fail");

		// InsertionSrot
		result = InsertionSort(v1);
		success = compare_vector(ans1, result);
		if (!success) fail_count++;
		printf("InsertionSort(v1): %s\n", success ? "succeed" : "fail");

		result = InsertionSort(v2);
		success = compare_vector(ans2, result);
		if (!success) fail_count++;
		printf("InsertionSort(v2): %s\n", success ? "succeed" : "fail");

		// QuickSrot
		result = QuickSort(v1);
		success = compare_vector(ans1, result);
		if (!success) fail_count++;
		printf("QuickSort(v1): %s\n", success ? "succeed" : "fail");

		result = QuickSort(v2);
		success = compare_vector(ans2, result);
		if (!success) fail_count++;
		printf("QuickSort(v2): %s\n", success ? "succeed" : "fail");
	}

	printf("##############################################################\n");
	printf("## Test fail counts: %3d                                    ##\n", fail_count);
	printf("##############################################################\n");
}