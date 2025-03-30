#include "filegen.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

///------------------Random------------------///
std::vector<int> randomInt(const std::string &fileName, int n, int max) {
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> v;
    std::uniform_int_distribution<int> dis(-max, max);
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
  std::uniform_int_distribution<int> dis(-max, max);
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
  int maxDec = max / n, currNum = max - maxDec / 2;
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
  float maxDec = max / n, currNum = max - maxDec / 2;
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
std::vector<int> almostSortedInt(const std::string &fileName, int n, int max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> v;
  int maxDiff = max / n;
  std::uniform_int_distribution<int> dis(-(maxDiff), maxDiff;
  for (int i = 0; i < n; i++) {
    v.push_back();
  }
}

std::vector<float> almostSortedFloat(const std::string &fileName, int n, float max) {
  std::ofstream file(fileName);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<float> v;
  int maxDiff = max / n;
  for (int i = 0; i < n; i++) {
    v.push_back();
  }
}

///----------------------------------------------------///