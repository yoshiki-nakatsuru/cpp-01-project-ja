#include "display.h"

namespace display{

void clearScreen(void);
void infoDisplay(int car_x_pos, int car_y_pos);

//初期化する
void initDisplay(void){
    clearScreen();
}

void updateDisplay(void){
    int car_x_pos;
    int car_y_pos;
    car::getCarPos(car_x_pos, car_y_pos);
    //画面の初期化
    clearScreen();
    //ステータス画面を描写
    try{
        infoDisplay(car_x_pos, car_y_pos);
    }catch(const std::out_of_range& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    //マップを描写
    map::mapDisplay(car_x_pos, car_y_pos,car::getcarDirectionMark());
} 

//画面全体の描写を削除する
void clearScreen(void) {
    std::cout << "\033[2J\033[1;1H";
}

//ステータス画面を描写する。
void infoDisplay(int car_x_pos, int car_y_pos){
    
    std::cout << "Speed: " << car::getCarSpeed() << "\tDirection: " << car::getCarDirection()  << std::endl;
    std::cout << "Gas: " << car::getCarGas() << "\tStatus: " << car::getCarStatus() << std::endl;
    std::cout << "Score: " <<  env::getGameScore() << "\tTime: " << env::getGameTime()<< "\tNext Location:" 
              << env::getGameNextLocation() << std::endl;
    std::cout << "Limited speed: " << map::getSpeedLimit(car_x_pos, car_y_pos) << "\tStreet Name: "
              << map::getStreetName(car_x_pos, car_y_pos) << std::endl;
}

}