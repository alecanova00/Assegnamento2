//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef HIGH_SPEED_TRAIN_SUPER_H
#define HIGH_SPEED_TRAIN_SUPER_H

#include "Train.h"
class High_speed_train_super:public Train
{
public:
	High_speed_train_super();
	High_speed_train_super(int speed, StationLink stns, int nmb, bool forward);
	High_speed_train_super(int speed, const StationLink* stns, int nmb, bool forward);
	High_speed_train_super(const High_speed_train_super& train) noexcept;
	High_speed_train_super(const High_speed_train_super&& train) noexcept;
	High_speed_train_super& operator= (High_speed_train_super& train)noexcept;
	High_speed_train_super& operator= (High_speed_train_super&& train)noexcept;
	~High_speed_train_super();
	void move();
	static const int MAX_SPEED = 300;
	static const Train_type TYPE = Train_type::Super_high_speed;
private:
	vector<Station*> pick(vector<Station*> stns);
};

#endif // !HIGH_SPEED_TRAIN_SUPER_H

