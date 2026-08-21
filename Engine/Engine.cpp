#include "pch.h"
#include "Engine.h"
#include "framework.h"

#include <iostream>

namespace nu
{
	bool Engine::Initialize()
	{
		m_renderer.Initialize("Game Engine", 1280, 1024);
		m_input.Initialize();
		m_audio.Initialize();
		m_particleSystem.Initialize(m_renderer);
		m_physics.Initialize();
		return true;
	}
	void Engine::Shutdown()
	{
		m_input.Shutdown();
		m_renderer.Shutdown();
		m_audio.Shutdown();
		m_particleSystem.Shutdown();
		m_physics.Shutdown();
	}

	void Engine::Update()
	{
		m_input.Update();
		m_time.Tick();
		m_audio.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
		m_physics.Update(m_time.GetDeltaTime());
	}
}
