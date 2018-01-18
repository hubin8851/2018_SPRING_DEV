#pragma once
#include "BaseComponent.h"
#include "CTXTReader.h"


namespace hbxdef
{

	class CConsoleOutput : public BaseComponent
	{
	private:
	protected:
		CTXTReader * m_pMaster;


	public:
		CConsoleOutput(int _id, CTXTReader* _master);
		virtual ~CConsoleOutput() {};

		void ResetMaster(CTXTReader* _master) { this->m_pMaster = _master; };

		CTXTReader* GetMaster() const {return this->m_pMaster;};

		virtual void Update();

		virtual bool HandleMessage(const Package& msg);
		virtual bool HandleMessage(const std::string& _InNum);

		const char* GetClassName() const { return "CConsoleOutput"; };


	};




}

