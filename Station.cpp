
#include "StationLink.h"



using namespace std;



Rail::Rail(){

    train = -1;
    time = 0;

}

Rail::~Rail(){

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

void Rail::set_time(int t){
    time = t;
}

int Rail::get_time(){
    return time;
}

bool Rail::is_free(){
    return (train == -1);
}

void Rail::decrease_time(){
    if(time != -1) time--;
}







/////////////////////////////STATION////////////////////////








Station::Station(){
    Station("default",50);
}

Station::Station(string sn ,double sd){
    station_name = sn;
    station_distance = sd;
    standard_rail_forward = new Rail[2];
    standard_rail_backward = new Rail[2];
}

Station::~Station(){
    station_name = "";
    station_distance = 0;
    delete[] standard_rail_forward;
    delete[] standard_rail_backward; 
}



string Station::get_station_name() {
    return station_name;
}

double Station::get_station_distance() {
    return station_distance;
}

int Station::get_station_type(){
    return -1;
}


bool Station::get_standard_rail_forward_status(int index){
    return standard_rail_forward[index].is_free();
}
bool Station::get_standard_rail_backward_status(int index){
    return standard_rail_backward[index].is_free();
}


bool Station::is_rail_free(int direction){
    
    
    if(direction == 0){

        for(int i = 0; i < 2; i++){
             if(get_standard_rail_forward_status(i)) return true;
        }
        
    }
    else{
        for(int i = 0; i < 2; i++){
            if(get_standard_rail_backward_status(i)) return true;
        }

    }
    
    return false;


}

Rail* Station::search_rail(int train_number,int direction){

    if(direction == 0){
        for(int i = 0; i < 2; i++){
            if(standard_rail_forward[i].get_train() == train_number) return &standard_rail_forward[i];
    }
    }
    else{
        for(int i = 0; i < 2; i++){
            if(standard_rail_backward[i].get_train() == train_number) return &standard_rail_backward[i];
    }
    }

    return nullptr;


}


bool Station::set_on_rail(int train_number,int direction){

    Rail* r;
    if(is_rail_free(direction)){

        if(direction == 0) r = search_rail(-1,direction);        

        else r = search_rail(-1,direction);

        if(r != nullptr) {
            r->set_train(train_number);
            r->set_time(5);
        }
    }
    else{
        return false;
    }



}

int Station::train_pause_time(int train_number){

    Rail* r;

    r = search_rail(train_number,0);

    if(r == nullptr ){
        r = search_rail(train_number,1);
    }

    if(r == nullptr) return -1;
    else{
        int t =  r->get_time();
        r->decrease_time();
        if(r->get_time() < 0 ) free_train(r);
        return t;
    } 
    
}


void Station::free_train(Rail* r){
    
    if(r != nullptr) r->clear_rail();
    
}


void Station::set_on_parking(int train){
    parking.push_back(train);
}

bool Station::is_train_turn(int train){
    
    if(train == parking.front()){
        parking.erase(parking.begin());
        return true;
    }
    else{
        return false;
    }
    
}



int PrimaryStation::get_station_type(){
    return 0;
}



int SecondaryStation::get_station_type(){
    return 1;
}






///////////////////////////STATION Link///////////////////






StationLink::StationLink(Station* st,StationLink* ps,StationLink* ns){
    station = st;
    next_station_link = ns;
    previous_station_link = ps;
}

StationLink::~StationLink(){
    delete next_station_link;
    delete previous_station_link;
    delete station;
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



