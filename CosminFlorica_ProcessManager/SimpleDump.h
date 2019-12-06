#pragma once
#include"DumpEngine.h"
#include"ProcessManager.h"


#ifndef SIMPLEDUMP_H
#define SIMPLEDUMP_H

class SimpleDump : public DumpEngine
{
public:
	SimpleDump(ProcessManager*p, int begin_offset, int end_offset);
};


#endif