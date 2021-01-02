#include <iostream>
#include <string>
#include "Rail.h"

using namespace std;





//template <typename T>
class Station{

    string station_name; 
    double station_distance;
    Rail* standard_rail_forward[2];
    Rail* standard_rail_backward[2];
    

    public:

        Station();
        Station(string st,double sd);
        ~Station();




        void set_station_name(string sn);
        void set_station_distance(double sd);

        string get_station_name();
        double get_station_distance();
        int get_station_type();

        bool get_standard_rail_forward_status(int index);
        bool get_standard_rail_backward_status(int index);

        void set_standard_rail_forward_status(int index,bool status);
        void set_standard_rail_backward_status(bool status);











        //T* parkinglot;





};

class SecondaryStation : public Station{

    bool transition_rail_forward;
    bool transition_rail_backward;



    public:


        int get_station_type();

        bool get_transition_rail_forward_status();
        bool get_transition_rail_backward_status();

        void set_transition_rail_forward_status(bool status);
        void set_transition_rail_backward_status(bool status);

};






