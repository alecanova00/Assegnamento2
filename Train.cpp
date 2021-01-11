//
// Created by Alessandro Visentin on 08/01/21.
//
#include "Train.h"

bool Train::can_move()const
{
	if (forward_direction && stations[next_station]->is_rail_free(1))
		return true;
	if (!forward_direction && stations[next_station]->is_rail_free(0))
		return true;
	return false;
}
Station Train::get_actual_station() const 
{
	if (status != Train_status::End)
		return *(stations[actual_station]);
	throw Error{ "The train's path is ended" };
}
Station Train::get_next_station()const
{
	if (status != Train_status::End)
		return *(stations[actual_station]);
	throw Error{ "The train's path is ended" };
}
int Train::get_remaining_time()const
{
	if (status == Train_status::Station)
		return stations[actual_station]->train_pause_time(train_number);
	else return -1;
}
Train::Train():CRUISE_SPEED{0},actual_speed{0},actual_station{0},next_station{0},delay{0},
forward_direction{true},next_station_distance{0},prev_station_distance{0},status{Train_status::Create},train_number{0}
{
}
Train::~Train()
{
}

vector<Station> Train::get_train_path() const 
{
	vector<Station>return_vector;
	for (int i = 0; i < stations.size(); i++)
	{
		return_vector.push_back(*stations[i]);
	}
	return return_vector;
}

void Train::arrive()
{
	actual_station++;
	next_station++;
	if (next_station > stations.size())
	{
		actual_station = 0;
		status = Train_status::End;
		actual_speed = 0;
	}
	else
	{
		status = Train_status::Station;
	}
}
vector<Station*> Train::revert(vector<Station*> stns)
{
	vector<Station*> return_vector(stns.size());
	for (int i = stns.size()-1; i >=0 ; i++)
	{
		return_vector.push_back(stns[i]);
	}
	return return_vector;
}

void Train::start_from_station()
{
	if (status==Train_status::Station)
	{
		next_station_distance = stations[next_station]->get_station_distance() - stations[actual_station]->get_station_distance();
		prev_station_distance = 0;
		status = Train_status::Move;
	}
}

Error::Error(string msg)
{
	message = msg;
}
string Error::get_message()
{
	return message;
}

