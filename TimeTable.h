//
// Created by Alessandro Canova on 01/01/21.
//

#ifndef ASSEGNAMENTO_2_TIMETABLE_H
#define ASSEGNAMENTO_2_TIMETABLE_H

#include <vector>
#include <list>
#include <string>
#include "Train.h"
#include "Train_type.h"

static std::string timeConversion(int time){
    std::string h; std::string m;
    int hour = (int)time/60;
    if(hour >23)hour-=24;
    if(hour<12) h="0";
    h+=std::to_string(hour);
    int minutes = (int)time%60;
    if(minutes < 10) m="0";
    m+=std::to_string(minutes);
    return h+":"+m;
}
/*
enum StationType{
    origine = 0, capolinea = 1
};
enum TrainType{
    regionale = 1, alta_velocita = 2, alta_velocita_super = 3
};*/


class TrainTimeTable{
private:
    int train;
    int stationType;
    Train_type trainType;
    std::vector<int> times;
    std::vector<int>* delays;
public:

    TrainTimeTable(int t, int st, Train_type tt, std::vector<int> tm);

    void setDelay(int delay, int station); //imposta il ritardo
    void toString() const; //stampa la riga del tabellone relativa a un treno

    int getTrainNumber(){return train;}
    Train_type getTrainType(){return trainType;}
    int getStationType(){return stationType;}
    std::vector<int> getTimes(){return times;}
    std::vector<int>* getDelays(){return delays;}
    void setTime (const int , const int);
    int getTime(const int);
    void setTimes(const std::vector<int>*);
    ~TrainTimeTable();
};

class TimeTable {
private:
    std::vector<TrainTimeTable> ttt;
public:
    TimeTable(std::string file);
    void chechOrari(std::list<Train*>*);
    void setDelay(int train, int delay, int station); //imposta il ritardo
    void toString() const; //stampa l'intero tabellone

    int getTrainNumber(const int train) {return ttt[train].getTrainNumber();};
    Train_type getTrainType(int train) { return ttt[train].getTrainType(); };
    int getStationType(int train) { return ttt[train].getStationType(); };
    int getTimeTableSize(){return ttt.size();}
    int getStartTime(const int train){return ttt[train].getTime(0);}

    int getArriveTime(const int train, const int station);
    int getTrainArriveTime(const int trainNumber, const int station);

    ~TimeTable();
};


#endif //ASSEGNAMENTO_2_TIMETABLE_H
