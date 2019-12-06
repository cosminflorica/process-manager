#include<iostream>
#include"LoadProcess.h"
#include"Process.h"
using namespace std;

LoadProcess::LoadProcess()
{
	this->head = new Process;
}
LoadProcess::LoadProcess(Process * p):LoadProcess()
{
	this->head = p;
	modify_list(this->head);
}

LoadProcess::~LoadProcess()
{
	delete this->head;
}

void LoadProcess::modify_dll()
{
	Process* copyhead = new Process();
	copyhead = this->head->GetNextProcess();

	while (copyhead != NULL)
	{
		Process*aux = new Process();
		aux = this->head;
		while (aux != copyhead)
		{
			if (copyhead->GetDllHead() != NULL)
			{
				if (aux->GetDllHead() != NULL)
				{
					if (strcmp(copyhead->GetDllHeadName(), aux->GetDllHeadName()) == 0)
						copyhead->SetProcessDllHead(copyhead->GetDllHeadNext());
					if (aux->GetDllHeadNext() != NULL && copyhead->GetDllHead()!=NULL)
					{
						if (strcmp(copyhead->GetDllHeadName(), aux->GetNextDllName() )== 0)
							copyhead->SetProcessDllHead(copyhead->GetDllHeadNext());
						if (copyhead->GetDllHeadNext() != NULL)
						{
							if (strcmp(copyhead->GetNextDllName(), aux->GetDllHeadName()) == 0)
								copyhead->SetNextDll(NULL);
							if (strcmp(copyhead->GetNextDllName(), aux->GetNextDllName()) == 0)
								copyhead->SetNextDll(NULL);
						}	
					}
				}
			}
			aux = aux->GetNextProcess();
		}
		copyhead = copyhead->GetNextProcess();
	}
	delete copyhead;
}

void LoadProcess::modify_list(Process*&head)
{
	Process*copyhead = new Process();
	copyhead = head;
	Process* Parinte = new Process();
	Process* copyParinte = new Process();
	Process* Aux = new Process();
	while (copyhead != NULL)
	{

		Aux = head;
		if (copyhead->GetProcessParentId() == 0)
		{
			Parinte = copyhead;
			copyParinte = Parinte;

			while (Aux->GetNextProcess() != NULL)
			{
				if (copyParinte->GetProcessId() == Aux->GetNextProcess()->GetProcessParentId())
				{
					Process*NextParinte = new Process();
					NextParinte = Parinte->GetNextProcess();
					Parinte->SetNextProcess(Aux->GetNextProcess());
					Aux->SetNextProcess(Parinte->GetNextProcess()->GetNextProcess());
					Parinte->GetNextProcess()->SetNextProcess(NextParinte);
					Parinte = Parinte->GetNextProcess();

				}
				if (Aux->GetNextProcess() != NULL)
					Aux = Aux->GetNextProcess();
				else break;
			}
			/*if (Aux->GetNextProcess() == NULL)
			{

				if (copyParinte->GetProcessId() == Aux->GetProcessParentId())
				{
					Process*NextParinte = new Process();
					NextParinte = Parinte->GetNextProcess();
					Parinte->SetNextProcess(Aux);
					Aux->SetNextProcess(NextParinte);
				}
			}*/
		}
		copyhead = copyhead->GetNextProcess();
	}
	modify_dll();
}


