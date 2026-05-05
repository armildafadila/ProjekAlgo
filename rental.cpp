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