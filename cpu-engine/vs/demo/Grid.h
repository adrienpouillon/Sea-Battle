#pragma once
#include "Boat.h"

#define COEF_DIS 0.12f

class Grid
{
protected:
	App* mApp;
	std::vector<std::vector<SeaCell*>> mAllCells;
	std::vector<Boat*> mAllBoats;

	XMFLOAT3 mPosCenter;

	int mCellSize;
public:

	void Init(XMFLOAT2 rowsCols, XMFLOAT3 pos, XMFLOAT3 scale, std::vector<std::vector<XMFLOAT2>> indexPosBoat, cpu_material* shaderSeaCellTouch, cpu_material* shaderSeaCellNotTouch);

	void CleanGrid();
	void CleanCells();
	void CleanBoats();

	void ReplaceCellsToCurrentePos();

	Cell* GetNearestCell(XMFLOAT3 pos);

	void SetCenterOfGrid(XMFLOAT3 position);
	XMFLOAT3 GetCenterOfGrid();

	void SetPosOfIndex00(XMFLOAT3 position);
	XMFLOAT3 GetPosOfIndex00();

	XMFLOAT3 GetPosOfCell(Cell* cell);
	XMFLOAT3 GetPosOfCell(XMFLOAT2 index);

	XMFLOAT2 GetSizeTabCell();

	void SetCellSize(int cellSize);
	int GetCellSize();
	
	std::vector<std::vector<SeaCell*>>* GetAllCells();
	std::vector<Boat*>* GetAllBoats();

	void SetApp(App* appp);
	App* GetApp();

	~Grid();

protected:
	void InitTabCell(XMFLOAT2 rowsCols, XMFLOAT3 scale, cpu_material* shaderSeaCellTouch, cpu_material* shaderSeaCellNotTouch);
	void InitTabBoat(std::vector<std::vector<XMFLOAT2>> indexPosBoat);
	
};

