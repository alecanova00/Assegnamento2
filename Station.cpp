#include "StationLink.h"
#include "Station.h"
#include "Rail.h"

using namespace std;



Rail::Rail(){

    train = -1;
    time = 0;

}

void Rail::set_train(int t){
    train = t;
}

int Rail::get_train(){
    return train;
}

void Rail::clear_rail(){
    train = -1;
}

int Rail::get_max_speed(){
    return MAX_SPEED;
}

int Rail::get_speed_limit_length(){
    return SPEED_LIMIT_LENGTH;
}

int Rail::get_time(){
    return time;
}

bool Rail::is_free(){
    return !(train == -1);
}

void Rail::decrease_time(){
    if(time != 0) time--;
}




/////////////////////////////STATION////////////////////////7



Station::Station(){
    Station("default",50);
}

Station::Station(string sn = "default",double sd = 50){
    station_name = sn;
    station_distance = sd;
}

Station::~Station(){
    station_name = "";
    station_distance = 0;
    delete[] standard_rail_forward;
    delete[] standard_rail_backward; 
}

void Station::set_station_name(string sn){
    station_name = sn;
}

void Station::set_station_distance(double sd){
    station_distance = sd;
}

string Station::get_station_name(){
    return station_name;
}

double Station::get_station_distance(){
    return station_distance;
}

int Station::get_station_type(){
    return 0;
}

bool Station::get_standard_rail_forward_status(int index){
    return standard_rail_forward[index]->is_free();
}
bool Station::get_standard_rail_backward_status(int index){
    return standard_rail_backward[index]->is_free();
}


bool Station::is_rail_free(int direction){

    bool status;

    if(direction = 0){

        for(int i = 0; i < 2; i++){
            status = get_standard_rail_forward_status(i);
        }
    }
    


};








/*void Station::set_standard_rail_forward_status(int index,bool status,Train train){
    standard_rail_forward[index]->
}

 */




///////////////////////////STATION Link///////////////////




StationLink::StationLink(Station* st,StationLink* ns,StationLink* ps){
    station = st;
    next_station_link = ns;
    previous_station_link = ps;
}

StationLink::~StationLink(){
    delete next_station_link;
    delete previous_station_link;
    station = nullptr;
}


Station* StationLink::get_station(){
    return station;
}


StationLink* StationLink::get_next_link(){
    return next_station_link;
}

StationLink* StationLink::get_previous_link(){
    return previous_station_link;
}

void StationLink::set_next_link(StationLink* sl){
    next_station_link = sl;
}

void StationLink::set_previous_link(StationLink* sl){
    previous_station_link = sl;
}
