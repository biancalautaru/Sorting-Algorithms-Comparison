#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;


template <typename T>
void heapify(vector<T> &v, int n, int k) {
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

template <typename T>
void buildHeap(vector<T> &v) {
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i);
}

template <typename T>
void heapSort(vector<T> &v) {
	buildHeap(v);
	int n = v.size();
	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}

template <typename T>
int pivotMedianaDin3(vector<T> &v, int st, int dr) {
	int mid = st + (dr - st) / 2;
	if (v[dr] < v[st])
		swap(v[st], v[dr]);
	if (v[mid] < v[st])
		swap(v[st], v[mid]);
	if (v[dr] < v[mid])
		swap(v[mid], v[dr]);
	return mid;
}

template <typename T>
void quickSortMedianaDin3(vector<T> &v, int st, int dr) {
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

template <typename T>
int pivotRandom(vector<T> &v, int st, int dr) {
	srand(time(NULL));
	return st + rand() % (dr - st + 1);
}

template <typename T>
void quickSortPivotRandom(vector<T> &v, int st, int dr) {
	if (st < dr) {
		int p = pivotRandom(v, st, dr);
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

template <typename T>
void countingSort(vector<T> &v, const int exp, const int base) {
	vector<int> f(base, 0);
	for (int i = 0; i < base; i++)
		f[i] = 0;
	for (int i = 0; i < v.size(); i++)
		f[(v[i] / exp) % base]++;
	for (int i = 1; i < base; i++)
		f[i] += f[i - 1];
	vector<int> a(v.size());
	for (int i = v.size() - 1; i >= 0; i--) {
		// cout << f[(v[i] / exp) % base] - 1;
		a[f[(v[i] / exp) % base] - 1] = v[i];
		f[(v[i] / exp) % base]--;
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = a[i];
}

template <typename T>
void radixSort(vector<T> &v, const int base) {
	int maxi = v[0];
	for (int i = 1; i < v.size(); i++)
		maxi = max(maxi, v[i]);
	for (long long exp = 1; exp <= maxi; exp *= base)
		countingSort(v, exp, base);
}

template <typename T>
void merge(vector<T> &v, int left, int mid, int right) {
	int n1 = mid - left + 1; // length of 1st aux vector
	int n2 = right - mid; // length of 2nd aux vector
	vector<T> L(n1), R(n2); // auxiliary vectors

	for (int i = 0; i < n1; i++)
		L[i] = v[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = v[mid + 1 + i];

	// merging the two halfs
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			v[k] = L[i], i++;
		else
			v[k] = R[j], j++;
		k++;
	}

	while (i < n1) // remainder of left side
		v[k] = L[i], i++, k++;
	while (j < n2) // remainder of right side
		v[k] = R[j], j++, k++;
}

template <typename T>
void mergeSort(vector<T> &v, int left, int right) {
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

template <typename T>
void shellSort(vector<T> &v) {
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

template <typename T>
void bubbleSort(vector<T> &v) {
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size() - i - 1; j++)
			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
}

template <typename T>
bool isSorted(vector<T> &v) {
	for (int i = 1; i < v.size(); i++)
		if (v[i - 1] > v[i])
			return false;
	return true;
}

int main() {
	string inputFile;
	ofstream fout("output.txt");
	int n, maxi, x;
	vector<int> a, v;
	chrono::time_point<chrono::system_clock> start_time, end_time;
	chrono::duration<double> time;

	fout << fixed << setprecision(10);

	for (int fileNumber = 1; fileNumber <= 8; fileNumber++) {
		if (fileNumber == 1)
			fout << "                        - Random -\n\n";
		else if (fileNumber == 9) {
			fout << "---------------------------------------------------------\n\n";
			fout << "                      - Few Unique -\n\n";
		}
		else if (fileNumber == 17) {
			fout << "---------------------------------------------------------\n\n";
			fout << "                     - Almost Sorted -\n\n";
		}
		else if (fileNumber == 25) {
			fout << "---------------------------------------------------------\n\n";
			fout << "                       - Reversed -\n\n";
		}

		inputFile = "teste/test" + to_string(fileNumber) + ".txt";
		ifstream fin(inputFile);
		fout << "------------------------- Test " << fileNumber << " -----------------------";
		if (fileNumber < 10)
			fout << "-\n\n";
		else
			fout << "\n\n";

		fin >> n >> maxi;
		fout << "                          N = " << n << "\n";
		fout << "                        Max = " << maxi << "\n\n";
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
		if (isSorted(v))
			fout << "                          STL Sort: " << time.count() << " secunde\n";
		else
			fout << "STL Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		heapSort(v);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "                         Heap Sort: " << time.count() << " secunde\n";
		else
			fout << "Heap Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		quickSortMedianaDin3(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << " Quick Sort cu pivot mediana din 3: " << time.count() << " secunde\n";
		else
			fout << "Quick Sort cu pivot mediana din 3 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		quickSortPivotRandom(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "        Quick Sort cu pivot random: " << time.count() << " secunde\n";
		else
			fout << "Quick Sort cu pivot random nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 10);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "             Radix Sort in baza 10: " << time.count() << " secunde\n";
		else
			fout << "Radix Sort in baza 10 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 65536);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "           Radix Sort in baza 2^16: " << time.count() << " secunde\n";
		else
			fout << "Radix Sort in baza 2^16 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		mergeSort(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "                        Merge Sort: " << time.count() << " secunde\n";
		else
			fout << "Merge Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		shellSort(v);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "                        Shell Sort: " << time.count() << " secunde\n";
		else
			fout << "Shell Sort nu a sortat corect numerele!\n";

		fout << "\n";
	}
	fout << "---------------------------------------------------------\n";
	return 0;
}