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
#include <stdlib.h>
#include <stdio.h>

//
// Entry point.. or is it?
// http://msdn.microsoft.com/en-us/library/988ye33t(v=vs.80).aspx
//
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	
	return TRUE;
}

int premain(void)
{
   fprintf(stdout,"[i] I'm a constructor\n");
   return 0;
}

int aftermain(void)
{
   fprintf(stdout,"[i] I run after main\n");
   return 0;
}


// Function definition for the ctors and dtors
typedef int MyFuncDef(void);

//
// http://msdn.microsoft.com/en-us/library/thfhx4st(v=vs.80).aspx
// \CRT\SRC\CRT0DAT.C
// \CRT\SRC\CRT0INIT.C
//

#pragma section(".CRT$XIU", long, read)
#pragma data_seg(".CRT$XIU")
static MyFuncDef *autostart[] = { premain};

#pragma section(".CRT$XCU", long, read)
#pragma data_seg(".CRT$XCU")
static MyFuncDef *autostart2[] = { premain};

// Doesn't work see .exe version
#pragma section(".CRT$XPU", long, read)
#pragma data_seg(".CRT$XPU")
static MyFuncDef *autoexit[] = { aftermain };

// Doesn't work see .exe version
#pragma section(".CRT$XTU", long, read)
#pragma data_seg(".CRT$XTU")
static MyFuncDef *autoexit2[] = { aftermain };

#pragma data_seg()    /* reset data-segment */
