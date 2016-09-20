/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : computational_geometry.cpp
 * PURPOSE     : Computational geometry project.
 *               Computational geometry support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 24.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "computational_geometry.h"

/* Define vectors rotation.
 * ARGUMENTS:
 *   - vectors:
 *       const vec &a, &b;
 * RETURNS:
 *   (INT) 1 if left, -1 if right, 0 otherwise.
 */
INT tcg::math::Rotation( const vec &a, const vec &b )
{
  if (fabs(b.X * a.Z - a.X * b.Z) < tsg::Threshold)
    return 0;
  if (b.X * a.Z - a.X * b.Z > 0)
    return 1;
  return -1;
} /* End of 'tcg::math::Rotation' function */

/* END OF 'computational_geometry.cpp' FILE */
