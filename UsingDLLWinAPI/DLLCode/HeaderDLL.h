
#pragma once
__declspec(dllimport) int myFunc(LPWSTR str);
__declspec(dllimport) void FileRead(struct person* pers);
__declspec(dllimport) void searchSurname(struct person* pers);
__declspec(dllimport) void writeToFile(struct person* current, int countCurrent);
__declspec(dllimport) void writeToFileIvanova(struct person* current, int countCurrent);
__declspec(dllimport) void searchSurnameIvanova(struct person* pers);



struct person
{
	char* Familia;
	char* Name;
	char* Othestvo;
	int ago;

};