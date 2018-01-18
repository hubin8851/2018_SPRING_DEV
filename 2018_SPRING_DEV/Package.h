#pragma once

#include <iostream>
#include <math.h>

namespace hbxdef
{
	const double SmallestDelay = 1.0f;

	class Package
	{
	public:
		int Msg;	//消息枚举

		void*	DataInfo;	//可能是数据也可能是函数指针

		int Sender;	//发送者,枚举值默认转换为int值
		
		int Receiver;	//接受者,枚举值默认转换为int值

		//原则上说消息可以延迟或者直接传给消息队列。如果延迟则需要用到此延迟阈值以便达成延迟目的
		double DispatchTime;	
	
		Package() :DispatchTime(-1),
			Sender(-1),
			Receiver(-1),
			Msg(-1),
			DataInfo(nullptr)
		{};

		Package(double _delayTime, int _s, int _r, int _msg, void* _info = nullptr) :
			DispatchTime(_delayTime),
			Sender(_s),
			Receiver(_r),
			Msg(_msg),
			DataInfo(_info)
		{};

		friend std::ostream& operator << (std::ostream& _os, const Package& _pakg)
		{
			_os << "time: " << _pakg.DispatchTime << "  Sender: " << _pakg.Sender
				<< "   Receiver: " << _pakg.Receiver << "   Msg: " << _pakg.Msg;
		}

	};

	inline bool operator==(const Package& t1, const Package& t2)
	{
		return (fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay) &&
			(t1.Sender == t2.Sender) &&
			(t1.Receiver == t2.Receiver) &&
			(t1.Msg == t2.Msg);
	}

	inline bool operator<(const Package& t1, const Package& t2)
	{
		if (t1 == t2)
		{
			return false;
		}

		else
		{
			return  (t1.DispatchTime < t2.DispatchTime);
		}
	}
}
