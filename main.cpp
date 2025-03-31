#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cmath>
#include "filegen.hpp"

using namespace std;
using namespace std::chrono;

int main() {
  int T; // number of tests
  cout << "enter number of test case files: ";
  cin >> T;
  cout << endl;

  for (int i = 0; i < T; i++) {
    int n, max;
    cin >> n >> max;
  }

  /// naming the generated files

  string randIntFile, randFloatFile;
  cout << "random integers: ";
  cin >> randIntFile;
  cout << "random floats: ";
  cin >> randFloatFile;

  string fewUniqIntFile, fewUniqFloatFile;
  cout << "few unique integers: ";
  cin >> fewUniqIntFile;
  cout << "few unique floats: ";
  cin >> fewUniqFloatFile;

  string revIntFile, revFloatFile;
  cout << "reversed integers: ";
  cin >> revIntFile;
  cout << "reversed floats: ";
  cin >> revFloatFile;

  string almSortedIntFile, almSortedFloatFile;
  cout << "almost sorted integers: ";
  cin >> almSortedIntFile;
  cout << "almost sorted floats: ";
  cin >> almSortedFloatFile;

  vector<int> randInt = randomInt(randIntFile, );

}