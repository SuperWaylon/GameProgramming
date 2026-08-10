#include "pch.h"
#include "Renderer.h"
#include "Transform.h"
#include "Model.h"
#include "mathUtil.h"
#include "Texture.h"

#include <iostream>
#include "Input.h"

namespace nu
{
    bool Renderer::Initialize(const char* name, int width, int height)
    {
        m_width = width;
        m_height = height;

        SDL_Init(SDL_INIT_VIDEO);

        if (!TTF_Init()) 
        {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_window = SDL_CreateWindow(name, width, height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        SDL_SetRenderVSync(m_renderer, 1);

        return true;
    }

    void Renderer::Shutdown() const
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Renderer::SetColor(float r, float g, float b, float a) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    void Renderer::Clear() const
    {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::Present() const
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::DrawPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::DrawFillRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void Renderer::DrawRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        SDL_RenderRect(m_renderer, &rect);
    }

    void Renderer::DrawLine(float x, float y, float x2, float y2) const
    {
        SDL_RenderLine(m_renderer, x, y, x2, y2);
    }

    void Renderer::DrawModel(const Model& model, const Transform& transform) const
    {        
        for(auto mesh : model.GetMeshes())
        {
            const Color& color = mesh.GetColor();
            SetColor(color.r, color.g, color.b, 1.0f);

            auto points = mesh.GetPoints();

            for (int i = 0; i < points.size() - 1; i++)
            {
                Vector2 v1 = points[i]; //local space
                Vector2 v2 = points[i + 1]; //local space

                //convert tot world space
                v1 *= transform.scale;
                v2 *= transform.scale;

                v1 = v1.Rotate(transform.rotation * DegToRad);
                v2 = v2.Rotate(transform.rotation * DegToRad);

                v1 += transform.position;
                v2 += transform.position;

                DrawLine(v1.x, v1.y, v2.x, v2.y);
            }
        }
    }

    void Renderer::DrawTexture(const Texture& texture, float x, float y, float angle, float scale, bool flipH) const
    {
        Vector2 size = texture.GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - (0.5 * destRect.w);
        destRect.y = y - (0.5 * destRect.h);
        

        SDL_RenderTextureRotated(m_renderer, texture.m_texture, NULL, &destRect, angle, NULL, (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    void Renderer::SetTextureColor(const Texture& texture, float r, float g, float b, float a) const
    {
        SDL_SetTextureColorModFloat(texture.m_texture, r, g, b);
        SDL_SetTextureAlphaModFloat(texture.m_texture, a);
    }
}