#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Ukuran layar dalam karakter
    const int lebar_layar = 40;
    const int tinggi_layar = 20;
    // Skala untuk mengatur jarak antar titik pada sumbu x dan y
    const int skala_x = 2;
    const int skala_y = 1;

    // Inisialisasi layar dengan spasi
    char layar[tinggi_layar][lebar_layar];
    for (int i = 0; i < tinggi_layar; ++i) {
        for (int j = 0; j < lebar_layar; ++j) {
            layar[i][j] = ' ';
        }
    }

    // Menggambar kurva y = x^2
    // Rentang x yang digunakan agar grafik berada di tengah layar
    int rentang_x = lebar_layar / (2 * skala_x);
    for (int x = -rentang_x; x <= rentang_x; ++x) {
        // Hitung nilai y dari fungsi
        int y = x * x;

        // Hitung posisi layar: offset agar grafik berada di tengah
        int posisi_x = x * skala_x + lebar_layar / 2;
        // Koordinat layar: baris 0 berada di atas, sehingga dikurangkan dari tinggi layar/2
        int posisi_y = tinggi_layar / 2 - y / skala_y;

        // Pastikan posisi masih berada dalam batas layar
        if (posisi_x >= 0 && posisi_x < lebar_layar &&
            posisi_y >= 0 && posisi_y < tinggi_layar) {
            layar[posisi_y][posisi_x] = '*';
            }
    }

    // Menampilkan layar
    for (int i = 0; i < tinggi_layar; ++i) {
        for (int j = 0; j < lebar_layar; ++j) {
            cout << layar[i][j];
        }
        cout << endl;
    }

    // Menunggu input agar jendela konsol tidak langsung tertutup
    cout << "\nTekan Enter untuk keluar..." << endl;
    cin.get();
    return 0;
}
