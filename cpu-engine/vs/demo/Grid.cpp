#include "stdafx.h"
#include "Grid.h"
#include "App.h"

void Grid::Init(XMFLOAT2 rowsCols, XMFLOAT3 pos, XMFLOAT3 scale, std::vector<std::vector<XMFLOAT2>> indexPosBoat, cpu_material* shaderSeaCellTouch, cpu_material* shaderSeaCellNotTouch)
{
	InitTabCell(rowsCols, scale, shaderSeaCellTouch, shaderSeaCellNotTouch);
	InitTabBoat(indexPosBoat);
	SetPosOfIndex00(pos);
}

void Grid::InitTabCell(XMFLOAT2 rowsCols, XMFLOAT3 scale, cpu_material* shaderSeaCellTouch, cpu_material* shaderSeaCellNotTouch)
{
	int count = 0;

	for (int r = 0; r < rowsCols.x; r++)
	{
		std::vector<SeaCell*> current;
		for (int c = 0; c < rowsCols.y; c++)
		{
			float posi = r * COEF_DIS;
			float posj = c * COEF_DIS;
			SeaCell* cell = mApp->SpawnCell<SeaCell>(XMFLOAT3(posi, posj, 0.f), scale);
			cell->SetMaterialIsTouch(shaderSeaCellTouch);
			cell->SetMaterialIsNotTouch(shaderSeaCellNotTouch);

			current.push_back(cell);
		}

		mAllCells.push_back(current);
	}
}

void Grid::InitTabBoat(std::vector<std::vector<XMFLOAT2>> indexPosBoat)
{
	int lenghtI = (int)indexPosBoat.size();
	for (int i = 0; i < lenghtI; i++)
	{
		std::vector<SeaCell*> allCellBoat = std::vector<SeaCell*>();
		int lenghtJ = (int)indexPosBoat[i].size();
		for (int j = 0; j < lenghtJ; j++)
		{
			XMFLOAT2 indexsAllCells = GetSizeTabCell();
			XMFLOAT2 indexsCell = indexPosBoat[i][j];
			if (indexsCell.x > -1 && indexsCell.x < indexsAllCells.x && indexsCell.y > -1 && indexsCell.y < indexsAllCells.y)
			{
				SeaCell* c = mAllCells[indexsCell.x][indexsCell.y];
				c->SetIsTouch(true);
				allCellBoat.push_back(c);
			}
			else
			{
				// bad index !!!
			}
		}

		Boat* boat = new Boat();
		boat->CreateBoat(allCellBoat);
		mAllBoats.push_back(boat);
	}
}

void Grid::CleanGrid()
{
	CleanCells();
	CleanBoats();
}

void Grid::CleanCells()
{
	/*for (auto it = mAllCells.begin(); it != mAllCells.end(); ++it)
	{
		for (auto it2 = it->begin(); it2 != it->end(); ++it2)
		{
			delete (*it2);
		}
	}*/

	for (auto it = mAllCells.begin(); it != mAllCells.end(); ++it)
	{
		for (auto it2 = it->begin(); it2 != it->end(); ++it2)
		{
			(*it2)->SetIsDestroy(true);
		}
	}

	for (auto& row : mAllCells)
	{
		row.clear();
	}
	mAllCells.clear();
}

void Grid::CleanBoats()
{
	for (auto it = mAllBoats.begin(); it != mAllBoats.end(); ++it)
	{
		delete* it;
	}
	mAllBoats.clear();
}

void Grid::ReplaceCellsToCurrentePos()
{
	XMFLOAT3 posGrid = GetPosOfIndex00();
	XMFLOAT2 indexs = GetSizeTabCell();
	for (int r = 0; r < indexs.x; r++)
	{
		for (int c = 0; c < indexs.y; c++)
		{
			float posi = r * COEF_DIS;
			float posj = c * COEF_DIS;
			mAllCells[r][c]->SetPosition(XMFLOAT3(posGrid.x + posi, posGrid.y + posj, posGrid.z));
		}
	}
}

Cell* Grid::GetNearestCell(XMFLOAT3 pos)
{
	XMFLOAT3 posGrid = GetPosOfIndex00();
	XMFLOAT3 diffPos = XMFLOAT3(pos.x + posGrid.x, pos.y + posGrid.y, pos.z + posGrid.z);
	XMFLOAT2 index = XMFLOAT2(diffPos.x / ((float)mCellSize), diffPos.z / ((float)mCellSize));
	if (index.x < 0 || index.y < 0)
	{
		return nullptr;
	}

	//std::vector<std::vector<Cell*>>* allCells = GetAllCells();
	int lenghtRows = mAllCells.size();
	int lenghtCols = mAllCells[0].size();
	if (index.x > lenghtRows - 1 || index.y > lenghtCols - 1)
	{
		return nullptr;
	}

	return mAllCells[index.x][index.y];
}

void Grid::SetCenterOfGrid(XMFLOAT3 position)
{
	mPosCenter = position;
	ReplaceCellsToCurrentePos();
}

XMFLOAT3 Grid::GetCenterOfGrid() 
{ 
	return mPosCenter;
}

void Grid::SetPosOfIndex00(XMFLOAT3 position)
{
	XMFLOAT2 cellSize = GetSizeTabCell();
	XMFLOAT2 halfRowsCols = XMFLOAT2(cellSize.x * 0.5f, cellSize.y * 0.5f);
	XMFLOAT2 moreLess = XMFLOAT2(halfRowsCols.x * (float)mCellSize, halfRowsCols.y * (float)mCellSize);
	SetCenterOfGrid(XMFLOAT3(position.x + moreLess.x, position.y, position.z + moreLess.y));
}

//Get TopLeft Pos
XMFLOAT3 Grid::GetPosOfIndex00()
{
	XMFLOAT2 cellSize = GetSizeTabCell();
	XMFLOAT2 halfRowsCols = XMFLOAT2(cellSize.x * 0.5f, cellSize.y * 0.5f);
	XMFLOAT2 moreLess = XMFLOAT2(halfRowsCols.x * (float)mCellSize, halfRowsCols.y * (float)mCellSize);
	XMFLOAT3 position = GetCenterOfGrid();
	return XMFLOAT3(position.x - moreLess.x, position.y, position.z - moreLess.y);
}

XMFLOAT3 Grid::GetPosOfCell(Cell* cell)
{
	XMFLOAT2 index = (XMFLOAT2)cell->GetIndexs();
	XMFLOAT3 addPos = XMFLOAT3(index.x * ((float)mCellSize), 0.f, index.y * ((float)mCellSize));
	XMFLOAT3 position = GetPosOfIndex00();
	return XMFLOAT3(position.x + addPos.x, position.y + addPos.y, position.z + addPos.z);
}

XMFLOAT3 Grid::GetPosOfCell(XMFLOAT2 index)
{
	XMFLOAT3 addPos = XMFLOAT3(index.x * ((float)mCellSize), 0.f, index.y * ((float)mCellSize));
	XMFLOAT3 position = GetPosOfIndex00();
	return XMFLOAT3(position.x + addPos.x, position.y + addPos.y, position.z + addPos.z);
}

XMFLOAT2 Grid::GetSizeTabCell()
{ 
	return XMFLOAT2(mAllCells.size(), mAllCells[0].size());
}

void Grid::SetCellSize(int cellSize) 
{ 
	mCellSize = cellSize;
}

int Grid::GetCellSize() 
{ 
	return mCellSize;
}

std::vector<std::vector<SeaCell*>>* Grid::GetAllCells()
{
	return &mAllCells;
}

std::vector<Boat*>* Grid::GetAllBoats()
{
	return &mAllBoats;
}


void Grid::SetApp(App* appp)
{
	mApp = appp;
}

App* Grid::GetApp()
{
	return mApp;
}

Grid::~Grid()
{
	CleanGrid();
}


