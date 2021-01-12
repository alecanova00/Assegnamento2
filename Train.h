//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef TRAIN_H
#define TRAIN_H
#include "Train_type.h"
#include "Train_status.h"
#include "StationLink.h"
#include "vector"
class Train
{
public:
    inline int get_next_station_distance() const { return next_station_distance; }
	inline int get_cruise_speed() const { return CRUISE_SPEED; }
	inline int get_actual_speed() const { return actual_speed; }
	inline int get_train_number() const { return train_number; }
	inline int get_delay()const { return delay; }
	inline Train_status get_status()const { return status; }
	Station* get_actual_station()const;
	Station* get_next_station()const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>return the remaining time from the start from the station, if the train is moving -1</returns>
	int get_remaining_time()const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>return true if the train is in a station</returns>
	bool is_arrived()const { return status == Train_status::Station; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns>return true if the train has ended is race </returns>
	bool has_ended()const { return status == Train_status::End; }
	/// <summary>
	/// get stations ordered by train's path
	/// </summary>
	/// <returns>the list of the stations</returns>
	vector<Station*> get_train_path()const;
	/// <summary>
	/// dummy method for virtualization
	/// </summary>
	virtual void move();
    inline int get_actual_station_index(){return actual_station;}
    Train();
    ~Train() ;
	void start();
protected:

	
	/// <summary>
	/// notify that the train starts from a station
	/// </summary>
	void start_from_station();
	/// <summary>
	/// max speed of a train that has to stop into a station
	/// </summary>
	static constexpr int STATION_SPEED = 80;
	/// <summary>
	/// the distance from the parking area to next station
	/// </summary>
	static constexpr int STATION_SAFE_DISTANCE = 5;
	/// <summary>
	/// const value to convert from km/h to km/m
	/// </summary>
	static constexpr int TIME_CONVERTER = 60;
	/// <summary>
	/// max speed of the train, choose by user
	/// </summary>
	int CRUISE_SPEED;
	/// <summary>
	/// actual speed, between 0 to cruise speed
	/// </summary>
	int actual_speed;
	/// <summary>
	/// total delay of the train
	/// </summary>
	int delay;
	/// <summary>
	/// pointer to the next station, nullptr if the race is ended
	/// </summary>
	vector<Station*> stations;
	int actual_station;
	int next_station;
	double next_station_distance;
	double prev_station_distance;
	Train_status status;
	int train_number;
	int internal_remaining_time;
	/// <summary>
	/// it's true if the train goes to begin to end, else false
	/// </summary>
	bool forward_direction;
	/// <summary>
	/// check if the train can move in his next station's rail
	/// </summary>
	/// <returns>true if can move into the station, else false</returns>
	bool can_move() const;
	/// <summary>
	/// notify that the train is arrived in his next station
	/// </summary>
	void arrive();
	/// <summary>
	/// inverts stations order (prev/succ)
	/// </summary>
	/// <param name="stns">stations list</param>
	/// <returns>stations list from end to begin</returns>
	vector<Station*> revert(vector<Station*> stns);
	
};
class Error
	{
	public:
		Error(string msg);
		string get_message();
	private:
		string message;
	};



#endif // !TRAIN_H






