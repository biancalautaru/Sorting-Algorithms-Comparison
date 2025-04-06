# 📌 Sorting Algorithms Comparison
*(project by Lăutaru Bianca-Maria and Cocu Matei-Iulian)*

The following **C++ implementation** provides a few different approaches on sorting various types of numerical vectors, alongside a source file that implements the **generation of the numbers** used.

---

## 📑 Table of Contents
1. [📂 Number Generator](#-number-generator)
2. [📊 Sorting Algorithms](#-sorting-algorithms)
3. [🔧 Main Function - I/O Interface](#-main-function)

---

## 📂 Number Generator
Implemented in a separate source file (`filegen.cpp`) and linked through its header file (`filegen.hpp`), the number generator is implemented using the `<random>` library, available after **C++11**.

The **inclusive template** for these generator functions (`generationtypeValuetype`) has **three parameters**:
- The name of the file where the numbers will be written (**`std::string`**).
- The amount of numbers the file will contain.
- The **maximum value** the numbers can take:
    - **Integers**: only positive values (**`[0, max]`** range).
    - **Real numbers**: may have negative values (**`[-max, max]`** range), but only for the **Random Generator**.

Apart from returning a `vector<>`, the function also generates the file itself, writing down all generated numbers.

Using the **Mersenne Twister 19937 generator (`mt19937`)**, an instantiation of `mersenne_twister_engine`, **four types** of files are generated (for both **integers** and **real numbers**):

### 🛠 Types of Number Generation
1️⃣ **Randomly Generated Numbers**
- Uses `mt19937` to generate numbers with as many unique values as possible.
- Recommended to have `n` significantly larger than `max` for better randomness.

2️⃣ **Few Unique Numbers**
- Uses `n / log(n)` unique numbers.
- Repeats numbers in clusters.
- The final vector is randomly shuffled.

3️⃣ **Numbers in Reversed Order**
- Generates values close to `max`, then sorts them **in descending order**.
- Maximum decrement: `max / n` (assuming `max > n`).

4️⃣ **Almost Sorted Numbers**
- Generates an already **sorted array**.
- Performs `n / log(n)` swaps **between closely-positioned numbers**.

---

## 📊 Sorting Algorithms

### 🔹 STL Sort
> Uses **IntroSort**, a hybrid sorting algorithm combining:
- **QuickSort** (for fast average-case performance).
- **HeapSort** (to avoid QuickSort's worst-case `O(n^2)`).
- **InsertionSort** (for small nearly sorted subarrays).

### 🔹 Bubble Sort
> The classic **`O(n^2)`** comparison-based algorithm.
- Implemented **only for small `n` values**.
- Demonstrates the **difference between `O(nlog(n))` and quadratic complexity**.

### 🔹 Quick Sort
> Two implementations:
- **Median-of-3 Pivot**: Statistically, this pivot selection (`mid = st + (dr - st) / 2`) is good because it avoids worst-case scenarios that occur with simple first/last element pivoting, it's *deterministic*, it works well on *partially sorted data-sets*, and, as for the implementation, overall, it's simply easier to understand than other more complex pivot selection strategies.
- **Random Pivot**: Picks **a pseudo-random pivot**; while performance may vary across different runs on a single data-set (introducing the concept of *non-determinism*), the random pivot selection makes the *worst-case scenario* extremely unlikely (this probability gets *significantly smaller* as `n` increases);

📝 **Observation**: The **1st** implementation is **at most times faster** than the **2nd**.

### 🔹 Heap Sort
- **Worst-case complexity** `O(nlog(n))` (better than QuickSort).
- **Poor cache performance**.

### 🔹 Merge Sort
> Uses **Divide & Conquer**:
- Recursively **splits** the array into halves until **base case (1 element)**.
- Merges and sorts subarrays **recursively**.
- **More efficient than HeapSort for large datasets**.
- **Easily parallelizable**.

### 🔹 Tim Sort
> **MergeSort-inspired hybrid algorithm**:
- Divides array into **small chunks (`runs`)**.
- Uses **InsertionSort** on each chunk.
- **Better than MergeSort** for certain cases.

### 🔹 Shell Sort
> **Improved version of InsertionSort**:
- Uses **decreasing interval sorting**.
- **Not stable**.
- **Poor worst-case time complexity**.
- Uses **Tokuda’s gap sequence** (one of the best practical choices).
- **Not easily parallelizable**.

### 🔹 Radix Sort
> **Fastest sorting algorithm implemented**:
- **Base-10 Radix Sort**: Best for **small `max` values**.
- **Base-65536 Radix Sort (`2^16`)**: Performs **better as `max` increases**.

⚠️ **Limitation**: Cannot directly sort **real numbers** unless they have a finite decimal representation.

---

## 🔧 Main Function

### ⚙️ Execution Flow
1️⃣ **User selects a test type** (Random, Few Unique, Reversed, Almost Sorted).

2️⃣ **Reads test files** (`tests/testX.txt`) and extracts values.

3️⃣ **Sorts the data using multiple algorithms**.

4️⃣ **Measures execution time**.

5️⃣ **Validates correctness** using `isSorted()`.

6️⃣ **Saves results** to output files.

### 📂 File Naming Convention
- **Input files**: `tests/testX.txt`
- **Output files**:
    - `results/resultsRandom.txt`
    - `results/resultsFewUnique.txt`
    - `results/resultsReversed.txt`
    - `results/resultsAlmostSorted.txt`
- **CSV File**: Stores execution times per test.

---
