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
Station Train::get_actual_station() const 
{
	if (status != Train_status::End)
		return *(actual_station->get_station());
	throw exception{ "The train's path is ended" };
}
Station Train::get_next_station()const
{
	if (status != Train_status::End)
		return *(next_station->get_station());
	throw exception{ "The train's path is ended" };
}
int Train::get_remaining_time()const
{
	if (status == Train_status::Station)
		return actual_station->get_station()->train_pause_time(train_number);
	else return -1;
}
Train::Train():CRUISE_SPEED{0},actual_speed{0},actual_station{nullptr},next_station{nullptr},delay{0},
forward_direction{true},next_station_distance{0},prev_station_distance{0},status{Train_status::Create},train_number{0}
{
}
Train::~Train()
{
}
StationLink* Train::revert(const StationLink* stns)
{
	StationLink* tmp=new StationLink(*(stns));
	while (tmp->get_next_link() != nullptr)tmp = tmp->get_next_link();
	StationLink* return_pointer=tmp;
	return_pointer->set_next_link(nullptr);
	while (tmp->get_previous_link() != nullptr)
	{
		return_pointer->set_next_link(return_pointer->get_previous_link());
		return_pointer->set_previous_link(return_pointer->get_next_link());
	}
	delete tmp;
	return return_pointer;
}

vector<Station> Train::get_train_path() const 
{
	StationLink* tmp = actual_station;
	vector<Station> return_vector;
	while (tmp != nullptr)
	{
		return_vector.push_back(*(tmp->get_station()));
		tmp = tmp->get_next_link();
	}
	delete tmp;
	return return_vector;
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
		next_station_distance = next_station->get_station()->get_station_distance() - actual_station->get_station()->get_station_distance();
		prev_station_distance = 0;
		actual_station = nullptr;
		status = Train_status::Move;
	}
	else 
	{
		status = Train_status::End;
		actual_station = nullptr;
		actual_speed = 0;
	}
}