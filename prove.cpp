
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>



using namespace std;


int main (void){


    

    string line;
    ifstream myfile("line_description.txt");
    string delimiter = "#";


    string origin_station;
    string* station_name;
    int* station_type;
    double* station_distance;


    station_name = new string[10];
    station_type = new int[10];
    station_distance = new double[10];

    if(myfile.is_open()){
        
        int c = 0;
        int counter = 0;

        while ( getline(myfile,line)){
            if(c == 0){
                origin_station = line;
                c++;
            }
            else{
                string token;

                token = line.substr(0,line.find(delimiter));
                station_name[counter] = token;
                line.erase(0,token.length()+1);

                token = line.substr(0,line.find(delimiter));
                station_type[counter] = stoi(token);
                line.erase(0,token.length()+1);

                token = line.substr(0,line.find(delimiter));
                station_distance[counter] = stod(token);
                line.erase(0,token.length()+1);

                counter++;

            }
            
        }

        myfile.close();

    }

    else cout << "errore";

    cout << "Stazione di origine:\t" << origin_station<<"\n"; 

    for(int i = 0; i < 4; i++){
        cout << "nome stazione:\t" << station_name[i] << "\t tipo stazione:   "<<station_type[i]<<"\t distanza da origine:   "<<station_distance[i]<<"\n";
    }

    return 0;

}