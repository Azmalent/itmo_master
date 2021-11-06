#include <iostream>
#include <limits>
#include "utils.h"

using namespace std;

float clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float roundToOnePoint(float value)
{
    return (float)((int)value * 10) / 10;
}

int inputInt(int max, const char* promptMessage, const char* errorMessage)
{
    return inputInt(0, max, promptMessage, errorMessage);
}

int inputInt(int min, int max, const char* promptMessage, const char* errorMessage)
{
    int value;
    while (true)
    {
        cout << '\n' << promptMessage << " (";
        if (min != 0) cout << "min: " << min << ", ";
        cout << "max: " << max << ") ";

        cin >> value;
        if (cin.fail()) 
        {
            cout << "Invalid input! Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (value > max || value < min) cout << errorMessage << '\n';
        else break;
    }
    
    return value;
}