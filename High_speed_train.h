//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef HIGH_SPEED_TRAIN_H
#define HIGH_SPEED_TRAIN_H

#include "Train.h"
 class High_speed_train:public Train
{
public:
	/// <summary>
	///  constructor of a high speed train
	/// </summary>
	/// <param name="speed">cruise speed, throw exception if not between 0 and MAX_SPEED</param>
	/// <param name="stns">list of station</param>
	/// <param name="nmb">number of the train</param>
	/// <param name="forward">direction true if forward,false if backward</param>
	High_speed_train(int speed, StationLink stns, int nmb, bool forward);
	/// <summary>
	///  constructor of a high speed train
	/// </summary>
	/// <param name="speed">cruise speed, throw exception if not between 0 and MAX_SPEED</param>
	/// <param name="stns">list of station</param>
	/// <param name="nmb">number of the train</param>
	/// <param name="forward">direction true if forward,false if backward</param>
	High_speed_train(int speed,const StationLink* stns, int nmb, bool forward);
	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	High_speed_train(const High_speed_train& train) noexcept;
	/// <summary>
	/// move constructor
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	High_speed_train(const High_speed_train&& train) noexcept;
	/// <summary>
	/// copy assignment
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	High_speed_train& operator= (High_speed_train& train)noexcept;
	/// <summary>
	/// move assignment
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	High_speed_train& operator= (High_speed_train&& train)noexcept;
	~High_speed_train();
	static const int MAX_SPEED = 240;
	static const Train_type TYPE = Train_type::High_speed;
	void move() ;
private:
	/// <summary>
	/// pick only primary stations from the list of stations
	/// </summary>
	/// <param name="stns"></param>
	/// <returns></returns>
	vector<Station*> pick(vector<Station*> stns);
};
#endif // !HIGH_SPEED_TRAIN_H
