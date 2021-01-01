//
// Created by Alessandro Canova on 01/01/21.
//

#ifndef ASSEGNAMENTO_2_TIMETABLE_H
#define ASSEGNAMENTO_2_TIMETABLE_H

#include "Train.h"
#include <vector>
class TrainTimeTable{
private:
    Train train;
    int stationType;
    std::vector<int> times;
public:
    TrainTimeTable(Train t, int st, std::vector<int> tm);

    void setOffset();
    void toString() const; //stampa la riga del tabellone relativa a un treno

    ~TrainTimeTable();
};

class TimeTable {
private:
    TrainTimeTable ttt;
public:
    TimeTable(std::string file);

    void setOffset();
    void toString() const; //stampa l'intero tabellone

    ~TimeTable();
};


#endif //ASSEGNAMENTO_2_TIMETABLE_H
