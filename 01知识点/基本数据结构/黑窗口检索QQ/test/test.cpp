// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"
#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#include <iostream>
//对比数据，找到相同字节集的偏移  
int GetInBuffer(const void *pStart, int nLen, const void *pFindBuffer, int nfLen)  
{  
	for (int i = 0; i < nLen - nfLen; i++)  
	{  
		if (memcmp((void *)((ULONG)pStart + i), pFindBuffer, nfLen) == 0)  
		{  
			return i;  
		}  
	}  

	return -1;  
}  

void ReadQQ(DWORD dwProcessId)  
{  
	//由于QQ是使用Unicode字符集的，所以我们使用wchar_t类型  
	static wchar_t QQDATA[] = L"Msg2.0.db";   
	

	//打开进程  
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, 0, dwProcessId);  

	int nMemLen = 28, nMemStart;  
	void *pMemAddress = NULL;  
	BYTE *bMemBuffer;  

	MEMORY_BASIC_INFORMATION mbi;  
	memset(&mbi, 0, sizeof(MEMORY_BASIC_INFORMATION));  

	wchar_t szQQnumber[15];  
	szQQnumber[0] = 0;  

	//寻找进程空间  
	while (VirtualQueryEx(hProcess, pMemAddress, &mbi, nMemLen) != 0)  
	{  
		if (mbi.Type == MEM_PRIVATE && mbi.Protect == PAGE_READWRITE)  
		{  
			//分配足够的内存空间，存放数据  
			bMemBuffer = new BYTE[mbi.RegionSize + 1];  
			bMemBuffer[mbi.RegionSize] = 0;  

			if (ReadProcessMemory(hProcess, pMemAddress, bMemBuffer, mbi.RegionSize, NULL))  
			{  
				//尝试寻找当前内存空间中是否包含Msg2.0.db  
				nMemStart = GetInBuffer(bMemBuffer, mbi.RegionSize, QQDATA, sizeof(QQDATA));  

				if (nMemStart != -1)  
				{  
					//向前推一定位置，因为路径是 ..\[QQ号]\Msg2.0.db  

					wchar_t *pQQText = (wchar_t *)&bMemBuffer[nMemStart - 28];  
					wchar_t *pQQstart = wcsstr(pQQText, L"\\");  
					if (pQQstart)  
					{  
						pQQstart++;  
						wchar_t *pQQEnd = wcsstr(pQQstart, L"\\");  
						if (pQQEnd)  
						{  
							lstrcpynW(szQQnumber, pQQstart, pQQEnd - pQQstart + 1);  
							wprintf(L"%s\n", szQQnumber);  
						}  
					}  

					delete[] bMemBuffer;  
					break;  
				}  
			}  

			//销毁刚刚分配的内存空间  
			delete[] bMemBuffer;  

		}  
		pMemAddress = (void *)((ULONG)pMemAddress + mbi.RegionSize);  
	}  

	CloseHandle(hProcess);  
}  

void FindQQ()  
{  
	DWORD dwProcessId = 0;  
	//进程快照~  
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  

	PROCESSENTRY32 pl;  
	pl.dwSize=sizeof(PROCESSENTRY32);  


	bool bmore=Process32First(Snapshot, &pl);  
	while(bmore)  
	{  

		if(lstrcmpi(pl.szExeFile, _T("QQ.exe")) == 0)  
		{  
			//读取QQ号  
			ReadQQ(pl.th32ProcessID);  
			//dwProcessId = pl.th32ProcessID;  
			//循环，读取本地所有登录的QQ号。  
			//break;    跳出循环  
		}  
		bmore= Process32Next(Snapshot, &pl);  
	}  

	CloseHandle(Snapshot);  
	//  return dwProcessId;  
}  

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{

			FindQQ();  
			system("pause");
			// TODO: 在此处为应用程序的行为编写代码。
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
