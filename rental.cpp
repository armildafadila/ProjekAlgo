#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct motor
{
    char namaMtr[50];
    char plat[15];
    int tahun;
    int harga;
    char status[20];
    char penyewa[60];
    int total;
    motor *next;
};

motor *head = NULL;

//void simpanfile
void simpanFile(){
    FILE *fp = fopen("rentalMotor.txt", "w");

    motor* bantu = head;
    while (bantu != NULL) {
        fprintf(fp, "%s;%s;%d;%d;%s;%s;%d\n",
            bantu->namaMtr,
            bantu->plat,
            bantu->tahun,
            bantu->harga,
            bantu->status,
            bantu->penyewa,
            bantu->total);

        bantu = bantu->next; // lanjut ke node berikutnya 
    }
    fclose(fp);
}

// LOAD FILE
void loadfile() {
    FILE *fp = fopen("rentalMotor.txt", "r"); //buka file untuk dibaca
    if (fp == NULL) return; // gaada file keluar

    while (true) {
        motor* baru = new motor; //node baru

        if (fscanf(fp, "%[^;];%[^;];%d;%d;%[^;];%[^;];%d\n",
            baru->namaMtr, baru->plat, &baru->tahun, &baru->harga, baru->status, baru->penyewa, &baru->total)== EOF)
            {
                delete baru;
                break;
            }

            baru->next = NULL; 

            if(head == NULL) {
                head = baru;
            } else {
                motor* bantu = head;
                while (bantu->next != NULL){
                    bantu = bantu->next;
                }
                bantu->next = baru;
            }
    }
    fclose(fp);
}

//TAMBAH DATA
void tambahData(){
    motor* baru = new motor;

    cout << "Nama Motor : "; 
    cin.ignore();
    cin.getline(baru->namaMtr, 80);
    cout << "Plat : ";
    cin >> baru->plat;
    cout << "Tahun : ";
    cin >> baru->tahun;
    cout << "Harga(/hari) : ";
    cin >> baru->harga;

    //defaultnya yang tampil
    strcpy(baru->status, "tersedia"); 
    strcpy(baru->penyewa, "-");
    baru->total = 0;
    baru->next = NULL;

    //data baaru ditaruh di node terakhir//sisip akhir
    if(head == NULL){ // klo belum ada data
        head = baru; // brt jadiin data pertama atau baru

    } else {
        motor* bantu = head;
        while (bantu->next != NULL){
            bantu = bantu->next;
        }
        bantu->next = baru;
    }
    cout << "Data berhasil ditambahkan! \n";
    simpanFile(); // langsung simpan ke file
}

void hapusData(){
    char hapus[60];

    cout << "=============================" << endl;
    cout << "      HAPUS DATA MOTOR       " << endl;
    cout << "=============================" << endl;
    cout << "Data motor yang ingin di hapus : ";
    cin.ignore(1000, '\n');
    cin.getline(hapus, 60);

    motor *bantu = head;
    motor *prev = NULL;

    while (bantu != NULL)
    {
        if(strcmp(bantu->namaMtr, hapus) == 0){
            if (prev == NULL)
                head = bantu->next;
            else
                prev->next = bantu->next;
            
            delete bantu;
            cout << "Data Berhasil dihapus" << endl;
            simpanFile();
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }
    cout << "Data tidak ada" << endl;
}

//SEWA
void sewaMotor() {
    char key[50];
    int hari;
    cout << "\nNama Motor: ";
    cin >> key;

    motor* bantu = head;

    while (bantu != NULL){
        if(strcmp(bantu->namaMtr, key) == 0){


            if(strcmp(bantu->status, "disewa") == 0){
                cout << "Motor sudah disewa!\n";
                return;
            }

            cout << "Harga: " << bantu->harga << endl;

            cout << "Nama Penyewa: ";
            cin >> bantu->penyewa;

            cout << "Lama Sewa: ";
            cin >> hari;

            bantu->total = bantu->harga * hari;
            strcpy(bantu->status, "disewa");

            cout << "Total: " << bantu->total << endl;
            simpanFile();
            return; 
        }

        bantu = bantu->next;
    }

    cout << "Motor tidak ditemukan!\n";
}

//KEMBALI
void kembaliMotor(){
    char namaCari[50];
    cout << "\nNama Motor: ";
    cin >> namaCari;

    motor* bantu = head;

    while (bantu != NULL) {
        if (strcmp(bantu->namaMtr, namaCari) == 0){

            strcpy(bantu->status, "tersedia");
            strcpy(bantu->penyewa, "-");
            bantu->total = 0;

            cout << "Motor Berhasil dikembalikan!\n";
            simpanFile();
            return;
        }
        bantu = bantu->next;
    }

    cout << "Motor tidak ditemukan!\n";
}

int main() {
    loadfile();

    int pilih;
    int subpilih;

    do{
        cout << "==============================="<< endl;
        cout << "   SISTEM ADMIN SEWA MOTOR   "<< endl;
        cout << "==============================="<< endl;

        cout << " 1. Kelola Data Motor" << endl;
        cout << " 2. Transaksi Sewa Motor" << endl;
        cout << " 3. Pencarian Data Motor" << endl;
        cout << " 4. Urutkan Data Motor" << endl;
        cout << " 5. Tampilkan Semua Data Motor" << endl;
        cout << " 6. Keluar" << endl;
        cout << "==============================="<< endl;
        cout << "Pilih Menu: ";
        cin >> pilih;
        cout << endl;

        switch (pilih)
        {
        case 1 :  
        subpilih = 0;
            do{
                cout << "============================"<< endl;
                cout << "     KELOLA DATA MOTOR      " << endl;
                cout << "============================"<< endl;
                
                cout << "1. Tambah Data Motor" << endl;
                cout << "2. Hapus Data Motor" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Pilih Sub Menu: ";
                cin >> subpilih;
                switch (subpilih)
                {
                case 1:
                    tambahData();
                    break;
                case 2:
                    hapusData();
                    break;
                case 3:
                    // Kembali ke Menu Utama
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            }while(subpilih != 3);
        break;
        
        case 2 :  
        subpilih = 0;
            do{ 
                cout << "============================"<< endl;
                cout << "     TRANSAKSI SEWA MOTOR   " << endl;
                cout << "============================"<< endl;
                cout << "1. Sewa Motor" << endl;
                cout << "2. Kembalikan Motor" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Pilih Sub Menu: ";
                cin >> subpilih;

                switch (subpilih)
                {
                case 1:
                    // Sewa Motor
                    break;
                case 2:
                    // Kembalikan Motor
                    break;
                case 3:
                    // Kembali ke Menu Utama
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            }while(subpilih != 3);
        break;

        case 3 :
        subpilih = 0;
        do{
            cout << "============================"<< endl;
            cout << "     PENCARIAN DATA MOTOR   " << endl;
            cout << "============================"<< endl; 
            cout << "1. Cari Berdasarkan Nama Motor" << endl;
            cout << "2. Cari Berdasarkan Plat Nomor" << endl;
            cout << "3. Kembali Ke Menu Utama" << endl;    
            cout << "Pilih Sub Menu: ";
            cin >> subpilih;

                switch (subpilih)
                {
                case 1:
                    //berdasarkan nama
                    break;
                case 2:
                    //berdasarkan plat
                    break;
                case 3:
                    //kembali ke menu utama
                    break;
                default:
                    cout << "Pilihan tidak valid" << endl;
                    break;
                }
        }while (subpilih != 3);
        break;

        case 4 :
        subpilih = 0;
        do{
            cout << "============================"<< endl;
            cout << "     URUTKAN DATA MOTOR     " << endl;
            cout << "============================"<< endl; 
            cout << "1. Urutkan Berdasarkan Harga" << endl;
            cout << "2. Urutkan Berdasarkan Nomor Plat" << endl;
            cout << "3. Kembali Ke Menu Utama" << endl;    
            cout << "Pilih Sub Menu: ";
            cin >> subpilih;

            
                switch (subpilih)
                {
                case 1:
                    /* code */
                    break;
                case 2:

                    break;

                case 3:

                    break;

                default:
                    cout << "Pilihan Tidak Valid" << endl;
                    break;
                }
        }while(subpilih != 3);  
        break;

        case 5 :  
            cout << "DATA MOTOR SAAT INI" << endl;
            // Tampilkan Semua Data
        break;
        case 6 :  
            cout << "Terima kasih telah menggunakan sistem admin sewa motor!" << endl;
        break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        break;
        }

    }while(pilih != 6);
};

