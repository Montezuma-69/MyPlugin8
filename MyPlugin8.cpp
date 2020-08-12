#include "MyPlugin8.h"
using namespace std;
#include <string>
#include <ctime>

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
	// ADD YOUR CODE HERE WHEN THE PLUGIN IS CALLED
	DeclareParameterCommand(m_transitionCommand, ID_CMD_1, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_2, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_3, "Command", "CMD", sizeof(m_transitionCommand));

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
	
	std::string s_genre = m_transitionCommand;
		char commentString[2048];
		std::string s_commentString;
		std::string s_Result;
		std::string s_MainPart;
		std::string s_EndPart;
		std::string SendString;
		const char* c_SendString;

	switch (id)
	{
	case ID_CMD_1:

			GetStringInfo("get_browsed_song 'comment'", commentString,100);
			s_commentString = commentString;

			s_Result = s_commentString.replace(s_commentString.find(s_genre), string(s_genre).size() , "");

			s_MainPart = "browsed_song 'comment' '";
			s_EndPart = "'";

			SendString = s_MainPart + s_Result + s_EndPart;
			c_SendString = SendString.c_str();

			SendCommand(c_SendString);
	break;

	case ID_CMD_2:
		GetStringInfo("get_browsed_song 'user1'", commentString, 100);
		s_commentString = commentString;

		s_Result = s_commentString.replace(s_commentString.find(s_genre), string(s_genre).size(), "");

		s_MainPart = "browsed_song 'user1' '";
		s_EndPart = "'";

		SendString = s_MainPart + s_Result + s_EndPart;
		c_SendString = SendString.c_str();

		SendCommand(c_SendString);

	break;

	case ID_CMD_3:
		GetStringInfo("get_browsed_song 'track'", commentString, 100);
		s_commentString = commentString;
		if (s_commentString.find("159") != string::npos) {}
		else {
			s_MainPart = "browsed_song 'track' '";
			s_Result = to_string(std::time(nullptr));
			s_Result = s_Result + to_string(rand() % 999 + 1000);
			s_EndPart = ".'";

			SendString = s_MainPart + s_Result + s_EndPart;
			c_SendString = SendString.c_str();
			SendCommand(c_SendString);
		}
	break;
	}

	return 0;

}





//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetParameterString(int id, char* outParam, int outParamSize)
{
	return S_OK;
}
