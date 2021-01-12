
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

#include "High_speed_train.h"
#include "High_speed_train_super.h"
#include "Regional_train.h"
#include "TimeTable.h"






using namespace std;


string const STATION_FILE_NAME = "../line_description.txt";
string const TIMETABLE_FILE_NAME = "../timetables.txt";

string const FILE_DELIMITER = "#";

void print(string s){
    cout<<s<<"\n";
}


int station_file_size(){
    
    string line;
    ifstream myfile(STATION_FILE_NAME);
    
    myfile.exceptions (ifstream::badbit);

    int count = 0;

    try{
        myfile.is_open();
        while (getline(myfile,line))
        {
            count++;
        }

    }
    catch(const ifstream::failure& e){
        cout << "ERRORE APERTURA/LETTURA FILE STAZIONI\n";
    }

    myfile.close();
    
    count--;
    
    return count;
    
}

StationLink* read_station_file(){
    string line;
    ifstream myfile(STATION_FILE_NAME);
    myfile.exceptions (ifstream::badbit);
    int fsize = station_file_size();

    StationLink* sl = nullptr;
    StationLink* first = nullptr;
    string station_name;
    int station_type;
    double station_distance;
    int counter = 0;
    
    try{
        myfile.is_open();
        while (getline(myfile,line)){
            
            
            if(counter == 0){
                sl = new StationLink(new PrimaryStation(line,0),nullptr,nullptr);
                first = sl;
                counter++;
                
            }
            else{

                if(line != ""){
                    station_name = line.substr(0,line.find(FILE_DELIMITER));
                    line.erase(0,station_name.length()+1);

                    station_type = stoi(line.substr(0,line.find(FILE_DELIMITER)));   
                    line.erase(0,to_string(station_type).length()+1);

                    station_distance = stod(line.substr(0,line.find(FILE_DELIMITER)));
                    line.erase(0,to_string(station_distance).length()+1);

                

                    if(station_type == 0){
                        sl->set_next_link(new StationLink(new PrimaryStation(station_name,station_distance),sl,nullptr)) ;
                        sl = sl->get_next_link();  
                    }
                    else{
                        sl->set_next_link(new StationLink(new SecondaryStation(station_name,station_distance),sl,nullptr)) ;
                        sl = sl->get_next_link(); 
                    }
                
                }

                else{
                    cout << "ERRORE LETTURA DATI DAL FILE DELLE STAZIONI\n";
                }

                

            }
            
            
        }
    }
    catch(const ifstream::failure& e){
        cout << "ERRORE APERTURA/LETTURA FILE STAZIONI\n";
    
    }   

    myfile.close();

    
    return first;

}

StationLink* invert_station_link(StationLink* first){

    StationLink* sl = first;

    while(sl->get_next_link() != 0){     //modo per far scorrere l'intera lista

        sl = sl->get_next_link();
        
    }

    while(sl->get_next_link() != 0){

        sl->set_next_link(sl->get_previous_link());
        sl->set_previous_link(nullptr);
        sl = sl->get_next_link();
    }

    return sl;

}


int main (void){

    //print("1");
    StationLink* first = read_station_file();
    StationLink* last = invert_station_link(read_station_file());

    StationLink* sl = first;

    while(sl != 0){     //modo per far scorrere l'intera lista
        cout << "Nome stazione:\t"<< sl->get_station()->get_station_name() <<"\n";
        cout << "Distanza stazione:\t"<<sl->get_station()->get_station_distance()<<"\n";
        cout << "Tipo stazione:\t"<<sl->get_station()->get_station_type()<<"\n";


        sl = sl->get_next_link();
        
    }

/*
    sl = last;
    while(sl != 0){     //modo per far scorrere l'intera lista
        cout << "Nome stazione:\t"<< sl->get_station()->get_station_name() <<"\n";
        cout << "Distanza stazione:\t"<<sl->get_station()->get_station_distance()<<"\n";
        cout << "Tipo stazione:\t"<<sl->get_station()->get_station_type()<<"\n";

        sl = sl->get_next_link();
        
    }
    */
    
    
 
    TimeTable timetable(TIMETABLE_FILE_NAME);



   


    list<Train> trains;
    
   
    for(int i = 0; i < timetable.getTimeTableSize(); i++){
      
        if(timetable.getTrainType(i) == Train_type::Regional){
            
            trains.push_back(Regional_train(120,first,timetable.getTrainNumber(i),!timetable.getStationType(i)));

        }
        else if(timetable.getTrainType(i) == Train_type::High_speed){

            trains.push_back(High_speed_train(200,first,timetable.getTrainNumber(i),!timetable.getStationType(i)));

        }

        else{

            trains.push_back(High_speed_train_super(280,first,timetable.getTrainNumber(i),!timetable.getStationType(i)));

        }
      
        
    }
   

    //cout << "\n"<<trains.front().get_train_number();



    
    timetable.toString();
    print("8");
    timetable.chechOrari(&trains);
print("9");
    cout << "\n\n\n";

    timetable.toString();
print("10");





/*
    int tempo = 0;

    while(tempo <= 1440){
        
        







    }


*/

    








    
    
    
     // non va mai modificato perchè bisogna conoscere sempre il primo
    /*StationLink* sl = first;
    
    while(sl != 0){     //modo per far scorrere l'intera lista
 
        cout << "Nome stazione:\t"<< sl->get_station()->get_station_name() <<"\n";
        cout << "Distanza stazione:\t"<<sl->get_station()->get_station_distance()<<"\n";
        cout << "Tipo stazione:\t"<<sl->get_station()->get_station_type()<<"\n";
        sl = sl->get_next_link();
        
    }*/
    



    

    return 0;

}