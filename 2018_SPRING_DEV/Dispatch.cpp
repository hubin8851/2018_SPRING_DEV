#include "stdafx.h"
#include <iostream>
#include "Dispatch.h"
#include "BaseComponent.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
#include "Package.h"

namespace hbxdef
{


	void MessageDispatcher::Discharge(BaseComponent * _pRec, const Package & msg)
	{
		if (!_pRec->HandleMessage(msg))
		{
			//telegram could not be handled
			std::cout << "Message not handled";
		}
	}

	MessageDispatcher * MessageDispatcher::Instance()
	{
		static MessageDispatcher instance;
		return &instance;
	}

	void MessageDispatcher::DispatchMes(double delay, int sender, int receiver, int msg, void * ExtraInfo)
	{
		//获取接受者和发送者的指针
		BaseComponent* pSender = EntityMgr->GetEntityFromID(sender);

		BaseComponent* pReceiver = EntityMgr->GetEntityFromID(receiver);
		if (pReceiver == NULL)
		{
			std::cout << "\nWarning! No Receiver with ID of " << receiver << " found";

			return;
		}
		Package tmpPackage(0, sender, receiver, msg, ExtraInfo);
		//如果未有异常，直接抛出                     
		if (fabs(delay)<0.0002)
		{
			//将消息包发给接收端
			Discharge(pReceiver, tmpPackage);
		}
		else	//当需要延迟时统计时间
		{
			double CurrentTime = Clock->GetCurrentTime();

			tmpPackage.DispatchTime = CurrentTime + delay;
			//放入队列
			PriorityQ.insert(tmpPackage);
		}
	}


}
