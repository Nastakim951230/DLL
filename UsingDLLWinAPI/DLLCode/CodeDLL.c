#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "HeaderDLL.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    switch (fdwReason)
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
    return TRUE;
}


void FileRead(struct person* pers)
{

    //(���� �� ������� ����� ��������� ���� ������ ������ �����)
    HANDLE Start = CreateFile(L"C:\\Users\\�����������\\source\\repos\\DLL\\UsingDLLWinAPI\\DLLCode\\Users2.csv", //������ �� �������� �����
        GENERIC_READ,//�������� ��� ������
        FILE_SHARE_READ,//������
        NULL, // ������ �� ���������
        OPEN_EXISTING, // ������ ������������ ����
        FILE_ATTRIBUTE_NORMAL,//������� ����
        NULL);//������� �������

    if (Start == INVALID_HANDLE_VALUE) //�������� ������������� �� ����
    {

        MessageBox(NULL, L"������, ������ ������� ����", L"����������", MB_OK);
        return;
    }
    DWORD countFileSymbols;
    LPCSTR argumentsFromFile = calloc(5000, sizeof(CHAR));
    if (!ReadFile(Start, argumentsFromFile, 5000, &countFileSymbols, NULL)) //�������� �� ����������� ������ ������
    {
        MessageBox(NULL, L"�������� ������ ��� ������ ������!", L"����������", MB_OK);
        return 0;
    }

    char* dataConvertToStruct = strtok(argumentsFromFile, ";"); //��������� ����� 
    int countRecords;

    for (int i = 0; i < 100; i++) //
    {
        countRecords = i;
        pers[i].Familia = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        pers[i].Name = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        pers[i].Othestvo = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        pers[i].ago = atoi(dataConvertToStruct);
        dataConvertToStruct = strtok(NULL, ";\r\n");

    }
    CloseHandle(Start);

    searchSurname(pers);
    searchSurnameIvanova(pers);
}

void searchSurname(struct person* pers) //����� �������
{
    struct person* People = malloc(sizeof(struct person));
    struct person* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "��������";
    for (int i = 0; i < 100; i++)
    {
        if (strstr(pers[i].Familia, forComprasion) != NULL)
        {
            People[j] = pers[i];
            forCurrentPeople = realloc(People, (j + 2) * sizeof(struct person));
            j++;
            People = forCurrentPeople;
        }
    }
    writeToFile(People, j);
}

void searchSurnameIvanova(struct person* pers) //����� ������� �� �������
{
    struct person* current = malloc(sizeof(struct person));
    struct person* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "������";
    for (int i = 0; i < 100; i++)
    {
        if (strstr(pers[i].Familia, forComprasion) != NULL)
        {
            current[j] = pers[i];
            forCurrentPeople = realloc(current, (j + 2) * sizeof(struct person));
            j++;
            current = forCurrentPeople;
        }
    }
    writeToFileIvanova(current, j);
}

void writeToFile(struct person* current, int countCurrent) //������ �������� ��������
{
    HANDLE Result = CreateFile(L"Resultat.csv", // ����������� ����
        GENERIC_WRITE, // ����������� ��� ������
        FILE_SHARE_WRITE, // ��������� �� ������������
        NULL, // ������ �� ���������
        CREATE_ALWAYS, // ������������ ������������
        FILE_ATTRIBUTE_NORMAL, // ����������� ����/����� I/O
        NULL); // ��������� ������� ���
    DWORD countFileSymbols;
    float averageAge = 0;
    char* dataForWritting = calloc(100, sizeof(char));
    for (int i = 0; i < countCurrent; i++)
    {
        sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Familia, current[i].Name, current[i].Othestvo, current[i].ago);
        WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
        averageAge += current[i].ago;
    }
    averageAge /= countCurrent;
    sprintf(dataForWritting, "������� �������: %f", averageAge);
    WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(Result);
}

void writeToFileIvanova(struct person* current, int countCurrent)
{
    HANDLE Result = CreateFile(L"Ivanova.csv", // ����������� ����
        GENERIC_WRITE, // ����������� ��� ������
        FILE_SHARE_WRITE, // ��������� �� ������������
        NULL, // ������ �� ���������
        CREATE_ALWAYS, // ������������ ������������
        FILE_ATTRIBUTE_NORMAL, // ����������� ����/����� I/O
        NULL); // ��������� ������� ���
    DWORD countFileSymbols;
    float averageAge = 0;
    char* dataForWritting = calloc(100, sizeof(char));
    for (int i = 0; i < countCurrent; i++)
    {
        sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Familia, current[i].Name, current[i].Othestvo, current[i].ago);
        WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
        averageAge += current[i].ago;
    }
    averageAge /= countCurrent;
    sprintf(dataForWritting, "������� �������: %f", averageAge);
    WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(Result);
}