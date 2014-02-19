#ifndef KONUM_LIST
#define KONUM_LIST
struct Konum
{
public:
    Konum *Next;
    unsigned int xMin;
    unsigned int yMin;
    unsigned int xMax;
    unsigned int yMax;
    unsigned int Cevre;
    unsigned int Alan;
    double Circularity;
    int merkezX;
    int merkezY;
};

class konumList
{
private:
    Konum *First;
    Konum *Last;
    unsigned int Count;

public:
    konumList()
    {
        this->First = 0;
        this->Last = 0;
        this->Count = 0;
    }

    void add(unsigned int xmin,unsigned int ymin,unsigned int xmax,unsigned int ymax)
    {
        Konum *New = 0;

        New = new Konum;
        New->xMin = xmin;
        New->yMin = ymin;
        New->xMax = xmax;
        New->yMax = ymax;
        New->Next = 0;

        if(this->First == 0)
        {
            this->First = New;
            this->Last = New;
        }
        else
        {
            this->Last->Next = New;
            this->Last = New;
        }

        this->Count++;
    }

    void removeAll()
    {
        unsigned int n = 0;
        Konum *Temp = this->First;
        Konum * Temp1;
        for(; n < Count && Temp->Next != 0; n++)
        {
           Temp1=Temp;
           Temp = Temp->Next;
           delete(Temp1);
        }
        this->First = 0;
        this->Last = 0;
        this->Count = 0;
    }

    Konum *getKonum(unsigned int Index) const
    {
        unsigned int n = 0;
        Konum *Temp = this->First;

        if(Index < this->Count)
        {
            for(; n < Index && Temp->Next != 0; n++)
                Temp = Temp->Next;
        }

        return (Temp);
    }

    void remove(unsigned int Index)
    {
      unsigned int n;
      Konum * Temp=0,* Temp1=0;
      for(n=0,Temp=First;n<Index && Temp!=0;n++,Temp=Temp->Next)
        Temp1=Temp;
      if(Temp!=0)
      {
        if(Temp1!=0)
          Temp1->Next=Temp->Next;
        else
          First=Temp->Next;
        if(n==Count-1)
          Last=Temp1;
        delete(Temp);
        Count--;
        if(Count==0)
        {
          First=0;
          Last=0;
        }
      }
    }

    void remove(Konum * silinecek)
    {
        unsigned int n = 0;
        Konum *Temp = this->First;
        Konum * Temp1;

            for(; n < Count && Temp->Next != 0; n++)
            {
                Temp1=Temp;
                Temp = Temp->Next;
                if(silinecek==Temp)
                  break;
            }
        if(silinecek==Temp)
        {
            Temp1->Next=Temp->Next;
            delete(Temp);
            Count--;
            if(Count==0)
            {
                First=0;
                Last=0;
            }

        }
    }


    int getCount() const
    {
        return (Count);
    }

    void cisimEle()
    {
      if(Count==0)
        return;
      Konum * * konumlar=new Konum* [Count];
      int kIndex=0;
      for(int i=0;i<Count;i++)
        konumlar[i]=0;
      for(int i=0;i<Count-1;i++)
        for(int j=i+1;j<Count;j++)
        {
          Konum * k1=getKonum(i);
          Konum * k2=getKonum(j);
          if(k1!=0 && k2!=0 &&
          k1->xMax<k2->xMax && k1->yMax<k2->yMax && k1->xMin>k2->xMin && k1->yMin>k2->yMin)
          {
            bool var=false;
            for(int l=0;l<kIndex;l++)
              if(konumlar[l]==k1)
                var=true;
            if(!var)
            konumlar[kIndex++]=k1;
          }
          else if(k1!=0 && k2!=0 &&
          k2->xMax<k1->xMax && k2->yMax<k1->yMax && k2->xMin>k1->xMin && k2->yMin>k1->yMin)
          {
            bool var=false;
            for(int l=0;l<kIndex;l++)
              if(konumlar[l]==k2)
                var=true;
            if(!var)
              konumlar[kIndex++]=k2;
          }

        }
        for(int i=0;i<kIndex;i++)
        {
          if(konumlar[i]==0)
            int a=0;
          remove(konumlar[i]);
        }
        delete [](konumlar);
    }
};
#endif

