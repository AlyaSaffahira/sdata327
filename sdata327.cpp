#include <iostream>
#include <fstream>

using namespace std;

struct KTP {
    string nik;
    string nama;
    string tempatLahir;
    string tanggalLahir;
    string jenisKelamin;
    string alamat;
    string agama;
    string statusPerkawinan;
    string pekerjaan;
    string kewarganegaraan;
};

struct Item {
    string kodeItem;
    string tanggalMasuk;
    bool terjual;
    Item* next;
};

struct Pembeli {
    string ktp;
    string waktuKedatangan;
    string kodeItem;
    Pembeli* next;
};

class Stack {
private:
    Item* top;
    int size;

public:
    Stack() {
        top = NULL;
        size = 0;
    }

    void push(string kodeItem, string tanggalMasuk) {
        Item* newItem = new Item;
        newItem->kodeItem = kodeItem;
        newItem->tanggalMasuk = tanggalMasuk;
        newItem->terjual = false;
        newItem->next = top;
        top = newItem;
        size++;
    }

    bool pop(Item& item) {
        if (isEmpty()) return false;

        item = *top;
        Item* temp = top;
        top = top->next;
        delete temp;
        size--;
        return true;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void display() {
        Item* current = top;
        cout << "\nDaftar Barang dalam Gudang:\n";
        cout << "Kode Item\tTanggal Masuk\n";
        cout << "--------------------------------\n";
        while (current != NULL) {
            cout << current->kodeItem << "\t\t" << current->tanggalMasuk << "\n";
            current = current->next;
        }
    }
};

class Queue {
private:
    Pembeli *front, *rear;
    int size;

public:
    Queue() {
        front = rear = NULL;
        size = 0;
    }

    void enqueue(string ktp, string waktuKedatangan, string kodeItem) {
        Pembeli* newPembeli = new Pembeli;
        newPembeli->ktp = ktp;
        newPembeli->waktuKedatangan = waktuKedatangan;
        newPembeli->kodeItem = kodeItem;
        newPembeli->next = NULL;

        if (isEmpty()) {
            front = rear = newPembeli;
        } else {
            rear->next = newPembeli;
            rear = newPembeli;
        }
        size++;
    }

    bool dequeue(Pembeli& pembeli) {
        if (isEmpty()) return false;

        pembeli = *front;
        Pembeli* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        size--;
        return true;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void display() {
        Pembeli* current = front;
        cout << "\nDaftar Antrian Pembeli:\n";
        cout << "KTP\t\tWaktu Kedatangan\tKode Item\n";
        cout << "----------------------------------------\n";
        while (current != NULL) {
            cout << current->ktp << "\t" << current->waktuKedatangan << "\t\t" 
                 << current->kodeItem << "\n";
            current = current->next;
        }
    }
};

class InventorySystem {
private:
    KTP dataKTP[100];
    int jumlahKTP;
    Stack stackBarang;
    Queue queuePembeli;
    string currentAdmin;

    bool isValidKTP(string nik) {
        for(int i = 0; i < jumlahKTP; i++) {
            if(dataKTP[i].nik == nik) return true;
        }
        return false;
    }

public:
    InventorySystem() {
        jumlahKTP = 0;
        loadKTPFromFile();
    }

    void tambahKTP() {
        if(jumlahKTP >= 100) {
            cout << "Penyimpanan KTP penuh!\n";
            return;
        }

        KTP ktp;
        cin.ignore();
        cout << "\nMasukkan data KTP baru:\n";
        cout << "NIK: ";
        getline(cin, ktp.nik);
        cout << "Nama: ";
        getline(cin, ktp.nama);
        cout << "Tempat Lahir: ";
        getline(cin, ktp.tempatLahir);
        cout << "Tanggal Lahir: ";
        getline(cin, ktp.tanggalLahir);
        cout << "Jenis Kelamin: ";
        getline(cin, ktp.jenisKelamin);
        cout << "Alamat: ";
        getline(cin, ktp.alamat);
        cout << "Agama: ";
        getline(cin, ktp.agama);
        cout << "Status Perkawinan: ";
        getline(cin, ktp.statusPerkawinan);
        cout << "Pekerjaan: ";
        getline(cin, ktp.pekerjaan);
        cout << "Kewarganegaraan: ";
        getline(cin, ktp.kewarganegaraan);

        dataKTP[jumlahKTP] = ktp;
        jumlahKTP++;
        saveKTPToFile(ktp);
        cout << "Data KTP berhasil ditambahkan!\n";
    }

    void saveKTPToFile(const KTP& ktp) {
        ofstream file("data_ktp.txt", ios::app);
        if(file.is_open()) {
            file << ktp.nik << endl;
            file << ktp.nama << endl;
            file << ktp.tempatLahir << endl;
            file << ktp.tanggalLahir << endl;
            file << ktp.jenisKelamin << endl;
            file << ktp.alamat << endl;
            file << ktp.agama << endl;
            file << ktp.statusPerkawinan << endl;
            file << ktp.pekerjaan << endl;
            file << ktp.kewarganegaraan << endl;
            file << "---" << endl;
            file.close();
        }
    }

    void loadKTPFromFile() {
        ifstream file("data_ktp.txt");
        if(file.is_open()) {
            string line;
            while(getline(file, line) && jumlahKTP < 100) {
                if(line == "---") {
                    jumlahKTP++;
                    continue;
                }
                static int lineCount = 0;
                switch(lineCount % 10) {
                    case 0: dataKTP[jumlahKTP].nik = line; break;
                    case 1: dataKTP[jumlahKTP].nama = line; break;
                    case 2: dataKTP[jumlahKTP].tempatLahir = line; break;
                    case 3: dataKTP[jumlahKTP].tanggalLahir = line; break;
                    case 4: dataKTP[jumlahKTP].jenisKelamin = line; break;
                    case 5: dataKTP[jumlahKTP].alamat = line; break;
                    case 6: dataKTP[jumlahKTP].agama = line; break;
                    case 7: dataKTP[jumlahKTP].statusPerkawinan = line; break;
                    case 8: dataKTP[jumlahKTP].pekerjaan = line; break;
                    case 9: dataKTP[jumlahKTP].kewarganegaraan = line; break;
                }
                lineCount++;
            }
            file.close();
        }
    }

    bool adminSignIn(string nik) {
        if(isValidKTP(nik)) {
            currentAdmin = nik;
            return true;
        }
        return false;
    }

    void entriItemBarang(string kodeItem, string tanggalMasuk) {
        if(currentAdmin.empty()) {
            cout << "Silakan login sebagai admin terlebih dahulu!\n";
            return;
        }
        stackBarang.push(kodeItem, tanggalMasuk);
        cout << "Item berhasil ditambahkan ke gudang.\n";
    }

    void catatPembeli(string ktp, string waktuKedatangan, string kodeItem) {
        if(isValidKTP(ktp)) {
            queuePembeli.enqueue(ktp, waktuKedatangan, kodeItem);
            cout << "Pembeli berhasil dicatat dalam antrian.\n";
        } else {
            cout << "KTP tidak valid!\n";
        }
    }

    bool jualItemBarang() {
        if(currentAdmin.empty()) {
            cout << "Silakan login sebagai admin terlebih dahulu!\n";
            return false;
        }

        if(queuePembeli.isEmpty() || stackBarang.isEmpty()) return false;

        Pembeli pembeli;
        Item item;

        queuePembeli.dequeue(pembeli);
        stackBarang.pop(item);

        cout << "Barang " << item.kodeItem << " terjual kepada pembeli dengan KTP: " 
             << pembeli.ktp << endl;
        return true;
    }

    void cetakDaftarBarang() {
        if(currentAdmin.empty()) {
            cout << "Silakan login sebagai admin terlebih dahulu!\n";
            return;
        }
        stackBarang.display();
    }

    void cetakAntrianPembeli() {
        if(currentAdmin.empty()) {
            cout << "Silakan login sebagai admin terlebih dahulu!\n";
            return;
        }
        queuePembeli.display();
    }
};

int main() {
    InventorySystem sistem;
    int pilihan;
    string nik, kodeItem, tanggalMasuk, waktuKedatangan;

    while(true) {
        cout << "===========================\n";
        cout << "  SISTEM INVENTORI GUDANG\n";
        cout << "===========================\n";
        cout << "1. Input Data KTP\n";
        cout << "2. Admin Sign In\n";
        cout << "3. Entri Item Barang\n";
        cout << "4. Catat Pembeli\n";
        cout << "5. Proses Penjualan\n";
        cout << "6. Lihat Daftar Barang\n";
        cout << "7. Lihat Antrian Pembeli\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                sistem.tambahKTP();
                break;

            case 2:
                cout << "Masukkan NIK Admin: ";
                cin >> nik;
                if(sistem.adminSignIn(nik)) {
                    cout << "Login berhasil!\n";
                } else {
                    cout << "NIK tidak valid!\n";
                }
                break;

            case 3:
                cout << "Masukkan Kode Item: ";
                cin >> kodeItem;
                cout << "Masukkan Tanggal Masuk (YYYY-MM-DD): ";
                cin >> tanggalMasuk;
                sistem.entriItemBarang(kodeItem, tanggalMasuk);
                break;

            case 4:
                cout << "Masukkan NIK Pembeli: ";
                cin >> nik;
                cout << "Masukkan Waktu Kedatangan (HH:MM): ";
                cin >> waktuKedatangan;
                cout << "Masukkan Kode Item: ";
                cin >> kodeItem;
                sistem.catatPembeli(nik, waktuKedatangan, kodeItem);
                break;

            case 5:
                if(sistem.jualItemBarang()) {
                    cout << "Penjualan berhasil!\n";
                } else {
                    cout << "Penjualan gagal! Periksa antrian pembeli dan stok barang.\n";
                }
                break;

            case 6:
                sistem.cetakDaftarBarang();
                break;

            case 7:
                sistem.cetakAntrianPembeli();
                break;

            case 8:
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                return 0;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}