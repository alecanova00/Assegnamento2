//
// Created by Alessandro Visentin on 04/01/21.
//
#include "Regional_train.h"
Regional_train::Regional_train(int speed, StationLink* stns, int nmb)
{
	if (speed > MAX_SPEED)
		throw new exception("Train's max speed in lower!");
	if (stns == nullptr)
		throw new exception("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	actual_station = stns; //salvare solo liste da fare
	train_number = nmb;
	next_station = stns->get_next_link();
}
Regional_train::Regional_train(const Regional_train& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station();
}
Regional_train::Regional_train(const Regional_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station();
	delete train;
}
Regional_train& Regional_train::operator= (Regional_train& train)noexcept
{
	Regional_train return_value{ train };
	return *this;
}
Regional_train& Regional_train::operator= (Regional_train&& train)noexcept
{
	Regional_train return_value{ train };
	delete train;
	return *this;
}
Regional_train::~Regional_train()
{
	delete actual_station;
	delete next_station;
}
void Regional_train::move() {
	if (get_remaining_time() > 0)
		return;
	if (get_remaining_time() == 0)
	{
		if (actual_station != nullptr)
			start_from_station();
		if (prev_station_distance < STATION_SAFE_DISTANCE)
		{
			if (STATION_SPEED < CRUISE_SPEED)
			{
				actual_speed = STATION_SPEED
			}
			else
				actual_speed = CRUISE_SPEED;
		}
		else if (next_station_distance < STATION_SAFE_DISTANCE)
			if (can_move())
			{
				if (prev_station_distance < STATION_SAFE_DISTANCE)
				{
					if (STATION_SPEED < CRUISE_SPEED)
					{
						actual_speed = STATION_SPEED
					}
					else
						actual_speed = CRUISE_SPEED;
				}
			}
			else
			{
				delay++;
				actual_speed = 0;
			}
		else
		{
			actual_speed = CRUISE_SPEED;
		}
		int covered_distance = actual_speed / 60;
		prev_station_distance += covered_distance;
		next_station_distance -= covered_distance;
	}


	
	
}
bool Regional_train::can_move() {
	if (forward_direction && next_station->get_station()->get_standard_rail_forward_status())
		return true;
	if (!forward_direction && next_station->get_station()->get_standard_rail_backward_status())
		return true;
	return false;
}
Train_type Regional_train::get_type()
{
	return type;
}
int Regional_train::get_max_speed() {
	return MAX_SPEED;
}
int Regional_train::get_cruise_speed()
{
	return CRUISE_SPEED;
}
int Regional_train::get_actual_speed()
{
	return actual_speed;
}
int Regional_train::get_train_number() {
	return train_number();
}
int Regional_train::get_delay() {
	return delay;
}
Station Regional_train::get_actual_station() {
	return actual_station->get_station();
}
Station Regional_train::get_next_station()
{
	return next_station->get_station();
}
int Regional_train::get_remaining_time() {
	actual_station->get_station()
}
void Regional_train::start_from_station()
{
	if (actual_station->get_next_link() != nullptr)
	{
		next_station_distance = next_station->get_station()->get_station_distance() - actual_station->get_station()->get_station_distance();
		actual_station = nullptr;
	}
}
bool Regional_train::is_arrived()
{
	if (next_station_distance <= 0)
		actual_station = next_station;
	prev_station_distance = 0;
	next_station = actual_station->get_next_link();
	actual_station->get_station()->//numero treno, 0 se forward, 1 se backward
}