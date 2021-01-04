#pragma once
#include "Train.h"
 class Regional_train:public Train
{
	Regional_train(int speed, TimeTable* tbl);
	Regional_train(const Regional_train& train) noexcept;
	Regional_train(const Regional_train&& train) noexcept;
	Regional_train& operator= (Regional_train& train)noexcept;
	Regional_train& operator= (Regional_train&& train)noexcept;
	~Regional_train();
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
	Train_type type=Train_type::Regional;
};