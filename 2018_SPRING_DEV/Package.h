#pragma once

#include <iostream>
#include <math.h>

namespace hbxdef
{
	const double SmallestDelay = 1.0f;

	class Package
	{
	public:
		int Msg;	//��Ϣö��

		void*	DataInfo;	//����������Ҳ�����Ǻ���ָ��

		int Sender;	//������,ö��ֵĬ��ת��Ϊintֵ
		
		int Receiver;	//������,ö��ֵĬ��ת��Ϊintֵ

		//ԭ����˵��Ϣ�����ӳٻ���ֱ�Ӵ�����Ϣ���С�����ӳ�����Ҫ�õ����ӳ���ֵ�Ա����ӳ�Ŀ��
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
