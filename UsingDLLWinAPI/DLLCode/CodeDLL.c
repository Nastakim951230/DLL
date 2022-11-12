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

    //(если не работае нужно поставить суда полную ссылку файла)
    HANDLE Start = CreateFile(L"C:\\Users\\ТрифоноваАР\\source\\repos\\DLL\\UsingDLLWinAPI\\DLLCode\\Users2.csv", //Ссылка на открытие файла
        GENERIC_READ,//Открытие для чтения
        FILE_SHARE_READ,//Чтение
        NULL, // Защита по умолчанию
        OPEN_EXISTING, // Только существующий файл
        FILE_ATTRIBUTE_NORMAL,//Обычный файл
        NULL);//атрибут шаблона

    if (Start == INVALID_HANDLE_VALUE) //Проверка неоткрывается ли файл
    {

        MessageBox(NULL, L"Ошибка, нельзя открыть файл", L"Оповещение", MB_OK);
        return;
    }
    DWORD countFileSymbols;
    LPCSTR argumentsFromFile = calloc(5000, sizeof(CHAR));
    if (!ReadFile(Start, argumentsFromFile, 5000, &countFileSymbols, NULL)) //Проверка на првильность чтения данных
    {
        MessageBox(NULL, L"Возникла ошибка при чтении данных!", L"Оповещение", MB_OK);
        return 0;
    }

    char* dataConvertToStruct = strtok(argumentsFromFile, ";"); //Разделяем стору 
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

void searchSurname(struct person* pers) //Поиск фамилии
{
    struct person* People = malloc(sizeof(struct person));
    struct person* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "Морозова";
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

void searchSurnameIvanova(struct person* pers) //Поиск фамилии по Иванова
{
    struct person* current = malloc(sizeof(struct person));
    struct person* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "Иванов";
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

void writeToFile(struct person* current, int countCurrent) //Запись среднего возраста
{
    HANDLE Result = CreateFile(L"Resultat.csv", // создаваемый файл
        GENERIC_WRITE, // открывается для записи
        FILE_SHARE_WRITE, // совместно не используется
        NULL, // защита по умолчанию
        CREATE_ALWAYS, // переписывает существующий
        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
        NULL); // атрибутов шаблона нет
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
    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
    WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(Result);
}

void writeToFileIvanova(struct person* current, int countCurrent)
{
    HANDLE Result = CreateFile(L"Ivanova.csv", // создаваемый файл
        GENERIC_WRITE, // открывается для записи
        FILE_SHARE_WRITE, // совместно не используется
        NULL, // защита по умолчанию
        CREATE_ALWAYS, // переписывает существующий
        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
        NULL); // атрибутов шаблона нет
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
    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
    WriteFile(Result, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(Result);
}