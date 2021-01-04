//
// Created by Alessandro Visentin on 04/01/21.
//
#include "High_speed_train.h"
High_speed_train::High_speed_train(int speed, TimeTable* tbl, StationLink* stns, int nmb)
{
	if (speed > MAX_SPEED)
		throw new exception("Train's max speed in lower!");
	if (tbl == nullptr)
		throw new exception("Timetable is null!");
	if (tbl == nullptr)
		throw new exception("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	StationLink* tmp= pick(stns);
	if (forward)
		actual_station = tmp;
	else
	{
		actual_station = revert(tmp);
	}
	train_number = nmb;
	next_station = tmp->get_next_link();
}
High_speed_train::High_speed_train(const High_speed_train& train) noexcept //?
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station();
}
High_speed_train::High_speed_train(const High_speed_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station();
	delete train;
}
High_speed_train& High_speed_train::operator= (High_speed_train& train)noexcept
{
	High_speed_train return_value{ train };
	return *this;
}
High_speed_train& High_speed_train::operator= (High_speed_train&& train)noexcept
{
	High_speed_train return_value{ train };
	delete train;
	return *this;
}
High_speed_train::~High_speed_train()
{
}
void High_speed_train::move() {
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
bool High_speed_train::can_move() {
	if (forward_direction && next_station->get_station()->get_standard_rail_forward_status())
		return true;
	if (!forward_direction && next_station->get_station()->get_standard_rail_backward_status())
		return true;
	return false;
}
Train_type High_speed_train::get_type()
{
	return type;
}
int High_speed_train::get_max_speed() {
	return MAX_SPEED;
}
int High_speed_train::get_cruise_speed()
{
	return CRUISE_SPEED;
}
int High_speed_train::get_actual_speed()
{
	return actual_speed;
}
int High_speed_train::get_train_number() {
	return train_number();
}
int High_speed_train::get_delay() {
	return delay;
}
Station High_speed_train::get_actual_station() {
	return actual_station->get_station();
}
Station High_speed_train::get_next_station()
{
	return next_station->get_station();
}
int High_speed_train::get_remaining_time() {
	actual_station->get_station()//metodo per il tempo rimanente
}
void High_speed_train::start_from_station()
{
	if (actual_station->get_next_link() != nullptr)
	{
		Station next = actual_station->get_next_link()->get_station();
		next_station_distance = next_station->get_station()->get_station_distance() - actual_station->get_station()->get_station_distance();
		actual_station = nullptr;
	}
}
bool High_speed_train::is_arrived()
{
	if (next_station_distance == 0)
		actual_station = next_station;
	prev_station_distance = 0;
	next_station = actual_station->get_next_link();	
}

vector<Station> High_speed_train::get_train_path()
{
	StationLink* tmp = actual_station;
	vector<Station> return_vector;
	while (tmp != nullptr)
	{
		return_vector.push_back(tmp);
		tmp = tmp->get_next_link();
	}
	delete tmp;
	return return_vector;
StationLink* High_speed_train::pick(StationLink* stns)
{
	StationLink* tmp = actual_station;
	while (tmp->get_next_link()!=nullptr)
	{
		if (tmp->get_station()->get_station_type() == 1)
		{
			tmp->get_previous_link()->set_next_link() = tmp->set_next_link();
			tmp->get_next_link()->set_previous_link() = tmp->set_previous_link();
			tmp = tmp->get_next_link();
		}
		if (tmp->get_next_link()->get_station()->get_station_type() == 1)
			tmp->set_next_link() = nullptr;
	}
	return tmp;
}
StationLink* High_speed_train::revert(StationLink* stns)
{
	while (stns->get_next_link() != nullptr)stns = stns->get_next_link();
	StationLink* tmp;
	while (stns->get_previous_link() != nullptr)
	{
		tmp->set_next_link() = stns->get_previous_link();
		tmp->set_previous_link() = stns->get_next_link();
	}
	return tmp;
}