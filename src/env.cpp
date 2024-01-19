#include "env.h"


namespace env{

const gameInfo kInitGameData = {INIT_SCORE, INIT_TIME, TARGET_1};

static gameInfo game_data = kInitGameData;

void setTarget(void);

//初期化する
void initEnv(void){
    game_data = kInitGameData; 
    game_data.time++;
}

//ゲーム情報を更新する
void updateEnv(void){
    int x_pos;
    int y_pos;

    game_data.time--;
    car::getCarPos(x_pos, y_pos);

    //自車の状態からスコアを減算する。
    //衝突した場合
    if(car::getCarStatus() == CAR_STT_COL_MES){
        game_data.score -= COLISINON_DAMAGE;
    //速度超過の場合
    }else if(car::getCarStatus() == CAR_STT_SPD_MES){
        game_data.score -= SPEEDING_DAMAGE;
    }

    //自車のいる場所に応じた処理
    //ガソリンスタンドで停車している場合
    if((map::getMapCellMark(x_pos, y_pos) == GAS_STATION) 
        && (car::getCarSpeed() == CAR_SPD_STOP)){
        car::setCarGas();
        game_data.time -= FUELING_TIME;
    //目的地で停車している場合
    }else if((map::getMapCellMark(x_pos, y_pos) == game_data.next_location) 
            && (car::getCarSpeed() == CAR_SPD_STOP)){
        game_data.score += (std::stoi(car::getCarGas()) + game_data.time * 4); 
        game_data.time = INIT_TIME;
        setTarget();
    }

}

//目的地を設定する。
void setTarget(void){
    if(game_data.next_location == TARGET_1){
        if((game_data.time % 2) == 0)game_data.next_location = TARGET_3;
        else game_data.next_location = TARGET_2;
    }else if(game_data.next_location == TARGET_2){
        if((game_data.time % 2) == 0)game_data.next_location = TARGET_1;
        else game_data.next_location = TARGET_3;
    }else{
        if((game_data.time % 2) == 0)game_data.next_location = TARGET_2;
        else game_data.next_location = TARGET_1;
    }
}

//スコアを出力する
int getGameScore(void){
    return game_data.score;
}

//残り時間を出力する
int getGameTime(void){
    return game_data.time;
}

//次の目的地を出力する。
std::string getGameNextLocation(void){
    return game_data.next_location;
}

}