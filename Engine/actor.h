#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>
#include <memory>

namespace nu
{
    class Scene;

    struct ActorDesc
    {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity{ 0.0f, 0.0f };
        float damping{ 0.0f };
        float lifespan{ 0 };
        std::shared_ptr<Model> model;
        bool wrap{ true };
    };

    class Actor
    {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_name{ actorDesc.name },
            m_tag{ actorDesc.tag },
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model },
            m_damping{ actorDesc.damping },
            m_lifespan{ actorDesc.lifespan },
            m_wrap{ actorDesc.wrap }
        {
        }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2& GetVelocity() { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        std::string& GetName() { return m_name; }
        std::string& GetTag() { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy = true) { m_destroyed = true; }
        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        float m_damping{ 0.0f };
        float m_lifespan{ 0 };
        bool m_destroyed = {false};
        bool m_wrap{ true };

        std::shared_ptr<Model> m_model;
        Scene* m_scene{ nullptr };

    };
}
