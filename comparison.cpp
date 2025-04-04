#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include "filegen.hpp"
using namespace std;

void heapify(vector<int> &v, int n, int k) {
	int st = 2 * k + 1;
	int dr = 2 * k + 2;
	int p = k;
	if (st < n && v[st] > v[p])
		p = st;
	if (dr < n && v[dr] > v[p])
		p = dr;
	if (p != k) {
		swap(v[k], v[p]);
		heapify(v, n, p);
	}
}

void buildHeap(vector<int> &v) {
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i);
}

void heapSort(vector<int> &v) {
	buildHeap(v);
	int n = v.size();
	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}

int pivotMedianaDin3(vector<int> &v, int st, int dr) {
	int mid = st + (dr - st) / 2;
	if (v[dr] < v[st])
		swap(v[st], v[dr]);
	if (v[mid] < v[st])
		swap(v[st], v[mid]);
	if (v[dr] < v[mid])
		swap(v[mid], v[dr]);
	return mid;
}

void quickSortMedianaDin3(vector<int> &v, int st, int dr) {
	if (st < dr) {
		int p = pivotMedianaDin3(v, st, dr);
		int val = v[p];
		swap(v[p], v[dr]);
		int i = st - 1;
		for (int j = st; j < dr; j++)
			if (v[j] < val) {
				i++;
				swap(v[i], v[j]);
			}
		swap(v[i + 1], v[dr]);
		quickSortMedianaDin3(v, st, i);
		quickSortMedianaDin3(v, i + 2, dr);
	}
}

int pivotRandom(int st, int dr) {
	srand(time(NULL));
	return st + rand() % (dr - st + 1);
}

void quickSortPivotRandom(vector<int> &v, int st, int dr) {
	if (st < dr) {
		int p = pivotRandom(st, dr);
		int val = v[p];
		swap(v[p], v[dr]);
		int i = st - 1;
		for (int j = st; j < dr; j++)
			if (v[j] < val) {
				i++;
				swap(v[i], v[j]);
			}
		swap(v[i + 1], v[dr]);
		quickSortPivotRandom(v, st, i);
		quickSortPivotRandom(v, i + 2, dr);
	}
}

void countingSort(vector<int> &v, const int exp, const int base) {
	vector<int> f(base, 0);
	for (int i = 0; i < base; i++)
		f[i] = 0;
	for (int i = 0; i < v.size(); i++)
		f[(v[i] / exp) % base]++;
	for (int i = 1; i < base; i++)
		f[i] += f[i - 1];
	vector<int> a(v.size());
	for (int i = v.size() - 1; i >= 0; i--) {
		a[f[(v[i] / exp) % base] - 1] = v[i];
		f[(v[i] / exp) % base]--;
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = a[i];
}

void radixSort(vector<int> &v, const int base) {
	int maxi = v[0];
	for (int i = 1; i < v.size(); i++)
		maxi = max(maxi, v[i]);
	for (long long exp = 1; exp <= maxi; exp *= base)
		countingSort(v, exp, base);
}

void merge(vector<int> &v, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = v[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = v[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			v[k] = L[i], i++;
		else
			v[k] = R[j], j++;
		k++;
	}

	while (i < n1)
		v[k] = L[i], i++, k++;
	while (j < n2)
		v[k] = R[j], j++, k++;
}

void mergeSort(vector<int> &v, int left, int right) {
	if (left >= right)
		return;

	int mid = (left + right) >> 1;
	mergeSort(v, left, mid);
	mergeSort(v, mid + 1, right);
	merge(v, left, mid, right);
}

vector<int> generateTokudaSeq(int n) {
	vector<int> gaps;
	int k = 1;
	while (true) {
		int gap = ceil((pow(9, k) - pow(4, k)) / (5 * pow(4, k - 1)));
		if (gap >= n) break;
		gaps.push_back(gap);
		k++;
	}
	reverse(gaps.begin(), gaps.end());
	return gaps;
}

void shellSort(vector<int> &v) {
	int n = v.size();
	vector<int> gaps = generateTokudaSeq(n);

	for (int gap : gaps) {
		for (int i = gap; i < n; i++) {
			float aux = v[i];
			int j = i;
			while (j >= gap && v[j - gap] > aux) {
				v[j] = v[j - gap];
				j -= gap;
			}
			v[j] = aux;
		}
	}
}

void bubbleSort(vector<int> &v) {
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size() - i - 1; j++)
			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
}

void insertionSort(std::vector<int>& v, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int temp = v[i];
		int j = i - 1;
		while (j >= left && v[j] > temp) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = temp;
	}
}

void timSort(std::vector<int>& v, int n, const int RUN) {
	for (int i = 0; i < n; i += RUN) {
		insertionSort(v, i, std::min(i + RUN - 1, n - 1));
	}
	for (int size = RUN; size < n; size = 2 * size) {
		for (int left = 0; left < n; left += 2 * size) {
			int mid = left + size - 1;
			int right = std::min(left + 2 * size - 1, n - 1);
			if (mid < right)
				merge(v, left, mid, right);
		}
	}
}

bool isSorted(vector<int> &v) {
	for (int i = 1; i < v.size(); i++)
		if (v[i - 1] > v[i])
			return false;
	return true;
}

int main() {
	int testsType, firstFile, lastFile;

	cout << "1. random\n2. few unique\n3. reversed\n4. almost sorted\n";
	cin >> testsType;

	if (testsType == 1) {
		firstFile = 1;
		lastFile = 10;
	}
	else
		if (testsType == 2) {
			firstFile = 11;
			lastFile = 20;
		}
		else
			if (testsType == 3) {
				firstFile = 21;
				lastFile = 30;
			}
			else
				if (testsType == 4) {
					firstFile = 31;
					lastFile = 40;
				}

	string outputFile, vectorType;

	if (testsType == 1)
		outputFile = "results/resultsRandom.txt", vectorType = "Random";
	else
		if (testsType == 2)
			outputFile = "results/resultsFewUnique.txt", vectorType = "Few Unique";
		else
			if (testsType == 3)
				outputFile = "results/resultsReversed.txt", vectorType = "Reversed";
			else
				outputFile = "results/resultsAlmostSorted.txt", vectorType = "Almost Sorted";

	ofstream fout(outputFile);
	fout << fixed << setprecision(10);

	string inputFile;
	int n, maxi, x;
	vector<int> a, v;
	chrono::time_point<chrono::system_clock> start_time, end_time;
	chrono::duration<double> time;

	for (int fileNumber = firstFile; fileNumber <= lastFile; fileNumber++) {
		fout << "-------------------------- Test " << fileNumber << " ----------------------";
		if (fileNumber < 10)
			fout << "-\n\n";
		else
			fout << "\n\n";

		inputFile = "tests/test" + to_string(fileNumber) + ".txt";
		ifstream fin(inputFile);

		fin >> n >> maxi;
		fout << "                           N = " << n << "\n";
		fout << "                         Max = " << maxi << "\n\n";
		a.clear();
		for (int i = 0; i < n; i++) {
			fin >> x;
			a.push_back(x);
		}

		v = a;
		start_time = chrono::high_resolution_clock::now();
		sort(v.begin(), v.end());
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "                         STL Sort: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "STL Sort", vectorType, time.count());
		}
		else
			fout << "STL Sort nu a sortat corect numerele!\n";

		if (n <= 100000) {
			v = a;
			start_time = chrono::high_resolution_clock::now();
			bubbleSort(v);
			end_time = chrono::high_resolution_clock::now();
			time = end_time - start_time;
			if (isSorted(v)) {
				fout << "                      Bubble Sort: ";
				if (time.count() < 10)
					fout << " ";
				if (time.count() < 100)
					fout << " ";
				fout << time.count() << " secunde\n";
				saveResultsToCSV(fileNumber, "Bubble Sort", vectorType, time.count());
			}
			else
				fout << "Bubble Sort nu a sortat corect numerele!\n";
		}

		if (testsType == 1 || testsType == 4 || n <= 100000) {
			v = a;
			start_time = chrono::high_resolution_clock::now();
			quickSortMedianaDin3(v, 0, n - 1);
			end_time = chrono::high_resolution_clock::now();
			time = end_time - start_time;
			if (isSorted(v)) {
				fout << "Quick Sort cu pivot mediana din 3: ";
				if (time.count() < 10)
					fout << " ";
				if (time.count() < 100)
					fout << " ";
				fout << time.count() << " secunde\n";
				saveResultsToCSV(fileNumber, "Quick Sort pivot 3", vectorType, time.count());
			}
			else
				fout << "Quick Sort cu pivot mediana din 3 nu a sortat corect numerele!\n";

			v = a;
			start_time = chrono::high_resolution_clock::now();
			quickSortPivotRandom(v, 0, n - 1);
			end_time = chrono::high_resolution_clock::now();
			time = end_time - start_time;
			if (isSorted(v)) {
				fout << "       Quick Sort cu pivot random: ";
				if (time.count() < 10)
					fout << " ";
				if (time.count() < 100)
					fout << " ";
				fout << time.count() << " secunde\n";
				saveResultsToCSV(fileNumber, "Quick Sort pivot random", vectorType, time.count());
			}
			else
				fout << "Quick Sort cu pivot random nu a sortat corect numerele!\n";
		}

		v = a;
		start_time = chrono::high_resolution_clock::now();
		heapSort(v);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "                        Heap Sort: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Heap Sort", vectorType, time.count());
		}
		else
			fout << "Heap Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		mergeSort(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "                       Merge Sort: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Merge Sort", vectorType, time.count());
		}
		else
			fout << "Merge Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 10);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "            Radix Sort in baza 10: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Radix Sort base 10", vectorType, time.count());
		}
		else
			fout << "Radix Sort in baza 10 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 65536);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "          Radix Sort in baza 2^16: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Radix Sort base 2^16", vectorType, time.count());
		}
		else
			fout << "Radix Sort in baza 2^16 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		shellSort(v);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "                       Shell Sort: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Shell Sort", vectorType, time.count());
		}
		else
			fout << "Shell Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		timSort(v, n, 32);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v)) {
			fout << "                         Tim Sort: ";
			if (time.count() < 10)
				fout << " ";
			if (time.count() < 100)
				fout << " ";
			fout << time.count() << " secunde\n";
			saveResultsToCSV(fileNumber, "Tim Sort", vectorType, time.count());
		}
		else
			fout << "Tim Sort nu a sortat corect numerele!\n";
		fout << "\n";

		cout << "test" << fileNumber << " finalizat!\n";
	}
	return 0;
}