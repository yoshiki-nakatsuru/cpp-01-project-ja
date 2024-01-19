#pragma once
#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include "common.h"
#include "map.h"

#define INIT_X_POS 4
#define INIT_Y_POS 8
#define INIT_GAS 200

namespace car{

enum kcarSpeed{
    kStop = 0,
    kLowSpeed = 1,
    kMidSpeed = 2,
    kHighSpeed = 3
};

enum kcarDirection{
    kNorth = 0,
    kWest = 1,
    kSouth = 2,
    kEast = 3

};

enum kcarStatus{
    kTurnL = -1,
    kOK = 0,
    kTurnR = 1,
    kGasEmpty,
    kSpeeding,
    kCollision,
    kExit
};

struct carState{
    kcarDirection direction;
    kcarSpeed speed;
    int gas;
    int x_pos;
    int y_pos;
    kcarStatus status;
};

extern void initCar(void);
extern void carUpdate(void);
extern void inputCommand(void);
extern std::string getCarDirection(void);
extern std::string getCarSpeed(void);
extern std::string getCarGas(void);
extern void getCarPos(int& x_pos, int& y_pos);
extern std::string getCarStatus(void);
extern std::string getcarDirectionMark();
extern void setCarGas(void);


}