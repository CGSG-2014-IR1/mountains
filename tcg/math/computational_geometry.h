/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : computational_geometry.h
 * PURPOSE     : Computational geometry project.
 *               Computational geometry support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 24.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __computational_geometry_h_
#define __computational_geometry_h_

#include "../def.h"

#include <vector>

/* Computational geometry project namespace */
namespace tcg
{
  /* Math support namespace */
  namespace math
  {
    /* Define vectors rotation.
     * ARGUMENTS:
     *   - vectors:
     *       const vec &a, &b;
     * RETURNS:
     *   (INT) 1 if left, -1 if right, 0 otherwise.
     */
    INT Rotation( const vec &a, const vec &b );

    /* Point struct */
    struct point
    {
      vec Loc;   // Point location.
      INT Index; // Point index.

      /* Class constructor.
       * ARGUMENTS:
       *   - point location:
       *       const vec &Loc;
       *   - point index:
       *       INT Index;
       */
      point( const vec &Loc, INT Index ) : Loc(round(Loc.X * 1e7) / 1e7, 0, round(Loc.Z * 1e7) / 1e7), Index(Index)
      {
      } /* End of 'point' function */
    }; /* End of 'point' struct */

    /* Triangle struct */
    struct triangle
    {
      INT P[3]; /* Triangle points indices */

      /* Struct constructor.
       * ARGUMENTS:
       *   - triangle points indices:
       *       INT P0, P1, P2;
       */
      triangle( INT P0, INT P1, INT P2 )
      {
        P[0] = P0;
        P[1] = P1;
        P[2] = P2;
      } /* End of 'triangle' function */
    }; /* End of 'triangle' struct */

    /* Polygon edge struct */
    struct edge
    {
      INT P0, P1; // Edge points indices.

      /* Struct constructor.
       * ARGUMENTS: None.
       */
      edge( VOID )
      {
      } /* End of 'edge' function */

      /* Struct constructor.
       * ARGUMENTS:
       *   - edge points indices:
       *       INT P0, P1;
       */
      edge( INT P0, INT P1 ) : P0(P0), P1(P1)
      {
      } /* End of 'edge' function */
    }; /* End of 'edge' struct */

    /* Flags of edge free side */
    enum
    {
      FREE_LEFT, FREE_RIGHT
    }; /* End of enum */

    /* Triangle edge struct */
    struct triangle_edge
    {
      INT
        P0, P1,   // Edge points indices.
        FreeSide; // Edge free side.

      /* Struct constructor.
       * ARGUMENTS: None.
       */
      triangle_edge( VOID )
      {
      } /* End of 'triangle_edge' function */

      /* Struct constructor.
       * ARGUMENTS:
       *   - edge points indices:
       *       INT P0, P1;
       */
      triangle_edge( INT P0, INT P1 ) : P0(P0), P1(P1), FreeSide(FREE_LEFT)
      {
      } /* End of 'triangle_edge' function */

      /* Struct constructor.
       * ARGUMENTS:
       *   - edge points indices:
       *       INT P0, P1;
       *   - edge free side:
       *       INT FreeSide;
       */
      triangle_edge( INT P0, INT P1, INT FreeSide ) : P0(P0), P1(P1), FreeSide(FreeSide)
      {
      } /* End of 'triangle_edge' function */

      /* Swap points function
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID swap( VOID );

      /* Compare edges function
       * ARGUMENTS:
       *   - edge to compare with:
       *       const triangle_edge &Edge;
       * RETURNS:
       *   (BOOL) TRUE if less, FALSE otherwise.
       */
      BOOL operator<( const triangle_edge &Edge );

      /* Compare edges function
       * ARGUMENTS:
       *   - edge to compare with:
       *       const triangle_edge &Edge;
       * RETURNS:
       *   (BOOL) TRUE if more, FALSE otherwise.
       */
      BOOL operator>( const triangle_edge &Edge );
    }; /* End of 'triangle_edge' struct */

    /* Edge stock class */
    class edge_stock
    {
    public:
      std::vector<triangle_edge> Edges; // Stock of active edges.

    public:
      /* Compare edges function
       * ARGUMENTS:
       *   - edges to compare:
       *       const triangle_edge &a, &b;
       * RETURNS:
       *   (INT) -1 if first is less, 1 if first is more, 0 if equal.
       */
      INT compare( const triangle_edge &a, const triangle_edge &b );

      /* Sort edges function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID sort( VOID );

      /* Add edge function.
       * ARGUMENTS:
       *   - edge to add or delete if it already exists:
       *       triangle_edge Edge;
       * RETURNS: None.
       */
      VOID add( triangle_edge Edge );

      /* Add edge that definitely is not already active.
       * ARGUMENTS:
       *   - edge to add:
       *       const triangle_edge &Edge;
       * RETURNS: None.
       */
      VOID push_back( const triangle_edge &Edge );

      /* Delete edge from end of stock.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID pop_back( VOID );

      /* Get edge by index function.
       * ARGUMENTS:
       *   - index of edge:
       *       INT n;
       * RETURNS:
       *   (triangle_edge &) reference to edge.
       */
      triangle_edge & operator[]( INT n );

      /* Get last edge function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (triangle_edge &) reference to last edge.
       */
      triangle_edge & last( VOID );

      /* Get number of active edges function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (INT) number of edges.
       */
      INT size( VOID );
    }; /* End of 'edge_stock' class */

    /* Triangulate polygon function.
     * ARGUMENTS:
     *   - polygon points:
     *       const std::vector<vec> &Points;
     *   - polygon points indices:
     *       const std::vector<INT> Indices;
     *   - stock of triangles to fill:
     *       std::vector<triangle> &Triangles;
     * RETURNS: None.
     */
    VOID TriangulateConst( const std::vector<vec> &Points, const std::vector<INT> &Indices, std::vector<triangle> &Triangles );

    /* Triangulate polygon function.
     * ARGUMENTS:
     *   - polygon points:
     *       const std::vector<vec> &Points;
     *   - polygon points indices:
     *       std::vector<INT> Indices;
     *   - stock of triangles to fill:
     *       std::vector<triangle> &Triangles;
     * RETURNS: None.
     */
    VOID Triangulate( const std::vector<vec> &Points, std::vector<INT> &Indices, std::vector<triangle> &Triangles );

    /* Triangulate set of points function.
     * ARGUMENTS:
     *   - set of points:
     *       const std::vector<vec> &Points;
     *   - stock of triangles to fill:
     *       std::vector<triangle> &Triangles;
     * RETURNS: None.
     */
    VOID Triangulate( const std::vector<vec> &Points, std::vector<triangle> &Triangles );
  } /* end of 'math' namespace */
} /* end of 'tcg' namespace */

#endif /* __computational_geometry_h_ */

/* END OF 'computational_geometry.h' FILE */
