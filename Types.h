//---------------------------------------------------------------------------

#ifndef TypesH
#define TypesH
#include <vector.h>
#include <Classes.hpp>
//---------------------------------------------------------------------------
typedef std::vector<double> Vect;//��� ��� ������� (�� �� ������� �����)
typedef struct _Cell{  //������������� ��� ��� �������� � �������� �� Excel
	PAnsiChar text;
	bool merged;//�������� �� ���� ������������
	int row_1, row_e, col_1, col_e;//������� �����������
}Cell;
typedef std::vector<Cell> CellVector;  //������������� ��� ��� �������� � �������� �� Excel
typedef std::vector<CellVector> CellMatrix;//������������� ��� ��� �������� � �������� �� Excel
typedef std::vector<Vect> Construct;//���������, ���������� ��������� ��������
typedef std::vector<Construct> Constructs;//����� �����������
typedef std::vector<Constructs> Series;//�����, ���������� ���� ������� �����������
typedef struct _Dimensions{//���������� �����, ������� � �����������
	int series, methods, constructs;
}Dimensions;
namespace Error{ //����������� ��������� ������ ��� �����������
	enum XlsEnum{
		series_unmerged,
		constructs_unmerged,
		method_unmerged,
		unaligned_data,
		invalid_value,
		short_table,
		table_not_full,
		wrong_type
	};
	const char* msgs[] = {
		"����� �� ���������",
		"���������� �� ���������",
		"������ �� ���������",
		"������ �� ���������",
		"�������� ��������",
		"�������� �������",
		"������� �� ��������� ���������",
		"������������ ��� ������"
	};
	class Xls{
	public:
		Xls(XlsEnum _c){this->code = _c;this->msg = (char *)msgs[_c];};
		Xls(XlsEnum _c, AnsiString add){
			this->code = _c;
			this->msg = AnsiString(AnsiString((char *)msgs[_c]) + " :: "+add).c_str();
		};
		XlsEnum code;
		char* msg;

	};
}

typedef struct _Load{  //��� ������ ��� ��������
	CellMatrix mat;//�������
	Dimensions dim;//�������
}Load;
typedef struct _MCell{//������ ��� ������ ���� �� ��������� ���������� � �����
	double corr;
	int type;	
}MCell;
typedef std::vector<MCell> MVect;
typedef std::vector<MVect> MMatrix;
#endif
