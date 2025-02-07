cmake_minimum_required(VERSION 3.16)

#Jangan lupa di samakan sama nama folder nya ya
project(Kalkulus_TugasAkhir_Kelompok)

set(CMAKE_CXX_STANDARD 17)

# Link Library SDL2 anda ke Direktori nya
include_directories("C:/SDL2/include")
link_directories("C:/SDL2/lib")

add_executable(Kalkulus_TugasAkhir_Kelompok Kalkulus_Kurva_2D_ReWrite.cpp)
# Misal ingin menjalankan Kalkulus_Kurva_2D.cpp maka Konfigurasi add_executeable nya :
# add_executable(Kalkulus_TugasAkhir_Kelompok Kalkulus_Kurva_2D.cpp)

target_link_libraries(Kalkulus_TugasAkhir_Kelompok SDL2 SDL2main opengl32 glu32)
