#pragma once
#include"Process.h"
#include"ProcessList.h"
#include"LoadProcess.h"

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

class ProcessManager : public ProcessList
{
	int maxMemorySize;
	int NumberOfObjectsCreated;
	
public:
	ProcessManager();
	ProcessManager(int maxMemory, char* fileName);
	void set_offsets();
	int getFileLength(char*filename);
	void load();
	void deleteProcess(Process*&p);
	void deleleProcessAll(Process*&p);
	void runProcess(Process* p);
	Process* GetHead();
	int GetMaxMemory();
	void ps();
	void kill(int id);
	void killall(char* nume);
	void run();
};

#endif