#include <iostream>
#include <Windows.h>
using namespace std;
LPCSTR windname = "practice.txt - Notepad";
DWORD baseAddr = 0x1B360A6166C;
int rv = 0;
int wv = 1337;
HWND hWnd = NULL;
HANDLE hProc = NULL;
DWORD pid = NULL;
int main()
{ 
	hWnd = FindWindowA(NULL, windname);
	if (hWnd)
	{
		GetWindowThreadProcessId(hWnd, &pid);
		if (pid != NULL)
		{
			hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if (hProc)
			{
				while (1)
				{
					if (GetAsyncKeyState(VK_F12))
					{
						ReadProcessMemory(hProc, (BYTE*)baseAddr, &rv, sizeof(rv), nullptr);
						WriteProcessMemory(hProc, (BYTE*)baseAddr, &wv, sizeof(wv), nullptr);
						WriteProcessMemory(hProc, (BYTE*)rv, &wv, sizeof(wv), nullptr);
						MessageBox(NULL, L"Value has been changed", L"Success", NULL);
					}

				}

			}
			else
				cout << "Could not get access to process\n" << endl;
		}
		else
			cout << "Could not get default process ID\n" << endl;
	}
	else
		cout << "Could not find window\n" << endl;
}