#include "stdafx.h"
#include "UserDefFunc.h"



bool AllisNum(std::string _str)
{
	for (int i = 0; i < _str.size(); i++)
	{
		int tmp = (int)_str[i];
		if (tmp >= 48 && tmp <= 57)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool isStrAppendNum(std::string _str)
{
	std::regex tmpreg("\\w+\\d");
	std::smatch tmpsmt;
	std::regex_match(_str, tmpsmt, tmpreg);
	if (!tmpsmt.empty())
	{
		return true;
	}
	return false;
}

//该函数完成一条数据的读取拆分，并将数据传出
//@stdMes:传入的字符串
//@MesInfo:传出的消息结构体
int ParseInputMessage(const std::string& strMes,
	hbxdef::MyMessage& MesInfo)
{
	int tmpi;
	tmpi = 
	sscanf(strMes.c_str(), "%s %d %d %d %d %d %d",
		&MesInfo._strId,
		&MesInfo._Loc[0], &MesInfo._Loc[1], &MesInfo._Loc[2],
		&MesInfo.offset[0], &MesInfo.offset[1], &MesInfo.offset[2]);
	if (isStrAppendNum(MesInfo._strId))
	{
		return tmpi;
	}
	return -1;
	
}


//处理每一行的输入并输出某一行
//@_fileName:传入的文件名
//@_path:传入的路径
hbxdef::FileResult ReadEachLine(const std::string& _fileName, const std::string& _path)
{
	std::ifstream InFile;
	std::string	_tmpStr(_path);
	InFile.open(_tmpStr.append(_fileName));
	if (!InFile.is_open())
	{
		std::cerr << "Error: 打开文件失败！" << std::endl;
		return hbxdef::IR_NOTOPEN;
	}

	bool _Fault = false;
	std::string eachLineOutPut("");

	g_vMessage.clear();
	while (!InFile.eof())
	{
		getline(InFile, _tmpStr);
		hbxdef::MyMessage _tmpMes;
		int _DataNum = ParseInputMessage(_tmpStr, _tmpMes);
		if (true == g_StartFlag)
		{
			g_StartFlag = false;
			_tmpMes._Type = hbxdef::Msg_Start;
			g_vMessage.emplace_back(_tmpMes);
			continue;
		}
		else if (7 == _DataNum && false == _Fault)
		{
			_tmpMes._Type = hbxdef::Msg_Normal;
			g_vMessage.emplace_back(_tmpMes);
			continue;
		}
		else if (-1 == _DataNum)
		{
			std::cerr << "无人机ID标识有误" << std::endl;
			return hbxdef::IR_DATAERROR;
		}
		_Fault = true;
		_tmpMes._Type = hbxdef::Msg_Fault;
		g_vMessage.emplace_back(_tmpMes);

	}
	return hbxdef::IR_OK;
}


//读取指定ID的消息并返回相应输出
//@_InNum:传入的索引号
hbxdef::FileResult ParseOutputMessage(const std::string& _InNum)
{
	int _tmpSort = std::stoi(_InNum);
	if (_tmpSort > g_vMessage.size() - 1)
	{
		std::cout << "Cannot find " << _InNum << std::endl;
		return hbxdef::IR_OUTRANGE;
	}

	auto  _tmp = g_vMessage[_tmpSort];	//从0索引但第一条是起始数据

	switch (_tmp._Type)
	{
	case hbxdef::Msg_Start:
		printf("%s %d %d %d %d \n", _tmp._strId, _tmpSort,
			_tmp._Loc[0],
			_tmp._Loc[1],
			_tmp._Loc[2]);
		break;
	case hbxdef::Msg_Normal:
		printf("%s %d %d %d %d \n", _tmp._strId, _tmpSort,
			_tmp._Loc[0] + _tmp.offset[0],
			_tmp._Loc[1] + _tmp.offset[1],
			_tmp._Loc[2] + _tmp.offset[2]);
		break;
	case hbxdef::Msg_Fault:
		std::cout << "Error: " << _InNum << std::endl;
		return hbxdef::IR_DATAERROR;
	case hbxdef::Msg_UnDef: default:
		std::cout << "未定义的消息类型" << std::endl;
		break;
	}


	return hbxdef::IR_OK;
}