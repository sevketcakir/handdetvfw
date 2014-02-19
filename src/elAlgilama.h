//---------------------------------------------------------------------------
/*
** El algýlama
** Þevket Umut ÇAKIR
*/
//---------------------------------------------------------------------------

#ifndef elAlgilamaH
#define elAlgilamaH
#include "Sabit.h"
#include "bgLearn.h"
#include "KonumList.cpp"
//---------------------------------------------------------------------------
class elAlgilama {
public:
//Public Fonksiyonlar
elAlgilama(int genislik,int yukseklik);
void ArkaplanEkle(unsigned char * buffer);
bool ElAlgila(unsigned char * buffer,double oran,bool teknik);
int OrtaParmakUzunlugu(int n1,int n2,int sayi);

~elAlgilama();
//Public Degiþkenler
//private:
//Private Fonksiyonlar
void init();
//Private Degiþkenler
int Genislik;
int Yukseklik;
int BufferBoyutu;
int PikselSayisi;
bool ArkaplanOgreniyor;
int ArkaplanFark;
unsigned char * TempBuffer1;
unsigned char * TempBuffer2;
unsigned char * OrjinalResim;
double * EgrilikBuffer1;
double * EgrilikBuffer2;
int * xDizi;
int * yDizi;
bgLearn * ArkaplanOgrenme;
konumList * KonumListesi;
private:
};

#endif
