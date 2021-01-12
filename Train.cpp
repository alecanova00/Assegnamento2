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
Station* Train::get_actual_station() const 
{
	if (status != Train_status::End && status!=Train_status::Remove)
		return stations[actual_station];
	return nullptr;
}
Station* Train::get_next_station()const
{
	if (status != Train_status::End && status != Train_status::Remove)
		return stations[next_station];
	return nullptr;
}

int Train::get_remaining_time()const
{
	if (status == Train_status::Station)
		return stations[actual_station]->train_pause_time(train_number);
	else return -1;
}
Train::Train():CRUISE_SPEED{0},actual_speed{0},actual_station{0},next_station{0},delay{0},
forward_direction{true},next_station_distance{0},prev_station_distance{0},status{Train_status::Default_initialized},train_number{0}
{
}
Train::~Train()
{
}

vector<Station*> Train::get_train_path() const
{
    return stations;
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
	vector<Station*> return_vector;
	for(int i = stns.size()-1; i >=0 ; i--)
	{
		return_vector.push_back(stns[i]);
	}
	return return_vector;	
}

void Train::start_from_station()
{
	if (status==Train_status::Station && forward_direction)
	{
		next_station_distance = stations[next_station]->get_station_distance() - stations[actual_station]->get_station_distance();
		prev_station_distance = 0;
		status = Train_status::Move;
	}
	if (status == Train_status::Station && !forward_direction)
	{
		next_station_distance = stations[actual_station]->get_station_distance() - stations[next_station]->get_station_distance();   //if the train goes backward the distance to the next station is negative
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

void Train::move(){

}

void Train::start()
{
	if (status == Train_status::Create)
	{
		status = Train_status::Station;
		actual_station = 0;
		next_station = 1;
	}
}
