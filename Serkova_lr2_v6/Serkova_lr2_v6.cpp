// Serkova_lr2_v6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "stdlib.h"
#include "iostream"
#include "stdio.h"
#include "time.h"
#include "process.h"
#include "ThreadPool.h"
#include "easylogging++.h" //library for logging
#define _ELPP_THREAD_SAFE
#define AMOUNT_THREAD 7

void Method(void*);
static DWORD WINAPI MainThreadFunction(PVOID pvParam);
ThreadPool *TP_Pool;
int  AmountThreadMax = 0, AmountThreadMin = 0, AmountTask = 0, flag=0, priority=0, numberThreadForChange=0;

_INITIALIZE_EASYLOGGINGPP

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	LOG(INFO) << "__________________________________"; 
	std::cout << "Enter the minimum amount of threads: "; //entering input data
	std::cin >> AmountThreadMin;
	if (AmountThreadMin == 0) AmountThreadMin = AMOUNT_THREAD;
	while (AmountThreadMax < AmountThreadMin)
	{
		std::cout << "Enter the maximum amount of threads: ";
		std::cin >> AmountThreadMax;
		if (AmountThreadMax == 0) AmountThreadMax = AmountThreadMin + 10;
	}
	std::cout << "Enter the amount of tasks: ";
	std::cin >> AmountTask;
	while (flag != 1 && flag != 2)
	{
		std::cout << "Choise priority? 1-no, 2-yes: ";
		std::cin >> flag;
	}
	if (flag == 2)
	{
		while((numberThreadForChange < 1) ||( numberThreadForChange > AmountThreadMin))
		{
			std::cout << "Enter thread: ";
			std::cin >> numberThreadForChange;
		}
		while ((priority < 1) || (priority >7))
		{
			std::cout << "1-Time-critical\n";
			std::cout << "2-Highest\n";
			std::cout << "3-Above normal\n";
			std::cout << "4-Normal\n";
			std::cout << "5-Below normal\n";
			std::cout << "6-Lowest\n";
			std::cout << "7-Idle\n";
			std::cin >> priority;
		}
	};
	//initialize the thread pool
	TP_Pool = new ThreadPool(AmountThreadMin, AmountThreadMax,numberThreadForChange,priority);
	int *ArrayOfTasks = new int[AmountTask];
	for (int i = 0; i < AmountTask; i++)
		ArrayOfTasks[i] = i + 1;
	for (int i = 0; i < AmountTask; i++)
	{
		TP_Pool->taskD->addFunction(Method, &ArrayOfTasks[i]);
		LOG(INFO) << "id " << GetCurrentThreadId() << ": task number " << ArrayOfTasks[i] << " added to the queue";
	}
	_getch();
	//finish cleaning
	delete TP_Pool;
	delete[] ArrayOfTasks;
	LOG(INFO) << "Array DELETED!";
	_getch();
	return 0;
}

void Method(void* param)//user's function for working
{
	int *i = (int*)param;
	int runtime = rand() % 10;

	if (runtime == 0)
	{
		LOG(INFO) << "id " << GetCurrentThreadId() << ": ERROR: task number " << *i << " is failed";
	}
	else
	{
		Sleep(runtime * 10000);
		LOG(INFO) << "id " << GetCurrentThreadId() << ": task number " << *i << " is complited";
	}

}