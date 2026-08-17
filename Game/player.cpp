#include "player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"

void Player::Update(float dt)
{

    float thrust = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W))  thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S))  thrust = -m_speed;

    m_isThrusting = thrust > 0.0f;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A))  rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D))  rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    // Particle System
    if (m_isThrusting && nu::RandomFloat(0.0f, 1.0f) < 0.3f)
    {
        nu::Particle particle;

        nu::Vector2 offset(-20.0f, 0.0f);
        offset = offset.Rotate(m_transform.rotation * nu::DegToRad);

        particle.position = m_transform.position + offset;
        particle.color = { 1.0f, 0.5f, 0.0f };
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

        nu::Engine::Get().GetPS().AddParticle(particle);
    }

    // Weapon switch
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_LCTRL))
    {
        m_weaponMode = (m_weaponMode == WeaponMode::FullAuto) ? WeaponMode::Spread : WeaponMode::FullAuto;
    }

    // Fire
    m_fireTimer -= dt;

    float currentFireRate = (m_weaponMode == WeaponMode::FullAuto) ? m_fireRate : m_spreadFireRate;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0.0f)
    {
        m_fireTimer = currentFireRate;

        BulletDesc bulletDesc;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        //bulletDesc.model = assets::bmodel;
        bulletDesc.texture = nu::Resources().Get<nu::Texture>("textures/bullet.png", nu::Engine::Get().GetRenderer());
        bulletDesc.transform = m_transform;
        bulletDesc.damping = 3.0f;
        bulletDesc.speed = 1000.0f;
        bulletDesc.lifespan = 1.0f;

        if (m_weaponMode == WeaponMode::FullAuto)
        {
            nu::Engine::Get().GetAudio().PlaySound("Laser1");

            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));
        }
        else // Spread
        {
            nu::Engine::Get().GetAudio().PlaySound("Laser2");

            // center
            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));

            // left
            bulletDesc.transform.rotation = m_transform.rotation - m_spreadAngle;
            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));

            // right
            bulletDesc.transform.rotation = m_transform.rotation + m_spreadAngle;
            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));
        }
    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LSHIFT))
    {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else
    {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    m_isThrusting = thrust > 0.0f;

    if (m_isThrusting)
    {
        nu::Engine::Get().GetAudio().PlayLoopingSound("Thrust");
    }
    else
    {
        nu::Engine::Get().GetAudio().StopLoopingSound("Thrust");
    }

    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const
{
    Actor::Draw(renderer);
}

void Player::OnCollision(Actor* other)
{
    if (other->GetTag() == "Enemy")
    {
        SetDestroyed();
        other->SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();

        nu::Engine::Get().GetAudio().PlaySound("Player Death");

        // create particle explosion
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 0.0f, 0.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}