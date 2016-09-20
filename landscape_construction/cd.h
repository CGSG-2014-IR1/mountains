/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : cd.h
 * PURPOSE     : Computational geometry project.
 *               Collision detection support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 14.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __tvc_cd_h_
#define __tvc_cd_h_

#include "def.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Collision detection namespace */
  namespace cd
  {
    /* Collision information class */
    class collision
    {
    public:
      /* Point class */
      class point
      {
      public:
        vec Location, Normal;   /* Coordinates and normal to point of intersection */

        /* Class constructor.
         * ARGUMENTS: None.
         */
        point( VOID );

        /* Class constructor.
         * ARGUMENTS:
         *   - point coordinates:
         *       const vec &Location;
         *   - normal:
         *       const vec &Normal;
         */
        point( const vec &Location, const vec &Normal = vec(0) );

        /* Class constructor.
         * ARGUMENTS:
         *   - point:
         *       const point &Point;
         */
        point( const point &Point );

        /* Copy point function.
         * ARGUMENTS:
         *   - point to copy:
         *       const point &Point;
         * RETURNS:
         *   (point &) self reference.
         */
        point & operator=( const point &Point );
      }; /* End of 'point' class */
      
      point Intersection, Nearest, Farthest;  /* One point of intersection */
      FLT T;                                  /* T value for intersecting ray */
      INT IsCollide;                          /* Number of collisions */

    public:
      /* Class constructor.
       * ARGUMENTS: None.
       */
      collision( VOID );

      /* Class constructor.
       * ARGUMENTS:
       *   - number of collisions:
       *       const INT &IsCollide;
       */
      collision( const INT &IsCollide );

      /* Class constructor.
       * ARGUMENTS:
       *   - number of collisions:
       *       const INT &IsCollide;
       *   - t value:
       *       const FLT &T;
       */
      collision( const INT &IsCollide, const FLT &T );

      /* Class constructor.
       * ARGUMENTS:
       *   - coordinates of intersection:
       *       const vec &Location;
       */
      collision( const vec &Location );

      /* Class constructor.
       * ARGUMENTS:
       *   - coordinates of intersection:
       *       const vec &Location;
       *   - t value:
       *       const FLT &T;
       */
      collision( const vec &Location, const FLT &T );

      /* Class constructor.
       * ARGUMENTS:
       *   - intersection point:
       *       const point &Point;
       *   - t value:
       *       const FLT &T;
       */
      collision( const point &Point, const FLT &T );

      /* Class constructor.
       * ARGUMENTS:
       *   - collision to copy:
       *       const collision &Collision;
       */
      collision( const collision &Collision );

      /* Copy collision function.
       * ARGUMENTS:
       *   - collision to copy:
       *       const collision &Collision;
       * RETURNS:
       *   (collision &) self reference.
       */
      collision & operator=( const collision &Collision );
    }; /* End of 'collision' class */

    /* Undefined shape class */
    class shape
    {
    public:
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
      virtual collision Intersect( const ray &Ray, const BOOL &ComputeNormal = FALSE, const BOOL &ComputePoint = FALSE, const trans &Trans = trans().SetUnit() ) const;

      /* Collide with another shape function.
       * ARGUMENTS:
       *   - shape to intersect with:
       *       const shape &Shape;
       * RETURNS:
       *   (BOOL) TRUE if collide, FALSE otherwise.
       */
      virtual BOOL Collide( const shape &Shape ) const;
    }; /* End of 'shape' class */

    /* Triangle class */
    class triangle : public shape
    {
    private:
      /* Intersection parametres */
      vec Du, Dv;                   /* Unit vectors for uv(texture) coordinate system */
    public:
      vec P0, P1, P2, Normal;       /* Points and plane normal */

    public:
      /* Class constructor.
       * ARGUMENTS: None
       */
      triangle( VOID );

      /* Class constructor.
       * ARGUMENTS:
       *   - triangle to copy:
       *       const triangle &Triangle;
       */
      triangle( const triangle &Triangle );

      /* Class constructor.
       * ARGUMENTS:
       *   - triangle points:
       *       const vec &P0, &P1, &P2;
       */
      triangle( const vec &P0, const vec &P1, const vec &P2 );

      /* Copy triangle function.
       * ARGUMENTS:
       *   - triangle to copy:
       *       const triangle &Triangle;
       * RETURNS:
       *   (triangle &) self reference.
       */
      triangle & operator=( const triangle &Triangle );

      /* Set triangle function.
       * ARGUMENTS:
       *   - triangle points:
       *       const vec &P0, &P1, &P2;
       * RETURNS: None.
       */
      VOID Set( const vec &P0, const vec &P1, const vec &P2 );

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
      collision Intersect( const ray &Ray, const BOOL &ComputeNormal = FALSE, const BOOL &ComputePoint = FALSE, const trans &Trans = trans().SetUnit() ) const;
    }; /* End of 'triangle' class */

    /* Plane class */
    class plane : public shape
    {
    public:
      vec Normal;     /* Normal to plane */
      FLT Distance;   /* Distance to plane */
    public:

      /* Class constructor.
       * ARGUMENTS: None.
       */
      plane( VOID );

      /* Class constructor.
       * ARGUMENTS:
       *   - new plane normal:
       *       const vec &Normal;
       *   - new distance to plane:
       *       const FLT &Distance;
       */
      plane( const vec &Normal, const FLT &Distance );

      /* Class constructor.
       * ARGUMENTS:
       *   - three points on plane:
       *       const vec &P0, &P1, &P2;
       */
      plane( const vec &P0, const vec &P1, const vec &P2 );

      /* Class constructor.
       * ARGUMENTS:
       *   - plane to copy:
       *       const plane &Plane;
       */
      plane( const plane &Plane );

      /* Copy plane function.
       * ARGUMENTS:
       *   - plane to copy:
       *       const plane &Plane;
       * RETURNS:
       *   (plane &) self reference.
       */
      plane & operator=( const plane &Plane );

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
      collision Intersect( const ray &Ray, const BOOL &ComputeNormal = FALSE, const BOOL &ComputePoint = FALSE, const trans &Trans = trans().SetUnit() ) const;
    }; /* End of 'plane' class */

    /* Finite plane class */
    class plane_finite : public shape
    {
    public:
      triangle Tr0, Tr1; /* Plane triangles */

    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - plane location:
       *       const vec &Loc;
       *   - plane Du and Dv:
       *       const vec &Du, &Dv;
       */
      plane_finite( const vec &Loc, const vec &Du, const vec &Dv );

      /* Class constructor.
       * ARGUMENTS:
       *   - plane to copy:
       *       const plane_finite &PlaneFinite;
       */
      plane_finite( const plane_finite &PlaneFinite );

      /* Copy plane function.
       * ARGUMENTS:
       *   - plane to copy:
       *       const plane_finite &PlaneFinite;
       * RETURNS:
       *   (plane_finite &) self reference.
       */
      plane_finite & operator=( const plane_finite &PlaneFinite );

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
      collision Intersect( const ray &Ray, const BOOL &ComputeNormal = FALSE, const BOOL &ComputePoint = FALSE, const trans &Trans = trans().SetUnit() ) const;
    }; /* End of 'plane_finite' class */
  } /* end of 'cd' namespace */
} /* end of 'tcg' namespace */

#endif /* __cd_h_ */

/* END OF 'cd.h' FILE */
