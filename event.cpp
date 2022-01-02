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
        if (info(P).namaEvent == cariNamaEvent){
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
    if (findEvent(L,info(P).namaEvent) == nil){
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

void deleteFirstEvent(listEvent &L, adrEvent &Q){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong dan adrEvent Q untuk menyimpan event yang sudah dihapus
    F.S. elemen pertama dari listEvent sudah dihapus
**/
    Q = first(L);
    if(first(L) == nil && last(L) == nil){
        cout<<"Tidak ada event untuk dihapus (list kosong)"<<endl;
    }else if (first(L) == last(L)){
        first(L) = nil;
        last(L) = nil;
    }else{
        first(L) = next(Q);
        next(Q) = nil;
        prev(first(L)) = nil;
    }
}

void deletelastEvent(listEvent &L, adrEvent &Q){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong dan adrEvent Q untuk menyimpan event yang sudah dihapus
    F.S. elemen terakhir dari listEvent sudah dihapus
**/
    Q = last(L);
    if(first(L) == nil && last(L) == nil){
        cout<<"Tidak ada event untuk dihapus (list kosong)"<<endl;
    }else if (first(L) == last(L)){
        first(L) = nil;
        last(L) = nil;
    }else{
        last(L) = prev(Q);
        prev(Q) = nil;
        next(last(L)) = nil;
    }
}

void deleteAfterEvent(adrEvent prec, adrEvent &Q){
/** I.S. terdefinisi sebuah listEvent L
    F.S. elemen setelah dari prec telah dihapus dan disimpan dalam pointer alamat P
**/
    Q = next(prec);
    next(prec) = next(Q);
    prev(next(Q)) = prec;
    prev(Q) = nil;
    next(Q) = nil;
}

void deleteEventMaster(listEvent &L, string namaEvent, adrEvent &Q){
    /** I.S. terdefinisi sebuah listEvent L dan namaEvent yang akan dihapus dari list
        F.S.event dengan nama namaEvent sudah dihapus dari list dan disimpan dalam pointer Q
    **/
    Q = findEvent(L,namaEvent);
    if (Q != nil){
        if (info(first(L)).namaEvent == namaEvent){
            deleteFirstEvent(L,Q);
        }else if(info(last(L)).namaEvent == namaEvent){
            deletelastEvent(L,Q);
        }else{
            adrEvent R = first(L);
            while(info(next(R)).namaEvent != namaEvent){
                R = next(R);
            }
            deleteAfterEvent(R,Q);
        }
    }else{
        cout<<"Event belum terdaftar !";
    }
}

void showAllEventName(listEvent L){
    adrEvent P = first(L);
    int i = 1;
    if (P != nil){
        while (P != nil){
            cout<<"["<<i<<"] ";
            cout<<info(P).namaEvent<<endl;
            P = next(P);
            i++;
        }
    }else{
        cout<<"Belum ada event untuk ditampilkan"<<endl;
    }

}

void joinEvent(listEvent &L, adrPeserta daftar){
/** I.S. terdefinisi listEvent L dan pointer peserta yang akan dimasukkan ke event tertentu
    F.S. peserta yang tersimpan di pointer P sudah masuk ke salah satu event yang dipilih
**/
    adrPeserta P = newElmPeserta(info(daftar));
    showAllEventName(L);
    string pilihan;
    cout<<"Peserta tersebut akan masuk ke event mana? (tulis nama eventnya): ";
    cin>>pilihan;
    adrEvent Q = findEvent(L,pilihan);
    if (Q != nil){
        if (findPeserta(peserta(Q),info(P).namaPeserta) == nil){
            if (info(Q).kuotaMaks <= info(Q).jumlahPeserta){
                info(P).jenisPeserta = "waiting_list";
            }else{
                string noKursi;
                info(Q).jumlahPeserta = info(Q).jumlahPeserta + 1;
                info(P).jenisPeserta = "reguler";
                cout<<"Masukkan nomor kursi: ";
                cin>>noKursi;
                info(P).noKursi = noKursi;
            }
            insertLastPeserta(peserta(Q),P);
            cout<<"Status peserta adalah "<<info(P).jenisPeserta<<endl;
        }else{
            cout<<"Peserta sudah terdaftar dalam event tersebut!"<<endl;
        }
    }else{
        cout<<"event tersebut tidak ada. Buat event terlebih dahulu!"<<endl;
    }
}

void showjumlahPesertasemuaEvent(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua nama event beserta jumlah pesertanya sudah ditampilkan
**/
    adrEvent P = first(L);
    int i = 1;
    if (P != nil){
        while (P != nil){
            cout<<"["<<i<<"] ";
            cout<<info(P).namaEvent<<"| ";
            cout<<info(P).jumlahPeserta<<endl;
            P = next(P);
            i++;
        }
    }else{
        cout<<"Tidak ada event untuk ditampilkan"<<endl;
    }
}

void showEventTersedia(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua nama event dengan jumlah peserta < kuotaMaks sudah ditampilkan
**/
    adrEvent P = first(L);
    int i = 1;
    if (P != nil){
        while (P != nil){
            if (info(P).kuotaMaks > info(P).jumlahPeserta){
            cout<<"["<<i<<"] ";
            cout<<info(P).namaEvent<<"| "<<endl;
            cout<<"Jumlah peserta        = ";
            cout<<info(P).jumlahPeserta<<endl;
            cout<<"Jumlah kuota maksimal = ";
            cout<<info(P).kuotaMaks<<endl;
            cout<<"Kuota yang tersedia   = ";
            cout<<info(P).kuotaMaks - info(P).jumlahPeserta<<endl;
        }
        P = next(P);
        i++;
        }
    }else{
        cout<<"Tidak ada event untuk ditampilkan"<<endl;
    }
}

void deletePesertaEventTertentu(listEvent &events, string namaEvent, string namaPeserta, adrPeserta &Q){
/** I.S. terdefinisi sebuah listPeserta L dan namaPeserta yang akan dihapus
    F.S. peserta dengan namaPeserta telah dihapus dari list
**/
    adrEvent P = findEvent(events,namaEvent);
    if(P != nil){
        Q = findPeserta(peserta(P),namaPeserta);
        if (Q != nil){
            if (info(first(peserta(P))).namaPeserta == namaPeserta){
                deleteFirstPeserta(peserta(P),Q);
            }else if(info(last(peserta(P))).namaPeserta == namaPeserta){
                deleteLastPeserta(peserta(P),Q);
            }else{
                adrPeserta R = first(peserta(P));
                while(info(next(R)).namaPeserta != namaPeserta){
                    R = next(R);
                }
                deleteAfterPeserta(R,Q);
            }
            if (info(Q).jenisPeserta == "reguler"){
                info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
            }
            if (info(P).jumlahPeserta < info(P).kuotaMaks){
                adrPeserta waiting = findFirstWaitingList(peserta(P));
                if (waiting != nil){
                    string noKursi;
                    info(waiting).jenisPeserta = "reguler";
                    cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                    cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<": ";
                    cin>>noKursi;
                    info(waiting).noKursi = noKursi;
                    info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                }
            }
        }else{
            cout<<"Peserta tidak terdaftar di event ini.";
        }
    }else{
        cout<<"Event tidak ada!"<<endl;
    }
}

void deletePesertaDiSemuaEvent(listEvent &L, string namaPeserta){
/** I.S. terdefinisi sebuah listEvent, nama peserta yang akan dihapus dari semua event, dan adrPeserta Q untuk menyimpan pointer peserta yang sudah dihapus
    F.S. peserta dengan nama namaPeserta sudah terhapus dari semua event
**/
    adrEvent P = first(L);
    while (P != nil){
        adrPeserta Q = first(peserta(P));
        while (Q != nil){
            if (info(first(peserta(P))).namaPeserta == namaPeserta){
                deleteFirstPeserta(peserta(P),Q);
                if (info(Q).jenisPeserta == "reguler"){
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }
                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    adrPeserta waiting = findFirstWaitingList(peserta(P));
                    if (waiting != nil){
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";
                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }
            }else if(info(last(peserta(P))).namaPeserta == namaPeserta){
                deleteLastPeserta(peserta(P),Q);
                if (info(Q).jenisPeserta == "reguler"){
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }
                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    adrPeserta waiting = findFirstWaitingList(peserta(P));
                    if (waiting != nil){
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";
                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }
            }else{
                adrPeserta R = first(peserta(P));
                while(info(next(R)).namaPeserta != namaPeserta){
                    R = next(R);
                }
                deleteAfterPeserta(R,Q);
                if (info(Q).jenisPeserta == "reguler"){
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }
                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    adrPeserta waiting = findFirstWaitingList(peserta(P));
                    if (waiting != nil){
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";
                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }
            }
            Q = next(Q);
        }
        P = next(P);
    }
}

void showAlldataEvent(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua event dan data pesertanya sudah ditampilkan
**/
    adrEvent P = first(L);
    if (P != nil){
        while(P != nil){
            cout<<info(P).namaEvent<<endl;
            adrPeserta Q = first(peserta(P));
            if(Q != nil){
                while (Q != nil){
                    cout<<"No Peserta        |"<<info(Q).noPeserta<<endl;
                    cout<<"Nama Peserta      |"<<info(Q).namaPeserta<<endl;
                    cout<<"E-mail Peserta    |"<<info(Q).emailPeserta<<endl;
                    cout<<"No. Telp. Peserta |"<<info(Q).noTelpPeserta<<endl;
                    cout<<"No. Kursi         |"<<info(Q).noKursi<<endl;
                    cout<<"Jenis Peserta     |"<<info(Q).jenisPeserta<<endl;
                    cout<<endl;
                    Q = next(Q);
                }
                cout<<endl;
            }else{
                cout<<"Peserta kosong"<<endl;
            }
        cout<<endl;
        P = next(P);
        }
    }else{
        cout<<"List Event kosong!"<<endl;
    }
}

void showAlldataEventTertentu(listEvent L, adrEvent P){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua event dan data pesertanya sudah ditampilkan
**/
    cout<<info(P).namaEvent<<endl;
    adrPeserta Q = first(peserta(P));
    if(Q != nil){
        while (Q != nil){
            cout<<"No Peserta        |"<<info(Q).noPeserta<<endl;
            cout<<"Nama Peserta      |"<<info(Q).namaPeserta<<endl;
            cout<<"E-mail Peserta    |"<<info(Q).emailPeserta<<endl;
            cout<<"No. Telp. Peserta |"<<info(Q).noTelpPeserta<<endl;
            cout<<"No. Kursi         |"<<info(Q).noKursi<<endl;
            cout<<"Jenis Peserta     |"<<info(Q).jenisPeserta<<endl;
            cout<<endl;
            Q = next(Q);
        }
        cout<<endl;
    }else{
        cout<<"Peserta kosong"<<endl;
    }
}

void deleteEventKosong(listEvent &L){
/** I.S. terdefinisi sebuah listEvent L yang mungkin kosong
    F.S. semua event dengan jumlah peserta 0 sudah dihapus dari list
**/
    adrEvent P = first(L);
    adrEvent Q;
    if (P != nil){
        while(P != nil){
            if(info(P).jumlahPeserta == 0){
                if(first(L) == P){
                    deleteFirstEvent(L,Q);
                }else if (last(L) == P){
                    deletelastEvent(L,Q);
                }else{
                    adrEvent R = first(L);
                    while (next(R) != P){
                        R = next(R);
                    }
                    deleteAfterEvent(R,Q);
                }
                P = first(L);
            }
            P = next(P);
        }
    }else{
        cout<<"List Event kosong. Tidak ada yang bisa dihapus."<<endl;
    }
}

int menu(){
/**
    Mengembalikan pilihan user terhadap menu yang dipilih;
**/
    int pilihan;
    cout<<"===============> MENU <==============="<<endl;
    cout<<"[1]  Tambahkan Event"<<endl;
    cout<<"[2]  Tambahkan Peserta"<<endl;
    cout<<"[3]  Menambahkan seorang peserta ke sebuah event"<<endl;
    cout<<"[4]  Menampilkan semua event dengan jumlah peserta"<<endl;
    cout<<"[5]  Menampilkan data peserta di event tertentu"<<endl;
    cout<<"[6]  Menampilkan semua event dengan data pesertanya"<<endl;
    cout<<"[7]  Mencari event tertentu dengan kuota yang masih tersedia"<<endl;
    cout<<"[8]  Mencari peserta tertentu pada sebuah event"<<endl;
    cout<<"[9]  Menghapus peserta dari event tertentu"<<endl;
    cout<<"[10] Menghapus data peserta dari sistem"<<endl;
    cout<<"[11] Menghapus event dengan peserta berjumlah 0"<<endl;
    cout<<"[12] Menampilkan semua data peserta"<<endl;
    cout<<"[13] Menghapus sebuah event"<<endl;
    cout<<"[0]  Exit"<<endl;
    cout<<endl;

    cout<<"Masukkan pilihan: ";
    cin>>pilihan;
    cout<<endl;
    return pilihan;
}







