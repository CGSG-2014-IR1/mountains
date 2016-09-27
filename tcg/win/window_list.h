/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : window_list.h
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

#ifndef __window_list_h_
#define __window_list_h_

#include "../def.h"
#include "../resource.h"
#include "window.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Main window_list class declaration */
  class window_list : private window
  {
  private:
    callback OnUpdate, OnClose;  // on update callback
  public:
    std::vector<std::pair<std::string, float *>> Value;

    /* Class constructor.
     * ARGUMENTS:
     *   - application instance handle:
     *       HINSTANCE hInst;
     */
    window_list( const char *ValueName, const callback &OnUpdate, const callback &OnClose ) :
      OnUpdate(OnUpdate), OnClose(OnClose),
      window(GetModuleHandle(NULL),
        (std::string(ValueName) + "ValueWindowClass").c_str(), ValueName, false, 0, false, 400, 700)
    {
      SetTimer(hWnd, InitializationTimer, 1000 / 30, NULL);
    } /* End of 'window_list' constructor */

    void Push( const char * Name, float *Ptr )
    {
      Value.push_back(std::pair<std::string, float *>(Name, Ptr));
    }

    /* Pop up function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void PopUp( void )
    {
      Show();
    } /* End of 'PopUp' function */

  private:
    double Num = 10;         // numerator
    int PosX = 0, PosY = 0;  // caret position
    /* WM_KEYDOWN window_list message handle function.
     * ARGUMENTS:
     *   - pressed key:
     *       UINT Key.
     * RETURNS: None.
     */
    VOID OnKeyDown( UINT Key )
    {
      if (Key >= '0' && Key <= '9')
      {
        *Value[PosY].second =
          (int)(*Value[PosY].second * (0.1 / Num)) / (0.1 / Num) + (Key - '0') * Num;
        if (Num > 0.01)
          Num /= 10, PosX++;
      }
      else if (Key == VK_UP)
      {
        if (PosY > 0)
          PosY--;
      }
      else if (Key == VK_DOWN)
      {
        if (PosY < Value.size() - 1)
          PosY++;
      }
      else if (Key == VK_LEFT)
      {
        if (Num < 10)
          Num *= 10, PosX--;
      }
      else if (Key == VK_RIGHT)
      {
        if (Num > 0.01)
          Num /= 10, PosX++;
      }
      else if (Key == VK_RETURN)
        OnUpdate();
    } /* End of 'OnKeyDown' function */

    /* WM_PAINT window_list message handle function.
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
      char buf[6]{'0', '0', '.', '0', '0', 0}, buf3[26];
      SetTextColor(hdc, 0x000000);
      HBRUSH brush = CreateSolidBrush(0x77aa00);
      HPEN pen = CreatePen(0, 1, 0x77aa00);
      SelectObject(hdc, brush);
      SelectObject(hdc, pen);
      SetBkMode(hdc, TRANSPARENT);

      for (int i = 0, size = Value.size(); i < size; i++)
      {
        sprintf(buf, "%05.2f", *Value[i].second);
        memset(buf3, 0, 26);
        strcpy(buf3, Value[i].first.c_str());
        DrawText(hdc, buf3, strlen(buf3), &rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
        rect.left += 9 * 26;
        if (i == PosY)
        {
          rect.left += 9 * (PosX + (PosX < 2 ? 0 : 1));
          Rectangle(hdc, rect.left, rect.top, rect.left + 9, rect.top + 18);
          rect.left -= 9 * (PosX + (PosX < 2 ? 0 : 1));
        }
        DrawText(hdc, buf, 5, &rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
        rect.top += 18;
        rect.left -= 9 * 26;
      }
      EndPaint(hWnd, &ps);
    } /* End of 'OnPaint' function */

    /* WM_DESTROY window_list message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID )
    {
      OnClose();
      Hide();
    } /* End of 'tcg::window_list::OnDestroy' function */
  }; /* End of 'win' class */
} /* end of 'tcg' namespace */

#endif /* __window_h_ */

/* END OF 'window_list.h' FILE */
