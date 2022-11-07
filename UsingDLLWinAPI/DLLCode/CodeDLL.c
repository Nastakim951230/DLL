#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}
__declspec(dllexport) int ReadFile(LPWSTR start);

struct person
{
	char Familia[1000];
	char Name[1000];
	char Othestvo[1000];
	int ago;
	
};
int ReadFile(LPWSTR start)
{
	
	DWORD d;
	HANDLE Start = CreateFile(start, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	LPCSTR rezult = "";
	if (Start == INVALID_HANDLE_VALUE)
	{
		rezult = L"Ошибка, нельзя открыть файл";
		MessageBox(NULL, rezult, L"Оповещение", MB_OK);
		return;
	}
	

}