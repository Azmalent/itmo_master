#include <stdexcept>
#include <stdlib.h>
#include <iostream>

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define ARRAYLIST_DEFAULT_CAPACITY 16
#define ARRAYLIST_GROWTH_FACTOR 2

template<typename T> 
class ArrayList final
{
    static_assert(std::is_default_constructible<T>::value, "ArrayList requires a default constructor!");
    static_assert(std::is_copy_constructible<T>::value, "ArrayList requires a copy constructor!");
    static_assert(std::is_destructible<T>::value, "ArrayList requires a destructor!");

private:
    static constexpr bool movable = std::is_move_constructible<T>::value;

    int capacity;
    T* array;

    int _size = 0;

    void extend();
    inline void initElement(int index, const T& value);

    class ConstIterator;
    class Iterator;

public:
    ArrayList(int capacity = ARRAYLIST_DEFAULT_CAPACITY);
    ArrayList(const ArrayList<T>& list);
    ArrayList(ArrayList<T>&& list);
	ArrayList<T>& operator=(const ArrayList<T>& that);
	ArrayList<T>& operator=(ArrayList<T>&& that);
    ~ArrayList();

    int insert(const T& value);
    int insert(int index, const T& value);
    void remove(int index);
    int size();

    const T& operator[](int index) const;
    T& operator[](int index);

    inline Iterator iterator();
    inline ConstIterator c_iterator();
    inline Iterator reverseIterator();
    inline ConstIterator c_reverseIterator();
};

//Constructors, assignment and destructor
template<typename T> 
ArrayList<T>::ArrayList(int size)
{
    if (size <= 0) throw std::invalid_argument("Capacity must be greater than 0!");

    capacity = size;
    array = (T*) malloc(sizeof(T) * capacity);
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& list)
{
    capacity = list.capacity;
    array = (T*) malloc(sizeof(T) * capacity);
    _size = list._size;

    for (int i = 0; i < _size; i++) initElement(i, list[i]);
}

template<typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& list)
{
    capacity = list.capacity;
    array = list.array;
    _size = list._size;

    list.array = nullptr;
    list._size = 0;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& that)
{
    if (this == &that) return *this;

    for (int i = 0; i < _size; i++) array[i].~T();
    free(array);

    capacity = that.capacity;
    array = (T*) malloc(sizeof(T) * capacity);
    _size = that._size;

    for (int i = 0; i < _size; i++) initElement(i, that[i]);

    return *this;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& that)
{
    if (this == &that) return *this;

    for (int i = 0; i < _size; i++) array[i].~T();
    free(array);

    capacity = that.capacity;
    array = that.array;
    _size = that._size;

    that.array = nullptr;
    that._size = 0;
    
    return *this;
}

template<typename T>
ArrayList<T>::~ArrayList()
{
    for (int i = 0; i < _size; i++) array[i].~T();
    free(array);
}



//Private member functions
template<typename T>
inline void ArrayList<T>::initElement(int index, const T& value)
{
    new(array + index) T(movable ? std::move_if_noexcept(value) : value);
} 

template<typename T>
void ArrayList<T>::extend()
{
    capacity *= ARRAYLIST_GROWTH_FACTOR;

    T* oldArray = array;
    array = (T*) malloc(sizeof(T) * capacity);

    for (int i = 0; i < _size; i++)
    {
        initElement(i, oldArray[i]);
        oldArray[i].~T();
    }

    free(oldArray);
}



//Public member functions
template<typename T>
int ArrayList<T>::insert(const T& value)
{
    return insert(_size, value);
}

template<typename T>
int ArrayList<T>::insert(int index, const T& value)
{
    if (index < 0 || index > _size) return -1;

    if (_size == capacity) extend();

    new(array + _size) T();
    if (index < _size)
    {
        for (int i = _size; i > index; i--) 
        {
            initElement(i, array[i-1]);
            array[i-1].~T();
        }
    }

    initElement(index, value);
    _size++;

    return index;
}

template<typename T>
void ArrayList<T>::remove(int index)
{
    if (index >= _size) return;

    array[index].~T();
    _size--;
    
    for (int i = index + 1; i < _size + 1; i++) 
    {
        initElement(i-1, array[i]);
        array[i].~T();
    }
}

template<typename T>
int ArrayList<T>::size()
{
    return _size;
}



//Indexers
template<typename T>
const T& ArrayList<T>::operator[](int index) const
{
    return array[index];
}

template<typename T>
T& ArrayList<T>::operator[](int index) 
{
    return array[index];
}



//Iterators
template<typename T>
class ArrayList<T>::ConstIterator
{
protected:
    ArrayList<T>& list;
    int curr;
    bool reverse;

public:
    ConstIterator(ArrayList<T>& list, bool reverse = false) : list(list), curr(reverse ? list._size - 1 : 0), reverse(reverse) {};

    const T& get() const
    {
        return list[curr];
    }

    void next()
    {
        reverse ? curr-- : curr++;
    }

    bool hasNext() const
    {
        return reverse ? curr >= 0 : curr < list._size;
    }

    Iterator& operator++()
    {
        curr++;
        return *this;
    }

    Iterator& operator--()
    {
        curr--;
        return *this;
    }
};

template<typename T>
class ArrayList<T>::Iterator : public ConstIterator
{

public:
    Iterator(ArrayList<T>& list, bool reverse = false) : ConstIterator(list, reverse) {}

    void set(const T& value)
    {
        this->list.initElement(this->curr, value);
    }
};

template<typename T>
inline typename ArrayList<T>::Iterator ArrayList<T>::iterator()
{
    return Iterator(*this);
}

template<typename T>
inline typename ArrayList<T>::ConstIterator ArrayList<T>::c_iterator()
{
    return ConstIterator(*this);
}

template<typename T>
inline typename ArrayList<T>::Iterator ArrayList<T>::reverseIterator()
{
    return Iterator(*this, true);
}

template<typename T>
inline typename ArrayList<T>::ConstIterator ArrayList<T>::c_reverseIterator()
{
    return ConstIterator(*this, true);
}

#endif