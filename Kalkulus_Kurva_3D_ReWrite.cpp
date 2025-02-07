#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#include <string>

// Ukuran window global
int windowWidth = 800, windowHeight = 600;

// Struktur warna sederhana
struct Color {
    float r, g, b;
};

// Jumlah fungsi yang tersedia
const int NUM_FUNCTIONS = 4;

// Teks legend untuk masing–masing fungsi (legend hanya ditampilkan di console)
const char* functionLegends[NUM_FUNCTIONS] = {
    "z = sin(x) * cos(y)",
    "z = cos(x) * sin(y)",
    "z = sin(x) * sin(y)",
    "z = cos(x) * cos(y)"
};

// Daftar preset warna yang akan dipakai (preset sebanyak 6)
const int NUM_PRESETS = 6;
Color presets[NUM_PRESETS] = {
    {0.5f, 0.5f, 1.0f},  // kebiruan
    {0.5f, 1.0f, 0.5f},  // kehijauan
    {1.0f, 0.5f, 0.5f},  // kemerahan
    {1.0f, 1.0f, 0.5f},  // kekuningan
    {1.0f, 0.5f, 1.0f},  // ungu muda
    {0.5f, 1.0f, 1.0f}   // kebiruan muda
};

// Untuk setiap fungsi, simpan preset warna yang sedang aktif
Color functionColors[NUM_FUNCTIONS];
int currentColorPreset[NUM_FUNCTIONS];

// Variabel global untuk rotasi, zoom, dan inersia
float rotateX = 20.0f, rotateY = -30.0f;
float zoom = -15.0f; // Kamera dijauhkan agar tampilan dari x,y = -5 s/d 5 utuh
bool mouseDown = false;
float spinX = 0.0f, spinY = 0.0f;

// Variabel global untuk pergantian fungsi
int currentFunctionIndex = 0;

// Fungsi untuk menghitung nilai z berdasarkan fungsi yang aktif
// Fungsi yang tersedia:
//   0: z = sin(x) * cos(y)
//   1: z = cos(x) * sin(y)
//   2: z = sin(x) * sin(y)
//   3: z = cos(x) * cos(y)
float computeFunction(float x, float y) {
    switch (currentFunctionIndex) {
        case 0:
            return sinf(x) * cosf(y);
        case 1:
            return cosf(x) * sinf(y);
        case 2:
            return sinf(x) * sinf(y);
        case 3:
            return cosf(x) * cosf(y);
        default:
            return sinf(x) * cosf(y);
    }
}

// Fungsi untuk menggambar permukaan fungsi sebagai kuadrat berisi warna
void drawFunction() {
    const float step = 0.1f;
    glBegin(GL_QUADS);
    for (float x = -5.0f; x <= 5.0f; x += step) {
        for (float y = -5.0f; y <= 5.0f; y += step) {
            // Hitung nilai z untuk tiap titik
            float z  = computeFunction(x, y);
            float z1 = computeFunction(x + step, y);
            float z2 = computeFunction(x, y + step);
            float z3 = computeFunction(x + step, y + step);

            // Ambil preset warna untuk fungsi yang aktif
            Color col = functionColors[currentFunctionIndex];
            float factor;

            // Vertex pertama
            factor = (z + 1.0f) / 2.0f;
            glColor3f(factor * col.r, factor * col.g, factor * col.b);
            glVertex3f(x, y, z);

            // Vertex kedua
            factor = (z1 + 1.0f) / 2.0f;
            glColor3f(factor * col.r, factor * col.g, factor * col.b);
            glVertex3f(x + step, y, z1);

            // Vertex ketiga
            factor = (z3 + 1.0f) / 2.0f;
            glColor3f(factor * col.r, factor * col.g, factor * col.b);
            glVertex3f(x + step, y + step, z3);

            // Vertex keempat
            factor = (z2 + 1.0f) / 2.0f;
            glColor3f(factor * col.r, factor * col.g, factor * col.b);
            glVertex3f(x, y + step, z2);
        }
    }
    glEnd();
}

// Fungsi untuk menggambar wireframe (garis tepi) dari permukaan fungsi
void drawFunctionWireframe() {
    const float step = 0.1f;
    glLineWidth(1.0f);
    // Untuk wireframe, gunakan warna hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    for (float x = -5.0f; x <= 5.0f; x += step) {
        for (float y = -5.0f; y <= 5.0f; y += step) {
            float z  = computeFunction(x, y);
            float z1 = computeFunction(x + step, y);
            float z2 = computeFunction(x, y + step);
            float z3 = computeFunction(x + step, y + step);
            glBegin(GL_LINE_LOOP);
                glVertex3f(x, y, z);
                glVertex3f(x + step, y, z1);
                glVertex3f(x + step, y + step, z3);
                glVertex3f(x, y + step, z2);
            glEnd();
        }
    }
}

// Fungsi untuk menggambar sumbu X, Y, dan Z lengkap dengan tick mark
void drawAxes() {
    // Nonaktifkan pencahayaan dan depth-test agar sumbu selalu terlihat
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Sumbu X (merah)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-5.0f, 0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);

        // Sumbu Y (hijau)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -5.0f, 0.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);

        // Sumbu Z (biru)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -5.0f);
        glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();

    // Gambar tick mark dengan jarak 1 satuan
    float tickSize = 0.1f;

    // Tick pada sumbu X (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = -5; i <= 5; i++) {
        if (i == 0) continue;
        glBegin(GL_LINES);
            glVertex3f(i, -tickSize, 0.0f);
            glVertex3f(i, tickSize, 0.0f);
        glEnd();
    }

    // Tick pada sumbu Y (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = -5; i <= 5; i++) {
        if (i == 0) continue;
        glBegin(GL_LINES);
            glVertex3f(-tickSize, i, 0.0f);
            glVertex3f(tickSize, i, 0.0f);
        glEnd();
    }

    // Tick pada sumbu Z (biru)
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int i = -5; i <= 5; i++) {
        if (i == 0) continue;
        glBegin(GL_LINES);
            glVertex3f(0.0f, -tickSize, i);
            glVertex3f(0.0f, tickSize, i);
        glEnd();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Fungsi untuk menangani input dari keyboard dan mouse
void handleInput(SDL_Event &event, bool &running) {
    if (event.type == SDL_QUIT) {
        running = false;
    }
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_w:  // Zoom in (mendekatkan kamera)
                zoom += 0.5f;
                break;
            case SDLK_s:  // Zoom out (menjauhkan kamera)
                zoom -= 0.5f;
                break;
            // Rotasi: A / Left untuk rotasi ke kiri (sumbu X)
            case SDLK_a:
            case SDLK_LEFT:
                rotateX -= 5.0f;
                break;
            // Rotasi: D / Right untuk rotasi ke kanan (sumbu X)
            case SDLK_d:
            case SDLK_RIGHT:
                rotateX += 5.0f;
                break;
            // Rotasi: Up/Down untuk rotasi atas/bawah (sumbu Y)
            case SDLK_UP:
                rotateY += 5.0f;
                break;
            case SDLK_DOWN:
                rotateY -= 5.0f;
                break;
            // Ganti fungsi dengan tombol F dan tampilkan legend di console
            case SDLK_f:
                currentFunctionIndex = (currentFunctionIndex + 1) % NUM_FUNCTIONS;
                std::cout << "Switched to function " << currentFunctionIndex << ": "
                          << functionLegends[currentFunctionIndex] << std::endl;
                break;
            // Ganti preset warna untuk fungsi aktif dengan tombol C
            case SDLK_c:
                currentColorPreset[currentFunctionIndex] = (currentColorPreset[currentFunctionIndex] + 1) % NUM_PRESETS;
                functionColors[currentFunctionIndex] = presets[currentColorPreset[currentFunctionIndex]];
                std::cout << "Changed color preset for function " << currentFunctionIndex
                          << " to preset " << currentColorPreset[currentFunctionIndex] << std::endl;
                break;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouseDown = true;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mouseDown = false;
        }
    }
    else if (event.type == SDL_MOUSEMOTION) {
        if (mouseDown) {
            // Update rotasi dan simpan kecepatan (spin) untuk inersia
            spinX = event.motion.xrel * 0.5f;
            spinY = event.motion.yrel * 0.5f;
            rotateX += spinX;
            rotateY += spinY;
        }
    }
    else if (event.type == SDL_MOUSEWHEEL) {
        // Zoom menggunakan scroll mouse
        if (event.wheel.y > 0) { // scroll ke atas: zoom in
            zoom += 0.5f;
        }
        else if (event.wheel.y < 0) { // scroll ke bawah: zoom out
            zoom -= 0.5f;
        }
    }
}

int main(int argc, char* argv[]) {
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL gagal diinisialisasi: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Buat window dengan dukungan OpenGL
    SDL_Window* window = SDL_CreateWindow("Grafik Fungsi 3D (F: ganti fungsi, C: ganti warna)",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          windowWidth, windowHeight,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Gagal membuat window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Buat konteks OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Gagal membuat OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Inisialisasi preset warna untuk setiap fungsi
    currentColorPreset[0] = 0;
    currentColorPreset[1] = 1;
    currentColorPreset[2] = 2;
    currentColorPreset[3] = 3;
    for (int i = 0; i < NUM_FUNCTIONS; i++) {
        functionColors[i] = presets[currentColorPreset[i]];
    }

    // Konfigurasi OpenGL dasar
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Pengaturan pencahayaan
    GLfloat light_position[] = { 0.0f, 0.0f, 10.0f, 1.0f };
    GLfloat ambientLight[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    // Aktifkan Color Material agar warna dari glColor mempengaruhi material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    // Set viewport dan perspektif
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)windowWidth / windowHeight, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    bool running = true;
    SDL_Event event;
    while (running) {
        // Proses event input
        while (SDL_PollEvent(&event)) {
            handleInput(event, running);
        }

        // Jika mouse tidak ditekan, terapkan inersia (momentum)
        if (!mouseDown) {
            rotateX += spinX;
            rotateY += spinY;
            spinX *= 0.95f;
            spinY *= 0.95f;
        }

        // Bersihkan buffer warna dan depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Atur kamera menggunakan gluLookAt
        gluLookAt(0.0, 0.0, zoom,   // posisi kamera
                  0.0, 0.0, 0.0,    // titik yang dilihat
                  0.0, 1.0, 0.0);   // sumbu atas

        // Terapkan rotasi (pertama sumbu Y, kemudian sumbu X)
        glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
        glRotatef(rotateX, 0.0f, 1.0f, 0.0f);

        // Gambar permukaan fungsi (filled) dengan pencahayaan
        glEnable(GL_LIGHTING);
        drawFunction();

        // Gambar overlay wireframe agar grid terlihat (nonaktifkan pencahayaan sementara)
        glDisable(GL_LIGHTING);
        drawFunctionWireframe();
        glEnable(GL_LIGHTING);

        // Gambar sumbu X, Y, dan Z dengan tick mark
        drawAxes();

        // Legend tidak dirender secara grafis; informasi fungsi aktif tercetak di console.
        SDL_GL_SwapWindow(window);
    }

    // Bersihkan resource SDL dan OpenGL
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
