#pragma once
#include <functional>
#include "BaseComponent.h"
namespace hbxdef
{
	class CTXTReader:
		public BaseComponent
	{
	private:
	protected:
		std::string m_FileName;
		std::string m_FilePath;

		FileResult m_Result;

		std::vector<hbxdef::MyMessage>	m_vMessage;
		bool m_FreshFlag;
		unsigned int  m_iSort;

		void ReadFile();
	public:
		CTXTReader(int _id, std::string _name = "data.txt", std::string _path = "");
		virtual ~CTXTReader() {};

		virtual void Update();

		virtual bool HandleMessage(const Package& msg);

		FileResult GetResult() const { return this->m_Result; };

		const char* GetClassName() const { return "CTXTReader"; };

		std::vector<hbxdef::MyMessage>& GetMessageVec() { return this->m_vMessage; };

	};



}
