#include <iostream>

using namespace std;


    class Rail{

        int train;
        int const MAX_SPEED = 80;
        int const SPEED_LIMIT_LENGTH = 10;
        int time;
        

        public:

            Rail();

            void set_train(int t);
            int get_train();

            void clear_rail();

            int get_max_speed();
            int get_speed_limit_length();
            int get_time();

            bool is_free();

            void decrease_time();

    };








    







