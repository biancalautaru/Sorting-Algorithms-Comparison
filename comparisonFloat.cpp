#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

void heapify(vector<float> &v, int n, int k) {
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

void buildHeap(vector<float> &v) {
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i);
}

void heapSort(vector<float> &v) {
	buildHeap(v);
	int n = v.size();
	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}

int pivotMedianaDin3(vector<float> &v, int st, int dr) {
	int mid = st + (dr - st) / 2;
	if (v[dr] < v[st])
		swap(v[st], v[dr]);
	if (v[mid] < v[st])
		swap(v[st], v[mid]);
	if (v[dr] < v[mid])
		swap(v[mid], v[dr]);
	return mid;
}

void quickSortMedianaDin3(vector<float> &v, int st, int dr) {
	if (st < dr) {
		int p = pivotMedianaDin3(v, st, dr);
		float val = v[p];
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

void quickSortPivotRandom(vector<float> &v, int st, int dr) {
	if (st < dr) {
		int p = pivotRandom(st, dr);
		float val = v[p];
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

void merge(vector<float> &v, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<float> L(n1), R(n2);

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

void mergeSort(vector<float> &v, int left, int right) {
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

void shellSort(vector<float> &v) {
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

void bubbleSort(vector<float> &v) {
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size() - i - 1; j++)
			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
}

void insertionSort(std::vector<float>& v, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		float temp = v[i];
		int j = i - 1;
		while (j >= left && v[j] > temp) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = temp;
	}
}

void timSort(std::vector<float>& v, int n, const int RUN) {
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

bool isSorted(vector<float> &v) {
	for (int i = 1; i < v.size(); i++)
		if (v[i - 1] > v[i])
			return false;
	return true;
}

int main() {
	int testsType, firstFile, lastFile;

	cout << "1. random\n2. few unique\n3. almost sorted\n4. reversed\n";
	cin >> testsType;

	if (testsType == 1) {
		firstFile = 41;
		lastFile = 50;
	}
	else
		if (testsType == 2) {
			firstFile = 51;
			lastFile = 60;
		}
		else
			if (testsType == 3) {
				firstFile = 61;
				lastFile = 70;
			}
			else
				if (testsType == 4) {
					firstFile = 71;
					lastFile = 80;
				}

	string outputFile;

	if (testsType == 1)
		outputFile = "results/resultsRandomFloat.txt";
	else
		if (testsType == 2)
			outputFile = "results/resultsFewUniqueFloat.txt";
		else
			if (testsType == 3)
				outputFile = "results/resultsAlmostSortedFloat.txt";
			else
				outputFile = "results/resultsReversedFloat.txt";

	ofstream fout(outputFile);
	fout << fixed << setprecision(10);

	string inputFile;
	int n;
    float x, maxi;
	vector<float> a, v;
	chrono::time_point<chrono::system_clock> start_time, end_time;
	chrono::duration<double> time;

	for (int fileNumber = firstFile; fileNumber <= lastFile; fileNumber++) {
		fout << "-------------------------- Test " << fileNumber << " ----------------------\n\n";

		inputFile = "tests/test" + to_string(fileNumber) + ".txt";
		ifstream fin(inputFile);

		fin >> n >> maxi;
		fout << "                           N = " << n << "\n";
		fout << "                         Max = " << int(maxi) << "\n\n";
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
		}
		else
			fout << "Merge Sort nu a sortat corect numerele!\n";

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
		}
		else
			fout << "Tim Sort nu a sortat corect numerele!\n";

		fout << "\n";

		cout << "test" << fileNumber << " finalizat!\n";
	}
	return 0;
}