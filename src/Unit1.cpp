//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "bgLearn.h"
#include "Sabit.h"
#include <time.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
bool elResmiKaydet=false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
yuv2=true;
katsayi=2;
rgb=false;
bg=new bgLearn(1,1);
KonumList=new konumList();
zaman=clock();
FPS=0;
bgOgreniyor=false;
}
//---------------------------------------------------------------------------
//---------------------Fonksiyonlar
int ObjeSayisi(unsigned char * buffer,int gen,int yuks)
{
  return 5;
}
void GriyeCevir(unsigned char * buffer,unsigned int size)
{
    for(int i=0;i<size;i+=3)
    {
        //unsigned char *pt=(buffer+i);
        //unsigned int ort=(*pt + *(pt+1)+ *(pt+2))/3;
        unsigned int ort=(buffer[i]+buffer[i+1]+buffer[i+2])/3;
        ort=ort>255?255:ort;
        buffer[i/3]=(unsigned char)ort;
    }

}
void RenkliyeCevir(unsigned char * buffer,unsigned int size)
{
    for(int i=size-1;i>=0;i-=3)
    {
        //unsigned char *pt=(buffer+i);
        //unsigned int ort=((*pt)+(*pt+1)+(*pt+2))/3;
        //ort=ort>255?255:ort;
        //buffer[i/3]=(unsigned char)ort;
        buffer[i]=buffer[i/3];
        buffer[i-1]=buffer[i/3];
        buffer[i-2]=buffer[i/3];
    }

}
//---------------------Fonksiyonlar
//---------------------------------------------------------------------------//
//                                                                           //
//      LRESULT CALLBACK OnVideoBuffer(HWND hwnd,LPVIDEOHDR lpVHdr)          //
//      Bufferda bir çerçeve oluþtuðunda otomatik olarak çaðrýlýr.           //
//      Parametreler capture penceresinin handleý ve bir LPVIDEOHDR yapýsýdýr//
//      LPVIDEOHDR yapýsýnýn lpData üyesi bufferý,                           //
//      dwBufferLength üyesi ise buffer boyutunu tutar.                      //
//      Gelen buffer isteðe baðlý olarak ekrana çizilir.                     //
//      Bu ise hem kullanýcýya hem de programcýya esneklik saðlar.           //
//                                                                           //
//---------------------------------------------------------------------------//
LRESULT CALLBACK OnVideoBuffer(HWND hwnd,LPVIDEOHDR lpVHdr)
{
 //---------------------------------------------------------------------------//
 //Video kaynaðýndan gelen bufferý frame dizisine kopyala
 //Bundan sonraki iþlemler frame dizisi üzerinden gerçekleþtirilecek
      //enter critical section
        Form1->videoSec->Acquire();

        //Zaman hesaplama
        if(clock()-Form1->zaman<1000)
          Form1->FPS++;
        else
        {
          Form1->zaman=clock();
          Form1->StatusBar1->SimpleText=IntToStr(Form1->FPS)+" FPS";
          Form1->FPS=0;
        }

          CopyMemory(Form1->TempBuffer1,lpVHdr->lpData,Form1->Rows*Form1->Cols*3);
          //GriyeCevir(Form1->TempBuffer1,Form1->Rows*Form1->Cols*3);
          GriyeCevir(Form1->TempBuffer1,Form1->Rows*Form1->Cols*3);
        bool elAlgilandi=false;
        if(Form1->bgOgreniyor)
            Form1->EA->ArkaplanEkle(Form1->TempBuffer1);
        else
          elAlgilandi=Form1->EA->ElAlgila(Form1->TempBuffer1,Form1->CSpinEdit1->Value*0.01,Form1->CheckBox1->Checked);

        if(Form1->videoCaptureStarted /*&& elAlgilandi*/)
        {
          CopyMemory(Form1->currentVideoFrame,Form1->EA->OrjinalResim,Form1->Cols*Form1->Rows);
          //CopyMemory(Form1->currentVideoFrame,Form1->EA->TempBuffer1,Form1->Cols*Form1->Rows);
          CopyMemory(Form1->TempBuffer2,Form1->EA->TempBuffer2,Form1->Cols*Form1->Rows);
          RenkliyeCevir(Form1->currentVideoFrame,Form1->Cols*Form1->Rows*3);
          RenkliyeCevir(Form1->TempBuffer2,128*128*3);

          if(elResmiKaydet)
          {
            Graphics::TBitmap * bitmap=new Graphics::TBitmap();
            bitmap->Width=128;
            bitmap->Height=128;
            for(int i=0;i<128;i++)
            for(int j=0;j<128;j++)
            {
              unsigned char a=Form1->TempBuffer2[i*128+j];
              bitmap->Canvas->Pixels[j][i]=TColor(RGB(a,a,a));
            }
            Form1->dlgResimKaydet->Execute();
            bitmap->SaveToFile(Form1->dlgResimKaydet->FileName);
            elResmiKaydet=false;
          }
        }

        //Zaman hesaplama


        Form1->videoFrameReady = true;
        Form1->videoSec->Release();

 //---------------------------------------------------------------------------//

 //---------------------------------------------------------------------------//
 //Ýsteðe baðlý olarak çerçeveyi ekrana çiz
 if(Form1->goster->Checked)
 {
 DrawDibDraw(Form1->hdd,
             Form1->hdc,
             0,
             0,
             Form1->VideoPanel->ClientWidth,
             Form1->VideoPanel->ClientHeight,
             &Form1->BMPInfo->bmiHeader,lpVHdr->lpData,
             0,
             0,
             Form1->BMPInfo->bmiHeader.biWidth,
             Form1->BMPInfo->bmiHeader.biHeight,
             DDF_SAME_HDC||DDF_HALFTONE);
    //int ssize=Form1->BMPInfo->bmiHeader.biSize;
    //Form1->BMPInfo->bmiHeader.biSize=Form1->Cols*Form1->Rows*1.5;
 DrawDibDraw(Form1->hdd2,
             Form1->hdc2,
             0,
             0,
             Form1->VideoPanel2->ClientWidth,
             Form1->VideoPanel2->ClientHeight,
             &Form1->BMPInfo->bmiHeader,Form1->currentVideoFrame,
             //&Form1->BMPInfo->bmiHeader,lpVHdr->lpData,
             0,
             0,
             Form1->BMPInfo->bmiHeader.biWidth,
             Form1->BMPInfo->bmiHeader.biHeight,
             DDF_SAME_HDC||DDF_SAME_DRAW
             //DDF_SAME_HDC||DDF_HALFTONE
             );
    //Form1->BMPInfo->bmiHeader.biSize=ssize;
  if(elAlgilandi)
  {
             int size=Form1->BMPInfo->bmiHeader.biSizeImage;
             int w=Form1->BMPInfo->bmiHeader.biWidth;
             int h=Form1->BMPInfo->bmiHeader.biHeight;
             Form1->BMPInfo->bmiHeader.biWidth=128;
             Form1->BMPInfo->bmiHeader.biHeight=128;
             //Form1->BMPInfo->bmiHeader.biSize=128*128*3;
             Form1->BMPInfo->bmiHeader.biSizeImage=128*128*3;
  DrawDibDraw(Form1->hdd3,
             Form1->hdc3,
             0,
             0,
             Form1->VideoPanel3->ClientWidth,
             Form1->VideoPanel3->ClientHeight,
             &Form1->BMPInfo->bmiHeader,Form1->TempBuffer2,
             0,
             0,
             128,128,
             //Form1->BMPInfo->bmiHeader.biWidth,
             //Form1->BMPInfo->bmiHeader.biHeight,
             DDF_SAME_HDC||DDF_HALFTONE);
             Form1->BMPInfo->bmiHeader.biWidth=w;
             Form1->BMPInfo->bmiHeader.biHeight=h;
             Form1->BMPInfo->bmiHeader.biSizeImage=size;
  }


 }
 //---------------------------------------------------------------------------//
 return TRUE;
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
   videoFrameSize = 1;

   videoCaptureStarted = false;
   videoFrameReady = false;

   videoSec = new TCriticalSection;
   currentVideoFrame = new char[1];

 //---------------------------------------------------------------------------//
 //Create video capture window
   hWndC = capCreateCaptureWindow ("", // window name if pop-up
                                   WS_SYSMENU,// window style
                                   0,0, 160, 120,// window position and dimensions
                                   Form1->Handle,
                                   nID /* child ID */);
 //---------------------------------------------------------------------------//

  //---------------------------------------------------------------------------//
 //Yüklü sürücüleri bul
   char szDeviceName[80];
   char szDeviceVersion[80];
   unsigned int numDrivers=0;
   for (int wIndex = 0; wIndex < 10; wIndex++)
   {
    if (capGetDriverDescription (wIndex, szDeviceName,
        sizeof (szDeviceName), szDeviceVersion,
        sizeof (szDeviceVersion)))
    {
        // Append name to list of installed capture drivers
        // and then let the user select a driver to use.
        numDrivers++;
    }
   }
 //---------------------------------------------------------------------------//
        if(numDrivers == 0)
        {
                ShowMessage("Video sürücüsü bulunamadý");
                return;
        }
 //---------------------------------------------------------------------------//
 //Video bufferýn çizimi VideoPanel üzerine yapýlacak
        hdd = DrawDibOpen();
        hdc = GetDC(VideoPanel->Handle);
        hdd2 = DrawDibOpen();
        hdc2 = GetDC(VideoPanel2->Handle);
        hdd3 = DrawDibOpen();
        hdc3 = GetDC(VideoPanel3->Handle);
        hdd4 = DrawDibOpen();
        hdc4 = GetDC(VideoPanel4->Handle);


 //---------------------------------------------------------------------------//
        if(!capDriverConnect(hWndC, 0))
        {
                ShowMessage("Sürücüyle baðlantý kurulamadý!!!");
                return;
        }
 //---------------------------------------------------------------------------//
 //CallBack fonksiyonunu setle
        capSetCallbackOnVideoStream(hWndC,&OnVideoBuffer);
 //---------------------------------------------------------------------------//
        capDriverGetCaps(hWndC, &CapDriverCaps, sizeof (CAPDRIVERCAPS));
        capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS));

        StartCapture();
 //---------------------------------------------------------------------------//
 //Sorun yok
 //Butonlarý etkinleþtir
        StartStopButton->Enabled = true;
        FormatButton->Enabled = true;
        SourceButton->Enabled = true;
 //---------------------------------------------------------------------------//
 //---------------------------------------------------------------------------//

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{

 StopCapture();
 capDriverDisconnect(hWndC);
 //if(bg->bgOgreniyor)
 //  bg->Bitir();
 //bg->~bgLearn();
 Sleep(500);
 delete [] (Form1->TempBuffer1);
 delete [] (Form1->TempBuffer2);
 delete [] (Form1->EgrilikBuffer);
 delete [] (Form1->TempEgrilik);
 delete [] (Form1->xDizi);
 delete [] (Form1->yDizi);
 KonumList->removeAll();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------//
//                                                                           //
//      StartCapture()                                                       //
//      Capture iþleminin baþlatýlmasýný saðlar.                             //
//      Capture baþlayýnca her frame sonunda OnVideBuffer CALLBACK           //
//      fonksiyonu otomatik olarak çaðrýlýr.                                 //           //
//                                                                           //
//---------------------------------------------------------------------------//
bool __fastcall TForm1::StartCapture()
{
 //---------------------------------------------------------------------------//
 //Video formatýný al
        GetVideoFormat();
 //---------------------------------------------------------------------------//
 //---------------------------------------------------------------------------//
 //Capture parametrelerini oku
        if(!capCaptureGetSetup(hWndC,&parms,sizeof(parms)))
        return false;
 //---------------------------------------------------------------------------//
 //---------------------------------------------------------------------------//
 //Gerekli capture parametrelerini deðiþtir
        parms.dwRequestMicroSecPerFrame = 33333;
        parms.fMakeUserHitOKToCapture = false;
        parms.vKeyAbort = false;
        parms.fAbortLeftMouse = false;
        parms.fAbortRightMouse = false;
        parms.fYield = true;
        parms.fCaptureAudio = false;
        parms.wPercentDropForError = 50;
 //---------------------------------------------------------------------------//
 //Capture parametrelerini setle
        if(!capCaptureSetSetup(hWndC,&parms,sizeof(CAPTUREPARMS)))
        return false;

 //---------------------------------------------------------------------------//
 //---------------------------------------------------------------------------//
 //Capture iþlemini baþlat
        if(capCaptureSequenceNoFile(hWndC))
        {
                videoCaptureStarted = true;
                StartStopButton->Hint = "Görüntü yakalamayý durdur";
        }
        else
        {
         videoCaptureStarted = false;
         return false;
        }
 //---------------------------------------------------------------------------//
 return true;
}

//---------------------------------------------------------------------------//
//                                                                           //
//      StopCapture()                                                        //
//                                                                           //
//---------------------------------------------------------------------------//
bool __fastcall TForm1::StopCapture()
{
 if(!videoCaptureStarted)
  return true;
 videoSec->Acquire();
 if(capCaptureStop(hWndC))
 {
  videoCaptureStarted = false;
  StartStopButton->Hint = "Görüntü yakalamayý baþlat";
  videoSec->Release();
  return true;
 }
 videoSec->Release();
 return false;
}


//---------------------------------------------------------------------------//
//                                                                           //
//      GetVideoFormat()                                                     //
//                                                                           //
//---------------------------------------------------------------------------//
void inline TForm1::GetVideoFormat()
{
 unsigned int size;

 size = capGetVideoFormatSize(hWndC);
 if(size != infoSize)
 {
  //enter critical section
        videoSec->Acquire();
        if(infoSize != 0)
         delete []BMPInfo;
        infoSize = size;
        BMPInfo = (BITMAPINFO *)malloc(infoSize);
        videoSec->Release();
  //exit critical section
 }

 capGetVideoFormat(hWndC,BMPInfo,infoSize);
 //---------------------------------------------------------------------------//
 //set video format to YUV2
 if(BMPInfo->bmiHeader.biCompression==844715353)
 {
 Form1->yuv2=true;
 Form1->katsayi=2;
 BMPInfo->bmiHeader.biBitCount = 16;
 BMPInfo->bmiHeader.biCompression = 844715353;
 BMPInfo->bmiHeader.biSizeImage = BMPInfo->bmiHeader.biWidth
                                  * BMPInfo->bmiHeader.biHeight
                                  * BMPInfo->bmiHeader.biBitCount / 8;
 }
 else
 {
 if(BMPInfo->bmiHeader.biCompression==0)
 {
 Form1->yuv2=false;
 Form1->rgb=true;
 Form1->katsayi=3;
 BMPInfo->bmiHeader.biBitCount = 24;
 BMPInfo->bmiHeader.biCompression = 0;
 BMPInfo->bmiHeader.biSizeImage = BMPInfo->bmiHeader.biWidth
                                  * BMPInfo->bmiHeader.biHeight
                                  * BMPInfo->bmiHeader.biBitCount / 8;
 }
 else
 {
 Form1->yuv2=false;
 Form1->rgb=false;
 Form1->katsayi=1.5;
 BMPInfo->bmiHeader.biBitCount = 12;
 BMPInfo->bmiHeader.biCompression = 808596553;
 BMPInfo->bmiHeader.biSizeImage = BMPInfo->bmiHeader.biWidth
                                  * BMPInfo->bmiHeader.biHeight
                                  * BMPInfo->bmiHeader.biBitCount / 8;
 }
 }
 capSetVideoFormat(hWndC,BMPInfo,infoSize);
 //---------------------------------------------------------------------------//
 Cols = ((int)(((float)(Form1->BMPInfo->bmiHeader.biWidth)/16)+0.75)<<4);
 Rows = ((int)(((float)(Form1->BMPInfo->bmiHeader.biHeight)/16)+0.75)<<4);


 if(videoFrameSize != Cols*Rows*Form1->katsayi)//BMPInfo->bmiHeader.biSizeImage)
 {
  //enter critical section
        videoSec->Acquire();
        delete []currentVideoFrame;
        videoFrameSize = Cols*Rows*Form1->katsayi;
        currentVideoFrame = new char[videoFrameSize];
        Form1->TempBuffer1=new unsigned char[videoFrameSize];
        Form1->TempBuffer2=new unsigned char[videoFrameSize];
        Form1->EgrilikBuffer=new double[videoFrameSize];
        Form1->TempEgrilik=new double[videoFrameSize];
        Form1->xDizi=new int[videoFrameSize];
        Form1->yDizi=new int[videoFrameSize];
        EA=new elAlgilama(Cols,Rows);

        if(yuv2)
        {
          for(int i=0; i<Form1->videoFrameSize; i+=2)
          {
            Form1->currentVideoFrame[i+1]=128;
          }
        }
        else
        {
          for(int i=(2*Form1->videoFrameSize/3); i<Form1->videoFrameSize; i++)
          {
            Form1->currentVideoFrame[i]=128;
          }
        }
        CopyMemory(TempBuffer1,currentVideoFrame,videoFrameSize);
        CopyMemory(TempBuffer2,currentVideoFrame,videoFrameSize);
        videoSec->Release();
  //exit critical section
 }
}

//---------------------------------------------------------------------------



void __fastcall TForm1::SetResolution(const int & width, const int & height)
{
 unsigned int size;

 if(!videoCaptureStarted)
 return;

 while(!StopCapture()) {}
 Sleep(500);
 size = capGetVideoFormatSize(hWndC);
 if(size != infoSize)
 {
  //enter critical section
        videoSec->Acquire();
        if(infoSize != 0)
         delete []BMPInfo;
        infoSize = size;
        BMPInfo = (BITMAPINFO *)malloc(infoSize);
        videoSec->Release();
  //exit critical section
 }

 capGetVideoFormat(hWndC,BMPInfo,infoSize);
 //---------------------------------------------------------------------------//
 //set resolution
 BMPInfo->bmiHeader.biWidth = width;
 BMPInfo->bmiHeader.biHeight = height;
 BMPInfo->bmiHeader.biSizeImage = BMPInfo->bmiHeader.biWidth
                                  * BMPInfo->bmiHeader.biHeight
                                  * BMPInfo->bmiHeader.biBitCount / 8;

 Sleep(500);
 capSetVideoFormat(hWndC,BMPInfo,infoSize);
 Sleep(500);
 while(!StartCapture()){}
}
//---------------------------------------------------------------------------













void __fastcall TForm1::N1Click(TObject *Sender)
{
 if(videoCaptureStarted)
  {
   StopCapture();
   VideoPanel->Repaint();
  }
 else
  StartCapture();

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Biim1Click(TObject *Sender)
{
 if(!CapDriverCaps.fHasDlgVideoFormat)
  return;

 if(videoCaptureStarted){
        Form1->Enabled = false;
        StopCapture();
        while(!capDlgVideoFormat(hWndC)){}
        //GetVideoFormat();
        StartCapture();
        Form1->Enabled = true;
 }
 else
 {
        while(!capDlgVideoFormat(hWndC)){}
        GetVideoFormat();
 }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Kaynak1Click(TObject *Sender)
{
 if (!CapDriverCaps.fHasDlgVideoSource)
  return;

 if(videoCaptureStarted)
 {
  Form1->Enabled = false;
  StopCapture();

  while(!capDlgVideoSource(hWndC)){}

  StartCapture();
  Form1->Enabled = true;
 }
 else
 {
  while(!capDlgVideoSource(hWndC)){}
  GetVideoFormat();
 }

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Arkaplanren1Click(TObject *Sender)
{
if(!bgOgreniyor)
{
  //Button1->Caption="Bitir";
  Arkaplanren1->Caption="Arkaplan Öðrenmeyi Durdur";
  //bg->~bgLearn();
  //bg->init(Cols,Rows);
  //bg->Basla();
}
else
{
  //Button1->Caption="Baþla";
  Arkaplanren1->Caption="Arkaplan Öðren";
  //bg->Bitir();

}
bgOgreniyor=!bgOgreniyor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AlglananResmiKaydet1Click(TObject *Sender)
{
elResmiKaydet=true;
}
//---------------------------------------------------------------------------

