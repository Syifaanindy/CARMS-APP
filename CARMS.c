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
char kategori_pesanan[20];
int total_transaksi;
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
void menu_laporan();
void data_pelanggan();
void L_mobil();

// bubble sort
void bubbleSort(mobil car[], int n);
#define MAX_MOBIL 100

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
    printf("2. Laporan\n");
    printf("3. Keluar\n\n");
    
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        kelola_mobil();
    } else if (pilihan == 2){
        menu_laporan();
    } else{ 
       main();
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
        while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n", 
               cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
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

    printf("Kategori (Mobil Keluarga,Minibus): ");
    scanf(" %[^\n]", car.kategori);

    if(strcmp(car.kategori, "Mobil Keluarga") == 0) {
        printf("Harga/jam: ");
        scanf("%d", &car.harga_perjam);
    } else {
        car.harga_perjam = 0;  
    }
    
    printf("Harga/hari: ");
    scanf("%d", &car.harga_perhari);

    fprintf(ptr, "Kode: %s\tNama: %s\tPlat: %s\tKategori: %s\tPerjam: %d\tPerhari: %d\n",
            car.kode, car.nama, car.plat, car.kategori,
            car.harga_perjam, car.harga_perhari);

    fclose(ptr);
    lihat();
}
void hapus() {
    char kodetohapus[20];
    FILE *fold, *fnew;
    fold = fopen("mobil.txt", "r");
    fnew = fopen("mobil_new.txt", "w");

    if (!fold || !fnew) {
        printf("Gagal membuka file!\n");
        return;
    }

    printf("Masukkan Kode Mobil yang ingin dihapus: ");
    scanf("%s", kodetohapus);
    getchar();

    int ketemu = 0;

    while (fscanf(fold, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) == 6) {
        
        if (strcmp(kodetohapus, cek.kode) != 0) {
            fprintf(fnew, "Kode: %s\tNama: %s\tPlat: %s\tKategori: %s\tPerjam: %d\tPerhari: %d\n",
                    cek.kode, cek.nama, cek.plat, cek.kategori, cek.harga_perjam, cek.harga_perhari);
        } else {
            ketemu = 1;
        }
    }

    fclose(fold);
    fclose(fnew);

    remove("mobil.txt");
    rename("mobil_new.txt", "mobil.txt");

    if (ketemu) {
        printf("Data mobil dengan kode %s berhasil dihapus.\n", kodetohapus);
    } else {
        printf("Kode mobil tidak ditemukan.\n");
    }
    
    printf("\nTekan Enter untuk kembali...");
    getchar();
    kelola_mobil();
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
    printf("Kode   Produk          Harga/Hari      Harga/Jam        Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t] \tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
        car.kode, car.nama, car.plat, car.kategori, &car.harga_perjam, &car.harga_perhari) != EOF) {
        printf("%-6s %-15s %-15d %-8d %-15s\n",
        car.kode, car.nama, car.harga_perhari, car.harga_perjam, car.kategori);
    }

    printf("---------------------------------------------------------------\n");
    fclose(ptr);
    printf("Tekan enter untuk kembali");
    getchar(); 
    getchar();
    kelola_mobil();

}

void edit() {
    char kodetoedit[20];
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

    while (fscanf(fold, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) == 6) {
        if (strcmp(kodetoedit, cek.kode) == 0) {
            ketemu = 1;
            printf("\nData ditemukan:\n");
            printf("Nama: %s\n", cek.nama);
            printf("Plat: %s\n", cek.plat);
            printf("Kategori: %s\n", cek.kategori);
            
            if (strcmp(cek.kategori, "Mobil Keluarga") == 0) {
                printf("Harga/jam saat ini: %d\n", cek.harga_perjam);
                printf("\nHarga/jam baru: ");
                scanf("%d", &cek.harga_perjam);
            }
            
            printf("\nHarga/hari saat ini: %d\n", cek.harga_perhari);
            printf("Harga/hari baru: ");
            scanf("%d", &cek.harga_perhari);
            getchar();
        }
        
        fprintf(fnew, "Kode: %s\tNama: %s\tPlat: %s\tKategori: %s\tPerjam: %d\tPerhari: %d\n",
                cek.kode, cek.nama, cek.plat, cek.kategori, cek.harga_perjam, cek.harga_perhari);
    }

    fclose(fold);
    fclose(fnew);

    if (ketemu) {
        remove("mobil.txt");
        rename("mobil_new.txt", "mobil.txt");
        printf("Data berhasil diubah.\n");
    } else {
        remove("mobil_new.txt");
        printf("Kode mobil tidak ditemukan.\n");
    }

    printf("\nTekan Enter untuk kembali...");
    getchar();
    kelola_mobil();
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

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) !=EOF)
    {
        if (strcmp(cek.kode, kode_cari) == 0)
        {
           kode_sama = 1;
            printf("\nData Mobil Ditemukan:\n");
            printf("Kode       : %s\n", cek.kode);
            printf("Nama       : %s\n", cek.nama);
            printf("Plat       : %s\n", cek.plat);
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
    printf("2. Minibus\n");
    printf("3. Keluar\n\n");

    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        mobil_keluarga();
    }else if (pilihan == 2){
        minibus();
    }else if (pilihan == 3){
        main();
}
}

void mobil_keluarga(){
    int pilihan,pilih;
    FILE *ptr;
	ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\tPILIHAN MOBIL KELUARGA\n");
    printf("============================================================\n\n");
    printf("Kode   Produk          Harga/Hari      Harga/Jam          Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

     while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
        if (strcmp(cek.kategori, "Mobil Keluarga") == 0){
            printf("%-6s %-15s %-15d %-15d %-15s\n",
                cek.kode, cek.nama, cek.harga_perhari, cek.harga_perjam, cek.kategori);
        }
    }
    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n");
    printf("3. Keluar\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        printf("1. Termurah\n");
        printf("2. Nama\n");
        printf("3. Keluar\n\n");
        printf("Input Pilihan Menu: ");
        scanf("%d",&pilih);

    if (pilih == 1) {
    mobil car[MAX_MOBIL];
    int count = 0;
    ptr = fopen("mobil.txt","r"); 
    if (ptr == NULL) {
        printf("File tidak bisa dibuka.\n");
        return;
    }
     while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
                  car[count].kode, car[count].nama, car[count].plat, car[count].kategori,
                  &car[count].harga_perjam, &car[count].harga_perhari) != EOF) {
                if (strcmp(car[count].kategori, "Mobil Keluarga") == 0) {
                    count++;
                    if (count >= MAX_MOBIL) break;
                }
            }
    fclose(ptr);

    bubbleSort(car, count);

        system("cls");
        printf("============================================================\n");
        printf("\t\tPILIHAN MOBIL KELUARGA\n");
        printf("============================================================\n\n");
        printf("Kode   Produk          Harga/Hari      Harga/Jam       Kategori    \n"); 
        printf("---------------------------------------------------------------\n");

   for (int i = 0; i < count; i++) {
    if (strcmp(car[i].kategori, "Mobil Keluarga") == 0){
        printf("%-6s %-15s %-15d %-15d %-15s\n",  
            car[i].kode, car[i].nama, car[i].harga_perhari, car[i].harga_perjam, car[i].kategori);
    }
}

    printf("---------------------------------------------------------------\n");
    printf("Tekan enter untuk kembali");
    getchar();
    getchar();
    mobil_keluarga();

}else if (pilih == 2) {
    char nama[50];
    int nama_sama = 0;
    FILE *ptr = fopen("mobil.txt", "r");

    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        getchar(); getchar();
        minibus();
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("\t\tCari Data Mobil\n");
    printf("============================================================\n");
    printf("Masukkan Nama Mobil yang ingin Dicari: ");
    scanf(" %[^\n]", nama);  

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) == 6) {
        if (strcmp(cek.nama, nama) == 0 && strcmp(cek.kategori, "Mobil Keluarga") == 0) {
            nama_sama = 1;
            printf("\nData Mobil Ditemukan:\n");
            printf("Kode       : %s\n", cek.kode);
            printf("Nama       : %s\n", cek.nama);
            printf("Plat       : %s\n", cek.plat);
            printf("Kategori   : %s\n", cek.kategori);
            printf("Harga/jam  : %d\n", cek.harga_perjam);
            printf("Harga/hari : %d\n", cek.harga_perhari);
            break;
        }
    }

    if (!nama_sama) {
        printf("\nData Mobil dengan nama %s Tidak Ditemukan.\n", nama);
    }
    fclose(ptr);
    printf("\nTekan Enter Untuk Kembali...");
    getchar();
    getchar();
    mobil_keluarga();

}else if (pilih == 3) {
    mobil_keluarga();
}

}else if (pilihan == 2){
    booking();
}else if (pilihan == 3){
    menu_pelanggan();
} 
    fclose(ptr);
}

void minibus(){
    int pilihan,pilih;
    FILE *ptr;
	ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\t\tPILIHAN MINIBUS\n");
    printf("============================================================\n\n");
    printf("Kode   Produk        Harga/Hari        Kategori    \n"); 
    printf("---------------------------------------------------------------\n");

     while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
        if (strcmp(cek.kategori, "Minibus") == 0){
            printf("%-6s %-15s %-15d %-15s\n",
                cek.kode, cek.nama, cek.harga_perhari, cek.kategori);
        }
    }
    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n");
    printf("3. Keluar\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);

    if (pilihan == 1){
        printf("1. Termurah\n");
        printf("2. Nama\n");
        printf("3. Keluar\n\n");
        printf("Input Pilihan Menu: ");
        scanf("%d",&pilih);

    if (pilih == 1) {
    mobil car[MAX_MOBIL];
    int count = 0;
    ptr = fopen("mobil.txt","r"); 
    if (ptr == NULL) {
        printf("File tidak bisa dibuka.\n");
        return;
    }
   while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
                  car[count].kode, car[count].nama, car[count].plat, car[count].kategori,
                  &car[count].harga_perjam, &car[count].harga_perhari) != EOF) {
                if (strcmp(car[count].kategori, "Minibus") == 0) {
                    count++;
                    if (count >= MAX_MOBIL) break;
                }
            }
    fclose(ptr);

    bubbleSort(car, count);

        system("cls");
        printf("============================================================\n");
        printf("\t\t\tPILIHAN MINIBUS\n");
        printf("============================================================\n\n");
        printf("Kode   Produk        Harga/Hari          Kategori    \n"); 
        printf("---------------------------------------------------------------\n");

   for (int i = 0; i < count; i++) {
    if (strcmp(car[i].kategori, "Minibus") == 0){
        printf("%-6s %-15s %-15d %-15s\n",  
            car[i].kode, car[i].nama, car[i].harga_perhari, car[i].kategori);
        }
    }

    printf("---------------------------------------------------------------\n");
    printf("Tekan enter untuk kembali");
    getchar();
    getchar();
    minibus();
}else if (pilih == 2) {
    char nama[50];
    int nama_sama = 0;
    FILE *ptr = fopen("mobil.txt", "r");

    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        getchar(); getchar();
        minibus();
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("\t\tCari Data Mobil\n");
    printf("============================================================\n");
    printf("Masukkan Nama Mobil yang ingin Dicari: ");
    scanf(" %[^\n]", nama);  

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) == 6) {
        if (strcmp(cek.nama, nama) == 0 && strcmp(cek.kategori, "Minibus") == 0) {
            nama_sama = 1;
            printf("\nData Mobil Ditemukan:\n");
            printf("Kode       : %s\n", cek.kode);
            printf("Nama       : %s\n", cek.nama);
            printf("Plat       : %s\n", cek.plat);
            printf("Kategori   : %s\n", cek.kategori);
            printf("Harga/hari : %d\n", cek.harga_perhari);
            break;
        }
    }

    if (!nama_sama) {
        printf("\nData Mobil dengan nama %s Tidak Ditemukan.\n", nama);
    }
    
    fclose(ptr);
    printf("\nTekan Enter Untuk Kembali...");
    getchar();  
    getchar();  
    minibus();

}else if (pilih == 3) {
    minibus();
}

}else if (pilihan == 2) {
    booking();
}else if (pilihan == 3) {
    menu_pelanggan();
        }
}

void bubbleSort(mobil car[], int n) {
    int i, j;
    mobil temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-1-i; j++) {
            if (car[j].harga_perhari > car[j+1].harga_perhari) {
                temp = car[j];
                car[j] = car[j+1];
                car[j+1] = temp;
            }
        }
    }
}

void booking(){
    pelanggan p;
    pesenan ps;
    int pilihan, hari, jam, found = 0;
    int pembayaran = 0; 
    FILE *ptr = fopen("datadiri.txt", "a+");
    if (ptr == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    FILE *sewa = fopen("Transaksi.txt", "a+");
    if (sewa == NULL) { 
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
        fclose(ptr);
        fclose(sewa);
     return;
    }

    while (fscanf(mobil, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t]\tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari) != EOF) {
    if (strcmp(cek.kode, p.kode_mobil) == 0) {
        found = 1;
        break;
    }
}

    if (!found) {
    printf("Kode mobil tidak ditemukan!\n");
    fclose(ptr);
    fclose(sewa);
    fclose(mobil);
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
     
        if (pilihan == 1){
            strcpy(ps.kategori_pesanan,"Harian  ");
            getchar(); 
            printf("Masukkan Jumlah Hari Sewa: ");
            scanf("%d", &hari);
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Tanggal Kembali (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_kembali);
            fprintf(ptr, "%s\t %lld\t%lld\t%s\t%s\n  \n", 
                    p.nama, p.hp, p.nik, p.alamat, p.kode_mobil);
            pembayaran = hari * cek.harga_perhari; 
            fprintf(sewa, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n\n", 
                    ps.kategori_pesanan, p.nama, p.kode_mobil, cek.nama, cek.plat, 
                    ps.tanggal_pergi, ps.tanggal_kembali, pembayaran);
        } else if (pilihan == 2 && strcmp(cek.kategori, "Mobil Keluarga") == 0){
            strcpy(ps.kategori_pesanan,"Perjam  ");
            getchar(); 
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Masukkan Jumlah Jam Sewa: ");
            scanf("%d", &jam);
            printf("Jam Pinjam (HH:MM): ");
            scanf("%s", ps.jam_pergi);
            printf("Jam Kembali (HH:MM): ");
            scanf("%s", ps.jam_kembali);
            fprintf(ptr, "%s\t %lld\t%lld\t%s\t%s\n  \n", 
                    p.nama, p.hp, p.nik, p.alamat, p.kode_mobil);
            pembayaran = jam * cek.harga_perjam; 
            fprintf(sewa, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n\n", 
                    ps.kategori_pesanan, p.nama, p.kode_mobil, cek.nama, cek.plat, 
                    ps.jam_pergi, ps.jam_kembali, pembayaran);
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
    } else if (pilihan == 2) {
        printf("Tanggal Pinjam  : %s\n", ps.tanggal_pergi);
        printf("Jam Pinjam      : %s\n", ps.jam_pergi);
        printf("Jam Kembali     : %s\n", ps.jam_kembali);
    }
    
    printf("Total Biaya     : Rp%d\n", pembayaran); 
    printf("============================================================\n");

    fclose(ptr);
    fclose(mobil);
    fclose(sewa);
    printf("\nTekan enter untuk kembali...");
    getchar(); 
    getchar();
    menu_pelanggan();
}
void laporan(){

}
void menu_laporan(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tLaporan\n");
    printf("============================================================\n\n");

    printf("Pilih Mobil:\n");
    printf("1. Laporan Data Mobil\n");
    printf("2. Laporan Data Pelanggan\n");
    printf("3. Laporan Peminjaman\n");
    printf("4. Laporan Transaksi\n\n");
    printf("5. Keluar\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
 if (pilihan == 1){
        L_mobil();
    }else if (pilihan == 2){
        data_pelanggan();
    }else if (pilihan == 3){
        
    }else if (pilihan == 4){
        
    }else if (pilihan == 5){
        menu_admin();
    }


}
void data_pelanggan(){
pelanggan p;
    mobil m;
    FILE *f_pelanggan, *f_mobil;
    char nama_mobil[50] = "-";
    int ditemukan;

    f_pelanggan = fopen("datadiri.txt", "r");
    if (f_pelanggan == NULL) {
        printf("File pelanggan tidak ditemukan.\n");
        return;
    }

    system("cls");
    printf("========================= Data Pelanggan ========================\n\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Nama           HP             NIK             Alamat                    Mobil yang Disewa\n");
    printf("---------------------------------------------------------------------------------------------\n");

    while (fscanf(f_pelanggan, "%[^\t]\t%lld\t%lld\t%[^\t]\t%[^\n]\n", 
                  p.nama, &p.hp, &p.nik, p.alamat, p.kode_mobil) != EOF) {
               
        f_mobil = fopen("mobil.txt", "r");
        if (f_mobil == NULL) {
            printf("File mobil tidak ditemukan.\n");
            fclose(f_pelanggan);
            return;
        }
        ditemukan = 0;
        while (fscanf(f_mobil, "%s\t%s\t%[^\t]\t%s\t%d\t%d\n", 
                      m.kode, m.kategori, m.nama, m.plat, &m.harga_perhari, &m.harga_perjam) != EOF) {
            if (strcmp(p.kode_mobil, m.kode) == 0) {
                strcpy(nama_mobil, m.nama);
                ditemukan = 1;
                break;
            }
        }
        
        if (!ditemukan) {
            strcpy(nama_mobil, "-");
        }

        printf("%-15s %-15lld %-15lld %-25s %-20s\n", 
               p.nama, p.hp, p.nik, p.alamat, nama_mobil);
    }
     printf("%s",p.kode_mobil);
    printf("---------------------------------------------------------------------------------------------\n");
    fclose(f_pelanggan);
    fclose(f_mobil);
    printf("Tekan enter untuk kembali...");
    getchar(); 
    getchar();
    kelola_mobil();
}
void L_mobil(){
      FILE *ptr;
    ptr = fopen("mobil.txt", "r");
    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }
    system("cls");
    printf("========================= Data Produk ========================\n\n");
    printf("------------------------------------------------------------------------------\n");
    printf("Kode   Produk          Harga/Hari      Harga/Jam        Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "Kode: %s\tNama: %[^\t]\tPlat: %[^\t] \tKategori: %[^\t]\tPerjam: %d\tPerhari: %d\n",
        car.kode, car.nama, car.plat, car.kategori, &car.harga_perjam, &car.harga_perhari) != EOF) {
        printf("%-6s %-15s %-15d %-8d %-15s\n",
        car.kode, car.nama, car.harga_perhari, car.harga_perjam, car.kategori);
    }

    printf("---------------------------------------------------------------\n");
    fclose(ptr);
    printf("Tekan enter untuk kembali");
    getchar(); 
    getchar();
    menu_laporan();

}
void L_pesanan_menu(){
     int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tLaporan Peminjaman\n");
    printf("============================================================\n\n");

    printf("Pilih Mobil:\n");
    printf("1. Peminjaman Harian\n");
    printf("2. Peminjaman  Perjam\n");
     printf("3. Seluruh Peminjaman\n");
    printf("4. Keluar\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
 if (pilihan == 1){
       
    }else if (pilihan == 2){
        
    }else if (pilihan == 3){
        menu_laporan();
    }
}
void L_transaksi(){
     int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tLaporan Transaksi\n");
    printf("============================================================\n\n");

    printf("Pilih Mobil:\n");
    printf("1. Transaksi Peminjaman Harian\n");
    printf("2. Transaksi Peminjaman  Perjam\n");
    printf("3. Seluruh Transaksi Peminjaman\n");
    printf("4. Keluar\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
 if (pilihan == 1){
       
    }else if (pilihan == 2){
        
    }else if (pilihan == 3){
       
    }else if (pilihan == 4){
        menu_laporan();
    }
}
