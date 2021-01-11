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
		actual_station = new StationLink(*(stns));
	else
	{
		actual_station = revert(stns);
	}
	train_number = nmb;
	next_station = actual_station->get_next_link();
	status = Train_status::Create;
}
Regional_train::Regional_train(int speed, StationLink stns, int nmb, bool forward)
{
	if (speed > MAX_SPEED)
		throw new exception("Train's max speed in lower!");
	if (stns.get_station() == nullptr)
		throw new exception("The stations' list is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	if (forward)
		actual_station = &stns;
	else
	{
		actual_station = revert(&stns);
	}
	train_number = nmb;
	next_station = actual_station->get_next_link();
	status = Train_status::Create;
}
Regional_train::Regional_train(const Regional_train& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
}
Regional_train::Regional_train(const Regional_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
	delete &train;
}
Regional_train& Regional_train::operator= (Regional_train& train)noexcept
{
	Regional_train return_value{ train };
	return return_value;
}
Regional_train& Regional_train::operator= (Regional_train&& train)noexcept
{
	Regional_train return_value{ train };
	delete &train;
	return return_value;
}
Regional_train::~Regional_train()
{
	actual_station = nullptr;
	next_station = nullptr;
	status = Train_status::Remove;
	actual_speed = 0;
}
void Regional_train::move() {
	if (status == Train_status::End || status == Train_status::Remove)
		return;
	if (get_remaining_time()<=0)
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
				int covered_distance = actual_speed / TIME_CONVERTER;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				if (next_station_distance <= 0)
					arrive();
			}
			else if (can_move())
			{
				int direction = (forward_direction) ? 1 : 0;
				next_station->get_station()->set_on_rail(train_number, direction);
				int covered_distance = actual_speed / TIME_CONVERTER;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				status = Train_status::Arriving;
				if (next_station_distance <= 0)
					arrive();
			}
		}
		else
		{
			if (status == Train_status::Move)
			{
				actual_speed = 0;
				next_station_distance = STATION_SAFE_DISTANCE;
				status = Train_status::Park;
				next_station->get_station()->set_on_parking(train_number);
			}
			if (!next_station->get_station()->is_train_turn(train_number))
				delay++;
			else
			{
				int direction = (forward_direction) ? 1 : 0;
					next_station->get_station()->set_on_rail(train_number, direction);
					int covered_distance = actual_speed / TIME_CONVERTER;
					prev_station_distance += covered_distance;
					next_station_distance -= covered_distance;
					status = Train_status::Arriving;
					if (next_station_distance <= 0)
						arrive();
			}

		}
	}
}



