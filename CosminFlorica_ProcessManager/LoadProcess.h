#pragma once
#include"Process.h"

#ifndef LOADPROCESS_H
#define LOADPROCESS_H



class LoadProcess
{
	Process *head;
public:
	LoadProcess();
	LoadProcess(Process* p);
	~LoadProcess();
	void modify_dll();
	void modify_list(Process*&head);
	
};

#endif