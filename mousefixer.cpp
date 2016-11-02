#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

/*Mouse sensitivity fixer for gta_sa.exe*/
using namespace std;

int main()
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hProcess;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, "gta_sa.exe") == 0)
            {  
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
            }
        }
    }
    float value;
    DWORD addr1 = 0xB6EC1C;
    DWORD addr2 = 0xB6EC1C-4;

	ReadProcessMemory(hProcess, (void*)addr1, &value, sizeof(value), 0);
	cout << "Sensitivity value is = " << value << endl;
	value = value*9/16;
	WriteProcessMemory(hProcess, (void*)addr2, &value, sizeof(value), 0);
	cout << "Written value to memory by your input = " << value << endl;
    CloseHandle(snapshot);
    cout << "Press 1 to repeat" << endl;
    int x;
    cin >> x;
    if(x==1)
    {
    	main();
    }
    else return 0;
}

