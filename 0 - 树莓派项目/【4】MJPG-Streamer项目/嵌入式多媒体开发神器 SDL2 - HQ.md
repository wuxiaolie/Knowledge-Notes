# 嵌入式多媒体开发神器 SDL2 - HQ

[TOC]

------

#### 注意

- 

------

## 强大无比的嵌入式多媒体开发神器：SDL2

### SDL 是什么？

==SDL（Simple DirectMedia Layer）是一套开源的跨平台多媒体开发库，使用 C 语言写成。==

它提供了绘制图像、播放声音、获取键盘输入等相关的 API，大大降低多媒体应用开发难度的同时，也让开发者只要用相同或是相似的代码就可以开发出跨多个平台（Linux、Windows、Mac OS X等）的应用软件。

多用于开发游戏、模拟器、媒体播放器等多媒体应用领域。

SDL 有两个常见版本：SDL1.2 和 SDL2.x。在不支持 OpenGL ES2 的嵌入式平台上，只能使用 SDL1.2，SDL2.x 依赖 OpengGL ES2。

**官网**：

> https://sourceforge.net/projects/mjpg-streamer/

**Github**：

> https://github.com/libsdl-org/SDL



### 示例：显示图片

```c
 void main()
 {
    SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    
    /* Create a Render */
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    /* Load bitmap image */
    SDL_Surface *bmp = SDL_LoadBMP("./hello.bmp");
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, bmp);
    SDL_FreeSurface(bmp);

    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL); // Copy the texture into render
    SDL_RenderPresent(render); // Show render on window

    /* Free all objects*/
    [...]

    /* Quit program */
    SDL_Quit();
    return 0;
}
```

**要快速上手 SDL，需要理解下面几个核心结构体和 API：**

对于这些结构体，网上有各种各样的解释，但是都比较晦涩生硬，下面是我理解。

**SDL_Window**

想要显示东西，首先要有一个容器来容纳程序绘制的内容。

这个容器，最常见的就是窗口。

对于 PC 机，一般都会有窗口的支持。

但是即便是没有桌面环境的嵌入式平台，SDL_Window 也能兼容，只不过这个窗口没有最小化、最大化、拉伸的功能罢了，都是纯软件的概念，和硬件无关。

一般只需要关注 x、y、w、h 4个成员变量，即窗口的原点坐标和宽高。

通过 SDL_CreateWindow() 可以创建一个窗口。

**SDL_Renderer**

当描述用 GPU 来进行绘画图像时，就用术语渲染。

渲染器，你可以认为就是画笔。

现实世界里，你可以用圆珠笔来画画，也可以用铅笔来画画，所以渲染器也有多种类型，不同的渲染器就好比不同的笔。

SDL2 支持的渲染器：

> <img src="assets/640-16501670112644.png" alt="图片" style="zoom:50%;" />

==在嵌入式平台上，一般就只支持 OpengGL ES2 这种渲染器类型。==

通过 SDL_CreateRenderer() 可以创建一个渲染器。

**SDL_Texture**

渲染器有了之后，就轮到要渲染的内容了。

Texture 负责描述渲染的内容。

既然是要显示图像，自然需要像素数据、像素格式、宽度、高度、渲染器类型等信息，这些都包含在 Texture 里。

最常见的情况：
调用SDL_CreateTextureFromSurface() 基于某个 Surface 来创建 Texture。Surface 用于描述像素数据。

**SDL_RenderCopy()/SDL_RenderPresent()**

我们把内存想象成是一块备用的画布，而此时屏幕正在显示另一块画布的内容。

你可以不断地调用 SDL_RenderCopy() 来往备用画布上画东西，无论你画多少次都可以。

只有当你调用 SDL_RenderPresent() 时，备用画布才会真正第切换到屏幕上。



###  实践应用

MJPG-Streamer 将每一种输入或输出是都抽象为一个插件。

例如采集摄像头的功能被实现为一个输入插件， 而 http 视频流被实现为一个输出插件。

==我们可以为 MJPG-Streamer 添加一个 SDL2 输出插件。==

==这样就可以在本地显示屏上查看到浏览器的图像了==，效果如下：

```
$ ./mjpg_streamer -i "input_uvc.so /dev/video0 -r 640x480 -f 30" -o "output_sdl2.so"
```

代码很简单，核心内容就是使用 SDL2 显示 JPG 图片，代码就不贴了。



###  内部实现

最后，我想简单地看一下 SDL2 的内部实现。

以最重要的显示功能为例。

SDL2 将底层显示封装为 video driver：

> <img src="assets/640-16501670112656.png" alt="图片" style="zoom:50%;" />

我们比较熟悉的包括：Wayland、X11、KMSDRM。

以 KMSDRM 这个 video driver 为例，为了支持这个显示驱动，需要实现这么多 API：

> <img src="assets/640-16501670112657.png" alt="图片" style="zoom:50%;" />

如果你想了解 SDL2 是如何实现屏幕显示的，可以尝试阅读这些 API。

### 总结

SDL2 的功能非常丰富，代码质量也很高。

==如果你想在板子进行多媒体开发，例如显示一些东西，又不想用 Qt 那么庞大的图形框架，可以考虑基于 SDL2 进行开发。==

















































































































































































































