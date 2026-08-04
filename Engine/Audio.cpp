#include "pch.h"
#include "Audio.h"
#include <iostream>
#include <fmod_errors.h>

namespace nu
{
	bool Audio::Initialize()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
		if (!CheckFMODResult(result))
			return false;

		void* extradriverdata = nullptr;
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result))
			return false;

		return true;
	}

	void Audio::Shutdown()
	{
		CheckFMODResult(m_fmodSystem->release());
	}

	void Audio::Update()
	{
		CheckFMODResult(m_fmodSystem->update());
	}

	bool Audio::AddSound(const std::string& name, const std::string& filename)
	{
		// check if key exists in sounds map
		if (m_sounds.find(name) != m_sounds.end())
		{
			std::cerr << "Audio System : name already exists " << name << std::endl;
			return false;
		}

		// create sound from key
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &sound);
		if (!CheckFMODResult(result))
			return false;

		// insert sound into map
		m_sounds[name] = sound;

		return true;
	}

	bool Audio::PlaySound(const std::string& name, bool loop)
	{
		// check if sound exists in sounds map
		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}

		// play sound from key
		FMOD::Channel* channel = nullptr;
		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds[name], nullptr, false, &channel);
		if (!CheckFMODResult(result))
			return false;


		if (loop)
		{
			m_sounds[name]->setLoopCount(-1);
		}

		return true;
	}

	bool Audio::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}

		return true;
	}

	bool Audio::PlayMusic(const std::string& name)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}

		// stop any currently playing music first
		StopMusic();

		m_sounds[name]->setMode(FMOD_LOOP_NORMAL);
		m_sounds[name]->setLoopCount(-1);

		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds[name], nullptr, false, &m_musicChannel);
		if (!CheckFMODResult(result))
			return false;

		return true;
	}

	void Audio::StopMusic()
	{
		if (m_musicChannel != nullptr)
		{
			m_musicChannel->stop();
			m_musicChannel = nullptr;
		}
	}

	bool Audio::PlayLoopingSound(const std::string& name)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}

		// already playing? don't restart it
		if (IsLoopingSoundPlaying(name))
			return true;

		m_sounds[name]->setMode(FMOD_LOOP_NORMAL);
		m_sounds[name]->setLoopCount(-1);

		FMOD::Channel* channel = nullptr;
		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds[name], nullptr, false, &channel);
		if (!CheckFMODResult(result))
			return false;

		m_loopingChannels[name] = channel;
		return true;
	}

	void Audio::StopLoopingSound(const std::string& name)
	{
		auto it = m_loopingChannels.find(name);
		if (it != m_loopingChannels.end() && it->second != nullptr)
		{
			it->second->stop();
			m_loopingChannels.erase(it);
		}
	}

	bool Audio::IsLoopingSoundPlaying(const std::string& name)
	{
		auto it = m_loopingChannels.find(name);
		if (it == m_loopingChannels.end() || it->second == nullptr)
			return false;

		bool playing = false;
		it->second->isPlaying(&playing);
		return playing;
	}
}