#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

HANDLE hProc{ 0 };
uintptr_t moduleBase, localplayerptr;

DWORD procId;

bool processFound;

float iFovValue{};

void GetInformation() {

	procId = GetProcId(L"Overwatch.exe");

	if (!procId) {

		processFound = 0;
	}
	else {
		hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		moduleBase = GetModuleBaseAddress(procId, L"Overwatch.exe");
		std::cout << (int)moduleBase << "\n";
		localplayerptr = moduleBase + 0x3B67458;
		std::cout << (int)localplayerptr << "\n";
		processFound = 1;
	}
}
void iFovChanger() {
	printf("Enter FOV Value: ");
	std::cin >> iFovValue;
	printf("\n");
	WriteProcessMemory(hProc, (BYTE*)localplayerptr, &iFovValue, sizeof(iFovValue), nullptr); 

}
int main() {
		GetInformation();
		if (processFound) {iFovChanger();}
		else {std::cout << "Process not found! \n"; return 0;}
}

