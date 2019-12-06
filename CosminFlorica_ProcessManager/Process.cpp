#include "Process.h"
#include<iostream>
#include<stdio.h>
using namespace std;

Process::Process()
{
	this->ProcessCounter = 0;
	this->ProcessName = new char[20];
	this->ProcessOffset = -1;
	this->ProcessSize = -1;
}
Process::Process(char * line) :Process()
{

	int ok = 0;
	char *p, *nume, *id, *idp, *dllList;
	dllList = (char*)malloc((strlen(line) + 1)*sizeof(char));
	strcpy(dllList, "lista_nula");
	p = strtok(line, " \n");
	while (p)
	{
		if (ok == 0) { nume = _strdup(p); SetProcessName(nume); free(nume); }
		if (ok == 1) { id = _strdup(p); SetProcessId(atoi(id)); free(id); }
		if (ok == 2) { idp = _strdup(p);; SetProcessParentId(atoi(idp)); free(idp); }
		if (ok == 3) { strcpy(dllList, p); }
		else if(ok>3)
		{ 
			strcat(dllList, " "); 
			strcat(dllList, p); 
		}
		ok++;
		p = strtok(NULL, " \n");
	}
	buildDllList(dllList);
	ProcessCounter++;
	free(dllList);
}
Process::Process(const Process& P)
{
	this->ProcessName = new char[strlen(P.ProcessName) + 1];
	strcpy(this->ProcessName, P.ProcessName);
	this->ProcessId = P.ProcessId;
	this->ProcessParentId = P.ProcessParentId;
	this->ProcessCounter = P.ProcessCounter;
	this->NextProcess = P.NextProcess;
}

Process::~Process()
{
	delete(this->ProcessName);
	delete(this->DllHead->Dllname);
	delete DllHead;
	delete NextProcess;
}

void Process::buildDllList(char * dllList)
{
	if (strcmp(dllList,"lista_nula")==0)
		this->DllHead = NULL;
	else
	{
		char* list = _strdup(dllList);
		char* p = strtok(list, " \n");
		while (p)
		{
			if (DllHead == NULL)
			{
				DllHead = new Dll;
				DllHead->Dllname = new char[strlen(dllList)+1];
				DllHead->DllSize = -1;
				DllHead->DllOfset = -1;
				strcpy(DllHead->Dllname, p);
				DllHead->nextDll = NULL;
			}
			else
			{
				Dll* copyhead = new Dll;

				copyhead = DllHead;
				while (copyhead->nextDll != NULL)
				{
					copyhead = copyhead->nextDll;
				}
				copyhead->nextDll = new Dll;
				copyhead->nextDll->Dllname = new char[strlen(dllList)+1];
				strcpy(copyhead->nextDll->Dllname, p);
				copyhead->DllOfset = -1;
				copyhead->DllSize = -1;
				copyhead->nextDll->nextDll = NULL;
			}
			p = strtok(NULL, " \n");
		}
		free(list);
		free(p);
	}
}

void Process::SetProcessName(char * nume)
{
	strcpy(ProcessName, nume);
}
void Process::SetProcessId(int id)
{
	ProcessId = id;
}
void Process::SetProcessParentId(int id)
{
	ProcessParentId = id;
}
void Process::SetNextProcess(Process* p)
{
	this->NextProcess = new Process();
	this->NextProcess = p;
}
void Process::SetProcessOffset(int offset)
{
	this->ProcessOffset = offset;
}
void Process::SetProcessSize(int size)
{
	this->ProcessSize = size;
}
void Process::SetNextDll(Dll * p)
{
	this->DllHead = p;
}
void Process::SetDllHeadOffset(int offset)
{
	this->DllHead->DllOfset = offset;
}
void Process::SetDllHeadSize(int size)
{
	this->DllHead->DllSize = size;
}
void Process::SetNextDllOffset(int offset)
{
	this->DllHead->nextDll->DllOfset = offset;
}
void Process::SetNextDllSize(int size)
{
	this->DllHead->nextDll->DllSize = size;
}
void Process::SetProcessDllHead(Dll * p)
{
	this->DllHead = p;
}

int Process::GetProcessCounter()
{
	return this->ProcessCounter;
}
char* Process::GetProcessName()
{
	return this->ProcessName;
}
int Process::GetProcessId()
{
	return this->ProcessId;
}
int Process::GetProcessParentId()
{
	return this->ProcessParentId;
}
int Process::GetProcessOffset()
{
	return this->ProcessOffset;
}
int Process::GetProcessSize()
{
	return this->ProcessSize;
}
int Process::GetDllHeadOffset()
{
	return this->DllHead->DllOfset;
}
int Process::GetDllHeadSize()
{
	return this->DllHead->DllSize;
}
int Process::GetNextDllOffset()
{
	return this->DllHead->nextDll->DllOfset;
}
int Process::GetNextDllSize()
{
	return this->DllHead->nextDll->DllSize;
}
char* Process::GetDllHeadName()
{
	return this->DllHead->Dllname;
}
char* Process::GetNextDllName()
{
	return this->DllHead->nextDll->Dllname;
}
Dll* Process::GetDllHead()
{
	return this->DllHead;
}
Dll*  Process::GetDllHeadNext()
{
	return this->DllHead->nextDll;
}
Process* Process::GetNextProcess()
{
	return this->NextProcess;
}