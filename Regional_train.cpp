//
// Created by Alessandro Visentin on 04/01/21.
//
#include "Regional_train.h"
Regional_train::Regional_train()
{
	status = Train_status::Default_initialized;
}
Regional_train::Regional_train(int speed, const StationLink* stns, int nmb, bool forward)
{
	if (speed <= 0)
		throw Error("Train's max speed in negative or null!");
	if (speed > MAX_SPEED)
		throw Error("Train's max speed in lower!");
	if (stns == nullptr)
		throw Error("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	StationLink* tmp = new StationLink(*stns);
	while (tmp != nullptr)
	{
		stations.push_back(tmp->get_station());
		tmp = tmp->get_next_link();
	}
	if (!forward)
		stations = revert(stations);
	train_number = nmb;
	status = Train_status::Create;
	forward_direction = forward;
	delete tmp;
}
Regional_train::Regional_train(int speed, StationLink stns, int nmb, bool forward)
{
	if (speed <= 0)
		throw Error("Train's max speed in negative or null!");
	if (speed > MAX_SPEED)
		throw Error("Train's max speed in lower!");
	if (stns.get_station() == nullptr)
		throw Error("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	while (stns.get_station() != nullptr)
	{
		stations.push_back(stns.get_station());
		stns = *stns.get_next_link();
	}
	if (!forward)
		stations = revert(stations);
	train_number = nmb;
	status = Train_status::Create;
}
Regional_train::Regional_train(const Regional_train& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
	forward_direction = train.forward_direction;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
}
Regional_train::Regional_train(const Regional_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
	forward_direction = train.forward_direction;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
	delete& train;
}
Regional_train& Regional_train::operator= (Regional_train& train)noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	forward_direction = train.forward_direction;
	status = train.status;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
	return *this;
}
Regional_train& Regional_train::operator= (Regional_train&& train)noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	forward_direction = train.forward_direction;
	status = train.status;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
	delete& train;
	return *this;
}
Regional_train::~Regional_train()
{
	actual_station = 0;
	next_station = 0;
	status = Train_status::Remove;
	actual_speed = 0;
	stations.clear();
}
void Regional_train::move() {
	double covered_distance = 0;
	switch (status)
	{
	case Train_status::Move:
		if (prev_station_distance < STATION_SAFE_DISTANCE)
		{
			actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
			 covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		else if (next_station_distance - actual_speed / TIME_CONVERTER < STATION_SAFE_DISTANCE)
		{
			if (can_move())
			{
				 covered_distance = actual_speed / TIME_CONVERTER;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				status = Train_status::Arriving;
			}
			else {
				actual_speed = 0;
				next_station_distance = 5;
				stations[next_station]->set_on_parking(train_number);
				status = Train_status::Park;
			}
		}
		else
		{
		 covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		break;
	case Train_status::Park:
		if (stations[next_station]->is_train_turn(train_number))
		{
			Train_status::Arriving;
			actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
			 covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		else {
			delay++;
		}
		break;
	case Train_status::Station:
		if (get_remaining_time() <= 0)
			start_from_station();
		break;
	case Train_status::Arriving:
		actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
		 covered_distance = actual_speed / TIME_CONVERTER;
		prev_station_distance += covered_distance;
		next_station_distance -= covered_distance;
		if (next_station_distance <= 0)
			arrive();
		break;
	case Train_status::Create:
		start();
		break;
	case Train_status::End:
	case Train_status::Remove:
	case Train_status::Default_initialized:
		break;
	default:
		break;
	}
}



