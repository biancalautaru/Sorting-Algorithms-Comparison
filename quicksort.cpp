#include <fstream>
#include <vector>
#include <random>
using namespace std;
ifstream fin("quick_sort.in");
ofstream fout("quick_sort.out");

// var 1
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

// var 2
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

int main() {
	int n;
	fin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int x;
		fin >> x;
		v.push_back(x);
	}
	quickSortMedianaDin3(v, 0, n - 1); // var 1
	// quickSortPivotRandom(v, 0, n - 1); // var 2
	for (int i = 0; i < n; i++)
		fout << v[i] << " ";
	return 0;
}