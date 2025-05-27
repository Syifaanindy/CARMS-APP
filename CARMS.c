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
 long long nik, hp;
 char kode_mobil[20];
 char alamat[200];

}pelanggan;

typedef struct {
char kode_mobil[20];
char tanggal_pergi[20];
char tanggal_kembali [20];
char jam_pergi[20];
char jam_kembali[20];
}pesenan;

typedef struct{
    char un[20];
    char pass[20];
}akun;
// var global
mobil cek, car, baru;

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

// pelanggan
void mobil_keluarga();
void minibus();
void booking();

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
            cari();
            break;
        case 3:
            tambah();
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
         while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tStok: %d\tKategori: %[^\t]\t Perjam: %d Perhari: %d\n", cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori,
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
    scanf(" %[^\n]", car.kategori);

    if(strcmp(car.kategori, "Mobil Keluarga")== 0){
        printf("Harga/jam: ");
        scanf("%d", &car.harga_perjam);
    }
    
    printf("Harga/hari:");
    scanf("%d",&car.harga_perhari);

    fprintf(ptr, "Kode: %s\tNama: %s\tPlat: %s\tStok: %d\tKategori: %s\tPerjam: %d\tPerhari: %d\n",
        car.kode, car.nama, car.plat, car.stok, car.kategori,
        car.harga_perjam, car.harga_perhari);


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
    printf("------------------------------------------------------------------------------\n");
    printf("Kode   Produk          Harga/Hari      Harga/Jam      Stok     Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
        car.kode, car.nama, car.plat, &car.stok, car.kategori, &car.harga_perjam, &car.harga_perhari) != EOF) {
        printf("%-6s %-15s %-15d %-15d %-8d %-15s\n",
        car.kode, car.nama, car.harga_perhari, car.harga_perjam, car.stok, car.kategori);
    }

    printf("---------------------------------------------------------------\n");
    fclose(ptr);
    printf("Tekan enter untuk kembali");
    getchar(); 
    getchar();
    kelola_mobil();

}
void edit(){
    char kodetoedit[20];
    int pilih;
    FILE *fold, *fnew;
    fold = fopen("mobil.txt", "r");
    fnew = fopen("mobil_new.txt", "w");

    if (!fold || !fnew) {
        printf("Gagal membuka file!\n");
        return;
    }

    int ketemu = 0;

    printf("Masukkan Kode Mobil yang ingin diedit: ");
    scanf("%s", kodetoedit);
    getchar();

    while (fscanf(fold, "Kode: %s\tNama: %[^\t]\tPlat: %s\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) == 7) {

        if (strcmp(kodetoedit, cek.kode) == 0) {
            ketemu = 1;
            printf("\nData ditemukan:\n");
            printf("Nama: %s\n", cek.nama);
            printf("Plat: %s\n", cek.plat);
            printf("Stok: %d\n", cek.stok);
            printf("Kategori: %s\n", cek.kategori);
            printf("Harga/jam: %d\n", cek.harga_perjam);
            printf("Harga/hari: %d\n", cek.harga_perhari);

            printf("\nEdit:\n1. Harga\n2. Stok\nPilihan: ");
            scanf("%d", &pilih);

            if (pilih == 1) {
                if (strcmp(cek.kategori, "Mobil Keluarga") == 0) {
                    printf("Harga/jam baru: ");
                    scanf("%d", &cek.harga_perjam);
                }
                printf("Harga/hari baru: ");
                scanf("%d", &cek.harga_perhari);
            } else if (pilih == 2) {
                printf("Stok baru: ");
                scanf("%d", &cek.stok);
            }
        }
        fprintf(fnew, "Kode: %s\tNama: %s\tPlat: %s\tStok: %d\tKategori: %s\tPerjam: %d\tPerhari: %d\n",
                cek.kode, cek.nama, cek.plat, cek.stok, cek.kategori, cek.harga_perjam, cek.harga_perhari);
    }

    fclose(fold);
    fclose(fnew);

    remove("mobil.txt");
    rename("mobil_new.txt", "mobil.txt");

    if (ketemu) {
        printf("Data berhasil diubah.\n");
    } else {
        printf("Kode mobil tidak ditemukan.\n");
    }
}

void cari(){
    char kode_cari[20];
    int kode_sama = 0;
    FILE *ptr = fopen("mobil.txt", "r");

    if (ptr == NULL)
    {
        printf("File tidak ditemukan.\n");
    }

    system("cls");
    printf("============================================================\n");
    printf("\t\tCari Data Mobil\n");
    printf("============================================================\n");
    printf("Masukkan Kode Mobil yang ingin Dicari: ");
    scanf("%s", kode_cari);

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %s\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) !=EOF)
    {
        if (strcmp(cek.kode, kode_cari) == 0)
        {
           kode_sama = 1;
            printf("\nData Mobil Ditemukan:\n");
            printf("Kode       : %s\n", cek.kode);
            printf("Nama       : %s\n", cek.nama);
            printf("Plat       : %s\n", cek.plat);
            printf("Stok       : %d\n", cek.stok);
            printf("Kategori   : %s\n", cek.kategori);
            printf("Harga/jam  : %d\n", cek.harga_perjam);
            printf("Harga/hari : %d\n", cek.harga_perhari);
            break;
        }
    }
    if (!kode_sama)
    {
        printf("\nData Mobil dengan Kode %s Tidak Ditemukan.\n", kode_cari);
    }
    fclose(ptr);
    printf("\nTekan Enter Untuk Kembali...");
    getchar();
    getchar();
    kelola_mobil();
}
void menu_pelanggan(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\tSELAMAT DATANG DI CARMS\n");
    printf("============================================================\n\n");

    printf("Pilih Mobil:\n");
    printf("1. Mobil Keluarga\n");
    printf("2. Minibus\n\n");

    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        mobil_keluarga();
    }else{
        minibus();
    }
}

void mobil_keluarga(){
    int pilihan;
    FILE *ptr;
	ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\tPILIHAN MOBIL KELUARGA\n");
    printf("============================================================\n\n");
    printf("Kode   Produk          Harga/Hari      Harga/Jam      Stok     Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
    if (strcmp(cek.kategori, "Mobil Keluarga") == 0){
        printf("%-6s %-15s %-15d %-15d %-8d %-15s\n",
            cek.kode, cek.nama, cek.harga_perhari, cek.harga_perjam, cek.stok, cek.kategori);
        }
    }
    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        cari();
    }else if (pilihan == 2){
        booking();
    }

    fclose(ptr);
}

void minibus(){
    int pilihan;
    FILE *ptr;
	ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\t\tPILIHAN MINIBUS\n");
    printf("============================================================\n\n");
    printf("Kode   Produk        Harga/Jam      Stok     Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
    if (strcmp(cek.kategori, "Minibus") == 0){
        printf("%-6s %-15s %-15d %-8d %-15s\n",
            cek.kode, cek.nama, cek.harga_perhari, cek.stok, cek.kategori);
        }
    }
    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        cari();
    }else if (pilihan == 3) {
        booking();
    }

    fclose(ptr);
}

void booking(){
    pelanggan p;
    pesenan ps;
    int pilihan, hari, jam, found = 0;

     FILE *ptr = fopen("datadiri.txt", "a+");
     if (ptr == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

     printf("Masukkan Nama: ");
     scanf(" %[^\n]", p.nama);

     printf("Masukkan No.HP: ");
     scanf("%lld", &p.hp);

     printf("Masukkan NIK: ");
     scanf("%lld", &p.nik);

     printf("Masukkan Alamat: ");
     scanf(" %[^\n]", p.alamat);

     printf("Masukkan Kode Mobil: ");
     scanf("%s", p.kode_mobil);

     FILE *mobil = fopen("mobil.txt", "r");
     if (mobil== NULL) {
        printf("Gagal membuka file mobil.txt.\n");
     return;
    }

    while (fscanf(mobil, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tStok: %d\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
              cek.kode, cek.nama, cek.plat, &cek.stok, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
    if (strcmp(cek.kode, p.kode_mobil) == 0) {
        found = 1;
        break;
    }
}

    if (!found) {
    printf("Kode mobil tidak ditemukan!\n");
    return;
    }

     system("cls");
     do {
        printf("===== Jadwal Booking ===== \n");
        printf("1. Perhari\n");

        if (strcmp(cek.kategori, "Mobil Keluarga") == 0) {
        printf("2. Perjam\n");
        }
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);
     
        if (pilihan ==1){
            printf("Masukkan Jumlah Hari Sewa: ");
            scanf("%d", &hari);
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Tanggal Kembali (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_kembali);
            fprintf(ptr, "==== BOOKING PERHARI ====\nNama: %s\nNo.HP: %lld\nNIK: %lld\nAlamat: %s\nKode Mobil: %s\nTanggal Pinjam: %s\nTanggal Kembali: %s\n\n", 
                    p.nama, p.hp, p.nik, p.alamat, p.kode_mobil, ps.tanggal_pergi, ps.tanggal_kembali);
        } else if (pilihan == 2 && strcmp(cek.kategori, "Mobil Keluarga") == 0){
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Masukkan Jumlah Jam Sewa: ");
            scanf("%d", &jam);
            printf("Jam Pinjam (HH:MM): ");
            scanf("%s", ps.jam_pergi);
            printf("Jam Kembali (HH:MM): ");
            scanf("%s", ps.jam_kembali);
            fprintf(ptr, "==== BOOKING PERJAM ====\nNama: %s\nNo.HP: %lld\nNIK: %lld\nAlamat: %s\nKode Mobil: %s\nTanggal Pinjam: %s\nJam Pinjam: %s\nJam Kembali: %s\n\n", 
                    p.nama, p.hp, p.nik, p.alamat, p.kode_mobil, ps.tanggal_pergi, ps.jam_pergi, ps.jam_kembali);

        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (!(pilihan == 1 || (pilihan == 2 && strcmp(cek.kategori, "Mobil Keluarga") == 0)));
    printf("============================================================\n");
    printf("                        INVOICE                             \n");
    printf("============================================================\n");
    printf("Nama            : %s\n", p.nama);
    printf("No. HP          : %lld\n", p.hp);
    printf("NIK             : %lld\n", p.nik);
    printf("Alamat          : %s\n", p.alamat);
    printf("Kode Mobil      : %s\n", p.kode_mobil);
    printf("Nama Mobil      : %s\n", cek.nama);
    printf("Plat Mobil      : %s\n", cek.plat);

   if (pilihan == 1) {
    printf("Tanggal Pinjam  : %s\n", ps.tanggal_pergi);
    printf("Tanggal Kembali : %s\n", ps.tanggal_kembali);
    printf("Total Biaya     : Rp%d\n", hari * cek.harga_perhari);
 } else if (pilihan == 2) {
    printf("Tanggal Pinjam  : %s\n", ps.tanggal_pergi);
    printf("Jam Pinjam      : %s\n", ps.jam_pergi);
    printf("Jam Kembali     : %s\n", ps.jam_kembali);
    printf("Total Biaya     : Rp%d\n", jam * cek.harga_perjam);
}

printf("============================================================\n");


    fclose(ptr);
    fclose(mobil);
    printf("\nTekan enter untuk kembali");
    getchar(); 
    getchar();
}
void laporan(){

}
