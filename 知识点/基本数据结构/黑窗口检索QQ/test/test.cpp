// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "test.h"
#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

#include <iostream>
//�Ա����ݣ��ҵ���ͬ�ֽڼ���ƫ��  
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
	//����QQ��ʹ��Unicode�ַ����ģ���������ʹ��wchar_t����  
	static wchar_t QQDATA[] = L"Msg2.0.db";   
	

	//�򿪽���  
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, 0, dwProcessId);  

	int nMemLen = 28, nMemStart;  
	void *pMemAddress = NULL;  
	BYTE *bMemBuffer;  

	MEMORY_BASIC_INFORMATION mbi;  
	memset(&mbi, 0, sizeof(MEMORY_BASIC_INFORMATION));  

	wchar_t szQQnumber[15];  
	szQQnumber[0] = 0;  

	//Ѱ�ҽ��̿ռ�  
	while (VirtualQueryEx(hProcess, pMemAddress, &mbi, nMemLen) != 0)  
	{  
		if (mbi.Type == MEM_PRIVATE && mbi.Protect == PAGE_READWRITE)  
		{  
			//�����㹻���ڴ�ռ䣬�������  
			bMemBuffer = new BYTE[mbi.RegionSize + 1];  
			bMemBuffer[mbi.RegionSize] = 0;  

			if (ReadProcessMemory(hProcess, pMemAddress, bMemBuffer, mbi.RegionSize, NULL))  
			{  
				//����Ѱ�ҵ�ǰ�ڴ�ռ����Ƿ����Msg2.0.db  
				nMemStart = GetInBuffer(bMemBuffer, mbi.RegionSize, QQDATA, sizeof(QQDATA));  

				if (nMemStart != -1)  
				{  
					//��ǰ��һ��λ�ã���Ϊ·���� ..\[QQ��]\Msg2.0.db  

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

			//���ٸոշ�����ڴ�ռ�  
			delete[] bMemBuffer;  

		}  
		pMemAddress = (void *)((ULONG)pMemAddress + mbi.RegionSize);  
	}  

	CloseHandle(hProcess);  
}  

void FindQQ()  
{  
	DWORD dwProcessId = 0;  
	//���̿���~  
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  

	PROCESSENTRY32 pl;  
	pl.dwSize=sizeof(PROCESSENTRY32);  


	bool bmore=Process32First(Snapshot, &pl);  
	while(bmore)  
	{  

		if(lstrcmpi(pl.szExeFile, _T("QQ.exe")) == 0)  
		{  
			//��ȡQQ��  
			ReadQQ(pl.th32ProcessID);  
			//dwProcessId = pl.th32ProcessID;  
			//ѭ������ȡ�������е�¼��QQ�š�  
			//break;    ����ѭ��  
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
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{

			FindQQ();  
			system("pause");
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
