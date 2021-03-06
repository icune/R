//---------------------------------------------------------------------------


#pragma hdrstop

#include "Xls.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
Xls::Xls(){
	this->book = xlCreateBook();
};
char* _readUni(int row, int col ,Sheet *sheet){//����������� ������ ������ ���� � ������
	CellType ct = sheet->cellType(row, col);
	AnsiString ss;
	switch(ct){
	     case CELLTYPE_NUMBER:
		 {
			double d = sheet->readNum(row, col);
			ss =  FloatToStr(d);

			break;
		 }
		 case CELLTYPE_STRING:
		 {
			const char* s = sheet->readStr(row, col);
			ss =  AnsiString(s);
			break;
		 }
		 default:
			if(row >= 3)
				int xxx = 4;
			ss =  AnsiString(sheet->readStr(row, col));
		 break;
	};
	//AnsiString* pss = new AnsiString(ss);
	AnsiString *pss = new AnsiString(sheet->readStr(row, col)); 
	return pss->c_str();
} 
#include <comobj.hpp>
#include <utilcls.h>
CellMatrix Xls::getRows(PAnsiChar fileName){//�������� ������ ���� � ���� �������
	CellMatrix R;
	Variant Excel, Book, XSheet, XCell;
	this->book->load(fileName);
	const char *eMsg = book->errorMessage();
	this->eMsg = eMsg;
	Sheet* sheet = book->getSheet(0);
	int lR = sheet->lastRow();
	int lC = sheet->lastCol();
    for(int row = 0; row < 3; ++row){
		//if(row > 2 && sheet->cellType(row, 0) == CELLTYPE_EMPTY) break;
		CellVector _rr;
		for(int col = sheet->firstCol(); col < sheet->lastCol(); ++col){
			Cell _rrc;
			_rrc.merged = sheet->getMerge(row, col, &_rrc.row_1, &_rrc.row_e, &_rrc.col_1, &_rrc.col_e);
			_rrc.text = _readUni(row, col, sheet);
			_rr.push_back(_rrc);
		};
		R.push_back(_rr);
	};

	this->book->release();
	
	Excel=CreateOleObject("Excel.Application");
	Book=Excel.OlePropertyGet("Workbooks").OlePropertyGet("Open", fileName);
	XSheet=Book.OlePropertyGet("Worksheets", 1);
	int rc, cc;
	rc = XSheet.OlePropertyGet("Cells").OlePropertyGet("Rows").OlePropertyGet("Count");
	cc = XSheet.OlePropertyGet("Cells").OlePropertyGet("Columns").OlePropertyGet("Count");
	for(int i = 4; i <= lR; i++){
		CellVector v;
		for(int j = 1; j <= lC; j++){
			XCell=XSheet.OlePropertyGet("Cells").
				   OlePropertyGet("Item",i,j);
			Cell c;
			c.merged = false;
			String txt = XCell.OlePropertyGet("Value");
			
			c.text = new char[txt.Length()*2];
			strcpy(c.text, txt.c_str());
			int zz = 2;
			v.push_back(c);
		};
		R.push_back(v);
	};
efor:			
    

	Excel.OleProcedure("Quit");
    return R;
};
Dimensions Xls::check(CellMatrix M){//�������� �� ���������� �������� ����� � ����������� ��������
	Dimensions r;
	if(M.size() < 5) throw Error::Xls(Error::short_table);
	CellVector r0 = M[0];
	if(r0.size() < 4) throw Error::Xls(Error::short_table);
	if(!r0[0].merged) throw Error::Xls(Error::series_unmerged);
	if(r0[0].row_1 != r0[0].row_e) throw Error::Xls(Error::series_unmerged);
	int r0w = r0[0].col_e - r0[0].col_1;
	int r0i = r0w+1;
	r.series = 1;
	while(r0i < r0.size()){
		if(!r0[r0i].merged) throw Error::Xls(Error::series_unmerged);
		if(r0[r0i].col_e - r0[r0i].col_1 != r0w)
			throw Error::Xls(Error::series_unmerged);
		r0i = r0[r0i].col_e+1;
		r.series += 1;
	};
	
	CellVector r1 = M[1];
	if(!r1[0].merged) throw Error::Xls(Error::constructs_unmerged);
	if(r1[0].row_1 != r1[0].row_e) throw Error::Xls(Error::constructs_unmerged);
	int r1w = r1[0].col_e - r1[0].col_1;
	int r1i = r1w+1;
	r.constructs = 1;
	while(r1i < r1.size()){
		if(!r1[r1i].merged) throw Error::Xls(Error::constructs_unmerged);
		if(r1[r1i].col_e - r1[r1i].col_1 != r1w)
			throw Error::Xls(Error::constructs_unmerged);
		r1i = r1[r1i].col_e+1;
		r.constructs += 1;
	};
	r.constructs /= r.series;

	CellVector r2 = M[2];
	if(r2[0].merged) throw Error::Xls(Error::constructs_unmerged);
    r.methods = r2.size()/r.constructs/r.series;
    int mustSize = r2.size();
	for(int i = 0; i < M.size(); i++){
		int mis = M[i].size();
		if(M[i].size() != mustSize)
			throw Error::Xls(Error::table_not_full);
	};

	for(int i = 3; i < M.size(); i++)
		for(int j = 0; j < mustSize; j++)
			try{
				AnsiString(M[i][j].text).ToDouble();
			}catch(EConvertError &e){
				throw Error::Xls(Error::invalid_value, AnsiString(M[i][j].text) + i + " " + j);
			};
	return r;
}
Load Xls::load(PAnsiChar fileName){//��������� ������ �� �����
	Load r;
	CellMatrix m = this->getRows(fileName);
	int sz = m.size();
	Dimensions dim = this->check(m);
	r.mat = m;
	r.dim = dim;
	return r;
}

#pragma package(smart_init)

