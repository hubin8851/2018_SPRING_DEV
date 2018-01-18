#pragma once

#include <set>
#include "Package.h"
#include "BaseComponent.h"



namespace hbxdef
{
#define Dispatch MessageDispatcher::Instance()

	const double SEND_MSG_IMMEDIATELY = 0.0f;
	const int   NO_ADDITIONAL_INFO = 0;

	class MessageDispatcher
	{
	private:
	protected:

		//延迟发送包的队列
		std::set<Package> PriorityQ;

		void Discharge(BaseComponent* _pRec, const Package& msg);
		
		MessageDispatcher() {};
		MessageDispatcher(const MessageDispatcher&);
		MessageDispatcher& operator=(const MessageDispatcher&);
	public:

		static MessageDispatcher* Instance();



		//
		void DispatchMes(double  delay,
			int    sender,
			int    receiver,
			int    msg,
			void*  ExtraInfo);


		void DispatchDelayedMessages();

	};



}
