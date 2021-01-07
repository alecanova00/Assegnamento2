//
// Created by Alessandro Visentin on 04/01/21.
//
#include "Regional_train.h"
Regional_train::Regional_train(int speed, const StationLink* stns, int nmb, bool forward)
{
	if (speed > MAX_SPEED)
		throw new exception("Train's max speed in lower!");
	if (stns == nullptr)
		throw new exception("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	if (forward)
		actual_station = stns;
	else
	{
		actual_station = revert(stns);
	}
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
	if (get_remaining_time() <= 0)
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
			int covered_distance = actual_speed / 60;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		else if (next_station_distance - actual_speed / 60 < STATION_SAFE_DISTANCE)
		{
			if (next_station_distance < STATION_SAFE_DISTANCE)
			{
				int covered_distance = actual_speed / 60;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				if (next_station_distance <= 0)
					is_arrived();
			}
			else if (can_move())
			{
				int direction = (forward_direction) ? 1 : 0;
				actual_station->get_station()->set_on_rail(train_number, direction);   //calculate delay
				int covered_distance = actual_speed / 60;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				if (next_station_distance <= 0)
					is_arrived();
			}
		}
		else
		{
			delay++;
			actual_speed = 0;
			next_station_distance = 5;
		}
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
	if (actual_station != nullptr)
		return actual_station->get_station()->train_pause_time(train_number);
	else return -1;
}
void Regional_train::start_from_station()
{
	if (actual_station->get_next_link() != nullptr)
	{
		next_station_distance = next_station->get_station()->get_station_distance() - actual_station->get_station()->get_station_distance();
		actual_station->get_station()->free_train(train_number);
		actual_station = nullptr;
	}
	else
	{
		actual_station = nullptr;
		next_station = nullptr;
		//return delay
	}
}
bool Regional_train::is_arrived()
{
	actual_station = next_station;
	prev_station_distance = 0;
	next_station = actual_station->get_next_link();
}

vector<Station> Regional_train::get_train_path()
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
}

StationLink* Regional_train::revert(StationLink* stns)
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