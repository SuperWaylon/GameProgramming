#pragma once
#include <vector>


namespace nu
{
	class Actor;

	class Scene
	{
	public:
		void AddActor(Actor* actor) { m_actors.push_back(actor); }

		

	private:
		std::vector<Actor*> m_actors;
	};
}