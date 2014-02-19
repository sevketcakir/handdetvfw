object Form1: TForm1
  Left = 231
  Top = 154
  Width = 680
  Height = 466
  Caption = 'Avu'#231'Yakala v1.1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 192
    Top = 272
    Width = 26
    Height = 13
    Caption = '/ 100'
  end
  object VideoPanel4: TPanel
    Left = 320
    Top = 0
    Width = 320
    Height = 240
    Caption = 'VideoPanel4'
    TabOrder = 7
  end
  object StartStopButton: TButton
    Left = 440
    Top = 288
    Width = 81
    Height = 25
    Caption = 'Ba'#351'lat / Durdur'
    TabOrder = 0
    Visible = False
  end
  object FormatButton: TButton
    Left = 336
    Top = 248
    Width = 75
    Height = 25
    Caption = 'Format'
    TabOrder = 1
    Visible = False
  end
  object SourceButton: TButton
    Left = 416
    Top = 248
    Width = 75
    Height = 25
    Caption = 'Source'
    TabOrder = 2
    Visible = False
  end
  object VideoPanel: TPanel
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Caption = 'VideoPanel'
    TabOrder = 3
  end
  object goster: TCheckBox
    Left = 144
    Top = 248
    Width = 113
    Height = 17
    Caption = 'Videoyu g'#246'r'#252'nt'#252'le'
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
  object GroupBox1: TGroupBox
    Left = 528
    Top = 280
    Width = 105
    Height = 49
    Caption = 'Arkaplan '#214#287'renme'
    TabOrder = 5
    Visible = False
    object Button1: TButton
      Left = 14
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Ba'#351'la'
      TabOrder = 0
    end
  end
  object VideoPanel3: TPanel
    Left = 8
    Top = 248
    Width = 128
    Height = 128
    Caption = 'VideoPanel3'
    TabOrder = 6
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 389
    Width = 664
    Height = 19
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object VideoPanel2: TPanel
    Left = 320
    Top = 0
    Width = 320
    Height = 240
    Caption = 'VideoPanel3'
    TabOrder = 9
  end
  object Chart1: TChart
    Left = 16
    Top = 600
    Width = 993
    Height = 113
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'E'#287'rilik Fonksiyonu (Curvature Function)')
    Legend.Visible = False
    View3D = False
    TabOrder = 10
    Visible = False
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Transparent = True
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = 11896070
      LinePen.Style = psDot
      LinePen.Width = 2
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object cbFonksiyonCizdir: TCheckBox
    Left = 344
    Top = 552
    Width = 153
    Height = 17
    Caption = 'E'#287'rilik Fonksiyonunu '#199'izdir'
    TabOrder = 11
    Visible = False
  end
  object Button2: TButton
    Left = 496
    Top = 248
    Width = 137
    Height = 25
    Caption = 'Alg'#305'lanan Resmi Kaydet'
    TabOrder = 12
    Visible = False
  end
  object CSpinEdit1: TCSpinEdit
    Left = 144
    Top = 272
    Width = 41
    Height = 22
    MaxValue = 100
    MinValue = 1
    TabOrder = 13
    Value = 67
  end
  object CheckBox1: TCheckBox
    Left = 144
    Top = 304
    Width = 121
    Height = 17
    Caption = 'Teknik1 / Teknik2'
    TabOrder = 14
  end
  object MainMenu1: TMainMenu
    Left = 608
    Top = 336
    object Video1: TMenuItem
      Caption = 'Video'
      object N1: TMenuItem
        Caption = '&Ba'#351'lat / Durdur'
        OnClick = N1Click
      end
      object Biim1: TMenuItem
        Caption = 'B&i'#231'im'
        OnClick = Biim1Click
      end
      object Kaynak1: TMenuItem
        Caption = '&Kaynak'
        OnClick = Kaynak1Click
      end
      object k1: TMenuItem
        Caption = '&'#199#305'k'#305#351
      end
    end
    object ElAlglama1: TMenuItem
      Caption = 'El Alg'#305'lama'
      object Arkaplanren1: TMenuItem
        Caption = 'Arkaplan '#214#287'ren'
        OnClick = Arkaplanren1Click
      end
      object AlglananResmiKaydet1: TMenuItem
        Caption = 'Alg'#305'lanan Resmi Kaydet'
        OnClick = AlglananResmiKaydet1Click
      end
    end
  end
  object dlgResimKaydet: TSaveDialog
    DefaultExt = '*.bmp'
    FileName = 'resim'
    Filter = 'Bitmap|*.bmp|*.BMP'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 576
    Top = 336
  end
end
