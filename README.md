# ImageLoader
Utilize stb_image and directx 9 & 11 to effortlessly load the image of your choice, made specifically for ImGui!

file    | can add from memory? | description
--------------------- | --- | --------------------------------
**[directx9](imageloaderdx9.h)** | false | load any image you want through file using stb_image
**[directx11](imageloaderdx11.h)** | true | load any image yu want through both file and memory using stb_image

## Usage

```cpp
static Texture t;
static bool result = t.Init("C:\\test.png", pDevice);
if (result)
{
     ImGui::Image(t.GetTexture(), ImVec2(512, 384));
}
```
