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
            int st = stoi(token);
            line.erase(0,token.length()+1);

            token = line.substr(0,line.find(delimiter));
            int traintype = stoi(token);
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
        vector<int> conversion = timeConversion(times[i]);
        cout<<conversion[0]<<":"<<conversion[1]<<"\t";
        cout<<" -> ";
        vector<int>conversionDelay = timeConversion((*delays)[i]);
        cout<<conversionDelay[0]<<":"<<conversionDelay[1]<<"   |   ";
    }
}


TrainTimeTable::TrainTimeTable(int t, StationType st, TrainType tt, std::vector<int> tm) {
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

TrainTimeTable::~TrainTimeTable() {

}

TimeTable::~TimeTable() {

}