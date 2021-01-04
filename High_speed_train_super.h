//
// Created by Alessandro Visentin on 04/01/21.
//
#pragma once
#include "Train.h"
class High_speed_train_super:public Train
{
public:
	High_speed_train_super(int speed,TimeTable* tbl);
	High_speed_train_super(const High_speed_train_super& train) noexcept;
	High_speed_train_super(const High_speed_train_super&& train) noexcept;
	High_speed_train_super& operator= (High_speed_train_super& train)noexcept;
	High_speed_train_super& operator= (High_speed_train_super&& train)noexcept;
	~High_speed_train_super();
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
	const int MAX_SPEED = 300;
	Train_type type = Train_type::Super_high_speed;
};

