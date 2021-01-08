

#ifndef Rail



#include <iostream>

using namespace std;


    class Rail{

        int train;
        int time;
        

        public:

            Rail();

            void set_train(int t);
            int get_train();

            void clear_rail();

            //int get_max_speed();
            //int get_speed_limit_length();
            void set_time(int t);
            int get_time();

            bool is_free();

            void decrease_time();

    };




#endif



    







