//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HelpMethodForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "HelpForm"
#pragma resource "*.dfm"
T_HelpMethodForm *_HelpMethodForm;
//---------------------------------------------------------------------------
__fastcall T_HelpMethodForm::T_HelpMethodForm(TComponent* Owner)
        : T_HelpForm(Owner)
{
}
//---------------------------------------------------------------------------
