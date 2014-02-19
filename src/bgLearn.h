/*
  bgLearn header
  Author : caki
*/
#ifndef BGLEARN
#define BGLEARN
#include "bgColorList.h"
class bgLearn {
public:
bgLearn(unsigned int width,unsigned int height);
~bgLearn();
void Basla();
void Bitir();
void FrameEkle(unsigned char * adres);
void bgFrameleriOlustur();
void init(unsigned int width,unsigned int height);
unsigned char **bgFrames;
bool bgVar;
bool bgOgreniyor;
private:
int frameCount;
unsigned int Width;
unsigned int Height;
bgColorList * Lists;
void RenkListesiTemizle();
};
#endif
