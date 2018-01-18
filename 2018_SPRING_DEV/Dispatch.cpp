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
		//��ȡ�����ߺͷ����ߵ�ָ��
		BaseComponent* pSender = EntityMgr->GetEntityFromID(sender);

		BaseComponent* pReceiver = EntityMgr->GetEntityFromID(receiver);
		if (pReceiver == NULL)
		{
			std::cout << "\nWarning! No Receiver with ID of " << receiver << " found";

			return;
		}
		Package tmpPackage(0, sender, receiver, msg, ExtraInfo);
		//���δ���쳣��ֱ���׳�                     
		if (fabs(delay)<0.0002)
		{
			//����Ϣ���������ն�
			Discharge(pReceiver, tmpPackage);
		}
		else	//����Ҫ�ӳ�ʱͳ��ʱ��
		{
			double CurrentTime = Clock->GetCurrentTime();

			tmpPackage.DispatchTime = CurrentTime + delay;
			//�������
			PriorityQ.insert(tmpPackage);
		}
	}


}
