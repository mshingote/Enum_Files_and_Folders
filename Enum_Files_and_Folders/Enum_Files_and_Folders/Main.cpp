/*________________________________________
Programmer: Mayur Shingote
Date: 11/12/2016
Note:- Anyone can use this code.
If there is any bug please let me know. :)
Email:-mayur.shingote@yahoo.com
___________________________________*/
#include <windows.h>
#include <TCHAR.h>
#include <stdio.h>

void Enum(TCHAR root[0xFF])
{
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR GeneralPath[0xFF];
	TCHAR AgainFolder[0xFF];
	TCHAR FileFullPath[0xFF];
	
	_stprintf(GeneralPath, _T("%s\\*.*"), root);
	hFind = FindFirstFile(GeneralPath, &wfd);
	
	if(INVALID_HANDLE_VALUE==hFind)
		return;
	
	do
	{
		if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) //Checking Founded File Attribute is it File or Folder/Directory
		{
			if( !_tcscmp(wfd.cFileName, _T(".")) || !_tcscmp(wfd.cFileName, _T("..")) ) //if Founded directory is same(.) or parent(..) then ignore them
				continue;
			_stprintf(AgainFolder, _T("%s\\%s"), root, wfd.cFileName);
			Enum(AgainFolder); //Recursion because folder is inside another folder
		}
		else
		{
			_stprintf(FileFullPath, _T("%s\\%s"), root, wfd.cFileName); //  "Folder\\fileName.extension"
			_tprintf(_T("%s\n"),FileFullPath); 
		}

	}while(FindNextFile(hFind, &wfd));
	
	CloseHandle(hFind);
	hFind=INVALID_HANDLE_VALUE;
}
int main()
{
	TCHAR Folder[0xFF]=_T("c:\\windows");
	Enum(Folder);
	return 0;
}
