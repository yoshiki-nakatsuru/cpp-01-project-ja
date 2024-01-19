#pragma once
#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include "common.h"

#define MAP_INVALID_SPACE 2
#define MAP_X_SIZE 40
#define MAP_Y_SIZE 25
#define MAP_X_RAW_SIZE (MAP_X_SIZE + MAP_INVALID_SPACE * 2)
#define MAP_Y_RAW_SIZE (MAP_Y_SIZE + MAP_INVALID_SPACE * 2)

namespace map{

enum kCellStatus{
    kCellvalid,
    kOnlyNorth,
    kOnlyEast,
    kOnlySsouth,
    kOnlyWest,
    kGasStation,
    kGoal,
    kCellInvalid
};
enum kSpeedLimit{
    kOnlyLowSpeed = 1,
    kNormal = 2,
    kHighway = 3
};

struct mapCell{
    std::string cellMark;
    std::string streetName;
    kCellStatus cellStatus;
    kSpeedLimit cellSpeedLimit;
};


extern void initMap(void);
extern void mapDisplay(int car_x_pos, int car_y_pos, std::string car_direction);
extern std::string getStreetName(int car_x_pos, int car_y_pos); 
extern bool judgeAccessibility(int x_pos, int y_pos);
extern std::string getMapCellMark(int x_pos, int y_pos);
extern std::string getSpeedLimit(int x_pos, int y_pos);

}