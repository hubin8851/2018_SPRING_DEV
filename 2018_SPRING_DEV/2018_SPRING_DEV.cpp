// 2018_SPRING_DEV.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>

#include "UserDefFunc.h"
#include "help_hbx.h"
#include "CTXTReader.h"
#include "CConsoleOutput.h"
#include "EntityManager.h"
#include "Dispatch.h"
#include "Package.h"



std::vector<hbxdef::MyMessage> g_vMessage;
bool g_StartFlag = true;
const char* g_filename = "data.txt";
const char* g_filepath = "";

void SetFileNameProp(int argc, const char **argv);
void RunTest(int argc, const char** argv);	//测试用例
void ClassRunTest(int argc, const char** argv);//消息机制测试用例

int main(int argc, const char** argv)
{
	if (1)
	{
		using namespace std;
		typedef std::map<string, vector<string > > STRING2VECTOR;
		std::map<string, vector<string> > testMap;
		std::vector<string> vec1;
		testMap.insert(STRING2VECTOR::value_type("10001", vec1));
	}

	SetFileNameProp(argc, argv);
	ClassRunTest(argc, argv);

    return 0;
}

void ClassRunTest(int argc, const char** argv)
{
	hbxdef::CTXTReader* g_TxtReader = new hbxdef::CTXTReader(hbxdef::classType::ent_txt, g_filename, g_filepath);
	hbxdef::CConsoleOutput* g_output = new hbxdef::CConsoleOutput(hbxdef::classType::ent_console, g_TxtReader);

	hbxdef::EntityMgr->RegisterEntity(g_TxtReader);
	hbxdef::EntityMgr->RegisterEntity(g_output);

	bool g_bReturn = true;
	while (g_bReturn)
	{
		g_output->Update();
		g_TxtReader->Update();
	}
}


void RunTest(int argc, const char** argv)
{
	std::string consoleInput("");

	//	ReadEachLine("data.txt", "C:\\Users\\hbx\\Desktop\\thoughtworks_2018_spring\\");
	ReadEachLine(g_filename, g_filepath);

	while ( getline(std::cin, consoleInput))
	{
		if (!AllisNum(consoleInput) || consoleInput == "")
		{
			std::cout << "请输入正确的ID数字..." << std::endl;
			continue;
		}
		else if ( "q" == consoleInput ) return;
		ParseOutputMessage(consoleInput);
	}
}


void SetFileNameProp(int argc, const char **argv)
{
	if (checkCmdLineFlag(argc, argv, "help"))
	{
		printhelp();
		getchar();
		return;
	}

	if (checkCmdLineFlag(argc, argv, "FileName"))
	{
		getCmdLineArgumentString(argc, argv, "FileName", (char**)&g_filename);
	}
	if (checkCmdLineFlag(argc, argv, "FilePath"))
	{
		getCmdLineArgumentString(argc, argv, "FilePath", (char**)&g_filepath);
	}

}