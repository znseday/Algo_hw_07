object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'TestTree'
  ClientHeight = 653
  ClientWidth = 1191
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pnlDraw: TPanel
    Left = 0
    Top = 209
    Width = 1191
    Height = 444
    Align = alClient
    TabOrder = 0
    object imgDraw: TImage
      Left = 1
      Top = 1
      Width = 1189
      Height = 442
      Align = alClient
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 599
      ExplicitHeight = 471
    end
  end
  object pnlTop: TPanel
    Left = 0
    Top = 0
    Width = 1191
    Height = 209
    Align = alTop
    TabOrder = 1
    ExplicitLeft = 1
    ExplicitTop = -5
    object Label1: TLabel
      Left = 391
      Top = 144
      Width = 13
      Height = 13
      Caption = 'N'
    end
    object EditNewItem: TEdit
      Left = 32
      Top = 21
      Width = 105
      Height = 21
      MaxLength = 5
      NumbersOnly = True
      TabOrder = 0
      Text = '10'
    end
    object btnAdd: TButton
      Left = 32
      Top = 83
      Width = 105
      Height = 25
      Caption = 'Add'
      TabOrder = 1
      OnClick = btnAddClick
    end
    object btnRemove: TButton
      Left = 143
      Top = 18
      Width = 113
      Height = 27
      Caption = 'Remove'
      TabOrder = 2
      OnClick = btnRemoveClick
    end
    object btnStandartTest: TButton
      Left = 280
      Top = 19
      Width = 193
      Height = 26
      Caption = #1053#1077#1073#1086#1083#1100#1096#1086#1081' '#1089#1090#1072#1088#1090#1086#1074#1099#1081' '#1085#1072#1073#1086#1088
      TabOrder = 3
      OnClick = btnStandartTestClick
    end
    object btnClearAll: TButton
      Left = 143
      Top = 83
      Width = 113
      Height = 25
      Caption = 'ClearAll'
      TabOrder = 4
      OnClick = btnClearAllClick
    end
    object btnPrintKPL: TButton
      Left = 200
      Top = 135
      Width = 153
      Height = 33
      Caption = #1042#1099#1074#1077#1089#1090#1080' '#1083#1080#1085#1077#1081#1085#1086' '#1050#1055#1051
      TabOrder = 5
      OnClick = btnPrintKPLClick
    end
    object btnPrintLKP: TButton
      Left = 32
      Top = 135
      Width = 153
      Height = 33
      Caption = #1042#1099#1074#1077#1089#1090#1080' '#1083#1080#1085#1077#1081#1085#1086' '#1051#1050#1055
      TabOrder = 6
      OnClick = btnPrintLKPClick
    end
    object EditTree: TEdit
      Left = 32
      Top = 174
      Width = 671
      Height = 21
      TabOrder = 7
    end
    object btnFind: TButton
      Left = 32
      Top = 51
      Width = 105
      Height = 26
      Caption = 'Find'
      TabOrder = 8
      OnClick = btnFindClick
    end
    object GroupBox1: TGroupBox
      Left = 504
      Top = 21
      Width = 171
      Height = 136
      Caption = #1056#1072#1073#1086#1090#1072#1090#1100' '#1089
      TabOrder = 9
      object rbBSTree: TRadioButton
        Left = 16
        Top = 24
        Width = 113
        Height = 17
        Caption = 'Simple Binary Tree'
        TabOrder = 0
      end
      object rbAVLTree: TRadioButton
        Left = 16
        Top = 47
        Width = 113
        Height = 17
        Caption = #1040#1042#1051' '#1044#1077#1088#1077#1074#1086
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object RadioButton3: TRadioButton
        Left = 16
        Top = 70
        Width = 113
        Height = 17
        Caption = #1044#1077#1082#1072#1088#1090#1086#1074#1086' '#1076#1077#1088#1077#1074#1086
        Enabled = False
        TabOrder = 2
      end
      object rbRBTree: TRadioButton
        Left = 16
        Top = 93
        Width = 113
        Height = 17
        Caption = 'std::set (RBTree)'
        TabOrder = 3
      end
    end
    object Memo: TMemo
      Left = 709
      Top = 1
      Width = 481
      Height = 207
      Align = alRight
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 10
    end
    object btnTest: TButton
      Left = 280
      Top = 91
      Width = 193
      Height = 38
      Caption = #1058#1077#1089#1090' '#1089#1086#1075#1083#1072#1089#1085#1086' '#1079#1072#1076#1072#1085#1080#1102
      TabOrder = 11
      OnClick = btnTestClick
    end
    object btnRemove_v2: TButton
      Left = 143
      Top = 51
      Width = 113
      Height = 25
      Caption = 'Remove_v2'
      TabOrder = 12
      OnClick = btnRemove_v2Click
    end
    object btnSmallRandom: TButton
      Left = 280
      Top = 51
      Width = 193
      Height = 25
      Caption = #1053#1077#1073#1086#1083#1100#1096#1086#1081' '#1089#1083#1091#1095#1072#1081#1085#1099#1081' '#1085#1072#1073#1086#1088
      TabOrder = 13
      OnClick = btnSmallRandomClick
    end
    object EditN: TEdit
      Left = 409
      Top = 141
      Width = 73
      Height = 21
      MaxLength = 10
      NumbersOnly = True
      TabOrder = 14
      Text = '100000'
    end
  end
end
