#include "bgColor.h" 


bgColor::bgColor()
{
  Intensity=0;
  Count=0;
}

bgColor::bgColor(unsigned char intensity,unsigned int count)
{
  Intensity=intensity;
  Count=count;
}

bgColor::bgColor(unsigned char intensity)
{
  Intensity=intensity;
  Count=0;
}
