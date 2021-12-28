#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <iostream>
#include <peserta.h>
using namespace std;

/** Pendefinisian **/
#define nil NULL
#define first(L) L.first
#define last(L) L.last
#define next(P) (P)->next
#define prev(P) (P)->prev
#define peserta(P) (P)->peserta //di setiap event terdapat list peserta
#define info(P) (P)->info

typedef struct elmEvent *adrEvent
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


#endif // EVENT_H_INCLUDED
