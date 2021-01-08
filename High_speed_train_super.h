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
private:
	const int MAX_SPEED = 300;
	Train_type type = Train_type::Super_high_speed;
	StationLink* High_speed_train::pick(const StationLink* stns)
};

