#include "peserta.h"

void createListPeserta(listPeserta &L){
/**
    I.S. -
    F.S. telah dibuat sebuah listPeserta L dengan first dan last nil
**/
    first(L) = nil;
    last(L) = nil;
}

adrPeserta findPeserta(listPeserta L, string cariNamaPeserta){
/**
    Mengembalikan pointer alamat adrPeserta apabila terdapat seorang peserta sesuai dengan cariNamaEvent bertipe string
    dan mengembalikan nil apabila sebaliknya
**/
    adrPeserta P = first(L);
    while (P != nil){
        if info(P).namaPeserta = cariNamaPeserta{
            return P;
        }
        P = next(P);
    }
    return nil;
}

/**
adrPeserta findFirstWaitingList(listPeserta L){

    //[Berguna untuk sistem waiting list]
    //Mengembalikan pointer alamat adrPeserta apabila ditemukan seorang peserta pertama dengan jenis "waiting_list"

    adrPeserta P = first(L);
    while (P != nil){
        //pencarian dari depan mencari waiting list pertama
        if (info(P).jenisPeserta = "waiting_list"){
            return P;
        }
        P = next(P);
    }
    return nil;
}
**/

adrPeserta findLastRegular(listPeserta L){
/**
    [Berguna untuk sistem waiting list]
    Mengembalikan pointer alamat adrPeserta terakhir yang berjenis "reguler" apabila terdapat peserta dengan jenis "waiting_list"
**/
    P = findFirstWaitingList(L);
    if (P != nil){
        return prev(P);
    }else{
        return nil;
    }

}

infotypePeserta createPeserta(){
/**
    mengembalikan data peserta baru sesuai inputan user
**/
    infotypePeserta newPeserta;
    string noPeserta;
    string namaPeserta;
    string emailPeserta;
    string noTelpPeserta;
    int noKursi;

    //menginput data peserta baru
    cout<<"Masukkan nomor peserta: ";
    cin>>noPeserta;
    cout<<"Masukkan nama peserta: ";
    cin>>namaPeserta;
    cout<<"Masukkan email peserta: ";
    cin>>emailPeserta;
    cout<<"Masukkan nomor telepon peserta: ";
    cin>>noTelpPeserta;

    //menyimpan data peserta ke newPeserta
    newPeserta.noPeserta = noPeserta;
    newPeserta.namaPeserta = namaPeserta;
    newPeserta.emailPeserta = emailPeserta;
    newPeserta.noTelpPeserta = noTelpPeserta;

    return newPeserta;
}

adrPeserta newElmPeserta(infotypePeserta input){
/**
    Mengembalikan P yang bertipe adrPeserta yang berisi input bertipe peserta
**/
    adrPeserta P = new elmPeserta;
    prev(P) = nil;
    next(P) = nil;
    info(P) = input;
    return P;
}

void insertLastPeserta(listPeserta &L, adrPeserta P){
/**
    I.S. listEvent L mungkin kosong
    F.S. seorang peserta P telah ditambahkan setelah elemen terakhir apabila peserta tsb belum ada di dalam list
         dan mengeluarkan pesan "peserta sudah ada dalam list (terdaftar)" apabila peserta sudah ada dalam list
**/
    if (findPeserta(L) != nil){
        //Peserta ada dalam list
        if (first(L) == nil && last(L) == nil){
            //listPeserta dalam keadaan kosong
            first(L) = P;
            last(L) = P;
        }else{
            //listPeserta tidak dalam keadaan kosong
            prev(P) = last(L);
            next(last(L)) = P;
            last(L) = P;
        }
    }else{
        //Event tidak ada dalam list
        cout<<"Peserta sudah ada dalam list. Tidak perlu ditambahkan lagi."<<endl;
    }

}

void deleteFirstPeserta(listPeserta &L, adrPeserta &P){
/** I.S. terdefinisi sebuah listPeserta L yang mungkin kosong
    F.S. elemen pertama dari list L telah dihapus dan disimpan dalam pointer alamat P
**/
    P = first(L);
    if(first(L) == nil && last(L) == nil){
        cout<<"Tidak ada peserta untuk dihapus (list kosong)"<<endl;
    }else if (first(L) == last(L)){
        first(L) = nil;
        last(L) = nil;
    }else{
        first(L) = next(P);
        next(P) = nil;
        prev(first(L)) = nil;
    }
}

void deleteLastPeserta(listPeserta &L, adrPeserta &P){
/** I.S. terdefinisi sebuah listPeserta L yang mungkin kosong
    F.S. elemen terakhir dari list L telah dihapus dan disimpan dalam pointer alamat P
**/
    P = last(L);
    if(first(L) == nil && last(L) == nil){
        cout<<"Tidak ada peserta untuk dihapus (list kosong)"<<endl;
    }else if (first(L) == last(L)){
        first(L) = nil;
        last(L) = nil;
    }else{
        last(L) = prev(P);
        prev(P) = nil;
        next(last(L)) = nil;
    }
}

void deleteAfterPeserta(adrPeserta prec, adrPeserta &P){
/** I.S. terdefinisi sebuah listPeserta L
    F.S. elemen setelah dari prec telah dihapus dan disimpan dalam pointer alamat P
**/
    P = next(prec);
    next(prec) = next(P);
    prev(next(P)) = prec;
    prev(P) = nil;
    next(P) nil;
}

void deletePesertaMaster(listPeserta &L, adrEvent P, string namaPeserta, adrPeserta &Q){
/** I.S. terdefinisi sebuah listPeserta L dan namaPeserta yang akan dihapus
    F.S. peserta dengan namaPeserta telah dihapus dari list
**/
    Q = first(peserta(P))
    while (P != nil){
        if(info(first(peserta(P))).namaPeserta == namaPeserta){
            deleteFirstPeserta(&L,)
        }
    }
}


