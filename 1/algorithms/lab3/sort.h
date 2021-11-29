#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <functional>

template<typename T>
T median(T a, T b, T c) {
    if (b <= a && a <= c || c <= a && a <= b) return a;
    if (a <= b && b <= c || c <= b && b <= a) return b;
    return c;
}

template<typename T>
inline void swap(T* a, T* b)
{
    constexpr bool movable = std::is_move_constructible<T>::value;

    T temp = T(movable ? std::move_if_noexcept(*a) : *a);
    *a = T(movable ? std::move_if_noexcept(*b) : *b);
    *b = T(movable ? std::move_if_noexcept(temp) : temp);
}

template<typename T>
void my_sort(T* array, int length, const std::function<bool(T, T)> compare = [](T a, T b) { return a < b; })
{
    my_sort(array, array + (length - 1), compare);
}

//compare returns TRUE if a < b
template<typename T>
void my_sort(T* begin, T* end, const std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) {
    static_assert(std::is_copy_constructible<T>::value, "Sorting requires a copy constructor!");

    //TODO: insertion sort for short arrays

    T* i = begin;
    T* j = end;
    T pivot = median(*begin, *(begin + (end - begin) / 2), *end);

    while(i <= j)
    {
        while (compare(*i, pivot)) i++;
        while (compare(pivot, *j)) j--;

        if (i <= j)
        {
            swap(i, j);
            i++;
            j--;
        }
    }

    if (j > begin) my_sort(begin, j, compare); //TODO: iterative
    if (i < end) my_sort(i, end, compare);
}

#endif
