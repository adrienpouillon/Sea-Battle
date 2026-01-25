#include "stdafx.h"
#include "Cell.h"

void Cell::OnInit()
{
	Entity::OnInit();

	mTag = CELL;

	mIsCollider = true;
	mBoxColliding = _CUBE;
}

void Cell::OnStart()
{
	Entity::OnStart();


}

void Cell::OnUpdate()
{
	Entity::OnUpdate();
}

void Cell::OnDestroy()
{
	Entity::OnDestroy();
}

void Cell::OnDelete()
{
	Entity::OnDelete();
}

void Cell::OnExit()
{
	Entity::OnExit();
}

void Cell::SetSize(XMFLOAT3 size)
{
	SetScale(size);
}

XMFLOAT3 Cell::GetSize()
{
	return GetScale();
}

void Cell::SetIndexs(XMFLOAT2 index)
{
	mIndex = index;
}

XMFLOAT2 Cell::GetIndexs()
{
	return mIndex;
}

/*void Cell::SetEntity(Entity* entity)
{
	mEntity = entity;
}

Entity* Cell::GetEntity()
{
	return mEntity;
}*/
