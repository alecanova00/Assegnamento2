//
// Created by Alessandro Canova on 01/01/21.
//

#ifndef ASSEGNAMENTO_2_TIMETABLE_H
#define ASSEGNAMENTO_2_TIMETABLE_H

#include "Train.h"
#include <vector>

static std::vector<int> timeConversion(int time){
    std::vector<int> v(3);
    int hour = (int)time/60;

    if(hour >23){
        v[3]=1;
        hour-=24;
    }else v[3]=0;
    v[0] = hour;

    int minutes = (int)time%60;
    v[1]=minutes;
    return v;

}

class TrainTimeTable{
private:
    Train train;
    int stationType;
    std::vector<int> times;
public:

    TrainTimeTable(Train t, int st, std::vector<int> tm);

    void setOffset(); //imposta il ritardo
    void toString() const; //stampa la riga del tabellone relativa a un treno

    ~TrainTimeTable();
};

class TimeTable {
private:
    TrainTimeTable ttt;
public:
    TimeTable(std::string file);

    void setOffset(Train t); //imposta il ritardo
    void toString() const; //stampa l'intero tabellone

    ~TimeTable();
};


#endif //ASSEGNAMENTO_2_TIMETABLE_H
