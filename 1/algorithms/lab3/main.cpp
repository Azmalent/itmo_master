#include "sort.h"
#include <iostream>

using namespace std;

int main()
{
    int array[] = {13, 23, 65, 10, -8, 0, 10, 4, -2, 19};
    cout << "QUICKSORT TEST\n" << "Before: \n";
    for (int i = 0; i < 10; i++)
    {
        cout << array[i] << ((i < 9) ? ", " : "\n\n");
    }

    my_sort(array,array + 9);
    cout << "After: \n";
    for (int i = 0; i < 10; i++)
    {
        cout << array[i] << ((i < 9) ? ", " : "\n\n");
    }
}