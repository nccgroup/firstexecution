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

//
// Previous documentation / examples consulted:
// http://msdn.microsoft.com/en-us/library/bb918180.aspx
// http://www.cnblogs.com/sunkang/archive/2011/05/24/2055635.html
// http://www.codeguru.com/cpp/misc/misc/applicationcontrol/article.php/c6945/Running-Code-Before-and-After-Main.htm
// http://buliedian.iteye.com/blog/1069072
// http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/md/ppc/_crt.c.htm
// http://src.chromium.org/svn/trunk/src/native_client_sdk/src/libraries/third_party/pthreads-win32/autostatic.c
// http://ci.boost.org/websvn/filedetails.php?repname=repos+1&path=%2Fbranches%2Frelease%2Flibs%2Fthread%2Fsrc%2Fwin32%2Ftss_pe.cpp&rev=66259&peg=66259
//
//
// Now a little rant:
//  So as you'll see that lots of the above examples claim that the dtors can be placed in
//  .CRT$XTU which is not the case in my testing using (Visual Studio 2010 Pro):
//     Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 16.00.40219.01
//     Microsoft (R) Incremental Linker Version 10.00.40219.01
//  instead to get this working I used .CRT$XTZ which is maybe not the right thing to do. - this however seems flaky
// 

// Called before the program exits
void atExit(){
	fprintf(stdout,"[i] I'm a deconstructor\n");
}

// Called before the program exits
int onExit(){
	fprintf(stdout,"[i] I'm a deconstructor too\n");
	return 0;
}

// Called before main
int intGlobalInit(){
	fprintf(stdout,"[i] I'm a global\n");

	//
	// These two result in populating the same LIFO queue
	// these are called by http://msdn.microsoft.com/en-GB/library/zb3b443a(v=vs.80).aspx
	// for source see CRT\SRC\ATONEXIT.C
	//
	atexit(atExit);
	_onexit(onExit);
	return 0;
}

//
// http://msdn.microsoft.com/en-us/library/bb918180.aspx
// 
int intGlobal = intGlobalInit();

//
// The programs main entrypoint
//
int _tmain(int argc, _TCHAR* argv[])
{
	fprintf(stdout,"[i] I'm main\n");
	return 0;
}

int premain(void)
{
   fprintf(stdout,"[i] I'm a constructor via a section\n");
   return 0;
}

int aftermain(void)
{
   fprintf(stdout,"[i] I run after main via a section\n");
   return 0;
}


// Function definition for the ctors and dtors
typedef int MyFuncDef(void);

//
// http://msdn.microsoft.com/en-us/library/thfhx4st(v=vs.80).aspx
// \CRT\SRC\CRT0DAT.C
// \CRT\SRC\CRT0INIT.C
//

// C initializers 
#pragma section(".CRT$XIU", long, read)
#pragma data_seg(".CRT$XIU")
static MyFuncDef *autostart[] = { premain};
#pragma data_seg() 

// C++ initializers
#pragma section(".CRT$XCU", long, read)
#pragma data_seg(".CRT$XCU")
static MyFuncDef *autostart2[] = { premain};
#pragma data_seg() 

// C pre-terminators
// this doesn't work for some reason 
//#pragma section(".CRT$XPU", long, read)
//#pragma data_seg(".CRT$XPU")
//static MyFuncDef *autoexit[] = { aftermain };

// C terminators 
// .CRT$XTU doesn't work hence we use .CRT$XTZ
// this doesn't work for some reason reliably - i.e. did in the past not now

#pragma section(".CRT$XTU", long, read)
	__declspec(allocate(".CRT$XTU"))MyFuncDef *autoexit2[]  = { aftermain };

// This another way of doing the above
// #pragma section(".CRT$XTU", long, read)
//#pragma data_seg(".CRT$XTU")
//static MyFuncDef *autoexit2[] = { aftermain };
//#pragma data_seg()    /* reset data-segment */


