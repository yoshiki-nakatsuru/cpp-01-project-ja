#pragma once
#include <iostream>
#include <string>
#include "common.h"
#include "car.h"

#define INIT_SCORE 100
#define INIT_TIME 50
#define COLISINON_DAMAGE 30
#define SPEEDING_DAMAGE 10
#define FUELING_TIME 5

namespace env{

struct gameInfo{
    int score;
    int time;
    std::string next_location;
};



extern void initEnv(void);
extern void updateEnv(void);
extern int getGameScore(void);
extern int getGameTime(void);
extern std::string getGameNextLocation(void);
}