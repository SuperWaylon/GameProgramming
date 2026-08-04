#pragma once
#include "File.h"
#include "random.h"
#include "Vector2.h"
#include "mathUtil.h"

#include "Text.h"
#include "Texture.h"

#include "Renderer.h"
#include "Input.h"
#include "gametime.h"
#include "Audio.h"
#include "ParticleSystem.h"

#include "actor.h"
#include "Scene.h"
#include "Game.h"

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

		Audio& GetAudio() { return m_audio; }

		ParticleSystem& GetPS() { return m_particleSystem; }

	private:

		Engine() = default;
	private:

		Input m_input;
		Renderer m_renderer;

		Time m_time;

		Audio m_audio;

		ParticleSystem m_particleSystem;
	};
	
}