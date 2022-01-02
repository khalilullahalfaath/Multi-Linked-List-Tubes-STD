#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <iostream>
#include "peserta.h"
using namespace std;

/** Pendefinisian **/
#define nil NULL
#define first(L) L.first
#define last(L) L.last
#define next(P) (P)->next
#define prev(P) (P)->prev
#define peserta(Q) (Q)->peserta //di setiap event terdapat list peserta
#define info(P) (P)->info

typedef struct elmEvent *adrEvent;
typedef struct event infotypeEvent;

struct event{
    string namaEvent, jenisEvent, tanggalPelaksanaan;
    int kuotaMaks, jumlahPeserta;
};

/** List Parent adalah double linked list dengan last**/
struct elmEvent{
    adrEvent prev, next;
    infotypeEvent info;
    listPeserta peserta;
};

struct listEvent{
    adrEvent first,last;
};

void createListEvent(listEvent &L);
adrEvent findEvent(listEvent L, string cariNamaEvent);
infotypeEvent createNewEvent();
adrEvent newElmEvent(infotypeEvent input);
void insertLastEvent(listEvent &L, adrEvent P);
void insertLastEvent(listEvent &L, adrEvent P);
void deleteFirstEvent(listEvent &L, adrEvent &Q);
void deletelastEvent(listEvent &L, adrEvent &Q);
void deleteAfterEvent(adrEvent prec, adrEvent &Q);
void deleteEventMaster(listEvent &L, string namaEvent, adrEvent &Q);
void joinEvent(listEvent &L, adrPeserta P);
void showjumlahPesertasemuaEvent(listEvent L);
void showAllEventName(listEvent L);
void showAlldataEvent(listEvent L);
void deletePesertaEventTertentu(listEvent &events, string namaEvent, string namaPeserta, adrPeserta &Q);
void deletePesertaDiSemuaEvent(listEvent &L, string namaPeserta);
void showAlldataEventTertentu(listEvent L, adrEvent P);
void showEventTersedia(listEvent L);
void deleteEventKosong(listEvent &L);
int menu();

#endif // EVENT_H_INCLUDED
