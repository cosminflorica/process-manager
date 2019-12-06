#pragma once
#include"Process.h"
#include"ProcessManager.h"

#ifndef DUMPENGINE_H
#define DUMPENGINE_H

class DumpEngine 
{
protected:
	ProcessManager* Manager;
public:
	DumpEngine();
	DumpEngine(ProcessManager* Process);
	~DumpEngine();
	void filltxt(char* fileName);
	void create_txt(char* fileName);
	void create_txt(char*fileName, int offset);
	void create_txt(int offset, char*fileName);
};



#endif