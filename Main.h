//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Xls.h>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include <Grids.hpp>
#include "Types.h"
#include "Mtmm.h";
//---------------------------------------------------------------------------
class T_MainForm : public TForm
{
public:
	Series series;
	Load load;
	Dimensions dim;
	MMatrix mmm;
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MMFile;
        TMenuItem *MMOpen;
        TMenuItem *MMSave;
        TMenuItem *MMQuit;
        TMenuItem *MMHelp;
        TMenuItem *MMAbout;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TComboBox *CorrCombo;
        TButton *CountButton;
        TButton *DataButton;
        TGroupBox *GroupBox2;
        TCSpinEdit *CSpinEdit1;
	TStringGrid *SG;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
	TLabel *MethodLabel;
	TLabel *ConstructLabel;
	TEdit *MethodEdit;
	TEdit *ConstructEdit;
        void __fastcall DataButtonClick(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall MMOpenClick(TObject *Sender);
	void __fastcall CountButtonClick(TObject *Sender);
	void __fastcall MMQuitClick(TObject *Sender);
	void __fastcall MMAboutClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall MMSaveClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall T_MainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE T_MainForm *_MainForm;
//---------------------------------------------------------------------------
#endif
