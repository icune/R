//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", _MainForm);
USEFORM("DataForm.cpp", _DataForm);
USEFORM("HelpForm.cpp", _HelpForm);
USEFORM("HelpMethodForm.cpp", _HelpMethodForm);
USEFORM("HelpProgramForm.cpp", _HelpProgramForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(T_MainForm), &_MainForm);
		Application->CreateForm(__classid(T_DataForm), &_DataForm);
		Application->CreateForm(__classid(T_HelpForm), &_HelpForm);
		Application->CreateForm(__classid(T_HelpMethodForm), &_HelpMethodForm);
		Application->CreateForm(__classid(T_HelpProgramForm), &_HelpProgramForm);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
