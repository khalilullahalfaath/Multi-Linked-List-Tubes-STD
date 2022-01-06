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
    while(pilihan != 0){
        system("cls");
        switch(pilihan){
        case 1:
        {
            cout<<">>>>>>>>>> REGISTRASI EVENT <<<<<<<<<<"<<endl;
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
            cout<<">>>>>>>>>> REGISTRASI PESERTA <<<<<<<<<<"<<endl;
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
            cout<<">>>>>>>>>> REGISTRASI PESERTA KE EVENT TERTENTU <<<<<<<<<<"<<endl;
            string inputNamaPeserta;
            cout<<"Berikut adalah list Peserta: "<<endl;
            showAllNamaPeserta(pesertaList);
            if (first(pesertaList) != nil){
                cout<<"Masukkan nama Peserta: ";
                cin>>inputNamaPeserta;
                adrPeserta pesertaEvent = findPeserta(pesertaList,inputNamaPeserta);
                if (pesertaEvent != nil){
                    joinEvent(events,pesertaEvent);
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
                cout<<">>>>>>>>>> TAMPILAN SEMUA JUMLAH PESERTA SEMUA EVENT <<<<<<<<<<"<<endl;
                showjumlahPesertasemuaEvent(events);
                getch();
                system("cls");
                break;
            }
        case 5:
            {
                cout<<">>>>>>>>>> TAMPILAN DATA PESERTA SUATU EVENT TERTENTU <<<<<<<<<<"<<endl;
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
                cout<<">>>>>>>>>> TAMPILAN SEMUA DATA EVENT BESERTA PESERTANYA <<<<<<<<<<"<<endl;
                showAlldataEvent(events);
                getch();
                system("cls");
                break;
            }
        case 7:
            {
                cout<<">>>>>>>>>> TAMPILAN SEMUA EVENT YANG TERSEDIA (BELUM FULL) <<<<<<<<<<"<<endl;
                showEventTersedia(events);
                getch();
                system("cls");
                break;
            }
        case 8:
            {
                cout<<">>>>>>>>>> PENCARIAN PESERTA DI SUATU EVENT TERTENTU <<<<<<<<<<"<<endl;
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
                        if(info(cariPeserta).jenisPeserta == "reguler"){
                            cout<<"Dengan status    : "<<info(cariPeserta).jenisPeserta<<endl;
                            cout<<"Dengan kursi     : "<<info(cariPeserta).noKursi<<endl;
                        }else if(info(cariPeserta).jenisPeserta == "waiting_list"){
                            cout<<"Dengan status    : "<<info(cariPeserta).jenisPeserta<<endl;
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
        case 9:
            {
                cout<<">>>>>>>>>> MENGHAPUS PESERTA DARI EVENT TERTENTU <<<<<<<<<<"<<endl;
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
                        }else{
                            break;
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
                cout<<">>>>>>>>>> MENGHAPUS PESERTA DARI SEMUA EVENT ATAU SISTEM <<<<<<<<<<"<<endl;
                string inputNamaPeserta;
                adrPeserta hapus;
                cout<<"Masukkan nama peserta yang akan dihapus dari semua event/sistem: ";
                cin>>inputNamaPeserta;
                if (findPeserta(pesertaList,inputNamaPeserta) != nil){
                    deletePeserta(pesertaList,inputNamaPeserta,hapus);
                    deletePesertaDiSemuaEvent(events,inputNamaPeserta);
                    cout<<"Peserta "<<info(hapus).namaPeserta<<" sudah dihapus dari sistem"<<endl;
                }else{
                    cout<<"Peserta tidak teregistrasi!"<<endl;
                }
                getch();
                system("cls");
                break;
            }
        case 11:
            {
                cout<<">>>>>>>>>> MENGHAPUS EVENT DENGAN JUMLAH PESERTA 0 <<<<<<<<<<"<<endl;
                deleteEventKosong(events);
                cout<<"Penghapusan berhasil!"<<endl;
                getch();
                system("cls");
                break;

            }
        case 12:
            {
                cout<<">>>>>>>>>> MENAMPILKAN PESERTA YANG TEREGISTRASI <<<<<<<<<<"<<endl;
                showListPeserta(pesertaList);
                cout<<"selesai"<<endl;
                getch();
                system("cls");
                break;
            }
        case 13:
            {
                cout<<">>>>>>>>>> MENGHAPUS SUATU EVENT DARI SISTEM <<<<<<<<<<"<<endl;
                string inputNamaEvent;
                adrEvent hapus;
                cout<<"Masukkan nama event yang mau dihapus: ";
                cin>>inputNamaEvent;
                if(findEvent(events,inputNamaEvent) != nil){
                    deleteEventMaster(events, inputNamaEvent,hapus);
                    cout<<info(hapus).namaEvent<<" sudah dihapus dari sistem"<<endl;
                }else{
                    cout<<"Event belum teregistrasi!"<<endl;
                }
                getch();
                system("cls");
                break;
            }
        case 14:
            {
                cout<<">>>>>>>>>> MENAMPILKAN SEMUA EVENT <<<<<<<<<<"<<endl;
                showAllEvent(events);
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
