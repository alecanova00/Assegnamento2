//
// Created by Alessandro Visentin on 04/01/21.
//
#ifndef Regional_train



#include "Train.h"
 class Regional_train:public Train
{
public:
	Regional_train(int speed,StationLink stns,int nmb,bool forward);
	Regional_train(int speed,const StationLink* stns, int nmb, bool forward);
	Regional_train(const Regional_train& train) noexcept;
	Regional_train(const Regional_train&& train) noexcept;
	Regional_train& operator= (Regional_train& train)noexcept;
	Regional_train& operator= (Regional_train&& train)noexcept;
	~Regional_train();
	static const int MAX_SPEED=160;
	void move()
private:	
	Train_type type=Train_type::Regional;
};

#endif // !Regional_train