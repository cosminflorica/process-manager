#include"SimpleDump.h"


SimpleDump::SimpleDump(ProcessManager *p, int begin_offset, int end_offset)
{
	this->Manager = p;
	if (end_offset > begin_offset)
	{
		Process*copyhead = new Process();
		copyhead = p->GetHead();

		while (copyhead != NULL)
		{
			filltxt(copyhead->GetProcessName());
			if (copyhead->GetDllHead() != NULL)
			{
				filltxt(copyhead->GetDllHeadName());
				if (copyhead->GetDllHeadNext() != NULL)
					filltxt(copyhead->GetNextDllName());
			}
			copyhead = copyhead->GetNextProcess();
		}

		FILE*dumpFile = fopen("SimpleDump.txt", "r+");
		fseek(dumpFile, begin_offset, SEEK_SET);
		char*line = new char[this->Manager->GetMaxMemory() + 1];
		fgets(line, this->Manager->GetMaxMemory() + 1, dumpFile);
		char*copyline = new char[end_offset - begin_offset + 1];
		strncpy(copyline, line, end_offset - begin_offset);
		copyline[end_offset - begin_offset] = '\0';
		remove("SimpleDump.txt");
		FILE*f = fopen("SimpleDump.txt", "w");

		fputs(copyline, f);
		fclose(f);
		delete copyhead;
		delete line;
	}
}

