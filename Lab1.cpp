#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#define IDC_MAIN_BUTTON	101			
#define IDC_2ND_BUTTON  102
#define IDC_MAIN_EDIT	201			
HWND hEdit1;
HWND hEdit2;

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass,sizeof(WNDCLASSEX));
	wClass.cbClsExtra=NULL;
	wClass.style=CS_DBLCLKS;
	wClass.cbSize=sizeof(WNDCLASSEX);
	wClass.cbWndExtra=NULL;
	wClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wClass.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm=NULL;
	wClass.hInstance=hInst;
	wClass.lpfnWndProc=(WNDPROC)WinProc;
	wClass.lpszClassName=L"Window Class";
	wClass.lpszMenuName=NULL;
	wClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,L"Window class creation failed\n",L"Window Class Failed",MB_ICONERROR);
	}

	HWND hWnd=CreateWindowEx(NULL,L"Window Class",	L"Windows application",WS_OVERLAPPEDWINDOW,200,200,640,480,NULL,NULL,hInst,NULL);
	if(!hWnd)
	{
		int nResult=GetLastError();
		MessageBox(NULL,L"Window creation failed\n",L"Window Creation Failed",MB_ICONERROR);
	}

    ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc ;
	PAINTSTRUCT ps ;
	switch(msg)
	{
		case WM_GETMINMAXINFO:
            MINMAXINFO * mmiStruct;
            mmiStruct = (MINMAXINFO*)lParam;
 
            POINT ptPoint;
 
            ptPoint.x = 650;    //Minimum width of the window.
            ptPoint.y = 500;    //Minimum height of the window.
            mmiStruct->ptMinTrackSize = ptPoint;
 
            ptPoint.x = GetSystemMetrics(SM_CXMAXIMIZED);   //Maximum width of the window.
            ptPoint.y = GetSystemMetrics(SM_CYMAXIMIZED);   //Maximum height of the window.
            mmiStruct->ptMaxTrackSize = ptPoint;
        break;
		case WM_PAINT:
		{
			RECT rect ;
			hdc=BeginPaint(hWnd,&ps);
			GetClientRect(hWnd,&rect);
			SetTextColor(hdc, RGB(250,0,0));
			DrawText (hdc,TEXT("Hello, Windows!"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_BOTTOM|DT_NOCLIP) ;
			DrawText (hdc,TEXT("2nd Text element."),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_NOCLIP);
			EndPaint (hWnd, &ps) ;
			return 0;
		}
		break;
		case WM_CREATE:
		{
			// Create edit box
			hEdit1=CreateWindowEx(WS_EX_CLIENTEDGE,L"EDIT",L"",WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,10,10,600,100,hWnd,(HMENU)IDC_MAIN_EDIT,GetModuleHandle(NULL),NULL);
			hEdit2=CreateWindowEx(WS_EX_CLIENTEDGE,L"EDIT",L"nothing to do here...",WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,10,120,490,56,hWnd,(HMENU)IDC_MAIN_EDIT,GetModuleHandle(NULL),NULL);
			HGDIOBJ hfDefault=GetStockObject(17);
			SendMessage(hEdit1,WM_SETFONT,(WPARAM)hfDefault,MAKELPARAM(FALSE,0));
			SendMessage(hEdit1,WM_SETTEXT,NULL,(LPARAM)L"Insert text here...");

			// Create push button
			HWND hWndButton1=CreateWindowEx(NULL,L"BUTTON",L"OK",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,510,120,100,24,hWnd,(HMENU)IDC_MAIN_BUTTON,GetModuleHandle(NULL),NULL);
			HWND hWndButton2=CreateWindowEx(NULL,L"BUTTON",L"Cancel",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,510,150,100,24,hWnd,(HMENU)IDC_2ND_BUTTON,GetModuleHandle(NULL),NULL);
			SendMessage(hWndButton1,WM_SETFONT,(WPARAM)hfDefault,MAKELPARAM(FALSE,0));
			SendMessage(hWndButton2,WM_SETFONT,(WPARAM)hfDefault,MAKELPARAM(FALSE,0));
		}
		break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				case IDC_MAIN_BUTTON:
				{
					char buffer[256];
					SendMessage(hEdit1,WM_GETTEXT,sizeof(buffer)/sizeof(buffer[0]),reinterpret_cast<LPARAM>(buffer));
					MessageBox(NULL,(LPCWSTR)buffer,L"Information",MB_ICONINFORMATION);
				}
				break;

				case IDC_2ND_BUTTON:
				{
					MessageBox(NULL,L"Nothing happen",L"Information",MB_ICONINFORMATION);
				}
			}
			break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}