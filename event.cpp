#include "event.h"

void createListEvent(listEvent &L){
/**
    I.S. -
    F.S. telah dibuat sebuah listEvent L dengan first dan last nil
**/
    first(L) = nil;
    last(L) = nil;
}

adrEvent findEvent(listEvent L, string cariNamaEvent){
/**
    Mengembalikan pointer alamat adrEvent apabila terdapat sebuah event sesuai dengan cariNamaEvent bertipe string
    dan mengembalikan nil apabila sebaliknya
**/
    adrEvent P = first(L);
    while (P != nil){
        if info(P).namaEvent = cariNamaEvent{
            return P;
        }
        P = next(P);
    }
    return nil;
}

infotypeEvent createNewEvent(){
/**
    Mengembalikan newEvent sesuai inputan dari user
**/
    infotypeEvent newEvent;
    string namaEvent;
    string jenisEvent;
    string tanggalPelaksanaan;
    int kuotaMaks;

    //menginput data event baru
    cout<<"Masukkan nama event: ";
    cin>>namaEvent;
    cout<<"Masukkan jenis event: ";
    cin>>jenisEvent;
    cout<<"Masukkan tanggal  pelaksanaan event: ";
    cin>>tanggalPelaksanaan;
    cout<<"Masukkan kuota maksimal event: ";
    cin>>kuotaMaks;

    //menyimpan data event yang sudah dibuat kedalam newEvent
    newEvent.namaEvent = namaEvent;
    newEvent.jenisEvent = jenisEvent;
    newEvent.tanggalPelaksanaan = tanggalPelaksanaan;
    newEvent.kuotaMaks = kuotaMaks;
    newEvent.jumlahPeserta = 0;

    return newEvent;
}

adrEvent newElmEvent(infotypeEvent input){
/**
    Mengembalikan P yang bertipe adrEvent yang berisi input bertipe event
**/
    adrEvent P = new elmEvent;
    prev(P) = nil;
    next(P) = nil;
    info(P) = input;
    createListPeserta(peserta(P));

    return P;
}

void insertLastEvent(listEvent &L, adrEvent P){
/**
    I.S. listEvent L mungkin kosong
    F.S. sebuah event P telah ditambahkan setelah elemen terakhir apabila event tsb belum ada di dalam list
         dan mengeluarkan pesan "Event sudah ada dalam list" apabila event sudah ada dalam list
**/
    if (findEvent(L) != nil){
        //Event tidak ada dalam list
        if (first(L) == nil && last(L) == nil){
            //listEvent dalam keadaan kosong
            first(L) = P;
            last(L) = P;
        }else{
            prev(P) = last(L);
            next(last(L)) = P;
            last(L) = P;
        }
    }else{
        //Event ada dalam list
        cout<<"Event sudah ada dalam list. Tidak perlu ditambahkan lagi."<<endl;
    }

}

