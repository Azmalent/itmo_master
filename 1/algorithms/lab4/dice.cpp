#include "dice.h"
#include <ctime>
#include <functional>
#include <sstream>

size_t Dice::seed()
{
    unsigned int t = static_cast<unsigned int>( time(nullptr) );

    std::hash<unsigned int> hasher;
    return hasher(t);
}

Dice::Dice(int rolls, int sides, int bonus)
{
    if (rolls < 1 || sides < 1) throw std::invalid_argument("Number of rolls and sides must be positive!");

    this->rolls = rolls;
    this->bonus = bonus;

    rng = std::mt19937( seed() );
    dist = std::uniform_int_distribution<int>(1, sides);
}

Dice::Dice(const Dice& dice)
{
    rolls = dice.rolls;
    bonus = dice.bonus;

    rng = dice.rng;
    dist = std::uniform_int_distribution<int>(1, dice.sides());
}

Dice::~Dice()
{
    ~rng();
    dist.~uniform_int_distribution<int>();
}

int Dice::sides() const
{
    return dist.max();
}

int Dice::min() const
{
    return rolls + bonus;
}

int Dice::max() const
{
    return rolls * sides() + bonus;
}

float Dice::average() const
{
    return ( min() + max() ) / 2.0f;
}

int Dice::roll()
{
    int sum = 0;
    for (int i = 0; i < rolls; i++) sum += dist(rng);
    return sum + bonus;
}

int Dice::lowest_of(int n)
{
    if (n < 1) throw std::invalid_argument("Number of roll attempts must be positive!");

    int min = roll();
    for (int i = 0; i < n - 1; i++)
    {
        int result = roll();
        if (result < min) min = result;
    }

    return min;
}

int Dice::highest_of(int n)
{
    if (n < 1) throw std::invalid_argument("Number of roll attempts must be positive!");

    int max = roll();
    for (int i = 0; i < n - 1; i++)
    {
        int result = roll();
        if (result > max) max = result;
    }

    return max;
}

int Dice::drop_lowest()
{
    int sum = 0;
    int lowest = sides();
    for (int i = 0; i < rolls; i++)
    {
        int result = dist(rng);
        sum += result;

        if (result < lowest) lowest = result;
    }
    return sum + bonus - lowest;
}

int Dice::drop_highest()
{
    int sum = 0;
    int highest = 1;
    for (int i = 0; i < rolls; i++)
    {
        int result = dist(rng);
        sum += result;

        if (result > highest) highest = result;
    }
    return sum + bonus - highest;
}

std::string Dice::to_string() const
{
    std::stringstream ss;
    ss << rolls << 'd' << sides();
    if (bonus != 0) ss << ' ' << (bonus < 0 ? '-' : '+') << ' ' << abs(bonus);

    return ss.str();
}

Dice operator*(int n, Dice dice)
{
    return Dice(dice.rolls * n, dice.sides(), dice.bonus * n);
}

Dice operator+(Dice dice, int n)
{
    return Dice(dice.rolls, dice.sides(), dice.bonus + n);
}

Dice operator+(int n, Dice dice)
{
    return dice + n;
}

Dice operator-(Dice dice, int n)
{
    return Dice(dice.rolls, dice.sides(), dice.bonus - n);
}

Dice Dice::d4 = Dice(1, 4);
Dice Dice::d6 = Dice(1, 6);
Dice Dice::d8 = Dice(1, 8);
Dice Dice::d10 = Dice(1, 10);
Dice Dice::d12 = Dice(1, 12);
Dice Dice::d20 = Dice(1, 20);

Dice operator "" _d4(unsigned long long n)
{
    return Dice((int) n, 4);
}

Dice operator "" _d6(unsigned long long n)
{
    return Dice((int) n, 6);
}

Dice operator "" _d8(unsigned long long n)
{
    return Dice((int) n, 8);
}

Dice operator "" _d10(unsigned long long n)
{
    return Dice((int) n, 10);
}

Dice operator "" _d12(unsigned long long n)
{
    return Dice((int) n, 12);
}

Dice operator "" _d20(unsigned long long n)
{
    return Dice((int) n, 20);
}