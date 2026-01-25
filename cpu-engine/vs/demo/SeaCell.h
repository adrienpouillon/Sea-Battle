#pragma once
#include "Cell.h"

class SeaCell : public Cell
{
protected:
	bool mIsTouch;
	cpu_material* mMaterialIsNotTouch;
	cpu_material* mMaterialIsTouch;
public:

	virtual void OnInit();
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnCollision(Entity* other);
	virtual void OnDestroy();
	virtual void OnDelete();
	virtual void OnExit();

	void SetIsTouch(bool isTouch);
	bool IsTouch(bool isTouch);
	bool GetIsTouch();

	void SetMaterialIsTouch(cpu_material* materialIsTouch);
	cpu_material* GetMaterialIsTouch();

	void SetMaterialIsNotTouch(cpu_material* materialIsNotTouch);
	cpu_material* GetMaterialIsNotTouch();

};

