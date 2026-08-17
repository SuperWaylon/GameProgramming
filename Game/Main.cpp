#include "Engine.h"
#include "player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "SDL3/SDL.h"

#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace nu;


int main()
{
    //Can't touch this
    SetWorkingDirectory("Assets");

    //INITIALIZATION

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

        Engine::Get().GetRenderer().Present();
    }

    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}

