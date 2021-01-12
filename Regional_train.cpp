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
	if (status == Train_status::End || status == Train_status::Remove)
		return;
	if (get_remaining_time() <= 0 && status != Train_status::Create)
	{
		if (status == Train_status::Station)
			start_from_station();
		if (prev_station_distance < STATION_SAFE_DISTANCE)
		{
			actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
			int covered_distance = actual_speed / TIME_CONVERTER;
			prev_station_distance += covered_distance;
			next_station_distance -= covered_distance;
		}
		else if (next_station_distance - actual_speed / TIME_CONVERTER < STATION_SAFE_DISTANCE)
		{
            if (status == Train_status::Arriving)
            {
                actual_speed = (CRUISE_SPEED < STATION_SPEED) ? CRUISE_SPEED : STATION_SPEED;
                int covered_distance = actual_speed / TIME_CONVERTER;
                prev_station_distance += covered_distance;
                next_station_distance -= covered_distance;
                if (next_station_distance <= 0) {
                    arrive();
                    return;
                }

            }

            if (status == Train_status::Move)
            {
                actual_speed = 0;
                next_station_distance = STATION_SAFE_DISTANCE;
                status = Train_status::Park;
                stations[next_station]->set_on_parking(train_number);
            }
            if (status == Train_status::Park && !stations[next_station]->is_train_turn(train_number))
                delay++;
            else
            {
                int direction = (forward_direction) ? 1 : 0;
                stations[next_station]->set_on_rail(train_number, direction);
                int covered_distance = actual_speed / TIME_CONVERTER;
                prev_station_distance += covered_distance;
                next_station_distance -= covered_distance;
                status = Train_status::Arriving;
                if (next_station_distance <= 0) {
                    arrive();
                    return;
                }
            }

		}else{

            int covered_distance = CRUISE_SPEED / TIME_CONVERTER;
            prev_station_distance += covered_distance;
            next_station_distance -= covered_distance;
		}
	}
}



