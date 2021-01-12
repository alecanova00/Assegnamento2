/**
 * Cosmin Catalin Popa  1225227
 * 
 * Classe Rail che descrive il binario dove i treni si possono fermare
 * 
*/

#ifndef Rail



#include <iostream>

using namespace std;


    class Rail{

        int train;      // variabile che memorizza il numero del treno fermato sul binario  
        int time;       // variabile che memorizza quanto tempo il treno deve rimanere fermo sul binario
        

        public:

            Rail();     //costruttore di default inizializza train e time a -1 e 0

            void set_train(int t);  //set del valore train
            int get_train();        //get del valore get

            void clear_rail();      //set del valore train a -1 quindi binario vuoto

            //int get_max_speed();
            //int get_speed_limit_length();


            void set_time(int t);   //set del valore time
            int get_time();         //get del valore time

            bool is_free();         //return true nel caso il valore in train sia -1 quindi il binario vuoto, return false se train ha un valore positivo 

            void decrease_time();   //diminuisce il valore di time di uno fino a -1 quindi fino a quando il treno dovrà ripartire

            ~Rail();                
    };




#endif



    







