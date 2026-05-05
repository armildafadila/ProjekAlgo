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
