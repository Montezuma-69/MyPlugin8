#ifndef MYPLUGIN8_H
#define MYPLUGIN8_H

// we include stdio.h only to use the sprintf() function
// we define _CRT_SECURE_NO_WARNINGS for the warnings of the sprintf() function
#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>

#include "vdjPlugin8.h"

class CMyPlugin8 : public IVdjPlugin8
{
public:
	HRESULT VDJ_API OnLoad();
	HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8* infos);
	ULONG VDJ_API Release();
	HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8* pluginInterface);
	HRESULT VDJ_API OnParameter(int id);
	HRESULT VDJ_API OnGetParameterString(int id, char* outParam, int outParamSize);

private:
#define STRMAX 200
char m_transitionCommand[STRMAX]{};


protected:
	typedef enum _ID_Interface
	{
		ID_CMD_1, 
		ID_CMD_2,
		ID_CMD_3,
		ID_CMD_4,
		ID_CMD_5,
		ID_CMD_6

	} ID_Interface;

};

#endif