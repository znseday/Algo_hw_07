//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>


#include "MySimpleTree_draw.h"
#include "UnitUniqueRandom.h"
#include "MyAVLTree_draw.h"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlDraw;
	TImage *imgDraw;
	TPanel *pnlTop;
	TEdit *EditNewItem;
	TButton *btnAdd;
	TButton *btnRemove;
	TButton *btnStandartTest;
	TButton *btnClearAll;
	TButton *btnPrintKPL;
	TButton *btnPrintLKP;
	TEdit *EditTree;
	TButton *btnFind;
	TGroupBox *GroupBox1;
	TRadioButton *rbBSTree;
	TRadioButton *rbAVLTree;
	TRadioButton *RadioButton3;
	TMemo *Memo;
	TButton *btnTest;
	TButton *btnRemove_v2;
	TButton *btnSmallRandom;
	TEdit *EditN;
	TLabel *Label1;
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnPrintKPLClick(TObject *Sender);
	void __fastcall btnPrintLKPClick(TObject *Sender);
	void __fastcall btnStandartTestClick(TObject *Sender);
	void __fastcall btnClearAllClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnRemoveClick(TObject *Sender);
	void __fastcall btnFindClick(TObject *Sender);
	void __fastcall btnRemove_v2Click(TObject *Sender);
	void __fastcall btnSmallRandomClick(TObject *Sender);
	void __fastcall btnTestClick(TObject *Sender);
private:	// User declarations

//	bool CheckCorrectCount();


public:		// User declarations

	BSTreeDraw<int>  *MyBSTree;
	AVLTreeDraw<int> *MyAVLTree;

	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
