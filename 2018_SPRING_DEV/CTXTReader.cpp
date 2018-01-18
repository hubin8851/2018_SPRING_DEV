#include "stdafx.h"
#include "UserDefFunc.h"
#include "CTXTReader.h"
#include "Package.h"
#include "Dispatch.h"


namespace hbxdef
{
	void CTXTReader::ReadFile()
	{
		std::ifstream InFile;
		std::string	_tmpStr(m_FilePath);
		InFile.open(_tmpStr.append(m_FileName));
		if (!InFile.is_open())
		{
			std::cerr << "Error: 打开文件失败！" << std::endl;
			this->m_Result = IR_NOTOPEN;
		}

		bool _Fault = false;
		std::string eachLineOutPut("");

		m_vMessage.clear();
		while (!InFile.eof())
		{
			getline(InFile, _tmpStr);
			hbxdef::MyMessage _tmpMes;
			int _DataNum = ParseInputMessage(_tmpStr, _tmpMes);
			if (true == g_StartFlag)
			{
				g_StartFlag = false;
				_tmpMes._Type = hbxdef::Msg_Start;
				m_vMessage.emplace_back(_tmpMes);
				continue;
			}
			else if (7 == _DataNum && false == _Fault)
			{
				_tmpMes._Type = hbxdef::Msg_Normal;
				m_vMessage.emplace_back(_tmpMes);
				continue;
			}
			else if (-1 == _DataNum)
			{
				std::cerr << "无人机ID标识有误" << std::endl;
				this->m_Result = hbxdef::IR_DATAERROR;
			}
			_Fault = true;
			_tmpMes._Type = hbxdef::Msg_Fault;
			m_vMessage.emplace_back(_tmpMes);

		}
		this->m_Result = hbxdef::IR_OK;
	}

	CTXTReader::CTXTReader(int _id, std::string _name, std::string _path) :m_FileName(_name),
		m_FilePath(_path), m_Result(IR_NODEF),
		m_FreshFlag(false), m_iSort(-1),
		BaseComponent(_id)
	{
		ReadFile();
	}

	void CTXTReader::Update()
	{
		if (m_FreshFlag)
		{
			ReadFile();
			m_FreshFlag = false;
		}
		if (m_iSort > this->GetMessageVec().size() - 1 || m_iSort < 0 )
		{
			std::cout << "Cannot find " << m_iSort << std::endl;
			return;
		}
		hbxdef::OutputMes _OMes(m_iSort, std::move(this->m_vMessage[m_iSort]) );
		Dispatch->DispatchMes(SEND_MSG_IMMEDIATELY, this->GetID(), ent_console, this->m_Result, (void*)&_OMes);
		return;
	}

	bool CTXTReader::HandleMessage(const Package & msg)
	{
		switch (msg.Msg)
		{
		case Msg_ReRead:
			m_FileName = ((TxtAttr*)(msg.DataInfo))->_name;
			m_FilePath = ((TxtAttr*)(msg.DataInfo))->_path;
			this->m_FreshFlag = true;
		case Msg_NoChange: 
			m_iSort = ((unsigned int)(msg.DataInfo));
			break;
		default:
			break;
		}

		return true;
	}

}

