/**
 * 
 * Cosmin Catalin Popa 1225227 
 * 
 * Classe station che descrive una stazione e le sue interazioni con i treni
 * 
 * 
 * 
*/



#ifndef Station


#include <iostream>
#include <string>
#include <vector>
#include "Rail.h"

using namespace std;






class Station{

    private:

        string station_name;            //variabile che memorizza il nome della stazione
        double station_distance;        //variabile che memorizza la distanza dalla stazione di origine
        Rail* standard_rail_forward;    //puntatore ai binari che vanno dall'origine al capolinea
        Rail* standard_rail_backward;   //puntatore ai binari che vanno dal capolinea all'origine

 
        vector<int> parking;            //vettore che funge da parcheggio nel caso i binari siano tutti occupati
        

        

        bool get_standard_rail_forward_status(int index);
        bool get_standard_rail_backward_status(int index);

        void set_standard_rail_forward_status(int index,bool status);
        void set_standard_rail_backward_status(bool status);



    public:

        

        Station();                        //costruttore di default
        Station(string st,double sd);     //costruttore standard che inizializza una station

        


        ~Station();                       




        

        string get_station_name();      //get della variabile station_name
        double get_station_distance();  //get della variabile station_distance
        virtual int get_station_type(); //get del tipo di stazione, ogni derivata da station avrà l'override di questa funzione

        bool is_rail_free(int direction);  //return true se c'è un binario libero, false se tutti occupati per quella direzione

        Rail* search_rail(int train_number, int direction); //return di un binario in cui dato il numero del treno e la direzione ha salvato in se un treno

        bool set_on_rail(int train_number,int direction);  //funzione che dato il numero di un treno e la sua direzione lo salva in un binario se ce ne sono liberi,return false se il binario non era libero



        int train_pause_time(int train_number);  // return il tempo che manca al treno prima di partire

        void free_train(Rail* r);               //dato un binario invoca la funzione clear_rail()

        void set_on_parking(int train);         //set di un treno nel parcheggio

        bool is_train_turn(int train);    //metodo che controlla se il treno richiesto si trova nella prima posizione della coda, return true se il treno puo andare su un binario, viene tolto dal vector automaticamente



        





};


class PrimaryStation : public Station{  //classe derivata da station che fa l'override della funzione get_station_type() che avrà un return di 0 indicando così il suo tipo

    public:
        PrimaryStation(string sn,double sd) : Station(sn,sd){};

        int get_station_type() override;

};




class SecondaryStation : public Station{//classe derivata da station che fa l'override della funzione get_station_type() che avrà un return di 1 indicando così il suo tipo 

   



    public:

        SecondaryStation(string sn,double sd):Station(sn,sd){};

        int get_station_type() override;
        


};






#endif