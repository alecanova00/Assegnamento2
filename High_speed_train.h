//
// Created by Alessandro Visentin on 04/01/21.
//
#pragma once
#include "Train.h"
 class High_speed_train:public Train
{
	High_speed_train(int speed, TimeTable* tbl);
	High_speed_train(const High_speed_train& train) noexcept;
	High_speed_train(const High_speed_train&& train) noexcept;
	High_speed_train& operator= (High_speed_train& train)noexcept;
	High_speed_train& operator= (High_speed_train&& train)noexcept;
	~High_speed_train();
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
	const int MAX_SPEED = 240;
	Train_type type = Train_type::High_speed_train;
};