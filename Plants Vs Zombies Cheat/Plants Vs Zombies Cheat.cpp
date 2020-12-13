// Plants Vs Zombies Cheat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include "mem.h"

int main()
{
	HANDLE hProcess = 0;

	uintptr_t moduleBase = 0,sunAddr = 0,moneyAddr = 0;
	bool Itemdelay = false, Sunpump = false, Sunreduce = false, GMPlants = false;
	const int newValue = 99999;
	//Get ProcId of the target process
	DWORD procId = GetProcId(L"popcapgame1.exe");

	if (procId)
	{
		//Get Handle to Process
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

		//Getmodulebaseaddress
		moduleBase = GetModuleBaseAddress(procId, L"popcapgame1.exe");

		uintptr_t dynamicPtrBaseAddr = moduleBase + 0x329670;

		sunAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, { 0x868, 0x5578 });
		moneyAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, { 0x9C, 0x50 });
		////std::cout << "Curent ammo = " << std::dec << ammoValue << std::endl;
		std::cout << "NUMPAD1 : Hack Sun 99999" << std::endl;
		std::cout << "NUMPAD2 : Pump Sun" << std::endl;
		std::cout << "NUMPAD3 : Item is not Delay" << std::endl;
		std::cout << "NUMPAD4 : Sun does not Reduce" << std::endl;
		std::cout << "NUMPAD5 : God Mode Plants" << std::endl;
	}
	else {
		std::cout << "Process not found, press enter to exit\n";
		getchar();
		return 0;
	}

	DWORD dwExit = 0;
	while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE)
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			mem::PatchEx((BYTE*)sunAddr, (BYTE*)&newValue, sizeof(newValue), hProcess);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			Sunpump = !Sunpump;

			if (Sunpump)
			{
				//FF 06 = inc [esi]
				mem::PatchEx((BYTE*)(moduleBase + 0x63418), (BYTE*)"\x81\x6F\x58\x00\x01\x00\x00\x8B\x77\x58", 10, hProcess);
				

			}

			else
			{
				//FF 0E = dec [esi]
				mem::PatchEx((BYTE*)(moduleBase + 0x63418), (BYTE*)"\xFF\x04F\x58\x90\x90\x90\x90\x8B\x77\x58", 10, hProcess);
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			Itemdelay = !Itemdelay;

			if (Itemdelay)
			{
				//FF 06 = inc [esi]
				mem::PatchEx((BYTE*)(moduleBase + 0x91E4C), (BYTE*)"\x81\x47\x24\x00\x02\x00\x00\x90\x90", 9, hProcess);
				

			}

			else
			{
				//FF 0E = dec [esi]
				mem::PatchEx((BYTE*)(moduleBase + 0x91E4C), (BYTE*)"\xFF\x47\x24\x8B\x47\x24\x3B\x47\x28", 9, hProcess);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			Sunreduce = !Sunreduce;

			if (Sunreduce)
			{
				mem::NopEx((BYTE*)(moduleBase + 0x1E846), 6, hProcess);
			}

			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x1E846), (BYTE*)"\x89\xB7\x78\x55\x00\x00", 6, hProcess);
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			GMPlants = !GMPlants;

			if (GMPlants)
			{
				mem::NopEx((BYTE*)(moduleBase + 0x140680), 4, hProcess);
			}

			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x140680), (BYTE*)"\x83\x46\x40\xFC", 4, hProcess);
			}
		}
		
		Sleep(10);
	}

	std::cout << "Process not found, press enter to exit\n";
	getchar();
	return 0;

	////Getmodulebaseaddress
	//uintptr_t moduleBase = GetModuleBaseAddress(procId, L"popcapgame1.exe");

	////Get Handle to Process
	//HANDLE hProcess = 0;
	//hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	////Resolve base address of the pointer chain
	//uintptr_t dynamicPtrBaseAddr = moduleBase + 0x329670;

	//std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;
	//std::cout << std::endl;
	////Resolve our ammo pointer chain
	//std::vector<unsigned int> sunOffsets = { 0x868, 0x5578 };
	//uintptr_t sunAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, sunOffsets);

	//int sunValue = 0;
	//ReadProcessMemory(hProcess, (BYTE*)sunAddr, &sunValue, sizeof(sunValue), nullptr);

	//std::cout << "sunAddr = " << "0x" << std::hex << sunAddr << " value = "<< std::dec << sunValue << std::endl;

	////Read Ammo value
	////int ammoValue = 0;

	////ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	////std::cout << "Curent ammo = " << std::dec << ammoValue << std::endl;

	//////Write to it
	////int newAmmo = 1337;
	////WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	//////Read out again
	////ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);

	////std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

	//getchar();

	//return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
