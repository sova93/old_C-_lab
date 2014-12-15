#include "stdafx.h"
#include "ThreadPool.h"
#include "easylogging++.h"
#define _ELPP_THREAD_SAFE

ThreadPool::ThreadPool(int min, int max, int newNumberThreadForChange, int newPriority) //creating thread pool
{
	AmountThreadMin = min;
	AmountThreadMax = max;
	numberThreadForChange = newNumberThreadForChange;
	priority = newPriority;
	LOG(INFO) << "Minimum amount of threads = " << to_string(AmountThreadMin);
	LOG(INFO) << "Maximum amount of threads = " << to_string(AmountThreadMax);
	taskD = new Task(this);
	workdD = new Worker(this);
	queueMutex = CreateMutex(NULL, false, NULL);
	notEmptySem = CreateSemaphore(NULL, 0, 1000, NULL);
}

ThreadPool::~ThreadPool(void) //killing thread pool
{
	delete taskD;
	delete workdD;
	CloseHandle(queueMutex);
	CloseHandle(notEmptySem);
}

ThreadPool::Task::Task(ThreadPool *parent_)
{
	parent = parent_;
}

ThreadPool::Task::~Task(void)
{
}

bool ThreadPool::Task::addFunction(FuncType newFunction, void* newParameter) //procedure for adding user's function
{
	long oldState = 0;
	WaitForSingleObject(parent->queueMutex, INFINITE);
	InformOfMethod newInformation;
	newInformation.functionForMethod = newFunction;
	newInformation.param = newParameter;
	parent->tasks.push(newInformation);
	ReleaseSemaphore(parent->notEmptySem, 1, &oldState);
	ReleaseMutex(parent->queueMutex);
	return true;
}

ThreadPool::Worker::Worker(ThreadPool *parent_) //constructor for worker-threads
{
	parent = parent_;
	threads.reserve(1000);
	InformOfMethod *emptyTask = new InformOfMethod;
	emptyTask->param = NULL;
	emptyTask->functionForMethod = NULL;
	for (int i = 0; i < parent_->AmountThreadMin; i++)
	{
		createWorker(emptyTask);
		if (i + 1 == parent_->numberThreadForChange)
		{
			switch (parent_->priority)
			{
			case 1: 
				SetThreadPriority(threads[i]->thread,THREAD_PRIORITY_TIME_CRITICAL ); 
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Time-critical";
				break;
			case 2:
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_HIGHEST);
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Highest"; 
				break;
			case 3:
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_ABOVE_NORMAL);
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Above normal"; 
				break;
			case 4:
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_NORMAL);
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Normal"; 
				break;
			case 5: 
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_BELOW_NORMAL); 
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Below normal"; 
				break;
			case 6:
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_LOWEST);
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Lowest"; 
				break;
			case 7: 
				SetThreadPriority(threads[i]->thread, THREAD_PRIORITY_IDLE);
				LOG(INFO) << "id " << GetThreadId(threads[i]->thread) << " Have priority Idle"; 
				break;
			default:
				break;
			}
		}
	}//choice priority
	//Sleep(100);
	threadMain = CreateThread(NULL, 0, ThreadPool::Worker::threadWorkerDispatcher, this, 0, NULL);
	LOG(INFO) << "____________Thread pool is created_____________";
}

ThreadPool::Worker::~Worker(void) //destructor for worker-threads
{
	for (int i = 0; i < threads.size(); i++)
	{
		killWorker(threads[i]);
		threads.erase(threads.begin() + i);
		i--;
	}
	TerminateThread(threadMain, NULL);
	CloseHandle(threadMain);
}

InformOfMethod ThreadPool::Worker::requestTask()//request task for adding
{
	InformOfMethod result = { 0 };
	WaitForSingleObject(parent->queueMutex, INFINITE);
	if (!parent->tasks.empty())
	{
		result = parent->tasks.front();
		parent->tasks.pop();
	}
	else LOG(WARNING) << "Queue is empty!";
	ReleaseMutex(parent->queueMutex);
	return result;
}

void ThreadPool::Worker::lookAroundWorkers() //look state of threads in pool
{
	int result = 0;
	int flagForDelete = 0;
	for (int i = 0; i < threads.size(); i++)
	{
		if (WaitForSingleObject(threads[i]->mutexBusy, 0) == WAIT_OBJECT_0)
		{
			bool isDead = false;
			if ((threads[i]->currentState == DEAD) || ((parent->AmountThreadMin < threads.size() - flagForDelete - 1) && (threads[i]->currentState == CAN_WORK)))
			{
				switch (threads[i]->currentState)
				{
				case DEAD:
					killWorker(threads[i]);
					threads.erase(threads.begin() + i);
					i--;
					isDead = true;
					break;
				case CAN_WORK:
					threads[i]->currentState = WILL_DIE;
					flagForDelete++;
				}
			}
			if (!isDead) ReleaseMutex(threads[i]->mutexBusy);
		}
	}
}

void ThreadPool::Worker::dispatch(InformOfMethod *newFunction) //adding function in work
{
	bool noFreeWorkers = true;
	long oldState = 0;
	InformOfMethod emptyTask = { 0 };
	for (int i = 0; i < threads.size(); i++)
	{
		if (WaitForSingleObject(threads[i]->mutexBusy, 0) == WAIT_OBJECT_0)
		{
			if (noFreeWorkers)
			{
				if (threads[i]->currentState == CAN_WORK || threads[i]->currentState == WILL_DIE)
				{
					threads[i]->task = *newFunction;
					ReleaseSemaphore(threads[i]->semaphore, 1, &oldState);
					noFreeWorkers = false;
				}
			}
			else
			{
				if (threads[i]->currentState == WILL_DIE)
				{
					threads[i]->task = emptyTask;
					ReleaseSemaphore(threads[i]->semaphore, 1, &oldState);
				}
			}
			ReleaseMutex(threads[i]->mutexBusy);
		}
	}
	if (noFreeWorkers)
		createWorker(newFunction);
}

void ThreadPool::Worker::createWorker(InformOfMethod *newFunction)//creating new worker
{
	threads.push_back(new WorkerThread);
	threads.back()->mutexBusy = CreateMutex(NULL, false, NULL);
	WaitForSingleObject(threads.back()->mutexBusy, INFINITE);
	threads.back()->task.functionForMethod = newFunction->functionForMethod;
	threads.back()->task.param = newFunction->param;
	threads.back()->currentState = CAN_WORK;
	threads.back()->semaphore = CreateSemaphore(NULL, 0, 1000, NULL);
	threads.back()->thread = CreateThread(NULL, 0, ThreadPool::Worker::threadWorker, threads.back(), 0, NULL);
	LOG(INFO) << "id " << GetCurrentThreadId() << ": create thread: id = " << GetThreadId(threads.back()->thread);
	ReleaseMutex(threads.back()->mutexBusy);  
	if (threads.size() > parent->AmountThreadMax) LOG(WARNING) << "WARNING! exceeded the maximum number of threads!";
}

void ThreadPool::Worker::killWorker(WorkerThread *target)//killing worker
{
	LOG(INFO) << "id " << GetCurrentThreadId() << ": kill thread: id = " << GetThreadId(target->thread);
	CloseHandle(target->mutexBusy);
	CloseHandle(target->semaphore);
	CloseHandle(target->thread);
}

DWORD WINAPI ThreadPool::Worker::threadWorkerDispatcher(PVOID pvParam)//function for WINAPI creating new worker dispatcher
{
	ThreadPool::Worker *currentWorker = (ThreadPool::Worker *)pvParam;
	ThreadPool *parent = currentWorker->parent;
	InformOfMethod currentTask;
	LOG(INFO) << "id " << GetCurrentThreadId() << ": worker dispatcher thread created";
	while (true)
	{
		WaitForSingleObject(parent->notEmptySem, INFINITE);
		currentTask = currentWorker->requestTask();
		currentWorker->lookAroundWorkers();
		currentWorker->dispatch(&currentTask);
	}
	return 0;
}

DWORD WINAPI ThreadPool::Worker::threadWorker(PVOID pvParam)//function for WINAPI creating thread worker
{
	ThreadPool::Worker::WorkerThread *currentWorker = (ThreadPool::Worker::WorkerThread *)pvParam;

	while (true)
	{
		WaitForSingleObject(currentWorker->mutexBusy, INFINITE);
		CurrentState instruction = currentWorker->currentState;  //save instruction from WD

		currentWorker->currentState = BUSY;
		FuncType F = currentWorker->task.functionForMethod;
		void * param = currentWorker->task.param;
		if (F != NULL)
			F(param);

		if (instruction == WILL_DIE)
		{
			currentWorker->currentState = DEAD;
			ReleaseMutex(currentWorker->mutexBusy);
			return 0;
		}

		currentWorker->currentState = CAN_WORK;
		ReleaseMutex(currentWorker->mutexBusy);
		WaitForSingleObject(currentWorker->semaphore, INFINITE);   //wait for next task
	}
	return 0;
}

