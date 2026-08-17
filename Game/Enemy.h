#pragma once
#include "Actor.h"

struct EnemyDesc : public nu::ActorDesc
{
    float speed{ 0.0f };
    float health{ 1.0f };
};

class Enemy : public nu::Actor
{
public:
    Enemy() = default;
    Enemy(const EnemyDesc& enemyDesc) :
        Actor{ enemyDesc },
        m_speed{ enemyDesc.speed },
        m_health{ enemyDesc.health}
    {}

    CLASS_PROTOTYPE(Enemy)

    void Update(float dt) override;
    void OnCollision(Actor* other) override;

    virtual void Read(const nu::json::value_t& value) override;

private:
    int m_ammo = 0;
    float m_speed = 0.0f;
    float m_health = 1.0f;
};