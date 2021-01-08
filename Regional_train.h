//
// Created by Alessandro Visentin on 04/01/21.
//
#pragma once
#include "Train.h"
 class Regional_train:public Train
{
	Regional_train(int speed,StationLink stns,int nmb,bool forward);
	Regional_train(const Regional_train& train) noexcept;
	Regional_train(const Regional_train&& train) noexcept;
	Regional_train& operator= (Regional_train& train)noexcept;
	Regional_train& operator= (Regional_train&& train)noexcept;
	~Regional_train();
private:
	const int MAX_SPEED=160;
	Train_type type=Train_type::Regional;
};