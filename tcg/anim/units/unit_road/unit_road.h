/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit_road.h
 * PURPOSE     : Computational geometry project.
 *               Road unit.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 25.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __unit_road_h_
#define __unit_road_h_

#include "../../../def.h"

#include "../../unit.h"
#include "../../render/prim/patch3.h"
#include "../../render/prim/trimesh.h"
#include "../../../math/cd.h"
#include "../../../math/noise.h"

/* Computational geometry project namespace */
namespace tcg
{
  using namespace math;

  /* Road unit class */
  class unit_road : public unit
  {
  private:
    fBm_multi_ridged fBm;

    #include "primitives.h"

    enum { LEFT, RIGHT, END_0, END_1 };

    #include "segment.h"

    #include "interpolation.h"

  private:
    const DOUBLE
      Width = 60, Height = 60,
      RoadHalfWidth = 0.2, RoadShoulderWidth = 0.2,
      MaxRoadLen = 0.4, MaxUpTan = 0.3, MaxTurnAngle = 15;

    anim *Ani;

    std::vector<vec> Points;
    std::vector<triangle> Triangles;
    primitive::patch3 Mountain;

    BOOL FirstPoint;
    vec PrevPoint;
    std::vector<segment> Segments;
    std::vector<triangle> RoadTriangles;
    primitive::trimesh Road;

    std::vector<std::vector<INT>> Houses;
    primitive::patch3 Village;

    cd::plane_finite Plane;

    enum { EDIT_ROAD, EDIT_HOUSE, EDIT_TRIANGLES };
    INT EditMode;
    BOOL IsLandscape;

    DOUBLE ScaleY;

    /* Test segment intersection function.
     * ARGUMENTS:
     *   - segment points:
     *       const vec &P0, &P1, &Q0, &Q1;
     * RETURNS:
     *   (BOOL) TRUE if intersect, FALSE otherwise.
     */
    BOOL SegmentTestSegment( const vec &P0, const vec &P1, const vec &Q0, const vec &Q1 )
    {
      if (P0 == Q0 || P0 == Q1 || P1 == Q0 || P1 == Q1)
        return FALSE;
      vec
        np = vec(P1.Z - P0.Z, 0, P0.X - P1.X).Normalizing(),
        nq = vec(Q1.Z - Q0.Z, 0, Q0.X - Q1.X).Normalizing();
      DOUBLE
        cp = -np.X * P0.X - np.Z * P0.Z,
        cq = -nq.X * Q0.X - nq.Z * Q0.Z,
        r00 = np.X * Q0.X + np.Z * Q0.Z + cp,
        r01 = np.X * Q1.X + np.Z * Q1.Z + cp,
        r10 = nq.X * P0.X + nq.Z * P0.Z + cq,
        r11 = nq.X * P1.X + nq.Z * P1.Z + cq;
      if (fabs(r00) < tsg::Threshold || fabs(r01) < tsg::Threshold || fabs(r10) < tsg::Threshold || fabs(r11) < tsg::Threshold)
        return FALSE;
      if (r00 * r01 < 0 && r10 * r11 < 0)
        return TRUE;
      return FALSE;
    } /* End of 'SegmentTestSegment' function */

    /* Test segment intersection function.
     * ARGUMENTS:
     *   - segment points:
     *       const vec &P0, &P1, &Q0, &Q1;
     * RETURNS:
     *   (BOOL) TRUE if intersect, FALSE otherwise.
     */
    BOOL SegmentTestSegmentInc( const vec &P0, const vec &P1, const vec &Q0, const vec &Q1 )
    {
      if (P0 == Q0 || P0 == Q1 || P1 == Q0 || P1 == Q1)
        return TRUE;
      vec
        np = vec(P1.Z - P0.Z, 0, P0.X - P1.X).Normalizing(),
        nq = vec(Q1.Z - Q0.Z, 0, Q0.X - Q1.X).Normalizing();
      if (np == nq || np == -nq)
        return FALSE;
      DOUBLE
        cp = -np.X * P0.X - np.Z * P0.Z,
        cq = -nq.X * Q0.X - nq.Z * Q0.Z,
        r00 = np.X * Q0.X + np.Z * Q0.Z + cp,
        r01 = np.X * Q1.X + np.Z * Q1.Z + cp,
        r10 = nq.X * P0.X + nq.Z * P0.Z + cq,
        r11 = nq.X * P1.X + nq.Z * P1.Z + cq;
      if ((fabs(r00) < tsg::Threshold || fabs(r01) < tsg::Threshold) && (fabs(r10) >= tsg::Threshold && fabs(r11) >= tsg::Threshold && r10 * r11 < 0) ||
          (fabs(r10) < tsg::Threshold || fabs(r11) < tsg::Threshold) && (fabs(r00) >= tsg::Threshold && fabs(r01) >= tsg::Threshold && r00 * r01 < 0))
        return TRUE;
      if (r00 * r01 < 0 && r10 * r11 < 0)
        return TRUE;
      return FALSE;
    } /* End of 'SegmentTestSegment' function */

    /* Intersect lines function.
     * ARGUMENTS:
     *   - line points and directions:
     *       const vec &P0, &P01, &Q0, &Q01;
     * RETURNS:
     *   (vec) intersection point.
     */
    vec LineIntersectLine( const vec &P0, const vec &P01, const vec &Q0, const vec &Q01 )
    {
      return P0 + P01 * ((Q01.X * (Q0.Z - P0.Z) + Q01.Z * (P0.X - Q0.X)) / (P01.Z * Q01.X - P01.X * Q01.Z));
    } /* End of 'LineIntersectLine' function */

    /* Test if point belongs to triangle function.
     * ARGUMENTS:
     *   - point:
     *       const vec &Point;
     *   - triangle vertices:
     *       const vec &T0, &T1, &T2;
     * RETURNS:
     *   (BOOL) TRUE if belongs, FALSE otherwise.
     */
    BOOL PointTestTriangle( const vec &Point, const vec &T0, const vec &T1, const vec &T2 )
    {
      if (Rotation(T1 - T0, Point - T0) >= 0 &&
          Rotation(T2 - T1, Point - T1) >= 0 &&
          Rotation(T0 - T2, Point - T2) >= 0)
        return TRUE;
      return FALSE;
    } /* End of 'PointTestTriangle' function */

    /* Test if point belongs to hexagon function.
     * ARGUMENTS:
     *   - point:
     *       const vec &Point;
     *   - hexagon vertices:
     *       const vec &H0, &H1, &H2, &H3, &H4, &H5;
     * RETURNS:
     *   (BOOL) TRUE if belongs, FALSE otherwise.
     */
    BOOL PointTestHexagon( const vec &Point, const vec &H0, const vec &H1, const vec &H2, const vec &H3, const vec &H4, const vec &H5 )
    {
      if (Rotation(H1 - H0, Point - H0) >= 0 &&
          Rotation(H2 - H1, Point - H1) >= 0 &&
          Rotation(H3 - H2, Point - H2) >= 0 &&
          Rotation(H4 - H3, Point - H3) >= 0 &&
          Rotation(H5 - H4, Point - H4) >= 0 &&
          Rotation(H0 - H5, Point - H5) >= 0)
        return TRUE;
      return FALSE;
    } /* End of 'PointTestHexagon' function */

    /* Intersect road segments function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     * RETURNS: None.
     */
    VOID IntersectRoadSegments( std::vector<road_segment> &RoadSegments )
    {
      // No segments.
      if (Segments.size() < 1)
        return;

      // Sort points in segments.
      INT tmp;
      for (INT i = 0; i < Segments.size(); i++)
        if (Points[Segments[i].P0].Z > Points[Segments[i].P1].Z || (Points[Segments[i].P0].Z == Points[Segments[i].P1].Z && Points[Segments[i].P0].X > Points[Segments[i].P1].X))
          COM_SWAP(Segments[i].P0, Segments[i].P1, tmp);

      // Sorted segment points
      std::vector<segment_point> SegmentPoints;
      SegmentPoints.reserve(Segments.size());
      for (INT i = 0; i < Segments.size(); i++)
      {
        SegmentPoints.push_back(segment_point(Segments[i].P0, 0, &Segments[i]));
        SegmentPoints.push_back(segment_point(Segments[i].P1, 1, &Segments[i]));
      }
      std::sort(SegmentPoints.begin(), SegmentPoints.end(), [this]( segment_point a, segment_point b )
      {
        if (Points[a.Index].Z <  Points[b.Index].Z ||
            Points[a.Index].Z == Points[b.Index].Z &&
            Points[a.Index].X <  Points[b.Index].X)
          return TRUE;
        return FALSE;
      });

      // Active segments.
      segment_ptr *Candidates = new segment_ptr[Segments.size()];
      INT NoofCandidates = 0;

      vec p0, q0, p01, q01;
      DOUBLE t0, t1, denom;

      for (INT i = 0; i < SegmentPoints.size(); i++)
      {
        // New active segment.
        if (SegmentPoints[i].No == 0)
        {
          Candidates[NoofCandidates].Segment = SegmentPoints[i].Segment;
          Candidates[NoofCandidates++].IsActive = TRUE;
        }
        // End of segment - find all intersections and delete.
        else
        {
          // Check all active segments.
          for (INT j = 0; j < NoofCandidates; j++)
          {
            // Unactive segment - move last candidate to current position.
            if (!Candidates[j].IsActive)
            {
              Candidates[j] = Candidates[--NoofCandidates];
              Candidates[j].IsActive = TRUE;
              j--;
              continue;
            }
            // Find current segment.
            if (SegmentPoints[i].Segment == Candidates[j].Segment)
            {
              Candidates[j].IsActive = FALSE;
              continue;
            }
            // Segments have common point.
            if (SegmentPoints[i].Segment->P0 == Candidates[j].Segment->P0 ||
                SegmentPoints[i].Segment->P0 == Candidates[j].Segment->P1 ||
                SegmentPoints[i].Segment->P1 == Candidates[j].Segment->P0 ||
                SegmentPoints[i].Segment->P1 == Candidates[j].Segment->P1)
              continue;
            // Segments first points and directions.
            p0 = Points[SegmentPoints[i].Segment->P0];
            q0 = Points[Candidates[j].Segment->P0];
            p01 = Points[SegmentPoints[i].Segment->P1] - p0;
            q01 = Points[Candidates[j].Segment->P1] - q0;
            // Segments are parallel.
            if (fabs(denom = p01.Z * q01.X - p01.X * q01.Z) < Threshold)
              continue;
            // Intersection distance in each segment.
            t0 = (q01.X * (q0.Z - p0.Z) + q01.Z * (p0.X - q0.X)) / denom;
            t1 = (p01.X * (p0.Z - q0.Z) + p01.Z * (q0.X - p0.X)) / -denom;
            // Intersection belongs to both segments.
            if (t0 >= 0 && t0 <= 1 && t1 >= 0 && t1 <= 1 &&
               (t0 > Threshold * 1000 && fabs(t0 - 1) > Threshold * 1000 || t1 > Threshold * 1000 && fabs(t1 - 1) > Threshold * 1000))
            {
              Points.push_back(p0 + p01 * t0);
              SegmentPoints[i].Segment->Intersections.push_back(intersection(t0, Points.size() - 1));
              Candidates[j].Segment->Intersections.push_back(intersection(t1, Points.size() - 1));
            }
          }
        }
      }
      // Sort each segment intersections.
      for (INT i = 0; i < Segments.size(); i++)
        std::sort(Segments[i].Intersections.begin(), Segments[i].Intersections.end(), []( intersection a, intersection b )
        {
          return a.t < b.t;
        });

      // Save segments to road segments.
      for (INT i = 0; i < Segments.size(); i++)
      {
        RoadSegments.push_back(road_segment(Segments[i].P0));
        for (INT j = 0; j < Segments[i].Intersections.size(); j++)
        {
          RoadSegments.back().P[1] = Segments[i].Intersections[j].Index;
          RoadSegments.push_back(road_segment(Segments[i].Intersections[j].Index));
        }
        RoadSegments.back().P[1] = Segments[i].P1;
      }

      // Free memory.
      delete [] Candidates;
    } /* End of 'IntersectRoadSegments' function */

    /* Set road segments function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, DOUBLE Shoulder;
     * RETURNS: None.
     */
    VOID SetRoadSegments( std::vector<road_segment> &RoadSegments, DOUBLE HalfWidth, DOUBLE Shoulder )
    {
      INT
        tmp, act = 0, actno = 0, rotate, isstraight, isneighbour,
        min[2][2], max[2][2], straight[2], minno[2][2], maxno[2][2], straightno[2];
      DOUBLE mincos[2][2], maxcos[2][2], actcos;
      road_segment CurrentSegment;
      vec Norm0, Norm1, Dir0, Dir1;

      for (INT i = 0; i < RoadSegments.size(); i++)
        if (RoadSegments[i].P[0] > RoadSegments[i].P[1])
          COM_SWAP(RoadSegments[i].P[0], RoadSegments[i].P[1], tmp);

      for (INT i = 0; i < RoadSegments.size(); i++)
      {
        CurrentSegment = RoadSegments[i];
        for (INT side = 0; side < 2; side++)
          for (INT no = 0; no < 2; no++)
            min[side][no] = -1, max[side][no] = -1, straight[no] = -1;
        for (INT j = i + 1; j < RoadSegments.size(); j++)
        {
          for (INT ino = 0; ino < 2; ino++)
            for (INT jno = 0; jno < 2; jno++)
            {
              if (RoadSegments[j].P[jno] == CurrentSegment.P[ino])
              {
                rotate = Rotation(Points[CurrentSegment.P[ino]] - Points[CurrentSegment.P[!ino]],
                                  Points[RoadSegments[j].P[!jno]] - Points[CurrentSegment.P[ino]]);
                actcos =
                    (Points[CurrentSegment.P[ino]] -  Points[CurrentSegment.P[!ino]]).Normalizing() &
                    (Points[RoadSegments[j].P[!jno]] - Points[CurrentSegment.P[ino]]).Normalizing();
                if (fabs(fabs(actcos) - 1) < 0.001)
                  rotate = 0;
                if (rotate == 0)
                {
                  straight[ino] = j;
                  straightno[ino] = jno;
                  continue;
                }
                if (rotate > 0 && (max[LEFT][ino] == -1 || actcos < maxcos[LEFT][ino]))
                {
                  max[LEFT][ino] = j;
                  maxno[LEFT][ino] = jno;
                  maxcos[LEFT][ino] = actcos;
                }
                if (rotate > 0 && max[RIGHT][ino] == -1 && straight[ino] == -1 && (min[LEFT][ino] == -1 || actcos > mincos[LEFT][ino]))
                {
                  min[LEFT][ino] = j;
                  minno[LEFT][ino] = jno;
                  mincos[LEFT][ino] = actcos;
                }
                if (rotate < 0 && (max[RIGHT][ino] == -1 || actcos < maxcos[RIGHT][ino]))
                {
                  max[RIGHT][ino] = j;
                  maxno[RIGHT][ino] = jno;
                  maxcos[RIGHT][ino] = actcos;
                }
                if (rotate < 0 && max[LEFT][ino] == -1 && straight[ino] == -1 && (min[RIGHT][ino] == -1 || actcos > mincos[RIGHT][ino]))
                {
                  min[RIGHT][ino] = j;
                  minno[RIGHT][ino] = jno;
                  mincos[RIGHT][ino] = actcos;
                }
              }
            }
        }

        Norm0 =
          vec(Points[CurrentSegment.P[1]].Z - Points[CurrentSegment.P[0]].Z, 0, Points[CurrentSegment.P[0]].X - Points[CurrentSegment.P[1]].X).Normalizing();

        for (INT side = 0; side < 2; side++)
          for (INT no = 0; no < 2; no++)
            if (CurrentSegment.Border[side][no] == -1)
            {
              isneighbour = TRUE, isstraight = FALSE;
              if (max[no == 0 ? !side : side][no] != -1)
                act = max[no == 0 ? !side : side][no], actno = maxno[no == 0 ? !side : side][no],
                RoadSegments[i].Rotation[no] = side * -2 + 1;
              else if (straight[no] != -1)
                act = straight[no], actno = straightno[no], isstraight = TRUE,
                RoadSegments[i].Rotation[no] = 0;
              else if (min[no == 0 ? side : !side][no] != -1)
                act = min[no == 0 ? side : !side][no], actno = minno[no == 0 ? side : !side][no];
              else
                isstraight = TRUE, isneighbour = FALSE;

              if (!isstraight)
              {
                Norm1 =
                  vec(Points[CurrentSegment.P[no]].Z - Points[RoadSegments[act].P[!actno]].Z, 0,
                      Points[RoadSegments[act].P[!actno]].X - Points[CurrentSegment.P[no]].X).Normalizing() * (no == 0 ? 1 : -1);
                Points.push_back(
                  LineIntersectLine(Points[CurrentSegment.P[no]] + Norm0 * HalfWidth * (side == LEFT ? 1 : -1), Points[CurrentSegment.P[1]] - Points[CurrentSegment.P[0]],
                                    Points[CurrentSegment.P[no]] + Norm1 * HalfWidth * (side == LEFT ? 1 : -1), Points[RoadSegments[act].P[!actno]] - Points[CurrentSegment.P[no]])
                );
                Points.push_back(Points[CurrentSegment.P[no]] + (Points.back() - Points[CurrentSegment.P[no]]) / HalfWidth * (HalfWidth + Shoulder));
              }
              else
              {
                Points.push_back(Points[CurrentSegment.P[no]] + Norm0 * HalfWidth * (side == LEFT ? 1 : -1));
                if (isneighbour)
                  Points.push_back(Points[CurrentSegment.P[no]] + Norm0 * (HalfWidth + Shoulder) * (side == LEFT ? 1 : -1));
                else
                  Points.push_back(Points.back() + (Norm0 * (side == LEFT ? 1 : -1) + vec(Norm0.Z, 0, -Norm0.X) * (no == 0 ? 1 : -1)) * Shoulder);
              }
              RoadSegments[i].Border[side][no] = Points.size() - 2;
              RoadSegments[i].Shoulder[side][no] = Points.size() - 1;
              if (isneighbour)
              {
                RoadSegments[i].Neighbour[side][no] = act;

                RoadSegments[act].Border[no == 0 ? side == LEFT ? !actno : actno : side == LEFT ? actno : !actno][actno] = RoadSegments[i].Border[side][no];
                RoadSegments[act].Shoulder[no == 0 ? side == LEFT ? !actno : actno : side == LEFT ? actno : !actno][actno] = RoadSegments[i].Shoulder[side][no];
                RoadSegments[act].Neighbour[no == 0 ? side == LEFT ? !actno : actno : side == LEFT ? actno : !actno][actno] = i;
                RoadSegments[act].Rotation[actno] = actno == no ? -RoadSegments[i].Rotation[no] : RoadSegments[i].Rotation[no];
              }
            }
      }
    } /* End of 'SetRoadSegments' function */

    /* Round road segment function.
     * ARGUMENTS:
     *   - old and new road segments:
     *       std::vector<road_segment> &OldRoadSegments, &NewRoadSegments;
     *   - road segment index:
     *       INT rs;
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, DOUBLE Shoulder;
     * RETURNS: None.
     */
    VOID RoundRoadSegment( std::vector<road_segment> &OldRoadSegments, std::vector<road_segment> &NewRoadSegments,
                           INT rs, DOUBLE HalfWidth, DOUBLE Shoulder )
    {
      for (INT no = 0; no < 2; no++)
        if (OldRoadSegments[rs].IsRounded[no] == 0)
        {
          INT
            nb = OldRoadSegments[rs].Neighbour[LEFT][no],
            nbno =
              OldRoadSegments[rs].P[no] == OldRoadSegments[nb].P[no] ? no : !no;
          OldRoadSegments[nb].IsRounded[nbno] = 1;
          INT nr, nrno, fr, frno;
          if (OldRoadSegments[rs].HalfLen < OldRoadSegments[nb].HalfLen)
            nr = rs, nrno = no, fr = nb, frno = nbno;
          else
            nr = nb, nrno = nbno, fr = rs, frno = no;
          vec
            p0 =
              Points[OldRoadSegments[nr].C],
            p1 =
              Points[OldRoadSegments[fr].C] +
              (Points[OldRoadSegments[fr].P[frno]] - Points[OldRoadSegments[fr].C]).Normalize() *
              (OldRoadSegments[fr].HalfLen - OldRoadSegments[nr].HalfLen),
            n =
              vec(Points[OldRoadSegments[nr].P[1]].Z - Points[OldRoadSegments[nr].P[0]].Z, 0,
                  Points[OldRoadSegments[nr].P[0]].X - Points[OldRoadSegments[nr].P[1]].X).Normalize(),
            o =
              LineIntersectLine(Points[OldRoadSegments[nr].P[nrno]],
                                Points[OldRoadSegments[nr].Shoulder[RIGHT][nrno]] - Points[OldRoadSegments[nr].Shoulder[LEFT][nrno]],
                                p0, n),
            r0 = p0 - o,
            r1 = p1 - o;
          DOUBLE angle = tsg::Rad2Deg(acos(r0.Normalizing() & r1.Normalizing())) * Rotation(r0, r1);
          INT num = max(fabs(angle) / MaxTurnAngle, 2);
          angle /= num;

          r0.RotateY(angle);
          Points.push_back(o + r0);
          NewRoadSegments.push_back(road_segment(OldRoadSegments[nr].C, Points.size() - 1));
          for (INT i = 2; i < num; i++)
          {
            r0.RotateY(angle);
            Points.push_back(o + r0);
            NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
          }
          Points.push_back(o + r1);
          NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));

          INT P = Points.size() - 1;
          DOUBLE L = OldRoadSegments[fr].HalfLen - OldRoadSegments[nr].HalfLen;
          num = max(L / MaxRoadLen, 1);
          if (num == 1)
            NewRoadSegments.push_back(road_segment(P, OldRoadSegments[fr].C));
          else
          {
            vec
              p = Points[P],
              len =
                (Points[OldRoadSegments[fr].P[!frno]] - Points[OldRoadSegments[fr].P[frno]]).Normalize() * L / num;
            Points.push_back(p + len);
            NewRoadSegments.push_back(road_segment(P, Points.size() - 1));
            for (INT i = 2; i < num; i++)
            {
              Points.push_back(p + (len * i));
              NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
            }
            NewRoadSegments.push_back(road_segment(Points.size() - 1, OldRoadSegments[fr].C));
          }
        }
        else if (OldRoadSegments[rs].IsRounded[no] == -1)
        {
          INT num = max(OldRoadSegments[rs].HalfLen / MaxRoadLen, 1);
          if (num == 1)
            NewRoadSegments.push_back(road_segment(OldRoadSegments[rs].P[no], OldRoadSegments[rs].C));
          else
          {
            vec
              p =
                Points[OldRoadSegments[rs].C] +
                (Points[OldRoadSegments[rs].P[no]] - Points[OldRoadSegments[rs].C]).Normalize() * OldRoadSegments[rs].HalfLen,
              len =
                (Points[OldRoadSegments[rs].P[!no]] - Points[OldRoadSegments[rs].P[no]]).Normalize() *
                OldRoadSegments[rs].HalfLen / num;
            Points.push_back(p + len);
            NewRoadSegments.push_back(road_segment(OldRoadSegments[rs].P[no], Points.size() - 1));
            for (INT i = 2; i < num; i++)
            {
              Points.push_back(p + (len * i));
              NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
            }
            NewRoadSegments.push_back(road_segment(Points.size() - 1, OldRoadSegments[rs].C));
          }
        }
    } /* End of 'RoundRoadSegment' function */

    /* Round road segments function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, DOUBLE Shoulder;
     * RETURNS: None.
     */
    VOID RoundRoadSegments( std::vector<road_segment> &RoadSegments, DOUBLE HalfWidth, DOUBLE Shoulder )
    {
      for (INT rs = 0; rs < RoadSegments.size(); rs++)
      {
        vec norm =
          vec(Points[RoadSegments[rs].P[1]].Z - Points[RoadSegments[rs].P[0]].Z, 0,
              Points[RoadSegments[rs].P[0]].X - Points[RoadSegments[rs].P[1]].X).Normalize() * (HalfWidth + Shoulder);
        vec c[2];
        for (INT no = 0; no < 2; no++)
        {
          vec str[2];
          str[LEFT] = Points[RoadSegments[rs].Shoulder[LEFT][no]] - (Points[RoadSegments[rs].P[!no]] + norm);
          str[RIGHT] = Points[RoadSegments[rs].Shoulder[RIGHT][no]] - (Points[RoadSegments[rs].P[!no]] - norm);
          if (str[LEFT].Length2D() < str[RIGHT].Length2D())
            c[no] = Points[RoadSegments[rs].P[!no]] + str[LEFT];
          else
            c[no] = Points[RoadSegments[rs].P[!no]] + str[RIGHT];

          if (RoadSegments[rs].Neighbour[LEFT][no] == -1 ||
              RoadSegments[rs].Neighbour[LEFT][no] != RoadSegments[rs].Neighbour[RIGHT][no])
            RoadSegments[rs].IsRounded[no] = -1;
          else
            RoadSegments[rs].IsRounded[no] = 0;
        }
        RoadSegments[rs].HalfLen = (c[1] - c[0]).Length2D() / 2;
        RoadSegments[rs].C = Points.size();
        Points.push_back((c[0] + c[1]) / 2);
      }

      std::vector<road_segment> NewRoadSegments;
      for (INT rs = 0; rs < RoadSegments.size(); rs++)
        RoundRoadSegment(RoadSegments, NewRoadSegments, rs, HalfWidth, Shoulder);
      RoadSegments = NewRoadSegments;
    } /* End of 'RoundRoadSegments' function */

    /* Interpolate road segment function.
     * ARGUMENTS:
     *   - old and new road segments:
     *       std::vector<road_segment> &OldRoadSegments, &NewRoadSegments;
     *   - road segment index:
     *       INT rs;
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, DOUBLE Shoulder;
     * RETURNS: None.
     */
    VOID InterpolateRoadSegment( std::vector<road_segment> &OldRoadSegments, std::vector<road_segment> &NewRoadSegments,
                                 INT rs, DOUBLE HalfWidth, DOUBLE Shoulder )
    {
      if (OldRoadSegments[rs].Neighbour[LEFT][0] != -1 && OldRoadSegments[rs].Neighbour[LEFT][0] == OldRoadSegments[rs].Neighbour[RIGHT][0] &&
          OldRoadSegments[rs].Neighbour[LEFT][1] != -1 && OldRoadSegments[rs].Neighbour[LEFT][1] == OldRoadSegments[rs].Neighbour[RIGHT][1] &&
          OldRoadSegments[rs].Rotation[0] != OldRoadSegments[rs].Rotation[1])
      {
        INT
          rot0 = OldRoadSegments[rs].Rotation[0], rot1 = OldRoadSegments[rs].Rotation[1],
          nb0 = OldRoadSegments[rs].Neighbour[LEFT][0], nb1 = OldRoadSegments[rs].Neighbour[LEFT][1];
        vec
          p0(Points[OldRoadSegments[nb0].P[0] == OldRoadSegments[rs].P[0] ? OldRoadSegments[nb0].P[1] : OldRoadSegments[nb0].P[0]]),
          p1(Points[OldRoadSegments[rs].P[0]]),
          p2(Points[OldRoadSegments[rs].P[1]]),
          p3(Points[OldRoadSegments[nb1].P[1] == OldRoadSegments[rs].P[1] ? OldRoadSegments[nb1].P[0] : OldRoadSegments[nb1].P[1]]);
        interpolation I(p0, p1, p2, p3);
        vec norm(I.Normal());

        INT num = max((INT)((Points[OldRoadSegments[rs].P[1]] - Points[OldRoadSegments[rs].P[0]]).Length2D() / MaxRoadLen / 2), 1);
        if (num == 1)
        {
          NewRoadSegments.push_back(road_segment(OldRoadSegments[rs].P[0], OldRoadSegments[rs].P[1]));
          return;
        }

        vec
          dir((Points[OldRoadSegments[rs].P[1]] - Points[OldRoadSegments[rs].P[0]]).Normalize()),
          norm0((Points[OldRoadSegments[rs].Border[LEFT][0]] - Points[OldRoadSegments[rs].Border[RIGHT][0]]).Normalize()),
          norm1((Points[OldRoadSegments[rs].Border[LEFT][1]] - Points[OldRoadSegments[rs].Border[RIGHT][1]]).Normalize()),
          c((Points[OldRoadSegments[rs].P[0]] + Points[OldRoadSegments[rs].P[1]]) / 2);
        DOUBLE
          len0 = (c + norm * (HalfWidth + Shoulder) * rot0 - Points[OldRoadSegments[rs].Shoulder[rot0 == 1 ? LEFT : RIGHT][0]]).Length2D(),
          len1 = (c + norm * (HalfWidth + Shoulder) * rot1 - Points[OldRoadSegments[rs].Shoulder[rot1 == 1 ? LEFT : RIGHT][1]]).Length2D();
        INT P0 = OldRoadSegments[rs].P[0], P1 = OldRoadSegments[rs].P[1], C = Points.size();
        Points.push_back(c);

        // First part.
        p1 = Points[P0] + norm0 * (HalfWidth + Shoulder) * rot0;
        p0 = p1 + dir * tsg::TMatr<DBL>().SetRotate(180, norm0) * len0;
        p2 = c + norm * (HalfWidth + Shoulder) * rot0;
        p3 = p2 - dir * tsg::TMatr<DBL>().SetRotate(180, norm) * len0;

        I = interpolation(p0, p1, p2, p3);
        
        DOUBLE t, first = -1, second = -1;
        for (INT i = 1; i <= num; i++)
        {
          first = i == 1 ? P0 : second;
          second = i == num ? C : Points.size();
          if (i != num)
          {
            t = I.t1 + (I.t2 - I.t1) * i / num;
            Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot0);
          }

          DOUBLE
            t1 = I.t1 + (I.t2 - I.t1) * (i - 1) / num,
            t2 = I.t1 + (I.t2 - I.t1) * i / num;
          vec n0(I.Normal(t1)), n1(I.Normal(t2)); 
          DOUBLE angle = tsg::Rad2Deg(acos(min(0.999, max(-0.999, n0 & n1))));
          INT anum = angle < MaxTurnAngle ? 1 : ceil(angle / MaxTurnAngle);
          if (anum == 1)
            NewRoadSegments.push_back(road_segment(first, second));
          else
          {
            t = t1 + (t2 - t1) / anum;
            Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot0);
            NewRoadSegments.push_back(road_segment(first, Points.size() - 1));
            for (INT j = 2; j < anum; j++)
            {
              t = t1 + (t2 - t1) * j / anum;
              Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot0);
              NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
            }
            NewRoadSegments.push_back(road_segment(Points.size() - 1, second));
          }
        }

        // Second part.
        p1 = Points[P1] + norm1 * (HalfWidth + Shoulder) * rot1;
        p0 = p1 - dir * tsg::TMatr<DBL>().SetRotate(180, norm1) * len1;
        p2 = c + norm * (HalfWidth + Shoulder) * rot1;
        p3 = p2 + dir * tsg::TMatr<DBL>().SetRotate(180, norm) * len1;
        
        I = interpolation(p0, p1, p2, p3);
        
        for (INT i = 1; i <= num; i++)
        {
          first = i == 1 ? P1 : second;
          second = i == num ? C : Points.size();
          if (i != num)
          {
            t = I.t1 + (I.t2 - I.t1) * i / num;
            Points.push_back(I(t) + I.Normal(t) * (HalfWidth + Shoulder) * rot1);
          }
        
          DOUBLE
            t1 = I.t1 + (I.t2 - I.t1) * (i - 1) / num,
            t2 = I.t1 + (I.t2 - I.t1) * i / num;
          vec n0(I.Normal(t1)), n1(I.Normal(t2)); 
          DOUBLE angle = tsg::Rad2Deg(acos(min(0.999, max(-0.999, n0 & n1))));
          INT anum = angle < MaxTurnAngle ? 1 : ceil(angle / MaxTurnAngle);
          if (anum == 1)
            NewRoadSegments.push_back(road_segment(first, second));
          else
          {
            t = t1 + (t2 - t1) / anum;
            Points.push_back(I(t) + I.Normal(t) * (HalfWidth + Shoulder) * rot1);
            NewRoadSegments.push_back(road_segment(first, Points.size() - 1));
            for (INT j = 2; j < anum; j++)
            {
              t = t1 + (t2 - t1) * j / anum;
              Points.push_back(I(t) + I.Normal(t) * (HalfWidth + Shoulder) * rot1);
              NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
            }
            NewRoadSegments.push_back(road_segment(Points.size() - 1, second));
          }
        }
      }
      else
      {
        INT num = max((INT)((Points[OldRoadSegments[rs].P[1]] - Points[OldRoadSegments[rs].P[0]]).Length2D() / MaxRoadLen), 1);
        if (num == 1)
        {
          NewRoadSegments.push_back(road_segment(OldRoadSegments[rs].P[0], OldRoadSegments[rs].P[1]));
          return;
        }

        INT rot = 1;
        if (OldRoadSegments[rs].Neighbour[LEFT][0] == OldRoadSegments[rs].Neighbour[RIGHT][0] &&
            OldRoadSegments[rs].Neighbour[LEFT][0] != -1 && OldRoadSegments[rs].Rotation[0] != 0)
          rot = OldRoadSegments[rs].Rotation[0];
        else if (OldRoadSegments[rs].Neighbour[LEFT][1] == OldRoadSegments[rs].Neighbour[RIGHT][1] &&
                 OldRoadSegments[rs].Neighbour[LEFT][1] != -1 && OldRoadSegments[rs].Rotation[1] != 0)
          rot = OldRoadSegments[rs].Rotation[1];
        vec
          dir = (Points[OldRoadSegments[rs].P[1]] - Points[OldRoadSegments[rs].P[0]]).Normalize(),
          norm(dir.Z, 0, -dir.X),
          norm0((Points[OldRoadSegments[rs].Border[LEFT][0]] - Points[OldRoadSegments[rs].Border[RIGHT][0]]).Normalize()),
          norm1((Points[OldRoadSegments[rs].Border[LEFT][1]] - Points[OldRoadSegments[rs].Border[RIGHT][1]]).Normalize()),
          p0, p1, p2, p3;
        DOUBLE len =
          rot == 1 ? (Points[OldRoadSegments[rs].P[1]] + norm1 * (HalfWidth + Shoulder) -
                      Points[OldRoadSegments[rs].P[0]] - norm0 * (HalfWidth + Shoulder)).Length2D() :
                     (Points[OldRoadSegments[rs].P[1]] - norm1 * (HalfWidth + Shoulder) -
                      Points[OldRoadSegments[rs].P[0]] + norm0 * (HalfWidth + Shoulder)).Length2D();
        INT P0, P1;
        if (OldRoadSegments[rs].Neighbour[LEFT][0] != OldRoadSegments[rs].Neighbour[RIGHT][0])
        {
          if ((Points[OldRoadSegments[rs].P[1]] - (Points[OldRoadSegments[rs].Shoulder[LEFT][0]] -  norm * (HalfWidth + Shoulder))).Length2D() <
              (Points[OldRoadSegments[rs].P[1]] - (Points[OldRoadSegments[rs].Shoulder[RIGHT][0]] + norm * (HalfWidth + Shoulder))).Length2D())
            Points.push_back(Points[OldRoadSegments[rs].Shoulder[LEFT][0]] - norm * (HalfWidth + Shoulder) + dir * MaxRoadLen);
          else
            Points.push_back(Points[OldRoadSegments[rs].Shoulder[RIGHT][0]] + norm * (HalfWidth + Shoulder) + dir * MaxRoadLen);
          P0 = Points.size() - 1;
          NewRoadSegments.push_back(road_segment(OldRoadSegments[rs].P[0], P0));
        }
        else
          P0 = OldRoadSegments[rs].P[0];

        if (OldRoadSegments[rs].Neighbour[LEFT][1] != OldRoadSegments[rs].Neighbour[RIGHT][1])
        {
          if ((Points[OldRoadSegments[rs].P[0]] - (Points[OldRoadSegments[rs].Shoulder[LEFT][1]] -  norm * (HalfWidth + Shoulder))).Length2D() <
              (Points[OldRoadSegments[rs].P[0]] - (Points[OldRoadSegments[rs].Shoulder[RIGHT][1]] + norm * (HalfWidth + Shoulder))).Length2D())
            Points.push_back(Points[OldRoadSegments[rs].Shoulder[LEFT][1]] - norm * (HalfWidth + Shoulder) - dir * MaxRoadLen);
          else
            Points.push_back(Points[OldRoadSegments[rs].Shoulder[RIGHT][1]] + norm * (HalfWidth + Shoulder) - dir * MaxRoadLen);
          P1 = Points.size() - 1;
          NewRoadSegments.push_back(road_segment(P1, OldRoadSegments[rs].P[1]));
        }
        else
          P1 = OldRoadSegments[rs].P[1];


        if (OldRoadSegments[rs].Neighbour[LEFT][0] != OldRoadSegments[rs].Neighbour[RIGHT][0] ||
            OldRoadSegments[rs].Neighbour[LEFT][0] == -1)
        {
          p1 = Points[P0] + norm * (HalfWidth + Shoulder) * rot;
          p0 = p1 - dir * len;
        }
        else
        {
          p1 = Points[P0] + norm0 * (HalfWidth + Shoulder) * rot;
          p0 = p1 + dir * tsg::TMatr<DBL>().SetRotate(180, norm0) * len;
        }
        if (OldRoadSegments[rs].Neighbour[LEFT][1] != OldRoadSegments[rs].Neighbour[RIGHT][1] ||
            OldRoadSegments[rs].Neighbour[LEFT][1] == -1)
        {
          p2 = Points[P1] + norm * (HalfWidth + Shoulder) * rot;
          p3 = p2 + dir * len;
        }
        else
        {
          p2 = Points[P1] + norm1 * (HalfWidth + Shoulder) * rot;
          p3 = p2 - dir * tsg::TMatr<DBL>().SetRotate(180, norm1) * len;
        }

        interpolation I(p0, p1, p2, p3);
        
        DOUBLE t, first = -1, second = -1;
        for (INT i = 1; i <= num; i++)
        {
          first = i == 1 ? P0 : second;
          second = i == num ? P1 : Points.size();
          if (i != num)
          {
            t = I.t1 + (I.t2 - I.t1) * i / num;
            Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot);
          }

          DOUBLE
            t1 = I.t1 + (I.t2 - I.t1) * (i - 1) / num,
            t2 = I.t1 + (I.t2 - I.t1) * i / num;
          vec n0(I.Normal(t1)), n1(I.Normal(t2)); 

          DOUBLE angle = tsg::Rad2Deg(acos(min(0.999, max(-0.999, n0 & n1))));
          INT anum = angle < MaxTurnAngle ? 1 : angle / MaxTurnAngle;
          if (anum == 1)
            NewRoadSegments.push_back(road_segment(first, second));
          else
          {
            t = t1 + (t2 - t1) / anum;
            Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot);
            NewRoadSegments.push_back(road_segment(first, Points.size() - 1));
            for (INT j = 2; j < anum; j++)
            {
              t = t1 + (t2 - t1) * j / anum;
              Points.push_back(I(t) - I.Normal(t) * (HalfWidth + Shoulder) * rot);
              NewRoadSegments.push_back(road_segment(Points.size() - 2, Points.size() - 1));
            }
            NewRoadSegments.push_back(road_segment(Points.size() - 1, second));
          }
        }
      }
    } /* End of 'InterpolateRoadSegment' function */

    /* Interpolate road segments function.                             
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, DOUBLE Shoulder;
     * RETURNS: None.
     */
    VOID InterpolateRoadSegments( std::vector<road_segment> &RoadSegments, DOUBLE HalfWidth, DOUBLE Shoulder )
    {
      std::vector<road_segment> NewRoadSegments;
      for (INT rs = 0; rs < RoadSegments.size(); rs++)
        InterpolateRoadSegment(RoadSegments, NewRoadSegments, rs, HalfWidth, Shoulder);
      RoadSegments = NewRoadSegments;
    } /* End of 'InterpolateRoadSegments' function */

    /* Cut triangle function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road segment and triangle indices:
     *       INT rs, tr;
     *   - road segment side:
     *       INT side;
     *   - neighbour and neighbour side to fill:
     *       INT &neighbour, &neighbourside;
     * RETURNS:
     *   (BOOL) TRUE if intersect, FALSE otherwise.
     */
    BOOL RoadCutTriangle( std::vector<road_segment> &RoadSegments, INT rs, INT tr, INT side,
                          BOOL &ToContinue, std::vector<INT> &SidePoints, INT &InSide, INT &OutSide,
                          std::vector<INT> &RoadPoints )
    {
      ToContinue = TRUE;

      SidePoints.clear();
      RoadPoints.clear();
      InSide = OutSide = -1;

      BOOL cross = FALSE;
      INT niside = -1;

      if (side == END_0 || side == END_1)
      {
        INT sm = 0;
        for (INT k = 0; k < 3; k++)
        {
          if (RoadSegments[rs].Shoulder[LEFT][side - 2] == Triangles[tr].P[k])
            sm++, niside = k;
          if (RoadSegments[rs].Shoulder[RIGHT][side - 2] == Triangles[tr].P[k])
            sm++, niside = k;
          for (INT j = 0; j < RoadSegments[rs].Intersections[side].size(); j++)
            if (RoadSegments[rs].Intersections[side][j].Index == Triangles[tr].P[k])
              sm++, niside = k;
        }
        if (sm > 1)
          return FALSE;

        if (RoadSegments[rs].Neighbour[LEFT][side - END_0] == -1)
          for (INT k = 0; k < 3; k++)
          {
            if (k == niside && !SegmentTestSegment(Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]], Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]],
                                                   Points[Triangles[tr].P[(niside + 1) % 3]], Points[Triangles[tr].P[(niside + 2) % 3]]))
              continue;
            else if ((k + 1) % 3 == niside)
              continue;
            if (SegmentTestSegmentInc(Points[Triangles[tr].P[k]], Points[Triangles[tr].P[(k + 1) % 3]],
                                   Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]], Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]]))
            {
              Points.push_back(LineIntersectLine(Points[Triangles[tr].P[k]],
                                                 Points[Triangles[tr].P[(k + 1) % 3]] - Points[Triangles[tr].P[k]],
                                                 Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]],
                                                 Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]] - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]));
              RoadSegments[rs].Intersections[side].push_back(
                intersection((Points.back() - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]).Length2D() /
                             (Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]] - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]).Length2D(), Points.size() - 1)
              );
              for (INT n = k + 1; n < 3; n++)
              {
                if (n == niside && !SegmentTestSegment(Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]], Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]],
                                                       Points[Triangles[tr].P[(niside + 1) % 3]], Points[Triangles[tr].P[(niside + 2) % 3]]))
                  continue;
                else if ((n + 1) % 3 == niside)
                  continue;
                if (SegmentTestSegmentInc(Points[Triangles[tr].P[n]], Points[Triangles[tr].P[(n + 1) % 3]],
                                       Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]], Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]]))
                {
                  Points.push_back(LineIntersectLine(Points[Triangles[tr].P[n]],
                                                     Points[Triangles[tr].P[(n + 1) % 3]] - Points[Triangles[tr].P[n]],
                                                     Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]],
                                                     Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]] - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]));
                  RoadSegments[rs].Intersections[side].push_back(
                    intersection((Points.back() - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]).Length2D() /
                                 (Points[RoadSegments[rs].Shoulder[RIGHT][side - END_0]] - Points[RoadSegments[rs].Shoulder[LEFT][side - END_0]]).Length2D (), Points.size() - 1)
                  );
                  INT p0, p1;
                  if (RoadSegments[rs].Intersections[side][RoadSegments[rs].Intersections[side].size() - 2].t <
                      RoadSegments[rs].Intersections[side][RoadSegments[rs].Intersections[side].size() - 1].t)
                    p0 = side == END_0 ? Points.size() - 1 : Points.size() - 2, p1 = side == END_0 ? Points.size() - 2 : Points.size() - 1;
                  else
                    p0 = side == END_0 ? Points.size() - 2 : Points.size() - 1, p1 = side == END_0 ? Points.size() - 1 : Points.size() - 2;
                  if (Rotation(Points[RoadSegments[rs].Shoulder[side - END_0][side - END_0]] - Points[RoadSegments[rs].Shoulder[!(side - END_0)][side - END_0]],
                               Points[Triangles[tr].P[k]] - Points[RoadSegments[rs].Shoulder[!(side - END_0)][side - END_0]]) > 0)
                  {
                    Triangles.push_back(triangle(p0, p1, Triangles[tr].P[k]));
                    if (n == k + 1)
                      Triangles.push_back(triangle(p1, Triangles[tr].P[(n + 1) % 3], Triangles[tr].P[k]));
                  }
                  else
                  {
                    Triangles.push_back(triangle(p0, p1, Triangles[tr].P[(k + 1) % 3]));
                    if (n == k + 2)
                      Triangles.push_back(triangle(p0, Triangles[tr].P[(k + 1) % 3], Triangles[tr].P[n]));
                  }
                  return TRUE;
                }
              }
            }
          }
        return FALSE;
      }

      INT sm = 0;
      for (INT k = 0; k < 3; k++)
      {
        if (RoadSegments[rs].Shoulder[side][0] == Triangles[tr].P[k])
          sm++, niside = k;
        if (RoadSegments[rs].Shoulder[side][1] == Triangles[tr].P[k])
          sm++, niside = k;
        for (INT j = 0; j < RoadSegments[rs].Intersections[side].size(); j++)
          if (RoadSegments[rs].Intersections[side][j].Index == Triangles[tr].P[k])
            sm++, niside = k;
      }
      if (sm > 1)
        return FALSE;

      for (INT k = 0; k < 3; k++)
      {
        if (k == niside && !SegmentTestSegment(Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]],
                                               Points[Triangles[tr].P[(niside + 1) % 3]], Points[Triangles[tr].P[(niside + 2) % 3]]))
          continue;
        else if ((k + 1) % 3 == niside)
          continue;
        if (SegmentTestSegmentInc(Points[Triangles[tr].P[k]], Points[Triangles[tr].P[(k + 1) % 3]],
                                  Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]]))
        {
          InSide = k;
          Points.push_back(LineIntersectLine(Points[Triangles[tr].P[k]], Points[Triangles[tr].P[(k + 1) % 3]] - Points[Triangles[tr].P[k]],
                                             Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]] - Points[RoadSegments[rs].Shoulder[side][0]]));
          RoadSegments[rs].Intersections[side].push_back(
            intersection((Points.back() - Points[RoadSegments[rs].Shoulder[side][0]]).Length2D() /
                          (Points[RoadSegments[rs].Shoulder[side][1]] - Points[RoadSegments[rs].Shoulder[side][0]]).Length2D(), Points.size() - 1)
          );
          for (INT n = k + 1; n < 3; n++)
          {
            if (n == niside && !SegmentTestSegment(Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]],
                                               Points[Triangles[tr].P[(niside + 1) % 3]], Points[Triangles[tr].P[(niside + 2) % 3]]))
              continue;
            else if ((n + 1) % 3 == niside)
              continue;
            if (SegmentTestSegmentInc(Points[Triangles[tr].P[n]], Points[Triangles[tr].P[(n + 1) % 3]],
                                      Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]]))
            {
              Points.push_back(LineIntersectLine(Points[Triangles[tr].P[n]], Points[Triangles[tr].P[(n + 1) % 3]] - Points[Triangles[tr].P[n]],
                                                 Points[RoadSegments[rs].Shoulder[side][0]], Points[RoadSegments[rs].Shoulder[side][1]] - Points[RoadSegments[rs].Shoulder[side][0]]));
              RoadSegments[rs].Intersections[side].push_back(
                intersection((Points.back() - Points[RoadSegments[rs].Shoulder[side][0]]).Length2D() /
                             (Points[RoadSegments[rs].Shoulder[side][1]] - Points[RoadSegments[rs].Shoulder[side][0]]).Length2D(), Points.size() - 1)
              );
              INT p0, p1, s0, s1;
              if (RoadSegments[rs].Intersections[side][RoadSegments[rs].Intersections[side].size() - 2].t <
                  RoadSegments[rs].Intersections[side][RoadSegments[rs].Intersections[side].size() - 1].t)
              {
                p0 = side == LEFT ? Points.size() - 2 : Points.size() - 1, p1 = side == LEFT ? Points.size() - 1 : Points.size() - 2;
                s0 = side == LEFT ? k : n, s1 = side == LEFT ? n : k;
              }
              else
              {
                p0 = side == LEFT ? Points.size() - 1 : Points.size() - 2, p1 = side == LEFT ? Points.size() - 2 : Points.size() - 1;
                s0 = side == LEFT ? n : k, s1 = side == LEFT ? k : n;
              }
              if (Rotation(Points[RoadSegments[rs].Shoulder[side][!side]] - Points[RoadSegments[rs].Shoulder[side][side]],
                           Points[Triangles[tr].P[k]] - Points[RoadSegments[rs].Shoulder[side][side]]) > 0)
              {
                Triangles.push_back(triangle(p0, p1, Triangles[tr].P[k]));

                RoadPoints.push_back(p1);
                RoadPoints.push_back(p0);
                RoadPoints.push_back(Triangles[tr].P[(k + 1) % 3]);

                if (n == k + 1)
                  Triangles.push_back(triangle(p1, Triangles[tr].P[(n + 1) % 3], Triangles[tr].P[k]));
                else
                  RoadPoints.push_back(Triangles[tr].P[n]);
              }
              else
              {
                Triangles.push_back(triangle(p0, p1, Triangles[tr].P[(k + 1) % 3]));

                RoadPoints.push_back(p1);
                RoadPoints.push_back(p0);
                RoadPoints.push_back(Triangles[tr].P[(n + 1) % 3]);

                if (n == k + 2)
                  Triangles.push_back(triangle(p0, Triangles[tr].P[(k + 1) % 3], Triangles[tr].P[n]));
                else
                  RoadPoints.push_back(Triangles[tr].P[k]);
              }

              INT nbno =
                PointTestTriangle(Points[RoadSegments[rs].Shoulder[side][0]],
                                  Points[Triangles[tr].P[0]], Points[Triangles[tr].P[1]], Points[Triangles[tr].P[2]]) ? 0 : 1;
              if (nbno != -1 && PointTestTriangle(Points[RoadSegments[rs].Shoulder[!side][nbno]],
                                                  Points[Triangles[tr].P[0]],
                                                  Points[Triangles[tr].P[1]],
                                                  Points[Triangles[tr].P[2]]))
              {
                SidePoints.push_back(side == LEFT ? nbno == 0 ? p0 : p1 : nbno == 0 ? p1 : p0);
                OutSide = side == LEFT ? nbno == 0 ? s0 : s1 : nbno == 0 ? s1 : s0;
              }
              return TRUE;
            }
          }

          INT
            nbno =
              PointTestTriangle(Points[RoadSegments[rs].Shoulder[side][0]],
                                Points[Triangles[tr].P[0]], Points[Triangles[tr].P[1]], Points[Triangles[tr].P[2]]) ? 0 : 1,
            cur = rs, curside = side, curnbno = nbno,
            next = RoadSegments[cur].Neighbour[curside][curnbno],
            nextside = next == -1 ? -1 : RoadSegments[cur].P[curnbno] == RoadSegments[next].P[curnbno] ? !curside : curside;

          std::vector<INT> Polygon;
          Polygon.push_back(Points.size() - 1);
          Polygon.push_back(RoadSegments[cur].Shoulder[curside][curnbno]);

          if (!cross && RoadSegments[cur].Neighbour[curside][curnbno] != RoadSegments[cur].Neighbour[!curside][curnbno])
            cross = TRUE;

          if (!cross && !PointTestTriangle(Points[RoadSegments[cur].Shoulder[!curside][curnbno]],
            Points[Triangles[tr].P[0]], Points[Triangles[tr].P[1]], Points[Triangles[tr].P[2]]))
            cross = TRUE;

          if (cross)
            SidePoints.push_back(RoadSegments[cur].Shoulder[curside][curnbno]);

          while (1)
          {
            if (next == rs)
              ToContinue = FALSE;
            if (next != -1)
            {
              for (INT n = 0; n < 3; n++)
              {
                if (SegmentTestSegmentInc(Points[Triangles[tr].P[n]], Points[Triangles[tr].P[(n + 1) % 3]],
                                          Points[RoadSegments[next].Shoulder[nextside][0]],
                                          Points[RoadSegments[next].Shoulder[nextside][1]]))
                {
                  Points.push_back(LineIntersectLine(Points[Triangles[tr].P[n]],
                                                     Points[Triangles[tr].P[(n + 1) % 3]] - Points[Triangles[tr].P[n]],
                                                     Points[RoadSegments[next].Shoulder[nextside][0]],
                                                     Points[RoadSegments[next].Shoulder[nextside][1]] -
                                                     Points[RoadSegments[next].Shoulder[nextside][0]]));
                  RoadSegments[next].Intersections[nextside].push_back(
                    intersection((Points.back() - Points[RoadSegments[next].Shoulder[nextside][0]]).Length2D() /
                                 (Points[RoadSegments[next].Shoulder[nextside][1]] -
                                  Points[RoadSegments[next].Shoulder[nextside][0]]).Length2D(), Points.size() - 1));
                  Polygon.push_back(Points.size() - 1);

                  if (cross || PointTestTriangle(Points[RoadSegments[next].Shoulder[!nextside][nextside == side ? nbno : !nbno]],
                                                 Points[Triangles[tr].P[0]], Points[Triangles[tr].P[1]], Points[Triangles[tr].P[2]]))
                  {
                    SidePoints.push_back(Points.size() - 1);
                    OutSide = n;
                  }
                  RoadPoints = Polygon;
                  if (n == k)
                  {
                    INT nr, fr;
                    if ((Points[Triangles[tr].P[k]] - Points[Points.size() - 1]).Length2D() <
                        (Points[Triangles[tr].P[k]] - Points[Points.size() - 2]).Length2D())
                      nr = Points.size() - 1, fr = nr - 1;
                    else
                      nr = Points.size() - 2, fr = nr + 1;

                    if (side == nbno && nr > fr)
                      for (INT trs = n, i = 0; i < 3; trs = (trs + 3 - 1) % 3, i++)
                        Polygon.push_back(Triangles[tr].P[trs]);
                    else if (side != nbno && nr < fr)
                      for (INT trs = (n + 1) % 3, i = 0; i < 3; trs = (trs + 1) % 3, i++)
                        Polygon.push_back(Triangles[tr].P[trs]);

                    else if (side == nbno && nr < fr)
                      for (INT trs = (n + 1) % 3, i = 0; i < 3; trs = (trs + 1) % 3, i++)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    if (side != nbno && nr > fr)
                      for (INT trs = n, i = 0; i < 3; trs = (trs + 3 - 1) % 3, i++)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                  }
                  else
                  {
                    if (side == nbno)
                    {
                      for (INT trs = n; trs != k; trs = (trs + 3 - 1) % 3)
                        Polygon.push_back(Triangles[tr].P[trs]);
                      for (INT trs = (n + 1) % 3; trs != (k + 1) % 3; trs = (trs + 1) % 3)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    }
                    else
                    {
                      for (INT trs = (n + 1) % 3; trs != (k + 1) % 3; trs = (trs + 1) % 3)
                        Polygon.push_back(Triangles[tr].P[trs]);
                      for (INT trs = n; trs != k; trs = (trs + 3 - 1) % 3)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    }
                  }
                  TriangulateConst(Points, Polygon, Triangles);
                  return TRUE;
                }
              }
              cur = next;
              curside = nextside;
              curnbno = curside == side ? nbno : !nbno;
              next = RoadSegments[cur].Neighbour[curside][curnbno],
              nextside = next == -1 ? -1 : RoadSegments[cur].P[curnbno] == RoadSegments[next].P[curnbno] ? !curside : curside;

              Polygon.push_back(RoadSegments[cur].Shoulder[curside][curnbno]);

              if (!cross && RoadSegments[cur].Neighbour[curside][curnbno] != RoadSegments[cur].Neighbour[!curside][curnbno])
                cross = TRUE;

              if (!cross && !PointTestTriangle(Points[RoadSegments[cur].Shoulder[!curside][curnbno]],
                                              Points[Triangles[tr].P[0]], Points[Triangles[tr].P[1]], Points[Triangles[tr].P[2]]))
                cross = TRUE;

              if (cross)
                SidePoints.push_back(RoadSegments[cur].Shoulder[curside][curnbno]);
            }
            else
            {
              for (INT n = 0; n < 3; n++)
              {
                if (SegmentTestSegmentInc(Points[Triangles[tr].P[n]], Points[Triangles[tr].P[(n + 1) % 3]],
                                          Points[RoadSegments[cur].Shoulder[LEFT][curnbno]],
                                          Points[RoadSegments[cur].Shoulder[RIGHT][curnbno]]))
                {
                  Points.push_back(LineIntersectLine(Points[Triangles[tr].P[n]],
                                                     Points[Triangles[tr].P[(n + 1) % 3]] - Points[Triangles[tr].P[n]],
                                                     Points[RoadSegments[cur].Shoulder[LEFT][curnbno]],
                                                     Points[RoadSegments[cur].Shoulder[RIGHT][curnbno]] -
                                                     Points[RoadSegments[cur].Shoulder[LEFT][curnbno]]));
                  RoadSegments[cur].Intersections[curnbno + 2].push_back(
                    intersection((Points.back() - Points[RoadSegments[cur].Shoulder[LEFT][curnbno]]).Length2D() /
                                 (Points[RoadSegments[cur].Shoulder[RIGHT][curnbno]] -
                                  Points[RoadSegments[cur].Shoulder[LEFT][curnbno]]).Length2D(), Points.size() - 1));
                  Polygon.push_back(Points.size() - 1);

                  if (cross)
                  {
                    SidePoints.push_back(Points.size() - 1);
                    OutSide = n;
                  }
                  RoadPoints = Polygon;
                  if (n == k)
                  {
                    INT nr, fr;
                    if ((Points[Triangles[tr].P[k]] - Points[Points.size() - 1]).Length2D() <
                      (Points[Triangles[tr].P[k]] - Points[Points.size() - 2]).Length2D())
                      nr = Points.size() - 1, fr = nr - 1;
                    else
                      nr = Points.size() - 2, fr = nr + 1;

                    if (side == nbno && nr > fr)
                      for (INT trs = n, i = 0; i < 3; trs = (trs + 3 - 1) % 3, i++)
                        Polygon.push_back(Triangles[tr].P[trs]);
                    else if (side != nbno && nr < fr)
                      for (INT trs = (n + 1) % 3, i = 0; i < 3; trs = (trs + 1) % 3, i++)
                        Polygon.push_back(Triangles[tr].P[trs]);

                    else if (side == nbno && nr < fr)
                      for (INT trs = (n + 1) % 3, i = 0; i < 3; trs = (trs + 1) % 3, i++)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    if (side != nbno && nr > fr)
                      for (INT trs = n, i = 0; i < 3; trs = (trs + 3 - 1) % 3, i++)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                  }
                  else
                  {
                    if (side == nbno)
                    {
                      for (INT trs = n; trs != k; trs = (trs + 3 - 1) % 3)
                        Polygon.push_back(Triangles[tr].P[trs]);
                      for (INT trs = (n + 1) % 3; trs != (k + 1) % 3; trs = (trs + 1) % 3)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    }
                    else
                    {
                      for (INT trs = (n + 1) % 3; trs != (k + 1) % 3; trs = (trs + 1) % 3)
                        Polygon.push_back(Triangles[tr].P[trs]);
                      for (INT trs = n; trs != k; trs = (trs + 3 - 1) % 3)
                        RoadPoints.push_back(Triangles[tr].P[trs]);
                    }
                  }
                  TriangulateConst(Points, Polygon, Triangles);
                  return TRUE;
                }
              }
              next = cur;
              nextside = !curside;

              Polygon.push_back(RoadSegments[cur].Shoulder[!curside][curnbno]);

              if (cross)
                SidePoints.push_back(RoadSegments[cur].Shoulder[!curside][curnbno]);
            }
          }
        }
      }
      return FALSE;
    } /* End of 'RoadCutTriangle' function */

    /* Insert road function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     * RETURNS: None.
     */
    VOID InsertRoad( std::vector<road_segment> &RoadSegments )
    {
      BOOL intersect[4], ToContinue;
      std::vector<INT> SidePoints[4], RoadPoints[4];
      INT InSide[4], OutSide[4];

      for (INT i = 0, roadsize = RoadSegments.size(); i < roadsize; i++)
        for (INT j = 0, size = Triangles.size(); j < size; j++)
        {
          ToContinue = TRUE;
          intersect[LEFT] = intersect[RIGHT] = intersect[END_0] = intersect[END_1] = FALSE;
          InSide[LEFT] =    InSide[RIGHT] =    OutSide[LEFT] =    OutSide[RIGHT] = -1;
          SidePoints[LEFT].clear(); SidePoints[RIGHT].clear();
          RoadPoints[LEFT].clear(); RoadPoints[RIGHT].clear();

          for (INT side = 0; side < 4; side++)
            if (ToContinue)
              intersect[side] = RoadCutTriangle(RoadSegments, i, j, side, ToContinue,
                                                SidePoints[side], InSide[side], OutSide[side], RoadPoints[side]);
            else
              break;

          if ((intersect[LEFT] || intersect[RIGHT]) && SidePoints[LEFT].size() > 0 && SidePoints[RIGHT].size() > 0)
          {
            INT rotright;
            if (PointTestTriangle(Points[RoadSegments[i].P[0]], Points[Triangles[j].P[0]], Points[Triangles[j].P[1]], Points[Triangles[j].P[2]]))
              rotright = LEFT;
            else
              rotright = RIGHT;

            if (OutSide[rotright] == OutSide[!rotright])
            {
              if ((Points[Triangles[j].P[OutSide[rotright]]] - Points[SidePoints[!rotright].back()]).Length2D() <
                  (Points[Triangles[j].P[OutSide[rotright]]] - Points[SidePoints[rotright].back()]).Length2D())
                for (INT trs = (OutSide[rotright] + 1) % 3, i = 0; i < 3; trs = (trs + 1) % 3, i++)
                  SidePoints[rotright].push_back(Triangles[j].P[trs]);
            }
            else
              for (INT trs = (OutSide[rotright] + 1) % 3; trs != (OutSide[!rotright] + 1) % 3; trs = (trs + 1) % 3)
                SidePoints[rotright].push_back(Triangles[j].P[trs]);

            std::reverse(SidePoints[!rotright].begin(), SidePoints[!rotright].end());
            SidePoints[rotright].insert(SidePoints[rotright].end(), SidePoints[!rotright].begin(), SidePoints[!rotright].end());

            TriangulateConst(Points, SidePoints[rotright], Triangles);
          }

          else if (RoadPoints[LEFT].size() > 0 != RoadPoints[RIGHT].size() > 0)
          {
            INT side = RoadPoints[LEFT].size() > 0 ? LEFT : RIGHT;
            TriangulateConst(Points, RoadPoints[side], Triangles);
          }

          if (intersect[LEFT] || intersect[RIGHT] || intersect[END_0] || intersect[END_1])
          {
            Triangles.erase(Triangles.begin() + j);
            j--;
            size--;
          }
        }
      for (INT i = 0, roadsize = RoadSegments.size(); i < roadsize; i++)
        for (INT j = 0, size = Triangles.size(); j < size; j++)
        {
          intersect[END_0] = intersect[END_1] = FALSE;

          for (INT side = 2; side < 4; side++)
            intersect[side] = RoadCutTriangle(RoadSegments, i, j, side, ToContinue,
                                              SidePoints[side], InSide[side], OutSide[side], RoadPoints[side]);

          if (intersect[END_0] || intersect[END_1])
          {
            Triangles.erase(Triangles.begin() + j);
            j--;
            size--;
          }
        }
      for (INT tr = 0, size = Triangles.size(); tr < size; tr++)
      {
        vec in =
          (Points[Triangles[tr].P[0]] + Points[Triangles[tr].P[1]]) * 0.5 +
          (Points[Triangles[tr].P[2]] - (Points[Triangles[tr].P[0]] + Points[Triangles[tr].P[1]]) * 0.5) * 0.5;
        for (INT rs = 0, roadsize = RoadSegments.size(); rs < roadsize; rs++)
        {
          vec
            P0 = RoadSegments[rs].Neighbour[LEFT][0] == -1 ?
                 (Points[RoadSegments[rs].Shoulder[LEFT][0]] + Points[RoadSegments[rs].Shoulder[RIGHT][0]]) / 2 :
                 Points[RoadSegments[rs].P[0]],
            P1 = RoadSegments[rs].Neighbour[LEFT][1] == -1 ?
                 (Points[RoadSegments[rs].Shoulder[LEFT][1]] + Points[RoadSegments[rs].Shoulder[RIGHT][1]]) / 2 :
                 Points[RoadSegments[rs].P[1]];
          if (PointTestHexagon(in,
                               P0,
                               Points[RoadSegments[rs].Shoulder[RIGHT][0]],
                               Points[RoadSegments[rs].Shoulder[RIGHT][1]],
                               P1,
                               Points[RoadSegments[rs].Shoulder[LEFT][1]],
                               Points[RoadSegments[rs].Shoulder[LEFT][0]]))
          {
            Triangles.erase(Triangles.begin() + tr);
            tr--;
            size--;
            break;
          }
        }
      }
    } /* End of 'InsertRoad' function */

    /* Set road segment texture coordinates function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road segment index:
     *       INT rs;
     *   - road width:
     *       DOUBLE HalfWidth;
     * RETURNS: None.
     */
    VOID SetTextureCoordinates( std::vector<road_segment> &RoadSegments, INT rs, DOUBLE HalfWidth )
    {
      if (!RoadSegments[rs].IsTexCoord[0] && !RoadSegments[rs].IsTexCoord[1])
      {
        RoadSegments[rs].IsTexCoord[0] = RoadSegments[rs].IsTexCoord[1] = TRUE;
        RoadSegments[rs].TexCoord[0] = 0;
        RoadSegments[rs].TexCoord[1] =
          (Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;
      }
      else if (!RoadSegments[rs].IsTexCoord[0] && RoadSegments[rs].IsTexCoord[1])
      {
        RoadSegments[rs].IsTexCoord[0] = TRUE;
        RoadSegments[rs].TexCoord[0] = RoadSegments[rs].TexCoord[1] +
          (Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;
      }
      else if (RoadSegments[rs].IsTexCoord[0] && !RoadSegments[rs].IsTexCoord[1])
      {
        RoadSegments[rs].IsTexCoord[1] = TRUE;
        RoadSegments[rs].TexCoord[1] = RoadSegments[rs].TexCoord[0] +
          (Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;
      }

      INT nb, nbno;
      for (INT side = 0; side < 2; side++)
        for (INT no = 0; no < 2; no++)
          if ((nb = RoadSegments[rs].Neighbour[side][no]) != -1)
          {
            nbno = RoadSegments[rs].P[no] == RoadSegments[nb].P[no] ? no : !no;
            if (!RoadSegments[nb].IsTexCoord[nbno])
            {
              RoadSegments[nb].IsTexCoord[nbno] = TRUE;
              RoadSegments[nb].TexCoord[nbno] = RoadSegments[rs].TexCoord[no];
              SetTextureCoordinates(RoadSegments, nb, HalfWidth);
            }
          }
    } /* End of 'SetTextureCoordinates' function */

    /* Set road segments texture coordinates function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road width:
     *       DOUBLE HalfWidth;
     * RETURNS: None.
     */
    VOID SetTextureCoordinates( std::vector<road_segment> &RoadSegments, DOUBLE HalfWidth )
    {
      for (INT i = 0; i < RoadSegments.size(); i++)
        SetTextureCoordinates(RoadSegments, i, HalfWidth);
    } /* End of 'SetTextureCoordinates' function */

    /* Triangulate road shoulder function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road height:
     *       DOUBLE Height;
     * RETURNS: None.
     */
    VOID TriangulateRoadShoulder( std::vector<road_segment> &RoadSegments )
    {
      BOOL IsNoError = TRUE;

      std::vector<INT> IDs, P0, P1, H0, H1;
      std::vector<uv> TextureCoords;

      for (INT i = 0; i < Points.size(); i++)
        IDs.push_back(0), P0.push_back(0), P1.push_back(0), H0.push_back(0), H1.push_back(0), TextureCoords.push_back(uv(0, 0));
      for (INT rs = 0, size = RoadSegments.size(); rs < size; rs++)
      {
        IDs[RoadSegments[rs].Border[LEFT][0]] = 1;
        IDs[RoadSegments[rs].Border[LEFT][1]] = 1;
        IDs[RoadSegments[rs].Border[RIGHT][0]] = 1;
        IDs[RoadSegments[rs].Border[RIGHT][1]] = 1;
      }
      for (INT rs = 0, size = RoadSegments.size(); rs < size; rs++)
      {
        P0[RoadSegments[rs].Border[LEFT][0]] = P0[RoadSegments[rs].Border[LEFT][1]] = RoadSegments[rs].Border[LEFT][0];
        P1[RoadSegments[rs].Border[LEFT][0]] = P1[RoadSegments[rs].Border[LEFT][1]] = RoadSegments[rs].Border[LEFT][1];
        H0[RoadSegments[rs].Border[LEFT][0]] = H0[RoadSegments[rs].Border[LEFT][1]] = RoadSegments[rs].P[0];
        H1[RoadSegments[rs].Border[LEFT][0]] = H1[RoadSegments[rs].Border[LEFT][1]] = RoadSegments[rs].P[1];

        P0[RoadSegments[rs].Border[RIGHT][0]] = P0[RoadSegments[rs].Border[RIGHT][1]] = RoadSegments[rs].Border[RIGHT][0];
        P1[RoadSegments[rs].Border[RIGHT][0]] = P1[RoadSegments[rs].Border[RIGHT][1]] = RoadSegments[rs].Border[RIGHT][1];
        H0[RoadSegments[rs].Border[RIGHT][0]] = H0[RoadSegments[rs].Border[RIGHT][1]] = RoadSegments[rs].P[0];
        H1[RoadSegments[rs].Border[RIGHT][0]] = H1[RoadSegments[rs].Border[RIGHT][1]] = RoadSegments[rs].P[1];
      }

      vec intr;
      for (INT rs = 0, size = RoadSegments.size(); rs < size; rs++)
      {
        vec norm =
          vec(Points[RoadSegments[rs].P[1]].Z - Points[RoadSegments[rs].P[0]].Z,
              0,
              Points[RoadSegments[rs].P[0]].X - Points[RoadSegments[rs].P[1]].X).Normalize() * 0.001;
        // Left.
        if (RoadSegments[rs].Intersections[LEFT].size() == 0)
        {
          Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][0],
                                       RoadSegments[rs].Border[LEFT][0],
                                       RoadSegments[rs].Border[LEFT][1]));
          Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][0],
                                       RoadSegments[rs].Border[LEFT][1],
                                       RoadSegments[rs].Shoulder[LEFT][1]));
        }
        else
        {
          std::sort(RoadSegments[rs].Intersections[LEFT].begin(), RoadSegments[rs].Intersections[LEFT].end(),
            []( intersection a, intersection b )
            {
              return a.t < b.t;
            });
          for (INT i = 0; i < RoadSegments[rs].Intersections[LEFT].size(); i++)
          {
            P0.push_back(RoadSegments[rs].Border[LEFT][0]);
            P1.push_back(RoadSegments[rs].Border[LEFT][1]);
            H0.push_back(RoadSegments[rs].P[0]);
            H1.push_back(RoadSegments[rs].P[1]);
          }
          Points.push_back(
            Points[RoadSegments[rs].Border[LEFT][0]] - norm +
            (Points[RoadSegments[rs].Border[LEFT][1]] - Points[RoadSegments[rs].Border[LEFT][0]]) *
             RoadSegments[rs].Intersections[LEFT][0].t
          );
          Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][0],
                                       RoadSegments[rs].Border[LEFT][0],
                                       Points.size() - 1));
          Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][0],
                                       Points.size() - 1,
                                       RoadSegments[rs].Intersections[LEFT][0].Index));
          for (INT i = 0, ni = RoadSegments[rs].Intersections[LEFT].size() - 1; i < ni; i++)
          {
            Points.push_back(Points[RoadSegments[rs].Border[LEFT][0]] - norm +
                            (Points[RoadSegments[rs].Border[LEFT][1]] - Points[RoadSegments[rs].Border[LEFT][0]]) *
                             RoadSegments[rs].Intersections[LEFT][(i + 1)].t);
            Triangles.push_back(triangle(RoadSegments[rs].Intersections[LEFT][i].Index,
                                         Points.size() - 2,
                                         Points.size() - 1));
            Triangles.push_back(triangle(RoadSegments[rs].Intersections[LEFT][i].Index,
                                         Points.size() - 1,
                                         RoadSegments[rs].Intersections[LEFT][i + 1].Index));
          }
          Triangles.push_back(triangle(RoadSegments[rs].Intersections[LEFT].back().Index,
                                       Points.size() - 1,
                                       RoadSegments[rs].Border[LEFT][1]));
          Triangles.push_back(triangle(RoadSegments[rs].Intersections[LEFT].back().Index,
                                       RoadSegments[rs].Border[LEFT][1],
                                       RoadSegments[rs].Shoulder[LEFT][1]));
        }
        // Right.
        if (RoadSegments[rs].Intersections[RIGHT].size() == 0)
        {
          Triangles.push_back(triangle(RoadSegments[rs].Border[RIGHT][0],
                                       RoadSegments[rs].Shoulder[RIGHT][0],
                                       RoadSegments[rs].Shoulder[RIGHT][1]));
          Triangles.push_back(triangle(RoadSegments[rs].Border[RIGHT][0],
                                       RoadSegments[rs].Shoulder[RIGHT][1],
                                       RoadSegments[rs].Border[RIGHT][1]));
        }
        else
        {
          std::sort(RoadSegments[rs].Intersections[RIGHT].begin(), RoadSegments[rs].Intersections[RIGHT].end(),
            []( intersection a, intersection b )
            {
              return a.t < b.t;
            });
          for (INT i = 0; i < RoadSegments[rs].Intersections[RIGHT].size(); i++)
          {
            P0.push_back(RoadSegments[rs].Border[RIGHT][0]);
            P1.push_back(RoadSegments[rs].Border[RIGHT][1]);
            H0.push_back(RoadSegments[rs].P[0]);
            H1.push_back(RoadSegments[rs].P[1]);
          }
          Points.push_back(Points[RoadSegments[rs].Border[RIGHT][0]] + norm +
                          (Points[RoadSegments[rs].Border[RIGHT][1]] - Points[RoadSegments[rs].Border[RIGHT][0]]) *
                           RoadSegments[rs].Intersections[RIGHT][0].t);
          Triangles.push_back(triangle(RoadSegments[rs].Border[RIGHT][0],
                                       RoadSegments[rs].Shoulder[RIGHT][0],
                                       RoadSegments[rs].Intersections[RIGHT][0].Index));
          Triangles.push_back(triangle(RoadSegments[rs].Border[RIGHT][0],
                                       RoadSegments[rs].Intersections[RIGHT][0].Index,
                                       Points.size() - 1));
          for (INT i = 0, ni = RoadSegments[rs].Intersections[RIGHT].size() - 1; i < ni; i++)
          {
            Points.push_back(Points[RoadSegments[rs].Border[RIGHT][0]] + norm +
                            (Points[RoadSegments[rs].Border[RIGHT][1]] - Points[RoadSegments[rs].Border[RIGHT][0]]) *
                             RoadSegments[rs].Intersections[RIGHT][(i + 1)].t);
            Triangles.push_back(triangle(Points.size() - 2,
                                         RoadSegments[rs].Intersections[RIGHT][i].Index,
                                         RoadSegments[rs].Intersections[RIGHT][i + 1].Index));
            Triangles.push_back(triangle(Points.size() - 2,
                                         RoadSegments[rs].Intersections[RIGHT][i + 1].Index,
                                         Points.size() - 1));
          }
          Triangles.push_back(triangle(Points.size() - 1,
                                       RoadSegments[rs].Intersections[RIGHT].back().Index,
                                       RoadSegments[rs].Shoulder[RIGHT][1]));
          Triangles.push_back(triangle(Points.size() - 1,
                                       RoadSegments[rs].Shoulder[RIGHT][1],
                                       RoadSegments[rs].Border[RIGHT][1]));
        }
      
        norm = vec(norm.Z, 0, -norm.X);
      
        // Begin.
        if (RoadSegments[rs].Neighbour[LEFT][0] == -1)
        {
          if (RoadSegments[rs].Intersections[END_0].size() == 0)
          {
            Triangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0],
                                         RoadSegments[rs].Shoulder[LEFT][0],
                                         RoadSegments[rs].Shoulder[RIGHT][0]));
            Triangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0],
                                         RoadSegments[rs].Shoulder[RIGHT][0],
                                         RoadSegments[rs].Border[RIGHT][0]));
          }
          else
          {
            std::sort(RoadSegments[rs].Intersections[END_0].begin(), RoadSegments[rs].Intersections[END_0].end(),
              []( intersection a, intersection b )
              {
                return a.t < b.t;
              });
            for (INT i = 0; i < RoadSegments[rs].Intersections[END_0].size(); i++)
            {
              P0.push_back(RoadSegments[rs].Border[LEFT][0]);
              P1.push_back(RoadSegments[rs].Border[RIGHT][0]);
              H0.push_back(RoadSegments[rs].P[0]);
              H1.push_back(RoadSegments[rs].P[0]);
            }
            Points.push_back(Points[RoadSegments[rs].Border[LEFT][0]] - norm +
                            (Points[RoadSegments[rs].Border[RIGHT][0]] - Points[RoadSegments[rs].Border[LEFT][0]]) *
                            RoadSegments[rs].Intersections[END_0][0].t);
      
            Triangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0],
                                         RoadSegments[rs].Shoulder[LEFT][0],
                                         RoadSegments[rs].Intersections[END_0][0].Index));
            Triangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0],
                                         RoadSegments[rs].Intersections[END_0][0].Index,
                                         Points.size() - 1));
            for (INT i = 0, ni = RoadSegments[rs].Intersections[END_0].size() - 1; i < ni; i++)
            {
              Points.push_back(Points[RoadSegments[rs].Border[LEFT][0]] - norm +
                              (Points[RoadSegments[rs].Border[RIGHT][0]] - Points[RoadSegments[rs].Border[LEFT][0]]) *
                               RoadSegments[rs].Intersections[END_0][(i + 1)].t);
              Triangles.push_back(triangle(Points.size() - 2,
                                           RoadSegments[rs].Intersections[END_0][i].Index,
                                           RoadSegments[rs].Intersections[END_0][i + 1].Index));
              Triangles.push_back(triangle(Points.size() - 2,
                                           RoadSegments[rs].Intersections[END_0][i + 1].Index,
                                           Points.size() - 1));
            }
            Triangles.push_back(triangle(Points.size() - 1,
                                         RoadSegments[rs].Intersections[END_0].back().Index,
                                         RoadSegments[rs].Shoulder[RIGHT][0]));
            Triangles.push_back(triangle(Points.size() - 1,
                                         RoadSegments[rs].Shoulder[RIGHT][0],
                                         RoadSegments[rs].Border[RIGHT][0]));
          }
        }
        // End.
        if (RoadSegments[rs].Neighbour[LEFT][1] == -1)
        {
          if (RoadSegments[rs].Intersections[END_1].size() == 0)
          {
            Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][1],
                                         RoadSegments[rs].Border[LEFT][1],
                                         RoadSegments[rs].Border[RIGHT][1]));
            Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][1],
                                         RoadSegments[rs].Border[RIGHT][1],
                                         RoadSegments[rs].Shoulder[RIGHT][1]));
          }
          else
          {
            std::sort(RoadSegments[rs].Intersections[END_1].begin(), RoadSegments[rs].Intersections[END_1].end(),
              []( intersection a, intersection b )
              {
                return a.t < b.t;
              });
            for (INT i = 0; i < RoadSegments[rs].Intersections[END_1].size(); i++)
            {
              P0.push_back(RoadSegments[rs].Border[LEFT][1]);
              P1.push_back(RoadSegments[rs].Border[RIGHT][1]);
              H0.push_back(RoadSegments[rs].P[1]);
              H1.push_back(RoadSegments[rs].P[1]);
            }
            Points.push_back(Points[RoadSegments[rs].Border[LEFT][1]] + norm +
                            (Points[RoadSegments[rs].Border[RIGHT][1]] - Points[RoadSegments[rs].Border[LEFT][1]]) *
                             RoadSegments[rs].Intersections[END_1][0].t);
            Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][1],
                                         RoadSegments[rs].Border[LEFT][1],
                                         Points.size() - 1));
            Triangles.push_back(triangle(RoadSegments[rs].Shoulder[LEFT][1],
                                         Points.size() - 1,
                                         RoadSegments[rs].Intersections[END_1][0].Index));
            for (INT i = 0, ni = RoadSegments[rs].Intersections[END_1].size() - 1; i < ni; i++)
            {
              Points.push_back(Points[RoadSegments[rs].Border[LEFT][1]] + norm +
                              (Points[RoadSegments[rs].Border[RIGHT][1]] - Points[RoadSegments[rs].Border[LEFT][1]]) *
                               RoadSegments[rs].Intersections[END_1][(i + 1)].t);
              Triangles.push_back(triangle(RoadSegments[rs].Intersections[END_1][i].Index,
                                           Points.size() - 2,
                                           Points.size() - 1));
              Triangles.push_back(triangle(RoadSegments[rs].Intersections[END_1][i].Index,
                                           Points.size() - 1,
                                           RoadSegments[rs].Intersections[END_1][i + 1].Index));
            }
            Triangles.push_back(triangle(RoadSegments[rs].Intersections[END_1].back().Index,
                                         Points.size() - 1,
                                         RoadSegments[rs].Border[RIGHT][1])
            );
            Triangles.push_back(triangle(RoadSegments[rs].Intersections[END_1].back().Index,
                                         RoadSegments[rs].Border[RIGHT][1],
                                         RoadSegments[rs].Shoulder[RIGHT][1])
            );
          }
        }
      }
      for (INT i = IDs.size(); i < Points.size(); i++)
        IDs.push_back(1);

      CreateMountain(Mountain, Ani, Points, Triangles, IDs, P0, P1, H0, H1);
    } /* End of 'TriangulateRoadShoulder' function */

    /* Triangulate road function.
     * ARGUMENTS:
     *   - road segments:
     *       std::vector<road_segment> &RoadSegments;
     *   - road width:
     *       DOUBLE HalfWidth;
     * RETURNS: None.
     */
    VOID TriangulateRoad( std::vector<road_segment> &RoadSegments, DOUBLE HalfWidth )
    {
      std::vector<tsg::TVec<uv>> TextureCoords;
      std::vector<triangle> Heights, P0, P1, H0, H1;
      vec norm, intr;
      DOUBLE bias[2], len[2], lenc;
      INT nb[2][2], nbh[2][2];
      for (INT rs = 0, size = RoadSegments.size(); rs < size; rs++)
      {
        DOUBLE factor = RoadSegments[rs].TexCoord[0] < RoadSegments[rs].TexCoord[1] ? 1 : -1;

        norm = vec(Points[RoadSegments[rs].P[1]].Z - Points[RoadSegments[rs].P[0]].Z, 0, Points[RoadSegments[rs].P[0]].X - Points[RoadSegments[rs].P[1]].X);

        intr = LineIntersectLine(Points[RoadSegments[rs].P[0]], Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]],
                                 Points[RoadSegments[rs].Border[RIGHT][0]], norm);
        if (PointTestHexagon(intr,
                             Points[RoadSegments[rs].P[0]],
                             Points[RoadSegments[rs].Border[RIGHT][0]],
                             Points[RoadSegments[rs].Border[RIGHT][1]],
                             Points[RoadSegments[rs].P[1]],
                             Points[RoadSegments[rs].Border[LEFT][1]],
                             Points[RoadSegments[rs].Border[LEFT][0]]))
          bias[RIGHT] = (intr - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;
        else
          bias[RIGHT] = (intr - Points[RoadSegments[rs].P[0]]).Length2D() / -HalfWidth * 3 / 8;
        len[RIGHT] =
          (Points[RoadSegments[rs].Border[RIGHT][1]] - Points[RoadSegments[rs].Border[RIGHT][0]]).Length2D() / HalfWidth * 3 / 8;

        lenc = (Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;

        intr = LineIntersectLine(Points[RoadSegments[rs].P[0]], Points[RoadSegments[rs].P[1]] - Points[RoadSegments[rs].P[0]],
                                 Points[RoadSegments[rs].Border[LEFT][0]], -norm);
        if (PointTestHexagon(intr,
                             Points[RoadSegments[rs].P[0]],
                             Points[RoadSegments[rs].Border[RIGHT][0]],
                             Points[RoadSegments[rs].Border[RIGHT][1]],
                             Points[RoadSegments[rs].P[1]],
                             Points[RoadSegments[rs].Border[LEFT][1]],
                             Points[RoadSegments[rs].Border[LEFT][0]]))
          bias[LEFT] = (intr - Points[RoadSegments[rs].P[0]]).Length2D() / HalfWidth * 3 / 8;
        else
          bias[LEFT] = (intr - Points[RoadSegments[rs].P[0]]).Length2D() / -HalfWidth * 3 / 8;
        len[LEFT] =
          (Points[RoadSegments[rs].Border[LEFT][1]] - Points[RoadSegments[rs].Border[LEFT][0]]).Length2D() / HalfWidth * 3 / 8;

        for (INT side = 0; side < 2; side++)
          for (INT no = 0; no < 2; no++)
          {
            nb[side][no] = RoadSegments[rs].Neighbour[side][no];
            if (nb[side][no] == -1)
              continue;
            nbh[side][no] =
              no == 0 ? RoadSegments[nb[side][no]].P[1] > RoadSegments[rs].P[0] ?
                        RoadSegments[nb[side][no]].P[1] : RoadSegments[nb[side][no]].P[0] :
                        RoadSegments[nb[side][no]].P[1] == RoadSegments[rs].P[1] ?
                        RoadSegments[nb[side][no]].P[0] : RoadSegments[nb[side][no]].P[1];
            nb[side][no] =
              no == 0 ? RoadSegments[nb[side][no]].P[1] > RoadSegments[rs].P[0] ?
                        RoadSegments[nb[side][no]].Border[!side][1] : RoadSegments[nb[side][no]].Border[side][0] :
                        RoadSegments[nb[side][no]].P[1] == RoadSegments[rs].P[1] ?
                        RoadSegments[nb[side][no]].Border[!side][0] : RoadSegments[nb[side][no]].Border[side][1];
          }

        RoadTriangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0], RoadSegments[rs].Border[RIGHT][0], RoadSegments[rs].Border[RIGHT][1]));
        TextureCoords.push_back(
          tsg::TVec<uv>(
            uv(0 + 0.125, RoadSegments[rs].TexCoord[0] + factor * bias[LEFT]),
            uv(1 - 0.125, RoadSegments[rs].TexCoord[0] + factor * bias[RIGHT]),
            uv(1 - 0.125, RoadSegments[rs].TexCoord[0] + factor * (len[RIGHT] + bias[RIGHT]))
          )
        );
        Heights.push_back(triangle(RoadSegments[rs].P[0], RoadSegments[rs].P[0], RoadSegments[rs].P[1]));
        P0.push_back(triangle(RoadSegments[rs].Border[LEFT][1],
                              RoadSegments[rs].Border[RIGHT][1],
                              RoadSegments[rs].Border[RIGHT][0]));
        P1.push_back(triangle(nb[LEFT][0] == -1 ?  RoadSegments[rs].Border[LEFT][1] :  nb[LEFT][0],
                              nb[RIGHT][0] == -1 ? RoadSegments[rs].Border[RIGHT][1] : nb[RIGHT][0],
                              nb[RIGHT][1] == -1 ? RoadSegments[rs].Border[RIGHT][0] : nb[RIGHT][1]));
        H0.push_back(triangle(RoadSegments[rs].P[1],
                              RoadSegments[rs].P[1],
                              RoadSegments[rs].P[0]));
        H1.push_back(triangle(nb[LEFT][0] == -1 ?  RoadSegments[rs].P[1] : nbh[LEFT][0],
                              nb[RIGHT][0] == -1 ? RoadSegments[rs].P[1] : nbh[RIGHT][0],
                              nb[RIGHT][1] == -1 ? RoadSegments[rs].P[0] : nbh[RIGHT][1]));

        RoadTriangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0], RoadSegments[rs].Border[RIGHT][1], RoadSegments[rs].Border[LEFT][1]));
        TextureCoords.push_back(
          tsg::TVec<uv>(
            uv(0 + 0.125, RoadSegments[rs].TexCoord[0] + factor * bias[LEFT]),
            uv(1 - 0.125, RoadSegments[rs].TexCoord[0] + factor * (len[RIGHT] + bias[RIGHT])),
            uv(0 + 0.125, RoadSegments[rs].TexCoord[0] + factor * (len[LEFT] + bias[LEFT]))
          )
        );
        Heights.push_back(triangle(RoadSegments[rs].P[0], RoadSegments[rs].P[1], RoadSegments[rs].P[1]));
        P0.push_back(triangle(RoadSegments[rs].Border[LEFT][1],
                              RoadSegments[rs].Border[RIGHT][0],
                              RoadSegments[rs].Border[LEFT][0]));
        P1.push_back(triangle(nb[LEFT][0] == -1 ?  RoadSegments[rs].Border[LEFT][1] :  nb[LEFT][0],
                              nb[RIGHT][1] == -1 ? RoadSegments[rs].Border[RIGHT][0] : nb[RIGHT][1],
                              nb[LEFT][1] == -1 ?  RoadSegments[rs].Border[LEFT][0] :  nb[LEFT][1]));
        H0.push_back(triangle(RoadSegments[rs].P[1],
                              RoadSegments[rs].P[0],
                              RoadSegments[rs].P[0]));
        H1.push_back(triangle(nb[LEFT][0] == -1 ?  RoadSegments[rs].P[1] : nbh[LEFT][0],
                              nb[RIGHT][1] == -1 ? RoadSegments[rs].P[0] : nbh[RIGHT][1],
                              nb[LEFT][1] == -1 ?  RoadSegments[rs].P[0] : nbh[LEFT][1]));

        if (RoadSegments[rs].Neighbour[LEFT][0] != RoadSegments[rs].Neighbour[RIGHT][0])
        {
          RoadTriangles.push_back(triangle(RoadSegments[rs].Border[LEFT][0], RoadSegments[rs].P[0], RoadSegments[rs].Border[RIGHT][0]));
          TextureCoords.push_back(
            tsg::TVec<uv>(
              uv(0 + 0.125, RoadSegments[rs].TexCoord[0] + factor * bias[LEFT]),
              uv(0.5, RoadSegments[rs].TexCoord[0]),
              uv(1 - 0.125, RoadSegments[rs].TexCoord[0] + factor * bias[RIGHT])
            )
          );
          Heights.push_back(triangle(RoadSegments[rs].P[0], RoadSegments[rs].P[0], RoadSegments[rs].P[0]));
          P0.push_back(triangle(RoadSegments[rs].Border[LEFT][1],
                                RoadSegments[rs].Border[LEFT][0],
                                RoadSegments[rs].Border[RIGHT][1]));
          P1.push_back(triangle(nb[LEFT][0],
                                RoadSegments[rs].Border[RIGHT][0],
                                nb[RIGHT][0]));
          H0.push_back(triangle(RoadSegments[rs].P[1],
                                RoadSegments[rs].P[0],
                                RoadSegments[rs].P[1]));
          H1.push_back(triangle(nbh[LEFT][0],
                                RoadSegments[rs].P[0],
                                nbh[RIGHT][0]));
        }

        if (RoadSegments[rs].Neighbour[LEFT][1] != RoadSegments[rs].Neighbour[RIGHT][1])
        {
          RoadTriangles.push_back(triangle(RoadSegments[rs].Border[RIGHT][1], RoadSegments[rs].P[1], RoadSegments[rs].Border[LEFT][1]));
          TextureCoords.push_back(
            tsg::TVec<uv>(
              uv(1 - 0.125, RoadSegments[rs].TexCoord[0] + factor * (len[RIGHT] + bias[RIGHT])),
              uv(0.5, RoadSegments[rs].TexCoord[0] + factor * lenc),
              uv(0 + 0.125, RoadSegments[rs].TexCoord[0] + factor * (len[LEFT] + bias[LEFT]))
            )
          );
          Heights.push_back(triangle(RoadSegments[rs].P[1], RoadSegments[rs].P[1], RoadSegments[rs].P[1]));
          P0.push_back(triangle(RoadSegments[rs].Border[RIGHT][0],
                                RoadSegments[rs].Border[RIGHT][1],
                                RoadSegments[rs].Border[LEFT][0]));
          P1.push_back(triangle(nb[RIGHT][1],
                                RoadSegments[rs].Border[LEFT][1],
                                nb[LEFT][1]));
          H0.push_back(triangle(RoadSegments[rs].P[0],
                                RoadSegments[rs].P[1],
                                RoadSegments[rs].P[0]));
          H1.push_back(triangle(nbh[RIGHT][1],
                                RoadSegments[rs].P[1],
                                nbh[LEFT][1]));
        }
      }
      CreateRoad(Road, Ani, Points, RoadTriangles, TextureCoords, Heights, P0, P1, H0, H1);
    } /* End of 'TriangulateRoad' function */

    /* Build houses function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID BuildHouses( VOID );

    /* Create landscape function.
     * ARGUMENTS:
     *   - road width and shoulder width:
     *       DOUBLE HalfWidth, Shoulder;
     * RETURN: None.
     */
    VOID CreateLandscape( DOUBLE HalfWidth, DOUBLE Shoulder );

    /* Add point function.
     * ARGUMENTS:
     *   - point:
     *       const vec &Point;
     * RETURNS: None.
     */
    VOID AddPoint( const vec &Point );

    /* Add segment function.
     * ARGUMENTS:
     *   - segment points:
     *       const vec &P0, &P1;
     * RETURNS: None.
     */
    VOID AddSegment( const vec &P0, const vec &P1 );

  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     */
    unit_road( anim *Ani, float H, float Lacunarity,
               float Octaves, float Offset,
               float Gain, float FSeed );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~unit_road( VOID );

    /* Response unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID );

    /* Render unit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );
  }; /* End of 'unit_road' class */
} /* end of 'tcg' namespace */

#endif /* __unit_road_h_ */

/* END OF 'unit_road.h' FILE */
