/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : animation.h
 * PURPOSE     : Computational geometry project.
 *               Animation class declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __animation_h_
#define __animation_h_

#include <vector>

#include "../win/window.h"
#include "timer.h"
#include "input.h"
#include "render/render.h"
#include "unit.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Animation system class declaration */
  class anim : public win, public render, public timer, public input, public unit_manager
  {
  private:
  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - application instance handle:
     *       HINSTANCE hInst;
     */
    anim( HINSTANCE hInstance = GetModuleHandle(NULL) );

    /* Class destructor */
    ~anim( VOID );

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );

    /* Add unit to animation system function.
     * ARGUMENTS:
     *   - unit to be add:
     *       unit *Uni;
     * RETURNS:
     *   (anim &) self reference.
     */
    anim & operator<<( unit *Uni )
    {
      unit_manager::AddUnit(Uni);
      return *this;
    } /* End of 'operator<<' function */

    /* New menu callback add function.
     * ARGUMENTS:
     *   - callback to add:
     *       const callback &Callback.
     * RETURNS:
     *   (anim &) self-reference.
     */
    anim & operator<<( const callback &Callback )
    {
      win::operator<<(Callback);
      return *this;
    } /* End of 'operator<<' function */

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC );

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC );

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    VOID Activate( BOOL IsActive );
    
    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID );

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID );
  }; /* End of 'anim' class */
} /* end of 'tcg' namespace */

#endif /* __animation_h_ */

/* END OF 'animation.h' FILE */
