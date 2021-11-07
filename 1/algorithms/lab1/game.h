#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <fstream>
#include <random>

using namespace std;

#define TOTAL_ROUNDS 10

#define STARTING_POPULATION 100
#define STARTING_WHEAT 2800
#define STARTING_AREA 1000

#define WHEAT_COST_PER_CITIZEN 20
#define WHEAT_COST_PER_ACRE 0.5f
#define MAX_AREA_PER_CITIZEN 10

#define MIN_LAND_PRICE 17
#define MAX_LAND_PRICE 26
#define PLAGUE_CHANCE 0.15f
#define STARVATION_RATE_TO_LOSE 0.45f
#define MAX_HARVEST_RATE 6
#define MAX_WHEAT_EATEN_BY_RATS 0.07f

#define SAVE_FILE_NAME "savefile"

enum class GameRating { Terrible, Average, Great, Perfect };

class HammurapiGame
{
private:
    int round = 0;

    int population = STARTING_POPULATION;
    float wheat = STARTING_WHEAT;
    int area = STARTING_AREA;
    
    float starvationRateSum = 0; 

    int wheatToEat = -1;
    int utilizedAcres = -1;

    random_device rd;
    mt19937 rng = mt19937(rd());
    
    uniform_real_distribution<float> unitDist = uniform_real_distribution<float>(0, 1);

    uniform_int_distribution<int> landPriceDist = uniform_int_distribution<int>(MIN_LAND_PRICE, MAX_LAND_PRICE);
    uniform_int_distribution<int> harvestDist   = uniform_int_distribution<int>(1, MAX_HARVEST_RATE);
    uniform_real_distribution<float> ratsDist   = uniform_real_distribution<float>(0, MAX_WHEAT_EATEN_BY_RATS);

    bool startRound();
    GameRating getRating();
    void save();

public:
    HammurapiGame();
    HammurapiGame(const HammurapiGame& copy);

    void play();
    
    static HammurapiGame load(ifstream& fin);
};

#endif