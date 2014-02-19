#include "bgColor.h"
#ifndef BGCOLORLIST
#define BGCOLORLIST
class bgColorList {
public:
bgColor ** Colors;
bgColorList();
~bgColorList();
void RenkArtir(unsigned char renk);
void Sirala();
unsigned char RenkVer(int ind);
private:
bool RenkVarmi(unsigned char renk);
int RenkIndeksi(unsigned char renk);
void RenkEkle(unsigned char renk);

unsigned char index;
};
#endif
