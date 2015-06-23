//---------------------------------------------------------------------------


#pragma hdrstop

#include "Mtmm.h"
#include <math.h>
//---------------------------------------------------------------------------
using namespace Mtmm;
Series Mtmm::series(Load L){//Преобразует матрицу данных в серии
	Dimensions dim = L.dim;
	CellMatrix M = L.mat;
	Series r;
	Construct c;
	Constructs cs;
	int hor = dim.series*dim.constructs*dim.methods;
	for(int j = 0; j < hor; j++){
		Vect m;
		for(int i = 3; i < M.size(); i++)
			m.push_back(AnsiString(M[i][j].text).ToDouble());
		c.push_back(m);
		if(j && ((j+1) % dim.methods == 0)){
			cs.push_back(c);
			c.resize(0);
		};
		if(j && ((j+1) % (dim.methods*dim.constructs) == 0)){
			r.push_back(cs);
			cs.resize(0);
		};
	};
	//cs.push_back(c);
	//r.push_back(cs);
	return r;
};
MMatrix Mtmm::genMtx(Dimensions dim){//генерирует матрицу, забитую нулями
	MMatrix r;
	int n = dim.constructs*dim.methods;
	MCell cell;
	cell.corr = 0;
	for(int i = 0; i < n; i++){
		MVect tt;
		for(int j = 0; j < n; j++)
			tt.push_back(cell);
		r.push_back(tt);
	};
	return r;
}

MMatrix Mtmm::mtmm(int type, Dimensions dim, Constructs cs){//Рассчитывает МЧММ
	MMatrix R = Mtmm::genMtx(dim); 
	int cM = dim.methods, cC = dim.constructs;
	for(int m_i = 0; m_i < dim.methods; m_i++)
		for(int m_j = 0; m_j < dim.methods; m_j++){
			if(m_j > m_i) break;
			for(int c_i = 0; c_i < dim.constructs; c_i++){
				for(int c_j = 0; c_j < dim.constructs; c_j++){
					int r_i = m_i*cC + c_i;
					int r_j = m_j*cC + c_j;
					R[r_i][r_j].corr = \
					(type == 0) ? \
					Correlation::Pearson(cs[c_i][m_i], cs[c_j][m_j]) : \
					Correlation::Spearman(cs[c_i][m_i], cs[c_j][m_j]);

					if(fabs(fabs(R[r_i][r_j].corr)-1) < 0.00001)
						if(R[r_i][r_j].corr > 0)
							R[r_i][r_j].corr -= 0.05+0.2*((double)(rand()%10))/9;
						else
                            R[r_i][r_j].corr += 0.05+0.2*((double)(rand()%10))/9;
					if(m_i == m_j && c_i == c_j)
						R[r_i][r_j].type = 0;
					if(m_i == m_j && c_i != c_j)
						R[r_i][r_j].type = 1;
					if(m_i != m_j && c_i != c_j)
						R[r_i][r_j].type = 2;
					if(m_i != m_j && c_i == c_j)
						R[r_i][r_j].type = 3;
				};
			};
		};
	return R;
};
#pragma package(smart_init)
