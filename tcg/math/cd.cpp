/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : cd.cpp
 * PURPOSE     : Computational geometry project.
 *               Collision detection support module.
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
tcg::cd::collision::point::point( VOID ) : Location(vec(0)), Normal(vec(0))
{
} /* End of 'tcg::cd::collision::point::point' function */

/* Class constructor.
 * ARGUMENTS:
 *   - point coordinates:
 *       const vec &Location;
 *   - normal:
 *       const vec &Normal;
 */
tcg::cd::collision::point::point( const vec &Location, const vec &Normal ) : Location(Location), Normal(Normal.Normalizing())
{
} /* End of 'tcg::cd::collision::point::point' function */

/* Class constructor.
 * ARGUMENTS:
 *   - point:
 *       const point &Point;
 */
tcg::cd::collision::point::point( const point &Point ) : Location(Point.Location), Normal(Point.Normal)
{
} /* End of 'tcg::cd::collision::point::point' function */

/* Copy point function.
 * ARGUMENTS:
 *   - point to copy:
 *       const point &Point;
 * RETURNS:
 *   (point &) self reference.
 */
tcg::cd::collision::point & tcg::cd::collision::point::operator=( const point &Point )
{
  Location = Point.Location;
  Normal = Point.Normal;

  return *this;
} /* End of 'tcg::cd::collision::point::operator=' function */

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::cd::collision::collision( VOID ) : IsCollide(0), T(0)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - number of collisions:
 *       const INT &IsCollide;
 */
tcg::cd::collision::collision( const INT &IsCollide ) : IsCollide(IsCollide), T(0)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - number of collisions:
 *       const INT &IsCollide;
 *   - t value:
 *       const FLT &T;
 */
tcg::cd::collision::collision( const INT &IsCollide, const FLT &T ) : IsCollide(IsCollide), T(T)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - coordinates of intersection:
 *       const vec &Loc;
 */
tcg::cd::collision::collision( const vec &Location ) : IsCollide(1), Intersection(Location), T(0)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - coordinates of intersection:
 *       const vec &Loc;
 *   - t value:
 *       const FLT &T;
 */
tcg::cd::collision::collision( const vec &Location, const FLT &T ) : IsCollide(1), Intersection(Location), T(T)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - intersection point:
 *       const point &Point;
 *   - t value:
 *       const FLT &T;
 */
tcg::cd::collision::collision( const point &Point, const FLT &T ) : IsCollide(1), Intersection(Point), T(T)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Class constructor.
 * ARGUMENTS:
 *   - collision to copy:
 *       const collision &Collision;
 */
tcg::cd::collision::collision( const collision &Collision ) :
  T(Collision.T), IsCollide(Collision.IsCollide),
  Intersection(Collision.Intersection), Nearest(Collision.Nearest), Farthest(Collision.Farthest)
{
} /* End of 'tcg::cd::collision::collision' function */

/* Copy collision function.
 * ARGUMENTS:
 *   - collision to copy:
 *       const collision &Collision;
 * RETURNS:
 *   (collision &) self reference.
 */
tcg::cd::collision & tcg::cd::collision::operator=( const collision &Collision )
{
  IsCollide = Collision.IsCollide;
  if (IsCollide)
  {
    Intersection = Collision.Intersection;
    Nearest = Collision.Nearest;
    Farthest = Collision.Farthest;
    T = Collision.T;
  }
  return *this;
} /* End of 'tcg::cd::collision::operator=' function */

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
tcg::cd::collision tcg::cd::shape::Intersect( const ray &Ray, const BOOL &ComputeNormal, const BOOL &ComputePoint, const trans &Trans ) const
{
  return collision(0);
} /* End of 'tcg::cd::shape::Intersect' function */

/* Collide with another shape function.
  * ARGUMENTS:
  *   - shape to intersect with:
  *       shape *Shape;
  * RETURNS:
  *   (BOOL) TRUE if collide, FALSE otherwise.
  */
BOOL tcg::cd::shape::Collide( const shape &Shape ) const
{
  return FALSE;
} /* End of 'tcg::cd::shape::Collide' function */

/* END OF 'tvc_cd.cpp' FILE */
