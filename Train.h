//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef Train
#include "Train_type.h"
#include "Train_status.h"
#include "Station.h"
#include "StationLink.h"
#include "vector"
class Train
{
public:
	virtual void move() abstract;
	Train_type get_type()const;
	 int get_max_speed() const;
	int get_cruise_speed()const;
	int get_actual_speed()const;
	int get_train_number()const;
	int get_delay()const;
	Station get_actual_station()const;
	Station get_next_station()const;
	int get_remaining_time()const;
	bool is_arrived()const;
	bool is_ended()const;
	vector<Station> get_train_path();
	Train_status get_status()const;
protected:
	Train();
	~Train();
	void start_from_station();
	const int MAX_SPEED;
	static const int STATION_SPEED = 80;
	static const int STATION_SAFE_DISTANCE = 5;
	static const int TIME_CONVERTER = 60;
	int CRUISE_SPEED;
	int actual_speed;
	int rail_position;
	int delay;
	StationLink* actual_station;
	StationLink* next_station;
	int next_station_distance;
	int prev_station_distance;
	Train_type type;
	Train_status status;
	int train_number;
	bool forward_direction;
	bool can_move() const;
	void arrive();
	StationLink* revert(const StationLink* stns);
	void arrive();
};
#endif // !Train






