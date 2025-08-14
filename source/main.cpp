#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <format>
#include <vector>
#include <chrono>

#include "ShaderStage.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Globals
static int gScreenWidth = 640;
static int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = nullptr;
static SDL_GLContext gOpenGLContext = nullptr;
static bool gQuit = false;

// App Time Variables
auto appStartTime = std::chrono::steady_clock::now();
std::chrono::duration<double> appElapsedTime {};

// Triangle Vars
GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;
GLuint gIndexBufferObject = 0;

// Shader Vars
std::unique_ptr<ShaderProgram> gGraphicsPipelineShaderProgram = nullptr;
glm::vec3 gObjectPosition = glm::vec3(0.0f, 0.0f, -1.f);

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " <<  glGetString(GL_VENDOR) << "\n"; 
    std::cout << "Graphics Card Unit: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
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

    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
    {
        std::cerr << std::format("Failed to initialize GLAD: {}\n", SDL_GetError());
        exit(1);
    }

    GetOpenGLVersionInfo();
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

        if (e.type == SDL_EVENT_KEY_DOWN)
        {
            if (e.key.key == SDLK_UP)
            {
                gObjectPosition.y += 0.05f;
                std::cout << "Up Arrow Key Pressed\n";
            }

            if (e.key.key == SDLK_DOWN)
            {
                gObjectPosition.y -= 0.05f;
                std::cout << "Down Arrow Key Pressed\n";
            }

            if (e.key.key == SDLK_Q)
            {
                gObjectPosition.z -= 0.05f;
                std::cout << "Q Arrow Key Pressed\n";
            }

            if (e.key.key == SDLK_E)
            {
                gObjectPosition.z += 0.05f;
                std::cout << "E Arrow Key Pressed\n";
            }
        }
    }
}

void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram->GetShaderProgramIdHandle());

    gGraphicsPipelineShaderProgram->LinkUniform("u_time", static_cast<GLfloat>(appElapsedTime.count()));

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), gObjectPosition);
    glm::mat4 projectionMat = glm::perspective(glm::radians(45.f), float(gScreenWidth)/float(gScreenHeight), 0.01f, 10.f);

    gGraphicsPipelineShaderProgram->LinkUniform("u_modelMatrix", modelMatrix);
    gGraphicsPipelineShaderProgram->LinkUniform("u_projectionMatrix", projectionMat);
}

void Draw()
{
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MainLoop()
{
    while (!gQuit)
    {
        appElapsedTime = std::chrono::duration<double>(std::chrono::steady_clock::now() - appStartTime);
        
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

void VertexSpecification()
{
    // Raw Vertex Data (Position, Color)
    const std::vector<GLfloat> vertexData {
        -0.5f, -0.5f, 0.0f, // BL Vertex Pos
        1.0f, 0.0f, 0.0f,   // BL Vertex Color
        0.5f, -0.5f, 0.0f,  // BR Vertex Pos
        0.0f, 1.0f, 0.0f,   // BR Vertex Color
        -0.5f, 0.5f, 0.0f,  // TL Vertex Pos
        0.0f, 0.0f, 1.0f,    // TL Vertex Color
        0.5f, 0.5f, 0.0f,  // TR Vertex Pos
        0.0f, 1.0f, 1.0f    // TR Vertex Color
    };

    // Index Drawing Order of Vertices
    const std::vector<GLuint> indexData {0, 1, 2, 1, 3, 2};
    
    // Input Raw Vertex Data into Vertex Buffer
    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    // Interpret data in Vertex Buffer through Vertex Arrays
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    glEnableVertexAttribArray(0); // Enable the Position Data attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)0); // Tell OpenGL that the 0 attribute is position attribute

    glEnableVertexAttribArray(1); // Enable the Color Data attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)(sizeof(GLfloat)*3));

    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexData.size(), indexData.data(), GL_STATIC_DRAW);
    
    // Reset OpenGL State Machine
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CreateShaderProgram(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader)
{
    ShaderStage vertShader {vertexShader, ShaderType::ShaderType_Vertex};
    ShaderStage fragShader {fragmentShader, ShaderType::ShaderType_Fragment};

    vertShader.Compile();
    fragShader.Compile();
    
    gGraphicsPipelineShaderProgram = std::make_unique<ShaderProgram>(vertShader, fragShader);
    gGraphicsPipelineShaderProgram->LinkProgram();
}

int main() 
{
    InitializeProgram();

    VertexSpecification();
    CreateShaderProgram("Source/Shaders/vertex.vert", "Source/Shaders/fragment.frag");
    
    MainLoop();
    Cleanup();
    
    return 0;
}