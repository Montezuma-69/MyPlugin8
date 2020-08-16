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
	DeclareParameterCommand(m_transitionCommand, ID_CMD_4, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_5, "Command", "CMD", sizeof(m_transitionCommand));
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
		char deck1track[2048];
		char deck2track[2048];
		char deck1user2[2048];
		char deck2user2[2048];

		std::string s_commentString;
		std::string s_deck1track;
		std::string s_deck2track;
		std::string s_deck1user2;
		std::string s_deck2user2;
		std::string s_Result;
		std::string s_MainPart;
		std::string s_EndPart;
		std::string SendString;
		const char* c_SendString;

		switch (id)
		{
			case ID_CMD_1:
			GetStringInfo("get_browsed_song 'comment'", commentString, 100);
			s_commentString = commentString;

			s_Result = s_commentString.replace(s_commentString.find(s_genre), string(s_genre).size(), "");

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

/*		case ID_CMD_3:
			GetStringInfo("get_browsed_song 'track'", commentString, 100);
			s_commentString = commentString;
			if (s_commentString.find("159") != string::npos) {}
			else {
				s_MainPart = "browsed_song 'track' '";
				s_Result = to_string(std::time(nullptr));
				s_Result = s_Result + to_string(std::rand() % 999 + 1000);
				s_EndPart = ".'";

				SendString = s_MainPart + s_Result + s_EndPart;
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}
			break;
*/

		case ID_CMD_4:
			GetStringInfo("deck 1 get_loaded_song track", deck1track, 100);
			s_deck1track = deck1track;
			GetStringInfo("deck 2 get_loaded_song track", deck2track, 100);
			s_deck2track = deck2track;
			GetStringInfo("deck 1 get_loaded_song user2", deck1user2, 200);
			s_deck1user2 = deck1user2;
			GetStringInfo("deck 2 get_loaded_song user2", deck2user2, 200);
			s_deck2user2 = deck2user2;

			if ((s_deck1track == s_deck2track) && (s_deck1track != "")) break;

			if (s_deck1track == "") {
				s_deck1track = to_string(std::time(nullptr)) + "1.";
				SendString = "deck 1 loaded_song track \"" + s_deck1track + "\"";
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}
			if (s_deck2track == "") {
				s_deck2track = to_string(std::time(nullptr)) + "2.";
				SendString = "deck 2 loaded_song track \"" + s_deck2track + "\"";
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}

			if (s_deck1user2.find(s_deck2track) != string::npos) {
				//.. found.
			}
			else {
				SendString = "deck 1 loaded_song user2 \"" + s_deck1user2 + s_deck2track + "\"";
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}

			if (s_deck2user2.find(s_deck1track) != string::npos) {
				//.. found.
			}
			else {
				SendString = "deck 2 loaded_song user2 \"" + s_deck2user2 + s_deck1track + "\"";
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}
			break;

		case ID_CMD_5:
			GetStringInfo("deck 1 get_loaded_song track", deck1track, 100);
			s_deck1track = deck1track;
			GetStringInfo("deck 2 get_loaded_song track", deck2track, 100);
			s_deck2track = deck2track;
			GetStringInfo("deck 1 get_loaded_song user2", deck1user2, 200);
			s_deck1user2 = deck1user2;
			GetStringInfo("deck 2 get_loaded_song user2", deck2user2, 200);
			s_deck2user2 = deck2user2;

			if (s_deck1track == s_deck2track) break;
			if (s_deck1track == "") break;
			if (s_deck2track == "") break;

			if (s_deck1user2.find(s_deck2track) != string::npos) {

				s_Result = s_deck1user2.replace(s_deck1user2.find(s_deck2track), string(s_deck2track).size(), "");
				SendString = "deck 1 loaded_song user2 \"" + s_Result + "\"";

				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}

			if (s_deck2user2.find(s_deck1track) != string::npos) {
				s_Result = s_deck2user2.replace(s_deck2user2.find(s_deck1track), string(s_deck1track).size(), "");
				SendString = "deck 2 loaded_song user2 \"" + s_Result + "\"";

				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}
			break;

			return 0;
		}
}





//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetParameterString(int id, char* outParam, int outParamSize)
{
	return S_OK;
}
