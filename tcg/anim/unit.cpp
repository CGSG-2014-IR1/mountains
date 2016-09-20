/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit.h
 * PURPOSE     : Computational geometry project.
 *               Unit class module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 23.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cmath>
#include <cstdlib>

#include "animation.h"

#include "unit.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::unit::unit( anim *Ani ) : Ani(Ani)
{
} /* End of 'tcg::unit::unit' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::unit::~unit( VOID )
{
} /* End of 'tcg::unit::~unit' function */

/* Response unit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit::Response( VOID )
{
} /* End of 'tcg::unit::Response' function */

/* Render unit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit::Render( VOID )
{
} /* End of 'tcg::unit::Render' function */

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::unit_manager::unit_manager( VOID )
{
} /* End of 'tcg::unit_manager::unit_manager' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::unit_manager::~unit_manager( VOID )
{
  for (INT i = 0; i < Units.size(); i++)
    delete Units[i];
} /* End of 'tcg::unit_manager::~unit_manager' function */

/* Add unit function.
 * ARGUMENTS:
 *   - unit:
 *       unit *Unit;
 * RETURNS: None.
 */
VOID tcg::unit_manager::AddUnit( unit *Uni )
{
  Units.push_back(Uni);
} /* End of 'tcg::unit_manager::AddUnit' function */

/* Response all units function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit_manager::Response( VOID )
{
  for (INT i = 0; i < Units.size(); i++)
    Units[i]->Response();
} /* End of 'tcg::unit_manager::Response' function */

/* Render all units function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit_manager::Render( VOID )
{
  for (INT i = 0; i < Units.size(); i++)
    Units[i]->Render();
} /* End of 'tcg::unit_manager::Render' function */

/* END OF 'unit.cpp' FILE */
