#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>

#define MIN_LENGTH_FOR_QSORT 20

template<typename T>
T median(T& a, T& b, T& c, const std::function<bool(T&, T&)> compare) {
    if (!compare(a, b) && !compare(c, a) || !compare(a, c) && !compare(b, a)) return a;
    if (!compare(b, a) && !compare(c, b) || !compare(b, c) && !compare(a, b)) return b;
    return c;
}

template<typename T>
inline void swap(T* a, T* b)
{
    constexpr bool movable = std::is_nothrow_move_constructible<T>::value;

    T temp = T(movable ? std::move_if_noexcept(*a) : *a);
    a->~T();

    new(a) T(movable ? std::move_if_noexcept(*b) : *b);
    b->~T();

    new(b) T(movable ? std::move_if_noexcept(temp) : temp);
}

template<typename T>
void my_isort(T* begin, T* end, const std::function<bool(T&, T&)> compare = [](T& a, T& b) { return a < b; }) {
    static_assert(std::is_copy_constructible<T>::value, "Sorting requires a copy constructor!");
    if (end - begin < 2) return;

    constexpr bool movable = std::is_nothrow_move_constructible<T>::value;

    for (T* p = begin + 1; p <= end; p++)
    {
        if (compare(*p, *(p-1)))
        {
            T* cur = p;
            T temp = T(movable ? std::move_if_noexcept(*cur) : *cur);
            cur->~T();

            do
            {
                T* prev = cur - 1;
                new(cur) T(movable ? std::move_if_noexcept(*prev) : *prev);
                prev->~T();

                cur--;
            }
            while (cur > begin && compare(temp, *(cur-1)));

            new(cur) T(movable ? std::move_if_noexcept(temp) : temp);
            temp.~T();
        }
    }
}

//compare returns TRUE if a < b
template<typename T>
void my_qsort(T* begin, T* end, const std::function<bool(T&, T&)> compare = [](T& a, T& b) { return a < b; }, bool optimize = true) {
    static_assert(std::is_copy_constructible<T>::value, "Sorting requires a copy constructor!");

    while (true)
    {
        if (end <= begin) return;
        if (optimize && (end - begin < MIN_LENGTH_FOR_QSORT))
        {
            my_isort(begin, end, compare);
            return;
        }

        T* i = begin;
        T* j = end;
        T pivot = median(*begin, *(begin + (end - begin) / 2), *end, compare);

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

        if (j-begin < end-i)
        {
            my_qsort(begin, j, compare, optimize);

            if (i < end) begin = i;
            else return;
        }
        else
        {
            my_qsort(i, end, compare, optimize);
            if (j > begin) end = j;
            else return;
        }
    }
}

#endif
