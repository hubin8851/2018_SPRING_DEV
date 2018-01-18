#pragma once
#include <vector>

namespace hbxdef
{
#ifdef NDEBUG
#define Assert(x) throw(x)
#else
#include <assert.h>
#define Assert(x) assert(x)
#endif

	typedef enum FileResult
	{
		IR_OK,
		IR_NOTOPEN,
		IR_DATAERROR,
		IR_OUTRANGE,
		IR_NODEF
	};

	typedef enum TXTMessageType
	{
		Msg_UnDef,
		Msg_Start,
		Msg_Normal,
		Msg_Fault
	} TXTMes_t;

	typedef enum ConsoleMessageType
	{
		Msg_ReRead,
		Msg_Delete,
		Msg_NoChange
	} ConsoleMes_t;

	typedef struct MyMessage
	{
		char _strId[20];
		int _Loc[3];
		int	offset[3];
		TXTMessageType _Type;

		MyMessage() :_Type(Msg_UnDef) {};
	};

	typedef struct OutputMes
	{
		unsigned int _num;
		MyMessage	_outMes;

		OutputMes(unsigned int _n, const MyMessage& _mes) :_num(_n), _outMes(_mes)
		{};
	};

	struct TxtAttr
	{
		std::string _name;
		std::string _path;
	};

	typedef enum classType
	{
		ent_txt,
		ent_console
	}class_t;


	//不安全，弃用
	// 	typedef union MyUnion	
	// 	{
	// 		int	offset[3];
	// 		MessageType _Type;
	// 
	// 		MyUnion() :_Type(Msg_UnDef) {};
	// 	};
}

extern std::vector<hbxdef::MyMessage> g_vMessage;
extern bool g_StartFlag;