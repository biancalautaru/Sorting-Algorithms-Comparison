#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include "filegen.hpp"

///--------------------------------------RANDOM-------------------------------------///
std::vector<int> randomInt(std::string fileName, int n, int max) {                  ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<int> v;                                                             ///
    std::uniform_int_distribution<int> dis(0, max);                                 ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(dis(gen));                                                        ///
      file << v[i] << " ";                                                          ///
    }                                                                               ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///
std::vector<float> randomFloat(std::string fileName, int n, float max) {            ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<float> v;                                                           ///
    std::uniform_real_distribution<float> dis(-max, max);                           ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(dis(gen));                                                        ///
      file << v[i] << " ";                                                          ///
    }                                                                               ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///


///------------------------------------FEW UNIQUE-----------------------------------///
template <typename T>                                                               ///
std::vector<T> fewUnique(std::string fileName, int n, T max) {                      ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<T> v;                                                               ///
    std::uniform_real_distribution<float> dis(0, max);                              ///
    int uniqNum = n / log(n);                                                       ///
    T uniq;                                                                         ///
    for (int i = 0; i < uniqNum; i++) {                                             ///
      uniq = dis(gen);                                                              ///
      for(int j = 0; j < n / uniqNum; j++)                                          ///
        v.push_back(uniq);                                                          ///
    }                                                                               ///
    std::shuffle(v.begin(), v.end(), gen);                                          ///                                                                         ///
    for (auto i : v)                                                                ///
      file << i << " ";                                                             ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
  }                                                                                 ///
///---------------------------------------------------------------------------------///


///--------------------------------------REVERSED-----------------------------------///
std::vector<int> reversedInt(std::string fileName, int n, int max) {                ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<int> v;                                                             ///
    int maxDec = max / n, currNum;                                                  ///
    std::uniform_int_distribution<int> dis(maxDec / 2 + maxDec / 4, maxDec);        ///
    currNum = max - dis(gen);                                                       ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(currNum);                                                         ///
      currNum -= dis(gen);                                                          ///
      file << v[i] << " ";                                                          ///
    }                                                                               ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///
std::vector<float> reversedFloat(std::string fileName, int n, float max) {          ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<float> v;                                                           ///
    float maxDec = max / n, currNum;                                                ///
    std::uniform_real_distribution<float> dis(maxDec / 2 + maxDec / 4, maxDec);     ///
    currNum = max - dis(gen);                                                       ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(currNum);                                                         ///
      currNum -= dis(gen);                                                          ///
      file << v[i] << " ";                                                          ///
    }                                                                               ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///


///-----------------------------------ALMOST SORTED---------------------------------///
std::vector<int> almostSortedInt(std::string fileName, int n, int max) {            ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<int> v;                                                             ///
    int maxDiff = max / n, currNum, numOfSwaps = 2 * (n / log(n));                  ///
    std::uniform_int_distribution<int> dis(maxDiff / 2 + maxDiff / 4, maxDiff);     ///
    currNum = dis(gen);                                                             ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(currNum);                                                         ///
      currNum += dis(gen);                                                          ///
    }                                                                               ///
    std::uniform_int_distribution<int> posPicker(0, n - 5); // position picker      ///
    std::uniform_int_distribution<int> swapper(1, 4); // dist. of swapped elements  ///
    for (int i = 0; i < numOfSwaps; i++)                                            ///
      std::swap(v[posPicker(gen)], v[posPicker(gen) + swapper(gen)]);               ///
    for (int i = 0; i < n; i++)                                                     ///
      file << v[i] << " ";                                                          ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///
std::vector<float> almostSortedFloat(std::string fileName, int n, float max) {      ///
    std::ofstream file(fileName);                                                   ///
    file << n << " " << max << "\n";                                                ///
    std::random_device rd;                                                          ///
    std::mt19937 gen(rd());                                                         ///
    std::vector<float> v;                                                           ///
    int numOfSwaps = 2 * (n / log(n));                                              ///
    float currNum, maxDiff = 1.0f * max / n;                                        ///
    std::uniform_real_distribution<float> dis(maxDiff / 2 + maxDiff / 4, maxDiff);  ///
    currNum = dis(gen);                                                             ///
    for (int i = 0; i < n; i++) {                                                   ///
      v.push_back(currNum);                                                         ///
      currNum += dis(gen);                                                          ///
    }                                                                               ///
    std::uniform_int_distribution<int> posPicker(0, n - 5); // position picker      ///
    std::uniform_int_distribution<int> swapper(1, 4); // dist. of swapped elements  ///
    for (int i = 0; i < numOfSwaps; i++) {                                          ///
      int pos = posPicker(gen);                                                     ///
      std::swap(v[pos], v[pos + swapper(gen)]);                                     ///
    }                                                                               ///
    for (int i = 0; i < n; i++)                                                     ///
      file << v[i] << " ";                                                          ///
    file.close();                                                                   ///
    std::cout << "file " << fileName << " succesfully created" << std::endl;        ///
    return v;                                                                       ///
}                                                                                   ///
///---------------------------------------------------------------------------------///

///---------------------------------------------------------------------------------------------------------------------///
void saveResultsToCSV(int fileNumber, const std::string &algorithm, const std::string &vectorType, double timeTaken) {  ///
  	std::string fileName;                                                                                           ///
  	if (fileNumber <= 40)										                ///
		  fileName = "sortingResultsInt.csv";	                                                                ///
  	else													        ///
    	fileName = "sortingResultsFloat.csv";	                                                                        ///
  	std::ofstream file(fileName, std::ios::app);									///
  	if (file.is_open()) {												///
		    file << fileNumber << "," << algorithm << "," << vectorType << "," << timeTaken << "\n";		///
		    file.close();											///
	  }														///
    else {														///
	    std::cout << "File could not be opened\n";									///
  	}														///
}															///
///---------------------------------------------------------------------------------------------------------------------///