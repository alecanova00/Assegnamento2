/**
 * Cosmin Catalin Popa 1225227
 * 
 * Classe StationLink che servirà a memorizzare le stazioni per poi metterle in ordine come una lista
 * 
 * 
*/



#include <iostream>
#include <string>
#include "Station.h"

using namespace std;


class StationLink{

    
    
    
    
    Station* station;                       //puntatore alla stazione memorizzata
    StationLink* next_station_link;         //puntatore al nodo sucessivo
    StationLink* previous_station_link;     //puntatore al nodo precedente


    public:

        StationLink(Station* st,StationLink* ps, StationLink* ns);  //construttore standard che salva la station (unico modo per assegnare una station ad un nodo) e i nodi sucessivi e precedenti
        ~StationLink();
        
        Station* get_station();                     //return del puntatore alla station
        StationLink* get_next_link();               //return del puntatore al nodo sucessivo
        StationLink* get_previous_link();           //return del puntatore al nodo precedente
        void set_next_link(StationLink* sl);        //set del puntatore al nodo sucessivo
        void set_previous_link(StationLink* sl);    //set del puntatore al nodo precedente


        
};














