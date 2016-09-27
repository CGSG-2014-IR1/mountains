/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : WIN.CPP
 * PURPOSE     : Simple animation system.
 *               Window class implementation module.
 * PROGRAMMER  : MM5.
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
 */
tcg::win::win( HINSTANCE hInst ) :
    IsInit(FALSE), hWnd(NULL), hInstance(hInst),
    Width(0), Height(0), IsActive(FALSE), IsFullScreen(FALSE),
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
  wc.lpszMenuName = (CHAR *)IDR_MENU1;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = MainWndClassName;
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }

  /* Window creation */
  hWnd = CreateWindow(MainWndClassName,
    "Landscape Construction",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    //1920, 0, 1000, 700,
    NULL, NULL, hInstance, (VOID *)this);
  if (hWnd == NULL)
  {
    MessageBox(NULL, "Error window creation", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }
  /* Show and update window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Send initialization timer message */
  PostMessage(hWnd, WM_TIMER, (WPARAM)InitializationTimer, 0);
} /* End of 'tcg::win::win' function */

/* Class destructor */
tcg::win::~win( VOID )
{
} /* End of 'tcg::win::~win' function */

/* Windowed application running function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT tcg::win::Run( VOID )
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
} /* End of 'tcg::win::Run' function */

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
LRESULT CALLBACK tcg::win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (Msg)
  {
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);
    /* Store window handle */
    ((win *)((CREATESTRUCT *)lParam)->lpCreateParams)->hWnd = hWnd;
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
    {
      switch (Msg)
      {
      case WM_CREATE:
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
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
        Win->OnPaint();
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        Win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
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
} /* End of 'tcg::win::WinFunc' function */

/* System exit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::win::DoExit( VOID )
{
  PostMessage(hWnd, WM_CLOSE, 0, 0);
} /* End of 'tcg::win::DoExit' function */

/* Enable/disable full screen window mode function.
 * ARGUMENTS:
 *   - fullscreen enable flag:
 *       BOOL IsToGoToFullScreen;
 * RETURNS: None.
 */
VOID tcg::win::SetFullScreen( BOOL IsToGoToFullScreen )
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
    /* for single monitor:
    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    */
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
} /* End of 'tcg::win::SetFullScreen' function */

/* END OF 'WIN.CPP' FILE */
