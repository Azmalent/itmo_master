#include "../arraylist.h"
#include <iostream>
#include <gtest/gtest.h>

struct Person
{
    const std::string name;

    Person(const char* name = "Steve") : name(std::string(name)) {}
    Person(const Person& person) : name(person.name) {}
    ~Person() = default;

    bool operator==(const Person& that) const
    {
        if (typeid(*this) != typeid(that)) return false;
        return name == that.name;
    }
};

class ArrayListTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        list.insert(Person(alice));
        list.insert(Person(bob));
        list.insert(Person(charlie));
    }

    const Person alice = Person("Alice");
    const Person bob = Person("Bob");
    const Person charlie = Person("Charlie");
    const Person dave = Person("Dave");

    ArrayList<Person> list;
};

TEST_F(ArrayListTest, CopyConstructor)
{
    ArrayList<Person> newList = list;

    int size = newList.size();
    ASSERT_EQ(size, list.size());

    for (int i = 0; i < size; i++)
    {
        EXPECT_EQ(list[i], newList[i]);
    }
}

TEST_F(ArrayListTest, MoveConstructor)
{
    ArrayList<Person> newList = std::move(list);

    ASSERT_EQ(newList.size(), 3);
    ASSERT_EQ(list.size(), 0);

    EXPECT_EQ(newList[0], alice);
    EXPECT_EQ(newList[1], bob);
    EXPECT_EQ(newList[2], charlie);
}

TEST_F(ArrayListTest, Insert)
{
    int index = list.insert(dave);
    EXPECT_EQ(index, 3);
    
    ASSERT_EQ(list.size(), 4);
    EXPECT_EQ(list[0], alice);
    EXPECT_EQ(list[1], bob);
    EXPECT_EQ(list[2], charlie);
    EXPECT_EQ(list[3], dave);
}

TEST_F(ArrayListTest, InsertAtIndex)
{
    int index = list.insert(2, dave);
    EXPECT_EQ(index, 2);
    
    ASSERT_EQ(list.size(), 4);
    EXPECT_EQ(list[0], alice);
    EXPECT_EQ(list[1], bob);
    EXPECT_EQ(list[2], dave);
    EXPECT_EQ(list[3], charlie);
}

TEST_F(ArrayListTest, InvalidInsertion)
{
    int a = list.insert(-1, dave);
    int b = list.insert(1000, dave);
    
    ASSERT_EQ(list.size(), 3);
    EXPECT_EQ(a, -1);
    EXPECT_EQ(b, -1);
}

TEST_F(ArrayListTest, Remove)
{
    list.remove(1);

    ASSERT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], alice);
    EXPECT_EQ(list[1], charlie);
}

TEST_F(ArrayListTest, Iterator)
{
    auto newList = ArrayList<Person>();
    
    for (auto it = list.c_iterator(); it.hasNext(); it.next())
    {
        newList.insert(it.get());
    }

    ASSERT_EQ(newList.size(), 3);
    EXPECT_EQ(newList[0], alice);
    EXPECT_EQ(newList[1], bob);
    EXPECT_EQ(newList[2], charlie);
}

TEST_F(ArrayListTest, ReverseIterator)
{
    auto newList = ArrayList<Person>();
    
    for (auto it = list.c_reverseIterator(); it.hasNext(); it.next())
    {
        newList.insert(it.get());
    }

    ASSERT_EQ(newList.size(), 3);
    EXPECT_EQ(newList[0], charlie);
    EXPECT_EQ(newList[1], bob);
    EXPECT_EQ(newList[2], alice);
}

TEST_F(ArrayListTest, IteratorSet)
{
    for (auto it = list.iterator(); it.hasNext(); it.next())
    {
        it.set(dave);
    }

    ASSERT_EQ(list.size(), 3);
    for (int i = 0; i < 3; i++) EXPECT_EQ(list[i], dave);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}