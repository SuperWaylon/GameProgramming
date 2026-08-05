#include "Engine.h"
#include "player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include "SDL3/SDL.h"
#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <memory>

using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

int main()
{
    std::cout << "====================Object====================\n";
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }

    std::cout << "====================Raw Pointers====================\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
    }

    std::cout << "====================Unique Pointers====================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

    std::cout << "====================Shared Pointers====================\n";
    std::shared_ptr<Object> objectC;
    {
        auto objectA = std::make_shared<Object>();
        std::cout << objectA.get() << std::endl;
        std::cout << objectA.use_count() << std::endl;
        auto objectB = objectA;
        std::cout << objectB.get() << std::endl;
        std::cout << objectB.use_count() << std::endl;
        objectC = objectA;
        std::cout << objectC.get() << std::endl;
        std::cout << objectC.use_count() << std::endl;
    }
    std::cout << objectC.use_count() << std::endl;

    //return 0;
    
    //INITIALIZATION
    SetWorkingDirectory("Assets");
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    //Create audio system
    Engine::Get().GetAudio().AddSound("alert", "audio/test/alert.mp3");
    Engine::Get().GetAudio().AddSound("duck-toy", "audio/test/duck-toy.mp3");
    Engine::Get().GetAudio().AddSound("error", "audio/test/error.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "audio/test/hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("mario", "audio/test/mario.mp3");
    Engine::Get().GetAudio().AddSound("oof", "audio/test/oof.mp3");
    Engine::Get().GetAudio().AddSound("scream", "audio/test/scream.mp3");
    Engine::Get().GetAudio().AddSound("whistle", "audio/test/whistle.mp3");

    Scene scene;

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/player.png", Engine::Get().GetRenderer());

    for (int i = 0; i < 20; i++)
    {}

    //Photoshop
    std::vector<Vector2> points;

    // handle events
    SDL_Event e;

    //MAIN LOOP
    bool quit = false;

    while (!quit) 
    {
        //UPDATE
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        //Engine
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        //Game
        game.Update(dt);
        
        
        //Paint Stuff
        /*
        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left))
        {
            Vector2 mousePosition = Engine::Get().GetInput().getMousePosition();

            if (points.empty() || std::isnan(points.back().x))
            {
                points.push_back(mousePosition);
            }
            else
            {
                Vector2 delta = mousePosition - points.back();
                if (delta.Length() > 10.0f)
                {
                    points.push_back(mousePosition);
        }
            }
        }
                
        if (Engine::Get().GetInput().GetButtonReleased(Input::MouseButton::Left))
        {
            if (!points.empty() && !std::isnan(points.back().x))
            {
                points.push_back(Vector2{ NAN, NAN });
            }
        }
        */

        //Audio Keys
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("alert");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            Engine::Get().GetAudio().PlaySound("duck-toy");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            Engine::Get().GetAudio().PlaySound("error");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            Engine::Get().GetAudio().PlaySound("hee-hee");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            Engine::Get().GetAudio().PlaySound("mario");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_6))
        {
            Engine::Get().GetAudio().PlaySound("oof");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_7))
        {
            Engine::Get().GetAudio().PlaySound("scream");
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_8))
        {
            Engine::Get().GetAudio().PlaySound("whistle");
        }

        //RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().DrawTexture(*texture, 30, 30, 0, 1.0f, false);
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        //Paint Stuff
        /*
        for (int i = 0; i < (int)points.size() - 1; i++)
        {
            if (std::isnan(points[i].x) || std::isnan(points[i + 1].x))
        {
                continue; 
            }

            Engine::Get().GetRenderer().SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        */
        Engine::Get().GetRenderer().Present();
    }

    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}

