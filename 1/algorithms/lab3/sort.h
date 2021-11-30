#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>

#define MIN_LENGTH_FOR_QSORT 50

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
void my_isort(T* begin, T* end, const std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }) {
    static_assert(std::is_copy_constructible<T>::value, "Sorting requires a copy constructor!");
    if (end - begin < 2) return;

    for (T* p = begin + 1; p < end; p++)
    {
        T* cur = p;
        while (cur > begin && compare(*cur, *(cur-1)))
        {
            swap(cur-1, cur);
            cur--;
        }
    }
}

//compare returns TRUE if a < b
template<typename T>
void my_qsort(T* begin, T* end, const std::function<bool(T, T)> compare = [](T a, T b) { return a < b; }, int minLength = MIN_LENGTH_FOR_QSORT) {
    static_assert(std::is_copy_constructible<T>::value, "Sorting requires a copy constructor!");

    if (end <= begin) return;

    auto stack = std::stack<std::pair<T*, T*>>();
    stack.push(std::make_pair(begin, end));

    do
    {
        std::pair<T*, T*> pair = stack.top();
        T* i = begin = pair.first;
        T* j = end = pair.second;
        stack.pop();

        if (j - i < minLength)
        {
            my_isort(i, j, compare);
            continue;
        }

        T pivot = median(*i, *(i + (j-i) / 2), *j);

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

        //TODO: fix this 
        if (j-begin < end-i)
        {
            my_qsort(begin, j, compare, minLength);
            if (i < end) stack.push(std::make_pair(i, end));
        }
        else
        {
            my_qsort(i, end, compare, minLength);
            if (j > begin) stack.push(std::make_pair(begin, j));
        }
    }
    while (!stack.empty());
}

#endif
