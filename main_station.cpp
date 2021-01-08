
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include "StationLink.h"


using namespace std;


string FILE_NAME = "line_description.txt";
string FILE_DELIMITER = "#";




int file_size(){
    
    string line;
    ifstream myfile(FILE_NAME);
    
    int count = 0;

    if(myfile.is_open()){
        while (getline(myfile,line))
        {
            count++;
        }
        
        myfile.close();
    
    }
    
    count--;
    
    return count;
    
}



StationLink* read_file(){
    string line;
    ifstream myfile(FILE_NAME);
    int fsize = file_size();

    StationLink* sl;
    StationLink* first;
    string station_name;
    int station_type;
    double station_distance;
    int counter = 0;
    

    if(myfile.is_open()){
        
        

        while (getline(myfile,line)){
            
            
            if(counter == 0){
                sl = new StationLink(new PrimaryStation(line,0),nullptr,nullptr);
                first = sl;
                counter++;
                
            }
            else{

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
            
            
        }

        myfile.close();

    }
    return first;

}

void print(string s){
    cout << s << "\n";
}
void print(double s){
    cout << s << "\n";
}
void print(int s){
    cout << s << "\n";
}
void print(bool s){
    cout << s << "\n";
}


int main (void){



    vector<int> trains(15);

    for(int i = 0; i < 15; i++){
        trains[i] = i;
    }
    
    
    
    StationLink* first = read_file(); // non va mai modificato perchè bisogna conoscere sempre il primo
    StationLink* sl = first;
    
    while(sl != 0){     //modo per far scorrere l'intera lista
 
        cout << "Nome stazione:\t"<< sl->get_station()->get_station_name() <<"\n";
        cout << "Distanza stazione:\t"<<sl->get_station()->get_station_distance()<<"\n";
        cout << "Tipo stazione:\t"<<sl->get_station()->get_station_type()<<"\n";
        sl = sl->get_next_link();
        
    }
    


/*              Test con dei treni

    vector<int> trains(15);

    for(int i = 0; i < 15; i++){
        trains[i] = i;
    }

    
    
    
    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[0],0);
    }   
    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[1],0);
    } 
    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[2],0);
    } 

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));
    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[2],0);
    } 

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));
    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[2],0);
    } 

    print(first->get_station()->train_pause_time(trains[0]));
    print(first->get_station()->train_pause_time(trains[1]));

    if(first->get_station()->is_rail_free(0)) {
        first->get_station()->set_on_rail(trains[2],0);
    } 
    print(first->get_station()->train_pause_time(trains[2]));



    */
    


    
    

    

    return 0;

}