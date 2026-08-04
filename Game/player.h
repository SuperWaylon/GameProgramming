#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
    float speed;
    std::shared_ptr<nu::Model> thrusterModel;   // <-- changed from nu::Model
};

class Player : public nu::Actor
{
public:
    enum class WeaponMode
    {
        FullAuto,
        Spread
    };

public:
    Player() = default;
    Player(const PlayerDesc& playerDesc) :
        Actor{ playerDesc },
        m_speed{ playerDesc.speed },
        m_thrusterModel{ playerDesc.thrusterModel }
    {
    }

    void Update(float dt) override;
    void Draw(const class nu::Renderer& renderer) const override;
    void OnCollision(Actor* other) override;

private:
    int m_ammo = 0;
    float m_speed = 0.0f;
    std::shared_ptr<nu::Model> m_thrusterModel;
    bool m_isThrusting = false;

    float m_fireRate = 0.25f;
    float m_fireTimer = 0.0f;

    WeaponMode m_weaponMode = WeaponMode::FullAuto;
    float m_spreadFireRate = 0.6f;
    float m_spreadAngle = 15.0f;
};