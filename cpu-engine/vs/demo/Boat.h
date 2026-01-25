#pragma once
#include "SeaCell.h"
#include <vector>

/*struct Node
{
public:
	Cell* mCurrenteCell;
	Node* mNext;
	Node* mPrev;
public:
	Node();
	Node(Cell* cell, Node* next, Node* prev) { mCurrenteCell = cell; mNext = next; mPrev = prev; }
	void SetCurrenteCell(Cell* currenteCell) { mCurrenteCell = currenteCell; }
	Cell* GetCurrenteCell() { return mCurrenteCell; }
	void SetNext(Node* next) { mNext = next; }
	Node* GetNext() { return mNext; }
	void SetPrev(Node* prev) { mPrev = prev; }
	Node* GetPrev() { return mPrev; }

	Node* GetBegin(Node* node)
	{
		Node* it = node;
		while (it != nullptr)
		{
			it = it->GetPrev();
		}
		return it;
	}

	Node* GetEnd(Node* node)
	{
		Node* it = node;
		while (it != nullptr)
		{
			it = it->GetNext();
		}
		return it;
	}
};*/

class Boat
{
protected:
	std::list<SeaCell*> mAllCell;
public:
	
	Boat();
	Boat(std::vector<SeaCell*> allCell);
	Boat(std::list<SeaCell*> allCell);

	void CreateBoat(std::vector<SeaCell*> allCell);
	void SetBoat(std::list<SeaCell*> allCell);
	std::list<SeaCell*> GetBoat();

	bool IsInAllCell(SeaCell* cell);
};

