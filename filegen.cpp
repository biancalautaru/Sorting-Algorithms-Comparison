#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include "filegen.hpp"

///------------------Random------------------///
std::vector<int> randomInt(const std::string &fileName, int n, int max) {
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> v;
    std::uniform_int_distribution<int> dis(0, max);
    for (int i = 0; i < n; i++) {
      v.push_back(dis(gen));
      file << v[i] << " ";
    }
    file.close();
    return v;
}

std::vector<float> randomFloat(const std::string &fileName, int n, float max) {
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<float> v;
    std::uniform_real_distribution<float> dis(-max, max);
    for (int i = 0; i < n; i++) {
      v.push_back(dis(gen));
      file << v[i] << " ";
    }
  file.close();
  return v;
}
///------------------------------------------///

///---------------------Few Unique---------------------///
std::vector<int> fewUniqueInt(const std::string &fileName, int n, int max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> v;
  std::uniform_int_distribution<int> dis(0, max);
  for (int i = 0; i < 1000; i++) {
    int uniq = dis(gen);
    for(int j = 0; j < n / 1000; j++) {
      v.push_back(uniq);
      file << v[j] << " ";
    }
  }
  file.close();
  return v;
}

std::vector<float> fewUniqueFloat(const std::string &fileName, int n, float max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<float> v;
  std::uniform_real_distribution<float> dis(-max, max);
  for (int i = 0; i < 1000; i++) {
    float uniq = dis(gen);
    for(int j = 0; j < n / 1000; j++) {
      v.push_back(uniq);
      file << v[j] << " ";
    }
  }
  file.close();
  return v;
}
///------------------------------------------///

///-------------------Reversed-----------------------///
std::vector<int> reversedInt(const std::string &fileName, int n, int max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> v;
  int maxDec = max / n, currNum = max;
  std::uniform_int_distribution<int> dis(maxDec / 2 + maxDec / 4, maxDec);
  for (int i = 0; i < n; i++) {
    v.push_back(currNum);
    currNum -= dis(gen);
    file << v[i] << " ";
  }
  file.close();
  return v;
}

std::vector<float> reversedFloat(const std::string &fileName, int n, float max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<float> v;
  float maxDec = max / n, currNum = max;
  std::uniform_real_distribution<float> dis(maxDec / 2 + maxDec / 4, maxDec);
  for (int i = 0; i < n; i++) {
    v.push_back(currNum);
    currNum -= dis(gen);
    file << v[i] << " ";
  }
  file.close();
  return v;
}
///--------------------------------------------------///

///----------------Almost Sorted-----------------------///
int swapDet (int n) {
  int numOfSwaps;
  if (n <= 5000) /// assuming n is always bigger or equal to 1000
    numOfSwaps = n / 100;
  else if (n <= 50000)
    numOfSwaps = n / 250;
  else if (n <= pow(10, 6))
    numOfSwaps = n / 500;
  else if (n <= pow(10, 7))
    numOfSwaps = n / 1000;
  else if (n <= pow(10, 8))
    numOfSwaps = n / 5000;
  else if (n <= pow(10, 9))
    numOfSwaps = n / 10000;
  else
    numOfSwaps = n / pow(10, 5);
  return numOfSwaps;
}

std::vector<int> almostSortedInt(const std::string &fileName, int n, int max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> v;
  int maxDiff = max / n, currNum = 0, numOfSwaps = swapDet(n);
  std::uniform_int_distribution<int> dis(maxDiff / 2 + maxDiff / 4, maxDiff); // number iterator
  for (int i = 0; i < n; i++) {
    v.push_back(currNum);
    currNum += dis(gen);
  }
  std::uniform_int_distribution<int> posPicker(0, n - 7); // position picker
  std::uniform_int_distribution<int> swapper(1, 4); // distance of swapped elements
  for (int i = 0; i < numOfSwaps; i++)
    std::swap(v[posPicker(gen)], v[posPicker(gen) + swapper(gen)]);
  for (int i = 0; i < n; i++)
    file << v[i] << " ";
  file.close();
  return v;
}

std::vector<float> almostSortedFloat(const std::string &fileName, int n, float max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<float> v;
  int maxDiff = max / n, currNum = 0, numOfSwaps = swapDet(n);
  std::uniform_real_distribution<float> dis(maxDiff / 2 + maxDiff / 4, maxDiff);
  for (int i = 0; i < n; i++) {
    v.push_back(currNum);
    currNum += dis(gen);
  }
  std::uniform_int_distribution<int> posPicker(0, n - 7); // position picker
  std::uniform_int_distribution<int> swapper(1, 4); // distance of swapped elements
  for (int i = 0; i < numOfSwaps; i++)
    std::swap(v[posPicker(gen)], v[posPicker(gen) + swapper(gen)]);
  for (int i = 0; i < n; i++)
    file << v[i] << " ";
  file.close();
  return v;
}
///----------------------------------------------------///