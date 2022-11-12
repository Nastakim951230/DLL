#include <windows.h>
#include <stdio.h>
#include "Struktura.h"
#define PATH L"DLLCode.dll"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	forReadData myFun = (forReadData)GetProcAddress(hMyDLL, "FileRead");
	struct person* pers = calloc(5000, sizeof(struct person));
	myFun(pers);
	FreeLibrary(hMyDLL);
	return 0;
}