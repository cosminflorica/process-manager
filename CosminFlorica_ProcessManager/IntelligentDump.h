#pragma once
#include"DumpEngine.h"
#include"ProcessManager.h"

#ifndef INTELLIGENTDUMP_H
#define INTELLIGENTDUMP_H

class IntelligentDump : DumpEngine
{
public:
	IntelligentDump(ProcessManager*p, int begin_offset, int end_offset);
};


#endif