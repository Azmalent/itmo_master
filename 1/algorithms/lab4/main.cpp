#include "dice.h"
#include <fstream>
#include <functional>
#include <iostream>

#define ROLL_AMOUNT 10000

void get_distribution(std::function<int(void)> func, std::string filename)
{
    std::ofstream fout("../dist/" + filename + ".txt");
    if (fout.good())
    {
        for (int i = 0; i < ROLL_AMOUNT; i++)
        {
            int n = func();
            fout << n << '\n';
        }

        fout.close();
    }
    else
    {
        std::cout << "Error writing to file 'dist/" << filename << ".txt'!";
        fout.close();
        exit(1);
    }
}

void get_distribution(Dice dice)
{
    get_distribution([&dice]() { return dice.roll(); }, dice.to_string());
}

int main()
{
    for (int i = 1; i <= 3; i++)
    {
        get_distribution(i * Dice::d6);
        get_distribution(i * Dice::d10);
    }

    get_distribution([]() { static Dice dice = 4_d6; return dice.drop_lowest(); }, "4d6, drop lowest");
    get_distribution([]() { static Dice dice = 4_d6; return dice.drop_highest(); }, "4d6, drop highest");
    get_distribution([]() { static Dice dice = 3_d6; return dice.lowest_of(2); }, "3d6, lower of 2 rolls");
    get_distribution([]() { static Dice dice = 3_d6; return dice.highest_of(2); }, "3d6, higher of 2 rolls");

    return 0;
}
