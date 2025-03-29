#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

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

int pivot(vector<int> &v, int st, int dr) {
	int di = 0;
	int dj = 1;
	while (st < dr) {
		if (v[st] > v[dr]) {
			swap(v[st], v[dr]);
			swap(di, dj);
		}
		st += di;
		dr -= dj;
	}
	return st;
}

int randomPivot(vector<int> &v, int st, int dr) {
	srand(time(NULL));
	int p = st + rand() % (dr - st + 1);
	int val = v[p];
	swap(v[p], v[dr]);
	int i = st - 1;
	for (int j = st; j < dr; j++)
		if (v[j] < val) {
			i++;
			swap(v[i], v[j]);
		}
	swap(v[i + 1], v[dr]);
	return i + 1;
}

void quickSort(vector<int> &v, int st, int dr) {
	if (st < dr) {
		int p = pivot(v, st, dr);
		quickSort(v, st, p - 1);
		quickSort(v, p + 1, dr);
	}
}

void quickSortRandomPivot(vector<int> &v, int st, int dr) {
	if (st < dr) {
		int p = randomPivot(v, st, dr);
		quickSortRandomPivot(v, st, p - 1);
		quickSortRandomPivot(v, p + 1, dr);
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
	for (long long exp = 1; maxi / exp > 0; exp *= base)
		countingSort(v, exp, base);
}

int main() {
	int n, maxi, x;
	vector<int> a, v;
	chrono::time_point<chrono::system_clock> start_time, end_time;
	chrono::duration<double> time;

	fin >> n >> maxi;
	fout << "  N = " << n << "\n";
	fout << "Max = " << maxi << "\n";
	for (int i = 0; i < n; i++) {
		fin >> x;
		a.push_back(x);
	}

	fout << fixed << setprecision(10);

	for (int i = 0; i < n; i++)
		v.push_back(a[i]);
	start_time = chrono::high_resolution_clock::now();
	heapSort(v);
	end_time = chrono::high_resolution_clock::now();
	time = end_time - start_time;
	fout << "                 Heap Sort:  " << time.count() << " secunde\n";

	v.clear();
	for (int i = 0; i < n; i++)
		v.push_back(a[i]);
	start_time = chrono::high_resolution_clock::now();
	quickSort(v, 0, n - 1);
	end_time = chrono::high_resolution_clock::now();
	time = end_time - start_time;
	fout << "                Quick Sort:  " << time.count() << " secunde\n";

	v.clear();
	for (int i = 0; i < n; i++)
		v.push_back(a[i]);
	start_time = chrono::high_resolution_clock::now();
	quickSortRandomPivot(v, 0, n - 1);
	end_time = chrono::high_resolution_clock::now();
	time = end_time - start_time;
	fout << "Quick Sort cu pivot random:  " << time.count() << " secunde\n";

	v.clear();
	for (int i = 0; i < n; i++)
		v.push_back(a[i]);
	start_time = chrono::high_resolution_clock::now();
	radixSort(v, 10);
	end_time = chrono::high_resolution_clock::now();
	time = end_time - start_time;
	fout << "     Radix Sort in baza 10:  " << time.count() << " secunde\n";

	v.clear();
	for (int i = 0; i < n; i++)
		v.push_back(a[i]);
	start_time = chrono::high_resolution_clock::now();
	radixSort(v, 65536);
	end_time = chrono::high_resolution_clock::now();
	time = end_time - start_time;
	fout << "   Radix Sort in baza 2^16:  " << time.count() << " secunde\n";
	return 0;
}