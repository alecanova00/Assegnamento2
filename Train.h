#pragma once
#include "Station.h"
#include "TimeTable.h"
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
	const int MAX_SPEED;
	int CRUISE_SPEED;
	int actual_speed;
	int rail_position;
	int delay;
	TimeTable* table;
	Station* actual_station;
	Station* next_statiom;
	int next_station_distance;
	Train_type type;
};

enum class Train_type
{
	Regional = 1, High_speed = 2, Super_high_speed = 3;
};