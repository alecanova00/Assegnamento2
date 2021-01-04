
class Train
{
	void move();
	bool can_move();
	Train_type get_type();
	int get_max_speed();
	int get_cruise_speed();
	int get_actual_speed();
	int get_train_number();
	int get_delay();
	Station get_actual_station();
	Station get_next_station();
	int get_remaining_time();
private:
	const int MAX_SPEED;
	const int CRUISE_SPEED;
	int actual_speed;
	int rail_position;
	int delay;
	Timetable table;
	Station actual_station;
	Station next_statiom;
	int next_station_distance;
};

public enum Train_type
{
	{Regional = 1, High_speed = 2, Super_high_speed = 3};
};