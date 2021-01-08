//
// Created by Alessandro Visentin on 08/01/21.
//
#include "Train.h"

bool Train::can_move()const
{
	if (forward_direction && next_station->get_station()->is_rail_free(1))
		return true;
	if (!forward_direction && next_station->get_station()->is_rail_free(0))
		return true;
	return false;
}
Train_type Train::get_type()const
{
	return type;
}
int Train::get_max_speed()const
{
	return MAX_SPEED;
}
int Train::get_cruise_speed()const
{
	return CRUISE_SPEED;
}
int Train::get_actual_speed()const
{
	return actual_speed;
}
int Train::get_train_number()const
{
	return train_number();
}
int Train::get_delay() const 
{
	return delay;
}
Station Train::get_actual_station() const 
{
	if (status != Train_status::End)
		return actual_station->get_station();
	throw exception{ "The train's path is ended" };
}
Station Train::get_next_station()const
{
	if (status != Train_status::End)
		return next_station->get_station();
	throw exception{ "The train's path is ended" };
}
int Train::get_remaining_time()const
{
	if (status == Train_status::Station)
		return actual_station->get_station()->train_pause_time(train_number);
	else return -1;
}
StationLink* Train::revert(const StationLink* stns)
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

vector<Station> Train::get_train_path()
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
bool Train::is_arrived()const
{
	return status == Train_status::Station;
}
bool Train::is_ended()const
{
	return status == Train_status::End;
}
void Train::arrive()
{
	actual_station = next_station;
	prev_station_distance = 0;
	next_station = actual_station->get_next_link();
	if (next_station == nullptr)
	{
		actual_station = nullptr;
		status = Train_status::End;
		actual_speed = 0;
	}
	else
	{
		status = Train_status::Station;
	}
}
void Train::start_from_station()
{
	if (actual_station->get_next_link() != nullptr)
	{
		Station next = actual_station->get_next_link()->get_station();
		next_station_distance = next_station->get_station()->get_station_distance() - actual_station->get_station()->get_station_distance();
		actual_station = nullptr;
	}
}