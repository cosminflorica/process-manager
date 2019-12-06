#include "ProcessManager.h"
#include "LoadProcess.h"
#include<iostream>

ProcessManager::ProcessManager()
{
	this->head = new Process();
}
ProcessManager::ProcessManager(int maxMemory, char * fileName) : ProcessList(fileName)
{
	this->maxMemorySize = maxMemory;
	static int objnumber = 0;
	objnumber++;
	this->NumberOfObjectsCreated = objnumber;
	load();
}
void ProcessManager::load()
{
	LoadProcess* p = new LoadProcess(this->head);
	set_offsets();
	delete p;
}
void ProcessManager::deleteProcess(Process *&p)
{
	Process* copyhead = new Process();
	int id = p->GetProcessId();
	if (head == p)
	{
		head = head->GetNextProcess();
		copyhead = head;
		while (copyhead != NULL)
		{
			if (copyhead->GetProcessParentId() == id)
				copyhead->SetProcessParentId(0);
			copyhead = copyhead->GetNextProcess();
		}
	}
	copyhead = head;
	Process*aux = new Process();
	while (copyhead->GetNextProcess() != NULL)
	{

		if (copyhead->GetNextProcess() == p)
		{
			aux = copyhead;
			copyhead->SetNextProcess(p->GetNextProcess());
			while (aux != NULL)
			{
				if (aux->GetProcessParentId() == id)
					aux->SetProcessParentId(0);
				aux = aux->GetNextProcess();
			}
		}
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
	delete aux;
}
void ProcessManager::deleleProcessAll(Process *& p)
{
	Process* copyhead = new Process();
	int id = p->GetProcessId();
	if (head == p)
	{
		head = head->GetNextProcess();
		copyhead = head;
		while (copyhead != NULL)
		{
			if (copyhead->GetProcessParentId() == id)
				head = head->GetNextProcess();
			copyhead = copyhead->GetNextProcess();
		}
	}
	copyhead = head;
	Process*aux = new Process();
	while (copyhead->GetNextProcess() != NULL)
	{

		if (copyhead->GetNextProcess() == p)
		{
			aux = copyhead;
			copyhead->SetNextProcess(p->GetNextProcess());
			while (aux != NULL)
			{
				if (aux->GetProcessParentId() == id)
				{
					copyhead->SetNextProcess(aux->GetNextProcess());
				}
				aux = aux->GetNextProcess();
			}
		}
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
	delete aux;

}
void ProcessManager::runProcess(Process* p)
{
	char*line = new char[p->GetProcessSize() + 1];

	FILE*f = fopen(p->GetProcessName(), "r");
	while (fgets(line, p->GetProcessSize() + 1, f)!=NULL)
		std::cout <<"\t"<< line;
	fclose(f);
	delete []line;
	std::cout << "\n";
	if (p->GetDllHead() != NULL)
	{
		char*line = new char[p->GetDllHeadSize() + 1];
		FILE*f = fopen(p->GetDllHeadName(), "r");
		std::cout << p->GetDllHeadName() << ": \n";
		while (fgets(line, p->GetDllHeadSize()+1, f)!=NULL)
			std::cout << "\t" << line;
		fclose(f);
		//delete line;
		std::cout << "\n";
		delete []line;
		if (p->GetDllHeadNext() != NULL)
		{
			char* line = new char[p->GetNextDllSize() + 1];
			FILE *f = fopen(p->GetNextDllName(), "r");
			std::cout << p->GetNextDllName() << ":\n";
			while (fgets(line, p->GetNextDllSize() + 1, f))
				std::cout << "\t" << line;
			fclose(f);
			std::cout << "\n";
			delete []line;

		}
	}
}
Process * ProcessManager::GetHead()
{
	return this->head;
}
int ProcessManager::GetMaxMemory()
{
	return this->maxMemorySize;
}
void ProcessManager::ps()
{
	Process*copyhead = new Process();
	copyhead = head;
	while (copyhead != NULL)
	{
		std::cout << copyhead->GetProcessName() << " id: " << copyhead->GetProcessId() << " in zona de memorie: <" << copyhead->GetProcessOffset() << " , " << copyhead->GetProcessSize()+copyhead->GetProcessOffset() << ">\n";
		if (copyhead->GetDllHead() != NULL)
		{
			std::cout << "\t"<< copyhead->GetDllHeadName() << " in zona de memorie: <" << copyhead->GetDllHeadOffset() << " , " << copyhead->GetDllHeadSize() + copyhead->GetDllHeadOffset()<<" >\n";
			if (copyhead->GetDllHeadNext() != NULL)
				std::cout <<"\t"<< copyhead->GetNextDllName() << " in zona de memorie: <" << copyhead->GetNextDllOffset() << " , " << copyhead->GetNextDllSize() + copyhead->GetNextDllOffset()<<" >\n";
		}
		copyhead = copyhead->GetNextProcess();
		std::cout << "\n";
	}
	delete copyhead;

}
void ProcessManager::kill(int id)
{
	Process*copyhead = new Process();
	copyhead = head;
	while (copyhead != NULL)
	{
		if (copyhead->GetProcessId() == id)
			deleteProcess(copyhead);
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
}
void ProcessManager::killall(char * nume)
{
	Process*copyhead = new Process();
	copyhead = head;
	while (copyhead != NULL)
	{
		if (strcmp(copyhead->GetProcessName(), nume) == 0)
			deleleProcessAll(copyhead);
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
}
void ProcessManager::run()
{
	Process*copyhead = new Process();
	copyhead = head;
	while (copyhead != NULL)
	{
		std::cout<< copyhead->GetProcessName() << ": \n";
		runProcess(copyhead);
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
}
void ProcessManager::set_offsets()
{
	Process* copyhead = new Process();
	copyhead = head;
	int lastoffset = 0;
	while (copyhead != NULL)
	{
		if (lastoffset + getFileLength(copyhead->GetProcessName()) > (this->maxMemorySize))
		{
			std::cout << "S-a depasit memoria alocata la adaugarea procesului: " << copyhead->GetProcessName() << "\n";
			copyhead->SetNextProcess(NULL);
		}
		else
		{
			copyhead->SetProcessOffset(lastoffset);
			copyhead->SetProcessSize(getFileLength(copyhead->GetProcessName()));
			lastoffset = copyhead->GetProcessOffset() + copyhead->GetProcessSize();
		}
		
		if (copyhead->GetDllHead() != NULL)
		{
			if (lastoffset + getFileLength(copyhead->GetDllHeadName()) > this->maxMemorySize)
			{
				std::cout << "S-a depasit memoria alocata la adaugarea dll-ului: "<<copyhead->GetDllHeadName()<<" apartinand procesului: "<<copyhead->GetProcessName()<<"\n";
				copyhead->SetProcessDllHead(NULL);
				copyhead->SetNextProcess(NULL);
			}
			else
			{
				copyhead->SetDllHeadOffset(lastoffset);
				copyhead->SetDllHeadSize(getFileLength(copyhead->GetDllHeadName()));
				lastoffset = copyhead->GetDllHeadOffset() + copyhead->GetDllHeadSize();
				if (copyhead->GetDllHeadNext() != NULL)
				{
					if (lastoffset + getFileLength(copyhead->GetNextDllName()) > this->maxMemorySize)
					{
						std::cout << "S-a depasit memoria alocata la adaugarea dll-ului: " << copyhead->GetNextDllName() << " apartinand procesului: " << copyhead->GetProcessName() << "\n";
						copyhead->SetNextDll(NULL);
						copyhead->SetNextProcess(NULL);
					}
					else
					{
						copyhead->SetNextDllOffset(lastoffset);
						copyhead->SetNextDllSize(getFileLength(copyhead->GetNextDllName()));
						lastoffset = copyhead->GetNextDllOffset() + copyhead->GetNextDllSize();
					}
				}
			}
			
			
		}
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
}
int ProcessManager::getFileLength(char * filename)
{
	FILE *fIn = fopen(filename, "r");
	int filelength;
	fseek(fIn, 0, SEEK_END);
	filelength = ftell(fIn);
	rewind(fIn);
	fclose(fIn);
	return filelength;

}

