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
            baru->namaMtr, 
            baru->plat, 
            &baru->tahun, 
            &baru->harga, 
            baru->status, 
            baru->penyewa, 
            &baru->total) != 7) // jika tidak lengkap lanjut ke "delete baru"
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

    cout << "-----------------------------------------"<< endl;
    cout << "|           TAMBAH DATA MOTOR           |"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "Nama Motor                 : "; 
    cin.ignore(1000, '\n');
    cin.getline(baru->namaMtr, 50);
    cout << "Plat (ABXXXXCD)            : ";
    cin >> baru->plat;
    cout << "Tahun                      : ";
    cin >> baru->tahun;
    cout << "Harga /24Jam (ex:70000)    : ";
    cin >> baru->harga;
    cout << "-----------------------------------------"<< endl;

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
    cout << "Data berhasil ditambahkan! " << endl;
    cout << endl;
    simpanFile(); // langsung simpan ke file
    cin.ignore(1000, '\n');
}

void hapusData(){
    char hapus[15];

    cout << "-----------------------------------------"<< endl;
    cout << "|            HAPUS DATA MOTOR           |"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "| Harap masukkan plat motor yang akan di hapus di bawah ini" << endl;
    cout << "| Plat motor (ABXXXXCD) : ";
    cin.ignore(1000, '\n');
    cin.getline(hapus, 15);

    motor *bantu = head;
    motor *prev = NULL;

    while (bantu != NULL)
    {
        if(strcmp(bantu->plat, hapus) == 0){
            if (prev == NULL)
                head = bantu->next;
            else
                prev->next = bantu->next;
            
            delete bantu;
            
            cout << "-----------------------------------------"<< endl;
            cout << "Data Berhasil dihapus" << endl;
            cout << endl;
            simpanFile();
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }
    cout << "Data tidak ada" << endl;
    cout << endl;
}

// BIAR KALAU INPUT HURUF BESAR KECIL TETEP BISA DAPET DATANYA
// fungsi compare tidak peduli kapital
int strcmpIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) return 1;
        a++; b++;
    }
    return tolower(*a) - tolower(*b);
}

//SEWA Motor
void sewaMotor() {
    char key[50];
    int hari;

    cout << "-----------------------------------------"<< endl;
    cout << "|               SEWA MOTOR              |"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "| Nama Motor : ";
    cin.ignore(1000, '\n');
    cin.getline(key, 50);

    motor* bantu = head;

    while (bantu != NULL){
        if(strcmpIgnoreCase(bantu->namaMtr, key) == 0){


            if(strcmp(bantu->status, "disewa") == 0){
                cout << "Motor sudah disewa!\n";
                return;
            }
            
            cout << "-----------------------------------------"<< endl;
            cout << "Harga                      : " << bantu->harga << endl;
            cout << "Nama Penyewa               : ";
            cin >> bantu->penyewa;
            cout << "Lama Sewa (jml hari) ex: 2 : ";
            cin >> hari;

            bantu->total = bantu->harga * hari;
            strcpy(bantu->status, "disewa");
            cout << "-----------------------------------------"<< endl;
            cout << "TOTAL BIAYA                : " << bantu->total << endl;
            cout << "Motor Berhasil Disewa, status berubah" << endl;
            cout << endl;

            simpanFile();
            return; 
        }

        bantu = bantu->next;
    }

    cout << "Motor tidak ditemukan!" << endl;
    cout << endl;
}

//Fungsi KEMBALI
void kembaliMotor(){
    char namaCari[50];

    cout << "-----------------------------------------"<< endl;
    cout << "|            KEMBALIKAN MOTOR           |"<< endl;
    cout << "-----------------------------------------"<< endl;
    cout << "| Nama Motor : " ;
    cin.ignore();
    cin.getline(namaCari, 50);

    motor* bantu = head;

    while (bantu != NULL) {
        if (strcmpIgnoreCase(bantu->namaMtr, namaCari) == 0){

            strcpy(bantu->status, "tersedia");
            strcpy(bantu->penyewa, "-");
            bantu->total = 0;

            cout << "-----------------------------------------"<< endl;
            cout << "Motor Berhasil Dikembalikan, status berubah" << endl;
            cout << endl;

            simpanFile();
            return;
        }
        bantu = bantu->next;
    }
    cout << "Motor tidak ditemukan! " << endl;
    cout << endl;
}

void cariNama(){
    char cari[50];

    cout << "-----------------------------------------" << endl;
    cout << "|         CARI DENGAN NAMA MOTOR        |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "| Masukkan Nama Motor : ";
    cin.ignore(1000, '\n');
    cin.getline(cari, 50);

    motor* bantu = head;

    //sequential search
    while (bantu != NULL) {
        if(strcmpIgnoreCase(bantu->namaMtr, cari) == 0){

            cout << "-----------------------------------------" << endl;
            cout << "Motor Berhasil Ditemukan!"                 << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Nama    : " << bantu->namaMtr << endl;
            cout << "Plat    : " << bantu->plat    << endl;
            cout << "Tahun   : " << bantu->tahun   << endl;
            cout << "Harga   : " << bantu->harga   << endl;
            cout << "Status  : " << bantu->status  << endl;
            cout << "Penyewa : " << bantu->penyewa << endl;
            cout << "Total   : " << bantu->total   << endl;
            cout << "-----------------------------------------" << endl;
            cout << endl;
            return;
        }
        bantu = bantu->next;
    }

    cout << "Motor Tidak Ditemukan!" << endl;
    cout << endl;
}

void cariPlat(){
    char cari[20];

    cout << "-----------------------------------------" << endl;
    cout << "|         CARI DENGAN PLAT MOTOR        |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "| Masukan plat motor : ";
    cin >> cari;

    motor* bantu = head;

    //sequential search
    while (bantu != NULL){

        if(strcmpIgnoreCase(bantu->plat, cari) == 0){

            cout << "-----------------------------------------" << endl;
            cout << "Motor Berhasil Ditemukan!"                 << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Nama    : " << bantu->namaMtr << endl;
            cout << "Plat    : " << bantu->plat    << endl;
            cout << "Tahun   : " << bantu->tahun   << endl;
            cout << "Harga   : " << bantu->harga   << endl;
            cout << "Status  : " << bantu->status  << endl;
            cout << "Penyewa : " << bantu->penyewa  << endl;
            cout << "Total   : " << bantu->total   << endl;
            cout << "-----------------------------------------" << endl;
            cout << endl;
            return;
        }
        bantu = bantu->next;
    }

    cout << "Motor Tidak Ditemukan!" << endl;
    cout << endl;
}

//TAMPIL DATA
void tampil(){
    if (head == NULL) {
            cout << "Belum ada data motor" << endl;
            return;
    }

    motor* bantu = head;

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "| NO | NAMA MOTOR          | PLAT     | TAHUN        | HARGA       |   STATUS   |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    
    int no = 1;
    while (bantu != NULL){
        printf("| %-3d| %-20s| %-9s| %-13d| %-12d| %-11s|\n", 
            no++, bantu->namaMtr, bantu->plat, bantu->tahun, bantu->harga, bantu->status);
        bantu = bantu->next;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;

}

// SWAP UNTUK MENUKAR
void swapData(motor* a, motor* b){
    char tmpstr[60];
    int tmpint;

    // tukar semua field string
    strcpy(tmpstr, a->namaMtr); strcpy(a->namaMtr, b->namaMtr); strcpy(b->namaMtr, tmpstr);
    strcpy(tmpstr, a->plat); strcpy(a->plat, b->plat); strcpy(b->plat, tmpstr);
    strcpy(tmpstr, a->status); strcpy(a->status, b->status); strcpy(b->status, tmpstr);
    strcpy(tmpstr, a->penyewa); strcpy(a->penyewa, b->penyewa); strcpy(b->penyewa, tmpstr);

    // tukar semua field angka
    tmpint = a->tahun; a->tahun = b->tahun; b->tahun = tmpint;
    tmpint = a->harga; a->harga = b->harga; b->harga = tmpint;
    tmpint = a->total; a->total = b->total; b->total = tmpint;
}

// urutkan harga dari yang paling murah
void urutHarga(){
    if (head == NULL || head->next == NULL) return;

    bool tukar;
    do {
        tukar = false;
        motor* skrg = head;

        while (skrg->next != NULL){
            // [i] badingkan node sekarang degan node berikutnya
            if (skrg->harga > skrg->next->harga){
                // [ii] kalau harga sekarang lebih besar -> tukar
                swapData(skrg, skrg->next);
                tukar = true;
            }
            skrg = skrg->next;
        }
    } while (tukar);

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|                         DATA URUT DARI HARGA TERENDAH                         |" << endl;
    tampil();
    simpanFile();
}

// urutkan plat A-Z
void urutPlat(){
    if(head == NULL || head->next == NULL) return;

    bool tukar;
    do {
        tukar = false;
        motor* skrg = head;

        while (skrg->next != NULL){
            if (strcmp(skrg->plat, skrg->next->plat) > 0) {
                swapData(skrg, skrg->next);
                tukar = true;
            }
            skrg = skrg->next;
        }
    } while (tukar);
    
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|                         DATA URUT DARI PLAT TERKECIL                          |" << endl;
    tampil();
    simpanFile();
}


int main() {
    loadfile();

    int pilih;
    int subpilih;

    do{
        cout << "=========================================" << endl;
        cout << "| NO |     SISTEM ADMIN SEWA MOTOR      |" << endl;
        cout << "=========================================" << endl;
        cout << "| 1  | Kelola Data Motor                |" << endl;
        cout << "| 2  | Transaksi Sewa Motor             |" << endl;
        cout << "| 3  | Pencarian Data Motor             |" << endl;
        cout << "| 4  | Urutkan Data Motor               |" << endl;
        cout << "| 5  | Tampilkan Semua Data Motor       |" << endl;
        cout << "| 6  | Keluar                           |" << endl;
        cout << "=========================================" << endl;
        cout << "| Pilih Menu: ";
        cin >> pilih;
        cout << endl;

        switch (pilih)
        {
        case 1 :  
        subpilih = 0;
            do{
                cout << "=========================================" << endl;
                cout << "|           KELOLA DATA MOTOR           |" << endl;
                cout << "=========================================" << endl;
                cout << "| 1.| Tambah Data Motor                 |" << endl;
                cout << "| 2.| Hapus Data Motor                  |" << endl;
                cout << "| 3.| Kembali ke Menu Utama             |" << endl;
                cout << "=========================================" << endl;
                cout << "| Pilih Sub Menu: ";
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
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            }while(subpilih != 3);
            cout << endl;
        break;
        
        case 2 :  
        subpilih = 0;
            do{ 
                cout << "=========================================" << endl;
                cout << "|          TRANSAKSI SEWA MOTOR         |" << endl;
                cout << "=========================================" << endl;
                cout << "| 1.| Sewa Motor                        |" << endl;
                cout << "| 2.| Kembalikan Motor                  |" << endl;
                cout << "| 3.| Kembali ke Menu Utama             |" << endl;
                cout << "=========================================" << endl;
                cout << "| Pilih Sub Menu: ";
                cin >> subpilih;

                switch (subpilih)
                {
                case 1:
                    sewaMotor();
                    break;
                case 2:
                    kembaliMotor();
                    break;
                case 3:
                    break;
                    cout << endl;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    break;
                }
            }while(subpilih != 3);
            cout << endl;
        break;

        case 3 :
        subpilih = 0;
        do{
            cout << "=========================================" << endl;
            cout << "|          PENCARIAN DATA MOTOR         |" << endl;
            cout << "=========================================" << endl; 
            cout << "| 1.| Cari Berdasarkan Nama Motor       |" << endl;
            cout << "| 2.| Cari Berdasarkan Plat Nomor       |" << endl;
            cout << "| 3.| Kembali Ke Menu Utama             |" << endl;
            cout << "=========================================" << endl;    
            cout << "| Pilih Sub Menu: ";
            cin >> subpilih;

                switch (subpilih)
                {
                case 1:
                    cariNama();
                    break;
                case 2:
                    cariPlat();
                    break;
                case 3:
                    break;
                default:
                    cout << "Pilihan tidak valid" << endl;
                    break;
                }
        }while (subpilih != 3);
        cout << endl;
        break;

        case 4 :
        subpilih = 0;
        do{
            cout << "=========================================" << endl;
            cout << "|           URUTKAN DATA MOTOR          |" << endl;
            cout << "=========================================" << endl;
            cout << "| 1.| Urutkan Berdasarkan Harga         |" << endl;
            cout << "| 2.| Urutkan Berdasarkan Nomor Plat    |" << endl;
            cout << "| 3.| Kembali Ke Menu Utama             |" << endl;    
            cout << "=========================================" << endl;
            cout << "| Pilih Sub Menu: ";
            cin >> subpilih;

                switch (subpilih)
                {
                case 1:
                    urutHarga();
                    break;
                case 2:
                    urutPlat();
                    break;
                case 3:
                    break;
                default:
                    cout << "Pilihan Tidak Valid" << endl;
                    break;
                }
        }while(subpilih != 3);
        cout << endl;
        break;

        case 5 :  
            cout << "---------------------------------------------------------------------------------" << endl;
            cout << "|                              DATA MOTOR SAAT INI                              |" << endl;
            tampil();
            cout << endl;
        break;
        case 6 :  
            cout << "Terima kasih telah menggunakan sistem admin sewa motor!" << endl;
            cout << endl;
        break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            cout << endl;
        break;
        }

    }while(pilih != 6);
};

