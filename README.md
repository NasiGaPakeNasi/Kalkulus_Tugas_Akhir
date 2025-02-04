Cara Build dan Menjalankan : 
1. ctrl + shift + p (Visual Studio Code, Command Pallete)
2. ketik CMake:Build (CMake akan membuild program (.exe) dari kode dan library kita)
3. cek di folder build apakah sudah ada hasil .exe nya atau tidak jika belum cek apakah ada yang salah pada konfigurasi CMakelists.txt apakah ada yang salah pada lik library ke SDL2 nya? dll

Setup Compiler, Builder, Library yang di pakai :
1. Compiler : 
- mingw64 versi 14.2.0 64 bit (Latest/Terbaru saat 2/2/2025)
gcc (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0 
cara pasang : download > extract > di dalam nya ada folder mingw64 > copy ke C:\ > edit environment variable bagian system variable > add > **C:\mingw64\bin** > selesai
*ini kalau mau compiler baru aja ya, mau pakai yang lama juga boleh, cara cek versi di cmd : gcc --version
download : https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.zip

2. Builder : 
- CMake (install cmake di extension Visual Studio Code) dan ini https://cmake.org/download/
  
3. Library : 
- SDL2 (Simple DirectMedia Layer 2) :
cara pasang : download > extract > cut ke C:\ > rename folder nya SDL2 > edit environment variable bagian system variable > add > **c:\SDL2\bin** > add lagi > **c:\SDL2\include** > add lagi > **c:\SDL2\lib** > selesai
pastikan sudah begini C:\SDL2\bin (di folder SDL 2 ada bin, include, lib, share)
download : https://github.com/libsdl-org/SDL/releases/download/release-2.30.11/SDL2-devel-2.30.11-mingw.zip

- OpenGL (Open Graphics Library) pakai FreeGLUT :
cara pasang : download > extract > di dalam nya ada folder freeglut cut ke C:\ > rename jadi FreeGLUT > edit environment variable bagian system variable > add > **c:\freeglut\bin** > selesai
download : https://www.transmissionzero.co.uk/software/freeglut-devel/ (Download yang MinGW karena kita pakai Compiler MinGW)

Selamat Mencoba!
