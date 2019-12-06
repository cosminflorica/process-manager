#include<iostream>
#include"DumpEngine.h"
#include"ProcessManager.h"
#include"Process.h"

DumpEngine::DumpEngine()
{
	this->Manager = new ProcessManager();
}
DumpEngine::DumpEngine(ProcessManager * Process) : DumpEngine()
{
	this->Manager = Process;
}
DumpEngine::~DumpEngine()
{
	delete this->Manager;
}
void DumpEngine::filltxt(char * fileName)
{
	FILE*dumpFile = fopen("SimpleDump.txt", "r+");
	fseek(dumpFile, 0, SEEK_END);
	FILE*f = fopen(fileName, "r");
	char* line = new char[this->Manager->GetMaxMemory() + 1];
	while (fgets(line, this->Manager->GetMaxMemory() + 1, f) != NULL)
	{
		fputs(line,dumpFile);
	}
	fclose(f);
	fclose(dumpFile);
	delete line;
}
void DumpEngine::create_txt(char* fileName) //tot fisierul
{
	int inputFileLength;
	char*line;
	char*outputFileName = new char[strlen(fileName) + strlen("IntelligentDump") + 2];
	strcpy(outputFileName, "IntelligentDump_");
	strcat(outputFileName, fileName);
	strcat(outputFileName, ".txt");

	FILE*fIn = fopen(fileName, "r");
	FILE*fOut = fopen(outputFileName, "w+");
	fseek(fIn, 0, SEEK_END);
	inputFileLength = ftell(fIn);
	rewind(fIn);
	line = new char[inputFileLength + 1];
	while (fgets(line, inputFileLength + 1, fIn) != NULL)
		fputs(line, fOut);
}
void DumpEngine::create_txt(char * fileName, int offset) //de la inceput pana la offset
{
	int inputFileLength;
	char*line;
	char*outputFileName = new char[strlen(fileName) + strlen("IntelligentDump") + 2];
	strcpy(outputFileName, "IntelligentDump_");
	strcat(outputFileName, fileName);
	strcat(outputFileName, ".txt");

	FILE*fIn = fopen(fileName, "r");
	FILE*fOut = fopen(outputFileName, "w+");

	fseek(fIn, 0, SEEK_END);
	inputFileLength = ftell(fIn);
	rewind(fIn);
	line = new char[inputFileLength + 1];
	fgets(line, offset + 1, fIn);
	fputs(line, fOut);
	
	//std::cout << line;
}
void DumpEngine::create_txt(int offset, char * fileName) // de la offset pana la sfarsit
{
	int inputFileLength;
	char*line;
	char*outputFileName = new char[strlen(fileName) + strlen("IntelligentDump") + 6];
	strcpy(outputFileName, "IntelligentDump_");
	strcat(outputFileName, fileName);
	strcat(outputFileName, ".txt");
	FILE*fIn = fopen(fileName, "r");
	FILE*fOut = fopen(outputFileName, "w+");

	
	fseek(fIn, 0, SEEK_END);
	inputFileLength = ftell(fIn);
	rewind(fIn);
	fseek(fIn, offset, SEEK_CUR);
	line = new char[inputFileLength + 1];
	fgets(line, inputFileLength + 1, fIn);
	fputs(line, fOut);
	
	//std::cout << line;
}