#include "Assets.h"

using namespace nu;

namespace assets
{
    //Player Model
       // Player ship
            Mesh ship{ {
                    Vector2{2,0}, 
                    Vector2{-2,2}, 
                    Vector2{-1,0}, 
                    Vector2{-2,-2}, 
                    Vector2{2,0} },
                    Color{1.0f, 1.0f, 1.0f} };
            std::shared_ptr<Model> pmodel = std::make_shared<Model>( std::vector<Mesh>{ ship } );

    // Thrust
        Mesh flame{ {
                Vector2{-1,0.6f},
                Vector2{-3,0}, 
                Vector2{-1,-0.6f}, 
                Vector2{-1,0.6f} }, 
                Color{1.0f, 0.5f, 0.0f} };
        std::shared_ptr<Model> thrusterModel = std::make_shared<Model>(std::vector<Mesh>{ flame });

    //Enemy Model
        // Main skull outline
            Mesh skull{ {
                    Vector2{4,4}, 
                    Vector2{-4,4}, 
                    Vector2{-4,-4}, 
                    Vector2{4,-4}, 
                    Vector2{4,4} }, 
                    Color{1.0f, 1.0f, 1.0f} };

        // Nose
            Mesh nose{ {
                    Vector2{0,0}, 
                    Vector2{-2,0.5f}, 
                    Vector2{-2,-0.5f}, 
                    Vector2{0,0} }, 
                    Color{1.0f, 1.0f, 1.0f} };

        // Teeth
            Mesh tooth1{ {
                    Vector2{-4,3.5f}, 
                    Vector2{-4,2.5f}, 
                    Vector2{-5,2.5f},
                    Vector2{-5,3.5f}, 
                    Vector2{-4,3.5f} }, 
                    Color{1.0f, 1.0f, 1.0f} };
            Mesh tooth2{ {
                    Vector2{-4,2}, 
                    Vector2{-4,1}, 
                    Vector2{-5,1}, 
                    Vector2{-5,2}, 
                    Vector2{-4,2} }, 
                    Color{1.0f, 1.0f, 1.0f} };
            Mesh tooth3{ {
                    Vector2{-4,0.5f}, 
                    Vector2{-4,-0.5f}, 
                    Vector2{-5,-0.5f}, 
                    Vector2{-5,0.5f}, 
                    Vector2{-4,0.5f} }, 
                    Color{1.0f, 1.0f, 1.0f} };
            Mesh tooth4{ {
                    Vector2{-4,-1}, 
                    Vector2{-4,-2}, 
                    Vector2{-5,-2}, 
                    Vector2{-5,-1}, 
                    Vector2{-4,-1} }, 
                    Color{1.0f, 1.0f, 1.0f} };
            Mesh tooth5{ {
                    Vector2{-4,-2.5f}, 
                    Vector2{-4,-3.5f}, 
                    Vector2{-5,-3.5f},
                    Vector2{-5,-2.5f}, 
                    Vector2{-4,-2.5f} }, 
                    Color{1.0f, 1.0f, 1.0f} };

        // Eyes 
            Mesh leftEye{ {
                    Vector2{0,3}, 
                    Vector2{0,1}, 
                    Vector2{2,1}, 
                    Vector2{2,3}, 
                    Vector2{0,3} }, 
                    Color{1.0f, 0.0f, 0.0f} };
            Mesh rightEye{ {
                    Vector2{0,-1}, 
                    Vector2{0,-3}, 
                    Vector2{2,-3}, 
                    Vector2{2,-1}, 
                    Vector2{0,-1} }, 
                    Color{1.0f, 0.0f, 0.0f} };
            std::shared_ptr<Model> emodel = std::make_shared<Model>(std::vector<Mesh>{ skull, nose, tooth1, tooth2, tooth3, tooth4, tooth5, leftEye, rightEye } );

    //Bullet Model
            //Bullet
            Mesh bulletMesh{
              {
                    Vector2{ -1, -1 },
                    Vector2{ 1, 0 },
                    Vector2{ -1, 1 },
                    Vector2{ -1, -1 } },
                    Color{ 1.0f, 0.0f, 0.0f } };
            std::shared_ptr<Model> bmodel = std::make_shared<Model>(std::vector<Mesh>{ bulletMesh });
}