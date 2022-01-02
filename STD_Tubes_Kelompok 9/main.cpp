#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "event.h"
#include "peserta.h"

using namespace std;

int main()
{
    listEvent events;
    listPeserta pesertaList;
    adrEvent E;
    adrPeserta P;
    infotypeEvent inputEvent;
    infotypePeserta inputPeserta;

    createListEvent(events);
    createListPeserta(pesertaList);

    int pilihan = menu();
    /**
    cout<<"===============> MENU <==============="<<endl;
    cout<<"[1]  Tambahkan Event"<<endl;
    cout<<"[2]  Tambahkan Peserta"<<endl;
    cout<<"[3]  Menambahkan seorang peserta ke sebuah event"<<endl;
    cout<<"[4]  Menampilkan jumlah peserta semua event"<<endl;
    cout<<"[5]  Menampilkan data peserta di event tertentu"<<endl;
    cout<<"[6]  Menampilkan semua event dengan data pesertanya"<<endl;
    cout<<"[7]  Mencari event tertentu dengan kuota yang masih tersedia"<<endl;
    cout<<"[8]  Mencari peserta tertentu pada sebuah event"<<endl;
    cout<<"[9]  Menghapus peserta dari event tertentu"<<endl;
    cout<<"[10] Menghapus data peserta dari sistem"<<endl;
    cout<<"[11] Menghapus event dengan peserta berjumlah 0"<<endl;
    cout<<"[0] Exit"<<endl;
    **/

    while(pilihan != 0){
        switch(pilihan){
        case 1:
        {
            inputEvent = createNewEvent();
            E = newElmEvent(inputEvent);
            insertLastEvent(events,E);
            cout<<"SUKSES!"<<endl;
            getch();
            system("cls");
            break;
        }
        case 2:
        {
            inputPeserta = createPeserta();
            P = newElmPeserta(inputPeserta);
            insertLastPeserta(pesertaList,P);
            cout<<"SUKSES!"<<endl;
            getch();
            system("cls");
            break;
        }

        case 3:
        {
            string inputNamaPeserta;
            cout<<"Berikut adalah list Peserta: "<<endl;
            showListPeserta(pesertaList);
            if (first(pesertaList) != nil){
                cout<<"Masukkan nama Peserta: ";
                cin>>inputNamaPeserta;
                adrPeserta pesertaEvent = findPeserta(pesertaList,inputNamaPeserta);
                if (pesertaEvent != nil){
                    joinEvent(events,pesertaEvent);
                    showjumlahPesertasemuaEvent(events);
                }else{
                    cout<<"Peserta tidak ada dalam listPeserta. Registrasilah dulu!"<<endl;
                }
                cout<<"SUKSES!"<<endl;
            }
            getch();
            system("cls");
            break;
        }
        case 4:
            {
                showjumlahPesertasemuaEvent(events);
                getch();
                system("cls");
                break;
            }
        case 5:
            {
                string inputNamaEvent;
                cout<<"Masukkan nama event yang akan ditampilkan data pesertanya: ";
                cin>>inputNamaEvent;
                E = findEvent(events,inputNamaEvent);
                if (E == nil){
                    cout<<"Event tersebut tidak ada dalam listEvent!"<<endl;
                }else{
                    showAlldataEventTertentu(events,E);
                }
                getch();
                system("cls");
                break;
            }
        case 6:
            {
                showAlldataEvent(events);
                getch();
                system("cls");
                break;
            }
        case 7:
            {
                showEventTersedia(events);
                getch();
                system("cls");
                break;
            }
        case 8:
            {
                adrEvent cariEvent;
                adrPeserta cariPeserta;
                string inputNamaPeserta, inputNamaEvent;
                cout<<"Masukkan nama peserta : ";
                cin>>inputNamaPeserta;
                cout<<"Masukkan nama event: ";
                cin>>inputNamaEvent;
                cariEvent = findEvent(events,inputNamaEvent);
                if (cariEvent != nil){
                    cariPeserta = findPeserta(peserta(cariEvent),inputNamaPeserta);
                    if (cariPeserta != nil){
                        cout<<inputNamaPeserta<<" terdaftar di "<<info(cariEvent).namaEvent<<endl;
                    }else{
                        cout<<inputNamaPeserta<<" tidak terdaftar di "<<info(cariEvent).namaEvent<<endl;
                    }
                }else{
                    cout<<"Event tidak ada!"<<endl;
                }
                getch();
                system("cls");
                break;
            }
        case 9:
            {
                adrEvent cariEvent;
                adrPeserta cariPeserta,dataHapus;
                string inputNamaPeserta, inputNamaEvent,mau;
                cout<<"Masukkan nama peserta : ";
                cin>>inputNamaPeserta;
                cout<<"Masukkan nama event: ";
                cin>>inputNamaEvent;
                cariEvent = findEvent(events,inputNamaEvent);
                if (cariEvent != nil){
                    cariPeserta = findPeserta(peserta(cariEvent),inputNamaPeserta);
                    if (cariPeserta != nil){
                        cout<<inputNamaPeserta<<" terdaftar di "<<info(cariEvent).namaEvent<<endl;
                        cout<<"Apakah yakin ingin menghapus "<<inputNamaPeserta<<" dari "<<info(cariEvent).namaEvent<<"? (y/t) ";
                        cin>>mau;
                        if (mau == "y" || mau == "Y"){
                            deletePesertaEventTertentu(events,inputNamaEvent,inputNamaPeserta,dataHapus);
                        }
                    }else{
                        cout<<inputNamaPeserta<<" tidak terdaftar di "<<info(cariEvent).namaEvent<<endl;
                    }
                }else{
                    cout<<"Event tidak ada!"<<endl;
                }
                getch();
                system("cls");
                break;
            }
        case 10:
            {
                string inputNamaPeserta;
                adrPeserta hapus;
                cout<<"Masukkan nama peserta yang akan dihapus dari semua event/sistem: ";
                cin>>inputNamaPeserta;
                deletePeserta(pesertaList,inputNamaPeserta,hapus);
                deletePesertaDiSemuaEvent(events,inputNamaPeserta);
                cout<<"Peserta "<<info(hapus).namaPeserta<<" sudah dihapus dari sistem"<<endl;
                getch();
                system("cls");
                break;
            }
        case 11:
            {
                deleteEventKosong(events);
                cout<<"Penghapusan berhasil!"<<endl;
                getch();
                system("cls");
                break;

            }
        case 12:
            {
                showListPeserta(pesertaList);
                cout<<"selesai"<<endl;
                getch();
                system("cls");
                break;
            }
        case 13:
            {
                string inputNamaEvent;
                adrEvent hapus;
                cout<<"Masukkan nama event yang mau dihapus: "<<endl;
                cin>>inputNamaEvent;

                deleteEventMaster(events, inputNamaEvent,hapus);
                cout<<info(hapus).namaEvent<<" sudah dihapus dari sistem"<<endl;
                getch();
                system("cls");
                break;
            }
        default:
            break;
        }
        pilihan = menu();
    }
    cout<<"PROGRAM SELESAI"<<endl;
    return 0;
}
