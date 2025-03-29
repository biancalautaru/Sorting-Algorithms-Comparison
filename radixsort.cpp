#include <fstream>
#include <vector>
using namespace std;
ifstream fin("radix_sort.in");
ofstream fout("radix_sort.out");

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
	int n;
	fin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int x;
		fin >> x;
		v.push_back(x);
	}
	// radixSort(v, 10); // var 1
	radixSort(v, 65536); // var 2
	for (int i = 0; i < n; i++)
		fout << v[i] << " ";
	return 0;
}