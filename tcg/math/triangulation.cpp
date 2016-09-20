/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : triangulation.cpp
 * PURPOSE     : Computational geometry project.
 *               Computational geometry support module.
 *               Triangulation support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 24.08.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <algorithm>

#include "computational_geometry.h"

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
VOID tcg::math::TriangulateConst( const std::vector<vec> &Points, const std::vector<INT> &Indices, std::vector<triangle> &Triangles )
{
  if (Points.size() < 3)
    return;

  std::vector<point> PolygonPoints;
  for (INT i = 0; i < Indices.size(); i++)
    PolygonPoints.push_back(point(Points[Indices[i]], Indices[i]));

  DOUBLE s = 0;
  for (INT i = 0; i < Indices.size(); i++)
    s += (Points[Indices[(i + 1) % Indices.size()]].X - Points[Indices[i]].X) *
         (Points[Indices[(i + 1) % Indices.size()]].Z + Points[Indices[i]].Z);

  if (s < 0)
    std::reverse(PolygonPoints.begin(), PolygonPoints.end());

  for (INT i = 0; i < PolygonPoints.size(); i++)
    for (INT j = i + 1; j < PolygonPoints.size(); j++)
      if (PolygonPoints[i].Loc == PolygonPoints[j].Loc)
        return;

  for (INT i = 0; i < PolygonPoints.size(); i++)
    for (INT j = i + 2; j < PolygonPoints.size(); j++)
    {
      vec
        p0 = PolygonPoints[i].Loc, p1 = PolygonPoints[(i + 1) % PolygonPoints.size()].Loc,
        q0 = PolygonPoints[j].Loc, q1 = PolygonPoints[(j + 1) % PolygonPoints.size()].Loc;
      vec
        np = vec(p0.Z - p1.Z, 0, p1.X - p0.X).Normalizing(),
        nq = vec(q0.Z - q1.Z, 0, q1.X - q0.X).Normalizing();
      DOUBLE
        cp = -np.X * p0.X - np.Z * p0.Z,
        cq = -nq.X * q0.X - nq.Z * q0.Z;

      if ((np.X * q0.X + np.Z * q0.Z + cp) * (np.X * q1.X + np.Z * q1.Z + cp) < 0 &&
          (nq.X * p0.X + nq.Z * p0.Z + cq) * (nq.X * p1.X + nq.Z * p1.Z + cq) < 0)
        return;
    }

  while (PolygonPoints.size() > 2)
  {
    INT size = PolygonPoints.size();
    for (INT i = 0; i < PolygonPoints.size(); i++)
    {
      if (Rotation(PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc,
                   PolygonPoints[(i + 2) % PolygonPoints.size()].Loc - PolygonPoints[(i + 1) % PolygonPoints.size()].Loc) > 0)
      {
        BOOL skip = FALSE;
        for (INT j = 0; j < PolygonPoints.size(); j++)
          if (j != i && j != (i + 1) % PolygonPoints.size() && j != (i + 2) % PolygonPoints.size() &&
              (Rotation(PolygonPoints[j].Loc -                              PolygonPoints[i].Loc,
                        PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc) *
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[(i + 1) % PolygonPoints.size()].Loc,
                        PolygonPoints[(i + 2) % PolygonPoints.size()].Loc - PolygonPoints[(i + 1) % PolygonPoints.size()].Loc) > 0 &&
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[i].Loc,
                        PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc) *
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[(i + 2) % PolygonPoints.size()].Loc,
                        PolygonPoints[i].Loc - PolygonPoints[(i + 2) % PolygonPoints.size()].Loc) > 0))
          {
            skip = TRUE;
            break;
          }
        if (skip)
          continue;

        Triangles.push_back(triangle(PolygonPoints[i].Index,
                                     PolygonPoints[(i + 1) % PolygonPoints.size()].Index,
                                     PolygonPoints[(i + 2) % PolygonPoints.size()].Index));
        PolygonPoints.erase(PolygonPoints.begin() + (i + 1) % PolygonPoints.size());
        break;
      }
    }
    if (size == PolygonPoints.size())
    {
      Triangles.push_back(triangle(PolygonPoints[0].Index, PolygonPoints[1].Index, PolygonPoints[2].Index));
      return;
    }
  }
} /* End of 'tcg::math::TriangulateConst' function */

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
VOID tcg::math::Triangulate( const std::vector<vec> &Points, std::vector<INT> &Indices, std::vector<triangle> &Triangles )
{
  if (Points.size() < 3)
    return;

  DOUBLE s = 0;
  for (INT i = 0; i < Indices.size(); i++)
    s += (Points[Indices[(i + 1) % Indices.size()]].X - Points[Indices[i]].X) *
         (Points[Indices[(i + 1) % Indices.size()]].Z + Points[Indices[i]].Z);

  if (s < 0)
    std::reverse(Indices.begin(), Indices.end());

  std::vector<point> PolygonPoints;
  for (INT i = 0; i < Indices.size(); i++)
    PolygonPoints.push_back(point(Points[Indices[i]], Indices[i]));

  for (INT i = 0; i < PolygonPoints.size(); i++)
    for (INT j = i + 2; j < PolygonPoints.size(); j++)
    {
      vec
        p0 = PolygonPoints[i].Loc, p1 = PolygonPoints[(i + 1) % PolygonPoints.size()].Loc,
        q0 = PolygonPoints[j].Loc, q1 = PolygonPoints[(j + 1) % PolygonPoints.size()].Loc;
      vec
        np = vec(p0.Z - p1.Z, 0, p1.X - p0.X).Normalizing(),
        nq = vec(q0.Z - q1.Z, 0, q1.X - q0.X).Normalizing();
      DOUBLE
        cp = -np.X * p0.X - np.Z * p0.Z,
        cq = -nq.X * q0.X - nq.Z * q0.Z;

      if ((np.X * q0.X + np.Z * q0.Z + cp) * (np.X * q1.X + np.Z * q1.Z + cp) < 0 &&
          (nq.X * p0.X + nq.Z * p0.Z + cq) * (nq.X * p1.X + nq.Z * p1.Z + cq) < 0)
        return;
    }

  while (PolygonPoints.size() > 2)
  {
    for (INT i = 0; i < PolygonPoints.size(); i++)
    {
      if (Rotation(PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc,
                   PolygonPoints[(i + 2) % PolygonPoints.size()].Loc - PolygonPoints[(i + 1) % PolygonPoints.size()].Loc) > 0)
      {
        BOOL skip = FALSE;
        for (INT j = 0; j < PolygonPoints.size(); j++)
          if (j != i && j != (i + 1) % PolygonPoints.size() && j != (i + 2) % PolygonPoints.size() &&
              (Rotation(PolygonPoints[j].Loc -                              PolygonPoints[i].Loc,
                        PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc) *
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[(i + 1) % PolygonPoints.size()].Loc,
                        PolygonPoints[(i + 2) % PolygonPoints.size()].Loc - PolygonPoints[(i + 1) % PolygonPoints.size()].Loc) > 0 &&
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[i].Loc,
                        PolygonPoints[(i + 1) % PolygonPoints.size()].Loc - PolygonPoints[i].Loc) *
               Rotation(PolygonPoints[j].Loc -                              PolygonPoints[(i + 2) % PolygonPoints.size()].Loc,
                        PolygonPoints[i].Loc - PolygonPoints[(i + 2) % PolygonPoints.size()].Loc) > 0))
          {
            skip = TRUE;
            break;
          }
        if (skip)
          continue;

        Triangles.push_back(triangle(PolygonPoints[i].Index,
                                     PolygonPoints[(i + 1) % PolygonPoints.size()].Index,
                                     PolygonPoints[(i + 2) % PolygonPoints.size()].Index));
        PolygonPoints.erase(PolygonPoints.begin() + (i + 1) % PolygonPoints.size());
        break;
      }
    }
  }
} /* End of 'tcg::math::Triangulate' function */

/* Swap points function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::math::triangle_edge::swap( VOID )
{
  INT tmp = P0;
  P0 = P1;
  P1 = tmp;
} /* End of 'tcg::math::triangle_edge::swap' function */

/* Compare edges function
 * ARGUMENTS:
 *   - edge to compare with:
 *       const triangle_edge &Edge;
 * RETURNS:
 *   (BOOL) TRUE if less, FALSE otherwise.
 */
BOOL tcg::math::triangle_edge::operator<( const triangle_edge &Edge )
{
  if (P0 < Edge.P0)
    return TRUE;
  if (P0 == Edge.P0 && P1 < Edge.P1)
    return TRUE;
  return FALSE;
} /* End of 'tcg::math::triangle_edge::operator<' function */

/* Compare edges function
 * ARGUMENTS:
 *   - edge to compare with:
 *       const triangle_edge &Edge;
 * RETURNS:
 *   (BOOL) TRUE if more, FALSE otherwise.
 */
BOOL tcg::math::triangle_edge::operator>( const triangle_edge &Edge )
{
  if (P0 > Edge.P0)
    return TRUE;
  if (P0 == Edge.P0 && P1 > Edge.P1)
    return TRUE;
  return FALSE;
} /* End of 'tcg::math::triangle_edge::operator>' function */

/* Compare edges function
 * ARGUMENTS:
 *   - edges to compare:
 *       const triangle_edge &a, &b;
 * RETURNS:
 *   (INT) -1 if first is less, 1 if first is more, 0 if equal.
 */
INT tcg::math::edge_stock::compare( const triangle_edge &a, const triangle_edge &b )
{
  if (a.P0 < b.P0)
    return -1;
  if (a.P0 == b.P0)
    if (a.P1 < b.P1)
      return -1;
    else if (a.P1 > b.P1)
      return 1;
    else
      return 0;
  return 1;
} /* End of 'tcg::math::edge_stock::compare' function */

/* Sort edges function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::math::edge_stock::sort( VOID )
{
  for (INT i = 0; i < Edges.size(); i++)
    if (Edges[i].P0 > Edges[i].P1)
      Edges[i].swap(), Edges[i].FreeSide = !Edges[i].FreeSide;
  std::sort(Edges.begin(), Edges.end());
} /* End of 'tcg::math::edge_stock::sort' function */

/* Add edge function.
 * ARGUMENTS:
 *   - edge to add or delete if it already exists:
 *       triangle_edge Edge;
 * RETURNS: None.
 */
VOID tcg::math::edge_stock::add( triangle_edge Edge )
{
  if (Edge.P0 > Edge.P1)
      Edge.swap(), Edge.FreeSide = !Edge.FreeSide;
  INT min = 0, max = Edges.size() - 1, medium, comp;
  if (compare(Edges[min], Edge) == 0)
  {
    Edges.erase(Edges.begin() + min);
    return;
  }
  if (compare(Edges[max], Edge) == 0)
  {
    Edges.erase(Edges.begin() + max);
    return;
  }
  while (max - min > 1)
  {
    medium = (min + max) / 2;
    comp = compare(Edges[medium], Edge);
    if (comp < 0)
      min = medium;
    else if (comp > 0)
      max = medium;
    else
    {
      Edges.erase(Edges.begin() + medium);
      return;
    }
  }
  if (Edges[min] > Edge)
    Edges.insert(Edges.begin() + min, Edge);
  else if (Edges[max] < Edge)
    Edges.insert(Edges.begin() + max + 1, Edge);
  else
    Edges.insert(Edges.begin() + max, Edge);
} /* End of 'tcg::math::edge_stock::add' function */

/* Add edge that definitely is not already active.
 * ARGUMENTS:
 *   - edge to add:
 *       const triangle_edge &Edge;
 * RETURNS: None.
 */
VOID tcg::math::edge_stock::push_back( const triangle_edge &Edge )
{
  Edges.push_back(Edge);
} /* End of 'tcg::math::edge_stock::push_back' function */

/* Delete edge from end of stock.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::math::edge_stock::pop_back( VOID )
{
  Edges.pop_back();
} /* End of 'tcg::math::edge_stock::pop_back' function */

/* Get edge by index function.
 * ARGUMENTS:
 *   - index of edge:
 *       INT n;
 * RETURNS:
 *   (triangle_edge &) reference to edge.
 */
tcg::math::triangle_edge & tcg::math::edge_stock::operator[]( INT n )
{
  return Edges[n];
} /* End of 'tcg::math::edge_stock::operator[] function */

/* Get last edge function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (triangle_edge &) reference to last edge.
 */
tcg::math::triangle_edge & tcg::math::edge_stock::last( VOID )
{
  return Edges.back();
} /* End of 'tcg::math::edge_stock::last' function */

/* Get number of active edges function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) number of edges.
 */
INT tcg::math::edge_stock::size( VOID )
{
  return Edges.size();
} /* End of 'tcg::math::edge_stock::size' function */

/* Triangulate set of points function.
 * ARGUMENTS:
 *   - set of points:
 *       const std::vector<vec> Points;
 *   - stock of triangles to fill:
 *       std::vector<triangle> &Triangles;
 * RETURNS: None.
 */
VOID tcg::math::Triangulate( const std::vector<vec> &Points, std::vector<triangle> &Triangles )
{
  // Clear stock of triangles.
  Triangles.clear();

  // Not enough points.
  if (Points.size() < 3)
    return;

  edge_stock ActiveEdges; // Stock of active edges.

  // Rounded points.
  std::vector<point> RoundPoints;
  RoundPoints.reserve(Points.size());
  for (INT i = 0; i < Points.size(); i++)
    RoundPoints.push_back(point(Points[i], i));

  // Sort points by X and Z
  std::sort(RoundPoints.begin(), RoundPoints.end(), []( point a, point b )
  {
    if (a.Loc.X < b.Loc.X)
      return 1;
    if (a.Loc.X == b.Loc.X && a.Loc.Z < b.Loc.Z)
      return 1;
    return 0;
  });

  // Build convex hull.

  // Bottom side.
  ActiveEdges.push_back(triangle_edge(0, 1));
  for (INT i = 1; i < RoundPoints.size() - 1; i++)
  {
    INT rotation =
      Rotation(RoundPoints[ActiveEdges.last().P1].Loc - RoundPoints[ActiveEdges.last().P0].Loc, RoundPoints[i + 1].Loc - RoundPoints[ActiveEdges.last().P1].Loc);
    while (rotation < 0 && ActiveEdges.size() > 0)
    {
      ActiveEdges.pop_back();
      if (ActiveEdges.size() > 0)
        rotation =
          Rotation(RoundPoints[ActiveEdges.last().P1].Loc - RoundPoints[ActiveEdges.last().P0].Loc, RoundPoints[i + 1].Loc - RoundPoints[ActiveEdges.last().P1].Loc);
    }
    if (ActiveEdges.size() > 0)
      ActiveEdges.push_back(triangle_edge(ActiveEdges.last().P1, i + 1));
    else
      ActiveEdges.push_back(triangle_edge(0, i + 1));
  }
  // Top side.
  ActiveEdges.push_back(triangle_edge(ActiveEdges.last().P1, Points.size() - 2));
  for (INT i = RoundPoints.size() - 2; i > 0; i--)
  {
    INT rotation =
      Rotation(RoundPoints[ActiveEdges.last().P1].Loc - RoundPoints[ActiveEdges.last().P0].Loc, RoundPoints[i - 1].Loc - RoundPoints[ActiveEdges.last().P1].Loc);
    while (rotation < 0 && ActiveEdges.size() > 0)
    {
      ActiveEdges.pop_back();
      if (ActiveEdges.size() > 0)
        rotation =
          Rotation(RoundPoints[ActiveEdges.last().P1].Loc - RoundPoints[ActiveEdges.last().P0].Loc, RoundPoints[i - 1].Loc - RoundPoints[ActiveEdges.last().P1].Loc);
    }
    ActiveEdges.push_back(triangle_edge(ActiveEdges.last().P1, i - 1));
  }

  ActiveEdges.sort();

  // Number of triangles is n + i - 2, where
  // n is number of points, i is number of interior points.
  // INT NoofTriangles = RoundPoints.size() * 2 - ActiveEdges.size() - 2;

  DOUBLE t, MinT, denom;         // Center coordinate of current and clothest circle with mating point(s).
  INT MatingPoint;               // One mating point.
  std::vector<INT> MatingPoints; // Stock of mating points.
  BOOL MoreMatingPoints;         // Some mating points flag.
  triangle_edge CurrentEdge;     // Current edge.
  vec P0, P1, P01;               // Current edge coordinates.
  ray Perp0, Perp1;              // Median perpendiculars coordinates.

  // Search triangles while stock of edges is not empty.
  while (ActiveEdges.size() > 0)
  {
    MinT = DBL_MAX;
    MatingPoint = -1;
    MatingPoints.clear();
    MoreMatingPoints = FALSE;
    CurrentEdge = ActiveEdges.last();
    if (CurrentEdge.FreeSide == FREE_RIGHT)
      CurrentEdge.swap();
    P0 = RoundPoints[CurrentEdge.P0].Loc, P1 = RoundPoints[CurrentEdge.P1].Loc, P01 = (P1 - P0).Normalizing();
    Perp0.Org = (P0 + P1) / 2;
    Perp0.Dir = vec(P1.Z - P0.Z, 0, P0.X - P1.X).Normalizing();

    // Find mating point(s).
    for (INT i = 0; i < Points.size(); i++)
    {
      // Skip points of current edge.
      if (i == CurrentEdge.P0 || i == CurrentEdge.P1)
        continue;
      // Skip triangles in right side.
      if (Rotation(P1 - P0, RoundPoints[i].Loc - P1) <= 0)
        continue;
      Perp1.Org = (RoundPoints[i].Loc + P1) / 2;
      Perp1.Dir = vec(RoundPoints[i].Loc.Z - P1.Z, 0, P1.X - RoundPoints[i].Loc.X);
      // Coordinate of circle center.
      denom = Perp0.Dir.Z * Perp1.Dir.X - Perp0.Dir.X * Perp1.Dir.Z;
      if (fabs(denom) < Threshold)
        continue;
      t = (Perp1.Dir.X * (Perp1.Org.Z - Perp0.Org.Z) + Perp1.Dir.Z * (Perp0.Org.X - Perp1.Org.X)) / denom;

      // Found some points on one circle.
      if (fabs(t - MinT) < Threshold)
      {
        if (!MoreMatingPoints)
        {
          MoreMatingPoints = TRUE;
          MatingPoints.clear();
          MatingPoints.push_back(MatingPoint);
        }
        MatingPoints.push_back(i);
      }
      // Found circle with less center coordinate.
      else if (t < MinT)
      {
        MoreMatingPoints = FALSE;
        MinT = t;
        MatingPoint = i;
      }
    }
    // Found one new triangle.
    if (!MoreMatingPoints)
    {
      Triangles.push_back(triangle(RoundPoints[CurrentEdge.P0].Index, RoundPoints[CurrentEdge.P1].Index, RoundPoints[MatingPoint].Index));
      ActiveEdges.pop_back();
      ActiveEdges.add(triangle_edge(CurrentEdge.P0, MatingPoint));
      ActiveEdges.add(triangle_edge(MatingPoint, CurrentEdge.P1));
    }
    // Found some new triangles on one circle.
    else
    {
      std::sort(MatingPoints.begin(), MatingPoints.end(), [RoundPoints, P0, P01]( INT a, INT b )
      {
        return (P01 & (RoundPoints[a].Loc - P0).Normalizing()) > (P01 & (RoundPoints[b].Loc - P0).Normalizing());
      });
      ActiveEdges.pop_back();

      Triangles.push_back(triangle(RoundPoints[CurrentEdge.P0].Index, RoundPoints[CurrentEdge.P1].Index, RoundPoints[MatingPoints[0]].Index));
      ActiveEdges.add(triangle_edge(MatingPoints[0], CurrentEdge.P1));
      for (INT j = 1; j < MatingPoints.size(); j++)
      {
        Triangles.push_back(triangle(RoundPoints[CurrentEdge.P0].Index, RoundPoints[MatingPoints[j - 1]].Index, RoundPoints[MatingPoints[j]].Index));
        ActiveEdges.add(triangle_edge(MatingPoints[j], MatingPoints[j - 1]));
      }
      ActiveEdges.add(triangle_edge(CurrentEdge.P0, MatingPoints.back()));
    }
  }
} /* End of 'tcg::math::Triangulate' function */

/* END OF 'triangulation.cpp' FILE */
