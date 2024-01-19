#include <iostream>
#include <unistd.h>
#include "display.h"
#include "car.h"
#include "env.h"
#include "map.h"

int main() {
    map::initMap();
    car::initCar();
    env::initEnv();
    display::initDisplay();

    //while(1){
    while(1)
    {   
        //車両情報更新
        car::carUpdate();
        //ゲーム情報更新
        env::updateEnv();
        //画面描写
        display::updateDisplay();

        //ゲーム終了処理
        //ガス欠
        if(std::stoi(car::getCarGas()) <= 0){
            std::cout << "empty gas! end game!" << std::endl;
            break;
        }
        //スコア不足
        if(env::getGameScore() <= 0){
            std::cout << "empty score! end game!" << std::endl;
            break; 
        }
        //時間超過
        if(env::getGameTime() <= 0){
            std::cout << "time over! end game!" << std::endl;
            break; 
        }
        //ユーザ入力処理
        car::inputCommand();
        //終了コマンド入力
        if(car::getCarStatus() == CAR_STT_EXT_MES){
            std::cout << "exit game!" << std::endl;
            break; 
        }
    }

    return 0;
} 