//
// Created by Alessandro Visentin on 04/01/21.
//
#pragma once
#include "Train.h"
 class High_speed_train:public Train
{
	High_speed_train(int speed, StationLink stns, int nmb, bool forward);
	High_speed_train(int speed,const StationLink* stns, int nmb, bool forward);
	High_speed_train(const High_speed_train& train) noexcept;
	High_speed_train(const High_speed_train&& train) noexcept;
	High_speed_train& operator= (High_speed_train& train)noexcept;
	High_speed_train& operator= (High_speed_train&& train)noexcept;
	~High_speed_train();
	void move();
	static const int MAX_SPEED = 240;
	static const Train_type TYPE = Train_type::High_speed;
private:
	StationLink* pick(const StationLink* stns);
};