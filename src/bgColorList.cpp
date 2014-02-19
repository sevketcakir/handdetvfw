#include "bgColorList.h"
#include <new>

bgColorList::bgColorList()
{
  Colors=new bgColor*[256];
  for(int i=0;i<256;i++)
    Colors[i]=0x00000000;
  index=0x00;
}

bgColorList::~bgColorList()
{
  for(int i=0;i<index;i++)
    if(Colors[i]!=NULL)
      delete(Colors[i]);
  if(Colors!=NULL)
    delete [](Colors);

}

void bgColorList::Sirala()
{
  for(unsigned char i=0;i<index;i++)
    for(unsigned char j=i;j<index;j++)
    {
      if((*Colors[j]).Count>(*Colors[i]).Count)
      {
        bgColor * temp=Colors[i];
        Colors[i]=Colors[j];
        Colors[j]=temp;
      }
    }
}

void bgColorList::RenkArtir(unsigned char renk)
{
  int i=RenkIndeksi(renk);
  if(i==-1)
    { RenkEkle(renk); i=index-1; }
  (*Colors[i]).Count++;

}


void bgColorList::RenkEkle(unsigned char renk)
{
  Colors[index++]=new bgColor(renk);
}

int bgColorList::RenkIndeksi(unsigned char renk)
{
  for(unsigned char i=0;i<index;i++)
    if((*Colors[i]).Intensity==renk)
      return i;
  return -1;
}

unsigned char bgColorList::RenkVer(int ind)
{
  if(Colors[ind]!=0x00000000)
    return (*Colors[ind]).Intensity;
  else
  {
    while(Colors[ind]==0x00000000)
    {
      ind--;
    }
    return (*Colors[ind]).Intensity;
  }
}

bool bgColorList::RenkVarmi(unsigned char renk)
{
  for(int i=0;i<256;i++)
    if(Colors[i]!=0x00000000)
    {
      if((*Colors[i]).Intensity==renk)
        return true;
    }
    else
      return false;
  return false;
}

