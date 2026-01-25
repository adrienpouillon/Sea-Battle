#include "stdafx.h"
#include "SeaCell.h"

void SeaCell::OnInit()
{
	Cell::OnInit();
	
	mTag = SEACELL;

	SetIsTouch(false);
}

void SeaCell::OnStart()
{
	Cell::OnStart();


}

void SeaCell::OnUpdate()
{
	Cell::OnUpdate();

	if (mIsTouch)
	{
		SetMaterial(mMaterialIsTouch);
	}
	else
	{
		SetMaterial(mMaterialIsNotTouch);
	}
}

void SeaCell::OnCollision(Entity* other)
{
	Cell::OnCollision(other);
}

void SeaCell::OnDestroy()
{
	Cell::OnDestroy();
}

void SeaCell::OnDelete()
{
	Cell::OnDelete();
}

void SeaCell::OnExit()
{
	Cell::OnExit();
}

void SeaCell::SetIsTouch(bool isTouch)
{
	mIsTouch = isTouch;
}

bool SeaCell::IsTouch(bool isTouch)
{
	return mIsTouch == isTouch;
}

bool SeaCell::GetIsTouch()
{
	return mIsTouch;
}

void SeaCell::SetMaterialIsTouch(cpu_material* materialIsTouch)
{
	mMaterialIsTouch = materialIsTouch;
}

cpu_material* SeaCell::GetMaterialIsTouch()
{
	return mMaterialIsTouch;
}

void SeaCell::SetMaterialIsNotTouch(cpu_material* materialIsNotTouch)
{
	mMaterialIsNotTouch = materialIsNotTouch;
}

cpu_material* SeaCell::GetMaterialIsNotTouch()
{
	return mMaterialIsNotTouch;
}


