#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct Penduduk {
    string nik;
    string nama;
    string alamat;
    string jenis_kelamin;
};

Penduduk data_penduduk[100];
int jumlah_data = 0;

void loadData() {
    ifstream file("penduduk.dat", ios::binary);
    if (!file) return;
    while (file.read(reinterpret_cast<char*>(&data_penduduk[jumlah_data]), sizeof(Penduduk))) {
        jumlah_data++;
    }
    file.close();
}

void saveData() {
    ofstream file("penduduk.dat", ios::binary | ios::trunc);
    for (int i = 0; i < jumlah_data; i++) {
        file.write(reinterpret_cast<const char*>(&data_penduduk[i]), sizeof(Penduduk));
    }
    file.close();
}

void inputData() {
    if (jumlah_data >= 100) {
        printf("Data penuh!\n");
        return;
    }
    cout << "Masukkan NIK: "; cin >> data_penduduk[jumlah_data].nik;
    cout << "Masukkan Nama: "; cin.ignore(); getline(cin, data_penduduk[jumlah_data].nama);
    cout << "Masukkan Alamat: "; getline(cin, data_penduduk[jumlah_data].alamat);
    cout << "Masukkan Jenis Kelamin: "; getline(cin, data_penduduk[jumlah_data].jenis_kelamin);
    jumlah_data++;
    saveData();
    printf("Data berhasil ditambahkan!\n");
}

void outputData() {
    for (int i = 0; i < jumlah_data - 1; i++) {
        for (int j = i + 1; j < jumlah_data; j++) {
            if (data_penduduk[i].nik > data_penduduk[j].nik) {
                Penduduk temp = data_penduduk[i];
                data_penduduk[i] = data_penduduk[j];
                data_penduduk[j] = temp;
            }
        }
    }
    for (int i = 0; i < jumlah_data; i++) {
        printf("NIK: %s\nNama: %s\nAlamat: %s\nJenis Kelamin: %s\n\n", data_penduduk[i].nik.c_str(), data_penduduk[i].nama.c_str(), data_penduduk[i].alamat.c_str(), data_penduduk[i].jenis_kelamin.c_str());
    }
}

void searchData() {
    string nik;
    cout << "Masukkan NIK yang dicari: "; cin >> nik;
    for (int i = 0; i < jumlah_data; i++) {
        if (data_penduduk[i].nik == nik) {
            printf("NIK: %s\nNama: %s\nAlamat: %s\nJenis Kelamin: %s\n", data_penduduk[i].nik.c_str(), data_penduduk[i].nama.c_str(), data_penduduk[i].alamat.c_str(), data_penduduk[i].jenis_kelamin.c_str());
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void editData() {
    string nik;
    cout << "Masukkan NIK yang ingin diedit: "; cin >> nik;
    for (int i = 0; i < jumlah_data; i++) {
        if (data_penduduk[i].nik == nik) {
            cout << "Masukkan Alamat baru: "; cin.ignore(); getline(cin, data_penduduk[i].alamat);
            saveData();
            printf("Data berhasil diperbarui!\n");
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void deleteData() {
    string nik;
    cout << "Masukkan NIK yang ingin dihapus: "; cin >> nik;
    for (int i = 0; i < jumlah_data; i++) {
        if (data_penduduk[i].nik == nik) {
            for (int j = i; j < jumlah_data - 1; j++) {
                data_penduduk[j] = data_penduduk[j + 1];
            }
            jumlah_data--;
            saveData();
            printf("Data berhasil dihapus!\n");
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

int main() {
    loadData();
    int pilihan;
    do {
        printf("\n1. Input Data\n2. Tampilkan Data\n3. Cari Data\n4. Edit Data\n5. Hapus Data\n6. Keluar\nPilih: ");
        cin >> pilihan;
        switch (pilihan) {
            case 1: inputData(); break;
            case 2: outputData(); break;
            case 3: searchData(); break;
            case 4: editData(); break;
            case 5: deleteData(); break;
        }
    } while (pilihan != 6);
    return 0;
}
