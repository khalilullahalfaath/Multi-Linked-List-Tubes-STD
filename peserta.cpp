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
    adrPeserta P = first(L); //assign P
    
    while (P != nil){
        //mengulang sampai selesai
        if (info(P).namaPeserta == cariNamaPeserta){
            //peserta dengan nama peserta cariNamaPeserta ditemukan
            return P;
        }
        P = next(P);
    }
    //tidak ditemukan
    return nil;
}

adrPeserta findFirstWaitingList(listPeserta L){
    //[Berguna untuk sistem waiting list]
    //Mengembalikan pointer alamat adrPeserta apabila ditemukan seorang peserta pertama dengan jenis "waiting_list"

    adrPeserta P = first(L); //assign P
    while (P != nil){
        //pencarian dari depan mencari waiting list pertama
        
        if (info(P).jenisPeserta == "waiting_list"){
            //waiting_list pertama ditemukan
            return P;
        }
        P = next(P);
    }
    //tidak ditemukan
    return nil;
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
    if (findPeserta(L,info(P).namaPeserta) == nil){
        //Peserta tidak ada dalam list

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
    P = first(L); //assign P = first(L)
    
    if(first(L) == nil && last(L) == nil){
        //list kosong
        cout<<"Tidak ada peserta untuk dihapus (list kosong)"<<endl;
  
    }else if (first(L) == last(L)){
        //list hanya satu elemen
        first(L) = nil;
        last(L) = nil;
   
    }else{
        //list lebih dari satu elemen
        first(L) = next(P);
        next(P) = nil;
        prev(first(L)) = nil;
    }
}

void deleteLastPeserta(listPeserta &L, adrPeserta &P){
/** I.S. terdefinisi sebuah listPeserta L yang mungkin kosong
    F.S. elemen terakhir dari list L telah dihapus dan disimpan dalam pointer alamat P
**/
    P = last(L); //assign P dengan last L
    
    if(first(L) == nil && last(L) == nil){
        //list kosong
        cout<<"Tidak ada peserta untuk dihapus (list kosong)"<<endl;
    
    }else if (first(L) == last(L)){
        //list hanya satu elemen
        first(L) = nil;
        last(L) = nil;
    
    }else{
        //list lebih dari satu elemen
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
    next(P) = nil;
}

void deletePeserta(listPeserta &L, string namaPeserta, adrPeserta &Q){
/** I.S. terdefinisi sebuah listPeserta L,mungkin kosong dan nama peserta yang akan dihapus dari list
    F.S. peserta dengan nama peserta namaPeserta sudah terhapus dari list
**/

    if (info(first(L)).namaPeserta == namaPeserta){
        //peserta yang akan dihapus adalah elemen pertama
        deleteFirstPeserta(L,Q);
    }else if (info(last(L)).namaPeserta == namaPeserta){
        //peserta yang akan dihapus adalah elemen terakhir
        deleteLastPeserta(L,Q);
    }else{
        adrPeserta R = first(L);
        while (info(next(R)).namaPeserta != namaPeserta){
            //mengulang sampai ditemukan next R adalah elemen hapus
            R = next(R);
        }
        
        deleteAfterPeserta(R,Q);
    }
}

void showAllNamaPeserta(listPeserta L){
/**
    I.S. terdefinisi sebuah listPeserta L, mungkin kosong
    F.S. semua nama peserta yang teregistrasi sudah ditampilkan
**/
    adrPeserta P = first(L); //assign P = first(L)
    
    if (P != nil){
        //list tidak kosong
        while (P != nil){
            //mengulang sampai selesai
            cout<<info(P).namaPeserta<<endl;
            P = next(P);
        }
    
    }else{
        //list kosong
        cout<<"List peserta kosong"<<endl;
    }
    cout<<endl;
}

void showListPeserta(listPeserta L){
/**
    I.S. terdefinisi sebuah listPeserta L, mungkin kosong
    F.S. semua data peserta sudah ditampilkan
**/
    adrPeserta P = first(L); //assign P = first(L)
    int i = 1; //penomoran
    
    if (P != nil){
        //list tdk kosong
        while (P != nil){
            cout<<"["<<i<<"]"<<endl;
            cout<<"No Peserta        |"<<info(P).noPeserta<<endl;
            cout<<"Nama Peserta      |"<<info(P).namaPeserta<<endl;
            cout<<"E-mail Peserta    |"<<info(P).emailPeserta<<endl;
            cout<<"No. Telp. Peserta |"<<info(P).noTelpPeserta<<endl;
            cout<<endl;
            P = next(P);
            i++;
        }
    
    }else{
        //list kosong
        cout<<"List peserta kosong"<<endl;
    }
    cout<<endl;
}




