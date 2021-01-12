//
// Created by Alessandro Visentin on 04/01/21.
//
#include "High_speed_train.h"
High_speed_train::High_speed_train(int speed, const StationLink* stns, int nmb, bool forward)
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
	stations = pick(stations);
	if (!forward)
		stations = revert(stations);
	train_number = nmb;
	status = Train_status::Create;
    forward_direction = forward;
	delete tmp;
}
High_speed_train::High_speed_train(int speed,  StationLink stns, int nmb, bool forward)
{
	if (speed <= 0)
		throw Error("Train's max speed in negative or null!");
	if (speed > MAX_SPEED)
		throw Error("Train's max speed in lower!");
	if (stns.get_station() == nullptr)
		throw Error("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	StationLink* tmp = new StationLink(stns);
	while (tmp != nullptr)
	{
		stations.push_back(tmp->get_station());
		tmp = tmp->get_next_link();
	}
	stations = pick(stations);
	if (!forward)
		stations = revert(stations);
	forward_direction = forward;
	train_number = nmb;
	status = Train_status::Create;
}
High_speed_train::High_speed_train(const High_speed_train& train) noexcept 
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
	delay = train.delay;
	forward_direction = train.forward_direction;
	train_number = train.train_number;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
}
High_speed_train::High_speed_train(const High_speed_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
	delay = train.delay;
	forward_direction = train.forward_direction;
	train_number = train.train_number;
	stations.clear();
	for (int i = 0; i < train.stations.size(); i++)
	{
		stations.push_back(train.stations[i]);
	}
	delete &train;
}
High_speed_train& High_speed_train::operator= (High_speed_train& train)noexcept
{
	High_speed_train return_value{ train };
	return *this;
}
High_speed_train& High_speed_train::operator= (High_speed_train&& train)noexcept
{
	High_speed_train return_value{ train };
	delete &train;
	return *this;
}
High_speed_train::~High_speed_train()
{
	actual_station = 0;
	next_station = 0;
	status = Train_status::Remove;
	actual_speed = 0;
	stations.clear();
}
void High_speed_train::move() {
	double covered_distance = 0;
	switch (status)
	{
	case Train_status::Move:
		if (prev_station_distance < STATION_SAFE_DISTANCE) //the train is near the starting station 
		{
			actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
			covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		else if (next_station_distance - actual_speed / TIME_CONVERTER < STATION_SAFE_DISTANCE) //the train is near the arriving station
		{
			if (can_move()) //the station has a free binary
			{
				actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
				covered_distance = actual_speed / TIME_CONVERTER;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				status = Train_status::Arriving;
				stations[next_station]->set_on_rail(train_number, forward_direction);
			}
			else {
				actual_speed = 0;
				next_station_distance = 5;
				stations[next_station]->set_on_parking(train_number);		//the station is occupy
				status = Train_status::Park;
			}
		}
		else //the train goes with his cruise speed
		{
			covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		break;
	case Train_status::Park:
		if (stations[next_station]->is_train_turn(train_number)) //the train can leave the parking area
		{
			actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
			covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
			status = Train_status::Arriving;
			stations[next_station]->set_on_rail(train_number, forward_direction);

		}
		else { //the train stay another minute in the parking area
			delay++;
		}
		break;
	case Train_status::Station:
		if (get_remaining_time() <= 0)
			start_from_station();
		break;
	case Train_status::Arriving:         //the train goes to the station
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

vector<Station*> High_speed_train::pick(vector<Station*>stns)
{
	vector<Station*> return_vector;
	for (int i = 0; i < stns.size(); i++)
	{
		if (stns[i]->get_station_type() == 0)
			return_vector.push_back(stns[i]);
	}
	return return_vector;
}
