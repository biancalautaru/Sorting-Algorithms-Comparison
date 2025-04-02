#ifndef FILEGEN_HPP
#define FILEGEN_HPP

#include <vector>
#include <string>

///----------------------------------------------------------------------///
/// it is assumed that for the "Reversed" and "Almost Sorted" generators,///
///     argument 'max' will always have a greater value than 'n'         ///
///----------------------------------------------------------------------///

///     generates a set of 'n' random integers;
/// the integers are all from the [0, max] interval,
/// where 'max' is the biggest (implicitly, for negative numbers, the smallest)
///                    value that can be possibly generated.
std::vector<int> randomInt(std::string fileName, int n, int max);

/// same logic applied for the randomInt generator, but with real (float) numbers
std::vector<float> randomFloat(std::string fileName, int n, float max);

///---------------------------------------------------------------------------------

///     generates a set of 'n' repetitive integers,
/// having hardcoded a number of n / log(n) unique numbers
/// that are from the [0, max] interval;
template <typename T>
std::vector<T> fewUnique(std::string fileName, int n, T max);

///---------------------------------------------------------------------------------

///     generates a set of 'n' sorted integers,
/// but in a reversed order, starting from
/// an arbitrary number close to 'max', and them
/// gradually decreasing the value of each element.
std::vector<int> reversedInt(std::string fileName, int n, int max);

/// same logic applied for the reversedInt generator, but with real numbers
std::vector<float> reversedFloat(std::string fileName, int n, float max);

///---------------------------------------------------------------------------------

///     after having determined the number of swaps needed,
/// a simple ascending sorted vector is generated, after which
/// as many swaps of closely-positioned elements as the
/// earlier determined number suggests are made.
std::vector<int> almostSortedInt(std::string fileName, int n, int max);

/// same logic applied for the almostSortedInt generator, but with real numbers
std::vector<float> almostSortedFloat(std::string fileName, int n, float max);

#endif //FILEGEN_HPP

