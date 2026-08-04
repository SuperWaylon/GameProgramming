#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
    float speed;
    BulletDesc() { wrap = false; }
};

class Bullet : public nu::Actor
{
public:
    Bullet() = default;
    Bullet(const BulletDesc& BulletDesc) :
        Actor{ BulletDesc },
        m_speed{ BulletDesc.speed }
    {}

    void Update(float dt) override;

private:
    float m_speed = 800.0f;
};