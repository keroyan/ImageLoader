# ImageLoader
Utilize stb_image and directx 9 & 11 to effortlessly load the image of your choice, made specifically for ImGui!

file    | support | description
--------------------- | --- | --------------------------------
**[ImageLoaderDX9.h](imageloaderdx9.h)** | file | load any image you want through file using stb_image
**[ImageLoaderDX11.h](imageloaderdx11.h)** | file, memory | load any image you want through both file and memory using stb_image

## Usage

### DX9

```cpp
static Texture t(pDevice);
static bool result = t.LoadTextureFromFile("C:\\test.png");
if (result)
{
     ImGui::Image(t.GetTexture(), ImVec2(512, 384));
}
```

### DX11

From Memory
```cpp
static Texture logo(pDevice);
static bool logo_result = logo.LoadTextureFromMemory(logo_bytes, logo_bytes_size);
if (logo_result)
{
     ImGui::Image(logo.GetTexture(), ImVec2(64, 64));
     // Note: You can get the actual size of the image using logo.GetWidth() and Logo.GetHeight()
}
```

From File
```cpp
static Texture logo(pDevice);
static bool logo_result = logo.LoadTextureFromFile("test.png");
if (logo_result)
{
     ImGui::Image(logo.GetTexture(), ImVec2(64, 64));
     // Note: You can get the actual size of the image using logo.GetWidth() and Logo.GetHeight()
}
```
