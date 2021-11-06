#include <iostream>
#include "game.h"
#include "utils.h"

using namespace std;

GameState::GameState()
{

}

GameState::~GameState()
{
    //TODO: destructor
}

void GameState::start()
{
    bool canContinue = true;
    do 
    {
        canContinue = startRound();
    } while (round < TOTAL_ROUNDS && canContinue);

    cout << (canContinue ? "You win!" : "You lose!") << '\n';

    if (avgStarvationRate > 0.33 || areaPerCitizen < 7) cout << "Terrible";
    else if (avgStarvationRate > 0.1 || areaPerCitizen < 9) cout << "Alright";
    else if (avgStarvationRate > 0.03 || areaPerCitizen < 10) cout << "Good";
    else cout << "Perfect";
}

bool GameState::startRound()
{
    int landPrice = landPriceDist(rng); 
    int harvestPerAcre = harvestDist(rng);

    cout << "\n-----------------------------------------------\n";
    cout << "It is the year " << (round + 1) << " of your reign.\n";

    //Смерть от голода
    int starved = (wheatToEat >= 0) ? population - (wheatToEat / WHEAT_UPKEEP_PER_CITIZEN) : 0;
    float starvationRate = (float)starved / population;

    if (starved > 0)
    {
        population -= starved;

        cout << starved << " citizens have starved (" << (int)(starvationRate * 100) << "% of your population)!\n";
        if (starvationRate >= 0.45) return false;
    }

    //Мигранты
    int migrants = clamp(starved / 2 + (5 - harvestPerAcre) * wheat / 600 + 1, 0, 50);
    if (migrants > 0)
    {
        population += migrants;
        cout << migrants << " migrants have arrived to the city.\n";
    }

    //Чума
    bool plague = plagueDist(rng) < PLAGUE_CHANCE;
    if (plague) 
    {
        population /= 2;
        cout << "A plague outbreak has killed half of the population!\n";
    }

    //Урожай
    if (utilizedAcres > 0)
    {
        int maxUsableArea = min(area, population * MAX_AREA_PER_CITIZEN);
        int wheatCollected = min(maxUsableArea, utilizedAcres) * (harvestPerAcre - WHEAT_UPKEEP_PER_ACRE);
        wheat += wheatCollected;
        cout << wheatCollected << " bushels of wheat were collected (" << harvestPerAcre << " per acre).\n";
    }

    //Крысы
    float wheatEatenByRats = roundToOnePoint(ratsDist(rng) * wheat);
    wheat -= wheatEatenByRats;
    cout << wheatEatenByRats << " bushels of wheat were eaten by rats!\n\n";

    //Вывод статов
    cout << "There are " << wheat << " bushels of wheat in the barns.\n";
    cout << "The current population of the city is " << population << ".\n";
    cout << "The area of the city is " << area << " acres.";
    cout << "An acre of land currently costs " << landPrice << " bushels of wheat.\n";

    //Запрос действий
    if (round < TOTAL_ROUNDS)
    {
        int areaToBuy = inputInt(-area, wheat / landPrice, "How many acres of land to buy/sell? Input negative number to sell.", "You can't afford to buy that much land!");
        area += areaToBuy;
        wheat -= areaToBuy * landPrice;

        wheatToEat = inputInt(wheat, "How many bushels of wheat to use as food?", "You don't have that much wheat!");
        wheat -= wheatToEat;
        
        int maxUsableArea = min(area, population * MAX_AREA_PER_CITIZEN);
        utilizedAcres = inputInt(maxUsableArea, "How many acres of wheat to plant?", "You can't plant that many!");
        utilizedAcres = min((int)(wheat / WHEAT_UPKEEP_PER_ACRE), utilizedAcres);
        wheat -= utilizedAcres * WHEAT_UPKEEP_PER_ACRE;
    }

    round++;
    avgStarvationRate += starvationRate / TOTAL_ROUNDS;
    areaPerCitizen = area / population;

    return true;
}

