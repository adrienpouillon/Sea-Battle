#pragma once
#include "../cpu-engine/Engine.h"

#define NOTHING 0
#define CELL  NOTHING + 1
#define SEACELL  CELL + 1

class App;


#define MISSILE NOTHING - 1


enum BoxCollider
{
	_NOTHING,
	_CUBE,
	_SPHERE,

	_COUNT
};

class Entity
{
protected:
	//engine
	cpu_entity* mEntity;
	App* mApp;

	//tag
	int mTag;

	//destroy
	bool mIsDestroy;

	//collider
	BoxCollider mBoxColliding;
	bool mIsCollider;
	
public:
	virtual void OnInit();
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnCollision(Entity* other);
	virtual void OnDestroy();
	virtual void OnDelete();
	virtual void OnExit();

	cpu_entity* GetEntity();

	void SetApp(App* appp);
	App* GetApp();

	void SetTransform(cpu_transform transform);
	cpu_transform* GetTransform();

	void SetPosition(XMFLOAT3 pos);
	void Translate(XMFLOAT3 offset);
	XMFLOAT3 GetPosition();

	void SetRotation(cpu_transform rot);
	void SetRotation(XMFLOAT4X4 rot);
	XMFLOAT4X4 GetRotation();

	void SetScale(XMFLOAT3 scale);
	void SetScaling(float scale);
	XMFLOAT3 GetScale();

	void SetDirection(XMFLOAT3 dir);
	void AddDirection(XMFLOAT3 offset);
	void Move(float pos);
	XMFLOAT3 GetDirection();

	void SetBoxColliding(BoxCollider boxColliding);
	BoxCollider GetBoxColliding();

	void SetIsCollider(bool isCollider);
	bool GetIsCollider();

	void SetTag(int tag);
	int IsTag(int tag);
	int IsTypeUp(int tag);
	int IsTypeDown(int tag);
	int GetTag();

	void SetIsDestroy(bool isDestroy);
	bool IsDestroy(bool isDestroy);
	bool GetIsDestroy();

	void SetMesh(cpu_mesh* mesh);
	cpu_mesh* GetMesh();

	void SetMaterial(cpu_material* material);
	cpu_material* GetMaterial();
};

