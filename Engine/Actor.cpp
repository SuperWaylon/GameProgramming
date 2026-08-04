#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "mathUtil.h"

namespace nu
{
    void Actor::Update(float dt)
    {
        //Lifespan
        if (m_lifespan > 0.0f)
        {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        //Physics
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / ((1.0f) + m_damping * dt);

        if (m_wrap)
        {
            m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
            m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
        }
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        if (m_model)
        {
            renderer.DrawModel(*m_model, m_transform);
        }
    }

    float Actor::GetRadius() const
    {
        return m_model->GetRadius() * m_transform.scale * 0.9f;
    }

}