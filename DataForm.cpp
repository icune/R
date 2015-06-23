//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
T_DataForm *_DataForm;
//---------------------------------------------------------------------------
__fastcall T_DataForm::T_DataForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall T_DataForm::FormShow(TObject *Sender)
{
	//���������� ����� ������
	SG->RowCount = mtx.size()+10;
	SG->ColCount = 0;
	if(mtx.size())
		SG->ColCount = mtx[0].size()+10;
	SG->FixedRows = 3;
	for(int i = 0; i< dim.series; i++){
		SG->Cells[i*dim.methods*dim.constructs][0] = PAnsiChar("����� �")+IntToStr(i);
		for(int j = 0; j < dim.constructs; j++){
			SG->Cells[i*dim.methods*dim.constructs + j*dim.methods][1] = \
			PAnsiChar("��������� �")+IntToStr(j);
			for(int k = 0; k < dim.methods; k++){
				SG->Cells[i*dim.methods*dim.constructs + j*dim.methods + k][2] = \
                PAnsiChar("����� �")+IntToStr(k);
			};
		};
	};
	for(int i = 3; i < mtx.size(); i++)
		for(int j = 0; j < mtx[i].size(); j++)
			try{
				SG->Cells[j][i] = mtx[i][j].text;
			}catch(...){
			};
}
//---------------------------------------------------------------------------

