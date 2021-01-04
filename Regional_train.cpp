#include "Regional_train.h"
Regional_train::Regional_train(int speed,TimeTable* tbl)
{
	if (speed > MAX_SPEED)
		throw new exception("Train's max speed in lower!");
	if(tbl==nullptr)
		throw new exception("Timetable is null!");
	CRUISE_SPEED = speed;
	actual_speed = 0;
	table = tbl;
}
Regional_train::Regional_train(const Regional_train& train) noexcept //?
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	table = train.table;
}
Regional_train(const Regional_train&& train) noexcept
{
	CRUISE_SPEED = train.CRUISE_SPEED;
	actual_speed = train.actual_speed;
	table = train.table;
	delete train;
}
Regional_train& operator= (Regional_train& train)noexcept;
Regional_train& operator= (Regional_train&& train)noexcept;
~Regional_train();
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