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
private:
	const int MAX_SPEED = 240;
	Train_type type = Train_type::High_speed_train;
};