#include "../sort.h"
#include "../../lab2/arraylist.h"
#include <fstream>
#include <gtest/gtest.h>

#define ARRAY_SIZE 1000
#define ARRAY_FILENAME "../../array.txt"

template<typename T>
inline void assert_sorted(T* begin, T* end, const std::function<bool(T&, T&)> compare = [](T& a, T& b) { return a < b; })
{
    for (T* cur = begin + 1; cur <= end; cur++)
    {
        ASSERT_FALSE(compare(*cur, *(cur-1)));
    }
}

struct Person final
{
    const std::string name;

    explicit Person(const char* name = "Steve") : name(std::string(name)) {}
    Person(const Person& person) = default;
    Person(const Person&& person) noexcept : name(person.name) {};

    ~Person() = default;

    bool operator==(const Person& that) const
    {
        if (typeid(*this) != typeid(that)) return false;
        return name == that.name;
    }
};

class IntSortTest : public ::testing::Test
{
protected:
    int array[ARRAY_SIZE];

    void SetUp() override
    {
        std::ifstream fin(ARRAY_FILENAME);
        if (fin.good())
        {
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                fin >> array[i];
            }
        }

        fin.close();
    }
};

class ArrayListTest : public ::testing::Test
{
protected:
    ArrayList<int> list = ArrayList<int>(ARRAY_SIZE);

    void SetUp() override
    {
        std::ifstream fin(ARRAY_FILENAME);
        if (fin.good())
        {
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                int n;
                fin >> n;
                list.insert(n);
            }
        }

        fin.close();
    }
};

class PersonSortTest : public ::testing::Test
{
protected:
    Person array[ARRAY_SIZE];

    void SetUp() override
    {
        const char* names[10] = {"Alice", "Bob", "Charlie", "Dave", "Edward", "Frank", "George", "Harold", "Ian", "Jane"};

        std::ifstream fin(ARRAY_FILENAME);
        if (fin.good())
        {
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                int n;
                fin >> n;

                int index = abs(n) % 10;
                new(array + i) Person(names[index]);
            }
        }

        fin.close();
    }
};

TEST_F(IntSortTest, AscendingInsertionSort)
{
    my_isort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; });
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; });
}

TEST_F(IntSortTest, DescendingInsertionSort)
{
    my_isort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; });
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; });
}

TEST_F(IntSortTest, AscendingQuicksort)
{
    my_qsort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; }, false);
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; });
}

TEST_F(IntSortTest, DescendingQuicksort)
{
    my_qsort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; }, false);
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; });
}

TEST_F(IntSortTest, AscendingMixedSort)
{
    my_qsort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; });
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a < b; });
}

TEST_F(IntSortTest, DescendingMixedSort)
{
    my_qsort<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; });
    assert_sorted<int>(array, array + ARRAY_SIZE-1, [](int a, int b) { return a > b; });
}

TEST_F(PersonSortTest, InsertionSort)
{
    my_isort<Person>(array, array + ARRAY_SIZE-1, [](Person& a, Person& b) { return a.name < b.name; });
    assert_sorted<Person>(array, array + ARRAY_SIZE-1, [](Person& a, Person& b) { return a.name < b.name; });
}

TEST_F(PersonSortTest, QuickSort)
{
    my_qsort<Person>(array, array + ARRAY_SIZE-1, [](Person& a, Person& b) { return a.name < b.name; });
    assert_sorted<Person>(array, array + ARRAY_SIZE-1, [](Person& a, Person& b) { return a.name < b.name; });
}

TEST_F(ArrayListTest, InsertionSort)
{
    my_isort(list.begin(), list.end());
    assert_sorted(list.begin(), list.end());
}

TEST_F(ArrayListTest, QuickSort)
{
    my_qsort(list.begin(), list.end());
    assert_sorted(list.begin(), list.end());
}
