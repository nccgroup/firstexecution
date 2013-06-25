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
#include <windows.h>

//
// Previous documentation / examples consulted:
// http://blog.dkbza.org/2007/03/pe-trick-thread-local-storage.html
// http://www.microsoft.com/msj/0999/hood/hood0999.aspx
// http://thelegendofrandom.com/blog/archives/2418
// http://waleedassar.blogspot.co.uk/2010/10/quick-look-at-tls-callbacks.html
// http://www.hexblog.com/?p=9
//

//
// This gets run before and after main
//
void __stdcall callback( LPVOID lpBlah,
						 DWORD  ul_reason_for_call,
						 LPVOID lpReserved
					   )
{

	if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
	{
		fprintf(stdout,"[i] I'm a TLS callback being called due to a DLL_PROCESS_ATACH\n");
	} else if ( ul_reason_for_call == DLL_PROCESS_DETACH ){
		fprintf(stdout,"[i] I'm a TLS callback being called due to a DLL_PROCESS_DETACH\n");
	} else {
		fprintf(stdout,"[i] I'm a TLS callback being called");
	}
}

//
// This is intheory the entry point
//
int _tmain(int argc, _TCHAR* argv[])
{
	fprintf(stdout,"[i] I'm main\n");
	return 0;
}

// This is from http://www.gamerzplanet.net/forums/c-c/421626-tls-callbacks-in-c.html
#ifdef _MSC_VER
#pragma comment(linker, "/INCLUDE:__tls_used")
#pragma comment(linker, "/INCLUDE:_tls_entry")
#pragma data_seg(".CRT$XLB" )

extern "C" PIMAGE_TLS_CALLBACK tls_entry = callback;
#endif