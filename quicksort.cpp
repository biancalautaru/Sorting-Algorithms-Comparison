#include <fstream>
#include <vector>
#include <random>
using namespace std;
ifstream fin("quick_sort.in");
ofstream fout("quick_sort.out");

// var 1
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

// var 2
// int randomPivot(vector<int> &v, int st, int dr) {
// 	srand(time(NULL));
// 	int p = st + rand() % (dr - st + 1);
// 	int val = v[p];
// 	swap(v[p], v[dr]);
// 	int i = st - 1;
// 	for (int j = st; j < dr; j++)
// 		if (v[j] < val) {
// 			i++;
// 			swap(v[i], v[j]);
// 		}
// 	swap(v[i + 1], v[dr]);
// 	return i + 1;
// }

void quickSort(vector<int> &v, int st, int dr) {
	if (st < dr) {
		int p = pivot(v, st, dr); // var 1
		// int p = randomPivot(v, st, dr); // var 2
		quickSort(v, st, p - 1);
		quickSort(v, p + 1, dr);
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
	quickSort(v, 0, n - 1);
	for (int i = 0; i < n; i++)
		fout << v[i] << " ";
	return 0;
}