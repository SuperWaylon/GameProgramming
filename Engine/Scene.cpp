#pragma once
#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Factory.h"

namespace nu
{
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{ 
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor)); 
	}

	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}

	bool Scene::Load(const std::string& sceneName)
	{
		json::document_t document;
		if (json::Load("data/scene.json", document))
		{
			if (JSON_HAS_NAME(document, "actors"))
			{
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray())
				{
					//Get actor type
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					//Create actor of type
					auto actor = Factory::Instance().Create<Actor>(typeName);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ(actorValue, prototype);

					if (prototype)
					{
						//Add prototype to factory registry
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						//Or just add the actor to the scene
						AddActor(std::move(actor));
					}
				}
			}
		}

		return true;
	}

	void Scene::Update(float dt)
	{
		//Update Actos
		for (auto& actor : m_actors)
		{
			actor->Update(dt);
		}

		//Update Collisions
		UpdateCollisions();

		//Destroyed Actors
		std::erase_if(m_actors, [](auto& actor) {return actor->m_destroyed;});

		//Pending Actors
		for (auto& actor : m_pendingActors)
		{
			m_actors.push_back(std::move(actor));
		}
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer)
	{
		for (const auto& actor : m_actors)
		{
			if (actor)
				actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors)
		{
			for (auto& actorB : m_actors)
			{
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) continue;

				//Check Collision
				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius())
				{
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}