#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "ResourceManager.h"

#include <vector>

namespace nu
{
	class Texture;
	class Renderer;

	struct Particle
	{
		bool active{ false };
		float lifespan{ 1 };
		float maxLifespan{ 1 };   

		Vector2 position{ 0, 0 };
		Vector2 velocity{ 0, 0 };
		Color color{ 0, 0, 0 };
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		bool Initialize(Renderer& renderer, size_t poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(const Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
		res_t<Texture> m_texture;
	};
}