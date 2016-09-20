/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : cd_plane.cpp
 * PURPOSE     : Computational geometry project.
 *               Collision detection support module.
 *               Plane support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "def.h"

#include "cd.h"

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::cd::plane::plane( VOID ) : Normal(0, 1, 0), Distance(0)
{
} /* End of 'tcg::cd::plane::plane' function */

/* Class constructor.
 * ARGUMENTS:
 *   - new plane normal:
 *       const vec &Normal;
 *   - new distance to plane:
 *       const FLT Distance;
 */
tcg::cd::plane::plane( const vec &Normal, const FLT &Distance ) : Normal(Normal.Normalizing()), Distance(Distance)
{
} /* End of 'tcg::cd::plane::plane' function */

/* Class constructor.
 * ARGUMENTS:
 *   - three points on plane:
 *       const vec &P0, &P1, &P2;
 */
tcg::cd::plane::plane( const vec &P0, const vec &P1, const vec &P2 ) :
  Normal(((P1 - P0) % (P2 - P0)).Normalizing()), Distance(Normal & P0)
{
} /* End of 'tcg::cd::plane::plane' function */

/* Class constructor.
 * ARGUMENTS:
 *   - plane to copy:
 *       const plane &Plane;
 */
tcg::cd::plane::plane( const plane &Plane ) : Normal(Plane.Normal), Distance(Plane.Distance)
{
} /* End of 'tcg::cd::plane::plane' function */

/* Copy plane function.
 * ARGUMENTS:
 *   - plane to copy:
 *       const plane &Plane;
 * RETURNS:
 *   (plane &) self reference.
 */
tcg::cd::plane & tcg::cd::plane::operator=( const plane &Plane )
{
  Normal = Plane.Normal;
  Distance = Plane.Distance;

  return *this;
} /* End of 'tcg::cd::plane::operator=' function */

/* Intersect with ray function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &Ray;
 *   - compute normal flag:
 *       const BOOL &ComputeNormal;
 *   - compute point flag:
 *       const BOOL &ComputePoint;
 *   - transformation matrix:
 *       const trans &Trans;
 * RETURNS:
 *   (collision) collision information.
 */
tcg::cd::collision tcg::cd::plane::Intersect( const ray &Ray, const BOOL &ComputeNormal, const BOOL &ComputePoint, const trans &Trans ) const
{
  /* Transform ray */
  ray RayTrans(Trans.InvTransformPoint(Ray.Org), Trans.InvTransformVector(Ray.Dir));
  FLT ScaleCoef = 1.0 / !RayTrans.Dir;
  RayTrans.Dir.Normalize();

  /* No intersection */
  DBL nd = Normal & RayTrans.Dir;
  if (fabs(nd) < tsg::Threshold)
    return collision(0);
  FLT t = (Distance - (Normal & RayTrans.Org)) / nd;
  if (t < 0)
    return collision(0);

  /* Ray intersects plane */
  collision Collision(1, t * ScaleCoef);

  /* Compute normal and point */
  if (ComputeNormal)
    Collision.Intersection.Normal = Trans.TransformNormal(Normal);
  if (ComputePoint)
    Collision.Intersection.Location = Ray(t * ScaleCoef);

  return Collision;
} /* End of 'tcg::cd::plane::Intersect' function */

/* Class constructor.
 * ARGUMENTS:
 *   - plane location:
 *       const vec &Loc;
 *   - plane Du and Dv:
 *       const vec &Du, &Dv;
 */
tcg::cd::plane_finite::plane_finite( const vec &Loc, const vec &Du, const vec &Dv ) :
  Tr0(Loc, Loc + Du, Loc + Dv), Tr1(Loc + Du + Dv, Loc + Du, Loc + Dv)
{
} /* End of 'tcg::cd::plane_finite::plane_finite' function */

/* Class constructor.
 * ARGUMENTS:
 *   - plane to copy:
 *       const plane_finite &PlaneFinite;
 */
tcg::cd::plane_finite::plane_finite( const plane_finite &PlaneFinite ) : Tr0(Tr0), Tr1(Tr1)
{
} /* End of 'tcg::cd::plane_finite::plane_finite' function */

/* Copy plane function.
 * ARGUMENTS:
 *   - plane to copy:
 *       const plane_finite &PlaneFinite;
 * RETURNS:
 *   (plane_finite &) self reference.
 */
tcg::cd::plane_finite & tcg::cd::plane_finite::operator=( const plane_finite &PlaneFinite )
{
  Tr0 = PlaneFinite.Tr0;
  Tr1 = PlaneFinite.Tr1;

  return *this;
} /* End of 'tcg::cd::plane_finite::operator=' function */

/* Intersect with ray function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &Ray;
 *   - compute normal flag:
 *       const BOOL &ComputeNormal;
 *   - compute point flag:
 *       const BOOL &ComputePoint;
 *   - transformation matrix:
 *       const trans &Trans;
 * RETURNS:
 *   (collision) collision information.
 */
tcg::cd::collision tcg::cd::plane_finite::Intersect( const ray &Ray, const BOOL &ComputeNormal, const BOOL &ComputePoint, const trans &Trans ) const
{
  collision Collision = Tr0.Intersect(Ray, ComputeNormal, ComputePoint, Trans);
  if (Collision.IsCollide)
    return Collision;
  return Tr1.Intersect(Ray, ComputeNormal, ComputePoint, Trans);
} /* End of 'tcg::cd::plane_finite::Intersect' function */

/* END OF 'tvc_cd_plane.cpp' FILE */
