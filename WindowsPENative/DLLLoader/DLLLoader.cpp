// First runner experiment
//
// Released as open source by NCC Group Plc - http://www.nccgroup.com/
//
// Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com
//
// http://www.github.com/nccgroup/firstrunner
//
// Released under AGPL see LICENSE for more information

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hMod = LoadLibrary(argv[1]);

	if(argc < 2){
		fprintf(stdout,"%S <DLLFileName>\n",argv[0]);
		return 1;
	}

	if(hMod == NULL){
		fprintf(stdout,"[!] Error loading DLL %S - %d\n",argv[1],GetLastError());
	} else {
		fprintf(stdout,"[i] DLL Loaded\n");
	}
	return 0;
}

