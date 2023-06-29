#pragma once
#include <cstdint>
#include <d3d11.h>
#include "stb_image.h"

class Texture {
  public: Texture(ID3D11Device * pDevice) 
  {
    this->pDevice = pDevice;
  }

  bool LoadTextureFromFile(const char * filename) 
  {
    std::uint8_t * image_data = stbi_load(filename, & image_width, & image_height, NULL, 4);
    return LoadTexture(image_data);
  }

  bool LoadTextureFromMemory(const std::uint8_t * image_buffer, int buffer_size) 
  {
    std::uint8_t * image_data = stbi_load_from_memory(image_buffer, buffer_size, & image_width, & image_height, NULL, 4);
    return LoadTexture(image_data);
  }

  // Load texture with the image data that you have, or use LoadTextureFromFile or LoadTextureFromMemory
  bool LoadTexture(std::uint8_t * image_data) 
  {
    if (!image_data)
      return false;

    LoadTextureDX11(image_data);
    stbi_image_free(image_data);
    return true;
  }

  ImTextureID GetTexture() 
  {
    return (void*) texture;
  }

  // Gets you the original width of the image!
  std::int32_t GetWidth() 
  {
    return image_width;
  }

  // Gets you the original height of the image!
  std::int32_t GetHeight() 
  {
    return image_height;
  }

  private:
    void LoadTextureDX11(std::uint8_t * image_data) 
    {
      D3D11_TEXTURE2D_DESC desc;
      ZeroMemory( & desc, sizeof(desc));
      desc.Width = image_width;
      desc.Height = image_height;
      desc.MipLevels = 1;
      desc.ArraySize = 1;
      desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      desc.SampleDesc.Count = 1;
      desc.Usage = D3D11_USAGE_DEFAULT;
      desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      desc.CPUAccessFlags = 0;

      ID3D11Texture2D * pTexture = NULL;
      D3D11_SUBRESOURCE_DATA subResource;
      subResource.pSysMem = image_data;
      subResource.SysMemPitch = desc.Width * 4;
      subResource.SysMemSlicePitch = 0;
      pDevice -> CreateTexture2D( & desc, & subResource, & pTexture);

      // Create texture view
      D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
      ZeroMemory( & srvDesc, sizeof(srvDesc));
      srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
      srvDesc.Texture2D.MipLevels = desc.MipLevels;
      srvDesc.Texture2D.MostDetailedMip = 0;
      pDevice -> CreateShaderResourceView(pTexture, & srvDesc, & texture);
      pTexture -> Release();
    }

    std::int32_t image_width = 0;
    std::int32_t image_height = 0;
    ID3D11ShaderResourceView * texture = NULL;
    ID3D11Device * pDevice = nullptr;
};
