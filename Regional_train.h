#pragma once
#include "Train.h"
 class Regional_train:public Train
{
	Regional_train(int speed);
	 void move();
	 bool can_move();
	 Train_type get_type();
	 int get_max_speed();
	 int get_cruise_speed();
	 int get_actual_speed();
	 int get_train_number();
	 int get_delay();
	 Station get_actual_station();
	 Station get_next_station();
	 int get_remaining_time();
private:
	const int MAX_SPEED=160;
	int CRUISE_SPEED;
	int actual_speed;
	int rail_position;
	int delay;
	Timetable table;
	Station actual_station;
	Station next_statiom;
	int next_station_distance;
	Train_type type=Train_type::Regional;
};