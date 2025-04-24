#include "Stats.hpp"

Stats defaultStatLine(10, 2.0, 2.2, 1, 0);
Growths defaultGrowths(35, 15, 25, 15, 0);

Growths inputGrowths[] = {
    Growths(65, 25, 30, 20, 40),
    Growths(50, 15, 25, 20, 0),
    Growths(20, 20, 15, 10, 0),
    Growths(35, 10, 30, 15, 0)
};

Stats inputStats[] = {
    Stats(20, 2.5, 1, 1, 30),
    Stats(10, 2.5, 2, 2, 0),
    Stats(8, 2.0, 3, 0, 0),
    Stats(12, 3, 1, 1, 0)
};

int inputCount = std::min((int)(sizeof(inputStats) / sizeof(Stats)), ENTITY_COUNT);

Growths growthTable[ENTITY_COUNT];
Stats statTable[ENTITY_COUNT];

void initstats() {
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (i < inputCount) {
            statTable[i] = inputStats[i];
            growthTable[i] = inputGrowths[i];
        }
        else {
            statTable[i] = defaultStatLine;
            growthTable[i] = defaultGrowths;
        }
        statTable[i].setGrowths(growthTable[i]);
    }
}
