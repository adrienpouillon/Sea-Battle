#include "stdafx.h"
#include "Entity.h"

App::App()
{
	s_pApp = this;
	//m_pShip = nullptr;
	mGrid = nullptr;
	srand(time(0));
}

App::~App()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void App::SpawnMissile()
{
	cpu_entity* pMissile = CreateEntity();
	pMissile->pMesh = &m_meshMissile;
	pMissile->transform.SetScaling(0.2f);
	pMissile->transform.pos = m_pShip->GetEntity()->transform.pos;
	pMissile->transform.SetRotation(m_pShip->GetEntity()->transform);
	pMissile->transform.Move(1.5f);
	m_missiles.push_back(pMissile);
}*/

/*void App::SpawnMissileWithMouse()
{
	XMFLOAT2 pt;
	GetCursor(pt);
	cpu_ray ray = GetCameraRay(pt);
	cpu_entity* pMissile = CreateEntity();
	pMissile->pMesh = &m_meshMissile;
	pMissile->transform.SetScaling(0.2f);
	pMissile->transform.pos = ray.pos;
	pMissile->transform.LookTo(ray.dir);
	pMissile->transform.Move(1.5f);
	pMissile->pMaterial = &m_materialMissile;
	m_missiles.push_back(pMissile);
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void App::CreateGrid(XMFLOAT2 rowsCols, std::vector<std::vector<XMFLOAT2>> indexPosBoat)
{
	/*XMFLOAT3 pos = XMFLOAT3(-0.5f, -0.55f, 1.5f);
	int nb1 = 10;
	int nb2 = 10;
	for (int i = 0; i < nb1; i++)
	{
		for (int j = 0; j < nb2; j++)
		{
			float posi = i * 0.12f;
			float posj = j * 0.12f;
			SpawnCell(XMFLOAT3(pos.x + posi, pos.y + posj, pos.z), XMFLOAT3(0.01f, 0.01f, 0.005f));
		}
	}*/
	if (mGrid != nullptr)
	{
		delete mGrid;
	}
	Grid* g = new Grid();
	g->SetApp(this);
	XMFLOAT3 pos = XMFLOAT3(-0.5, -0.55, 1.5f);
	XMFLOAT3 scale = XMFLOAT3(0.01f, 0.01f, 0.005f);
	g->Init(rowsCols, pos, scale, indexPosBoat, &mMaterialSeaCellTouch, &mMaterialSeaCellNotTouch);
	mGrid = g;
}

std::vector<std::vector<XMFLOAT2>> App::CreateBoat(XMFLOAT2 rowsCols)
{
	int minIndexR = 0;
	int maxIndexR = rowsCols.x;
	int minIndexC = 0;
	int maxIndexC = rowsCols.y;

	int minTall = 1;
	int maxTall = 4;

	int minNb = 0;
	int maxNb = 2;

	int nb = 0;
	int add = GetRandomNumber(2, 5);
	while (add > 0)
	{
		nb += add;
		add = GetRandomNumber(minNb, maxNb);
	}

	std::vector<std::vector<XMFLOAT2>> indexPosBoat = std::vector<std::vector<XMFLOAT2>>();

	for (int i = 0; i < nb; i++)
	{
		int tallBoat = GetRandomNumber(minTall, maxTall);
		std::vector<XMFLOAT2> indexPos;
		for (int j = 0; j < tallBoat; j++)
		{
			XMFLOAT2 indexCell;

			if (j == 0)
			{
				indexCell = XMFLOAT2(GetRandomNumber(minIndexR, maxIndexR), GetRandomNumber(minIndexC, maxIndexC));
			}
			else if (j == 1)
			{
				indexCell = indexPos[j - 1];
				indexCell.x += GetRandomNumber(-1, 1);
				indexCell.y += GetRandomNumber(-1, 1);
			}
			else
			{
				XMFLOAT2 indexFormer = indexPos[j - 1];
				XMFLOAT2 indexFormerFormer = indexPos[j - 2];
				XMFLOAT2 indexDir = XMFLOAT2(indexFormer.x - indexFormerFormer.x, indexFormer.y - indexFormerFormer.y);
				indexCell = XMFLOAT2(indexFormer.x + indexDir.x, indexFormer.y + indexDir.y);
			}
			
			bool isValide = true;

			if (isValide)
			{
				if (indexCell.x < minIndexR || indexCell.x > maxIndexR - 1 || indexCell.y < minIndexC || indexCell.y > maxIndexC - 1)
				{
					isValide = false;
				}
			}
			
			if (isValide)
			{
				for (int r = 0; r < indexPosBoat.size(); r++)
				{
					for (int c = 0; c < indexPosBoat[r].size(); c++)
					{
						XMFLOAT2 indexFormerCell = indexPosBoat[r][c];
						if (indexFormerCell.x == indexCell.x && indexFormerCell.y == indexCell.y)
						{
							isValide = false;
						}
					}
				}
			}

			if (isValide)
			{
				indexPos.push_back(indexCell);
			}
			else
			{
				j = tallBoat;
			}
		}

		if (indexPos.size() > 0)
		{
			indexPosBoat.push_back(indexPos);
		}
	}
	return indexPosBoat;
}

void App::OnInit()
{
	//Resources
	mMeshSphere.CreateSphere(0.5f);
	mMeshCube.CreateCube(5, ToColor(224, 224, 224));

	mFont.Create(0.04f);

	// Shader
	mMaterialEntity.ps = EntityShader;
	mMaterialSeaCellNotTouch.ps = SeaCellNotTouchShader;
	mMaterialSeaCellTouch.ps = SeaCellTouchShader;
}

void App::OnStart()
{
	OnInit();

	XMFLOAT2 rowsCols = XMFLOAT2(10, 10);
	std::vector<std::vector<XMFLOAT2>> indexPosBoat = CreateBoat(rowsCols);
	CreateGrid(rowsCols,  indexPosBoat);

	// UI
	/*mSprite = *CreateSprite();
	mSprite->CenterAnchor();
	mSprite->x = 40;
	mSprite->y = 0;
	mSprite->pTexture = &m_texture;*/
	
	//Resources
	//m_font.Create(0.04f);
	//m_texture.Load("bird_amiga.png");
	//m_meshShip.CreateSpaceship();
	//m_meshSphere.CreateSphere(2.0f, 12, 12, ToColor(224, 224, 224));

	// Shader
	//m_materialShip.color = ToColor(255, 128, 0);
	//m_materialMissile.ps = MissileShader;
	//m_materialRock.ps = RockShader;

	// UI
	//m_pSprite = CreateSprite();
	//m_pSprite->CenterAnchor();
	//m_pSprite->x = 40;
	//m_pSprite->y = 0;
	//m_pSprite->pTexture = &m_texture;

	// 3D
	//m_missileSpeed = 10.0f;
	//m_camera.transform.pos.z = -5.0f;
	//m_pBall = CreateEntity();
	//m_pBall->pMesh = &m_meshSphere;
	//m_pBall->transform.pos.x = 3.0f;
	//m_pBall->transform.pos.y = 3.0f;
	//m_pBall->transform.pos.z = 5.0f;
	//m_pRock = CreateEntity();
	//m_pRock->pMesh = &m_meshSphere;
	//m_pRock->pMaterial = &m_materialRock;
	//m_pRock->transform.SetScaling(0.1f);

	// Ship
	//m_pShip = new Ship;
	//m_pShip->Create(&m_meshShip, &m_materialShip);
	//m_pShip->GetFSM()->ToState(ID(StateIdle));

	// Particle
	//m_particleData.Create(1000000);
	//m_particlePhysics.gy = -0.5f;
	//m_pEmitter = CreateParticleEmitter();
	//m_pEmitter->density = 2000.0f;
	//m_pEmitter->colorMin = ToColor(255, 0, 0);
	//m_pEmitter->colorMax = ToColor(255, 128, 0);
}

void App::OnUpdate()
{
	// YOUR CODE HERE

	// Move sprite
	//m_pSprite->y = 60 + RoundToInt(sinf(m_totalTime)*20.0f);

	// Turn ball
	//m_pBall->transform.AddYPR(m_deltaTime);

	// Move rock
	//m_pRock->transform.OrbitAroundAxis(m_pBall->transform.pos, CPU_UP, 3.0f, m_totalTime*2.0f);
	//m_pEmitter->pos = m_pRock->transform.pos;
	//m_pEmitter->dir = m_pRock->transform.dir;
	//m_pEmitter->dir.x = -m_pEmitter->dir.x; 
	//m_pEmitter->dir.y = -m_pEmitter->dir.y; 
	//m_pEmitter->dir.z = -m_pEmitter->dir.z; 

	// Turn camera
	//m_camera.transform.AddYPR(0.0f, 0.0f, m_deltaTime*0.1f);

	// Move ship
	if ( input.IsKey(VK_UP) )
	{
		m_camera.transform.Move(dtime*1.0f);
	}
	if ( input.IsKey(VK_DOWN) )
	{
		m_camera.transform.Move(-dtime*1.0f);
	}

	// Fire
	//if ( input.IsKeyDown(VK_LBUTTON) || input.IsKey(VK_RBUTTON) )
	//	app.SpawnMissileWithMouse();

	//std::list<Entity*> toDestroy = std::list<Entity*>();
	
	UpdateEntity();
	CollisionEntity();
	DeleteEntity();

	//for (auto it = mEntities.begin(); it != mEntities.end();)
	//{
	//	delete *it;
	//}

	// Quit
	if ( input.IsKeyDown(VK_ESCAPE) )
		Quit();
}

void App::OnExit()
{
	// YOUR CODE HERE

	//DELPTR(m_pShip);
	delete mGrid;//CleanTab and SetIsDestroy Entity

	ClearEntity();//CleanTab and Destroy Entity

	
}

void App::OnRender(int pass)
{
	// YOUR CODE HERE

	if ( pass!=CPU_PASS_UI_END )
		return;

	// Debug
	std::string info = std::to_string(m_fps) + " fps, ";
	info += std::to_string(m_statsDrawnTriangleCount) + " triangles, ";
	info += std::to_string(m_statsClipEntityCount) + " clipped entities\n";
	info += std::to_string(mEntities.size()) + " entity, ";
	info += std::to_string(m_particleData.alive) + " particles, ";
	DrawText(&mFont, info.c_str(), (int)GetMainRT()->widthHalf, 10, CPU_TEXT_CENTER);
}

void App::UpdateEntity()
{
	for (auto it = mEntities.begin(); it != mEntities.end();)
	{
		Entity* entity = *it;
		entity->OnUpdate();
		it++;
	}
}

void App::CollisionEntity()
{
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		Entity* entity1 = *it1;
		if (!entity1->GetIsCollider())
		{
			continue;
		}

		bool UpMe = false;
		for (auto it2 = mEntities.begin(); it2 != mEntities.end(); ++it2)
		{
			Entity* entity2 = *it2;

			if (*it1 == *it2)
			{
				//it is me
				UpMe = true;
				continue;
			}
			else if (UpMe == false)
			{
				if ((*it2)->GetIsCollider())
				{
					//pass collider
					continue;
				}
			}

			bool collided = false;
			switch (entity1->GetBoxColliding())
			{
			case _CUBE:

				switch (entity2->GetBoxColliding())
				{
				case _CUBE:   collided = CollisionRectRect(*it1, *it2); break;
				case _SPHERE: collided = CollisionRectSphere(*it1, *it2); break;
				}

				break;
			case _SPHERE:
				switch (entity2->GetBoxColliding())
				{
				case _CUBE:   collided = CollisionSphereRect(*it1, *it2); break;
				case _SPHERE: collided = CollisionSphereSphere(*it1, *it2); break;
				}
				break;
			}

			if (collided)
			{
				entity1->OnCollision(entity2);
				entity2->OnCollision(entity1);
			}
		}
	}
}

void App::DeleteEntity()
{
	for (auto it = mEntities.begin(); it != mEntities.end();)
	{
		Entity* entity = *it;
		if (entity->IsDestroy(true))
		{
			entity->OnDelete();
			//toDestroy.push_back(entity);
			delete* it;
		}
		else
		{
			it++;
		}
	}
}

void App::ClearEntity()
{
	for (auto it = mEntities.begin(); it != mEntities.end();)
	{
		(*it)->OnDelete();
		delete* it;
	}
	mEntities.clear();
}

/*void App::MissileShader(cpu_ps_io& io)
{
	// garder seulement le rouge du pixel éclairé
	io.color.x = io.p.color.x;//r
	//io.color.y = io.p.color.y;//g
	//io.color.z = io.p.color.z;//b
}*/

void App::EntityShader(cpu_ps_io& io)
{
	io.color.x = io.p.color.x;//r
	io.color.y = io.p.color.y;//g
	io.color.z = io.p.color.z;//b
}

void App::SeaCellNotTouchShader(cpu_ps_io& io)
{
	// garder seulement le bleu du pixel éclairé
	//io.color.x = io.p.color.x;//r
	//io.color.y = io.p.color.y;//g
	io.color.z = io.p.color.z;//b
}

void App::SeaCellTouchShader(cpu_ps_io& io)
{
	// garder seulement le rouge du pixel éclairé
	io.color.x = io.p.color.x;//r
	//io.color.y = io.p.color.y;//g
	//io.color.z = io.p.color.z;//b
}

void App::RockShader(cpu_ps_io& io)
{
	float scale = ((sinf(ttime*3.0f)*0.5f)+0.5f) * 0.5f + 0.5f; 
	io.color.x = io.p.color.x * scale;
	io.color.y = io.p.color.y * scale;
	io.color.z = io.p.color.z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool App::CollisionRectRect(Entity* entityCollider, Entity* otherColliding)
{
	XMFLOAT3 posCollider = entityCollider->GetPosition(); // top left
	XMFLOAT3 scaleCollider = entityCollider->GetScale();  // top left

	XMFLOAT3 posOther = otherColliding->GetPosition();    // top left
	XMFLOAT3 scaleOther = otherColliding->GetScale();     // top left

	return (fabs(posCollider.x - posOther.x) <= (scaleCollider.x + scaleOther.x) * 0.5f) &&
		   (fabs(posCollider.y - posOther.y) <= (scaleCollider.y + scaleOther.y) * 0.5f) &&
		   (fabs(posCollider.z - posOther.z) <= (scaleCollider.z + scaleOther.z) * 0.5f);
}

bool App::CollisionRectSphere(Entity* entityCollider, Entity* otherColliding)
{
	XMFLOAT3 posCollider = entityCollider->GetPosition();
	XMFLOAT3 scaleCollider = entityCollider->GetScale();
	XMFLOAT3 scaleHalfCollider = XMFLOAT3(scaleCollider.x * 0.5f, scaleCollider.y * 0.5f, scaleCollider.z * 0.5f);

	XMFLOAT3 posOther = otherColliding->GetPosition();
	float scaleOther = otherColliding->GetScale().x * 0.5f;


	float cx = std::max(posCollider.x - scaleHalfCollider.x, std::min(posOther.x, posCollider.x + scaleHalfCollider.x));
	float cy = std::max(posCollider.y - scaleHalfCollider.y, std::min(posOther.y, posCollider.y + scaleHalfCollider.y));
	float cz = std::max(posCollider.z - scaleHalfCollider.z, std::min(posOther.z, posCollider.z + scaleHalfCollider.z));

	float dx = posOther.x - cx;
	float dy = posOther.y - cy;
	float dz = posOther.z - cz;

	return (dx * dx + dy * dy + dz * dz) <= scaleOther * scaleOther;
}

bool App::CollisionSphereRect(Entity* entityCollider, Entity* otherColliding)
{
	return CollisionRectSphere(otherColliding, entityCollider);
}

bool App::CollisionSphereSphere(Entity* entityCollider, Entity* otherColliding)
{
	XMFLOAT3 posCollider = entityCollider->GetPosition(); // top left
	XMFLOAT3 posOther = otherColliding->GetPosition();    // top left

	float rCollider = entityCollider->GetScale().x * 0.5f;
	float rOther = otherColliding->GetScale().x * 0.5f;

	XMFLOAT3 dis = { posCollider.x - posOther.x, posCollider.y - posOther.y, posCollider.z - posOther.z };
	float dist2 = dis.x * dis.x + dis.y * dis.y + dis.z * dis.z;

	float r = rCollider + rOther;
	return dist2 <= r * r;
}

cpu_material* App::GetMaterialEntity()
{
	return &mMaterialEntity;
}

int App::GetRandomNumber(int min, int max)
{
	int range = max - min + 1;
	int value = rand() % range + min;
	return value;
}


/*Ship::Ship()
{
	m_pEntity = nullptr;
	m_pFSM = nullptr;
}

Ship::~Ship()
{
}

void Ship::Create(cpu_mesh* pMesh, cpu_material* pMaterial)
{
	m_pEntity = cpu.CreateEntity();
	m_pEntity->pMesh = pMesh;
	m_pEntity->pMaterial = pMaterial;
	m_pEntity->transform.pos.z = 5.0f;
	m_pEntity->transform.pos.y = -3.0f;

	m_pFSM = cpu.CreateFSM(this);
	m_pFSM->SetGlobal<StateGlobal>();
	m_pFSM->Add<StateIdle>();
	m_pFSM->Add<StateBlink>();
}

void Ship::Destroy()
{
	m_pFSM = cpu.Release(m_pFSM);
	m_pEntity = cpu.Release(m_pEntity);
}

void Ship::Update()
{
	// Turn ship
	m_pEntity->transform.AddYPR(dtime, dtime, dtime);

	// Move ship
	m_pEntity->transform.pos.z += dtime * 1.0f;

	// Fire
	if (input.IsKey(VK_SPACE) )
		app.SpawnMissile();
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void StateGlobal::OnEnter(Ship& cur, int from)
{
}

void StateGlobal::OnExecute(Ship& cur)
{
	cur.Update();
}

void StateGlobal::OnExit(Ship& cur, int to)
{
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void StateIdle::OnEnter(Ship& cur, int from)
{
}

void StateIdle::OnExecute(Ship& cur)
{
	// Blink every 3 seconds
	if ( cur.GetFSM()->totalTime>3.0f )
	{
		cur.GetFSM()->ToState(ID(StateBlink));
		return;
	}
}

void StateIdle::OnExit(Ship& cur, int to)
{
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void StateBlink::OnEnter(Ship& cur, int from)
{
}

void StateBlink::OnExecute(Ship& cur)
{
	float v = fmod(cur.GetFSM()->totalTime, 0.2f);
	if ( v<0.1f )
	{
		cur.GetEntity()->visible = true;
	}
	else
	{
		cur.GetEntity()->visible = false;
	}

	if ( cur.GetFSM()->totalTime>1.0f )
	{
		cur.GetFSM()->ToState(ID(StateIdle));
		return;
	}
}

void StateBlink::OnExit(Ship& cur, int to)
{
}*/
