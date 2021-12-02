#ifndef DICE_H
#define DICE_H

#include <random>
#include <stdexcept>

class Dice final
{
private:
    unsigned int rolls;
    int bonus;

    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;

    static size_t seed();

public:
    Dice(int rolls, int sides, int bonus = 0);
    Dice(const Dice& dice);
    ~Dice();

    int sides() const;
    int min() const;
    int max() const;
    float average() const;

    int roll();
    int lowest_of(int n);
    int highest_of(int n);
    int drop_lowest();
    int drop_highest();

    std::string to_string() const;

    friend Dice operator*(int n, Dice dice);
    friend Dice operator+(Dice dice, int n);
    friend Dice operator+(int n, Dice dice);
    friend Dice operator-(Dice dice, int n);

    static Dice d4, d6, d8, d10, d12, d20;
};

Dice operator "" _d4(unsigned long long n);
Dice operator "" _d6(unsigned long long n);
Dice operator "" _d8(unsigned long long n);
Dice operator "" _d10(unsigned long long n);
Dice operator "" _d12(unsigned long long n);
Dice operator "" _d20(unsigned long long n);

#endif
