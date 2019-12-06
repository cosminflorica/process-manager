#include<iostream>
#include"ProcessManager.h"
#include"DumpEngine.h"
#include"SimpleDump.h"
#include"IntelligentDump.h"
using namespace std;


int main()
{
	ProcessManager *P=new ProcessManager(1024,"in.txt");
	P->run();
	std::cout << "\n";
	P->ps();
	// int simple_dump_start, simple_dump_end, intelligent_dump_start, intelligent_dump_end;
	// cin >> simple_dump_start >> simple_dump_end >> intelligent_dump_start >> intelligent_dump_end;
	// SimpleDump*sd = new SimpleDump(P, 10,200);
	// IntelligentDump*id = new IntelligentDump(P, intelligent_dump_start, intelligent_dump_end);
}