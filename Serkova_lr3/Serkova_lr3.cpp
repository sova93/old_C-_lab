// Serkova_lr3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include "math.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int sum = 0, a = 0, b = 0;
	char equally;
	HANDLE access = CreateMutex(NULL, false, L"Mutex");
	HANDLE sharedMemory = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, 16, L"SharedMemory");
	if (sharedMemory != NULL)
	{
		void* adressOfSharedMemory = MapViewOfFile(sharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
		while (true)
		{
			WaitForSingleObject(access, INFINITE);
			memcpy(&sum, adressOfSharedMemory, sizeof(int));
			if (sum != 0)
			{
				std::cout << sum << std::endl;
			}
			std::cout << "Enter nuber for sum A and B" << std::endl;
			std::cin >> a >> b;
			sum = a + b;
			memcpy(adressOfSharedMemory, &sum, sizeof(int));
			ReleaseMutex(access);
			std::cout << "Enter = for getting sum from other window" << std::endl;
			std::cin >> equally;
			if (equally != '=')	{UnmapViewOfFile(adressOfSharedMemory);	break;}
			WaitForSingleObject(access, INFINITE);
			memcpy(&sum, adressOfSharedMemory, sizeof(int));
			ReleaseMutex(access);
		}
	}
	return 0;
}



