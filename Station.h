
#ifndef Station


#include <iostream>
#include <string>
#include <vector>
#include "Rail.h"

using namespace std;






class Station{

    private:

        string station_name; 
        double station_distance;
        Rail* standard_rail_forward;
        Rail* standard_rail_backward;

 
        vector<int> parking;
        

        

        bool get_standard_rail_forward_status(int index);
        bool get_standard_rail_backward_status(int index);

        void set_standard_rail_forward_status(int index,bool status);
        void set_standard_rail_backward_status(bool status);



    public:

        

        Station();
        Station(string st,double sd);

        


        ~Station();




        

        string get_station_name();
        double get_station_distance();
        virtual int get_station_type();

        bool is_rail_free(int direction);  //return true se libero

        Rail* search_rail(int train_number, int direction);

        bool set_on_rail(int train_number,int direction);  //return false se il binario non era libero



        int train_pause_time(int train_number);  // return il tempo che manca se 0 si parte se -1 errore inaspettato

        void free_train(Rail* r);

        void set_on_parking(int train);

        bool is_train_turn(int train);    //return true se il treno puo andare su un binario, viene tolto dal vector automaticamente



        





};


class PrimaryStation : public Station{

    public:
        PrimaryStation(string sn,double sd) : Station(sn,sd){};

        int get_station_type() override;

};




class SecondaryStation : public Station{

   



    public:

        SecondaryStation(string sn,double sd):Station(sn,sd){};

        int get_station_type() override;
        


};






#endif