/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : window_value.h
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

#ifndef __window_value_h_
#define __window_value_h_

#include "../def.h"
#include "../resource.h"
#include "window.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Main window class declaration */
  class window_value : private window
  {
  private:
    callback OnUpdate;  // on update callback
  public:
    double Value;

    /* Class constructor.
     * ARGUMENTS:
     *   - application instance handle:
     *       HINSTANCE hInst;
     */
    window_value( const char *ValueName, const callback &OnUpdate,
                  double InitValue = 0 ) :
      OnUpdate(OnUpdate),
      window(GetModuleHandle(NULL),
        (std::string(ValueName) + "ValueWindowClass").c_str(), ValueName, false, 0, false, 70, 70),
      Value(InitValue)
    {
      SetTimer(hWnd, InitializationTimer, 1000 / 30, NULL);
    } /* End of 'window_value' constructor */

    /* Pop up function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void PopUp( void )
    {
      Show();
    } /* End of 'PopUp' function */

  private:
    double Num = 10;  // numerator
    int Pos = 0;      // caret position
    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - pressed key:
     *       UINT Key.
     * RETURNS: None.
     */
    VOID OnKeyDown( UINT Key )
    {
      if (Key >= '0' && Key <= '9')
      {
        Value = (int)(Value * (0.1 / Num)) / (0.1 / Num) + (Key - '0') * Num;
        if (Num > 0.01)
          Num /= 10, Pos++;
      }
      else if (Key == VK_BACK)
      {
        if (Num < 10)
          Num *= 10, Pos--;
      }
      else if (Key == VK_RETURN)
        OnUpdate();
    } /* End of 'OnKeyDown' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnPaint( VOID )
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      Erase(hdc);
      RECT rect;
      GetClientRect(hWnd, &rect);
      SetTextColor(hdc, 0x000000);
      HFONT hfnt = CreateFont(18, 9, 0, 0, 0, 0, 0, 0,
                              DEFAULT_CHARSET,
                              0, 0, 0, 0, "Consolas");
      SelectObject(hdc, hfnt);
      char buf[6]{'0', '0', '.', '0', '0', 0};
      sprintf(buf, "%05.2lf", Value);
      DrawText(hdc, buf, 5, &rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
      SetTextColor(hdc, 0x0000ff);
      rect.left += 9 * (Pos + (Pos < 2 ? 0 : 1));
      sprintf(buf, "%d", (int)(Value * (1.0 / Num)) % 10);
      DrawText(hdc, buf, 1, &rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
      EndPaint(hWnd, &ps);
    } /* End of 'OnPaint' function */

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID )
    {
      Hide();
    } /* End of 'tcg::window_value::OnDestroy' function */
  }; /* End of 'win' class */
} /* end of 'tcg' namespace */

#endif /* __window_h_ */

/* END OF 'window.h' FILE */
