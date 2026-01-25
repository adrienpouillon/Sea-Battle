#include "stdafx.h"
#include "Boat.h"

Boat::Boat()
{
	CreateBoat(std::vector<SeaCell*>());
}

Boat::Boat(std::vector<SeaCell*> allCell)
{
	CreateBoat(allCell);
}

Boat::Boat(std::list<SeaCell*> allCell)
{
	SetBoat(allCell);
}

void Boat::CreateBoat(std::vector<SeaCell*> allCell)
{
	int lenght = (int)allCell.size();
	for (int i = 0; i < lenght; i++)
	{
		mAllCell.push_back(allCell[i]);
	}
}

void Boat::SetBoat(std::list<SeaCell*> allCell)
{
	mAllCell = allCell;
}

std::list<SeaCell*> Boat::GetBoat()
{
	return mAllCell;
}

bool Boat::IsInAllCell(SeaCell* cell)
{
	for (auto it = mAllCell.begin(); it != mAllCell.end();++it)
	{
		SeaCell* currenteCell = *it;
		if (currenteCell == cell)
		{
			return true;
		}
	}
	return false;
}
