#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>    // Untuk system()
#include <functional>
#include <limits>

using namespace std;

// Ukuran layar (jumlah baris dan kolom)
const int tinggi_layar = 40;
const int lebar_layar  = 80;

// Fungsi untuk membersihkan layar (clear screen)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    // Daftar fungsi matematika yang akan diplot beserta legend-nya.
    // Setiap fungsi menerima x (double) dan menghasilkan y (double).
    vector<function<double(double)>> functions;
    vector<string> legends;

    // Fungsi 0: y = x^2
    functions.push_back([](double x) {
        return x * x;
    });
    legends.push_back("y = x^2");

    // Fungsi 1: y = x^3
    functions.push_back([](double x) {
        return x * x * x;
    });
    legends.push_back("y = x^3");

    // Fungsi 2: y = 5*sin(x)
    functions.push_back([](double x) {
        return 5 * sin(x);
    });
    legends.push_back("y = 5*sin(x)");

    // Fungsi 3: y = 5*cos(x)
    functions.push_back([](double x) {
        return 5 * cos(x);
    });
    legends.push_back("y = 5*cos(x)");

    int currentFunctionIndex = 0;

    // Faktor skala untuk konversi koordinat dunia ke layar
    double skala_x = 1.0;  // Satuan: "pixel" per unit x
    double skala_y = 1.0;  // Satuan: "baris" per unit y

    char choice;
    do {
        // Bersihkan layar
        clearScreen();

        // Inisialisasi array 2D layar dengan spasi
        vector<vector<char>> layar(tinggi_layar, vector<char>(lebar_layar, ' '));

        // Titik tengah layar (origin) untuk sumbu:
        int origin_x = lebar_layar / 2;
        int origin_y = tinggi_layar / 2;

        // Gambar sumbu horizontal (x) dengan karakter '-' dan sumbu vertikal (y) dengan '|'
        for (int j = 0; j < lebar_layar; j++) {
            layar[origin_y][j] = '-';
        }
        for (int i = 0; i < tinggi_layar; i++) {
            layar[i][origin_x] = '|';
        }
        // Titik origin (persimpangan sumbu)
        layar[origin_y][origin_x] = '+';

        // Ambil fungsi yang aktif
        auto f = functions[currentFunctionIndex];

        // Untuk setiap kolom layar, hitung x dunia dan y hasil fungsi
        for (int j = 0; j < lebar_layar; j++) {
            // Ubah kolom ke koordinat x: x = (j - origin_x) / skala_x
            double x = (j - origin_x) / skala_x;
            double y_val = f(x);
            // Konversi y ke indeks layar:
            // karena layar[0] berada di atas, baris dihitung dari atas
            int i = origin_y - static_cast<int>(round(y_val * skala_y));
            if (i >= 0 && i < tinggi_layar) {
                layar[i][j] = '*';
            }
        }

        // Tampilkan legend di atas grafik
        cout << "Fungsi Aktif: " << legends[currentFunctionIndex] << endl;
        cout << "Tekan F untuk ganti fungsi, Q untuk keluar." << endl << endl;

        // Tampilkan layar (grafik) baris per baris
        for (int i = 0; i < tinggi_layar; i++) {
            for (int j = 0; j < lebar_layar; j++) {
                cout << layar[i][j];
            }
            cout << endl;
        }

        // Minta input dari pengguna (baca satu karakter)
        cout << endl << "Pilihan Anda: ";
        cin >> choice;
        // Abaikan sisa input (agar input selanjutnya bersih)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Jika pengguna menekan 'F' atau 'f', ganti fungsi
        if (choice == 'f' || choice == 'F') {
            currentFunctionIndex = (currentFunctionIndex + 1) % functions.size();
        }

    } while (choice != 'q' && choice != 'Q');

    return 0;
}
