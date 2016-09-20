/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : cd_plane.cpp
 * PURPOSE     : Computational geometry project.
 *               Collision detection support module.
 *               Triangle support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../def.h"

#include "cd.h"

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::cd::triangle::triangle( VOID )
{
} /* End of 'tcg::cd::triangle::triangle' function */

/* Class constructor.
 * ARGUMENTS:
 *   - triangle points:
 *       const vec &P0, &P1, &P2;
 */
tcg::cd::triangle::triangle( const vec &P0, const vec &P1, const vec &P2 ) :
  P0(P0), P1(P1), P2(P2), Normal(((P1 - P0) % (P2 - P0)).Normalizing()),
  Du(((P2 - P0) * ((P1 - P0) & (P2 - P0)) - (P1 - P0) * ((P2 - P0) & (P2 - P0))) /
    ((DBL)((P1 - P0) & (P2 - P0)) * ((P1 - P0) & (P2 - P0)) - (DBL)((P1 - P0) & (P1 - P0)) * ((P2 - P0) & (P2 - P0)))),
  Dv(((P1 - P0) * ((P1 - P0) & (P2 - P0)) - (P2 - P0) * ((P1 - P0) & (P1 - P0))) /
    ((DBL)((P1 - P0) & (P2 - P0)) * ((P1 - P0) & (P2 - P0)) - (DBL)((P1 - P0) & (P1 - P0)) * ((P2 - P0) & (P2 - P0))))
{
} /* End of 'tcg::cd::triangle::triangle' function */

/* Class constructor.
 * ARGUMENTS:
 *   - triangle to copy:
 *       const triangle &Triangle;
 */
tcg::cd::triangle::triangle( const triangle &Triangle ) :
  P0(Triangle.P0), P1(Triangle.P1), P2(Triangle.P2), Normal(Triangle.Normal), Du(Triangle.Du), Dv(Triangle.Dv)
{
} /* End of 'tcg::cd::triangle::triangle' function */

/* Copy triangle function.
 * ARGUMENTS:
 *   - triangle to copy:
 *       const triangle &Triangle;
 * RETURNS:
 *   (triangle &) self reference.
 */
tcg::cd::triangle & tcg::cd::triangle::operator=( const triangle &Triangle )
{
  P0 = Triangle.P0, P1 = Triangle.P1, P2 = Triangle.P2, Normal = Triangle.Normal;
  Du = Triangle.Du, Dv = Triangle.Dv;

  return *this;
} /* End of 'tcg::cd::triangle::operator=' function */

/* Set triangle function.
 * ARGUMENTS:
 *   - triangle points:
 *       const vec &P0, &P1, &P2;
 * RETURNS: None.
 */
VOID tcg::cd::triangle::Set( const vec &P0, const vec &P1, const vec &P2 )
{
  this->P0 = P0, this->P1 = P1, this->P2 = P2;
  Normal = ((P1 - P0) % (P2 - P0)).Normalizing(),
  Du = ((P2 - P0) * ((P1 - P0) & (P2 - P0)) - (P1 - P0) * ((P2 - P0) & (P2 - P0))) /
    ((DBL)((P1 - P0) & (P2 - P0)) * ((P1 - P0) & (P2 - P0)) - (DBL)((P1 - P0) & (P1 - P0)) * ((P2 - P0) & (P2 - P0)));
  Dv = ((P1 - P0) * ((P1 - P0) & (P2 - P0)) - (P2 - P0) * ((P1 - P0) & (P1 - P0))) /
    ((DBL)((P1 - P0) & (P2 - P0)) * ((P1 - P0) & (P2 - P0)) - (DBL)((P1 - P0) & (P1 - P0)) * ((P2 - P0) & (P2 - P0)));
} /* End of 'tcg::cd::triangle::Set' function */

/* Intersection of triangle with ray function 
 * ARGUMENTS:
 *   - intersection ray:
 *       const ray &Ray;
 *   - compute normal flag:
 *       const BOOL &ComputeNormal;
 *   - compute point:
 *       const BOOL &ComputePoint;
 *   - transformation matrix:
 *       const trans &Trans;
 * RETURNS:
 *   (collision) collision information.
 */
tcg::cd::collision tcg::cd::triangle::Intersect( const ray &Ray, const BOOL &ComputeNormal, const BOOL &ComputePoint, const trans &Trans ) const
{
  /* Transform ray */
  ray RayTrans(Trans.InvTransformPoint(Ray.Org), Trans.InvTransformVector(Ray.Dir));
  FLT ScaleCoef = 1.0 / !RayTrans.Dir;
  RayTrans.Dir.Normalize();

  if (fabs(P0.X - P1.X) < tsg::Threshold && fabs(P0.Y - P1.Y) < tsg::Threshold && fabs(P0.Z - P1.Z) < tsg::Threshold ||
      fabs(P0.X - P2.X) < tsg::Threshold && fabs(P0.Y - P2.Y) < tsg::Threshold && fabs(P0.Z - P2.Z) < tsg::Threshold ||
      fabs(P1.X - P2.X) < tsg::Threshold && fabs(P1.Y - P2.Y) < tsg::Threshold && fabs(P1.Z - P2.Z) < tsg::Threshold)
    return collision(0);

  DBL nd = Normal & RayTrans.Dir;
  if (fabs(nd) < tsg::Threshold)
    return collision(0);

  DBL t = ((P0 & Normal) - (Normal & RayTrans.Org)) / nd;
  if (t < 0)
    return collision(0);

  vec P = RayTrans(t);
  DBL
    u = (P & Du) - (P0 & Du),
    v = (P & Dv) - (P0 & Dv);

  if (u < 0 || v < 0 || (u + v) > 1)
    return collision(0);

  collision Collision(1, t * ScaleCoef);

  if (ComputePoint)
    Collision.Intersection.Location = Ray(t * ScaleCoef);
  if (ComputeNormal)
    Collision.Intersection.Normal = Trans.TransformNormal(Normal);

  return Collision;
} /* End of 'tcg::cd::triangle::Intersect' function */

/* END OF 'tvc_cd_triangle.cpp' FILE */
