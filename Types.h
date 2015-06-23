//---------------------------------------------------------------------------

#ifndef TypesH
#define TypesH
#include <vector.h>
#include <Classes.hpp>
//---------------------------------------------------------------------------
typedef std::vector<double> Vect;//тип для вектора (он же столбец чисел)
typedef struct _Cell{  //Промежуточный тип для загрузки и выгрузки из Excel
	PAnsiChar text;
	bool merged;//Является ли блок объедененным
	int row_1, row_e, col_1, col_e;//границы объединения
}Cell;
typedef std::vector<Cell> CellVector;  //Промежуточный тип для загрузки и выгрузки из Excel
typedef std::vector<CellVector> CellMatrix;//Промежуточный тип для загрузки и выгрузки из Excel
typedef std::vector<Vect> Construct;//Конструкт, содержащий измерения методами
typedef std::vector<Construct> Constructs;//Набор конструктов
typedef std::vector<Constructs> Series;//Серии, содержащие набо наборов конструктов
typedef struct _Dimensions{//Количество серий, методов и конструктов
	int series, methods, constructs;
}Dimensions;
namespace Error{ //Определение возможных ошибок для отображения
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
		"Серии не выровнены",
		"Конструкты не выровнены",
		"Методы не выровнены",
		"Данные не выровнены",
		"Неверное значение",
		"Короткая таблица",
		"Таблица не заполнена полностью",
		"Неправильный тип ячейки"
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

typedef struct _Load{  //Тип данных при загрузке
	CellMatrix mat;//Матрица
	Dimensions dim;//Размеры
}Load;
typedef struct _MCell{//Ячейка для метода МЧММ со значением корреляции и типом
	double corr;
	int type;	
}MCell;
typedef std::vector<MCell> MVect;
typedef std::vector<MVect> MMatrix;
#endif
