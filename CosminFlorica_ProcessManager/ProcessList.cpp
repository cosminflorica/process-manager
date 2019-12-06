#include"Process.h"
#include"ProcessList.h"
#include<iostream>

ProcessList::ProcessList()
{
	this->head = new Process();
}
          
ProcessList::ProcessList(char * fileName)
{
	FILE *fIn = fopen(fileName, "r");
	int fileLength;
	fseek(fIn, 0, SEEK_END);
	fileLength = ftell(fIn);
	rewind(fIn);
	this->head = new Process();
	while (fileLength)
	{
		char *line = new char[fileLength];
		fgets(line, fileLength, fIn);
		fileLength -= strlen(line) + 1;
		if (this->head->GetProcessCounter() == 0)
		{
			this->head = new Process(line);
		}
		else
		{
			Process* copyHead = this->head;
			while (copyHead->GetNextProcess()!=NULL)
			{
				copyHead = copyHead->GetNextProcess();
			}
			Process* copyProcess = new Process(line);
			copyHead->SetNextProcess(copyProcess);
			
		}
		delete line;
	}

}