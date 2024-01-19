#include "map.h"

namespace map{

//定数
const mapCell kInvalidCell = {"*", "", kCellInvalid, kNormal};
const mapCell kNormalStreet = {" ", "municipal road", kCellvalid, kNormal};
const mapCell kNarrowStreet = {"'", "narrow road", kCellvalid, kOnlyLowSpeed};

//関数宣言
void outOfMap(void);
void invalidArea(int x_postion, int y_position, int x_size, int y_size);
void lonStreet(int x_position, int y_position, int street_length, mapCell street_status);
void latStreet(int x_position, int y_position, int street_length, mapCell street_status);
void pointLocation(int x_position, int y_position, mapCell point_status);

//静的変数
static std::array<std::array<mapCell,  MAP_X_RAW_SIZE>, MAP_Y_RAW_SIZE> stage_map_{{}};

//マップの初期化
void initMap(void){
    for(int i = 0; i < stage_map_.size(); i++){
        for (int j = 0; j < stage_map_[i].size(); j++){
            stage_map_[i][j] = kNormalStreet;
        }
    }

    outOfMap();

    try{
        invalidArea(2, 2, MAP_X_SIZE - 4 ,MAP_Y_SIZE - 4);   
        latStreet(2, 8, 36, {" ", "ew_street_1st", kCellvalid, kNormal});
        latStreet(2, 12, 36, {" ", "ew_street_2nd", kCellvalid, kNormal});
        latStreet(2, 17, 36, {" ", "ew_street_3rd", kCellvalid, kNormal});

        lonStreet(5, 2, 20, {" ", "ns_street_1st", kCellvalid, kNormal});
        lonStreet(18, 2, 20, {" ", "ns_street_2nd", kCellvalid, kNormal});
        
        lonStreet(25, 2, 5, kNormalStreet);

        latStreet(19, 3, 1, kNarrowStreet);
        latStreet(19, 6, 1, kNarrowStreet);
        lonStreet(20, 3, 3, kNarrowStreet);

        lonStreet(25, 9, 2, kNarrowStreet);

        latStreet(28, 19, 1, kNarrowStreet);
        lonStreet(26, 18, 1, kNarrowStreet);

        //縦貫高速
        lonStreet(30, 1, 22, {"|", "traversal highway", kCellvalid, kHighway});
        //環状高速
        lonStreet(38, 1, 22, {"|", "Loop highway", kCellvalid, kHighway});
        lonStreet(1, 1, 22, {"|", "Loop highway", kCellvalid, kHighway});
        latStreet(1, 1, 37, {"-", "Loop highway", kCellvalid, kHighway});
        latStreet(1, 23, 37, {"-", "Loop highway", kCellvalid, kHighway});
        pointLocation(2, 2, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(3, 2, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(2, 3, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(36, 2, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(37, 2, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(37, 3, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(2, 22, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(3, 22, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(2, 21, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(36, 22, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(37, 21, {" ", "Loop highway", kCellvalid, kHighway});
        pointLocation(37, 22, {" ", "Loop highway", kCellvalid, kHighway});

        //ガソリンステーション 
        pointLocation(27, 19, {GAS_STATION, "GAS_station_A", kGasStation, kOnlyLowSpeed});
        pointLocation(20, 5, {GAS_STATION, "GAS_station_B", kGasStation, kOnlyLowSpeed});
        pointLocation(6, 9, {GAS_STATION, "GAS_station_C", kGasStation, kOnlyLowSpeed});
        //目的地
        pointLocation(25, 5, {TARGET_1, "station_A", kGoal, kNormal});
        pointLocation(34, 12, {TARGET_2, "station_B", kGoal, kNormal});
        pointLocation(5, 20, {TARGET_3, "station_C", kGoal, kNormal});

    }catch(const std::out_of_range& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//マップの非表示領域の作成
void outOfMap(void){
    for(int i = 0; i < MAP_INVALID_SPACE + 1; i++){
        for (int j = 0; j < stage_map_[i].size(); j++){
            stage_map_[i][j] = kInvalidCell;
        }
    }
    for(int i = MAP_Y_RAW_SIZE - 1- MAP_INVALID_SPACE; i < MAP_Y_RAW_SIZE; i++){
        for (int j = 0; j < stage_map_[i].size(); j++){
            stage_map_[i][j] = kInvalidCell;
        }   
    }
    for(int i = 0; i < stage_map_.size(); i++){
        for (int j = 0; j < MAP_INVALID_SPACE + 1; j++){
            stage_map_[i][j] = kInvalidCell;
        }
    }
    for(int i = 0; i < stage_map_.size(); i++){
        for (int j = MAP_X_RAW_SIZE - 1 - MAP_INVALID_SPACE; j < MAP_X_RAW_SIZE; j++){
            stage_map_[i][j] = kInvalidCell;
        }
    }
}

//指定した範囲の進入不可領域を作成する
void invalidArea(int x_position, int y_position, int x_size, int y_size){
    if(x_position < 0)throw std::out_of_range("input x_position is out of map.");
    if(y_position < 0)throw std::out_of_range("input y_position is out of map.");
    if(x_position + x_size > MAP_X_SIZE)throw std::out_of_range("input x_size + x_position is out of map.");
    if(y_position + y_size > MAP_Y_SIZE)throw std::out_of_range("input y_size + y_position is out of map.");

    for(int i = y_position + MAP_INVALID_SPACE; i < y_position + MAP_INVALID_SPACE + y_size; i++){
        for (int j = x_position + MAP_INVALID_SPACE; j < x_position + MAP_INVALID_SPACE + x_size; j++){
            stage_map_[i][j] = kInvalidCell;
        }
    }

}

//横方向の道を作成する。
void latStreet(int x_position, int y_position, int street_length, mapCell street_status){
    if(x_position < 0)throw std::out_of_range("input x_position is out of map.");
    if(y_position < 0 && y_position > MAP_Y_SIZE)throw std::out_of_range("input y_position is out of map.");
    if(x_position + street_length > MAP_X_SIZE)throw std::out_of_range("input street_length + x_position is out of map.");

    for (int x_pos = x_position + MAP_INVALID_SPACE; x_pos <= x_position + MAP_INVALID_SPACE + street_length; x_pos++){
        stage_map_[y_position + MAP_INVALID_SPACE][x_pos] = street_status;
    }
}

//縦方向の道を作成する。
void lonStreet(int x_position, int y_position, int street_length, mapCell street_status){
    if(x_position < 0 && x_position > MAP_X_SIZE)throw std::out_of_range("input x_position is out of map.");
    if(y_position < 0)throw std::out_of_range("input y_position is out of map.");
    if(y_position + street_length > MAP_Y_SIZE)throw std::out_of_range("input street_length + y_position is out of map.");

    for (int y_pos = y_position + MAP_INVALID_SPACE; y_pos <= y_position + MAP_INVALID_SPACE + street_length; y_pos++){
        stage_map_[y_pos][x_position + MAP_INVALID_SPACE] = street_status;
    }
}

//1マス地点の作成する。
void pointLocation(int x_position, int y_position, mapCell point_status){
    stage_map_[y_position + MAP_INVALID_SPACE][x_position + MAP_INVALID_SPACE] = point_status;
}

//マップを描写する。
void mapDisplay(int car_x_pos, int car_y_pos, std::string car_direction){
    if(car_x_pos < 0)throw std::out_of_range("input car_x_pos is out of map.");
    if(car_y_pos < 0)throw std::out_of_range("input car_y_pos is out of map.");
    if(car_x_pos > MAP_X_SIZE)throw std::out_of_range("input car_x_pos is out of map.");
    if(car_y_pos > MAP_Y_SIZE)throw std::out_of_range("car_y_pos is out of map.");

    for(int y_pos = MAP_INVALID_SPACE; y_pos < stage_map_.size() - MAP_INVALID_SPACE; y_pos++){
        for(int x_pos = MAP_INVALID_SPACE; x_pos < stage_map_[y_pos].size() - MAP_INVALID_SPACE; x_pos++){
            //自車がいる場所では、自車の進行方向のマークを描写する。
            if((y_pos == car_y_pos + MAP_INVALID_SPACE) && (x_pos == car_x_pos + MAP_INVALID_SPACE)){
                std::cout << car_direction;
            }else{
                std::cout << stage_map_[y_pos][x_pos].cellMark;
            }
        }
        std::cout << std::endl;
    }
}

//道路の名前を出力する。
std::string getStreetName(int x_pos, int y_pos){
    return stage_map_[y_pos + MAP_INVALID_SPACE][x_pos + MAP_INVALID_SPACE].streetName;
}

//指定の領域に対する進入可否を判断する。
bool judgeAccessibility(int x_pos, int y_pos){
    if(stage_map_[y_pos + MAP_INVALID_SPACE][x_pos + MAP_INVALID_SPACE].cellStatus != kCellInvalid)return true;
    else return false;
}

//指定したセルのマークを出力する。
std::string getMapCellMark(int x_pos, int y_pos){
    return stage_map_[y_pos + MAP_INVALID_SPACE][x_pos + MAP_INVALID_SPACE].cellMark;
}

//指定したセルの速度制限値を出力する。
std::string getSpeedLimit(int x_pos, int y_pos){
    std::string output;
    switch(stage_map_[y_pos + MAP_INVALID_SPACE][x_pos + MAP_INVALID_SPACE].cellSpeedLimit){
        case kOnlyLowSpeed:{
            output =  CAR_SPD_LOW;
            break;
        }case kHighway:{
            output = CAR_SPD_HIGH;
            break;
        }default:{
            output = CAR_SPD_MID;
            break;
        }

    }
    return output;
}

}