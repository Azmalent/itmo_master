#include <fstream>
#include <iostream>
#include "game.h"
#include "utils.h"

using namespace std;

HammurapiGame::HammurapiGame() 
{
    //NO-OP
}

HammurapiGame::HammurapiGame(const HammurapiGame& copy)
{
    round = copy.round;
    population = copy.population;
    wheat = copy.wheat;
    area = copy.area;
    wheatToEat = copy.wheatToEat;
    utilizedAcres = copy.utilizedAcres;
}

void HammurapiGame::play()
{
    bool canContinue = true;
    do 
    {
        canContinue = startRound();
    } while (round < TOTAL_ROUNDS && canContinue);

    GameRating rating = canContinue ? getRating() : GameRating::Terrible;

    cout << "\n--------------- The End ---------------\n";
    cout << "Average starvation rate: " << (int)(starvationRateSum / round * 100) << "%\n";
    if (population > 0) cout << "Farmland per citizen: " << roundToOnePoint((float) area / population) << " acres\n";
    cout << '\n';

    if (rating == GameRating::Perfect) cout << "Congratulations, you did perfectly!\nYou were a wise and prudent ruler.\nThe people universally admire you.\n";
    else if (rating == GameRating::Great) cout << "You were a great ruler.\nMost people admire you and support your reign.\n";
    else if (rating == GameRating::Average) cout << "You were an average ruler.\nWhile you weren't the worst, you still have made many enemies among your people.\n";
    else cout << "You were a terrible ruler.\nThe citizens have rebelled against your tyranny, forcing you into exile.\n";
}

bool HammurapiGame::startRound()
{
    int landPrice = landPriceDist(rng); 
    int harvestPerAcre = harvestDist(rng);

    cout << "\n--------------- Year #" << (round + 1) << " ---------------\n";

    //Смерть от голода
    int starved = (wheatToEat >= 0) ? population - (wheatToEat / WHEAT_COST_PER_CITIZEN) : 0;
    float starvationRate = (float)starved / population;
    starvationRateSum += starvationRate;
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
    if (unitDist(rng) < PLAGUE_CHANCE) 
    {
        population /= 2;
        cout << "A plague outbreak has killed half of the population!\n";
    }

    //Урожай
    if (utilizedAcres > 0)
    {
        int maxUsableArea = min(area, population * MAX_AREA_PER_CITIZEN);
        int wheatCollected = min(maxUsableArea, utilizedAcres) * (harvestPerAcre - WHEAT_COST_PER_ACRE);
        wheat += wheatCollected;
        cout << wheatCollected << " bushels of wheat were collected (" << harvestPerAcre << " per acre).\n";
    }

    //Крысы
    float wheatEatenByRats = roundToOnePoint(ratsDist(rng) * wheat);
    wheat -= wheatEatenByRats;
    cout << wheatEatenByRats << " bushels of wheat were eaten by rats!\n\n";

    //Вывод статов
    cout << "There are " << wheat << " bushels of wheat in the barns.\n";
    cout << "The current population of the city is " << population << " people.\n";
    cout << "The area of the city is " << area << " acres.\n";
    cout << "An acre of land currently costs " << landPrice << " bushels of wheat.\n";

    //Запрос действий
    if (round < TOTAL_ROUNDS - 1)
    {
        int areaToBuy = inputInt(-area, wheat / landPrice, " > How many acres of land to buy/sell? Input negative number to sell.", "You can't afford to buy that much land!");
        area += areaToBuy;
        wheat -= areaToBuy * landPrice;

        wheatToEat = inputInt(wheat, " > How many bushels of wheat to use as food?", "You don't have that much wheat!");
        wheat -= wheatToEat;
        
        int maxUsableArea = min(area, population * MAX_AREA_PER_CITIZEN);
        utilizedAcres = inputInt(maxUsableArea, " > How many acres of wheat to plant?", "You don't have that much farmland!");
        utilizedAcres = min((int)(wheat / WHEAT_COST_PER_ACRE), utilizedAcres);
        wheat -= utilizedAcres * WHEAT_COST_PER_ACRE;
    }
    
    round++;

    if (round < TOTAL_ROUNDS - 1)
    {
        cout << "\n > Would you like to save your progress and exit? (y/n) ";
        char c;
        cin >> c;
        if (c == 'y')
        {
            save();
            exit(EXIT_SUCCESS);
        }
    }

    return true;
}

GameRating HammurapiGame::getRating()
{
    float areaPerCitizen = (population > 0) ? (float) area / population : 0;

    if (starvationRateSum > 0.33 || areaPerCitizen < 7) return GameRating::Terrible;
    if (starvationRateSum > 0.1 || areaPerCitizen < 9) return GameRating::Average;
    else if (starvationRateSum > 0.03 || areaPerCitizen < 10) return GameRating::Great;
    return GameRating::Perfect;
}

void HammurapiGame::save()
{
    ofstream fout(SAVE_FILE_NAME);
    
    fout << round << '\n';
    fout << population << '\n';
    fout << wheat << '\n';
    fout << area << '\n';
    fout << starvationRateSum << '\n';
    fout << utilizedAcres;
    
    fout.close();
}

HammurapiGame HammurapiGame::load(ifstream& fin)
{
    HammurapiGame game;
    fin >> game.round >> game.population >> game.wheat >> game.area >> game.starvationRateSum >> game.wheatToEat
        >> game.utilizedAcres;

    fin.close();

    return game;
}