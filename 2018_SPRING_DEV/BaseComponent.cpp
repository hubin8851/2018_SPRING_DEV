#include "stdafx.h"
#include "BaseComponent.h"

namespace hbxdef
{
	void BaseComponent::ResetID( int _id)
	{
		Assert((m_MyID >= _id));
		m_MyID = _id;
		m_iNextID = m_MyID + 1;
	}
}


