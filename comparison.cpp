#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
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

int pivotRandom(vector<int> &v, int st, int dr) {
	srand(time(NULL));
	return st + rand() % (dr - st + 1);
}

void quickSortPivotRandom(vector<int> &v, int st, int dr) {
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

bool isSorted(vector<int> &v) {
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

	for (int fileNumber = 1; fileNumber <= 20; fileNumber++) {
		if (fileNumber == 1)
			fout << "                       - Random -\n\n";
		else if (fileNumber == 6) {
			fout << "-------------------------------------------------------\n\n";
			fout << "                     - Few Unique -\n\n";
		}
		else if (fileNumber == 11) {
			fout << "-------------------------------------------------------\n\n";
			fout << "                    - Almost Sorted -\n\n";
		}
		else if (fileNumber == 16) {
			fout << "-------------------------------------------------------\n\n";
			fout << "                      - Reversed -\n\n";
		}

		inputFile = "test" + to_string(1) + ".txt";
		ifstream fin(inputFile);
		fout << "------------------------ Test " << fileNumber << " ----------------------";
		if (fileNumber < 10)
			fout << "-\n\n";
		else
			fout << "\n\n";

		fin >> n >> maxi;
		fout << "                         N = " << n << "\n";
		fout << "                       Max = " << maxi << "\n\n";
		a.clear();
		for (int i = 0; i < n; i++) {
			fin >> x;
			a.push_back(x);
		}

		v = a;
		start_time = chrono::high_resolution_clock::now();
		heapSort(v);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "                        Heap Sort: " << time.count() << " secunde\n";
		else
			fout << "Heap Sort nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		quickSortMedianaDin3(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "Quick Sort cu pivot mediana din 3: " << time.count() << " secunde\n";
		else
			fout << "Quick Sort cu pivot mediana din 3 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		quickSortPivotRandom(v, 0, n - 1);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "       Quick Sort cu pivot random: " << time.count() << " secunde\n";
		else
			fout << "Quick Sort cu pivot random nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 10);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "            Radix Sort in baza 10: " << time.count() << " secunde\n";
		else
			fout << "Radix Sort in baza 10 nu a sortat corect numerele!\n";

		v = a;
		start_time = chrono::high_resolution_clock::now();
		radixSort(v, 65536);
		end_time = chrono::high_resolution_clock::now();
		time = end_time - start_time;
		if (isSorted(v))
			fout << "          Radix Sort in baza 2^16: " << time.count() << " secunde\n";
		else
			fout << "Radix Sort in baza 2^16 nu a sortat corect numerele!\n";

		fout << "\n";
	}
	fout << "-------------------------------------------------------\n";
	return 0;
}