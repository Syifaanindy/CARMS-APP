#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>     
#include <conio.h>   

// tipe data bentukan 
typedef struct{
    char kode[20];
    char kategori[20];
    char nama[50];
    char plat[20];
    int stok;
    int harga_perhari;
    int harga_perjam;
}mobil;

typedef struct{
 char nama[100];
 int nik, hp;
 char kode_mobil[20];
 char alamat[200];
 int tanggal_pergi;
 int tanggal_kembali;

}pelanggan;

typedef struct {
char kode_mobil[20];
int tanggal_pergi;
int tanggal_kembali;
}pesenan;

typedef struct{
    char un[20];
    char pass[20];
}akun;
// var global
mobil cek, car;

// void login
int login(akun admin, char inuser[], char inpass[]);

//void menu
void persetujuan();
void menu_admin();
void menu_pelanggan();

// kelola mobil
void kelola_mobil();
void tambah();
void hapus();
void lihat();
void edit();
void cari();

//laporan
void laporan();

int main() {
    int pilih;
    char inuser[20];
    char inpass[20];
    akun akun_admin = {"admin123", "123admin"}; // username: admin123, password: 123

    do {
        system("cls");
        printf("==============================================================\n");
        printf("\t\t  SELAMAT DATANG DI CARMS\n");
        printf("==============================================================\n\n");

        printf("Masuk sebagai:\n");
        printf("1. Admin\n");
        printf("2. Pelanggan\n\n");

        printf("Input pilihan Menu: ");
        scanf("%d",&pilih);


        switch (pilih) {
            case 1:
                printf("Masukkan username: ");
                scanf("%s", inuser);
                printf("Masukkan password: ");
                scanf("%s", inpass);

                if (login(akun_admin, inuser, inpass)) {
                    printf("Login berhasil. Selamat datang, %s!\n", inuser);
                    menu_admin();
                } else {
                    printf("Login gagal. Username atau password salah.\n");
                }
                break;
            case 2:
                 persetujuan();
                break;

            case 3:
                printf("Terima kasih telah menggunakan program.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilih != 3);

    return 0;
}

// athentication
int login(akun admin, char inuser[], char inpass[]) {
    if (strcmp(inuser,admin.un ) == 0 && strcmp(inpass, admin.pass) == 0) {
        return 1;
    } else {
        return 0;
    }
}
// end authentication

void persetujuan(){
    int pilihan;
    system("cls");
    printf("==============================================================\n");
    printf("\t\t  SELAMAT DATANG DI CARMS\n");
    printf("==============================================================\n\n");

    printf("Sebelum lanjut untuk memilih dan menyewa mobil, kami himbau\n");
    printf("kepada pelanggan untuk menyetujui beberapa ketentuan yang\n");
    printf("berlaku yakni sebagai berikut:\n\n");

    printf("a. Keterlambatan pengembalian mobil akan dikenakan denda\n");
    printf("   per jamnya sebesar 10%% dari harga rental, berlaku kelipatan.\n\n");

    printf("b. Kerusakan yang terjadi pada kendaraan setelah sewa akan\n");
    printf("   murni menjadi tanggung jawab pelanggan selaku penyewa.\n\n");

    printf("c. Kendaraan wajib dikembalikan dengan bensin yang sama\n");
    printf("   seperti saat pertama kali diambil.\n\n");

    printf("Dengan demikian apakah ketentuan dapat diterima?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n\n");
    printf("Pilihan Anda: ");
    scanf("%d",&pilihan);

    if(pilihan == 1){
        menu_pelanggan();
    }else{
        main();
    }

}
void menu_admin(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tMENU UTAMA\n");
    printf("============================================================\n\n");

    printf("Pilih menu:\n");
    printf("1. Kelola Data Mobil\n");
    printf("2. Laporan\n\n");

    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        kelola_mobil();
    }else{
        laporan();
    }
}
void kelola_mobil(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t  MENU KELOLA DATA MOBIL\n");
    printf("============================================================\n\n");

    printf("Pilih menu:\n");
    printf("1. Lihat Data Mobil\n");
    printf("2. Cari Data Mobil\n");
    printf("3. Input Data Mobil\n");
    printf("4. Update Data Mobil\n");
    printf("5. Hapus Data Mobil\n");
    printf("6. Keluar\n\n");

    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);

    switch (pilihan) {
        case 1:
            lihat();
            break;
        case 2:
            tambah();
            break;
        case 3:
            cari();
            break;
        case 4:
            edit();
            break;
        case 5:
            hapus();
            break;
        case 6:
            menu_admin();
            break;
        default:
            printf(">> Pilihan tidak valid.\n");
            break;
    }
}
void tambah(){
    char kode[20];
    FILE *ptr = fopen("mobil.txt", "a+");
    int kode_sama = 0;
    system("cls");
    do {
        kode_sama = 0;
        printf("Masukkan kode Mobil: ");
        scanf("%s", kode);

        rewind(ptr);
         while (fscanf(ptr, "Kode: %s/tNama: %[^\n]\tPlat: %s\tStok: %d\tKategori: %[^\n]\t Harga/jam: %d Harga/hari: %d\n", cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori,
             &cek.harga_perjam, &cek.harga_perhari) != EOF){
            if (strcmp(kode, cek.kode) == 0) {
                printf("Kode %s sudah digunakan!\n", kode);
                kode_sama = 1;
                break;
            }
        }
    } while (kode_sama);

    strcpy(car.kode, kode);
    getchar(); 

    printf("Nama Mobil: ");
    scanf(" %[^\n]", car.nama);
    
    printf("Plat Mobil: ");
    scanf(" %[^\n]", car.plat);

    printf("Stok: ");
    scanf("%d", &car.stok);

    printf("Kategori (Mobil Keluarga,Minibus): ");
    scanf("%s", car.kategori);

    printf("Harga/jam: ");
    scanf("%d",&car.harga_perjam);

    printf("Harga/hari:");
    scanf("%d",&car.harga_perhari);

    fprintf(ptr, "Kode: %s", car.kode);
    fprintf(ptr, "Nama: %s", car.nama);
    fprintf(ptr, "Plat: %s", car.plat);
    fprintf(ptr, "Stok: %d", car.stok);
    fprintf(ptr, "Harga/jam: %d", car.harga_perjam);
    fprintf(ptr, "Harga/hari: %d", car.harga_perhari);
    fprintf(ptr, "Kategori: %s\n", car.kategori); 

    fclose(ptr);
    lihat();
}
void hapus(){

}
void lihat(){
    FILE *ptr;
    ptr = fopen("mobil.txt", "r");
    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }
    system("cls");
    printf("========================= Data Produk ========================\n\n");
    printf("---------------------------------------------------------------\n");
    printf("Kode   Produk          Harga        Stok     Kategori    \n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(ptr, "%s %s %s %d %d %d %s\n", car.kode, car.nama,
                  car.plat, &car.stok,&car.harga_perjam, &car.harga_perhari, car.kategori) != EOF) {
        printf("%-6s %-15s %-10d %-8d %-15s\n",
               car.kode, car.nama, car.plat, car.stok, car.harga_perjam, car.harga_perhari, car.kategori);
    }

    printf("---------------------------------------------------------------\n");
    fclose(ptr);
    kelola_mobil();

}
void edit(){

}
void cari(){

}
void menu_pelanggan(){

}
void laporan(){

}
