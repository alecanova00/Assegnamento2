
#include <iostream>
#include <string>
#include "Station.h"

using namespace std;


class StationLink{

    
    Station* station;
    StationLink* next_station_link;
    StationLink* previous_station_link;


    public:

        StationLink(Station* st,StationLink* ns, StationLink* ps);
        ~StationLink();
        
        Station* get_station();
        StationLink* get_next_link();
        StationLink* get_previous_link();
        void set_next_link(StationLink* sl);
        void set_previous_link(StationLink* sl);
        
};











