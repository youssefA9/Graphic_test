#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#define WM_LBUTTONUP
#include <tchar.h>
#include <windows.h>
#include<iostream>
#include <vector>
using namespace std;
#include<math.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Code::Blocks Template Windows App"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        544,                 /* The programs width */
        375,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

//Vector to Store the Radiuses of the circles

void draweight(HDC hdc, int x, int y, int xc, int yc,int rgb) {
    if (rgb == 1) {
        SetPixel(hdc, xc + x, yc + y, RGB(128, 0, 0));
        SetPixel(hdc, xc - x, yc + y, RGB(0, 0, 0));
        SetPixel(hdc, xc + x, yc - y, RGB(0, 128, 0));
        SetPixel(hdc, xc - x, yc - y, RGB(0, 0, 0));

        SetPixel(hdc, xc - y, yc + x, RGB(0, 0, 0));
        SetPixel(hdc, xc + y, yc - x, RGB(0, 0, 128));
        SetPixel(hdc, xc + y, yc + x, RGB(128, 0, 0));
        SetPixel(hdc, xc - y, yc - x, RGB(128, 0, 0));
    
    
    }
    else {
        SetPixel(hdc, xc + x, yc + y, RGB(0, 0, 0));
        SetPixel(hdc, xc - x, yc + y, RGB(0, 0, 0));
        SetPixel(hdc, xc + x, yc - y, RGB(0, 0, 0));
        SetPixel(hdc, xc - x, yc - y, RGB(0, 0, 0));

        SetPixel(hdc, xc - y, yc + x, RGB(0, 0, 0));
        SetPixel(hdc, xc + y, yc - x, RGB(0, 0, 0));
        SetPixel(hdc, xc + y, yc + x, RGB(0, 0, 0));
        SetPixel(hdc, xc - y, yc - x, RGB(0, 0, 0));
    }
}
void midpoint(HDC hdc, int xc, int yc, int r,int RGB) {
    int x = 0;
    int y = r;
    double d = 1 - r;
    while (x < y) {
        if (d <= 0) {
            d = d + 2 * x + 3;
            x++;
        }
        else {
            d = d + 2 * (x - y) + 5;
            x++;
            y--;
        }
        draweight(hdc, x, y, xc, yc,RGB);
    }
}

void parametricline(HDC hdc, int x1, int y1, int x2, int y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    for (double t = 0; t < 1; t += 0.001) {
        int x = x1 + (dx * t);
        int y = y1 + (dy * t);
        SetPixel(hdc, x, y, RGB(1, 1, 1));
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
int x1, x2, y, y2;
int rr, x_c, y_c, x_2, y_2;
vector<int>radius;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int smallestR = 0;
    int largestR = 0;
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONUP:
        x_c = LOWORD(lParam);
        y_c = HIWORD(lParam);
        x1 = LOWORD(lParam);
        y = HIWORD(lParam);
        radius.clear();
        break;
    case WM_RBUTTONUP:
        x_2 = LOWORD(lParam);
        y_2 = HIWORD(lParam);
        x2 = LOWORD(lParam);
        y2 = HIWORD(lParam);
        rr = sqrt(pow((x_2 - x_c), 2) + pow((y_2 - y_c), 2));
        radius.push_back(rr);

        parametricline(hdc, x1, y, x2, y2);
        midpoint(hdc, x_c, y_c, rr,0);

        if (radius.size() > 1) {
            if (radius[radius.size() - 1] > radius[radius.size() - 2]) {
                smallestR = radius[radius.size() - 2];
                largestR = radius[radius.size() - 1];
            }
            else {
                largestR = radius[radius.size() - 2];
                smallestR = radius[radius.size() - 1];
            }
            for (int i = smallestR; i < largestR; i++) {
                midpoint(hdc, x_c, y_c, i, 1);
            }
            radius.erase(radius.begin());
        }
        parametricline(hdc, x1, y, x2, y2);
        
        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
