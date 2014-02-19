/*
  bgLearn implementation
  Author : caki
*/
#include "bgLearn.h"
#include <vcl.h>
bgLearn::bgLearn(unsigned int width,unsigned int height)
{
init(width,height);
}

void bgLearn::init(unsigned int width,unsigned int height)
{
  Width=width;
  Height=height;
  frameCount=3;
  bgOgreniyor=false;
  bgVar=false;
}

bgLearn::~bgLearn()
{
  //RenkListesiTemizle();
  if(bgVar)
  {
    bgVar=false;
    for(int i=0;i<frameCount;i++)
      delete [](bgFrames[i]);
    delete [] bgFrames;
  }
}

void bgLearn::RenkListesiTemizle()
{
  try {
  for(int i=0;i<Width*Height;i++)
    Lists[i].~bgColorList();
  }
  catch(Exception &exc) {}
}

void bgLearn::Basla()
{
  Lists=new bgColorList[Width*Height];
  bgOgreniyor=true;
}
void bgLearn::Bitir()
{
  bgOgreniyor=false;
  for(int i=0;i<Width*Height;i++)
  {
    Lists[i].Sirala();
  }
  bgFrameleriOlustur();
  RenkListesiTemizle();
  bgVar=true;
}
void bgLearn::FrameEkle(unsigned char * Adres)
{
  for(int i=0;i<Width*Height;i++)
  {
    Lists[i].RenkArtir(Adres[i]);
  }
}

void bgLearn::bgFrameleriOlustur()
{
  bgFrames=new unsigned char*[frameCount];
  int bufferSize=Width*Height*1.5;
  for(int i=0;i<frameCount;i++)
  {
    bgFrames[i]=new unsigned char[bufferSize];
    for(int j=bufferSize/2;j<bufferSize;j++)
      bgFrames[i][j]=128;
    for(int j=0;j<bufferSize/3*2;j++)
    {
      bgFrames[i][j]=Lists[j].RenkVer(i);
    }
  }

}
