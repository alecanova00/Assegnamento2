//
// Created by Alessandro Canova on 01/01/21.
//

#include "TimeTable.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

TimeTable::TimeTable(std::string file) {
    ifstream timetables(file);
    string delimiter = "#";
    string line;
    if(timetables.is_open()){
        while (getline(timetables, line)){
            string token;
            token = line.substr(0,line.find(delimiter));
            int train = stoi(token);
            line.erase(0,token.length()+1);

            token = line.substr(0,line.find(delimiter));
            int st = static_cast<int>(stoi(token));
            line.erase(0,token.length()+1);

            token = line.substr(0,line.find(delimiter));
            Train_type traintype = static_cast<Train_type>(stoi(token));
            line.erase(0,token.length()+1);

            vector<int> times;

            while (true){
                token = line.substr(0,line.find(delimiter));
                if(token=="")break;
                times.push_back(stoi(token));
                line.erase(0,token.length()+1);
            }

            TrainTimeTable train_time_table(train, st, traintype, times);
            ttt.push_back(train_time_table);

        }
        timetables.close();


    }else cout<<"file corrotto\n";


}

void TrainTimeTable::toString() const {
    cout<<"treno: "<<train<<", tipo stazione: "<<stationType<<", tipo treno: "<<trainType<<", orari: ";
    for(int i=0; i<times.size(); i++){
        /*
        vector<int> conversion = timeConversion(times[i]);
        cout<<conversion[0]<<":"<<conversion[1]<<"\t";
        cout<<" -> ";
        vector<int>conversionDelay = timeConversion((*delays)[i]);
        cout<<conversionDelay[0]<<":"<<conversionDelay[1]<<"   |   ";
*/
        string time = timeConversion(times[i]);
        cout<<time<<" -> "<<timeConversion((*delays)[i])<<"   |   ";
        //cout<<times[i]<<" -> "<<(*delays)[i]<<"   |   ";
    }
}


TrainTimeTable::TrainTimeTable(int t, int st, Train_type tt, std::vector<int> tm) {
    train = t;
    stationType = st;
    trainType = tt;
    times = tm;
    delays = new vector<int>(tm.size());
}

void TrainTimeTable::setDelay(int delay, int station) {
    for(int i = station; i<(*delays).size(); i++){
        (*delays)[i] += delay;
    }
}

void TimeTable::toString() const {
    for(int i=0;i<ttt.size(); i++){
        ttt[i].toString();
        cout<<"\n";
    }
}

void TimeTable::setDelay(int train, int delay, int station) {
    for(int i=0; i<ttt.size(); i++){
        if(ttt[i].getTrainNumber() == train){
            ttt[i].setDelay(delay, station);
            break;
        }
    }
}

void TimeTable::chechOrari(list<Train>* lista) {
    //foreach treni nella lista di tutti i treni

    //5 minuti di stop alle stazioni

    //decelerazione tot metri prima
    //conversione km -> metri

    list<Train>::iterator i;
    for(i = (*lista).begin(); i != (*lista).end(); i++){ //scorro la lista di treni ricevuta
        for(int j =0; j<ttt.size(); j++){//scorro la lista di orari salvata
            
            if(ttt[j].getTrainNumber() == (*i).get_train_number()){ //se l'elemento nella lista e l'elemento negli orari combaciano
                cout << "\nVector \t\n";
                vector<Station*> stations = (*i).get_train_path(); //stazioni che il treno deve fare
                cout << "\n dopo vector \t\n";
                double speed = (*i).get_cruise_speed()/3.6; //velocità del treno
                cout << "\nSPEEEEEEED \t" << speed << "\n";
                if(ttt[j].getTimes().size() < stations.size()){ //caso in cui ho un difetto di orari
                    vector<int> updatedTimes = ttt[j].getTimes();
                    for(int m=ttt[j].getTimes().size(); m < stations.size(); m++){
                        int distanceBetweenStations = (stations[m])->get_station_distance()-stations[m-1]->get_station_distance();
                        int time = (int)(distanceBetweenStations/speed)+10; //10 sta per il margine
                        updatedTimes.push_back(ttt[j].getTime(m-1)+time);
                    }
                    ttt[j].setTimes(&updatedTimes);
                }else if (ttt[j].getTimes().size() > stations.size()){ //caso in cui ho un eccesso di orari
                    vector<int> cuttedTimes (stations.size());
                    for(int m =0; m< stations.size(); m++){
                        cuttedTimes[m] = ttt[j].getTime(m);
                    }
                    ttt[j].setTimes(&cuttedTimes);
                }

                for (int ij = 0; ij < stations.size() - 1; ij++) { //aggiustamento degli orari
                    int distanceBetweenStations =
                            ((stations[ij + 1]->get_station_distance()*1000) - (stations[ij]->get_station_distance()*1000))-10000; //-10 perchè deve decellerare

                    int time_deceleration = ( 10000/(80/3.6) ) / 60; //tempo che impiega a percorrere gli ultimi 10km prima della stazione
                    int time = (int) time_deceleration + (distanceBetweenStations / speed + 1) + 5 ; //tempo totale



                    int predicted_time = ttt[j].getTimes()[ij + 1] - ttt[j].getTimes()[ij]; //tempo scritto negli orari
                    if (time != predicted_time) { //se il tempo scritto e quello calcolato sono diversi
                        ttt[j].setTime(ttt[j].getTime(ij) + time, ij + 1); //cambio l'orario in memoria con quello aggiornato
                    }
                }
            }
        }
    }
}

void TrainTimeTable::setTimes(const std::vector<int> * updatedTimes) {
    if((*updatedTimes).size() > times.size()){
        for(int i=times.size(); i<(*updatedTimes).size(); i++){
            times.push_back((*updatedTimes)[i]);
            delays->push_back(0);
        }
    }
    if((*updatedTimes).size() < times.size()){
        times.resize((*updatedTimes).size());
    }
    for(int i=0; i< (*updatedTimes).size(); i++){
        times[i] = (*updatedTimes)[i];
    }
}

void TrainTimeTable::setTime(const int updated_time, const int station) {
    times[station] = updated_time;
}

int TrainTimeTable::getTime(const int station) {
    return times[station];
}

TrainTimeTable::~TrainTimeTable() {

}

TimeTable::~TimeTable() {

}

int TimeTable::getArriveTime(const int train, const int station) {
    return ttt[train].getTime(station);
}
