#pragma once
typedef int(_cdecl* forReadData)(struct person*);
struct person
{
	char* Familia;
	char* Name;
	char* Othestvo;
	int ago;

};