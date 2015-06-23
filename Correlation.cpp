//---------------------------------------------------------------------------


#pragma hdrstop

#include "Correlation.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
using namespace Correlation;
void _log(Vect v){
	AnsiString s;
	for(int i = 0; i < v.size(); i++){
		s += AnsiString(v[i]) + " ";
	};
	OutputDebugString(s.c_str());
}
double Tools::mean(Vect X_){ //������� �������� �������
	double r = 0;
	for(int i = 0; i < X_.size(); i++)
		r += X_[i];
	return r/X_.size();
};
bool _sortf(double i, double j){return i<j;};//������� ����������
int _countOf(Vect X, double v){//���������� ��������� v � �
	int r = 0;
	for(int i = 0; i < X.size(); i++)
		if(X[i] == v) r++;
	return r;
}
int _indexOf(Vect X, double v){//����� �������� v � X
	for(int i = 0; i < X.size(); i++)
		if(X[i] == v)
			return i;
	return -1;
};
Vect Tools::range(Vect X){//���������� ����� ������� ��� ��������
	Vect r, sorted = X;
	std::sort(sorted.begin(), sorted.end(), _sortf);
	for(int i = 0; i < X.size(); i++)
		r.push_back(_indexOf(sorted, X[i]) + _countOf(r, X[i]));
	return r;
}
double Correlation::Pearson(Vect X, Vect Y){//���������� ������������ �������
	_log(X);
	_log(Y);
	//http://www.machinelearning.ru/wiki/index.php?title=%D0%9A%D0%BE%D1%8D%D1%84%D1%84%D0%B8%D1%86%D0%B8%D0%B5%D0%BD%D1%82_%D0%BA%D0%BE%D1%80%D1%80%D0%B5%D0%BB%D1%8F%D1%86%D0%B8%D0%B8_%D0%9F%D0%B8%D1%80%D1%81%D0%BE%D0%BD%D0%B0
	double uX = Tools::mean(X), uY = Tools::mean(Y);//���������� �������
	double top = 0;//���������
	double bottom = 0;//�����������
	double bot_x = 0, bot_y = 0;//����� ��� ������ �����������
	for(int i = 0; i < X.size(); i++){
		top += (X[i] - uX)*(Y[i] - uY);
		bot_x += (X[i] - uX)*(X[i] - uX);
		bot_y += (Y[i] - uY)*(Y[i] - uY);
		
	};
	bottom = sqrt( bot_x * bot_y );
	if(bottom == 0) bottom = 1;
	return top/bottom;
}

double Correlation::Spearman(Vect X, Vect Y){//���������� ������������ ��������
	//http://www.machinelearning.ru/wiki/index.php?title=%D0%9A%D0%BE%D1%8D%D1%84%D1%84%D0%B8%D1%86%D0%B8%D0%B5%D0%BD%D1%82_%D0%BA%D0%BE%D1%80%D1%80%D0%B5%D0%BB%D1%8F%D1%86%D0%B8%D0%B8_%D0%A1%D0%BF%D0%B8%D1%80%D0%BC%D0%B5%D0%BD%D0%B0
	Vect rX = Tools::range(X), rY = Tools::range(Y);//���������� ������ ��� ��������
	double r = 0;
	double n = rX.size();
	for(int i = 0; i < rX.size(); i++)
		r += pow(rX[i] - rY[i], 2);
	r = 1-6*r/( pow(n, 3) - n );
	return r;
}
