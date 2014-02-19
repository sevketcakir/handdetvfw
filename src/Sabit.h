//---------------------------------------------------------------------------

#ifndef SabitH
#define SabitH
#include <new>
#include "KonumList.cpp"
#include <math.h>
//---------------------------------------------------------------------------
class Sabit {
public:
  static char * HelloWorld()
  { return "Hello World!"; }

/*  static int ObjeSayisi(unsigned char * buffer,int gen,int yuks)
  {
    int os=0;
     for(int i=0;i<yuks;i++)
       for(int j=0;j<gen;j++)
       {
          int ind=gen*i+j;
          if(buffer[ind]==255)
          {
            Sabit::ObjeSil(buffer,gen,yuks,i,j);
            os++;
          }
       }

    return os;
  }*/

  static void Dilation(unsigned char * buffer,int gen,int yuks,unsigned char * rBuffer)
  {
     for(int i=1;i<yuks-1;i++)
       for(int j=1;j<gen-1;j++)
       {
         if(buffer[ i*gen + j ] == 255)
         {
            rBuffer[ (i-1)*gen + j ] =255;
            rBuffer[ (i+1)*gen + j ] =255;
            rBuffer[ i*gen + j-1 ] =255;
            rBuffer[ i*gen + j+1 ] =255;
         }
       }
  }

  static void Erosion(unsigned char * buffer,int gen,int yuks,unsigned char * rBuffer)
  {
     for(int i=1;i<yuks-1;i++)
       for(int j=1;j<gen-1;j++)
       {
            rBuffer[i*gen + j]=buffer[ i*gen + j ] & buffer[ (i-1)*gen + j ] & buffer[ (i+1)*gen + j ] & buffer[ i*gen + j-1 ] & buffer[ i*gen + j+1 ];
         /*if(buffer[ i*gen + j ] ==255 &&
            buffer[ (i-1)*gen + j ] ==255 &&
            buffer[ (i+1)*gen + j ] ==255 &&
            buffer[ i*gen + j-1 ] ==255 &&
            buffer[ i*gen + j+1 ] ==255)
            rBuffer[i*gen + j]=255;
         else
           rBuffer[i*gen + j]=0;*/
       }
  }

  static void IkiliResim(unsigned char * buffer,int gen,int yuks)
  {
     for(int i=0;i<yuks;i++)
       for(int j=0;j<gen;j++)
       {
         int ind=gen*i+j;
         if(buffer[ind]!=0)
           buffer[ind]=255;
       }
  }
  static void Fark(unsigned char * buffer,int gen,int yuks,unsigned char * rBuffer)
  {
     for(int i=0;i<yuks;i++)
       for(int j=0;j<gen;j++)
       {
         int ind=gen*i+j;
         /*if(buffer[ind]==255 && rBuffer[ind]==0)
           rBuffer[ind]=255;
         else
           rBuffer[ind]=0;*/
           rBuffer[ind]=rBuffer[ind]^buffer[ind];
       }
  }
  static void Fark2(unsigned char * buffer,int gen,int yuks,unsigned char * rBuffer)
  {
     for(int i=0;i<yuks;i++)
       for(int j=0;j<gen;j++)
       {
         int ind=gen*i+j;
         /*if(buffer[ind]==255 && rBuffer[ind]==0)
           rBuffer[ind]=255;
         else
           rBuffer[ind]=0;*/
           rBuffer[ind]=rBuffer[ind]&buffer[ind];
       }
  }
    static void KareCiz(unsigned char * buffer,int gen,int yuks,int x1,int y1,int x2,int y2,unsigned char renk)
    {
      x1=x1>0?x1:0;
      y1=y1>0?y1:0;
      for(int j=x1;j<=x2 && j<gen;j++)
      {
        buffer[y1*gen+j]=renk;
        buffer[y2*gen+j]=renk;
      }
      for(int i=y1;i<=y2 && i<yuks ;i++)
      {
        buffer[i*gen+x1]=renk;
        buffer[i*gen+x2]=renk;
      }
    }


  static void Objeler(unsigned char * buffer,int gen,int yuks,konumList * kl)
  {
     for(int i=0;i<yuks;i++)
       for(int j=0;j<gen;j++)
       {
          int ind=gen*i+j;
          if(buffer[ind]==255)
          {
            unsigned int xmin=j,xmax=j,ymin=i,ymax=i;
            Sabit::ObjeSil(buffer,gen,yuks,i,j,xmin,ymin,xmax,ymax);
            kl->add(xmin,ymin,xmax,ymax);
          }
       }

  }

  static void AgirlikMerkeziBul(unsigned char * buffer,int gen,int yuks,konumList * k1,unsigned char renk)
  {
        for(int i=0;i<k1->getCount();i++)
        {
          Konum * konum=k1->getKonum(i);
          bool bulundu=false;
          for(int x=konum->xMin;x<=konum->xMax && !bulundu;x++)
            for(int y=konum->yMin;y<=konum->yMax&& !bulundu ;y++)
            {
              int ind=y*gen+x;
              if(buffer[ind]==renk && !bulundu)
              {
                long aMerkeziX=x;
                long aMerkeziY=y;
                int xk=x,yk=y;
                int adet=0;
                int xtemp=x;
                int ytemp=y;
                while(Sabit::KomsuSinir(buffer,gen,yuks,xtemp,ytemp,xk,yk,renk,renk-1))
                {
                  xtemp=xk;
                  ytemp=yk;
                  aMerkeziX+=xk;
                  aMerkeziY+=yk;
                  adet++;
                  bulundu=true;
                }
                if(adet!=0)
                {
                aMerkeziX/=adet;
                aMerkeziY/=adet;
                }
                Sabit::KareCiz(buffer,gen,yuks,aMerkeziX-5,aMerkeziY-5,aMerkeziX+5,aMerkeziY+5,127);
              }
            }
        }
  }

  static void CisimCevre(unsigned char * buffer,int gen,int yuks,konumList * k1,unsigned char aRenk,unsigned char dRenk)
  {
     for(int cs=0;cs<k1->getCount();cs++)
     {
       Konum * konum=k1->getKonum(cs);
       for(int x=konum->xMin;x<=konum->xMax;x++)
       for(int y=konum->yMin;y<=konum->yMax;y++)
       {
         if(buffer[y*gen+x]==aRenk)
         {
           int xtemp=x,ytemp=y;
           int xk,yk;
           int count=1;
           while(Sabit::KomsuSinir(buffer,gen,yuks,xtemp,ytemp,xk,yk,aRenk,dRenk))
           {
             xtemp=xk;
             ytemp=yk;
             count++;
           }
           konum->Cevre=count;
         }
       }
     }
  }
  static void CisimAlan(unsigned char * buffer,int gen,int yuks,konumList * k1,unsigned char aRenk)
  {
     for(int cs=0;cs<k1->getCount();cs++)
     {
       Konum * konum=k1->getKonum(cs);
       int alan=0;
       konum->merkezX=0;
       konum->merkezY=0;
       for(int x=konum->xMin;x<=konum->xMax;x++)
       for(int y=konum->yMin;y<=konum->yMax;y++)
       {
         if(buffer[y*gen+x]==aRenk)
         {
           alan++;
           konum->merkezX+=x;
           konum->merkezY+=y;
         }
       }
       konum->merkezX/=alan;
       konum->merkezY/=alan;
       konum->Alan=alan;
     }
  }

  static void CircularityHesapla(konumList * kl)
  {
     for(int cs=0;cs<kl->getCount();cs++)
     {
       Konum * konum=kl->getKonum(cs);
       konum->Circularity=4.0*M_PI*(double)konum->Alan/((double)(konum->Cevre*konum->Cevre));
     }
  }

  static int Egrilik(unsigned char * buffer,int gen,int yuks,Konum * konum,unsigned char aRenk,unsigned char dRenk,double * eBuffer,int * xNokta,int * yNokta)
  {
      int count=0;
      for(int y=konum->yMin;y<=konum->yMax;y++)
        for(int x=konum->xMin;x<=konum->xMax;x++)
       {
         if(buffer[y*gen+x]==aRenk)
         {
           int basx=x,basy=y;
           int xtemp=x,ytemp=y;
           int xk,yk;
           xNokta[0]=x;
           yNokta[0]=y;
           double aci=0.0,sonaci=0.0;
           while(Sabit::KomsuSinir(buffer,gen,yuks,xtemp,ytemp,xk,yk,aRenk,dRenk))
           {

             //aci+=atan2(ytemp-konum->merkezY,xtemp-konum->merkezX)-sonaci;//Sabit::acilar[(xtemp-xk+1)*3+ytemp-yk+1];
             //aci+=sonaci-Sabit::acilar[(xtemp-xk+1)*3+ytemp-yk+1];
             //sonaci=atan2(ytemp-konum->merkezY,xtemp-konum->merkezX);//Sabit::acilar[(xtemp-xk+1)*3+ytemp-yk+1];
             //sonaci=Sabit::acilar[(xtemp-xk+1)*3+ytemp-yk+1];
             aci=Sabit::acilar[(xtemp-xk+1)*3+ytemp-yk+1];
             eBuffer[count++]=aci;
             xNokta[count]=xk;
             yNokta[count]=yk;
             xtemp=xk;
             ytemp=yk;
             //count++;
           }
             aci=Sabit::acilar[(xtemp-basx+1)*3+ytemp-basy+1];
             eBuffer[count++]=aci;
         }
       }

       return count;
  }

  static void KenarDonmeAcisi(double * buffer1,double * buffer2,int sayi)
  {
     double toplam=0.0;
     for(int i=0;i<sayi;i++)
     {
       double a1=0.0;//buffer1[i];
       double a2=buffer1[(i+1)%sayi]-buffer1[i];
       if(a2<0.0)
         a2+=360.0;
       double fark=a1-a2;
       if(fark<-180.0)
         fark+=360;
       toplam+=fark;
       buffer2[i]=toplam;
     }
  }

  static void MaxNokta(double * buffer,int sayi,int fark,int * minler,int minsay)
  {
    int lMax=buffer[0];
    int cMin=0;
    for(int i=1;i<sayi;i++)
    {
      if(buffer[i]>lMax)
        lMax=buffer[i];

      if(lMax-buffer[i]>fark)
        {
          minler[cMin++]=i;
          lMax=buffer[i];
        }
      if(cMin==minsay)
        break;
    }
  }

  static void GreyOpen(double * buffer1,double * buffer2,int sayi,int cap)
  {
    int max;
    for(int i=cap/2;i<sayi+cap/2;i++)
    {
      max=buffer1[(i-cap/2)%sayi];
      for(int j=i-cap/2;j<i+cap/2;j++)
      {
        if(buffer1[j%sayi]>max)
          max=buffer1[j%sayi];
      }
      buffer2[i%sayi]=max;
    }
  }

  static void Smooth(double * buffer1,double * buffer2,int sayi) // 7 parametreli smooth fonk.
  {
    for(int i=3;i<=sayi+2;i++)
    {
      double d1=buffer1[(i-3)%sayi];
      double d2=buffer1[(i-2)%sayi];
      double d3=buffer1[(i-1)%sayi];
      double d4=buffer1[i%sayi];
      double d5=buffer1[(i+1)%sayi];
      double d6=buffer1[(i+2)%sayi];
      double d7=buffer1[(i+3)%sayi];
      double min=(d1+2*d2+3*d3+4*d4+3*d5+2*d6+d7)/16;//(d1+2*d2+3*d3+2*d4+d5)/9;
      buffer2[i%sayi]=min;
    }

  }

  static void CizgiCiz(unsigned char * buffer,int gen,int yuks,int x0,int y0,int x1,int y1,unsigned char renk)
  {
     bool rotated=false;
   int dy = y1 - y0;
   int dx = x1 - x0;
   int stepx, stepy;
   int offset, max_offset;

   if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
   if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
   dy <<= 1;  // dy is now 2*dy
   dx <<= 1;  // dx is now 2*dx

   max_offset = gen*yuks;//320*Form1->Cols+240;

   offset = y0 * gen + x0;

   if ((offset >= 0) && (offset < max_offset))
      buffer[offset] = renk;
   else
      ;

   if (dx > dy)
   {
      int fraction = dy - (dx >> 1);  // same as 2*dy - dx
      while (x0 != x1)
      {
         if (fraction >= 0)
         {
            y0 += stepy;
            fraction -= dx;           // same as fraction -= 2*dx
         }
         x0 += stepx;
         fraction += dy;              // same as fraction -= 2*dy

         offset = y0 * gen + x0;

         if ((offset >= 0) && (offset < max_offset))
            buffer[offset] = renk;
         else
            ;
      }
   }
   else
   {
      int fraction = dx - (dy >> 1);
      while (y0 != y1)
      {
         if (fraction >= 0)
         {
            x0 += stepx;
            fraction -= dy;
         }
         y0 += stepy;
         fraction += dx;

         offset = y0 * gen + x0;

         if ((offset >= 0) && (offset < max_offset))
            buffer[offset] = renk;
         else
            ;
      }
   }


  }

  static void DuzResmeCevir(unsigned char * buffer,int gen,int yuks,int x1,int y1,int x2,int y2,unsigned char * duzResim,int olcek)
  {
    double oran=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))/(double)olcek;
    //double aci2=atan2(y2-y1,x2-x1);
    //double aci=aci2-M_PI_2;
    double aci2=atan2(y1-y2,x1-x2)+M_PI;
    double aci=aci2+M_PI_2;
    for(int i=0;i<olcek;i++)
      for(int j=0;j<olcek;j++)
      {
        unsigned int ort=0;
        int sayi=0;
        int xx=x1+cos(aci)*floor(oran*i)+cos(aci2)*floor(oran*j);
        int yy=y1+sin(aci)*floor(oran*i)+sin(aci2)*floor(oran*j);
        //int xx=x1+cos(aci)*ceil(oran*i)+cos(aci2)*ceil(oran*j);
        //int yy=y1+sin(aci)*ceil(oran*i)+sin(aci2)*ceil(oran*j);
        for(int x=0;x<ceil(oran);x++)
          for(int y=0;y<ceil(oran);y++)
          {
            //int xxx=xx+ceil(cos(aci)*x)+ceil(cos(aci2)*y);
            //int yyy=yy+ceil(sin(aci)*x)+ceil(sin(aci2)*y);
            int xxx=xx+(cos(aci)*x)+(cos(aci2)*y);
            int yyy=yy+(sin(aci)*x)+(sin(aci2)*y);
            int offset=yyy*gen+xxx;
            if(offset>=0 && offset<gen*yuks)
            {
              ort+=buffer[offset];
              //buffer[yyy*gen+xxx]=255;
              sayi++;
            }
          }
          if(sayi!=0)
          {
            duzResim[i*olcek+j]=(unsigned char)(ort/sayi);
          }
      }
  }



private:
  static void ObjeSil(unsigned char * buffer,int gen,int yuks,int x,int y,unsigned int &xMin,unsigned int &yMin,unsigned int &xMax,unsigned int &yMax)
  {
    buffer[x*gen+y]=254;
    int sat,sut;
    sat=x-1;sut=y-1;
    bool yok=true;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x-1;sut=y;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x-1;sut=y+1;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x;sut=y-1;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x;sut=y+1;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x+1;sut=y-1;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x+1;sut=y;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }
    sat=x+1;sut=y+1;
    if(yok && sat>=0 && sat<=yuks && sut>=0 && sut<=gen && buffer[sat*gen+sut]==255)
      {
      Sabit::MaxSetle(sut,sat,xMin,yMin,xMax,yMax);
      Sabit::ObjeSil(buffer,gen,yuks,sat,sut,xMin,yMin,xMax,yMax);
      yok=false;
      }

  }

  static void MaxSetle(int sut,int sat,unsigned int &xMin,unsigned int &yMin,unsigned int &xMax,unsigned int &yMax)
  {
    if(sat<yMin)
      yMin=sat;
    else if(sat>yMax)
      yMax=sat;
    if(sut<xMin)
      xMin=sut;
    else if(sut>xMax)
      xMax=sut;
  }

  static bool KomsuSinir(unsigned char * buffer,int gen,int yuks,int x,int y,int &xKomsu,int &yKomsu,unsigned char aranacakRenk,unsigned char degisecekRenk)
  {
        for(int i=0;i<8;i++)
        {
          int sutun=x+Sabit::xk[i];
          int satir=y+Sabit::yk[i];
          if(satir>0 && satir<yuks && sutun>0 && sutun<gen && buffer[satir*gen+sutun]==aranacakRenk)
          {
            buffer[satir*gen+sutun]=degisecekRenk;
            xKomsu=sutun;
            yKomsu=satir;
            return true;
          }
        }
    return false;
  }
  static const int xk[8];
  static const int yk[8];
  static const double acilar[9];
};

//const int Sabit::xk[8]={1,1,0,-1,-1,-1,0,1};
//const int Sabit::yk[8]={0,-1,-1,-1,0,1,1,1};

const int Sabit::xk[8]={0,1,1, 1, 0,-1,-1,-1};// Ýlk yön sað alt köþe oldu
const int Sabit::yk[8]={1,1,0,-1,-1,-1, 0, 1};// Ýlk yön sað alt köþe oldu
const double Sabit::acilar[9]={135, 180, 225, 90, 0, 270, 45, 0, 315};
#endif
