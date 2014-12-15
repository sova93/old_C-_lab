#pragma once
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include "windows.h"
#include "process.h"
#define _ELPP_THREAD_SAFE
#include "easylogging++.h"

using namespace std;

enum CurrentState { WILL_DIE, CAN_WORK,BUSY, DEAD }; //thread's state
typedef void(*FuncType)(void*);

struct InformOfMethod //information about user's function
{
	FuncType functionForMethod;
	void *param;
};

class ThreadPool
{
private:
	class Task //class for adding user's function
	{
	private:
		ThreadPool *parent;
	public:
		Task(ThreadPool *);
		~Task(void);
		bool addFunction(FuncType, void*);
	};

	class Worker //class for working thread
	{
	public:
		Worker(ThreadPool *);
		~Worker(void);
	private:
		struct WorkerThread
		{
			HANDLE thread;
			CurrentState currentState;
			InformOfMethod task;
			HANDLE mutexBusy;
			HANDLE semaphore;
			
		};

		InformOfMethod requestTask();
		void lookAroundWorkers();
		void dispatch(InformOfMethod *);
		void createWorker(InformOfMethod *);
		void killWorker(WorkerThread *);

		static DWORD WINAPI threadWorkerDispatcher(PVOID pvParam);
		static DWORD WINAPI threadWorker(PVOID pvParam);

		vector<WorkerThread*> threads;
		int threadCounter;
		ThreadPool *parent;
		HANDLE threadMain;
	};

	int AmountThreadMin;
	int AmountThreadMax;
	int priority;
	int numberThreadForChange;
	queue<InformOfMethod> tasks;
	HANDLE notEmptySem;
	HANDLE queueMutex;

public:
	ThreadPool(int, int,int,int);
	~ThreadPool(void);
	Task *taskD;
	Worker *workdD;
};
