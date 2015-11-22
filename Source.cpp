#include <afxwin.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "accctrl.h"
#include "aclapi.h"
#include "MyDLL2.h"
#pragma comment (lib,"MyDLL2.lib")


class CMyMainWnd : public CFrameWnd {
public:
    CMyMainWnd() { // конструктор
        Create(NULL, L"My title");

    }
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();

};


BEGIN_MESSAGE_MAP(CMyMainWnd, CFrameWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()



class CMyApp : public CWinApp {
public:
    CMyApp() {}; // конструктор
    virtual BOOL InitInstance() {
        m_pMainWnd = new CMyMainWnd();
        m_pMainWnd->ShowWindow(SW_SHOW);
        return TRUE;
    }
};

void CMyMainWnd::OnPaint() {
    LPWSTR dirName = L"D:\\";
 
    CPaintDC* pDC = new CPaintDC(this);
    ULONGLONG i =  MySpace(L"D:\\");

    CString str;
    str.Format(L"Static = %u bytes", i);
    pDC->TextOutW(1, 1, str, str.GetLength());

    //////////dynamic
    HINSTANCE hDllInstance = LoadLibraryEx(L"MyDLL2.dll", 0, DONT_RESOLVE_DLL_REFERENCES);
    typedef ULONGLONG(*functionDll)(LPWSTR);
    functionDll fpFunction = (functionDll)GetProcAddress(hDllInstance, "MySpace");
    i = fpFunction(L"D:\\");
    str.Format(L"Dynamic is %u bytes", i);
    pDC->TextOutW(1, 50, str, str.GetLength());
    FreeLibrary(hDllInstance);
    //////////
}

CMyApp theApp;