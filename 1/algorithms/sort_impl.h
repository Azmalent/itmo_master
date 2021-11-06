#include "sort.h"

template <typename T>
T median(T a, T b, T c) {
    if (b <= a && a <= c || c <= a && a <= b) return a;
    if (a <= b && b <= c || c <= b && b <= a) return b;
    return c;
}

template<typename T>
void insertionsort(T* array, int length) {
    for (int i = 0; i < length - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < length; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            T temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }
}

template<typename T> 
void quicksort(T* array, int length) {
    T pivot = median(array[0], array[length/2], array[length-1]);
}