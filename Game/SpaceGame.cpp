#include "SpaceGame.h"
#include "Engine.h"
#include "player.h"
#include "Enemy.h"
#include "Assets.h"

#include <memory>

using namespace nu; 

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	m_titleFont = Resources().GetWithID<Font>("title_font", "fonts/airstrike.ttf", 64.0f);
	m_titleText = new Text(m_titleFont);
	m_titleText->Create(Engine::Get().GetRenderer(), "Blast++", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = Resources().GetWithID<Font>("title_font", "fonts/airstrike.ttf", 32.0f);

	m_scoreText = new Text(Resources().Get<Font>("fonts/airstrike.ttf", 32.0f));
	m_livesText = new Text(Resources().Get<Font>("fonts/airstrike.ttf", 32.0f));
	m_difficultyText = new Text(Resources().Get<Font>("fonts/airstrike.ttf", 32.0f));

	//Initialize Audio Here
	Engine::Get().GetAudio().AddSound("BGM", "audio/RockNRoll.mp3");
	Engine::Get().GetAudio().AddSound("Enemy Death", "audio/edeath.wav");
	Engine::Get().GetAudio().AddSound("Player Death", "audio/pdeath.wav");
	Engine::Get().GetAudio().AddSound("Laser1", "audio/laser1.wav");
	Engine::Get().GetAudio().AddSound("Laser2", "audio/laser2.wav");
	Engine::Get().GetAudio().AddSound("Thrust", "audio/thrust.wav");

	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
	
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;

	case SpaceGame::GameState::StartGame:
		Engine::Get().GetAudio().PlayMusic("BGM");
		m_score = 0;
		m_lives = 3;
		m_spawnTime = 3.0f;
		m_stateTimer = 1.0f;
		m_difficultyLevel = 1;
		m_gameState = GameState::StartLevel;

		break;
	
	case SpaceGame::GameState::StartLevel:
		m_scene->RemoveAllActors();
		m_spawnTime = 5.0f;
		SpawnPlayer();
		m_gameState = GameState::Game;
	
		break;
	case SpaceGame::GameState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f)
		{
			m_spawnTimer = m_spawnTime;

			int spawnAmount = 1 + (m_difficultyLevel / 3);   //levels 1-2: 1 enemy, 3-5: 2 enemies, 6+: 3 enemies
			for (int i = 0; i < spawnAmount; i++)
			{
				SpawnEnemy();
			}

			//Increase difficulty
			m_spawnCount++;
			if (m_spawnCount > 5 && m_spawnTime > m_minSpawnTime)
			{
				m_spawnCount = 0;
				m_spawnTime = std::max(m_minSpawnTime, m_spawnTime - 0.5f);
				m_difficultyLevel++;
			}
		}

		break;
	case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f)
		{
			if (m_lives > 0)
			{
				m_gameState = GameState::StartLevel;
			}
			else
			{
				m_scene->RemoveAllActors();
				m_gameState = GameState::Title;
				Engine::Get().GetAudio().StopMusic();
			}
		}
		break;
	default:
		break;
	}
	Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer)
{
	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.jpg", Engine::Get().GetRenderer()), 500, 500);
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		m_titleText->Draw(renderer, renderer.GetWidth() / 2.0f - 125.0f, renderer.GetHeight() / 2.0f - 80.0f);
		break;

	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
	break;
	case SpaceGame::GameState::Game:

		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 30.0f);

		m_difficultyText->Create(renderer, "Difficulty: " + std::to_string(m_difficultyLevel), { 1.0f, 1.0f, 1.0f });
		m_difficultyText->Draw(renderer, 30.0f, 70.0f);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() - 300.0f, 30.0f);

		break;
	case SpaceGame::GameState::GameOver:
		break;
	default:
		break;
	}
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;
	m_stateTimer = m_lives > 0 ? 1.5f : 3.0f; 
	m_gameState = GameState::GameOver;
}

void SpaceGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy()
{
	auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
	actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor));
}