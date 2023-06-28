# ImageLoaderDX9
A texture loader from file using stb_image for directx9! can be used for ImGui!

## Usage

```cpp
        static Texture t;
        static bool result = t.Init("C:\\test.png", pDevice);
        if (result)
        {
            ImGui::Image(t.GetTexture(), ImVec2(512, 384));
        }
```
