#ifndef PESERTA_H_INCLUDED
#define PESERTA_H_INCLUDED

#include <iostream>
using namespace std;

/** Pendefinisian **/
#define nil NULL
#define first(L) L.first
#define last(L) L.last
#define next(P) (P)->next
#define prev(P) (P)->prev
#define info(P) (P)->info

typedef struct elmPeserta *adrPeserta;
typedef struct peserta infotypePeserta;

struct peserta{
    string noPeserta, namaPeserta, emailPeserta, noTelpPeserta;
    string noKursi;
    string jenisPeserta;
};

/** listPeserta adalah double linked list dengan pointer last**/
struct elmPeserta{
    adrPeserta prev,next;
    infotypePeserta info;
};

struct listPeserta{
    adrPeserta first;
    adrPeserta last;
};

void createListPeserta(listPeserta &L);
adrPeserta findPeserta(listPeserta L, string cariNamaPeserta);
adrPeserta findFirstWaitingList(listPeserta L);
adrPeserta newElmPeserta(infotypePeserta input);
infotypePeserta createPeserta();
void insertLastPeserta(listPeserta &L, adrPeserta P);
void deleteFirstPeserta(listPeserta &L, adrPeserta &P);
void deleteLastPeserta(listPeserta &L, adrPeserta &P);
void deleteAfterPeserta(adrPeserta prec, adrPeserta &P);
void deletePeserta(listPeserta &L, string namaPeserta, adrPeserta &Q);
void showListPeserta(listPeserta L);



#endif // PESERTA_H_INCLUDED
