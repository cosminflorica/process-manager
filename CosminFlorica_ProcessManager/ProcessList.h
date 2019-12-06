#pragma once
#include"Process.h"

#ifndef PROCESSLIST_H
#define PROCESSLIST_H

class ProcessList
{
protected:
	Process *head;
public:
	ProcessList();
	ProcessList(char *fileName);
};

#endif