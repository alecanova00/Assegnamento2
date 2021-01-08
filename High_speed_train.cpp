//
// Created by Alessandro Visentin on 04/01/21.
//
#include "High_speed_train.h"
High_speed_train::High_speed_train(int speed, const StationLink* stns, int nmb, bool forward)
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
	status = Train_status::Create;
}
High_speed_train::High_speed_train(const High_speed_train& train) noexcept //?
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
}
High_speed_train::High_speed_train(const High_speed_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	actual_station = train.actual_station;
	next_station = train.next_station;
	status = train.status;
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
	actual_station = nullptr;
	next_station = nullptr;
	status = Train_status::Remove;
	actual_speed = 0;
}
void High_speed_train::move() {
	if (status == Train_status::End || status == Train_status::Remove)
		return;
	if (get_remaining_time() <= 0)
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
					is_arrived();
			}
			else if (can_move())
			{
				int direction = (forward_direction) ? 1 : 0;
				actual_station->get_station()->set_on_rail(train_number, direction);   //calculate delay
				int covered_distance = actual_speed / TIME_CONVERTER;
				prev_station_distance += covered_distance;
				next_station_distance -= covered_distance;
				status = Train_status::Arriving
					if (next_station_distance <= 0)
						is_arrived();
			}
		}
		else
		{
			delay++;
			actual_speed = 0;
			next_station_distance = STATION_SAFE_DISTANCE;
			status = Train_status::Park;
		}
	}
}



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
