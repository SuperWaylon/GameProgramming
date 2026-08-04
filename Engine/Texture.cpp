#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

#include <SDL3_image/SDL_image.h>
#include <iostream>

using namespace nu;

Texture::~Texture()
{
    // if texture exists, destroy texture
    if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
}

bool Texture::Load(const std::string& filename, Renderer& renderer)
{
    // load image onto surface
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        std::cerr << "Could not load image: " << filename << std::endl;
        return false;
    }

    // create texture from surface, texture is a friend class of renderer
    m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
    // once texture is created, surface can be freed up
    SDL_DestroySurface(surface);
    if (m_texture == nullptr)
    {
        std::cerr << "Could not create texture: " << filename << std::endl;
        return false;
    }

    return true;
}

Vector2 Texture::GetSize()
{
    Vector2 v;
    SDL_GetTextureSize(m_texture, &v.x, &v.y);
    return v;
}