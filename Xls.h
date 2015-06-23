//---------------------------------------------------------------------------

#ifndef XlsH
#define XlsH
//---------------------------------------------------------------------------
#include "libxl-3.6.2.0/include_cpp/libxl.h"
#include <vector.h>
#include "Types.h"
using namespace libxl;

class Xls{
    private:
        Book* book; 
    public:
       const char *eMsg;
       Xls();
	   CellMatrix getRows(PAnsiChar);
	   Dimensions check(CellMatrix);
	   Load load(PAnsiChar);
};
#endif
