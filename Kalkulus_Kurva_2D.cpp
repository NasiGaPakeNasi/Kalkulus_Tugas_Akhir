#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int lebar_layar = 40; // Lebar layar dalam karakter
    const int tinggi_layar = 20; // Tinggi layar dalam karakter
    const int skala_x = 2; // Skala untuk sumbu x
    const int skala_y = 1; // Skala untuk sumbu y

    char layar[tinggi_layar][lebar_layar];

    // Inisialisasi layar dengan spasi
    for (int i = 0; i < tinggi_layar; ++i) {
        for (int j = 0; j < lebar_layar; ++j) {
            layar[i][j] = ' ';
        }
    }

    // Hitung nilai y untuk setiap x dan tandai pada layar
    for (int x = -lebar_layar / 2 / skala_x; x <= lebar_layar / 2 / skala_x; ++x) {
        int y = x * x; // Fungsi kuadrat
        int posisi_x = x * skala_x + lebar_layar / 2;
        int posisi_y = tinggi_layar / 2 - y / skala_y;

        // Pastikan posisi tidak keluar dari batas layar
        if (posisi_x >= 0 && posisi_x < lebar_layar && posisi_y >= 0 && posisi_y < tinggi_layar) {
            layar[posisi_y][posisi_x] = '*';
        }
    }

    // Tampilkan layar
    for (int i = 0; i < tinggi_layar; ++i) {
        for (int j = 0; j < lebar_layar; ++j) {
            cout << layar[i][j];
        }
        cout << endl;
    }

    return 0;
}