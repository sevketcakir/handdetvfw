//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vfw.h>
#include <Graphics.hpp>
#include <Syncobjs.hpp>
#include <mmsystem.h>
#include <ExtCtrls.hpp>
#include <time.h>
#include "bgLearn.h"
#include "KonumList.cpp"
#include "elAlgilama.h"
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "CSPIN.h"
#define VIDEO_PORT 5965
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *StartStopButton;
        TButton *FormatButton;
        TButton *SourceButton;
        TPanel *VideoPanel;
        TCheckBox *goster;
        TGroupBox *GroupBox1;
        TPanel *VideoPanel3;
        TPanel *VideoPanel4;
        TStatusBar *StatusBar1;
        TPanel *VideoPanel2;
        TChart *Chart1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TCheckBox *cbFonksiyonCizdir;
        TButton *Button1;
        TButton *Button2;
        TMainMenu *MainMenu1;
        TMenuItem *Video1;
        TMenuItem *N1;
        TMenuItem *Biim1;
        TMenuItem *Kaynak1;
        TMenuItem *k1;
        TMenuItem *ElAlglama1;
        TMenuItem *Arkaplanren1;
        TMenuItem *AlglananResmiKaydet1;
        TSaveDialog *dlgResimKaydet;
        TCSpinEdit *CSpinEdit1;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall Biim1Click(TObject *Sender);
        void __fastcall Kaynak1Click(TObject *Sender);
        void __fastcall Arkaplanren1Click(TObject *Sender);
        void __fastcall AlglananResmiKaydet1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        bool __fastcall StartCapture();
        bool __fastcall StopCapture();
        void inline GetVideoFormat();
        void __fastcall SetResolution(const int & width, const int & height);

        HWND hWndC;//capture window handle
        HDRAWDIB hdd, hdd2,hdd3,hdd4;
        HDC hdc, hdc2,hdc3,hdc4;
        //video capture
        CAPDRIVERCAPS CapDriverCaps;
        CAPSTATUS CapStatus;
        CAPTUREPARMS parms;
        BITMAPINFO *BMPInfo;

        int nID;
        float katsayi;
        bool videoCaptureStarted, videoFrameReady, yuv2, rgb;
        unsigned char *currentVideoFrame;
        unsigned int videoFrameSize,infoSize, Cols, Rows;
        TCriticalSection *videoSec;

        bool bgOgreniyor;
        unsigned char * TempBuffer1;
        unsigned char * TempBuffer2;
        double * EgrilikBuffer;
        double * TempEgrilik;
        int * xDizi,*yDizi;
        bgLearn *bg;
        konumList * KonumList;
        clock_t zaman;
        unsigned int FPS;
        elAlgilama *EA;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
