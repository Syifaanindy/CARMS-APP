#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>     
#include <conio.h>   
#include <ctype.h>

// tipe data bentukan 
typedef struct{
    char kode[20];
    char kategori[20];
    char nama[50];
    char plat[20];
    int harga_perhari;
    int harga_perjam;
    char status[50];
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
char nama_pelanggan[100]; 

}pesenan;

typedef struct{
    char un[20];
    char pass[20];
}akun;

// var global
mobil cek, car, baru,temp_mobil;

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

// pengambilan dan pemngembalian
void menu_ambilbalik();
void ambil();
void pengembalian();

// pelanggan
void mobil_keluarga();
void minibus();
void booking();
void ubah_status(char kode[20]);

//laporan
void menu_laporan();
void data_pelanggan();
void L_mobil();
void L_pesanan_menu();
void L_transaksi();
void L_peminjaman();

//laporan transaksi
void L_transaksi_harian();
void L_transaksi_perjam();
void L_transaksi_seluruh();

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
    printf("3. Ambil dan Pengembalian Mobil\n");
    printf("4. Keluar\n\n");

    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
    if (pilihan == 1){
        kelola_mobil();
    } else if (pilihan == 2){
        menu_laporan();
    } else if (pilihan == 3){
        menu_ambilbalik();
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
    printf("1. Lihat Data/Cari Mobil\n");
    printf("2. Input Data Mobil\n");
    printf("3. Update Data Mobil\n");
    printf("4. Hapus Data Mobil\n");
    printf("5. Keluar\n\n");

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
            edit();
            break;
        case 4:
            hapus();
            break;
        case 5:
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
    int kat;
    
    system("cls");
    
    do {
        kode_sama = 0;
        printf("Masukkan kode Mobil: ");
        scanf("%s", kode);

        rewind(ptr);
        while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s \n", 
               cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) != EOF) {
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

    strcpy(car.status, "Tersedia");

    do {
    printf("Kategori (1.Mobil Keluarga, 2.Minibus): ");
    scanf(" %d", &kat);

    if(kat == 1){
        strcpy(car.kategori, "Mobil Keluarga");
        printf("Harga/jam: ");
        scanf("%d", &car.harga_perjam);
    } else if (kat == 2){
        strcpy(car.kategori, "Minibus");
        car.harga_perjam = 0;  
    } else {
        printf("Pilihan tidak valid. Silakan coba lagi.\n");
    }
}while (kat < 1 || kat > 2);
    
    printf("Harga/hari: ");
    scanf("%d", &car.harga_perhari);

    
    
    fprintf(ptr, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
            car.kode, car.nama, car.plat, car.kategori,
            car.harga_perjam, car.harga_perhari,car.status);

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
        if (fold) fclose(fold);
        if (fnew) fclose(fnew);
        return;
    }

    system("cls");

    printf("=================================== Data Mobil ==================================\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-8s %-18s %-18s %-18s %-15s %-18s\n",
        "Kode", "Nama Mobil", "Harga Perjam", "Harga Perhari", "Kategori","Status"); 
    printf("----------------------------------------------------------------------------------\n");

    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        printf("%-8s %-18s %-18d %-18d %-15s %-18s\n",
            cek.kode, cek.nama, cek.harga_perjam, cek.harga_perhari, cek.kategori, cek.status);
    }

    printf("---------------------------------------------------------------------------------\n\n");
    
    printf("Masukkan Kode Mobil yang ingin dihapus: ");
    scanf("%s", kodetohapus);
    getchar();

    int ketemu = 0;

    rewind(fold); 

    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        if (strcmp(kodetohapus, cek.kode) != 0) {
            fprintf(fnew, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
                cek.kode, cek.nama, cek.plat, cek.kategori,
                cek.harga_perjam, cek.harga_perhari, cek.status);
        } else {
            ketemu = 1;
        }
    }

    fclose(fold);
    fclose(fnew);

    if (ketemu) {
        remove("mobil.txt");
        rename("mobil_new.txt", "mobil.txt");
        printf("Data mobil dengan kode %s berhasil dihapus.\n", kodetohapus);
    } else {
        remove("mobil_new.txt");
        printf("Kode mobil tidak ditemukan.\n");
    }

    system("cls");
    FILE *ptr = fopen("mobil.txt", "r");
    if (ptr != NULL) {
        printf("\n=================================== Data Mobil Terbaru ==================================\n\n");
        printf("---------------------------------------------------------------------------------\n");
        printf("%-8s %-18s %-18s %-18s %-15s %-18s\n",
            "Kode", "Nama Mobil", "Harga Perjam", "Harga Perhari", "Kategori","Status"); 
        printf("----------------------------------------------------------------------------------\n");
        while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                    cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
            printf("%-8s %-18s %-18d %-18d %-15s %-18s\n",
                cek.kode, cek.nama, cek.harga_perjam, cek.harga_perhari, cek.kategori, cek.status);
        }
        printf("---------------------------------------------------------------------------------\n");
        fclose(ptr);
    } else {
        printf("Gagal membuka file mobil.txt untuk menampilkan data terbaru.\n");
    }

    printf("\nTekan Enter untuk kembali...");
    getchar();
    kelola_mobil();
}

void lihat() {
    FILE *ptr;
    char kode_cari[20];
    int kode_sama = 0;
    ptr = fopen("mobil.txt", "r");
    
    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }

    system("cls");
    printf("=================================== Data Mobil ==================================\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-8s %-18s %-18s %-18s %-15s %-18s\n",
        "Kode", "Nama Mobil", "Harga Perjam", "Harga Perhari", "Kategori","Status"); 
    printf("----------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        printf("%-8s %-18s %-18d %-18d %-15s %-18s\n",
        cek.kode, cek.nama, cek.harga_perjam, cek.harga_perhari, cek.kategori, cek.status);
    }

    printf("---------------------------------------------------------------------------------\n\n");

    getchar();
    printf("Masukkan Kode Mobil yang ingin Dicari (Enter untuk skip): ");
    fgets(kode_cari, sizeof(kode_cari), stdin);
    kode_cari[strcspn(kode_cari, "\n")] = '\0';

    if (strlen(kode_cari) == 0) {
        fclose(ptr);
        kelola_mobil();
        return;  
    }

    rewind(ptr);
    while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",
         cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        if (strcmp(cek.kode, kode_cari) == 0) {
            kode_sama = 1;
            printf("\nData Mobil Ditemukan:\n");
            printf("Kode       : %s\n", cek.kode);
            printf("Nama       : %s\n", cek.nama);
            printf("Plat       : %s\n", cek.plat);
            printf("Kategori   : %s\n", cek.kategori);
            printf("Harga/jam  : %d\n", cek.harga_perjam);
            printf("Harga/hari : %d\n", cek.harga_perhari);
            printf("Status     : %s\n", cek.status);
            break;
        }
    }

    if (!kode_sama) {
        printf("\nData Mobil dengan Kode %s Tidak Ditemukan.\n", kode_cari);
    }
    
    fclose(ptr);
    printf("\nTekan Enter Untuk Kembali...");
    getchar(); 
    kelola_mobil();
}

void edit() {
    char kodetoedit[20];
    int kategori_baru;
    FILE *fold, *fnew;
    fold = fopen("mobil.txt", "r");
    fnew = fopen("mobil_new.txt", "w");
    if (!fold || !fnew) {
        printf("Gagal membuka file!\n");
        return;
    }
    system("cls");
    printf("=================================== Data Mobil ==================================\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-8s %-18s %-18s %-18s %-15s %-18s\n",
        "Kode", "Nama Mobil", "Plat", "Harga Perjam", "Harga Perhari", "Kategori", "Status");
    printf("----------------------------------------------------------------------------------\n");

    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
        cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        printf("%-8s %-18s %-18s %-18d %-15d %-18s %-18s\n",
            cek.kode, cek.nama, cek.plat, cek.harga_perjam, cek.harga_perhari, cek.kategori, cek.status);
    }

    printf("---------------------------------------------------------------------------------\n\n");

    printf("Masukkan Kode Mobil yang ingin diedit: ");
    scanf("%s", kodetoedit);
    getchar();

    rewind(fold); 
    int ketemu = 0;
    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
        cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        if (strcmp(kodetoedit, cek.kode) == 0) {
            ketemu = 1;
            printf("\nData ditemukan:\n");
            printf("Nama: %s\n", cek.nama);
            printf("Plat: %s\n", cek.plat);
            printf("Kategori: %s\n", cek.kategori);
            printf("Harga/jam saat ini: %d\n", cek.harga_perjam);
            printf("Harga/hari saat ini: %d\n", cek.harga_perhari);

            printf("Nama baru (Enter untuk skip): ");
            char temp[50];
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n') {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(cek.nama, temp);
            }

            printf("Plat baru (Enter untuk skip): ");
            fgets(temp, sizeof(temp), stdin);
            if (temp[0] != '\n') {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(cek.plat, temp);
            }

            do{
                printf("Kategori baru (0 untuk skip)\n 1. Mobil Keluarga\n 2. Minibus\n Pilih: ");
                scanf("%d", &kategori_baru);
                getchar();
                if (kategori_baru == 1) {
                    strcpy(cek.kategori, "Mobil Keluarga");
                    printf("Harga/jam baru (0 untuk skip): ");
                    int h_jam;
                    scanf("%d", &h_jam);
                    getchar();
                    if (h_jam != 0) cek.harga_perjam = h_jam;

                    printf("Harga/hari baru (0 untuk skip): ");
                    int h_hari;
                    scanf("%d", &h_hari);
                    getchar();
                    if (h_hari != 0) cek.harga_perhari = h_hari;

                } else if (kategori_baru == 2) {
                    strcpy(cek.kategori, "Minibus");
                    printf("Harga/hari baru (0 untuk skip): ");
                    int h_hari;
                    scanf("%d", &h_hari);
                    getchar();
                    if (h_hari != 0) cek.harga_perhari = h_hari;

                } else if (kategori_baru == 0) {
                    printf("Kategori tidak diubah.\n");
                } else {
                    printf("Pilihan tidak valid. Silahkan coba lagi.\n\n");
                }
            } while (kategori_baru < 0 || kategori_baru > 2);
        }

        fprintf(fnew, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
            cek.kode, cek.nama, cek.plat, cek.kategori, cek.harga_perjam, cek.harga_perhari, cek.status);
    }

    fclose(fold);
    fclose(fnew);

    if (ketemu) {
        remove("mobil.txt");
        rename("mobil_new.txt", "mobil.txt");
        printf("\nData berhasil tersimpan.\n");
        lihat();
        printf("\nTekan Enter untuk kembali...");
        getchar();
        kelola_mobil();
    } else {
        remove("mobil_new.txt");
        printf("Kode mobil tidak ditemukan.\n");
        printf("\nTekan Enter untuk kembali...");
        getchar();
        kelola_mobil();
    }
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
    if (pilihan == 1) {
        mobil_keluarga();
    } else if (pilihan == 2) {
        minibus();
    } else if (pilihan == 3){
        main();
}
}

void mobil_keluarga() {
    int pilihan, pilih;	
    FILE *ptr;
    ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\tPILIHAN MOBIL KELUARGA\n");
    printf("============================================================\n\n");
    printf("Kode   Produk          Harga/Hari      Harga/Jam          Kategori    \n"); 
    printf("------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
        cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        if (strcmp(cek.kategori, "Mobil Keluarga") == 0 && strcmp(cek.status, "Tersedia") == 0) {
            printf("%-6s %-15s %-15d %-15d %-15s\n",
                cek.kode, cek.nama, cek.harga_perhari, cek.harga_perjam, cek.kategori);
        }
    }
    fclose(ptr);

    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n");
    printf("3. Keluar\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);

    if (pilihan == 1) {
        printf("1. Urutkan dari yang Termurah\n");
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
           
            while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                car[count].kode, car[count].nama, car[count].plat, car[count].kategori,
                &car[count].harga_perjam, &car[count].harga_perhari, car[count].status) == 7) {
                if (strcmp(car[count].kategori, "Mobil Keluarga") == 0 && strcmp(car[count].status, "Tersedia") == 0) {
                    count++;
                    if (count >= MAX_MOBIL) break;
                }
            }
            fclose(ptr);

            bubbleSort(car, count);

            system("cls");
            printf("============================================================\n");
            printf("\t\tPILIHAN MOBIL KELUARGA (Termurah)\n");
            printf("============================================================\n\n");
            printf("Kode   Produk          Harga/Hari      Harga/Jam       Kategori    \n"); 
            printf("---------------------------------------------------------------\n");

            for (int i = 0; i < count; i++) {
                printf("%-6s %-15s %-15d %-15d %-15s\n",  
                    car[i].kode, car[i].nama, car[i].harga_perhari, car[i].harga_perjam, car[i].kategori);
            }

            printf("---------------------------------------------------------------\n");
            printf("Tekan enter untuk kembali");
            getchar();
            getchar();
            mobil_keluarga();

        } else if (pilih == 2) {
            
            char nama[50];
            int nama_sama = 0;
            ptr = fopen("mobil.txt", "r");
            if (ptr == NULL) {
                printf("File tidak ditemukan.\n");
                getchar(); getchar();
                mobil_keluarga();
                return;
            }

            system("cls");
            printf("============================================================\n");
            printf("\t\tCari Data Mobil\n");
            printf("============================================================\n");
            printf("Masukkan Nama Mobil yang ingin Dicari: ");
            scanf(" %[^\n]", nama);  

            //mengubah nama input ke huruf kecil
            for (int i = 0; nama[i]; i++) {
                nama[i] = tolower(nama[i]);
            }

            while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
                if (strcmp(cek.kategori, "Mobil Keluarga") == 0 && strcmp(cek.status, "Tersedia") == 0) {
                    char temp[50];
                    strcpy(temp, cek.nama);
                    for (int i = 0; temp[i]; i++) temp[i] = tolower(temp[i]);
                    if (strncmp(temp, nama, strlen(nama)) == 0) {
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
            }
            fclose(ptr);

            if (!nama_sama) {
                printf("\nData Mobil dengan nama %s Tidak Ditemukan.\n", nama);
            }
            printf("\nTekan Enter Untuk Kembali...");
            getchar(); getchar();
            mobil_keluarga();

        } else if (pilih == 3) {
            mobil_keluarga();
        }
    } else if (pilihan == 2) {
    booking("Mobil Keluarga");
    } else if (pilihan == 3) {
        menu_pelanggan();
    }
}

void minibus(){
    int pilihan,pilih;
    FILE *ptr;
    ptr = fopen("mobil.txt","r");

    system("cls");
    printf("============================================================\n");
    printf("\t\t\tPILIHAN MINIBUS\n");
    printf("============================================================\n\n");
    printf("Kode     Nama Mobil       Harga/Hari        Kategori    \n"); 
    printf("---------------------------------------------------------------\n");

    while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",
        cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        if (strcmp(cek.kategori, "Minibus") == 0 && strcmp(cek.status, "Tersedia") == 0){
            printf("%-6s %-15s %-15d %-15s\n",
                cek.kode, cek.nama, cek.harga_perhari, cek.kategori);
        }
    }
    fclose(ptr);

    printf("\nPilih:\n");
    printf("1. Cari Mobil\n");
    printf("2. Booking\n");
    printf("3. Keluar\n\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);

    if (pilihan == 1){
        printf("1. Urutkan Harga dari yang Termurah\n");
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
            while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",
                car[count].kode, car[count].nama, car[count].plat, car[count].kategori,
                &car[count].harga_perjam, &car[count].harga_perhari, car[count].status) == 7) {
                if (strcmp(car[count].kategori, "Minibus") == 0 && strcmp(car[count].status, "Tersedia") == 0) {
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
                printf("%-6s %-15s %-15d %-15s\n",  
                    car[i].kode, car[i].nama, car[i].harga_perhari, car[i].kategori);
            }

            printf("---------------------------------------------------------------\n");
            printf("Tekan enter untuk kembali");
            getchar();
            getchar();
            minibus();
        } else if (pilih == 2) {
            char nama[50];
            int nama_sama = 0;
            ptr = fopen("mobil.txt", "r");

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

            //mengubah nama input ke huruf kecil
            for (int i = 0; nama[i]; i++) {
                nama[i] = tolower(nama[i]);
            }

            while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%s\n",
                cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
                if (strcmp(cek.kategori, "Minibus") == 0 && strcmp(cek.status, "Tersedia") == 0) {
                    char temp[50];
                    strcpy(temp, cek.nama);
                    for (int i = 0; temp[i]; i++) temp[i] = tolower(temp[i]);
                    if (strncmp(temp, nama, strlen(nama)) == 0) {
                        nama_sama = 1;
                        printf("\nData Mobil Ditemukan:\n");
                        printf("Kode       : %s\n", cek.kode);
                        printf("Nama       : %s\n", cek.nama);
                        printf("Plat       : %s\n", cek.plat);
                        printf("Kategori   : %s\n", cek.kategori);
                        printf("Harga/jam  : %d\n", cek.harga_perjam);
                        printf("Harga/hari : %d\n", cek.harga_perhari);
                        printf("Status     : %s\n", cek.status);
                        break;
                    }
                }
            }

            fclose(ptr);

            if (!nama_sama) {
                printf("\nData Mobil dengan nama %s Tidak Ditemukan.\n", nama);
            }
            printf("\nTekan Enter Untuk Kembali...");
            getchar();  
            getchar();  
            minibus();

        } else if (pilih == 3) {
            minibus();
        }

    } else if (pilihan == 2) {
        booking("Minibus");
    } else if (pilihan == 3) {
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

void booking(const char* kategori_dipilih) {
    pelanggan p;
    pesenan ps;
    int pilihan, hari, jam, ketemu = 0;
    int pembayaran = 0; 
    FILE *ptr = fopen("datadiri.txt", "a+");
    FILE *pinjaman = fopen("pinjaman.txt", "a");
    FILE *sewa = fopen("Transaksi.txt", "a+");
    if (ptr == NULL || sewa == NULL || pinjaman == NULL) {
        printf("Gagal membuka file.\n");
        if (ptr) fclose(ptr);
        if (sewa) fclose(sewa);
        if (pinjaman) fclose(pinjaman);
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

    do {
        ketemu = 0;
        printf("Masukkan Kode Mobil: ");
        scanf("%s", p.kode_mobil);

        FILE *mobil = fopen("mobil.txt", "r");
        if (mobil == NULL) {
            printf("Gagal membuka file mobil.txt.\n");
            fclose(ptr);
            fclose(sewa);
            fclose(pinjaman);
            return;
        }

        while (fscanf(mobil, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
            cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
            if (
                strcmp(cek.kode, p.kode_mobil) == 0 &&
                strcmp(cek.status, "Tersedia") == 0 &&
                strcmp(cek.kategori, kategori_dipilih) == 0
            ) {
                ketemu = 1;
                break;
            }
        }
        fclose(mobil);

        if (!ketemu) {
            printf("\nKode mobil tidak ditemukan, sedang disewa, atau bukan kategori %s! Silakan masukkan lagi.\n\n", kategori_dipilih);
        }
    } while (!ketemu);

    system("cls");
    do {
        printf("===== Jadwal Booking ===== \n");
        printf("1. Perhari\n");
        if (strcmp(cek.kategori, "Mobil Keluarga") == 0) {
            printf("2. Perjam\n");
        }
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        int double_booking = 0;
        char line[256], kategori[20], nama_pelanggan[100], kode[20], nama_mobil[50], plat[20];
        char tgl_pergi[20], jam_pergi[20], jam_kembali[20], tgl_kembali[20], status[20];
        int total;
        FILE *fcek = fopen("Transaksi.txt", "r");

        if (pilihan == 1) {
            strcpy(ps.kategori_pesanan, "Harian");
            printf("Masukkan Jumlah Hari Sewa: ");
            scanf("%d", &hari);
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Tanggal Kembali (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_kembali);

            if (fcek != NULL) {
                while (fgets(line, sizeof(line), fcek)) {
                    int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                        kategori, nama_pelanggan, kode, nama_mobil, plat, tgl_pergi, tgl_kembali, &total, status);
                    if (baris == 9 && strcmp(kategori, "Harian") == 0 &&
                        strcmp(kode, p.kode_mobil) == 0 &&
                        strcmp(tgl_pergi, ps.tanggal_pergi) == 0 &&
                        (strcmp(status, "Belum Berjalan") == 0 || strcmp(status, "Disewa") == 0)) {
                        double_booking = 1;
                        break;
                    }
                }
                fclose(fcek);
            }
            if (double_booking) {
                printf("Maaf, mobil sudah dibooking pada tanggal tersebut!\n");
                fclose(ptr); fclose(sewa); fclose(pinjaman);
                printf("Tekan enter untuk kembali...");
                getchar(); getchar();
                menu_pelanggan();
                return;
            }

            fprintf(ptr, "%s\t%lld\t%lld\t%s\t%s\n", 
                p.nama, p.hp, p.nik, p.alamat, p.kode_mobil);

            pembayaran = hari * cek.harga_perhari;
            fprintf(sewa, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n", 
                ps.kategori_pesanan, p.nama, p.kode_mobil, cek.nama, cek.plat, 
                ps.tanggal_pergi, ps.tanggal_kembali, pembayaran, "Belum Berjalan");

        } else if (pilihan == 2 && strcmp(cek.kategori, "Mobil Keluarga") == 0) {
            strcpy(ps.kategori_pesanan, "Perjam");
            printf("Tanggal Pinjam (DD-MM-YYYY): ");
            scanf("%s", ps.tanggal_pergi);
            printf("Masukkan Jumlah Jam Sewa: ");
            scanf("%d", &jam);
            printf("Jam Pinjam (HH:MM): ");
            scanf("%s", ps.jam_pergi);
            printf("Jam Kembali (HH:MM): ");
            scanf("%s", ps.jam_kembali);

            if (fcek != NULL) {
                while (fgets(line, sizeof(line), fcek)) {
                    int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                        kategori, nama_pelanggan, kode, nama_mobil, plat, tgl_pergi, jam_pergi, jam_kembali, &total, status);
                    if (baris == 10 && strcmp(kategori, "Perjam") == 0 &&
                        strcmp(kode, p.kode_mobil) == 0 &&
                        strcmp(tgl_pergi, ps.tanggal_pergi) == 0 &&
                        strcmp(jam_pergi, ps.jam_pergi) == 0 &&
                        (strcmp(status, "Belum Berjalan") == 0 || strcmp(status, "Disewa") == 0)) {
                        double_booking = 1;
                        break;
                    }
                }
                fclose(fcek);
            }
            if (double_booking) {
                printf("Maaf, mobil sudah dibooking pada tanggal dan jam tersebut!\n");
                fclose(ptr); fclose(sewa); fclose(pinjaman);
                printf("Tekan enter untuk kembali...");
                getchar(); getchar();
                menu_pelanggan();
                return;
            }

            fprintf(ptr, "%s\t%lld\t%lld\t%s\t%s\n", 
                p.nama, p.hp, p.nik, p.alamat, p.kode_mobil);

            pembayaran = jam * cek.harga_perjam;
            fprintf(sewa, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n", 
                ps.kategori_pesanan, p.nama, p.kode_mobil, cek.nama, cek.plat, 
                ps.tanggal_pergi, ps.jam_pergi, ps.jam_kembali, pembayaran, "Belum Berjalan");
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
    fclose(sewa);
    fclose(pinjaman);

    printf("\nTekan enter untuk kembali...");
    getchar(); 
    getchar();
    menu_pelanggan();
}


void ubah_status(char kode_mobil[20]) {
    FILE *fold, *ftemp;
    mobil car;
    int ketemu = 0;

    fold = fopen("mobil.txt", "r");
    ftemp = fopen("temp.txt", "w");
    if (!fold || !ftemp) {
        printf("Gagal membuka file!\n");
        if (fold) fclose(fold);
        if (ftemp) fclose(ftemp);
        return;
    }

    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
        car.kode, car.nama, car.plat, car.kategori,
        &car.harga_perjam, &car.harga_perhari, car.status) == 7) {

        if (strcmp(kode_mobil, car.kode) == 0) {
            strcpy(car.status, "Disewa");
            ketemu = 1;
        }

        fprintf(ftemp, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
            car.kode, car.nama, car.plat, car.kategori,
            car.harga_perjam, car.harga_perhari, car.status);
    }

    fclose(fold);
    fclose(ftemp);

    if (ketemu) {
        remove("mobil.txt");
        rename("temp.txt", "mobil.txt");
    } else {
        remove("temp.txt");
        printf("Kode mobil %s tidak ditemukan.\n", kode_mobil);
    }
}

void menu_laporan(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tLaporan\n");
    printf("============================================================\n\n");

    printf("Pilih Menu:\n");
    printf("1. Laporan Data Mobil\n");
    printf("2. Laporan Data Pelanggan\n");
    printf("3. Laporan Peminjaman\n");
    printf("4. Laporan Transaksi\n");
    printf("5. Keluar\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
 if (pilihan == 1){
        L_mobil();
    }else if (pilihan == 2){
        data_pelanggan();
    }else if (pilihan == 3){
        L_peminjaman();
    }else if (pilihan == 4){
        L_transaksi();
    }else if (pilihan == 5){
        menu_admin();
    }
}
void data_pelanggan() {
    pelanggan p;
    mobil daftar_mobil[MAX_MOBIL];
    int jumlah_mobil = 0;
    FILE *f_pelanggan, *f_mobil;
    char nama_mobil[50], plat_mobil[20];
    int ditemukan;

    f_pelanggan = fopen("datadiri.txt", "r");
    if (f_pelanggan == NULL) {
        printf("File pelanggan tidak ditemukan.\n");
        return;
    }

    f_mobil = fopen("mobil.txt", "r");
    if (f_mobil == NULL) {
        printf("File mobil tidak ditemukan.\n");
        fclose(f_pelanggan);
        return;
    }

    while (fscanf(f_mobil, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                  daftar_mobil[jumlah_mobil].kode,
                  daftar_mobil[jumlah_mobil].nama,
                  daftar_mobil[jumlah_mobil].plat,
                  daftar_mobil[jumlah_mobil].kategori,
                  &daftar_mobil[jumlah_mobil].harga_perjam,
                  &daftar_mobil[jumlah_mobil].harga_perhari,
                  daftar_mobil[jumlah_mobil].status) == 7) {
        jumlah_mobil++;
        if (jumlah_mobil >= MAX_MOBIL) break;
    }
    fclose(f_mobil);

    system("cls");
    printf("========================= Data Pelanggan ========================\n\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Nama           HP             NIK             Alamat                    Mobil yang Disewa      Plat\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    while (fscanf(f_pelanggan, "%[^\t]\t%lld\t%lld\t%[^\t]\t%[^\n]\n", 
                  p.nama, &p.hp, &p.nik, p.alamat, p.kode_mobil) == 5) {

        ditemukan = 0;
        for (int i = 0; i < jumlah_mobil; i++) {
            if (strcmp(p.kode_mobil, daftar_mobil[i].kode) == 0) {
                strcpy(nama_mobil, daftar_mobil[i].nama);
                strcpy(plat_mobil, daftar_mobil[i].plat);
                ditemukan = 1;
                break;
            }
        }
        if (!ditemukan) {
            strcpy(nama_mobil, "-");
        }

        printf("%-15s %-15lld %-15lld %-25s %-20s %-10s\n", 
         p.nama, p.hp, p.nik, p.alamat, nama_mobil, plat_mobil);
    }   
      printf("----------------------------------------------------------------------------------------------------\n");
    fclose(f_pelanggan);
    printf("Tekan enter untuk kembali...");
    getchar(); 
    getchar();
    menu_laporan();
}

void L_mobil() {
    FILE *ptr;
    ptr = fopen("mobil.txt", "r");
    char kode_cari[20];
    int kode_sama = 0;
    if (ptr == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }
    system("cls");
    printf("=================================== Data Mobil ==================================\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-8s %-18s %-18s %-15s %-15s %-15s %-12s\n",
        "Kode", "Nama Mobil", "Plat", "Harga Perjam", "Harga Perhari", "Kategori", "Status");
    printf("---------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                 cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
        printf("%-8s %-18s %-18s %-15d %-15d %-15s %-12s\n",
            cek.kode, cek.nama, cek.plat, cek.harga_perjam, cek.harga_perhari, cek.kategori, cek.status);
    }

    printf("---------------------------------------------------------------------------------\n\n");
    fclose(ptr);

    printf("Masukkan Kode Mobil yang ingin dicari (Enter untuk skip): ");
    getchar();
    fgets(kode_cari, sizeof(kode_cari), stdin);
    kode_cari[strcspn(kode_cari, "\n")] = '\0';

    if (strlen(kode_cari) > 0) {
        ptr = fopen("mobil.txt", "r");
        if (ptr == NULL) {
            printf("File tidak ditemukan.\n");
            printf("Tekan enter untuk kembali...");
            getchar();
            menu_laporan();
            return;
        }
        while (fscanf(ptr, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                     cek.kode, cek.nama, cek.plat, cek.kategori, &cek.harga_perjam, &cek.harga_perhari, cek.status) == 7) {
            if (strcmp(cek.kode, kode_cari) == 0) {
                kode_sama = 1;
                printf("\nData Mobil Ditemukan:\n");
                printf("Kode       : %s\n", cek.kode);
                printf("Nama       : %s\n", cek.nama);
                printf("Plat       : %s\n", cek.plat);
                printf("Kategori   : %s\n", cek.kategori);
                printf("Harga/jam  : %d\n", cek.harga_perjam);
                printf("Harga/hari : %d\n", cek.harga_perhari);
                printf("Status     : %s\n", cek.status);
                break;
            }
        }
        fclose(ptr);
        if (!kode_sama) {
            printf("\nData Mobil dengan kode %s tidak ditemukan.\n", kode_cari);
        }
    }

    printf("\nTekan enter untuk kembali...");
    getchar();
    menu_laporan();
}

void L_pesanan_menu(){
     int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\t\t\tLaporan Peminjaman\n");
    printf("============================================================\n\n");

    printf("Pilih Menu:\n");
    printf("1. Peminjaman Harian\n");
    printf("2. Peminjaman  Perjam\n");
    printf("3. Seluruh Peminjaman\n");
    printf("4. Pengembalian\n");
    printf("5. Keluar\n");
    printf("Input Pilihan Menu: ");
    scanf("%d",&pilihan);
 if (pilihan == 1){
       
    }else if (pilihan == 2){
        
    }else if (pilihan == 3){
        menu_laporan();
    }else if (pilihan == 4){
        menu_laporan();
    }else if (pilihan == 5){
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
        L_transaksi_harian();
    }else if (pilihan == 2){
         L_transaksi_perjam();
    }else if (pilihan == 3){
        L_transaksi_seluruh();
    }else if (pilihan == 4){
        menu_laporan();
    }
}

void L_transaksi_harian() {
    pesenan p;
    FILE *f_transaksi;
    char status[20];
    int ada_data = 0;
    char line[256];

    system("cls");
    printf("========================= Laporan Transaksi Harian =========================\n\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Kategori   Kode Mobil   Nama Mobil        Plat         Tgl Pergi   Tgl Kembali   Total      Status\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    f_transaksi = fopen("Transaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.tanggal_kembali, &p.total_transaksi, status);
            if (baris == 9 && strstr(p.kategori_pesanan, "Harian") != NULL) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.tanggal_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    f_transaksi = fopen("RiwayatTransaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.tanggal_kembali, &p.total_transaksi, status);
            if (baris == 9 && strstr(p.kategori_pesanan, "Harian") != NULL && strcmp(status, "Selesai") == 0) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.tanggal_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    if (!ada_data) {
        printf("%-10s %-12s %-15s %-12s %-12s %-13s %-10s %-10s\n", "-", "-", "-", "-", "-", "-", "-", "-");
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tekan enter untuk kembali...");
    getchar();
    getchar();
    L_transaksi();
}

void L_transaksi_perjam() {
    pesenan p;
    FILE *f_transaksi;
    char status[20];
    int ada_data = 0;
    char line[256];

    system("cls");
    printf("========================= Laporan Transaksi Perjam =========================\n\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("Kategori   Kode Mobil   Nama Mobil        Plat         Tgl Pinjam   Jam Pergi   Jam Kembali   Total      Status\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    f_transaksi = fopen("Transaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi, status);
            if (baris == 10 && strstr(p.kategori_pesanan, "Perjam") != NULL) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-11s %-12s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.jam_pergi, p.jam_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    f_transaksi = fopen("RiwayatTransaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi, status);
            if (baris == 10 && strstr(p.kategori_pesanan, "Perjam") != NULL && strcmp(status, "Selesai") == 0) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-11s %-12s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.jam_pergi, p.jam_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    if (!ada_data) {
        printf("%-10s %-12s %-15s %-12s %-12s %-11s %-12s %-10s %-10s\n", "-", "-", "-", "-", "-", "-", "-", "-", "-");
    }

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("Tekan enter untuk kembali...");
    getch();
    getchar();
    L_transaksi();
}

void L_transaksi_seluruh() {
    pesenan p;
    FILE *f_transaksi;
    int ada_data = 0;
    char status[20];
    char line[256];

    system("cls");
    printf("========================= Seluruh Transaksi Peminjaman =========================\n\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Kategori   Kode Mobil   Nama Mobil        Plat         Tgl Pergi     Jam Pergi   Jam Kembali   Tgl Kembali   Total     Status\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");

    f_transaksi = fopen("Transaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi, status);
            if (baris == 10 && strstr(p.kategori_pesanan, "Perjam") != NULL) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-10s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.jam_pergi, p.jam_kembali, "-", p.total_transaksi, status);
                continue;
            }
            baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                         p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                         p.tanggal_pergi, p.tanggal_kembali, &p.total_transaksi, status);
            if (baris == 9 && strstr(p.kategori_pesanan, "Harian") != NULL) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-10s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, "-", "-", p.tanggal_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    f_transaksi = fopen("RiwayatTransaksi.txt", "r");
    if (f_transaksi != NULL) {
        while (fgets(line, sizeof(line), f_transaksi)) {
            int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                             p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                             p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi, status);
            if (baris == 10 && strstr(p.kategori_pesanan, "Perjam") != NULL && strcmp(status, "Selesai") == 0) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-10s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, p.jam_pergi, p.jam_kembali, "-", p.total_transaksi, status);
                continue;
            }
            baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                         p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, cek.nama, cek.plat,
                         p.tanggal_pergi, p.tanggal_kembali, &p.total_transaksi, status);
            if (baris == 9 && strstr(p.kategori_pesanan, "Harian") != NULL && strcmp(status, "Selesai") == 0) {
                ada_data = 1;
                printf("%-10s %-12s %-15s %-12s %-12s %-10s %-12s %-13s %-10d %-10s\n",
                       p.kategori_pesanan, p.kode_mobil, cek.nama, cek.plat,
                       p.tanggal_pergi, "-", "-", p.tanggal_kembali, p.total_transaksi, status);
            }
        }
        fclose(f_transaksi);
    }

    if (!ada_data) {
        printf("%-10s %-12s %-15s %-12s %-10s %-13s %-13s %-10s %-10s\n", "-", "-", "-", "-", "-", "-", "-", "-", "-");
    }

    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Tekan enter untuk kembali...");
    getch();
    getchar();
    L_transaksi();
}

void menu_ambilbalik(){
    int pilihan;
    system("cls");
    printf("============================================================\n");
    printf("\tMenu Ambil Mobil dan Pengembalian Mobil\n");
    printf("============================================================\n\n");

    do{
    printf("Pilih:\n");
    printf("1. Ambil Mobil\n");
    printf("2. Pengembalian Mobil\n");
    printf("3. Kembali\n");
    printf("Input Pilihan Menu: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        ambil();
    } else if (pilihan == 2) {
        pengembalian();
    } else if (pilihan == 3) {
        menu_admin();
    } else {
        printf("Pilihan tidak valid. Silakan coba lagi.");
        getchar();
        getchar();
        system("cls");
    }
} while (pilihan != 3);
}

void ambil() {
    pesenan p;
    char kode_mobil[20];
    char tanggal[20];
    char is_perjam;
    char jam_pergi_input[20];

    system("cls");
    printf("============================================================\n");
    printf("\t\tMenu Ambil Mobil\n");
    printf("============================================================\n\n");
    printf("Masukkan kode mobil: ");
    scanf("%19s", kode_mobil);
    printf("Masukkan tanggal pengambilan (DD-MM-YYYY): ");
    scanf("%19s", tanggal);
    printf("Apakah sewa per jam? (y/n): ");
    scanf(" %c", &is_perjam);

    if (is_perjam == 'y') {
        printf("Masukkan jam pergi (HH:MM): ");
        scanf("%19s", jam_pergi_input);
    }

    FILE *transaksiFile = fopen("Transaksi.txt", "r");
    if (transaksiFile == NULL) {
        printf("Gagal membuka file Transaksi.txt.\n");
        printf("Tekan Enter untuk kembali...");
        getchar(); getchar();
        return;
    }

    int ketemu = 0;
    char line[256];
    char nama_pelanggan[100], kode[20];
    char tgl_pergi[20], jam_pergi[20], jam_kembali[20], tgl_kembali[20], status[20];
    int total;

    while (fgets(line, sizeof(line), transaksiFile)) {
        int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, jam_pergi, jam_kembali, &total, status);

        if (baris == 10 && strcmp(kode, kode_mobil) == 0 && strcmp(tgl_pergi, tanggal) == 0 &&
            ((is_perjam == 'y' && strcmp(jam_pergi, jam_pergi_input) == 0) || (is_perjam != 'y')) &&
            strcmp(status, "Belum Berjalan") == 0) {
            ketemu = 1;
            strcpy(cek.kode, kode);
            break;
        }

        baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, tgl_kembali, &total, status);
        if (baris == 9 && strcmp(kode, kode_mobil) == 0 && strcmp(tgl_pergi, tanggal) == 0 &&
            is_perjam != 'y' && strcmp(status, "Belum Berjalan") == 0) {
            ketemu = 1;
            strcpy(cek.kode, kode);
            break;
        }
    }
    fclose(transaksiFile);

    if (!ketemu) {
        printf("Tidak ada bookingan untuk kode mobil %s pada tanggal %s", kode_mobil, tanggal);
        if(is_perjam == 'y') {
            printf(" dan jam pergi %s", jam_pergi_input);
        }
        printf(".\nTekan Enter untuk kembali...");
        getchar(); getchar();
        menu_admin();
        return;
    }

    ubah_status(kode_mobil);

    FILE *fold = fopen("Transaksi.txt", "r");
    FILE *fnew = fopen("Transaksi_new.txt", "w");
    if (!fold || !fnew) {
        printf("Gagal membuka file transaksi!\n");
        if (fold) fclose(fold);
        if (fnew) fclose(fnew);
        printf("Tekan Enter untuk kembali...");
        getchar(); getchar();
        menu_admin();
        return;
    }
    while (fgets(line, sizeof(line), fold)) {
        int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, jam_pergi, jam_kembali, &total, status);

        if (baris == 10 && strcmp(kode, kode_mobil) == 0 && strcmp(tgl_pergi, tanggal) == 0 &&
            ((is_perjam == 'y' && strcmp(jam_pergi, jam_pergi_input) == 0) || (is_perjam != 'y')) &&
            strcmp(status, "Belum Berjalan") == 0) {
            fprintf(fnew, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
                cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, jam_pergi, jam_kembali, total, "Disewa");
        } else {
            baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
                cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, tgl_kembali, &total, status);
            if (baris == 9 && strcmp(kode, kode_mobil) == 0 && strcmp(tgl_pergi, tanggal) == 0 &&
                is_perjam != 'y' && strcmp(status, "Belum Berjalan") == 0) {
                fprintf(fnew, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
                    cek.kategori, nama_pelanggan, kode, cek.nama, cek.plat, tgl_pergi, tgl_kembali, total, "Disewa");
            } else {
                fputs(line, fnew);
            }
        }
    }
    fclose(fold);
    fclose(fnew);
    remove("Transaksi.txt");
    rename("Transaksi_new.txt", "Transaksi.txt");

    printf("Status mobil dengan kode %s telah diubah menjadi 'Disewa'.\n", kode_mobil);
    printf("Tekan Enter untuk kembali...");
    getchar(); getchar();
    menu_admin();
}

void pengembalian() {
    char kode_mobil[20];
    int ketemu = 0;
    mobil car;

    system("cls");
    printf("============================================================\n");
    printf("\tMenu Pengembalian Mobil\n");
    printf("============================================================\n\n");
    printf("Masukkan kode mobil yang akan dikembalikan: ");
    scanf("%19s", kode_mobil);

    FILE *ftrans = fopen("Transaksi.txt", "r");
pesenan p;
char line[256];
int ketemu_trans = 0;
char jam_kembali_sebenarnya[10];
int denda = 0, keterlambatan = 0;
char transaksi_line[256];

while (fgets(line, sizeof(line), ftrans)) {
 
    int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d",
        p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, car.nama, car.plat,
        p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi);
    if (baris == 9 && strcmp(p.kode_mobil, kode_mobil) == 0 && strcmp(p.kategori_pesanan, "Perjam") == 0) {
        ketemu_trans = 1;
        strcpy(transaksi_line, line);
        break;
    }
   
    baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%d",
        p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, car.nama, car.plat,
        p.tanggal_pergi, &p.total_transaksi);
    if (baris == 7 && strcmp(p.kode_mobil, kode_mobil) == 0 && strcmp(p.kategori_pesanan, "Harian") == 0) {
        ketemu_trans = 2;
        strcpy(transaksi_line, line);
        break;
    }
}
fclose(ftrans);

if (!ketemu_trans) {
    printf("Data transaksi tidak ditemukan untuk kode mobil %s.\n", kode_mobil);
    printf("Tekan Enter untuk kembali...");
    getchar(); getchar();
    menu_admin();
    return;
}

    printf("Masukkan jam pengembalian sebenarnya (HH:MM): ");
    scanf("%s", jam_kembali_sebenarnya);

    if (strcmp(p.kategori_pesanan, "Perjam") == 0) {
        int jam_kembali, menit_kembali, jam_sebenarnya, menit_sebenarnya;
        sscanf(p.jam_kembali, "%d:%d", &jam_kembali, &menit_kembali);
        sscanf(jam_kembali_sebenarnya, "%d:%d", &jam_sebenarnya, &menit_sebenarnya);

        int total_menit_kembali = jam_kembali * 60 + menit_kembali;
        int total_menit_sebenarnya = jam_sebenarnya * 60 + menit_sebenarnya;

        if (total_menit_sebenarnya > total_menit_kembali) {
            keterlambatan = (total_menit_sebenarnya - total_menit_kembali + 59) / 60; 
            denda = (int)(0.1 * p.total_transaksi) * keterlambatan;
            printf("Terlambat %d jam. Denda: Rp%d\n", keterlambatan, denda);
        } else {
            printf("Tidak ada keterlambatan.\n");
        }
    }

    FILE *fold = fopen("mobil.txt", "r");
    FILE *fnew = fopen("mobil_new.txt", "w");
    if (!fold || !fnew) {
        printf("Gagal membuka file!\n");
        if (fold) fclose(fold);
        if (fnew) fclose(fnew);
        return;
    }

    while (fscanf(fold, "%s\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                  car.kode, car.nama, car.plat, car.kategori,
                  &car.harga_perjam, &car.harga_perhari, car.status) == 7) {
        if (strcmp(kode_mobil, car.kode) == 0 && strcmp(car.status, "Disewa") == 0) {
            strcpy(car.status, "Tersedia");
            ketemu = 1;
        }
        fprintf(fnew, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
                car.kode, car.nama, car.plat, car.kategori,
                car.harga_perjam, car.harga_perhari, car.status);
    }
    fclose(fold);
    fclose(fnew);

    if (ketemu) {
    remove("mobil.txt");
    rename("mobil_new.txt", "mobil.txt");
    printf("Mobil dengan kode %s berhasil dikembalikan dan status diubah menjadi 'Tersedia'.\n", kode_mobil);
} else {
    remove("mobil_new.txt");
    printf("Kode mobil tidak ditemukan atau mobil tidak sedang disewa.\n");
    printf("Tekan Enter untuk kembali...");
    getchar(); getchar();
    menu_admin();
    return; 
}

    FILE *ftrans_old = fopen("Transaksi.txt", "r");
    FILE *ftrans_new = fopen("Transaksi_new.txt", "w");
    FILE *friwayat = fopen("RiwayatTransaksi.txt", "a");
    if (!ftrans_old || !ftrans_new || !friwayat) {
        printf("Gagal membuka file transaksi/riwayat!\n");
        if (ftrans_old) fclose(ftrans_old);
        if (ftrans_new) fclose(ftrans_new);
        if (friwayat) fclose(friwayat);
        printf("Tekan Enter untuk kembali...");
        getchar(); getchar();
        menu_admin();
        return;
    }

    while (fgets(line, sizeof(line), ftrans_old)) {
    pesenan temp;
    char temp_nama[50], temp_plat[20], temp_jam_pergi[20], temp_jam_kembali[20], temp_tgl_kembali[20], temp_status[20];
    int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
        temp.kategori_pesanan, temp.nama_pelanggan, temp.kode_mobil, temp_nama, temp_plat,
        temp.tanggal_pergi, temp_jam_pergi, temp_jam_kembali, &temp.total_transaksi, temp_status);

    if (baris == 10 && strcmp(temp.kode_mobil, kode_mobil) == 0 && strcmp(temp.kategori_pesanan, "Perjam") == 0) {
       
        fprintf(friwayat, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
            temp.kategori_pesanan, temp.nama_pelanggan, temp.kode_mobil, temp_nama, temp_plat,
            temp.tanggal_pergi, temp_jam_pergi, temp_jam_kembali, temp.total_transaksi, "Selesai");
      
    }
   
    else {
        baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            temp.kategori_pesanan, temp.nama_pelanggan, temp.kode_mobil, temp_nama, temp_plat,
            temp.tanggal_pergi, temp_tgl_kembali, &temp.total_transaksi, temp_status);
        if (baris == 9 && strcmp(temp.kode_mobil, kode_mobil) == 0 && strcmp(temp.kategori_pesanan, "Harian") == 0) {
           
            fprintf(friwayat, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
                temp.kategori_pesanan, temp.nama_pelanggan, temp.kode_mobil, temp_nama, temp_plat,
                temp.tanggal_pergi, temp_tgl_kembali, temp.total_transaksi, "Selesai");
         
        } else {
            fputs(line, ftrans_new);
        }
    }
}
    fclose(ftrans_old);
    fclose(ftrans_new);
    fclose(friwayat);
    remove("Transaksi.txt");
    rename("Transaksi_new.txt", "Transaksi.txt");

    printf("Tekan Enter untuk kembali...");
    getchar(); getchar();
    menu_admin();
}


void L_peminjaman() {
    pesenan p;
    FILE *f_transaksi, *f_pelanggan;
    int bulan, tahun;
    int total_pendapatan = 0;
    char nama_pelanggan[100];
    pelanggan pl;
    int ditemukan_pelanggan;
    char status[20];
    char line[256];

    printf("Masukkan bulan (1-12): ");
    scanf("%d", &bulan);
    fflush(stdin);
    printf("Masukkan tahun: ");
    scanf("%d", &tahun);
    fflush(stdin);

    f_transaksi = fopen("RiwayatTransaksi.txt", "r");
    if (f_transaksi == NULL) {
        printf("File RiwayatTransaksi.txt tidak ditemukan.\n");
        return;
    }

    system("cls");
    printf("========================= Laporan Peminjaman Bulanan =========================\n\n");
    printf("Bulan: %d, Tahun: %d\n\n", bulan, tahun);
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    printf("Kategori   Nama Pelanggan   Kode Mobil   Nama Mobil        Tgl Pergi   Tgl/Jam Kembali   Total Biaya\n");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), f_transaksi)) {
        int baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, car.nama, car.plat,
            p.tanggal_pergi, p.jam_pergi, p.jam_kembali, &p.total_transaksi, status);
        if (baris == 10 && strcmp(status, "Selesai") == 0) {
            int bulanTransaksi, tahunTransaksi;
            sscanf(p.tanggal_pergi, "%*2d-%2d-%4d", &bulanTransaksi, &tahunTransaksi);
            if (bulanTransaksi == bulan && tahunTransaksi == tahun) {
                f_pelanggan = fopen("datadiri.txt", "r");
                strcpy(nama_pelanggan, p.nama_pelanggan);
                if (f_pelanggan != NULL) {
                    ditemukan_pelanggan = 0;
                    while (fscanf(f_pelanggan, "%[^\t]\t%lld\t%lld\t%[^\t]\t%[^\n]\n",
                        pl.nama, &pl.hp, &pl.nik, pl.alamat, pl.kode_mobil) == 5) {
                        if (strcmp(p.kode_mobil, pl.kode_mobil) == 0) {
                            strcpy(nama_pelanggan, pl.nama);
                            ditemukan_pelanggan = 1;
                            break;
                        }
                    }
                    fclose(f_pelanggan);
                }
                printf("%-10s %-16s %-12s %-15s %-11s %-13s %-10d\n",
                    p.kategori_pesanan, nama_pelanggan, p.kode_mobil, car.nama,
                    p.tanggal_pergi, p.jam_kembali, p.total_transaksi);
                total_pendapatan += p.total_transaksi;
            }
            continue;
        }
       
        baris = sscanf(line, "%19[^\t]\t%99[^\t]\t%19[^\t]\t%49[^\t]\t%19[^\t]\t%19[^\t]\t%19[^\t]\t%d\t%19[^\n]",
            p.kategori_pesanan, p.nama_pelanggan, p.kode_mobil, car.nama, car.plat,
            p.tanggal_pergi, p.tanggal_kembali, &p.total_transaksi, status);
        if (baris == 9 && strcmp(status, "Selesai") == 0) {
            int bulanTransaksi, tahunTransaksi;
            sscanf(p.tanggal_pergi, "%*2d-%2d-%4d", &bulanTransaksi, &tahunTransaksi);
            if (bulanTransaksi == bulan && tahunTransaksi == tahun) {
                f_pelanggan = fopen("datadiri.txt", "r");
                strcpy(nama_pelanggan, p.nama_pelanggan);
                if (f_pelanggan != NULL) {
                    ditemukan_pelanggan = 0;
                    while (fscanf(f_pelanggan, "%[^\t]\t%lld\t%lld\t%[^\t]\t%[^\n]\n",
                        pl.nama, &pl.hp, &pl.nik, pl.alamat, pl.kode_mobil) == 5) {
                        if (strcmp(p.kode_mobil, pl.kode_mobil) == 0) {
                            strcpy(nama_pelanggan, pl.nama);
                            ditemukan_pelanggan = 1;
                            break;
                        }
                    }
                    fclose(f_pelanggan);
                }
                printf("%-10s %-16s %-12s %-15s %-11s %-13s %-10d\n",
                    p.kategori_pesanan, nama_pelanggan, p.kode_mobil, car.nama,
                    p.tanggal_pergi, p.tanggal_kembali, p.total_transaksi);
                total_pendapatan += p.total_transaksi;
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    printf("Total Pendapatan: %d\n", total_pendapatan);
    fclose(f_transaksi);
    printf("Tekan enter untuk kembali...");
    getchar(); getchar();
    menu_laporan();
}
