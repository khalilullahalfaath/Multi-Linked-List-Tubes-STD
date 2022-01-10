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
    Mengembalikan alamat adrEvent dengan namaEvent = cariNamaEvent
    dan mengembalikan nil apabila tidak ditemukan sebuah event dengan namaEvent = cariNamaEvent
**/
    adrEvent P = first(L); //assign P dengan first(L)

    //Mengecek berulang sampai akhir listEvent
    while (P != nil){
        //Apabila didapat sebuah event dengan namaEvent = cariNamaEvent akan return alamat event tersebut
        if (info(P).namaEvent == cariNamaEvent){
            return P;
        }

        P = next(P);
    }

    //List sudah dicek semuanya, return NULL
    return nil;
}

infotypeEvent createNewEvent(){
/**
    Mengembalikan newEvent yang bertipe infotypeEvent sesuai inputan dari user
**/
    infotypeEvent newEvent;
    string namaEvent, jenisEvent, tanggalPelaksanaan,tempatPelaksanaan;
    int kuotaMaks;

    //menginput data event baru
    cout<<"Masukkan nama event              : ";getline(cin >> ws, namaEvent);
    cout<<"Masukkan jenis event             : ";getline(cin >> ws, jenisEvent);
    cout<<"Masukkan tanggal event           : ";getline(cin >> ws, tanggalPelaksanaan);
    cout<<"Masukkan tempat pelaksanaan event: ";getline(cin >> ws, tempatPelaksanaan);
    cout<<"Masukkan kuota maksimal event    : ";cin>>kuotaMaks;



    //menyimpan data event yang sudah dibuat kedalam newEvent
    newEvent.namaEvent = namaEvent;
    newEvent.jenisEvent = jenisEvent;
    newEvent.tanggalPelaksanaan = tanggalPelaksanaan;
    newEvent.tempatPelaksanaan = tempatPelaksanaan;
    newEvent.kuotaMaks = kuotaMaks;
    newEvent.jumlahPeserta = 0;

    return newEvent;
}

adrEvent newElmEvent(infotypeEvent input){
/**
    Mengembalikan P yang bertipe adrEvent yang berisi input bertipe infotypeEvent
**/
    //Alokasi P bertipe adrEvent
    adrEvent P = new elmEvent;

    prev(P) = nil;
    next(P) = nil;
    info(P) = input;

    //Setiap event memuat satu listPeserta yang merupakan peserta dari event tersebut
    createListPeserta(peserta(P));

    return P;
}

void insertLastEvent(listEvent &L, adrEvent P){
/**
    I.S. listEvent L, mungkin kosong dan sebuah adrEvent P yang siap dimasukkan ke dalam listEvent
    F.S. sebuah event P telah ditambahkan sebagai elemen terakhir, apabila event tsb belum ada di dalam listEvent
         dan mengeluarkan pesan "Event sudah ada dalam list. Tidak perlu ditambahkan lagi"
         apabila event sudah ada dalam list.
**/
    //Mengecek apakah event dengan nama event namaEvent ada dalam listEvent
    if (findEvent(L,info(P).namaEvent) == nil){
        //Event tidak ada dalam list

        if (first(L) == nil && last(L) == nil){
            //listEvent dalam keadaan kosong
            first(L) = P;
            last(L) = P;

        }else{
            //listEvent tidak kosong
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
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. elemen pertama dari listEvent sudah dihapus dan disimpan dalam adrEvent Q
**/
    Q = first(L);
    if(first(L) == nil && last(L) == nil){
        //listEvent kosong

        cout<<"Tidak ada event untuk dihapus (list kosong)"<<endl;

    }else if (first(L) == last(L)){
        //listEvent hanya ada satu elemen

        first(L) = nil;
        last(L) = nil;

    }else{
        //ListEvent punya lebih dari satu elemen

        first(L) = next(Q);
        next(Q) = nil;
        prev(first(L)) = nil;
    }
}

void deletelastEvent(listEvent &L, adrEvent &Q){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. elemen terakhir dari listEvent sudah dihapus dan disimpan dalam adrEvent Q
**/
    Q = last(L);
    if(first(L) == nil && last(L) == nil){
        //listEvent kosong
        cout<<"Tidak ada event untuk dihapus (list kosong)"<<endl;

    }else if (first(L) == last(L)){
        //listEvent hanya ada satu elemen
        first(L) = nil;
        last(L) = nil;

    }else{
        //listEvent punya lebih dari satu elemen
        last(L) = prev(Q);
        prev(Q) = nil;
        next(last(L)) = nil;
    }
}

void deleteAfterEvent(adrEvent prec, adrEvent &Q){
/** I.S. terdefinisi sebuah adrEvent prec yang elemen setelahnya akan dihapus
    F.S. elemen setelah prec telah dihapus dari listEvent dan disimpan dalam adrEvent Q
**/
    Q = next(prec);
    next(prec) = next(Q);
    prev(next(Q)) = prec;
    prev(Q) = nil;
    next(Q) = nil;
}

void deleteEventMaster(listEvent &L, string namaEvent, adrEvent &Q){
/** I.S. terdefinisi sebuah listEvent L dan namaEvent yang akan dihapus dari list
    F.S. event dengan nama namaEvent sudah dihapus dari list dan disimpan dalam adrEvent Q.
         Apabila event tidak ditemukan di dalam listEvent maka akan mengeluarkan pesan "Event belum terdaftar!"
**/
    Q = findEvent(L,namaEvent);
    if (Q != nil){
        //Event ditemukan di dalam listEvent

        if (info(first(L)).namaEvent == namaEvent){
            //Event yang ingin dihapus merupakan elemen pertama dalam list
            deleteFirstEvent(L,Q);

        }else if(info(last(L)).namaEvent == namaEvent){
            //Event yang ingin dihapus merupakan elemen terakhir dalam list
            deletelastEvent(L,Q);

        }else{
            //Event yang ingin dihapus bukan elemen pertama atau terakhir dari list.
            adrEvent R = first(L);
            while(info(next(R)).namaEvent != namaEvent){
                //Mencari elemen dengan elemen setelahnya merupakan event yang ingin dihapus
                R = next(R);
            }

            deleteAfterEvent(R,Q);
        }

    }else{
        cout<<"Event belum terdaftar !";
    }
}

void showAllEventName(listEvent L){
/** I.S. terdefinisi sebuah listEvent L
    F.S. semua namaEvent dari setiap event sudah ditampilkan. Apabila listEvent kosong, akan menampilkan pesan "Belum ada event untuk ditampilkan"
**/
    //P diassign first(L)
    adrEvent P = first(L);
    int i = 1;
    if (P != nil){
        //listEvent tidak kosong
        while (P != nil){
            //Mengulang sampai semua event sudah ditampilkan
            cout<<"["<<i<<"] ";
            cout<<info(P).namaEvent<<endl;
            P = next(P);
            i++;
        }
    }else{
        //listEvent kosong
        cout<<"Belum ada event untuk ditampilkan"<<endl;
    }

}

void joinEvent(listEvent &L, adrPeserta daftar){
/** I.S. terdefinisi listEvent L dan pointer peserta yang akan dimasukkan ke event tertentu
    F.S. peserta yang tersimpan di pointer P sudah masuk ke salah satu event yang dipilih
    Process. Akan dibuat sebuah event baru dengan info sama dengan info daftar. Kemudian akan ditampilkan semua event yang terdaftar
             dan user akan memilih event yang akan diikuti. Apabila event ditemukan dan peserta belum terdaftar di dalam event tersebut,
             akan diperiksa apakah kuotaMaks dari event sudah terpenuhi, apabila iya, jenis peserta akan menjadi "waiting_list"
             atau "reguler" apabila sebaliknya dan akan diminta no. kursi untuk peserta di event tsb.

**/
    //Mengcopy info(daftar) ke dalam P
    adrPeserta P = newElmPeserta(info(daftar));
    cout<<"Berikut adalah event-event yang tersedia"<<endl;
    showAllEventName(L); //Menampilkan nama dari setiap event yang teregistrasi
    cout<<endl;

    string pilihan;
    cout<<"Peserta tersebut akan masuk ke event mana? (tulis nama eventnya): ";getline(cin >> ws, pilihan);

    //mencari event dengan namaEvent = pilihan
    adrEvent Q = findEvent(L,pilihan);

    if (Q != nil){
        //event ditemukan dalam listEvent
        if (findPeserta(peserta(Q),info(P).namaPeserta) == nil){
            //peserta belum terdaftar dalam event tsb

            if (info(Q).kuotaMaks <= info(Q).jumlahPeserta){
                //kuotaMaks sudah tercapai
                //peserta tsb berjenis "waiting_list"
                info(P).jenisPeserta = "waiting_list";

            }else{
                //kuotaMaks belum tercapai
                //Diminta untuk menginputkan no. kursi
                //peserta tsb berjenis "reguler"
                string noKursi;

                info(Q).jumlahPeserta = info(Q).jumlahPeserta + 1;
                info(P).jenisPeserta = "reguler";

                cout<<"Masukkan nomor kursi: ";
                cin>>noKursi;

                info(P).noKursi = noKursi;
            }

            //peserta masuk ke dalam event
            insertLastPeserta(peserta(Q),P);
            cout<<endl;

            cout<<info(P).namaPeserta<<" sudah masuk ke dalam "<<info(Q).namaEvent<<endl;
            cout<<"Status peserta adalah "<<info(P).jenisPeserta<<endl;

        }else{
            //peserta sudah terdaftar di dalam event
            cout<<"Peserta sudah terdaftar dalam event tersebut!"<<endl;
        }

    }else{
        //event tidak ditemukan dalam listEvent
        cout<<"event tersebut tidak ada. Buat event terlebih dahulu!"<<endl;
    }
}

void showjumlahPesertasemuaEvent(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua nama event beserta jumlah pesertanya sudah ditampilkan.
         Menampilkan pesan "Tidak ada event untuk ditampilkan" apabila list kosong
**/
    adrEvent P = first(L);   //assign P dengan first(L)
    int i = 1;  //Penomoran

    if (P != nil){
        //listEvent tidak kosong
        cout<<"Nama event | jumlah peserta "<<endl;

        while (P != nil){
            //mengulang untuk semua event
            cout<<"["<<i<<"] ";
            cout<<info(P).namaEvent<<" | ";
            cout<<info(P).jumlahPeserta<<endl;
            P = next(P);
            i++;

        }

    }else{
        //listEvent kosong
        cout<<"Tidak ada event untuk ditampilkan"<<endl;
    }
}

void showEventTersedia(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua nama event dengan jumlah peserta < kuotaMaks sudah ditampilkan, beserta kuoata yang tersedia.
         Apabila list kosong, akan menampilkan pesan "Tidak ada event untuk ditampilkan"
**/
    adrEvent P = first(L); //assign P dengan first(L)
    int i = 1; //penomoran

    if (P != nil){
        //listEvent tidak kosong

        while (P != nil){
            //mengulang sampai semua event

            if (info(P).kuotaMaks > info(P).jumlahPeserta){
                //kuota maksimum belum terpenuhi
                //Akan ditampilkan: namaEvent, jumlah peserta, kuota maksimal, dan kuota yang tersedia
                cout<<"["<<i<<"] ";
                cout<<info(P).namaEvent<<"| "<<endl;
                cout<<"Jumlah peserta        = ";
                cout<<info(P).jumlahPeserta<<endl;
                cout<<"Jumlah kuota maksimal = ";
                cout<<info(P).kuotaMaks<<endl;
                cout<<"Kuota yang tersedia   = ";
                cout<<info(P).kuotaMaks - info(P).jumlahPeserta<<endl;
                cout<<endl;
            }

            P = next(P);
            i++;
        }

    }else{
        //listEvent kosong
        cout<<"Tidak ada event untuk ditampilkan"<<endl;

    }
    //Menampilkan pesan "sudah ditampilkan" untuk tidak membingungkan apabila tidak ada event yang kuotanya tersedia
    cout<<"Sudah ditampilkan"<<endl;
}

void deletePesertaEventTertentu(listEvent &events, string namaEvent, string namaPeserta, adrPeserta &Q){
/** I.S. terdefinisi sebuah listPeserta L dan nama peserta dan nama Event yang pesertanya tsb akan dihapus
    F.S. peserta dengan namaPeserta telah dihapus dari anggota peserta event yang ditunjuk
**/
    adrEvent P = findEvent(events,namaEvent); //mencari event dengan namaEvent == namaEvent input

    if(P != nil){
        //event ditemukan

        Q = findPeserta(peserta(P),namaPeserta); //mencari peserta dengan namaPeserta = namaPeserta input di anggota peserta event

        if (Q != nil){
            //peserta ditemukan. Akan dilakukan penghapusan sesuai posisi element

            if (info(first(peserta(P))).namaPeserta == namaPeserta){
                //elemen hapus merupakan elemen pertama
                deleteFirstPeserta(peserta(P),Q);

            }else if(info(last(peserta(P))).namaPeserta == namaPeserta){
                //elemen hapus merupakan elemen terakhir
                deleteLastPeserta(peserta(P),Q);

            }else{
                adrPeserta R = first(peserta(P)); //assign R dengan first(peserta event)

                while(info(next(R)).namaPeserta != namaPeserta){
                    //mengulang sampai ditemukan info(next(R)) = namaPeserta
                    R = next(R);
                }

                //elemen hapus merupakan elemen setelah R
                deleteAfterPeserta(R,Q);
            }

            if (info(Q).jenisPeserta == "reguler"){
                //peserta merupakan peserta reguler sehingga mempengaruhi jumlah peserta untuk event tsb
                info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
            }

            if (info(P).jumlahPeserta < info(P).kuotaMaks){
                //kuota maksimal event belum terpenuhi

                //Akan dicari peserta dengan waiting_list teratas
                adrPeserta waiting = findFirstWaitingList(peserta(P));

                if (waiting != nil){
                    //waiting_list teratas ditemukan dan akan menjadi peserta reguler
                    //akan diinput no. kursinya
                    string noKursi;
                    info(waiting).jenisPeserta = "reguler";
                    cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;

                    cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<": ";
                    cin>>noKursi;
                    info(waiting).noKursi = noKursi;

                    //jumlah peserta bertambah
                    info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                }
            }

        }else{
            //peserta tidak ditemukan
            cout<<"Peserta tidak terdaftar di event ini.";
        }

    }else{
        //event tidak ditemukan
        cout<<"Event tidak ada!"<<endl;
    }
}

void deletePesertaDiSemuaEvent(listEvent &L, string namaPeserta){
/** I.S. terdefinisi sebuah listEvent, nama peserta yang akan dihapus dari semua event
    F.S. peserta dengan nama namaPeserta sudah terhapus dari semua event
**/
    /*
    adrEvent P = first(L); //assign P = first(L)

    while (P != nil){
        //mengulang untuk semua event

        adrPeserta Q = first(peserta(P)); //assign Q = first(listPeserta(event))

        while (Q != nil){
            //mengulang utk semua peserta yg terdaftar di event tsb

            if (info(first(peserta(P))).namaPeserta == namaPeserta){
                //peserta tsb merupakan elemen pertama
                deleteFirstPeserta(peserta(P),Q);

                //mengecek apakah peserta tsb "reguler". Kalau iya, akan merubah jumlah peserta berkurang 1
                if (info(Q).jenisPeserta == "reguler"){
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }

                //mengecek apakah kuota peserta masih tersedia
                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    //kuota tersedia. Akan dicari waiting_list pertama

                    adrPeserta waiting = findFirstWaitingList(peserta(P));
                    if (waiting != nil){
                        //waiting_list pertama ditemukan. Merubah menjadi reguler
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";

                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        cout<<endl;

                        //jumlah peserta menjadi bertambah 1
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }

            }else if(info(last(peserta(P))).namaPeserta == namaPeserta){
                //peserta tsb merupakan elm terakhir
                deleteLastPeserta(peserta(P),Q);

                if (info(Q).jenisPeserta == "reguler"){
                        //mengecek apakah peserta tsb "reguler". Kalau iya, akan merubah jumlah peserta berkurang 1
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }

                //mengecek apakah kuota peserta masih tersedia
                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    //kuota tersedia. Akan dicari waiting_list pertama
                    adrPeserta waiting = findFirstWaitingList(peserta(P));
                    if (waiting != nil){
                        //waiting_list pertama ditemukan. Merubah menjadi reguler
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";


                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        cout<<endl;

                        //jumlah peserta menjadi bertambah 1
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }

            }else{
                adrPeserta R = first(peserta(P)); //assign R dengan first peserta event

                while(info(next(R)).namaPeserta != namaPeserta){
                    //mengulang sampai ditemukan yang after R adalah elemen yang mau dihapus
                    R = next(R);
                }
                deleteAfterPeserta(R,Q);

                //mengecek apakah peserta tsb "reguler". Kalau iya, akan merubah jumlah peserta berkurang 1
                if (info(Q).jenisPeserta == "reguler"){
                        info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
                }

                if (info(P).jumlahPeserta < info(P).kuotaMaks){
                    //kuota masih tersedia. Mengecek waiting_list pertama
                    adrPeserta waiting = findFirstWaitingList(peserta(P));

                    if (waiting != nil){
                        //waiting_list pertama ditemukan. Merubah jenis peserta menjadi reguler
                        string noKursi;
                        info(waiting).jenisPeserta = "reguler";

                        cout<<"EVENT: "<<info(P).namaEvent<<endl;
                        cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                        cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" ";
                        cin>>noKursi;
                        cout<<endl;


                        //jumlah peserta menjadi bertambah 1
                        info(waiting).noKursi = noKursi;
                        info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                    }
                }
            }
            Q = next(Q);
        }
        P = next(P);
    }
    */
    adrEvent P = first(L);
    while (P != nil){
        adrPeserta Q = findPeserta(peserta(P),namaPeserta);
        if (Q != nil){
            deletePeserta(peserta(P),namaPeserta,Q);
            //mengecek apakah peserta tsb "reguler". Kalau iya, akan merubah jumlah peserta berkurang 1
            if (info(Q).jenisPeserta == "reguler"){
                    info(P).jumlahPeserta = info(P).jumlahPeserta - 1;
            }

            //mengecek apakah kuota peserta masih tersedia
            if (info(P).jumlahPeserta < info(P).kuotaMaks){
                //kuota tersedia. Akan dicari waiting_list pertama

                adrPeserta waiting = findFirstWaitingList(peserta(P));
                if (waiting != nil){
                    //waiting_list pertama ditemukan. Merubah menjadi reguler
                    string noKursi;
                    info(waiting).jenisPeserta = "reguler";

                    cout<<"EVENT: "<<info(P).namaEvent<<endl;
                    cout<<"Waiting list teratas adalah "<<info(waiting).namaPeserta<<endl;
                    cout<<"Masukkan no. kursi peserta "<<info(waiting).namaPeserta<<" : ";
                    cin>>noKursi;
                    cout<<endl;

                    //jumlah peserta menjadi bertambah 1
                    info(waiting).noKursi = noKursi;
                    info(P).jumlahPeserta = info(P).jumlahPeserta + 1;
                }
            }
        }
        P = next(P);
    }
}

void showAlldataEvent(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua event dan data pesertanya sudah ditampilkan
**/
    adrEvent P = first(L);
    int i = 1;
    int k = 1;

    if (P != nil){
        //event tidak ksosong

        while(P != nil){

            //data dari event ditampilkan
            cout<<"["<<i<<"]"<<endl;
            cout<<"Nama event           |"<<info(P).namaEvent<<endl;
            cout<<"Jenis event          |"<<info(P).jenisEvent<<endl;
            cout<<"Tanggal pelaksanaan  |"<<info(P).tanggalPelaksanaan<<endl;
            cout<<"Tempat pelaksanaan   |"<<info(P).tempatPelaksanaan<<endl;
            cout<<"Jumlah peserta       |"<<info(P).jumlahPeserta<<endl;
            cout<<"Kuota maksimum       |"<<info(P).kuotaMaks<<endl;

            adrPeserta Q = first(peserta(P)); //assign Q dengan peserta pertama dalam event P

            if(Q != nil){
                //peserta tidak kosong
                cout<<endl;
                cout<<">>>>> DAFTAR PESERTA <<<<<"<<endl;

                while (Q != nil){
                    cout<<"["<<k<<"]"<<endl;
                    cout<<"No Peserta        |"<<info(Q).noPeserta<<endl;
                    cout<<"Nama Peserta      |"<<info(Q).namaPeserta<<endl;
                    cout<<"E-mail Peserta    |"<<info(Q).emailPeserta<<endl;
                    cout<<"No. Telp. Peserta |"<<info(Q).noTelpPeserta<<endl;
                    cout<<"No. Kursi         |"<<info(Q).noKursi<<endl;
                    cout<<"Jenis Peserta     |"<<info(Q).jenisPeserta<<endl;
                    cout<<endl;
                    Q = next(Q);
                    k = k + 1;
                }
            }else{
                //peserta tidak kosong
                cout<<endl;
                cout<<"Peserta kosong"<<endl;
            }
        cout<<endl;
        i = i + 1;
        P = next(P);
        cout<<"Klik sembarang untuk melanjutkan ke event selanjutnya"<<endl;
        getch();
        system("cls");
        }

    }else{
        //event kosong
        cout<<"List Event kosong!"<<endl;
    }
    cout<<"Semua event sudah ditampilkan"<<endl;
    cout<<"Klik sembarang untuk melanjutkan"<<endl;
}

void showAlldataEventTertentu(listEvent L, adrEvent P){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong dan adrEvent P yang akan ditampilkan pesertanya
    F.S. event tsb dan data pesertanya sudah ditampilkan
**/
    int k = 1; //penomoran

    //data dari event ditampilkam
    cout<<"Nama event           |"<<info(P).namaEvent<<endl;
    cout<<"Jenis event          |"<<info(P).jenisEvent<<endl;
    cout<<"Tanggal pelaksanaan  |"<<info(P).tanggalPelaksanaan<<endl;
    cout<<"Tempat pelaksanaan   |"<<info(P).tempatPelaksanaan<<endl;
    cout<<"Jumlah peserta       |"<<info(P).jumlahPeserta<<endl;
    cout<<"Kuota maksimum       |"<<info(P).kuotaMaks<<endl;

    adrPeserta Q = first(peserta(P)); //assign Q = first peserta dari event
    if(Q != nil){
        //daftar peserta tdk kosong

        cout<<">>>>> DAFTAR PESERTA <<<<<"<<endl;
        while (Q != nil){
            cout<<"["<<k<<"]"<<endl;
            cout<<"No Peserta        |"<<info(Q).noPeserta<<endl;
            cout<<"Nama Peserta      |"<<info(Q).namaPeserta<<endl;
            cout<<"E-mail Peserta    |"<<info(Q).emailPeserta<<endl;
            cout<<"No. Telp. Peserta |"<<info(Q).noTelpPeserta<<endl;
            cout<<"No. Kursi         |"<<info(Q).noKursi<<endl;
            cout<<"Jenis Peserta     |"<<info(Q).jenisPeserta<<endl;
            cout<<endl;
            Q = next(Q);
            k = k + 1;
        }
        cout<<endl;

    }else{
        //daftar peserta kosonb
        cout<<endl;
        cout<<"Peserta kosong"<<endl;
    }
}

adrEvent findEvent0Peserta(listEvent L){
/**
    Mengembalikan alamat event dengan jumlah peserta = 0, dan nil jika tidak ditemukan.
**/
    adrEvent P = first(L); //assign

    while (P != nil){
        //mengulang sampai ujung listEvent
        if(info(P).jumlahPeserta == 0){
            return P;
        }
        P = next(P);
    }
    return nil;
}

void deleteEventKosong(listEvent &L){
/** I.S. terdefinisi sebuah listEvent L yang mungkin kosong
    F.S. semua event dengan jumlah peserta 0 sudah dihapus dari list
**/
    adrEvent P = findEvent0Peserta(L);
    adrEvent Q;
    if (P != nil){
        while(P != nil){
            deleteEventMaster(L,info(P).namaEvent,Q);
            P = findEvent0Peserta(L);
        }
    }else{
        cout<<"List Event kosong/ Tidak ada yang bisa dihapus."<<endl;
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
    cout<<"[14] Menampilkan semua event"<<endl;
    cout<<"[0]  Exit"<<endl;
    cout<<endl;

    cout<<"Masukkan pilihan: ";
    cin>>pilihan;

    while(1){
        //mengulang sampai berhasil
        if(cin.fail() || pilihan < 0 || pilihan > 14){
            //mengecek apabila user memasukkan string maka akan ada error atau pilihan tidak ada dalam menu

            //clear cin
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"INPUT INVALID"<<endl;
            getch();
            system("cls");

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
            cout<<"[14] Menampilkan semua event"<<endl;
            cout<<"[0]  Exit"<<endl;
            cout<<endl;

            cout<<"Masukkan pilihan: ";
            cin>>pilihan;
        }

        if(!cin.fail() && pilihan >= 0 && pilihan <= 14){
            //user tidak menginputkan string dan pilihan masuk dalam range menu
            return pilihan;
        }
    }
}

void showAllEvent(listEvent L){
/** I.S. terdefinisi sebuah listEvent L, mungkin kosong
    F.S. semua event sudah ditampilkan
**/
    adrEvent P = first(L);
    int i = 1;
    if (P != nil){
        while(P != nil){
            cout<<"["<<i<<"]"<<endl;
            cout<<"Nama event           |"<<info(P).namaEvent<<endl;
            cout<<"Jenis event          |"<<info(P).jenisEvent<<endl;
            cout<<"Tanggal pelaksanaan  |"<<info(P).tanggalPelaksanaan<<endl;
            cout<<"Tempat pelaksanaan   |"<<info(P).tempatPelaksanaan<<endl;
            cout<<"Jumlah peserta       |"<<info(P).jumlahPeserta<<endl;
            cout<<"Kuota maksimum       |"<<info(P).kuotaMaks<<endl;
            cout<<endl;
            i++;
            P = next(P);
        }
    }else{
        cout<<"List Event kosong!"<<endl;
    }
}







