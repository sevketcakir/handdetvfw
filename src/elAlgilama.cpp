//---------------------------------------------------------------------------
/*
** El algýlama
** Þevket Umut ÇAKIR
*/
//---------------------------------------------------------------------------
#include "elAlgilama.h"
#include <new>
#include <math.h>
#include <windows.h>
elAlgilama::elAlgilama(int genislik,int yukseklik)
{
  init();
  Genislik=genislik;
  Yukseklik=yukseklik;
  BufferBoyutu=genislik*yukseklik*1.5;
  PikselSayisi=genislik*yukseklik;
  TempBuffer1=new unsigned char[BufferBoyutu];
  TempBuffer2=new unsigned char[BufferBoyutu];
  OrjinalResim=new unsigned char[BufferBoyutu];
  EgrilikBuffer1=new double[PikselSayisi];
  EgrilikBuffer2=new double[PikselSayisi];
  xDizi=new int[PikselSayisi];
  yDizi=new int[PikselSayisi];
  ArkaplanOgrenme=new bgLearn(genislik,yukseklik);
  KonumListesi=new konumList();
}

elAlgilama::~elAlgilama()
{
  delete [] (OrjinalResim);
  delete [] (TempBuffer1);
  delete [] (TempBuffer2);
  delete [] (EgrilikBuffer1);
  delete [] (EgrilikBuffer2);
  delete [] (xDizi);
  delete [] (yDizi);
  if(ArkaplanOgrenme->bgOgreniyor)
    ArkaplanOgrenme->Bitir();
  ArkaplanOgrenme->~bgLearn();
}

void elAlgilama::init()
{
  ArkaplanFark=15;
  ArkaplanOgreniyor=false;
}

void elAlgilama::ArkaplanEkle(unsigned char * buffer)
{
  if(!ArkaplanOgrenme->bgOgreniyor)
    ArkaplanOgrenme->Basla();
  ArkaplanOgreniyor=true;

  ArkaplanOgrenme->FrameEkle(buffer);
}

bool elAlgilama::ElAlgila(unsigned char * buffer,double oran,bool teknik)
{
  bool donenDeger=false;
  if(ArkaplanOgrenme->bgOgreniyor)
    ArkaplanOgrenme->Bitir();
  ArkaplanOgreniyor=false;

  if(!ArkaplanOgrenme->bgVar)
    return false;

  //Arkaplandan ayýrt etme
  for(int i=0;i<PikselSayisi;i++)
  {
    if(abs(buffer[i]-ArkaplanOgrenme->bgFrames[0][i])<15 || abs(buffer[i]-ArkaplanOgrenme->bgFrames[1][i])<15 || abs(buffer[i]-ArkaplanOgrenme->bgFrames[2][i])<15 )
      OrjinalResim[i]=0;
    else
      OrjinalResim[i]=buffer[i];
  }

  CopyMemory(TempBuffer1,OrjinalResim,PikselSayisi);
  Sabit::IkiliResim(TempBuffer1,Genislik,Yukseklik);
  Sabit::Erosion(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::Erosion(TempBuffer2,Genislik,Yukseklik,TempBuffer1);
  Sabit::Erosion(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::Erosion(TempBuffer2,Genislik,Yukseklik,TempBuffer1);

  Sabit::Dilation(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::Dilation(TempBuffer2,Genislik,Yukseklik,TempBuffer1);
  Sabit::Dilation(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::Dilation(TempBuffer2,Genislik,Yukseklik,TempBuffer1);

  Sabit::KareCiz(TempBuffer1,Genislik,Yukseklik,0,0,Genislik-1,Yukseklik-1,0);
  Sabit::Erosion(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::Dilation(TempBuffer2,Genislik,Yukseklik,TempBuffer1);
  Sabit::Fark(TempBuffer1,Genislik,Yukseklik,TempBuffer2);
  Sabit::KareCiz(TempBuffer2,Genislik,Yukseklik,0,0,Genislik-1,Yukseklik-1,0);

  Sabit::Objeler(TempBuffer2,Genislik,Yukseklik,KonumListesi);

  KonumListesi->cisimEle();

  Sabit::CisimCevre(TempBuffer2,Genislik,Yukseklik,KonumListesi,254,253);
  Sabit::CisimAlan(TempBuffer1,Genislik,Yukseklik,KonumListesi,255);
  Sabit::CircularityHesapla(KonumListesi);
  if(KonumListesi->getCount()>0)
  {
    for(int i=0;i<KonumListesi->getCount();i++)
    {
      Konum * konum=KonumListesi->getKonum(i);

      //Aðýrlýk merkezine kare çiz

      if(konum->Circularity>0.1 && konum->Circularity<0.3)
      {
        int sayi=Sabit::Egrilik(TempBuffer2,Genislik,Yukseklik,konum,253,254,EgrilikBuffer1,xDizi,yDizi);
        Sabit::KenarDonmeAcisi(EgrilikBuffer1,EgrilikBuffer2,sayi);

        Sabit::Smooth(EgrilikBuffer2,EgrilikBuffer1,sayi);
        Sabit::Smooth(EgrilikBuffer1,EgrilikBuffer2,sayi);

        int minler[4]={0};
        Sabit::MaxNokta(EgrilikBuffer2,sayi,130,minler,4);
                if(minler[0]!=0&&minler[1]!=0&&minler[2]!=0&&minler[3]!=0&&minler[0]!=sayi-1&&minler[1]!=sayi-1&&minler[2]!=sayi-1&&minler[3]!=sayi-1)
                {

                  int maxUzaklik=0,n1,n2,n3;
                  for(int k=0;k<4;k++)
                    for(int l=k;l<4;l++)
                    {
                      int xfark=xDizi[minler[k]]-xDizi[minler[l]];
                      int yfark=yDizi[minler[k]]-yDizi[minler[l]];
                      int uzaklik=xfark*xfark+yfark*yfark;
                      if(uzaklik>maxUzaklik)
                      {
                        maxUzaklik=uzaklik;
                        n1=k;
                        n2=l;
                      }
                    }

                  if(n1==(n2+1)%4)
                  {
                    n1=(n1+1)%4;
                    int temp=n2;
                    n2=n1;
                    n1=temp;
                  }
                  else
                  {
                    n2=(n2+1)%4;
                  }
                  n3=(n2+1)%4;

                  int x1,y1,x2,y2,x3,y3,x4,y4;
                  if(teknik)
                  {
                  int opUzunlugu=OrtaParmakUzunlugu(minler[n2],minler[n3],sayi);

                  double aci=atan2(yDizi[minler[n1]]-yDizi[minler[n2]],xDizi[minler[n1]]-xDizi[minler[n2]])-M_PI;
                  int ox=(xDizi[minler[n1]]+xDizi[minler[n2]])/2+cos(aci-M_PI_2)*opUzunlugu/2;
                  int oy=(yDizi[minler[n1]]+yDizi[minler[n2]])/2+sin(aci-M_PI_2)*opUzunlugu/2;

                  opUzunlugu*=oran*sqrt(2)/2;

                  x1=ox+cos(aci+M_PI/4)*opUzunlugu;
                  y1=oy+sin(aci+M_PI/4)*opUzunlugu;
                  x2=ox+cos(aci+3*M_PI/4)*opUzunlugu;
                  y2=oy+sin(aci+3*M_PI/4)*opUzunlugu;
                  x3=ox+cos(aci-M_PI/4)*opUzunlugu;
                  y3=oy+sin(aci-M_PI/4)*opUzunlugu;
                  x4=ox+cos(aci+5*M_PI/4)*opUzunlugu;
                  y4=oy+sin(aci+5*M_PI/4)*opUzunlugu;
                  }
                  else
                  {
                  x1=xDizi[minler[n1]];
                  x2=xDizi[minler[n2]];
                  y1=yDizi[minler[n1]];
                  y2=yDizi[minler[n2]];



                  double uzunluk=sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1))/8.0;

                  double aci=atan2(y2-y1,x2-x1)-M_PI_2;
                  //Form1->Caption=atan2(y2-y1,x2-x1);
                  x1+=uzunluk*cos(aci);
                  x2+=uzunluk*cos(aci);
                  y1+=uzunluk*sin(aci);
                  y2+=uzunluk*sin(aci);

                  x1+=uzunluk*cos(aci-M_PI_2);
                  x2+=uzunluk*cos(aci+M_PI_2);
                  y1+=uzunluk*sin(aci-M_PI_2);
                  y2+=uzunluk*sin(aci+M_PI_2);


                  x3=x1+uzunluk*cos(aci)*10;
                  x4=x2+uzunluk*cos(aci)*10;
                  y3=y1+uzunluk*sin(aci)*10;
                  y4=y2+uzunluk*sin(aci)*10;
                  int tempx=x1,tempy=y1;
                  x1=x2; y1=y2; x2=tempx; y2=tempy;
                  tempx=x3; tempy=y3;
                  x3=x4;y3=y4;x4=tempx;y4=tempy;

                  }
                  for(int i=0;i<Genislik*Yukseklik*1.5;i++)
                  {
                    TempBuffer2[i]=127;
                  }
                  //Sabit::DuzResmeCevir(OrjinalResim,Genislik,Yukseklik,1,1,129,129,TempBuffer2,128);
                  Sabit::DuzResmeCevir(OrjinalResim,Genislik,Yukseklik,x1,y1,x2,y2,TempBuffer2,128);
                  donenDeger=true;
                  //Sabit::CizgiCiz(TempBuffer2,Genislik,Yukseklik,x1,y1,x2,y2,127);
                  //Sabit::CizgiCiz(TempBuffer2,Genislik,Yukseklik,x1,y1,x3,y3,127);
                  //Sabit::CizgiCiz(TempBuffer2,Genislik,Yukseklik,x2,y2,x4,y4,127);
                  //Sabit::CizgiCiz(TempBuffer2,Genislik,Yukseklik,x3,y3,x4,y4,127);

                  Sabit::CizgiCiz(OrjinalResim,Genislik,Yukseklik,x1,y1,x2,y2,255);
                  Sabit::CizgiCiz(OrjinalResim,Genislik,Yukseklik,x1,y1,x3,y3,255);
                  Sabit::CizgiCiz(OrjinalResim,Genislik,Yukseklik,x2,y2,x4,y4,255);
                  Sabit::CizgiCiz(OrjinalResim,Genislik,Yukseklik,x3,y3,x4,y4,255);

                  /*
                  unsigned char renk=127;
                  for(int n=0;n<4;n++)
                  {
                    if(n==n1 || n==n2)
                      renk=251;
                    else renk=127;
                    Sabit::KareCiz(TempBuffer2,Genislik,Yukseklik,
                           xDizi[minler[n]]-2,yDizi[minler[n]]-2,xDizi[minler[n]]+2,yDizi[minler[n]]+2,renk);
                  }
                  */
                }
                //Sabit::KareCiz(TempBuffer2,Genislik,Yukseklik,
                //  konum->xMin,konum->yMin,konum->xMax,konum->yMax ,255);



      }
    }
  }
  Sabit::Fark2(TempBuffer1,Genislik,Yukseklik,OrjinalResim);

  KonumListesi->removeAll();

  return donenDeger;
}

int elAlgilama::OrtaParmakUzunlugu(int n1,int n2,int sayi)
{
  int uzunluk=0,tuzunluk=0;
  int x=(xDizi[n1]+xDizi[n2])/2;
  int y=(yDizi[n1]+yDizi[n2])/2;
  //int artis=n2-n2>0?1:-1;
  n2=n2<n1?n2+sayi:n2;
  for(int i=n1;i<=n2;i++)
  {
    tuzunluk=(xDizi[i%sayi]-x)*(xDizi[i%sayi]-x)+(yDizi[i%sayi]-y)*(yDizi[i%sayi]-y);
    if(tuzunluk>uzunluk)
      uzunluk=tuzunluk;
  }
  return sqrt(uzunluk);
}
