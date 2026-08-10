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
#include <random>
#include <fstream>

using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{
    //INITIALIZATION
    SetWorkingDirectory("Assets");

    {
        //Read file (Input file)
        std::ifstream file("data/text.txt");;
        if (file.is_open())
        {
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
        else
        {
            std::cout << "Could not load.\n";
        }
        file.close();
    }

    {
        //Write file (Output file)
        std::ofstream file("data/text.txt", std::ios::app);;
        if (file.is_open())
        {
            file << "\nHave a good day.\n";
        }
    }

    {
        //Read / Write (input / output file)
        std::fstream file("data/text.txt", std::ios::in | std::ios::out | std::ios::app);;
        if (file.is_open())
        {
            //Input
            file << "Add a line.\n";
            file.seekg(0);
            //Output
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        //save game data
        bool save = false;
        if (save == true)
        {
            name = "Waylon Rossiter";
            score = 1234;
            isAlive = true;

            //Save game data
            std::ofstream file("data/game.txt");;
            if (file.is_open())
            {
                file << name << "\n";
                file << score << "\n";
                file << std::boolalpha << isAlive << "\n";
            }
        }
        //load game data
        bool load = true;
        if (load)
        {
            //Read file (Input file)
            std::ifstream file("data/game.txt");;
            if (file.is_open())
            {
                std::getline(file, name);

                std::string str;
                std::getline(file, str);

                score = std::stoi(str);
                //file >> score;
                file >> std::boolalpha >> isAlive;
            }
        }
        //Display game data
        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }
    return 0;

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

