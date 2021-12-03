#include "sort.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define MAX_ARRAY_SIZE 100
#define SORTING_ITERATIONS 1000

#define ARRAY_FILENAME "../array.txt"
#define ISORT_FILENAME "../isort.txt"
#define QSORT_FILENAME "../qsort.txt"

using namespace std;
using namespace std::chrono;

void measure(int* array, std::function<void(int*, int*)> sort, const char* filename)
{
    ofstream fout(filename);
    if (fout.good())
    {
        for (int size = 1; size <= MAX_ARRAY_SIZE; size++)
        {
            int arrayCopy[size];

            auto startTime = steady_clock::now();

            for (int k = 0; k < SORTING_ITERATIONS; k++)
            {
                for (int i = 0; i < size; i++)
                {
                    arrayCopy[i] = array[i];
                }

                sort(arrayCopy, arrayCopy + size - 1);
            }

            auto endTime = steady_clock::now();

            auto time = duration<double, milli>(endTime - startTime);
            fout << size << ' ' << time.count() << '\n';
        }
    }

    fout.close();
}

int main()
{
    int array[MAX_ARRAY_SIZE];

    ifstream fin(ARRAY_FILENAME);
    if (fin.good())
    {
        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        {
            fin >> array[i];
        }
    }
    else
    {
        cout << "Error reading array file!";
        exit(1);
    }

    fin.close();

    measure(array, [](int* begin, int* end) { my_isort<int>(begin, end, [](int a, int b) { return a < b; }); }, ISORT_FILENAME);
    measure(array, [](int* begin, int* end) { my_qsort<int>(begin, end, [](int a, int b) { return a < b; }, false); }, QSORT_FILENAME);
}