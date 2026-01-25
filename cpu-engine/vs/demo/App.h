#pragma once

#include <vector>
#include "Entity.h"
#include "SeaCell.h"
#include "Grid.h"

class Ship;

class App : public cpu_engine
{
protected:
	Grid* mGrid;

	// Shader
	cpu_material mMaterialSeaCellTouch;
	cpu_material mMaterialSeaCellNotTouch;
	cpu_material mMaterialEntity;
public:
	App();
	virtual ~App();

	

	static App* GetInstance() { return s_pApp; }
	static App& GetInstanceRef() { return *s_pApp; }

	template<typename T>
	T* CreateEntity();
	template<typename T>
	T* SpawnCell(XMFLOAT3 pos, /*cpu_transform rot,*/ XMFLOAT3 scale);
	//void SpawnMissile();
	//void SpawnMissileWithMouse();

	void CreateGrid(XMFLOAT2 rowsCols, std::vector<std::vector<XMFLOAT2>> indexPosBoat);
	std::vector<std::vector<XMFLOAT2>> CreateBoat(XMFLOAT2 rowsCols);

	void OnInit();
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
	void OnRender(int pass) override;

	

	void UpdateEntity();
	void CollisionEntity();
	void DeleteEntity();

	void ClearEntity();

	//static void MissileShader(cpu_ps_io& io);
	static void EntityShader(cpu_ps_io& io);
	static void SeaCellNotTouchShader(cpu_ps_io& io);
	static void SeaCellTouchShader(cpu_ps_io& io);
	static void RockShader(cpu_ps_io& io);

	bool CollisionRectRect(Entity* entityCollider, Entity* otherColliding);
	bool CollisionRectSphere(Entity* entityCollider, Entity* otherColliding);
	bool CollisionSphereRect(Entity* entityCollider, Entity* otherColliding);
	bool CollisionSphereSphere(Entity* entityCollider, Entity* otherColliding);

	cpu_material* GetMaterialEntity();

	int GetRandomNumber(int min, int max);



private:
	inline static App* s_pApp = nullptr;

	cpu_mesh mMeshSphere;
	cpu_mesh mMeshCube;
	cpu_sprite* mSprite;

	std::list<Entity*> mEntities;

	// Resources
	cpu_font mFont;
	//cpu_mesh m_meshShip;
	//cpu_mesh m_meshMissile;
	//cpu_mesh m_meshSphere;
	//cpu_texture m_texture;

	// UI
	//cpu_sprite* m_pSprite;

	// Shader
	//cpu_material m_materialShip;
	//cpu_material m_materialMissile;
	//cpu_material m_materialRock;

	// 3D
	/*Ship* m_pShip;
	std::list<Entity*> mEntities;
	float m_missileSpeed;
	cpu_entity* m_pBall;
	cpu_entity* m_pRock;
	cpu_particle_emitter* m_pEmitter;*/
};

template<typename T>
inline T* App::CreateEntity()
{
	T* e = new T();
	e->SetApp(this);
	e->OnInit();
	mEntities.push_back(e);
	return e;
}

template<typename T>
inline T* App::SpawnCell(XMFLOAT3 pos, /*cpu_transform rot,*/ XMFLOAT3 scale)
{
	T* cell = CreateEntity<T>();
	cpu_entity* c_e = cell->GetEntity();
	cpu_transform* c_t = cell->GetTransform();
	c_e->pMesh = &mMeshCube;
	cell->SetScale(scale);
	cell->SetPosition(pos);
	//e->SetRotation(rot);
	return cell;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*class Ship
{
public:
	Ship();
	~Ship();

	void Create(cpu_mesh* pMesh, cpu_material* pMaterial);
	void Destroy();

	void Update();

	cpu_entity* GetEntity() { return m_pEntity; }
	cpu_fsm<Ship>* GetFSM() { return m_pFSM; }

protected:
	cpu_entity* m_pEntity;
	cpu_fsm<Ship>* m_pFSM;
};*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*struct StateGlobal
{
	void OnEnter(Ship& cur, int from);
	void OnExecute(Ship& cur);
	void OnExit(Ship& cur, int to);
};

struct StateIdle
{
	void OnEnter(Ship& cur, int from);
	void OnExecute(Ship& cur);
	void OnExit(Ship& cur, int to);
};

struct StateBlink
{
	void OnEnter(Ship& cur, int from);
	void OnExecute(Ship& cur);
	void OnExit(Ship& cur, int to);
};*/
