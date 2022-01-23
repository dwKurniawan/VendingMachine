#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

int menu;
int jumlah;
int bayar;
bool i = false;
char lagi;

fstream data_pembelian;

struct produk
{
    string merek;
    int harga{};
};

void draw_hline(int len) {
    for (int i = 0; i < len; ++i)
        cout << char(196);
    cout << endl;
}


void listmenu() {
    //LIST MENU
    cout << " ______________________________________ " << endl;
    cout << "|           Vending Machine            |" << endl;
    cout << "|______________________________________|" << endl;
    cout << "|     Menu              |      Harga   |" << endl;
    cout << "|                       |              |" << endl;
    cout << "|   1. Coca-Cola        |  Rp.  4.000  |" << endl;
    cout << "|   2. Pepsi            |  Rp.  4.000  |" << endl;
    cout << "|   3. Air Mineral      |  Rp.  2.000  |" << endl;
    cout << "|   4. Kopi Good Day    |  Rp.  5.000  |" << endl;
    cout << "|   5. Fanta            |  Rp.  4.000  |" << endl;
    cout << "|   6. Mizone           |  Rp.  4.000  |" << endl;
    cout << "|   0. Exit Menu        |              |" << endl;
    cout << "|______________________________________|" << endl;
}


void hitungstruk(int menu, int total) {
    //ISI DATA LIST MENU
    produk drink[7];
    drink[0] = { "Exit Menu",0 };
    drink[1] = { "Coca-Cola",4000 };
    drink[2] = { "Pepsi",4000 };
    drink[3] = { "Air Mineral",2000 };
    drink[4] = { "Kopi Good day",5000 };
    drink[5] = { "Fanta",4000 };
    drink[6] = { "Mizone",4000 };

    //MENCATAT DATA PEMBELIAN
    data_pembelian.open("data1.txt", ios::app);
    data_pembelian << '|' << setw(13) << drink[menu].merek << '|' << setw(15) << jumlah << '|' << setw(20) << total << '|' << endl;
    data_pembelian.close();
}

void sangkyu() {
    draw_hline(54);
    cout << setw(32) << "Terima Kasih\n" << endl;
    cout << setw(43) << "Telah Menggunakan Layanan Kami :)" << endl;
    draw_hline(54);
}

void struk() {
    //TAMPILKAN STRUK PEMBELIAN
    cout << "=====================================================\n";
    cout << "\t\tSTRUK PEMBELIAN ANDA\n";
    cout << "=====================================================";

    data_pembelian.open("data1.txt", ios::app);
    //TAMBAHKAN "==== " SEBAGAI BATAS AKHIR LOOPING STRUK
    data_pembelian << "===================================================== ";
    data_pembelian.close();

    //VARIABEL LOOPING STRUK
    int databool = false;
    string data1, struk;

    data_pembelian.open("data1.txt");

    //MENYUSUN STRUK DATA
    while (!databool) {
        getline(data_pembelian, struk); //membaca "data1.txt dan memasukKannya ke struk
        data1.append("\n" + struk); //menambah dan memasuKkan isi "struk" ke "data1"

        //lakukan perulangan hingga bertemu "===== "
        if (struk == "===================================================== ") {
            databool = true;
        }
    }
    //TAMPILKAN STRUK
    cout << data1 << endl;

    cout << "\n" << endl;
    
    draw_hline(54);
    cout << setw(32) << "Terima Kasih\n" << endl;
    cout << setw(43) << "Telah Menggunakan Layanan Kami :)" << endl;
    draw_hline(54);

   system("pause");
}


int main() {
    //ISI DATA LIST MENU
    produk drink[7];
    drink[0] = { "Exit Menu",0 };
    drink[1] = { "Coca-Cola",4000 };
    drink[2] = { "Pepsi",4000 };
    drink[3] = { "Air Mineral",2000 };
    drink[4] = { "Kopi Good day",5000 };
    drink[5] = { "Fanta",4000 };
    drink[6] = { "Mizone",4000 };

    data_pembelian.open("data1.txt", ios::out);
    data_pembelian << '|' << setw(13) << "Menu" << '|' << setw(15) << "Jumlah" << '|' << setw(20) << "Harga" << '|' << "\n|-------------|---------------|--------------------| \n";
    data_pembelian.close();

    while (i = true) {
        //MEMANGGIL LIST MENU
        listmenu();

        //MENU PEMBELIAN
        cout << "PILIH MENU\t  : ";
        cin >> menu;
        cout << "MENU\t\t  : " << drink[menu].merek << endl;
        cout << "HARGA\t\t  : Rp. " << drink[menu].harga << endl;

        if ((menu == 0) && (bayar >= 1)) {
            system("cls");

            struk();

            Sleep(2000);
            return 0;
        }
        else if ((menu == 0) && (bayar == 0)) {
            system("cls");

            sangkyu();
            
            Sleep(2000);
            return 0;
        }

        cout << "JUMLAH PEMBELIAN  : ";
        cin >> jumlah;

        //MENGHITUNG HARGA TOTAL PEMBELIAN
        int total = drink[menu].harga * jumlah;

        //TAMMPILKAN HARGA TOTAL PEMBELIAN
        cout << "\nTOTAL HARGA PEMBELIAN   : Rp. " << total << endl;
        cout << "NOMINAL YANG DIBAYARKAN : Rp. ";
        cin >> bayar; //INPUT PEMBAYARAN

        //MEMERIKSA JUMLAH UANG YANG MASUK UNTUK PEMBAYARAN
        if (bayar < total) {
            cout << "NOMINAL TIDAK CUKUP";
            Sleep(1000);
            system("cls");
            i  = true;
        }
        else if (bayar > total) {
            int kembalian = bayar - total;
            cout << "KEMBALIAN : Rp.  " << kembalian << "\n" << endl;

            Sleep(1000);

            cout << "\nV SILAHKAN AMBIL PESANAN ANDA ^^ V\n";

            //MEMANGGIL "hitung struk" UNTUK MENCATAT DATA PEMBELIAN
            hitungstruk(menu, total);

            Sleep(1500);

            //MENANYAKAN APAKAH INGIN MEMBELI LAGI
            cout << "\nAPAKAH INGIN MEMBELI LAGI? (y/n) ";
            cin >> lagi;
        }
        else if (bayar == total) {
            //MEMANGGIL "hitung struk" UNTUK MENCATAT DATA PEMBELIAN
            hitungstruk(menu, total);

            cout << "\nV SILAHKAN AMBIL PESANAN ANDA ^^ V\n";
            Sleep(1500);

            //MENANYAKAN APAKAH INGIN MEMBELI LAGI
            cout << "\nAPAKAH INGIN BELI LAGI? (y/n) ";
            cin >> lagi;
        };

        //PILIHAN UNTUK MENGULANG PEMBELIAN
        if (lagi == 'y') {
            system("cls"); //jika ya, maka clear program dan perulangan
            i = true;
        }
        else if (lagi == 'n') {
            system("cls"); //jika no, clear program dan tampilkan struk pembelian
            struk();
            return 0;
        }
    }
}