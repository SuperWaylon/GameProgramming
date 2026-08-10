#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Texture.h"

#include <algorithm>

namespace nu
{
	bool ParticleSystem::Initialize(Renderer& renderer, size_t size)
	{
		m_particles.resize(size);
		m_texture = Resources().Get<Texture>("textures/particle.png", renderer);

		if (!m_texture)
		{
			std::cerr << "ParticleSystem: failed to load textures/particle.png\n";
		}

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		for (auto& particle : m_particles)
		{
			particle = Particle{};
		}
	}

	void ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			particle.lifespan -= dt;
			particle.active = particle.lifespan > 0;
			particle.position += particle.velocity * dt;
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer)
	{
		if (!m_texture) return;

		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			float alpha = std::clamp(particle.lifespan / particle.maxLifespan, 0.0f, 1.0f);

			renderer.SetTextureColor(*m_texture, particle.color.r, particle.color.g, particle.color.b, alpha);
			renderer.DrawTexture(*m_texture, particle.position.x, particle.position.y, 0.0f, 1.0f);
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle)
		{
			*freeParticle = particle;
			freeParticle->active = true;
			freeParticle->maxLifespan = particle.lifespan;
		}
		else
		{
			std::cerr << "ParticleSystem: pool exhausted, particle dropped\n";
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.active)
				return &particle;
		}

		return nullptr;
	}
}