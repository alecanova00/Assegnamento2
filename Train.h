//
// Created by Alessandro Visentin on 04/01/21.
//
#pragma once
#include "Station.h"
#include "StationLink.h"
class Train
{
	virtual void move();
	virtual bool can_move();
	virtual Train_type get_type();
	virtual int get_max_speed();
	virtual int get_cruise_speed();
	virtual int get_actual_speed();
	virtual int get_train_number();
	virtual int get_delay();
	virtual Station get_actual_station();
	virtual Station get_next_station();
	virtual int get_remaining_time();
protected:
	Train();
	virtual void start_from_station();
	virtual bool is_arrived();
	const int MAX_SPEED;
	const int STATION_SPEED=80;
	const int STATION_SAFE_DISTANCE = 5;
	int CRUISE_SPEED;
	int actual_speed;
	int rail_position;
	int delay;
	StationLink* actual_station;
	StationLink* next_station;
	int next_station_distance;
	int prev_station_distance;
	Train_type type;
	int train_number;
	bool forward_direction;

};

enum class Train_type
{
	Regional = 1, High_speed = 2, Super_high_speed = 3;
};