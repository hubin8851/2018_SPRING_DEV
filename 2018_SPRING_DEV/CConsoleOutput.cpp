#include "stdafx.h"
#include "UserDefEnum.h"
#include "UserDefFunc.h"
#include "CConsoleOutput.h"
#include "Package.h"
#include "Dispatch.h"

namespace hbxdef
{



	CConsoleOutput::CConsoleOutput(int _id, CTXTReader * _master):
		m_pMaster(_master),
		BaseComponent(_id)
	{

	}

	void CConsoleOutput::Update()
	{
		std::string consoleInput("");
		getline(std::cin, consoleInput);
		if (!AllisNum(consoleInput) || consoleInput == "")
		{
			std::cout << "请输入正确的ID数字..." << std::endl;
			return;
		}
		else if ("q" == consoleInput) exit(0);

		Dispatch->DispatchMes(SEND_MSG_IMMEDIATELY, this->GetID(), ent_txt, Msg_NoChange, (void*)std::stoi(consoleInput));
	}

	bool CConsoleOutput::HandleMessage(const Package & msg)
	{
		hbxdef::OutputMes* _tOMes = (hbxdef::OutputMes*)(msg.DataInfo);


		switch (_tOMes->_outMes._Type)
		{
		case Msg_Start:
			//开始读取数据			
			printf("%s %d %d %d %d \n", _tOMes->_outMes._strId, _tOMes->_num,
				_tOMes->_outMes._Loc[0],
				_tOMes->_outMes._Loc[1],
				_tOMes->_outMes._Loc[2]);
			break;
		case Msg_Normal:
			printf("%s %d %d %d %d \n", _tOMes->_outMes._strId, _tOMes->_num,
				_tOMes->_outMes._Loc[0] + _tOMes->_outMes.offset[0],
				_tOMes->_outMes._Loc[1] + _tOMes->_outMes.offset[1],
				_tOMes->_outMes._Loc[2] + _tOMes->_outMes.offset[2]);
			break;
		case Msg_Fault:
			std::cout << "Error: " << _tOMes->_num << std::endl;
			break;
		default:
			//std::cout << "未定义的消息类型" << std::endl;
			break;
		}
		return true;
	}

	bool CConsoleOutput::HandleMessage(const std::string& _InNum)
	{
		int _tmpSort = std::stoi(_InNum);
		if (_tmpSort > this->GetMaster()->GetMessageVec().size() - 1)
		{
			std::cout << "Cannot find " << _InNum << std::endl;
			return true;
		}

		hbxdef::MyMessage _tmpMes = this->GetMaster()->GetMessageVec()[_tmpSort];
//		char _strbuff[256];

		switch (_tmpMes._Type)
		{
		case Msg_Start:
			//开始读取数据			
			printf( "%s %d %d %d %d \n", _tmpMes._strId, _tmpSort,
				_tmpMes._Loc[0],
				_tmpMes._Loc[1],
				_tmpMes._Loc[2]);
			break;
		case Msg_Normal:
			printf("%s %d %d %d %d \n", _tmpMes._strId, _tmpSort,
				_tmpMes._Loc[0] + _tmpMes.offset[0],
				_tmpMes._Loc[1] + _tmpMes.offset[1],
				_tmpMes._Loc[2] + _tmpMes.offset[2]);
			break;
		case Msg_Fault:
			std::cout << "Error: " << _tmpSort << std::endl;
			break;
		default:
			std::cout << "未定义的消息类型" << std::endl;
			break;
		}
//		Dispatch->DispatchMes(SEND_MSG_IMMEDIATELY, this->GetID(), ent_txt, Msg_Normal, nullptr);

		return true;
	}

}

