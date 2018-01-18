#pragma once
#include <regex>
#include "UserDefEnum.h"

extern  std::vector<hbxdef::MyMessage> g_vMessage;
extern bool g_StartFlag;

//判断录入字符串是否为数字
bool AllisNum(std::string _str);

//判断录入字符串是否为字符串加数字的形式
bool isStrAppendNum(std::string _str);

//该函数完成一条数据的读取拆分，并将数据传出
//@stdMes:传入的字符串
//@MesInfo:传出的消息结构体
int ParseInputMessage(const std::string& strMes,
	hbxdef::MyMessage& MesInfo);

//读取指定ID的消息并返回相应输出
//@_InNum:传入的索引号
hbxdef::FileResult ParseOutputMessage(const std::string& _InNum);

//处理每一行的输入并输出某一行
//@_fileName:传入的文件名
//@_path:传入的路径
hbxdef::FileResult ReadEachLine(const std::string& _fileName = "data.txt", const std::string& _path = "");