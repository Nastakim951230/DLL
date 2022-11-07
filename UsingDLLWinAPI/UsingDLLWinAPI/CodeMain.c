
#include <windows.h>
#define PATH L"DLLCode.dll"
typedef int(_cdecl* MyFunction)(LPWSTR);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    
    HINSTANCE MyDLL;
    if ((MyDLL = LoadLibrary(PATH)) == NULL) return 1;
    MyFunction myFun = (MyFunction)GetProcAddress(MyDLL, "ReadFile");
    myFun(L"./DLL/UsingDLLWinAPI/Users.csv");
    FreeLibrary(MyDLL);//отключение DLL
    return 0;
}
