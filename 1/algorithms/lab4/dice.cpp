#include "dice.h"
#include "utils.h"
#include <ctime>
#include <functional>
#include <regex>
#include <sstream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
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

int Dice::roll_all(ArrayList<Dice>& dice)
{
    int sum = 0;
    for (int i = 0; i < dice.size(); i++) sum += dice[i].roll();
    return sum;
}

/*
 * <dice expression> ::= [number]d<number> [bonus]
 *      number          ::= <non-zero digit><digit sequence>
 *      digit sequence  ::= <empty> | <digit><digit sequence>
 *      digit           ::= "0" | <non-zero digit>
 *      non-zero digit  ::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
 *      bonus           ::= <op> <number>
 *      op              ::= "+" | "-"
 */
Dice Dice::parse(std::string str)
{
    static const auto regex = std::regex("^([1-9][0-9]*)?d([1-9][0-9]*)\\s*([+-]\\s*[1-9][0-9]*)?$");
    trim_in_place(str);

    std::smatch match;
    if ( std::regex_match(str, match, regex) )
    {
        int rolls = match[1] != "" ? std::stoi(match[1]) : 1;
        int sides = std::stoi(match[2]);

        int bonus = 0;
        if (match[3] != "")
        {
            bool negative = match[3].str()[0] == '-';
            std::string bonus_string = match[3].str().substr(1);
            trim_in_place(bonus_string);

            bonus = std::stoi(bonus_string) * (negative ? -1 : 1);
        }

        return Dice(rolls, sides, bonus);
    }

    throw std::runtime_error("Error parsing dice string!");
}

ArrayList<Dice> Dice::parse_list(std::string str)
{
    ArrayList<Dice> dice;
    ArrayList<std::string> parts = split(str, ",");

    for (int i = 0; i < parts.size(); i++)
    {
        dice.insert( Dice::parse(parts[i]) );
    }

    return dice;
}

std::string Dice::to_string() const
{
    std::stringstream ss;

    if (rolls > 1) ss << rolls;
    ss << 'd' << sides();
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

const Dice Dice::d4 = Dice(1, 4);
const Dice Dice::d6 = Dice(1, 6);
const Dice Dice::d8 = Dice(1, 8);
const Dice Dice::d10 = Dice(1, 10);
const Dice Dice::d12 = Dice(1, 12);
const Dice Dice::d20 = Dice(1, 20);

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
#pragma clang diagnostic pop