#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace nu
{
	class Audio
	{
	public:
		Audio() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const std::string& name, const std::string& filename);
		bool PlaySound(const std::string& name, bool loop = false);

		bool PlayMusic(const std::string& name);
		void StopMusic();

		bool PlayLoopingSound(const std::string& name);
		void StopLoopingSound(const std::string& name);
		bool IsLoopingSoundPlaying(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);

	private:
		FMOD::System* m_fmodSystem = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
		FMOD::Channel* m_musicChannel = nullptr;
		std::map<std::string, FMOD::Channel*> m_loopingChannels;

	};
}