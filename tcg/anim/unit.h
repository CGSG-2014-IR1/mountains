/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit.h
 * PURPOSE     : Computational geometry project.
 *               Unit class declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __unit_h_
#define __unit_h_

#include "../def.h"

#include <vector>

/* Computational geometry project namespace */
namespace tcg
{
  /* Unit class */
  class unit
  {
  public:
    anim *Ani; // Animation.

    /* Class constructor.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     */
    unit( anim *Ani );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    virtual ~unit( VOID );

    /* Response unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Response( VOID );

    /* Render unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Render( VOID );
  }; /* End of 'unit' class */

  /* Unit manager class */
  class unit_manager
  {
  private:
    std::vector<unit *> Units;

  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    unit_manager( VOID );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~unit_manager( VOID );

    /* Add unit function.
     * ARGUMENTS:
     *   - unit:
     *       unit *Unit;
     * RETURNS: None.
     */
    VOID AddUnit( unit *Uni );

    /* Response all units function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID );

    /* Render all units function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );
  }; /* End of 'unit_manager' class */
} /* end of 'tcg' namespace */

#endif /* __unit_h_ */

/* END OF 'unit.h' FILE */
