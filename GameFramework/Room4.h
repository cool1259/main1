#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class Room4 :public IScene
{
public:
	Room4() {}
	virtual ~Room4() {}


	// IScene을(를) 통해 상속됨
	virtual void initialize() override
	{
		if (!sceneObjectPool_.isEmpty())
			return;

		shared_ptr<Entity>& entity = sceneObjectPool_.acquire();
		entity->addComponent<PartyUI>();
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"PartyUI");
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->addComponent<Mouse>();
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"mouse");
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setMouse(entity);

		


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
		entity->addComponent<FarBackGround>(2);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);


		





		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData(PRACTICE).json", ifstream::binary); //데이터에 다 읽어옴

		//std::string data;
		Json::Reader reader; //json리더기
		Json::Value root; //값을받아올 루트
		reader.parse(data, root); // 읽어온 데이터를 루트에 값으로 파싱해줌
		const Json::Value& arr = root["Point"]; //루트에 point부분(인덱스) 가져옴 

		for (auto obj : arr)
		{

			auto jsonName = obj["Name"].asDouble();

			auto X = obj["X"].asDouble();
			auto Y = obj["Y"].asDouble();

			auto Width = obj["Width"].asDouble();
			auto Height = obj["Height"].asDouble();

			if (jsonName == 0)
			{
				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
				entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			}
			else if (jsonName == 1)
			{

			
				if (doorEntity_.lock() == nullptr)
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"Room5");
					entity->getComponent<Transform>().position_ = _vec3(X, Y - 257 / 2 + 172 / 2 - 45.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_ = entity;

	
					if (SceneManager::getInstance()->pastSceneName_ == L"Room5")
					{


						playerPosition= _vec3(_vec3(X, Y - 257 / 2 + 172 / 2 - 45.f - 20.f, 0.f));
						
					}

				  
					
				}
				else
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"Room3");
					entity->getComponent<Transform>().position_ = _vec3(X, Y - 257 / 2 + 172 / 2 - 45.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_2 = entity;

					if (SceneManager::getInstance()->pastSceneName_ == L"Room3")
					{
						playerPosition= _vec3(_vec3(X, Y - 257 / 2 + 172 / 2 - 45.f - 20.f, 0.f));
				
					}

				}
			}

			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);


			}

		}

		//밧줄
	/*	entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(1, _vec3(-525, -800.f, 0.f), _vec3(2, 170.f, 1.f));
		entityManager_->insertEntity(entity);*/

		_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(-mapSize.x / 2, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(mapSize.x / 2 - 10.f, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);






		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"초록버섯");
		entity->getComponent<Transform>().position_ = { 200.f,30.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"초록버섯");
		entity->getComponent<Transform>().position_ = { 100.f,30.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"초록버섯");
		entity->getComponent<Transform>().position_ = { 0.f,30.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"초록버섯");
		entity->getComponent<Transform>().position_ = { 70.f,30.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"초록버섯");
		entity->getComponent<Transform>().position_ = { 150.f,30.f,-0.f };
		entityManager_->insertEntity(entity);
		entity->getComponent<AtlasAnimation>().setRight(false);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"주황버섯");
		entity->getComponent<Transform>().position_ = { 200.f,-252.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"주황버섯");
		entity->getComponent<Transform>().position_ = { 0.f,-252.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"주황버섯");
		entity->getComponent<Transform>().position_ = { 130.f,-252.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"주황버섯");
		entity->getComponent<Transform>().position_ = { 300.f,-252.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		auto player = GameManager::getInstance()->getPlayer();
		player->getComponent<Transform>().position_ = playerPosition;
		player->getComponent<PlayerController>().setReCameraSetting();

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"키쿠");
		entity->addComponent<NPC1>(L"키쿠");
		entity->getComponent<Transform>().position_ = _vec3(750.f,-310.f,0.f);
		entityManager_->insertEntity(entity);


		/*entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"SHOP");
		entity->addComponent<ItemShop>();
		EntityManager::getInstance()->insertEntity(entity);
		GameManager::getInstance()->setShop(entity);
		entity->getComponent<ItemShop>().bornSceneName_ = L"Room4";*/

	}

	virtual void update() override
	{
		entityManager_->update();

		if (!doorEntity_.expired())
		{
			if (InputManager::getInstance()->keyDown(DIK_UP))
			doorEntity_.lock()->getComponent<Door>().checkAndChangeScene();
		}
		if (!doorEntity_2.expired())
		{
			if (InputManager::getInstance()->keyDown(DIK_UP))
				doorEntity_2.lock()->getComponent<Door>().checkAndChangeScene();
		}
	}

	virtual void lateUpdate() override
	{
		entityManager_->lateUpdate();

	}

	virtual void render() override
	{
		entityManager_->render();

	}

	virtual void release() override
	{
		//entityManager_->releaseAll();
		entityManager_->releaseEntity(Entity::ENTITYTYPE::UNKNOWN);
		//entityManager_->releaseEntity(Entity::ENTITYTYPE::PLAYER);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::ENEMY);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::MAP);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::TRAP);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::EFFECT);

		//entityManager_->releaseEntity(Entity::ENTITYTYPE::GOLD);


		//entityManager_->releaseEntity(Entity::ENTITYTYPE::FILDITEM);


	}

	virtual void refresh()override
	{
		entityManager_->refresh();
	}
private:
	bool stageClear_ = false;
	weak_ptr<Entity> doorEntity_;
	weak_ptr<Entity> doorEntity_2;
	vector<shared_ptr<Entity>> remainMonster;
	shared_ptr<Entity> MapControllerEntity;
	
};