#include "sort.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define ARRAY_SIZE 1000
#define MIN_M 5
#define MAX_M 250

#define ARRAY_FILENAME "../array.txt"
#define QSORT_FILENAME "../qsort.txt"

using namespace std;
using namespace std::chrono;

void assert_sorted(int* array)
{
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        if (array[i] < array[i-1]) throw std::exception();
    }
}

int main()
{
    int baseArray[ARRAY_SIZE], array[ARRAY_SIZE];
    ifstream fin(ARRAY_FILENAME);
    if (fin.good())
    {
        for (int i = 0; i < ARRAY_SIZE; i++) fin >> baseArray[i];
    }
    fin.close();

    ofstream fout(QSORT_FILENAME);
    if (fout.good())
    {
        for (int m = MIN_M; m <= MAX_M; m++)
        {
            for (int i = 0; i < ARRAY_SIZE; i++) array[i] = baseArray[i];

            auto startTime = steady_clock::now();
            my_qsort<int>(array, array + ARRAY_SIZE, [](int a, int b) { return a < b; }, m);
            auto endTime = steady_clock::now();

            assert_sorted(array);
            fout << m << ' ' << duration_cast<microseconds>(endTime - startTime).count() << '\n';
        }

        fout.close();
    }
}