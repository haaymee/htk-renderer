#include <iostream>
#include <SDL3/SDL.h>
#include <format>
#include <SDL3/SDL_opengl.h>

// Globals
static int gScreenWidth = 640;
static int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = nullptr;
static SDL_GLContext gOpenGLContext = nullptr;
static bool gQuit = false;

void GetOpenGLVersionInfo()
{
    std::cout << std::format("Vendor: {}\nRenderer: {}\nVersion: {}\nShading Language: {}\n",
        glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void InitializeProgram()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << std::format("SDL3 video subsystem unable to initialize: {}\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    gGraphicsApplicationWindow = SDL_CreateWindow("HTK", gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!gGraphicsApplicationWindow)
    {
        std::cerr << std::format("SDL3 Window unable to initialize: {}\n", SDL_GetError());
        exit(1);
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if (!gOpenGLContext)
    {
        std::cerr << std::format("SDL OpenGL Context not available: {}\n", SDL_GetError());
        exit(1);
    } 
}

void Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            std::cout << "Requested to quit application...\n";
            gQuit = true;
        }
    }
}

void PreDraw()
{
    
}

void Draw()
{
    
}

void MainLoop()
{
    while (!gQuit)
    {
        Input();

        PreDraw();

        Draw();

        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

void Cleanup()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}

int main() 
{

    InitializeProgram();
    MainLoop();
    Cleanup();
    
    return 0;
}