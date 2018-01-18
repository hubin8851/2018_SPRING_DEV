#pragma once
#include <regex>
#include "UserDefEnum.h"

extern  std::vector<hbxdef::MyMessage> g_vMessage;
extern bool g_StartFlag;

//�ж�¼���ַ����Ƿ�Ϊ����
bool AllisNum(std::string _str);

//�ж�¼���ַ����Ƿ�Ϊ�ַ��������ֵ���ʽ
bool isStrAppendNum(std::string _str);

//�ú������һ�����ݵĶ�ȡ��֣��������ݴ���
//@stdMes:������ַ���
//@MesInfo:��������Ϣ�ṹ��
int ParseInputMessage(const std::string& strMes,
	hbxdef::MyMessage& MesInfo);

//��ȡָ��ID����Ϣ��������Ӧ���
//@_InNum:�����������
hbxdef::FileResult ParseOutputMessage(const std::string& _InNum);

//����ÿһ�е����벢���ĳһ��
//@_fileName:������ļ���
//@_path:�����·��
hbxdef::FileResult ReadEachLine(const std::string& _fileName = "data.txt", const std::string& _path = "");