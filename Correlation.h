//---------------------------------------------------------------------------

#ifndef CorrelationH
#define CorrelationH
#include "algorithm.h"
#include "Types.h"
//---------------------------------------------------------------------------

namespace Correlation{
	namespace Tools{
		double mean(Vect);
		Vect range(Vect);	
	};
	double Pearson(Vect, Vect);
	double Spearman(Vect, Vect);
}
#endif
