//---------------------------------------------------------------------------

#ifndef HelpFormH
#define HelpFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class T_HelpForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall T_HelpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE T_HelpForm *_HelpForm;
//---------------------------------------------------------------------------
#endif
