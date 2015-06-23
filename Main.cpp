//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
T_MainForm *_MainForm;
//---------------------------------------------------------------------------
__fastcall T_MainForm::T_MainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------







#include <DataForm.h>
#include <HelpForm.h>
#include <HelpProgramForm.h>
#include <HelpMethodForm.h>
void __fastcall T_MainForm::DataButtonClick(TObject *Sender)
{
        _DataForm->Show();        
}
//---------------------------------------------------------------------------

void __fastcall T_MainForm::N1Click(TObject *Sender)
{
        _DataForm->Show();        
}
//---------------------------------------------------------------------------



void __fastcall T_MainForm::MMOpenClick(TObject *Sender)
{
	TOpenDialog* openDialog = new TOpenDialog(this);
	openDialog->Options << ofFileMustExist;
	openDialog->Filter = "Файлы Excel (*.xls)|*.xls";
	if(!openDialog->Execute())
		return;
	Xls xls;
	try{
		load = xls.load(openDialog->Files->Strings[0].c_str());
	}catch(Error::Xls e){
		ShowMessage(e.msg);
	}
	dim = load.dim;
	_DataForm->mtx = load.mat;
	_DataForm->dim = load.dim;
	MethodEdit->Text = dim.methods;
	ConstructEdit->Text = dim.constructs;
	_DataForm->Show();
	series = Mtmm::series(load);
	
}
//---------------------------------------------------------------------------


AnsiString _fmt(double v, int cnt){
	AnsiString fmt = "0.";
	for(int i = 0; i < cnt; i++)
		fmt += "0";
	return AnsiString::FormatFloat(fmt, v);
}


void __fastcall T_MainForm::CountButtonClick(TObject *Sender)
{
	if(!series.size()){
		ShowMessage("Данные не загружены");
		return;
	};
	MMatrix m = Mtmm::mtmm(CorrCombo->ItemIndex, load.dim, series[0]);
	mmm = m;
	SG->RowCount = dim.methods*(dim.constructs + 1)+2;
	SG->ColCount = dim.methods*(dim.constructs + 1)+2;
	int cC = dim.constructs;
	for(int m_i = 0; m_i < dim.methods; m_i++)
		for(int m_j = 0; m_j < dim.methods; m_j++){
			if(m_j > m_i) break;
			for(int c_i = 0; c_i < dim.constructs; c_i++){
				for(int c_j = 0; c_j < dim.constructs; c_j++){
					if( (m_j == m_i) && (c_j > c_i) ) break;
					SG->Cells[2+m_j*(cC+1)+c_j][2+m_i*(cC+1)+c_i] = \
					_fmt(m[m_i*cC+c_i][m_j*cC+c_j].corr, CSpinEdit1->Value);
				};
			};
		};
	for(int i = 0; i < dim.methods; i++){
		SG->Cells[2 + i*(dim.constructs+1)][0] = "М"+AnsiString(i+1);
		SG->Cells[0][2 + i*(dim.constructs+1)] = "М"+AnsiString(i+1);
		for(int j = 0; j < dim.constructs; j++){
			SG->Cells[2 + i*(dim.constructs+1)+j][1] = "K"+AnsiString(j+1);
			SG->Cells[1][2 + i*(dim.constructs+1)+j] = "K"+AnsiString(j+1);
		};
	};
}
//---------------------------------------------------------------------------

void __fastcall T_MainForm::MMQuitClick(TObject *Sender)
{
	Application->Terminate();	
}
//---------------------------------------------------------------------------

void __fastcall T_MainForm::MMAboutClick(TObject *Sender)
{
	_HelpProgramForm->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall T_MainForm::N4Click(TObject *Sender)
{
	_HelpForm->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall T_MainForm::N5Click(TObject *Sender)
{
	_HelpMethodForm->ShowModal();	
}
//---------------------------------------------------------------------------

int _s2m(int coord, Dimensions dim){//Преобразует координату на экране в матричную координату
	int cC = dim.constructs;
	coord -=2;
	return (coord%(cC+1)) + cC*coord/(cC+1);
};
bool _canPaint(int coord, Dimensions dim){//Нужно ли здесь рисовать
	int cC = dim.constructs;
	coord -=2;
	return (coord%(cC+1)) != cC;
}
void __fastcall T_MainForm::SGDrawCell(TObject *Sender, int ACol, int ARow,
	  TRect &Rect, TGridDrawState State)
{
	// Здесь прорисовка цвета
	if(ACol > ARow || (ACol < 2) || (ARow < 2) || !mmm.size()) return;
	if(!_canPaint(ACol, dim) || !_canPaint(ARow, dim)) return;
	const int t2c[] = {clBlue, clRed, 0x000066ff, clGreen};
	SG->Canvas->Brush->Color = t2c[mmm[_s2m(ARow, dim)][_s2m(ACol, dim)].type];
	SG->Canvas->FillRect(Rect);
	SG->Canvas->Font->Color = clWhite;
	SG->Canvas->TextOut(Rect.Left+2, Rect.Top+2, SG->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------

 void showP(Book *book,Sheet *sheet, char *str, unsigned short row,unsigned short col,  Color color, FillPattern pattern = FILLPATTERN_SOLID)
    {
		libxl::Format* format = book->addFormat();
		format->setFillPattern(pattern);
		format->setPatternForegroundColor(color);
		sheet->writeBlank(row, col, format);
		sheet->writeStr(row, col, str);
	}
void __fastcall T_MainForm::MMSaveClick(TObject *Sender)
{
 	TSaveDialog* saveDialog = new TSaveDialog(this);
	saveDialog->Filter = "Файлы Excel (*.xls)|*.xls";
	if(!saveDialog->Execute())
		return;
	MMatrix m = mmm;
	int cC = dim.constructs;
	Book* book = xlCreateBook();
	Sheet *sheet = book->addSheet("1");
		const int t2c[] = {
			COLOR_BLUE,
			COLOR_RED,
			COLOR_LIGHTORANGE,
			COLOR_GREEN,
            COLOR_WHITE
		};
	for(int m_i = 0; m_i < dim.methods; m_i++)
		for(int m_j = 0; m_j < dim.methods; m_j++){
			if(m_j > m_i) break;
			for(int c_i = 0; c_i < dim.constructs; c_i++){
				for(int c_j = 0; c_j < dim.constructs; c_j++){
					if( (m_j == m_i) && (c_j > c_i) ) break;
					showP(
						book,
						sheet,
						_fmt(m[m_i*cC+c_i][m_j*cC+c_j].corr, CSpinEdit1->Value).c_str(),
						2+m_i*(cC+1)+c_i,
						2+m_j*(cC+1)+c_j,
						t2c[m[m_i*cC+c_i][m_j*cC+c_j].type]
					);
					
				};
			};
		};

	for(int i = 0; i < dim.methods; i++){
		showP(
						book,
						sheet,
						("М"+AnsiString(i+1)).c_str(),
						0,
						2 + i*(dim.constructs+1),
						t2c[4]
					);
		showP(
						book,
						sheet,
						("М"+AnsiString(i+1)).c_str(),
						2 + i*(dim.constructs+1),
						0,
						t2c[4]
					);
		for(int j = 0; j < dim.constructs; j++){
				showP(
						book,
						sheet,
						("K"+AnsiString(j+1)).c_str(),
						1,
						2 + i*(dim.constructs+1)+j,
						t2c[4]
					);
				showP(
						book,
						sheet,
						("K"+AnsiString(j+1)).c_str(),
						2 + i*(dim.constructs+1)+j,
						1,
						t2c[4]
					);
		};
	};
	book->save((saveDialog->Files->Strings[0]+".xls").c_str());
}
//---------------------------------------------------------------------------

