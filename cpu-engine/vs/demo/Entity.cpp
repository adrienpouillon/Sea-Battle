#include "stdafx.h"
#include "Entity.h"
#include "App.h"

/*
void ::OnInit()
{
	Entity::OnInit();
	mTag = ;

	//mIsCollider = false;
	//mBoxColliding = _NOTHING;
}

void ::OnStart()
{
	Entity::OnStart();


}

void ::OnUpdate()
{
	Entity::OnUpdate();
}

void ::OnCollision(Entity* other)
{
	Entity::OnCollision(other);
}

void ::OnDestroy()
{
	Entity::OnDestroy();
}

void ::OnDelete()
{
	Entity::OnDelete();
}

void ::OnExit()
{
	Entity::OnExit();
}
*/

void Entity::OnInit()
{
	mEntity = mApp->cpu_engine::CreateEntity();
	mTag = NOTHING;

	mIsCollider = false;
	mBoxColliding = _NOTHING;

	mIsDestroy = false;

	SetMaterial(mApp->GetMaterialEntity());
}

void Entity::OnStart()
{

}

void Entity::OnUpdate()
{

}

void Entity::OnCollision(Entity* other)
{

}

void Entity::OnDestroy()
{

}

void Entity::OnDelete()
{
	delete mEntity;
}

void Entity::OnExit()
{
	OnDelete();
}

cpu_entity* Entity::GetEntity()
{
	return mEntity;
}

void Entity::SetApp(App* appp)
{
	mApp = appp;
}

App* Entity::GetApp()
{
	return mApp;
}

void Entity::SetTransform(cpu_transform transform)
{
	mEntity->transform = transform;
}

cpu_transform* Entity::GetTransform()
{
	return &mEntity->transform;
}

void Entity::SetPosition(XMFLOAT3 pos)
{
	mEntity->transform.pos = pos;
}

void Entity::Translate(XMFLOAT3 offset)
{
	XMFLOAT3 pos = GetPosition();
	SetPosition(XMFLOAT3(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z));
}

XMFLOAT3 Entity::GetPosition()
{
	return mEntity->transform.pos;
}

void Entity::SetRotation(cpu_transform rot)
{
	mEntity->transform.SetRotation(rot);
}

void Entity::SetRotation(XMFLOAT4X4 rot)
{
	mEntity->transform.rot = rot;
}

XMFLOAT4X4 Entity::GetRotation()
{
	return mEntity->transform.rot;
}

void Entity::SetScale(XMFLOAT3 scale)
{
	mEntity->transform.sca = scale;
}

void Entity::SetScaling(float scale)
{
	mEntity->transform.SetScaling(scale);
}

XMFLOAT3 Entity::GetScale()
{
	return mEntity->transform.sca;
}

void Entity::SetDirection(XMFLOAT3 dir)
{
	mEntity->transform.dir = dir;
}

void Entity::AddDirection(XMFLOAT3 offset)
{
	XMFLOAT3 dir = GetDirection();
	SetDirection(XMFLOAT3(dir.x + offset.x, dir.y + offset.y, dir.z + offset.z));
}

void Entity::Move(float dis)
{
	mEntity->transform.Move(dis);
}

XMFLOAT3 Entity::GetDirection()
{
	return mEntity->transform.dir;
}

void Entity::SetBoxColliding(BoxCollider boxColliding)
{
	mBoxColliding = boxColliding;
}

BoxCollider Entity::GetBoxColliding()
{
	return mBoxColliding;
}

void Entity::SetIsCollider(bool isCollider)
{
	mIsCollider = isCollider;
}

bool Entity::GetIsCollider()
{
	return mIsCollider;
}

void Entity::SetTag(int tag)
{
	mTag = tag;
}

int Entity::IsTag(int tag)
{
	return mTag == tag;
}

int Entity::IsTypeUp(int tag)
{
	return mTag >= tag;
}

int Entity::IsTypeDown(int tag)
{
	return mTag <= tag;
}

int Entity::GetTag()
{
	return mTag;
}

void Entity::SetIsDestroy(bool isDestroy)
{
	mIsDestroy = isDestroy;
}

bool Entity::IsDestroy(bool isDestroy)
{
	return mIsDestroy == isDestroy;
}

bool Entity::GetIsDestroy()
{
	return mIsDestroy;
}

void Entity::SetMesh(cpu_mesh* mesh)
{
	mEntity->pMesh = mesh;
}

cpu_mesh* Entity::GetMesh()
{
	return mEntity->pMesh;
}

void Entity::SetMaterial(cpu_material* material)
{
	mEntity->pMaterial = material;
}

cpu_material* Entity::GetMaterial()
{
	return mEntity->pMaterial;
}
