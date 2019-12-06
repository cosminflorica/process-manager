#include"IntelligentDump.h"

IntelligentDump::IntelligentDump(ProcessManager*p, int begin_offset, int end_offset)
{
	this->Manager = p;
	char* Start, *End;
	Start = new char[20];
	End = new char[20];
	Process*copyhead = new Process();
	int start_offset, last_offset;
	if (end_offset > begin_offset)
	{
		copyhead = this->Manager->GetHead();
		while (copyhead != NULL)
		{
			if ((copyhead->GetProcessOffset() < begin_offset) && (copyhead->GetDllHeadOffset() > begin_offset))
			{
				Start = copyhead->GetProcessName();
				start_offset = begin_offset - copyhead->GetProcessOffset();
				create_txt(start_offset, Start);
				break;
			}
			else if (copyhead->GetDllHead() != NULL)
			{
				if ((copyhead->GetDllHeadOffset() < begin_offset) && (copyhead->GetNextDllOffset() > begin_offset))
				{
					Start = copyhead->GetDllHeadName();
					start_offset = begin_offset - copyhead->GetDllHeadOffset();
					create_txt(start_offset, Start);
					break;
				}
				else if (copyhead->GetDllHeadNext() != NULL)
				{
					if ((copyhead->GetNextDllOffset() < begin_offset) && ((copyhead->GetNextDllOffset() + copyhead->GetNextDllSize()) > begin_offset))
					{
						Start = copyhead->GetNextDllName();
						start_offset = begin_offset - copyhead->GetNextDllOffset();
						create_txt(start_offset, Start);
						break;
					}
				}
			}
			copyhead = copyhead->GetNextProcess();
		}

		copyhead = this->Manager->GetHead();
		while (copyhead != NULL)
		{
			if ((copyhead->GetProcessOffset() < end_offset) && (copyhead->GetProcessOffset() + copyhead->GetProcessSize() > end_offset))
			{
				End = copyhead->GetProcessName();
				last_offset = end_offset - copyhead->GetProcessOffset();
				create_txt(End, last_offset);
				break;
			}
			else if (copyhead->GetDllHead() != NULL)
			{
				if ((copyhead->GetDllHeadOffset() < end_offset) && (copyhead->GetDllHeadOffset() + copyhead->GetDllHeadSize() > end_offset))
				{
					End = copyhead->GetDllHeadName();
					last_offset = end_offset - copyhead->GetDllHeadOffset();
					create_txt(End, last_offset);
					break;
				}
				else if (copyhead->GetDllHeadNext() != NULL)
				{
					if ((copyhead->GetNextDllOffset() < end_offset) && ((copyhead->GetNextDllOffset() + copyhead->GetNextDllSize()) > end_offset))
					{
						End = copyhead->GetNextDllName();
						last_offset = end_offset - copyhead->GetNextDllOffset();
						create_txt(End, last_offset);
						break;
					}
				}
			}
			copyhead = copyhead->GetNextProcess();
		}

		copyhead = this->Manager->GetHead();
		while (copyhead != NULL && strcmp(Start, End) != 0)
		{
			if (strcmp(copyhead->GetProcessName(), Start) == 0)
			{
				if (copyhead->GetDllHead() != NULL && strcmp(copyhead->GetDllHeadName(), End) != 0)
				{
					create_txt(copyhead->GetDllHeadName());
					if (copyhead->GetDllHeadNext() != NULL && strcmp(copyhead->GetNextDllName(), End) != 0)
						create_txt(copyhead->GetNextDllName());
					else break;
				}
				else break;

				Process*aux = new Process();
				aux = copyhead->GetNextProcess();
				while (aux != NULL)
				{
					if (strcmp(aux->GetProcessName(), End) != 0)
					{
						create_txt(aux->GetProcessName());
						if (aux->GetDllHead() != NULL && strcmp(aux->GetDllHeadName(), End) != 0)
						{
							create_txt(aux->GetDllHeadName());
							if (aux->GetDllHeadNext() != NULL && strcmp(aux->GetNextDllName(), End) != 0)
								create_txt(aux->GetNextDllName());
							else break;
						}
						else break;
					}
					else break;
					
					aux = aux->GetNextProcess();
				}
				break;
			}
			else if (copyhead->GetDllHead() != NULL && strcmp(copyhead->GetDllHeadName(), Start) == 0)
			{
				if (copyhead->GetDllHeadNext() != NULL && strcmp(copyhead->GetNextDllName(), End) != 0)
					create_txt(copyhead->GetNextDllName());
				else break;
				Process*aux = new Process();
				aux = copyhead->GetNextProcess();
				while (aux != NULL)
				{
					if (strcmp(aux->GetProcessName(), End) != 0)create_txt(aux->GetProcessName());
					if (aux->GetDllHead() != NULL && strcmp(aux->GetDllHeadName(), End) != 0)
					{
						create_txt(aux->GetDllHeadName());
						if (aux->GetDllHeadNext() != NULL && strcmp(aux->GetNextDllName(), End) != 0)
							create_txt(aux->GetNextDllName());
					}
					aux = aux->GetNextProcess();
				}
				break;
			}

			copyhead = copyhead->GetNextProcess();
		}
	}
	else std::cout << "Modificati valorile de offset";
	delete Start;
	delete End;
}
