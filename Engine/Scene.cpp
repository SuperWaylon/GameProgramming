#pragma once
#include "pch.h"
#include "Scene.h"
#include "Actor.h"

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