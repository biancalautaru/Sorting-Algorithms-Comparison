#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cmath>
#include "filegen.hpp"

using namespace std;
using namespace std::chrono;

/////////////////////////sectiunea aceasta de copiat//////////////////////////////////////////
const int RUN = 32;

template <typename T>
void insertionSort(std::vector<T>& v, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        T temp = v[i];
        int j = i - 1;
        while (j >= left && v[j] > temp) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = temp;
    }
}

template <typename T>
void timSort(std::vector<T>& v, int n) {
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
//////////////////////////////////////////////////////////////////////////////////////////



void processFileName(string &filename, int n, int max) { filename += '_' + to_string(n) + '_' + to_string(max); }

string pft(string filename, string type) { filename += '_' + type; return filename; }

int main() {
  int T;

//  int T; // number of tests
//  cout << "enter number of test case files: ";
//  cin >> T;
//  cout << "there will be " << 2 * T << " test files created:\n";
//  cout << T << " files containing int type numbers\n";
//  cout << "and " << T << " files containing float type numbers\n\n";
//  vector<vector<int>> intTests(T, vector<int>());
//  vector<vector<float>> floatTests(T, vector<float>());
//  int ngtmax = 0, nlemax = 0;
//  for (int i = 0; i < T; i++) { // 2 * T files will be created
//    string fileName;			// integers and real numbers
//    int n, max;
//    cout << "enter N and MAX value: ";
//    cin >> n >> max;
//    cout << "enter the file name: ";
//    cin >> fileName;
//	processFileName(fileName, n, max);
//    if (n > max) {
//    	if (ngtmax % 2) {
//    		cout << "tipul de fisier: few unique" << endl;
//            intTests[i] = fewUniqueInt(pft(fileName, "int"), n, max);
//            floatTests[i] = fewUniqueFloat(pft(fileName, "float"), n, max);
//            ngtmax = 0;
//    	}
//        else {
//        	cout << "tipul de fisier: random" << endl;
//            intTests[i] = randomInt(pft(fileName, "int"), n, max);
//            floatTests[i] = randomFloat(pft(fileName, "float"), n, max);
//            ngtmax = 1;
//        }
//    }
//    else { // if n <= max
//		if (nlemax % 4 == 0) {
//            cout << "tipul de fisier: random" << endl;
//            intTests[i] = randomInt(pft(fileName, "int"), n, max);
//            floatTests[i] = randomFloat(pft(fileName, "float"), n, max);
//    		nlemax++;
//		}
//    	else if (nlemax % 4 == 1) {
//            cout << "tipul de fisier: few unique" << endl;
//            intTests[i] = fewUniqueInt(pft(fileName, "int"), n, max);
//            floatTests[i] = fewUniqueFloat(pft(fileName, "float"), n, max);
//            nlemax++;
//    	}
//        else if (nlemax % 4 == 2) {
//        	cout << "tipul de fisier: reversed" << endl;
//            intTests[i] = reversedInt(pft(fileName, "int"), n, max);
//            floatTests[i] = reversedFloat(pft(fileName, "float"), n, max);
//        	nlemax++;
//        }
//        else if (nlemax % 4 == 3) {
//        	cout << "tipul de fisier: almost sorted" << endl;
//        	intTests[i] = almostSortedInt(pft(fileName, "int"), n, max);
//            floatTests[i] = almostSortedFloat(pft(fileName, "float"), n, max);
//        	nlemax = 0;
//        }
//    }
//    cout << '\n';
//  }
  return 0;
}