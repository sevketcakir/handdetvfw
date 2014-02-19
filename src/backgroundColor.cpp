/*
  backgroundColor implementation
  Author : caki
*/
#include "backgroundColor.h"
backgroundColor::backgroundColor()
{
  Intensity=0;
  Count=0;
}

backgroundColor::backgroundColor(unsigned char intensity,unsigned int count)
{
  Intensity=intensity;
  Count=count;
}

backgroundColor::backgroundColor(unsigned char intensity)
{
  Intensity=intensity;
  Count=0;
}
