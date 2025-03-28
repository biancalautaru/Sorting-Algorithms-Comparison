#include <fstream>
#include <vector>
using namespace std;
ifstream fin("heap_sort.in");
ofstream fout("heap_sort.out");

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

int main() {
	int n;
	fin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int x;
		fin >> x;
		v.push_back(x);
	}
	heapSort(v);
	for (int i = 0; i < n; i++)
		fout << v[i] << " ";
	return 0;
}