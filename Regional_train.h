//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef REGIONAL_TRAIN_H
#define REGIONAL_TRAIN_H
#include "Train.h"
 class Regional_train:public Train
{
public:
	/// <summary>
	/// constructor of a regional train
	/// </summary>
	/// <param name="speed">cruise speed, throw exception if not between 0 and MAX_SPEED</param>
	/// <param name="stns">list of station</param>
	/// <param name="nmb">number of the train</param>
	/// <param name="forward">direction true if forward,false if backward</param>
	Regional_train(int speed,StationLink stns,int nmb,bool forward);
	/// <summary>
	/// constructor of a regional train
	/// </summary>
	/// <param name="speed">cruise speed, throw exception if not between 0 and MAX_SPEED</param>
	/// <param name="stns">list of station</param>
	/// <param name="nmb">number of the train</param>
	/// <param name="forward">direction true if forward,false if backward</param>
	Regional_train(int speed,const StationLink* stns, int nmb, bool forward);
	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	Regional_train(const Regional_train& train) noexcept;
	/// <summary>
	/// move constructor
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	Regional_train(const Regional_train&& train) noexcept;
	/// <summary>
	/// copy assignment
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	Regional_train& operator= (Regional_train& train)noexcept;
	/// <summary>
	/// move assignment
	/// </summary>
	/// <param name="train"></param>
	/// <returns></returns>
	Regional_train& operator= (Regional_train&& train)noexcept;
	~Regional_train();
	static const int MAX_SPEED=160;
	static const Train_type TYPE = Train_type::Regional;
	void move();
};

#endif // !REGIONAL_TRAIN_H