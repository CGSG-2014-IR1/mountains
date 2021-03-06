/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : window.cpp
 * PURPOSE     : Simple animation system.
 *               Window class implementation module.
 * PROGRAMMER  : MM5,
 *               IR1.
 * LAST UPDATE : 23.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstdlib>

#include "window.h"
#include "../resource.h"

/* Class constructor.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInst;
 *   - window class name:
 *       const char *ClassName = "MyWindowClass";
 *   - window caption:
 *       const char *Caption = "Window";
 *   - flag if window should have built-in controls:
 *       bool Control = true;
 *   - window menu ID:
 *       UINT Menu = 0;
 *   - flag if window shoukd be visible on start:
 *       bool Show = false;
 *   - window sizes:
 *       int W = CW_USEDEFAULT, H = CW_USEDEFAULT
 */
tcg::window::window( HINSTANCE hInst, const char *ClassName,
                     const char *Caption,
                     bool Control,
                     UINT Menu, bool Show,
                     int W, int H ) :
    IsInit(FALSE), hWnd(NULL), hInstance(hInst),
    Width(0), Height(0), IsActive(Show), IsFullScreen(FALSE),
    MouseWheel(0)
{
  /* Fill and register window class */
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(VOID *);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIconSm = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON,
    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
  wc.hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON,
    GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
  wc.lpszMenuName = (CHAR *)Menu;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = ClassName;
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }

  /* Window creation */
  hWnd = CreateWindow(ClassName,
    Caption,
    Control ? WS_OVERLAPPEDWINDOW : WS_OVERLAPPED,
    CW_USEDEFAULT, CW_USEDEFAULT, W, H,
    NULL, NULL, hInstance, (VOID *)this);
  if (hWnd == NULL)
  {
    MessageBox(NULL, "Error window creation", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }
  /* Show and update window */
  if (Show)
    ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Send initialization timer message */
  PostMessage(hWnd, WM_TIMER, (WPARAM)InitializationTimer, 0);
} /* End of 'tcg::window::window' function */

/* Windowed application running function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT tcg::window::Run( VOID )
{
  MSG msg;

  /* Message loop */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      if (IsInit)
        Idle();
  }
  return msg.wParam;
} /* End of 'tcg::window::Run' function */

/* Window message handle function (CALLBACK version).
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier (see WM_***):
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK tcg::window::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  window *Win;

  switch (Msg)
  {
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);
    /* Store window handle */
    ((window *)((CREATESTRUCT *)lParam)->lpCreateParams)->hWnd = hWnd;
  default:
    Win = (window *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
    {
      switch (Msg)
      {
      case WM_CREATE:
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_CLOSE:
      case WM_DESTROY:
        Win->OnDestroy();
        return 0;
      case WM_SIZE:
        Win->OnSize((UINT)wParam, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam));
        return 0;
      case WM_ACTIVATE:
        Win->OnActivate((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBkgnd((HDC)wParam);
      case WM_PAINT:
      case WM_TIMER:
        Win->OnPaint();
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        Win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        Win->OnKeyDown(wParam);
        return 0;
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        Win->OnButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (INT)(SHORT)HIWORD(wParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_COMMAND:
        UINT m = LOWORD(wParam);
        if (m == ID_FILE_EXIT)
          Win->OnDestroy();
        else
          for (auto &i : Win->MenuCallbacks)
            if (i.first == m)
              i.second();
        return 0;
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'tcg::window::WinFunc' function */

/* System exit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::window::DoExit( VOID )
{
  PostMessage(hWnd, WM_CLOSE, 0, 0);
} /* End of 'tcg::window::DoExit' function */

/* Enable/disable full screen window mode function.
 * ARGUMENTS:
 *   - fullscreen enable flag:
 *       BOOL IsToGoToFullScreen;
 * RETURNS: None.
 */
VOID tcg::window::SetFullScreen( BOOL IsToGoToFullScreen )
{
  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* save old window size */
    GetWindowRect(hWnd, &SaveRect);

    /* determine monitor with window */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* obtain monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* go to full screen mode */
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    /* restore window size */
    SetWindowPos(hWnd, HWND_TOPMOST,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'tcg::window::SetFullScreen' function */

/* END OF 'window.cpp' FILE */
