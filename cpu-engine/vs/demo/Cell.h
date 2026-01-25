#pragma once
#include "Entity.h"

class Cell : public Entity
{
protected:
	XMFLOAT2 mIndex;
	//Entity* mEntity;
public:

	virtual void OnInit();
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void OnDelete();
	virtual void OnExit();

	void SetSize(XMFLOAT3 size);
	XMFLOAT3 GetSize();

	void SetIndexs(XMFLOAT2 index);
	XMFLOAT2 GetIndexs();

	//void SetEntity(Entity* entity);
	//Entity* GetEntity();
};

