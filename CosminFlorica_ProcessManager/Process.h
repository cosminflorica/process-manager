#pragma once
#include<iostream>
#include<stdio.h>


#ifndef PROCESS_H
#define PROCESS_H

struct Dll
{
	char *Dllname;
	int DllSize;
	int DllOfset;
	Dll* nextDll;
};

class Process
{
	
protected:
	char *ProcessName;
	int ProcessId;
	int ProcessParentId;
	int ProcessCounter;
	int ProcessSize;
	int ProcessOffset;
	Dll *DllHead;
	Process *NextProcess;
public:

	Process();
	Process(char *line);
	Process(const Process& P);
	~Process();
	void buildDllList(char *list);

	void SetProcessName(char* nume);
	void SetProcessId(int id);
	void SetProcessParentId(int id);
	void SetNextProcess(Process* p);
	void SetProcessOffset(int offset);
	void SetProcessSize(int size);
	void SetNextDll(Dll*p);
	void SetDllHeadOffset(int offset);
	void SetDllHeadSize(int size);
	void SetNextDllOffset(int offset);
	void SetNextDllSize(int size);
	void SetProcessDllHead(Dll*p);

	int GetProcessCounter();
	char* GetProcessName();
	int GetProcessId();
	int GetProcessParentId();
	int GetProcessOffset();
	int GetProcessSize();
	int GetDllHeadOffset();
	int GetDllHeadSize();
	int GetNextDllOffset();
	int GetNextDllSize();
	char* GetDllHeadName();
	char* GetNextDllName();
	Dll* GetDllHead();
	Dll* GetDllHeadNext();
	Process* GetNextProcess();
};


#endif