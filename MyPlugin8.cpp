#include "MyPlugin8.h"
using namespace std;
#include <string>

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
	// ADD YOUR CODE HERE WHEN THE PLUGIN IS CALLED
	DeclareParameterCommand(m_transitionCommand, ID_CMD_1, "Command", "CMD", sizeof(m_transitionCommand));

	return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetPluginInfo(TVdjPluginInfo8* infos)
{
	infos->PluginName = "MyPlugin8";
	infos->Author = "Atomix Productions";
	infos->Description = "My first VirtualDJ 8 plugin";
	infos->Version = "1.0";
	infos->Flags = 0x00;
	infos->Bitmap = NULL;

	return S_OK;
}
//---------------------------------------------------------------------------
ULONG VDJ_API CMyPlugin8::Release()
{
	// ADD YOUR CODE HERE WHEN THE PLUGIN IS RELEASED

	delete this;
	return 0;
}
//---------------------------------------------------------------------------

HRESULT VDJ_API CMyPlugin8::OnGetUserInterface(TVdjPluginInterface8* pluginInterface)
{
	pluginInterface->Type = VDJINTERFACE_DEFAULT;

	return S_OK;
}

//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnParameter(int id)
{
	switch (id)
	{
	case ID_CMD_1:

		std::string s_genre = m_transitionCommand;

			char commentString[2048];
			GetStringInfo("get_browsed_song 'comment'", commentString,100);
			std::string s_commentString = commentString;

			std::string s_Result = s_commentString.replace(s_commentString.find(s_genre), string(s_genre).size() , "");

			std::string s_MainPart = "browsed_song 'comment' '";
			std::string s_EndPart = "'";

			std::string SendString = s_MainPart + s_Result + s_EndPart;
			const char* c_SendString = SendString.c_str();

			SendCommand(c_SendString);
	break;
	}
	return 0;
}

//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetParameterString(int id, char* outParam, int outParamSize)
{
	return S_OK;
}
