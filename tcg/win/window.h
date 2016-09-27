/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : window.h
 * PURPOSE     : Simple animation system.
 *               Window class declaration module.
 * PROGRAMMER  : MM5,
 *               IR1.
 * LAST UPDATE : 24.09.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __window_h_
#define __window_h_

#include "../def.h"

#include <vector>
#include <functional>

/* Computational geometry project namespace */
namespace tcg
{
  typedef std::function<void(void)> callback;

  /* Main window class declaration */
  class window
  {
  private:
    /* Save rectangle for full screen mode */
    RECT SaveRect;

  protected:
    /* Initialization timer identifier */
    static const INT InitializationTimer = 303030;

    /* Initialization flag */
    bool IsInit;

    /* Window data */
    HWND hWnd;                                             // Window handle
    HINSTANCE hInstance;                                   // Application instance handle
    INT Width, Height;                                     // Window size
    bool IsActive;                                         // Active flag
    bool IsFullScreen;                                     // Full screen flag
    std::vector<std::pair<UINT, callback>> MenuCallbacks;  // Winapi menu custom callbacks

  public:
    INT MouseWheel;           // Wheel relative rotate counter

  public:
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
    window( HINSTANCE hInst = GetModuleHandle(NULL),
            const char *ClassName = "MyWindowClass",
            const char *Caption = "Window",
            bool Control = true,
            UINT Menu = 0,
            bool Show = false,
            int W = CW_USEDEFAULT, int H = CW_USEDEFAULT );

    /* New menu callback add function.
     * ARGUMENTS:
     *   - callback to add:
     *       const callback &Callback.
     * RETURNS:
     *   (window &) self-reference.
     */
    window & operator<<( const std::pair<UINT, callback> &Callback )
    {
      MenuCallbacks.push_back(Callback);
      return *this;
    } /* End of 'operator<<' function */

    /* Windowed application running function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) Error level for operation system (0 for success).
     */
    INT Run( VOID );

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
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

    /* System exit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DoExit( VOID );

    /* Enable/disable full screen window mode function.
     * ARGUMENTS:
     *   - fullscreen enable flag:
     *       BOOL IsToGoToFullScreen;
     * RETURNS: None.
     */
    VOID SetFullScreen( BOOL IsToGoToFullScreen );

    /***
     * Cracked message handle functions
     ***/

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnDestroy( VOID );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnPaint( VOID );

    /* WM_ACTIVATE window message handle function.
     * ARGUMENTS:
     *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
     *       UINT Reason;
     *   - handle of active window:
     *       HWND hWndActDeact;
     *   - minimized flag:
     *       BOOL IsMinimized;
     * RETURNS: None.
     */
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );

    /* WM_*BUTTONDOWN window message handle function.
     * ARGUMENTS:
     *   - double click flag:
     *       BOOL IsDoubleClick;
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - pressed key:
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnKeyDown( UINT Keys );

    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys );

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel delta value (120 points per rotate):
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
      HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
      HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));

      /* Default action - draw white rectangle */
      Rectangle(hDC, 0, 0, Width, Height);
      SelectObject(hDC, hOldPen);
      SelectObject(hDC, hOldBrush);
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    virtual VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */
    
    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */

    /* Get screen width function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) screen width.
     */
    INT GetW( VOID )
    {
      return Width;
    } /* End of 'GetW' function */

    /* Get screen height function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) screen height.
     */
    INT GetH( VOID )
    {
      return Height;
    } /* End of 'GetH' function */

  public:
    /* Show window function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    inline void Show( void )
    {
      ShowWindow(hWnd, SW_SHOW);
    } /* End of 'Show' function */

    /* Hide window function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    inline void Hide( void )
    {
      ShowWindow(hWnd, SW_HIDE);
    } /* End of 'Hide' function */
  }; /* End of 'window' class */
} /* end of 'tcg' namespace */

#endif /* __window_h_ */

/* END OF 'window.h' FILE */
