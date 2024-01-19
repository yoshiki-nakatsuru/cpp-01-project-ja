#include "car.h"

namespace car{

//定数
const carState initCarState = {kEast, kStop, INIT_GAS, INIT_X_POS, INIT_Y_POS, kOK};

//関数宣言
void carMoveFunction(void);
void carTurnFunction(int turn_direction);
bool judgeSpeeding(void);

//静的変数
carState egoCar = initCarState;

//初期化する
void initCar(){
    egoCar = initCarState;
}

//自車情報をアップデートする。
void carUpdate(void){

    //ガソリン残量の計算
    switch(egoCar.speed){
        case kStop:{
            break;
        }case kLowSpeed:{
            egoCar.gas -= 1;
            break;
        }case kMidSpeed:{
            egoCar.gas -= 3;
            break;
        }case kHighSpeed:{
            egoCar.gas -= 6;
            break;
        }default: {
            break;
        }
    }
    //ユーザ入力を反映する
    //直進動作
    if(egoCar.status == kOK){
        //直進動作
        carMoveFunction();
    }else if((egoCar.status == kTurnL) || (egoCar.status == kTurnR)){
        //カーブ動作
        if(egoCar.speed == kLowSpeed)carMoveFunction();
        else carTurnFunction(static_cast<int>(egoCar.status));
    }
    //衝突した場合、停止させる。
    if(egoCar.status == kCollision)egoCar.speed = kStop;
    //速度超過判定
    if(egoCar.status == kOK){
        if(judgeSpeeding())egoCar.status = kSpeeding;
    }

}

//ユーザのコマンド入力を受け取る
void inputCommand(){
    std::cout << "input:";

    std::string userInput;
    std::getline(std::cin, userInput);
    
    egoCar.status = kOK;
    //加速
    if((userInput == "accelerate") || (userInput == "w")){
        if(static_cast<int>(egoCar.speed) < static_cast<int>(kHighSpeed)){
            egoCar.speed = static_cast<kcarSpeed>(static_cast<int>(egoCar.speed) + 1);
        }
        std::cout << "input: accelerate" << std::endl;
    //減速
    }else if((userInput == "decelerate") || (userInput == "s")){
        if(static_cast<int>(egoCar.speed) > static_cast<int>(kStop)){
            egoCar.speed = static_cast<kcarSpeed>(static_cast<int>(egoCar.speed) - 1);
        }
        std::cout << "input: decelerate" << std::endl;
    //右折
    }else if((userInput == "turn right") || (userInput == "d")){
        if(egoCar.direction == kNorth){
            egoCar.direction = kEast;
        }else{
            egoCar.direction = static_cast<kcarDirection>(static_cast<int>(egoCar.direction) - 1);
        }
        egoCar.status = kTurnR;
        std::cout << "input: turn right" << std::endl;
    //左折
    }else if((userInput == "turn left") || (userInput == "a")){
        if(egoCar.direction == kEast){
            egoCar.direction = kNorth;
        }else{
            egoCar.direction = static_cast<kcarDirection>(static_cast<int>(egoCar.direction) + 1);
        }
        egoCar.status = kTurnL;
        std::cout << "input: turn left" << std::endl;
    //停止
    }else if((userInput == "stop") || (userInput == "e")){
        egoCar.speed = kStop;
        std::cout << "input: stop" << std::endl;
    //直進
    }else if(userInput == "continue straight"){
        if(egoCar.speed == kStop)egoCar.speed = kLowSpeed;
        std::cout << "input: continue straight" << std::endl;
    //現状維持
    }else if(userInput == ""){
        std::cout << "input: do not change speed" << std::endl;
    //終了コマンド
    }else if(userInput == "exit"){
        std::cout << "input: exit" << std::endl;
        egoCar.status = kExit;
    //それ以外の入力
    }else{
        std::cout << "input: invalid input" << std::endl;
    }
}


//直進動作
void carMoveFunction(void){
    int temp_x_pos;
    int temp_y_pos;
    int speed = static_cast<int>(egoCar.speed);
    //速度分だけ繰り返す。
    for(int i = 0; i < speed; i++){
        temp_x_pos = egoCar.x_pos;
        temp_y_pos = egoCar.y_pos;
        egoCar.x_pos += ((static_cast<int>(egoCar.direction) - 2) * (static_cast<int>(egoCar.direction) % 2));
        egoCar.y_pos += ((static_cast<int>(egoCar.direction) - 1) * ((static_cast<int>(egoCar.direction) + 1) % 2));
        //進入不可の場所に入った場合
        if(map::judgeAccessibility(egoCar.x_pos, egoCar.y_pos) == false){
            egoCar.status = kCollision;
            egoCar.x_pos = temp_x_pos;
            egoCar.y_pos = temp_y_pos;
            return;
        }
    }
    egoCar.status = kOK;
}

//カーブ動作
void carTurnFunction(int turn_direction){
    int temp_x_pos;
    int temp_y_pos;
    int speed = static_cast<int>(egoCar.speed) - 1;
    int prev_direction;
    
    prev_direction = static_cast<int>(egoCar.direction) + turn_direction;
    if(prev_direction > 3)prev_direction = 0;
    if(prev_direction < 0)prev_direction = 3;

    //中速は1回、高速は2回繰り返す
    for(int i = 0; i < speed; i++){
        //元の方向に1マス動く
        temp_x_pos = egoCar.x_pos;
        temp_y_pos = egoCar.y_pos;
        egoCar.x_pos += ((prev_direction - 2) * (prev_direction % 2));
        egoCar.y_pos += ((prev_direction - 1) * ((prev_direction+ 1) % 2));
        //進入不可の場所に入った場合
        if(map::judgeAccessibility(egoCar.x_pos, egoCar.y_pos) == false){
            egoCar.status = kCollision;
            egoCar.x_pos = temp_x_pos;
            egoCar.y_pos = temp_y_pos;
            return;
        }
        //旋回した方向に1マス動く
        temp_x_pos = egoCar.x_pos;
        temp_y_pos = egoCar.y_pos;
        egoCar.x_pos += ((static_cast<int>(egoCar.direction) - 2) * (static_cast<int>(egoCar.direction) % 2));
        egoCar.y_pos += ((static_cast<int>(egoCar.direction) - 1) * ((static_cast<int>(egoCar.direction) + 1) % 2));
        //進入不可の場所に入った場合
        if(map::judgeAccessibility(egoCar.x_pos, egoCar.y_pos) == false){
            egoCar.status = kCollision;
            egoCar.x_pos = temp_x_pos;
            egoCar.y_pos = temp_y_pos;
            return;
        }
    }
    egoCar.status = kOK;
}

bool judgeSpeeding(void){
    std::string speed_limit = map::getSpeedLimit(egoCar.x_pos, egoCar.y_pos);
    bool output = false;

    if(speed_limit == CAR_SPD_LOW){
        if(static_cast<int>(egoCar.speed) >= static_cast<int>(kMidSpeed))output = true;
    }else if(speed_limit == CAR_SPD_MID){
        if(egoCar.speed == kHighSpeed)output = true;
    }else if(speed_limit == CAR_SPD_HIGH){
        if(egoCar.speed == kStop)output = true;
    }
    return output;
}

//車両方向を文字列で出力する。
std::string getCarDirection(void){
    std::string output;
    switch(egoCar.direction){
        case kNorth:{
            output = "North";
            break;
        }case kEast:{
            output = "East";
            break;
        }case kSouth:{
            output = "South";
            break;
        }case kWest:{
            output = "West";
            break;
        }default:{
            output ="unknown";
            break;
        }
    }
    return output;
}

//車速を文字列で出力する。
std::string getCarSpeed(void){
    std::string output;
    switch(egoCar.speed){
        case kStop:{
            output = CAR_SPD_STOP;
            break;
        }case kLowSpeed:{
            output = CAR_SPD_LOW;
            break;
        }case kMidSpeed:{
            output = CAR_SPD_MID;
            break;
        }case kHighSpeed:{
            output = CAR_SPD_HIGH;
            break;
        }default:{
            output ="unknown";
            break;
        }
    }
    return output;
}

//ガソリン残量を文字列で出力する。
std::string getCarGas(void){
    return std::to_string(egoCar.gas);
}

//自車位置を渡す。
void getCarPos(int& x_pos, int& y_pos){
    x_pos = egoCar.x_pos;
    y_pos = egoCar.y_pos;
}

//ステータス状態を文字列で出力する。
std::string getCarStatus(void){
    std::string output;
    switch(egoCar.status){
        case kOK:{
            output = "OK";
            break;
        }case kTurnL:{
            output = "Turn Left";
            break;
        }case kTurnR:{
            output = "Turn Right";
            break;
        }case kGasEmpty:{
            output = "Gas Empty";
            break;
        }case kSpeeding:{
            output = CAR_STT_SPD_MES;
            break;
        }case kCollision:{
            output = CAR_STT_COL_MES;
            break;
        }case kExit:{
            output =  CAR_STT_EXT_MES;
            break;
        }default:{
            output = "unknown status";
            break;
        }
    }
    return output;
}

//車両の向きのマークを出力する。
std::string getcarDirectionMark(){
    std::string output;
    switch(egoCar.direction){
        case kNorth:{
            output = "▲";
            break;
        }case kEast:{
            output = "▶";
            break;
        }case kSouth:{
            output = "▼";
            break;
        }case kWest:{
            output = "◀";
            break;
        }default:{
            output ="◆";
            break;
        }
    }
    return output;
}

void setCarGas(void){
    egoCar.gas = INIT_GAS;
}

}