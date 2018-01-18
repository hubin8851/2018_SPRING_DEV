#include "stdafx.h"
#include "EntityManager.h"
#include "BaseComponent.h"

namespace hbxdef
{


	//Instance
	EntityManager* EntityManager::Instance()
	{
		static EntityManager instance;

		return &instance;
	}

	//------------------------- GetEntityFromID -----------------------------------
	BaseComponent* EntityManager::GetEntityFromID(int id)const
	{

		EntityMap::const_iterator ent = m_EntityMap.find(id);

		assert((ent != m_EntityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");

		return ent->second;
	}


	void EntityManager::RemoveEntity(BaseComponent* pEntity)
	{
		m_EntityMap.erase(m_EntityMap.find(pEntity->GetID()));
	}


	void EntityManager::RegisterEntity(BaseComponent* NewEntity)
	{
		m_EntityMap.insert(std::make_pair(NewEntity->GetID(), NewEntity));
	}
}


