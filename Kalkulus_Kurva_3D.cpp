#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

float rotateX = 0.0f, rotateY = 0.0f;
float zoom = -10.0f;

// Fungsi matematika
float function(float x, float y) {
    return sin(x) * cos(y);
}

void drawFunction() {
    float step = 0.1f;
    glBegin(GL_QUADS);
    for (float x = -5.0f; x <= 5.0f; x += step) {
        for (float y = -5.0f; y <= 5.0f; y += step) {
            float z = function(x, y);
            float z1 = function(x + step, y);
            float z2 = function(x, y + step);
            float z3 = function(x + step, y + step);

            glColor3f((z + 1) / 2, (z + 1) / 2, 1.0f); // Pewarnaan berdasarkan nilai z
            glVertex3f(x, y, z);
            glColor3f((z1 + 1) / 2, (z1 + 1) / 2, 1.0f);
            glVertex3f(x + step, y, z1);
            glColor3f((z3 + 1) / 2, (z3 + 1) / 2, 1.0f);
            glVertex3f(x + step, y + step, z3);
            glColor3f((z2 + 1) / 2, (z2 + 1) / 2, 1.0f);
            glVertex3f(x, y + step, z2);
        }
    }
    glEnd();
}


void handleInput(SDL_Event& event, bool& running) {
    if (event.type == SDL_QUIT) {
        running = false;
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_w:
                zoom += 0.5f;
                break;
            case SDLK_s:
                zoom -= 0.5f;
                break;
            case SDLK_LEFT:
                rotateY -= 5.0f;
                break;
            case SDLK_RIGHT:
                rotateY += 5.0f;
                break;
            case SDLK_UP:
                rotateX += 5.0f;
            break;
            case SDLK_DOWN:
                rotateX -= 5.0f;
            break;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            rotateX += event.motion.yrel * 0.5f;
            rotateY += event.motion.xrel * 0.5f;
        }
    }
}


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("3D Function Graph",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // Pengaturan pencahayaan dan kedalaman
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 0.0f, 0.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            handleInput(event, running);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
        drawFunction();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// Definisi WinMain untuk mengatasi masalah undefined reference
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main(__argc, __argv);
}
