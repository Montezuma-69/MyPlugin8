#include "MyPlugin8.h"
using namespace std;
#include <string>
#include <ctime>

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>


auto split(const std::string& value, char separator)
-> std::vector<std::string>
{
	std::vector<std::string> result;
	std::string::size_type p = 0;
	std::string::size_type q;
	while ((q = value.find(separator, p)) != std::string::npos) {
		result.emplace_back(value, p, q - p);
		p = q + 1;
	}
	result.emplace_back(value, p);
	return result;
}

template <typename KeyFn>
struct key_fn_adaptor
{
	KeyFn&& _key_fn;
	template <typename Lhs, typename Rhs>
	auto operator()(Lhs&& lhs, Rhs&& rhs) const -> bool
	{
		return _key_fn(lhs) < _key_fn(rhs);
	}
};

template <typename Range>
void sort_range_with_key_fn(Range&& range)
{
	// enable ADL with fallback on default implementations
	using std::begin;
	using std::end;

	std::sort(begin(range), end(range));
	//    std::sort(begin(range), end(range),
	//        key_fn_adaptor<KeyFn>{std::forward<KeyFn>(key_fn)});
}

class noop
{
	friend auto operator<<(std::ostream& os, const noop&)
		-> std::ostream&
	{
		return os;
	}
} noop;

template <typename Iterator, typename Separator>
auto join(Iterator first, Iterator last, Separator&& separator = noop)
-> std::string
{
	if (first == last) {
		return std::string{};
	}
	else {
		std::ostringstream os;
		os << *first;
		for (++first; first != last; ++first) {
			os << *first << separator;
		}
		return os.str(); // NOTE: move is currently not supported
	}
}

template <typename Range, typename Separator>
auto join_range(Range&& range, Separator&& separator = noop)
-> std::string
{
	// enable ADL with fallback on default implementations
	using std::begin;
	using std::end;
	//    return join(begin(range), end(range), '.');
	return join(begin(range), end(range), std::forward<Separator>(separator));
}

//-----------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnLoad()
{
	// ADD YOUR CODE HERE WHEN THE PLUGIN IS CALLED
	DeclareParameterCommand(m_transitionCommand, ID_CMD_1, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_2, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_3, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_4, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_5, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_6, "Command", "CMD", sizeof(m_transitionCommand));
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

			SendString = "browsed_song 'comment' '" + s_Result + "'";
			c_SendString = SendString.c_str();

			SendCommand(c_SendString);
			break;

		case ID_CMD_2:
			GetStringInfo("get_browsed_song 'user1'", commentString, 100);
			s_commentString = commentString;

			s_Result = s_commentString.replace(s_commentString.find(s_genre), string(s_genre).size(), "");

			SendString = "browsed_song 'user1' '" + s_Result + "'";
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


		case ID_CMD_6:
			GetStringInfo("get_browsed_song 'comment'", commentString, 100);
			s_commentString = commentString;

			s_Result = s_commentString + s_genre;

			auto&& tokens = split(s_Result, '.');
			sort_range_with_key_fn(tokens);
			s_Result = join_range(tokens, '.');

			SendString = "browsed_song 'comment' '" + s_Result + "'";
			c_SendString = SendString.c_str();

			SendCommand(c_SendString);
			break;

			return 0;
		}
}





//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetParameterString(int id, char* outParam, int outParamSize)
{
	return S_OK;
}
