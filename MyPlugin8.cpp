#include "MyPlugin8.h"
using namespace std;
#include <string>
#include <ctime>

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <regex>

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
	DeclareParameterCommand(m_transitionCommand, ID_CMD_7, "Command", "CMD", sizeof(m_transitionCommand));
	DeclareParameterCommand(m_transitionCommand, ID_CMD_8, "Command", "CMD", sizeof(m_transitionCommand));
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


std::string rtrim(std::string s, std::string const& delim = " \t\r\n")
{
	std::string::size_type last = s.find_last_not_of(delim.c_str());
	return last == std::string::npos ? "" : s.erase(last + 1);
}

std::string ltrim(std::string s, std::string const& delim = " \t\r\n")
{
	return s.erase(0, s.find_first_not_of(delim.c_str()));
}

std::string trim(std::string s, std::string const& delim = " \t\r\n")
{
	return ltrim(rtrim(s, delim), delim);
}

std::string CaseChecker(std::string data, int T)
{

	std::locale::global(std::locale("de_DE.UTF-8"));

	static int typ = 0;
	if (T == 1) { typ = 1; } //artist
	if (T == 2) { typ = 2; } //title

	static string s_c;

	static string last = " ";
	for_each(data.begin(), data.end(), [](char & c) {
		if (last == " " && c != ' ' ) c = toupper(c);
		if (last != " " && c != ' ' ) c = tolower(c);
		if (last == "-") c = toupper(c);
		if (last == ",") c = toupper(c);
		if (last == "(") c = toupper(c);
		if (last == "\'" && typ == 1) c = toupper(c);
		if (last == "\'" && typ == 2) c = tolower(c);

		last = c;
		});
	last = " ";

	data = std::regex_replace(data, std::regex("ö"), "Ö");
	return data;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnParameter(int id)
{
	
	std::string t_command = m_transitionCommand;
		char commentString[2048];
		char deck1track[2048];
		char deck2track[2048];
		char deck1user2[2048];
		char deck2user2[2048];
		char artist[2048];
		char title[2048];
		char genre[2048];
		char user1[2048];
		char remix[2048];

		const char* c_SendString;

		std::string s_commentString;
		std::string s_deck1track;
		std::string s_deck2track;
		std::string s_deck1user2;
		std::string s_deck2user2;
		std::string s_Result;
		std::string SendString;
		std::string s_artist;
		std::string s_title;
		std::string s_genre;
		std::string s_user1;
		std::string s_remix;

		int mix;
		int xxx;
		std::size_t found;

		switch (id)
		{
			case ID_CMD_1: //Tag Genre entfernen
			GetStringInfo("get_browsed_song 'genre'", genre, 100);
			s_genre = genre;

			s_Result = s_genre.replace(s_genre.find(t_command), string(t_command).size(), "");

			SendString = "browsed_song 'genre' '" + s_Result + "'";
			c_SendString = SendString.c_str();

			SendCommand(c_SendString);
			break;

		case ID_CMD_2: //Tag aus user1 entfernen
			GetStringInfo("get_browsed_song 'user1'", user1, 100);
			s_user1 = user1;

			s_Result = s_user1.replace(s_user1.find(t_command), string(t_command).size(), "");

			SendString = "browsed_song 'user1' '" + s_Result + "'";
			c_SendString = SendString.c_str();

			SendCommand(c_SendString);

			break;

		case ID_CMD_3: //Großbuchstaben und Kleinbuchstaben
			GetStringInfo("get_browsed_song 'artist'", artist, 100);
			s_artist = trim(artist," ");
			GetStringInfo("get_browsed_song 'title'", title, 100);
			s_title = trim(title, " ");

			s_artist = CaseChecker(s_artist, 1);
			s_title = CaseChecker(s_title, 2);

			SendString = "browsed_song 'artist' \"" + s_artist + "\"";
			SendCommand(SendString.c_str());
			SendString = "browsed_song 'title' \"" + s_title + "\"";
			SendCommand(SendString.c_str());
			break;


		case ID_CMD_4: //merge zwei songs
			GetStringInfo("deck 1 get_loaded_song track", deck1track, 100);
			s_deck1track = deck1track;
			GetStringInfo("deck 2 get_loaded_song track", deck2track, 100);
			s_deck2track = deck2track;
			GetStringInfo("deck 1 get_loaded_song user2", deck1user2, 200);
			s_deck1user2 = deck1user2;
			GetStringInfo("deck 2 get_loaded_song user2", deck2user2, 200);
			s_deck2user2 = deck2user2;

			if ((s_deck1track == s_deck2track) && (s_deck1track != "")) break;

			if (s_deck1track.find(".")) {
				s_deck1track = to_string(std::time(nullptr)) + "1.";
				SendString = "deck 1 loaded_song track \"" + s_deck1track + "\"";
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);
			}
			if (s_deck2track.find(".")) {
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

		case ID_CMD_5: //unmerge zwei Songs
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

		case ID_CMD_7: // .mix und .xxx auswerten
			GetStringInfo("get_loaded_song 'user1'", user1, 100);
			s_user1 = user1;

			found = s_user1.find("mix.");
			if (found != std::string::npos) { mix = 1; } else { mix = 0; }
	
			SendString = "set 'mix' " + to_string(mix);
				c_SendString = SendString.c_str();
				SendCommand(c_SendString);

			found = s_user1.find("xxx.");
			if (found != std::string::npos) { xxx = 1; } else { xxx = 0; }
			GetStringInfo("get_var '$censor'", user1, 100);
			s_user1 = user1;

			if (s_user1 == "1" && xxx == 1) { s_Result = "1"; }
			else { s_Result = "0"; }
			
			SendString = "set 'xxx' " + s_Result;
			SendCommand(SendString.c_str());

			if (s_Result == "1") { SendString = "video_fx 'Shader' on"; } else { SendString = "video_fx 'Shader' off"; }
			SendCommand(SendString.c_str());
			break;

		case ID_CMD_8: //Remix Klammern entfernen
			GetStringInfo("get_browsed_song 'remix'", remix, 100);
			s_remix = remix;

			if (s_remix.at(0) == '\'') { break; }


			if (s_remix.at(0) == ' ') { s_remix.replace(0, 1, ""); }
			if (s_remix.at(0) == ' ') { s_remix.replace(0, 1, ""); }

			replaceAll(s_remix, "[", "");
			replaceAll(s_remix, "]", "");
			replaceAll(s_remix, "(", "");
			replaceAll(s_remix, ")", "");
			replaceAll(s_remix, "  ", " ");
			replaceAll(s_remix, "  ", " ");
			replaceAll(s_remix, "  ", " ");

			s_remix = regex_replace(s_remix, regex(" Clean Single"), ".Clean.Single");
			s_remix = regex_replace(s_remix, regex(" Clean"), ".Clean");
			s_remix = regex_replace(s_remix, regex(" Extended"), ".Extended");
			s_remix = regex_replace(s_remix, regex(" Intro"), ".Intro");
			s_remix = regex_replace(s_remix, regex(" Outro"), ".Outro");
			s_remix = regex_replace(s_remix, regex(" Dirty"), ".Dirty");
			s_remix = regex_replace(s_remix, regex(" RS"), ".RS");
			s_remix = regex_replace(s_remix, regex(" HD"), ".HD");
			s_remix = regex_replace(s_remix, regex(" 1080"), ".1080");
			s_remix = regex_replace(s_remix, regex(" Full.HD"), ".Full HD");


			SendString = "browsed_song 'remix' '" + s_remix + "'";
			SendCommand(SendString.c_str());
			break;

		case ID_CMD_6: //genre hinzufügen und sortieren
			GetStringInfo("get_browsed_song 'genre'", genre, 100);
			s_genre = genre;

			if (s_genre.find(".") == string::npos) { s_genre = ""; }

			s_Result = s_genre + t_command;

			auto&& tokens = split(s_Result, '.');
			sort_range_with_key_fn(tokens);
			s_Result = join_range(tokens, '.');

			SendString = "browsed_song 'genre' '" + s_Result + "'";
			SendCommand(SendString.c_str());
			break;
					
		}
	return 0;
}





//---------------------------------------------------------------------------
HRESULT VDJ_API CMyPlugin8::OnGetParameterString(int id, char* outParam, int outParamSize)
{
	return S_OK;
}
