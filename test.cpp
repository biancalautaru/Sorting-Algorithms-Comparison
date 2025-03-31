//
// Created by cocum on 3/30/2025.
//
#include <iostream>
#include <string>
#include <algorithm>
#include "filegen.hpp"

#include <cmath>
#include <iomanip>
using namespace std;

//----------------------Merge Sort--------------------------//
void merge(vector<int> &v, int left, int mid, int right) {
    int n1 = mid - left + 1; // length of 1st aux vector
    int n2 = right - mid; // length of 2nd aux vector
    vector<int> L(n1), R(n2); // auxiliary vectors

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

void mergeSort(vector<int> &v, int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) >> 1;
    mergeSort(v, left, mid);
    mergeSort(v, mid + 1, right);
    merge(v, left, mid, right);
}
//----------------------------------------------------------//

//-------------------------Shell Sort--------------------------//
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
//----------------------------------------------------------//

int main() {
    string fileName;
    // cin >> fileName;
    vector<int> foo = randomInt("testMerge", 100, 1000);
    mergeSort(foo, 0, foo.size() - 1);
    for (int i = 0; i < foo.size(); i++)
        cout << foo[i] << " ";
    cout << endl;
    cout << endl;

    cout << fixed << setprecision(3);
    vector<float> bar = randomFloat("testShell", 100, 1000.0f);
    shellSort(bar);
    for (int i = 0; i < bar.size(); i++)
        cout << bar[i] << " ";
    return 0;
}