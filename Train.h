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
	virtual void move()=0;
	inline int get_cruise_speed() const { return CRUISE_SPEED; }
	inline int get_actual_speed() const { return actual_speed; }
	inline int get_train_number() const { return train_number; }
	inline int get_delay()const { return delay; }
	inline Train_status get_status()const { return status; }
	Station get_actual_station()const;
	Station get_next_station()const;
	int get_remaining_time()const;
	bool is_arrived()const { return status == Train_status::Station; }
	bool is_ended()const { return status == Train_status::End; }
	vector<Station> get_train_path()const;
protected:
	Train();
	~Train();
	void start_from_station();
	static const int STATION_SPEED = 80;
	static const int STATION_SAFE_DISTANCE = 5;
	static const int TIME_CONVERTER = 60;
	int CRUISE_SPEED;
	int actual_speed;
	int delay;
	StationLink* actual_station;
	StationLink* next_station;
	int next_station_distance;
	int prev_station_distance;
	Train_status status;
	int train_number;
	bool forward_direction;
	bool can_move() const;
	void arrive();
	StationLink* revert(const StationLink* stns);
};
#endif // !Train






