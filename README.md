# Cara Build dan Menjalankan

## Langkah-langkah Build
1. **Buka Command Palette di Visual Studio Code**  
   Tekan `Ctrl + Shift + P`.

2. **Build Proyek**  
   Ketik `CMake: Build` lalu tekan Enter.  
   *CMake akan membuild program (.exe) dari kode dan library yang digunakan.*

3. **Cek Hasil Build**  
   - Buka folder `build` dan periksa apakah sudah ada file `.exe`.
   - Jika belum, periksa konfigurasi di file `CMakeLists.txt` (misalnya, link library ke SDL2 dan lain-lain).

> **Catatan:** Pastikan semua setup sudah benar agar build berjalan lancar!

---

# Setup Compiler, Builder, dan Library

## 1. Compiler
- **Nama:** mingw64  
- **Versi:** 14.2.0 64 bit  
  *(Latest/Terbaru per 2 Februari 2025)*  
- **Detail:**  
  gcc (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0
- **Cara Pasang:**
  1. Download dan extract arsip.
  2. Di dalamnya terdapat folder `mingw64`.  
  3. Copy folder `mingw64` ke `C:\`.
  4. Buka *Environment Variables* (System Variables) dan tambahkan path:
     ```
     C:\mingw64\bin
     ```
  5. Selesai.
- **Cek Versi:**  
  Buka command prompt dan ketik:
  ```bash
  gcc --version
  ```
- **Download:**  
  [Download mingw64 versi 14.2.0](https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.zip)

## 2. Builder: CMake
- **Cara Pasang:**
  - Install extension **CMake** di Visual Studio Code.
  - Download CMake dari: [https://cmake.org/download/](https://cmake.org/download/)

## 3. Library

### SDL2 (Simple DirectMedia Layer 2)
- **Cara Pasang:**
  1. Download dan extract arsip.
  2. Pindahkan folder hasil extract ke `C:\` dan ganti nama folder menjadi **SDL2**.
  3. Edit *Environment Variables* (System Variables) dan tambahkan path:
     - `C:\SDL2\bin`
     - `C:\SDL2\include`
     - `C:\SDL2\lib`
  4. Pastikan struktur folder seperti berikut:
     ```
     C:\SDL2\
         bin\
         include\
         lib\
         share\
     ```
- **Download:**  
  [Download SDL2-devel-2.30.11-mingw.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.30.11/SDL2-devel-2.30.11-mingw.zip)

### OpenGL dengan FreeGLUT
- **Cara Pasang:**
  1. Download dan extract arsip FreeGLUT.
  2. Di dalamnya terdapat folder `freeglut`.  
  3. Pindahkan folder tersebut ke `C:\` dan ganti nama menjadi **FreeGLUT**.
  4. Edit *Environment Variables* (System Variables) dan tambahkan path:
     - `C:\FreeGLUT\bin`
- **Download:**  
  [Download FreeGLUT-devel (MinGW)](https://www.transmissionzero.co.uk/software/freeglut-devel/)  
  *Pastikan memilih versi untuk MinGW.*

---

## Selamat Mencoba!


