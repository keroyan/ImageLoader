#pragma once

// #define STB_IMAGE_IMPLEMENTATION <---- define this if you haven't already!

#include <cstdint>
#include <d3d9.h>
#include <d3dx9tex.h>
#include "stb_image.h"
#include "imgui.h"


class Texture
{
public:
    bool Init(const char* filename, IDirect3DDevice9* pDevice) 
    {
        std::int32_t
            image_width = 0,
            image_height = 0;

        stbi_set_flip_vertically_on_load_thread(false);
        std::uint8_t* image_data = stbi_load(filename, &image_width, &image_height, nullptr, STBI_rgb_alpha);
        if (!image_data)
            return false;

        IDirect3DTexture9* temp_texture;
        if (pDevice->CreateTexture(image_width, image_height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &temp_texture, nullptr) != D3D_OK)
        {
            temp_texture->Release();
            stbi_image_free(image_data);
            return false;
        }

        D3DLOCKED_RECT locked_rect;
        if (temp_texture->LockRect(0, &locked_rect, nullptr, D3DLOCK_DISCARD) != D3D_OK)
        {
            temp_texture->Release();
            stbi_image_free(image_data);
            return false;
        }

        for (int y = 0; y < image_height; ++y)
        {
            const auto src = reinterpret_cast<const std::uint32_t*>(image_data + image_width * 4 * y);
            const auto dest = reinterpret_cast<std::uint32_t*>((unsigned char*)locked_rect.pBits + locked_rect.Pitch * y);

            for (int i = 0; i < image_width; ++i)
            {
                auto color = src[i];
                color = (color & 0xFF00FF00) | ((color & 0xFF0000) >> 16) | ((color & 0xFF) << 16);
                dest[i] = color;
            }
        }

        temp_texture->UnlockRect(0);

        IDirect3DTexture9* texture;
        if (pDevice->CreateTexture(image_width, image_height, 1, D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture, nullptr) != D3D_OK)
        {
            temp_texture->Release();
            stbi_image_free(image_data);
            return false;
        }

        pDevice->UpdateTexture(temp_texture, texture);
        temp_texture->Release();

        this->texture = texture;
        return true;
    }

    void Destroy()
    {
        reinterpret_cast<IDirect3DTexture9*>(texture)->Release();
        texture = nullptr;
    }

    ImTextureID GetTexture()
    {
        return texture;
    }

private:
    void* texture;
};
