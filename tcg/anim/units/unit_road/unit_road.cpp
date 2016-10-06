/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : unit_road.cpp
 * PURPOSE     : Computational geometry project.
 *               Road unit.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 25.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cmath>
#include <cstdlib>

#include "../../../def.h"

#include "../../animation.h"
#include "unit_road.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::unit_road::unit_road( anim *Ani, float H, float Lacunarity,
                           float Octaves, float Offset,
                           float Gain, float FSeed ) :
  fBm(H, Lacunarity, Gain, Offset, Octaves, FSeed),
  unit(Ani), Ani(Ani), Mountain(Ani), Road(Ani), Village(Ani), IsLandscape(FALSE), FirstPoint(TRUE),
  Plane(vec(1 - 4, 0, 1 - 4), vec(0, 0, 58 + 8), vec(58 + 8, 0, 0)), EditMode(EDIT_TRIANGLES), ScaleY(1)
{
  Houses.push_back(std::vector<INT>());
  IfTess = 1;

  Ani->Camera.SetDirLocUp(vec(Width / 2,
                              Width * Ani->Camera.ProjDist,
                              Height / 2),
                          vec(0, -1, 0),
                          vec(0, 0, -1));

  srand(30);
  for (INT i = 0; i < 2500; i++)
    AddPoint(vec(rand(0, 60), 0, rand(0, 60)));
  for (INT i = 0; i < 60; i++)
  {
    AddPoint(vec(i,      0, 0));
    AddPoint(vec(60,     0, i));
    AddPoint(vec(60 - i, 0, 60));
    AddPoint(vec(0,      0, 60 - i));
  }
  AddPoint(vec(0,  0,  0));
  AddPoint(vec(60, 0,  0));
  AddPoint(vec(60, 0, 60));
  AddPoint(vec(0,  0, 60));

  math::Triangulate(Points, Triangles);

  std::vector<INT> IDs;
  for (INT i = 0; i < Points.size(); i++)
    IDs.push_back(0);

  CreateMountain(Mountain, Ani, Points, Triangles, IDs);
  Mountain.Material->SetUniform("IfTess", IfTess);
} /* End of 'tcg::unit_road::unit_road' function */

/* Class destructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::unit_road::~unit_road( VOID )
{
} /* End of 'tcg::unit_road::~unit_road' function */

/* Response unit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit_road::Response( VOID )
{
  static BOOL IsWireframe = FALSE;
  static vec LookAt;
  static DOUBLE Dist, Angle;

  if (Ani->KeysClick['T'])
  {
    IfTess = 1 - IfTess;
    Mountain.Material->SetUniform("IfTess", IfTess);
  }

  if (!IsLandscape)
  {
    if (Ani->KeysClick[VK_LBUTTON])
    {
      DOUBLE X = Ani->MsX, Y = Ani->MsY, W = Ani->GetW(), H = Ani->GetH();

      ray Ray;
      Ray.Dir = Ani->Camera.Dir * Ani->Camera.ProjDist +
                Ani->Camera.Right * (X / W * Ani->Camera.Width - Ani->Camera.Width / 2) +
                Ani->Camera.Up * (Ani->Camera.Height / 2 - Y / H * Ani->Camera.Height);
      Ray.Org = Ani->Camera.Loc + Ray.Dir;
      Ray.Dir.Normalize();

      cd::collision Collision = Plane.Intersect(Ray, 0, 1);
      if (Collision.IsCollide)
      {
        if (EditMode == EDIT_ROAD)
        {
          if (FirstPoint)
            FirstPoint = FALSE;
          else
            AddSegment(PrevPoint, Collision.Intersection.Location);
          PrevPoint = Collision.Intersection.Location;
        }
        else if (EditMode == EDIT_HOUSE)
        {
          Houses.back().push_back(Points.size());
          Points.push_back(Collision.Intersection.Location);
        }
        else
        {
          AddPoint(Collision.Intersection.Location);
          math::Triangulate(Points, Triangles);
        }
      }
    }

    if (Ani->Keys[VK_RBUTTON])
    {
      DOUBLE dx = 1, dy = 1, w = Ani->GetW(), h = Ani->GetH();
      if (w > h)
        dx = w / h;
      else
        dy = h / w;
      Ani->Camera.Translate(vecf(-Ani->MsDeltaX / w * dx * Ani->Camera.Loc.Y / 1.5, 0,
                                 -Ani->MsDeltaY / h * dy * Ani->Camera.Loc.Y / 1.5));
    }
    if (Ani->Keys[VK_SPACE])
    {
      if (EditMode == EDIT_ROAD)
        FirstPoint = TRUE;
      else if (EditMode == EDIT_HOUSE)
        Houses.push_back(std::vector<INT>());
    }
    if (Ani->KeysClick['H'] && EditMode != EDIT_HOUSE)
      EditMode = EDIT_HOUSE;
    if (Ani->KeysClick['R'] && EditMode != EDIT_ROAD)
    {
      Houses.push_back(std::vector<INT>());
      EditMode = EDIT_ROAD;
      FirstPoint = TRUE;
    }
    if (Ani->KeysClick['B'])
    {
      CreateLandscape(RoadHalfWidth, RoadShoulderWidth);
      IsLandscape = TRUE;
      LookAt = vec(Ani->Camera.Loc.X, 0, Ani->Camera.Loc.Z);
      Dist = Ani->Camera.Loc.Y;
    }
    if (Ani->WheelDelta != 0)
    {
      DOUBLE X = Ani->MsX, Y = Ani->MsY, W = Ani->GetW(), H = Ani->GetH();
    
      ray Ray;
      Ray.Dir = Ani->Camera.Dir * Ani->Camera.ProjDist +
                Ani->Camera.Right * (X / W * Ani->Camera.Width - Ani->Camera.Width / 2) +
                Ani->Camera.Up * (Ani->Camera.Height / 2 - Y / H * Ani->Camera.Height);
      Ray.Org = Ani->Camera.Loc + Ray.Dir;
      Ray.Dir.Normalize();

      cd::collision Collision = Plane.Intersect(Ray, 0, 1);
      if (Collision.IsCollide)
      {
        DOUBLE sd;
        if (Ani->WheelDelta > 0)
          sd = pow(9.9 / 10.0, Ani->WheelDelta / 10.0);
        else
          sd = pow(10.0 / 9.9, -Ani->WheelDelta / 10.0);
        if (!(Ani->Camera.Loc - Collision.Intersection.Location) > 2 || sd > 1)
          Ani->Camera.SetDirLocUp(Collision.Intersection.Location + (Ani->Camera.Loc - Collision.Intersection.Location) * sd, vec(0, -1, 0), vec(0, 0, -1));
      }
    }
  }

  if (IsLandscape)
  {
    if (ScaleY == 0.0001)
      ScaleY += 0.0001;
    else
      ScaleY = COM_MIN(ScaleY + Ani->DeltaTime / 6, 1);
    if (Angle < 60)
      if (Angle == 0)
        Angle += 0.0001;
      else
      {
        Angle += Ani->DeltaTime * 10;
        Ani->Camera.SetLookAtLocUp(LookAt + vec(0, cos(tsg::Deg2Rad(Angle)) * Dist, sin(tsg::Deg2Rad(Angle)) * Dist),
                                   LookAt, vec(0.0, 1.0, 0.0));
      }
    if (Ani->Keys[VK_UP])
      Ani->Camera.SetLookAtLocUp(Ani->Camera.Loc + vec(0, Ani->DeltaTime * 20, 0),
                                 cd::plane(vec(0, 0, 0),
                                           vec(1, 0, 0),
                                           vec(1, 0, -1)).Intersect(ray(Ani->Camera.Loc, Ani->Camera.Dir), 0, 1).Intersection.Location,
                                 vec(0.0, 1.0, 0.0));
    if (Ani->Keys[VK_DOWN] && Ani->Camera.Loc.Y > 0.2)
      Ani->Camera.SetLookAtLocUp(Ani->Camera.Loc - vec(0, Ani->DeltaTime * 20, 0),
                                 cd::plane(vec(0, 0, 0),
                                           vec(1, 0, 0),
                                           vec(1, 0, -1)).Intersect(ray(Ani->Camera.Loc, Ani->Camera.Dir), 0, 1).Intersection.Location,
                                 vec(0.0, 1.0, 0.0));
    if (Ani->Keys[VK_LEFT])
      Ani->Camera.MoveRight(-Ani->DeltaTime * 30);
    if (Ani->Keys[VK_RIGHT])
      Ani->Camera.MoveRight(Ani->DeltaTime * 30);
    if (Ani->WheelDelta != 0)
    {
      DOUBLE X = Ani->MsX, Y = Ani->MsY, W = Ani->GetW(), H = Ani->GetH();

      ray Ray;
      Ray.Dir = Ani->Camera.Dir * Ani->Camera.ProjDist +
                Ani->Camera.Right * (X / W * Ani->Camera.Width - Ani->Camera.Width / 2) +
                Ani->Camera.Up * (Ani->Camera.Height / 2 - Y / H * Ani->Camera.Height);
      Ray.Org = Ani->Camera.Loc + Ray.Dir;
      Ray.Dir.Normalize();
      Ani->Camera.Translate(vecf(Ray.Dir * Ani->WheelDelta / 70.0));
    }
    if (Ani->Keys[VK_LBUTTON] &&
        Ani->MsX >= 0 && Ani->MsX < Ani->GetW() &&
        Ani->MsY >= 0 && Ani->MsY < Ani->GetH())
    {
      if (Ani->MsDeltaX != 0)
      {
        DOUBLE OldX = Ani->MsX - Ani->MsDeltaX, NewX = Ani->MsX, W = Ani->GetW(), H = Ani->GetH();

        vec
          OldDirX = (Ani->Camera.Dir * Ani->Camera.ProjDist +
                     Ani->Camera.Right * (OldX / W * Ani->Camera.Width - Ani->Camera.Width / 2) +
                     Ani->Camera.Up * Ani->Camera.Height / 2).Normalize(),

          NewDirX = (Ani->Camera.Dir * Ani->Camera.ProjDist +
                     Ani->Camera.Right * (NewX / W * Ani->Camera.Width - Ani->Camera.Width / 2) +
                     Ani->Camera.Up * Ani->Camera.Height / 2).Normalize();
        DOUBLE AngleX = tsg::Rad2Deg(acos(OldDirX & NewDirX));
        if (Ani->MsDeltaX > 0)
          AngleX = -AngleX;
        Ani->Camera.RotateUp(AngleX);
      }
      if (Ani->MsDeltaY != 0)
      {
        DOUBLE OldY = Ani->MsY - Ani->MsDeltaY, NewY = Ani->MsY, W = Ani->GetW(), H = Ani->GetH();

        vec
          OldDirY = (Ani->Camera.Dir * Ani->Camera.ProjDist +
                     Ani->Camera.Right * -Ani->Camera.Width / 2 +
                     Ani->Camera.Up * (Ani->Camera.Height / 2 - OldY / H * Ani->Camera.Height)).Normalize(),
          NewDirY = (Ani->Camera.Dir * Ani->Camera.ProjDist +
                     Ani->Camera.Right * -Ani->Camera.Width / 2 +
                     Ani->Camera.Up * (Ani->Camera.Height / 2 - NewY / H * Ani->Camera.Height)).Normalize();
        DOUBLE AngleY = tsg::Rad2Deg(acos(OldDirY & NewDirY));
        if (Ani->MsDeltaY > 0)
          AngleY = -AngleY;
        if (Ani->MsDeltaY < 0 && Ani->Camera.Dir.Y > -0.9 || Ani->MsDeltaY > 0 && Ani->Camera.Dir.Y < 0.9)
          Ani->Camera.RotateRight(AngleY);
      }
    }
    Ani->Camera.SetDirLocUp(Ani->Camera.Loc, Ani->Camera.Dir, vec(0, 1, 0));
  }

  if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
  {
    IsWireframe = !IsWireframe;
    if (IsWireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
} /* End of 'tcg::unit_road::Response' function */

/* Render unit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit_road::Render( VOID )
{
  Ani->World.SetScale(1, ScaleY, 1);
  Mountain.Render();
  if (IsLandscape)
  {
    Road.Render();
    Village.Render();
  }
  else
  {
    glPushMatrix();

    DOUBLE sx = 1, sy = 1, w = Ani->GetW(), h = Ani->GetH();
    if (w > h)
      sx = h / w;
    else
      sy = w / h;
    glScalef(sx, sy, 0.0);

    glScalef((Width * Ani->Camera.ProjDist) / Ani->Camera.Loc.Y,
             (Width * Ani->Camera.ProjDist) / Ani->Camera.Loc.Y, 0.0);
    glTranslatef((-Ani->Camera.Loc.X + (Width / 2)) / (Width / 2),
                 (Ani->Camera.Loc.Z - (Height / 2)) / (Height / 2), 0.0);

    glPointSize(5);
    glBegin(GL_POINTS);
      glColor3d(0.9, 0.9, 0.9);
      for (INT i = 0; i < Segments.size(); i++)
      {
        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1, -Points[Segments[i].P0].Z / (Height / 2) + 1);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1, -Points[Segments[i].P1].Z / (Height / 2) + 1);
      }
    glEnd();
    glPointSize(1);

    glLineWidth(1);
    glBegin(GL_LINES);
      for (INT i = 0; i < Segments.size(); i++)
      {
        vec
          bn = vec(Points[Segments[i].P1].Z - Points[Segments[i].P0].Z, 0,
                  Points[Segments[i].P0].X - Points[Segments[i].P1].X).Normalize() *
               RoadHalfWidth / (Width / 2),
          sn = vec(Points[Segments[i].P1].Z - Points[Segments[i].P0].Z, 0,
                  Points[Segments[i].P0].X - Points[Segments[i].P1].X).Normalize() *
               (RoadHalfWidth + RoadShoulderWidth) / (Width / 2);
        glColor3d(0.9, 0.9, 0.9);
        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1, -Points[Segments[i].P0].Z / (Height / 2) + 1);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1, -Points[Segments[i].P1].Z / (Height / 2) + 1);
        // Borders.
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1 - bn.X, -Points[Segments[i].P0].Z / (Height / 2) + 1 + bn.Z);
        glColor3d(0.9, 0.9, 0.9);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 - bn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 + bn.Z);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 - bn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 + bn.Z);
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1 - bn.X, -Points[Segments[i].P1].Z / (Height / 2) + 1 + bn.Z);

        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1 + bn.X, -Points[Segments[i].P0].Z / (Height / 2) + 1 - bn.Z);
        glColor3d(0.9, 0.9, 0.9);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 + bn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 - bn.Z);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 + bn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 - bn.Z);
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1 + bn.X, -Points[Segments[i].P1].Z / (Height / 2) + 1 - bn.Z);
        // Shoulders.
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1 - sn.X, -Points[Segments[i].P0].Z / (Height / 2) + 1 + sn.Z);
        glColor3d(0.9, 0.9, 0.9);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 - sn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 + sn.Z);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 - sn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 + sn.Z);
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1 - sn.X, -Points[Segments[i].P1].Z / (Height / 2) + 1 + sn.Z);

        glVertex2d(Points[Segments[i].P0].X / (Width / 2) - 1 + sn.X, -Points[Segments[i].P0].Z / (Height / 2) + 1 - sn.Z);
        glColor3d(0.9, 0.9, 0.9);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 + sn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 - sn.Z);
        glVertex2d((Points[Segments[i].P0].X + Points[Segments[i].P1].X) / 2 / (Width / 2) - 1 + sn.X,
                  -(Points[Segments[i].P0].Z + Points[Segments[i].P1].Z) / 2 / (Height / 2) + 1 - sn.Z);
        glColor3d(0.2, 0.2, 0.2);
        glVertex2d(Points[Segments[i].P1].X / (Width / 2) - 1 + sn.X, -Points[Segments[i].P1].Z / (Height / 2) + 1 - sn.Z);
      }
      if (!FirstPoint && EditMode == EDIT_ROAD)
      {
        DOUBLE x = Ani->MsX, y = Ani->MsY, dx = 1, dy = 1;
        ray Ray;
        Ray.Dir = Ani->Camera.Dir * Ani->Camera.ProjDist +
                  Ani->Camera.Right * (x / w * Ani->Camera.Width - Ani->Camera.Width / 2) +
                  Ani->Camera.Up * (Ani->Camera.Height / 2 - y / h * Ani->Camera.Height);
        Ray.Org = Ani->Camera.Loc + Ray.Dir;
        Ray.Dir.Normalize();
        
        cd::collision Collision = Plane.Intersect(Ray, 0, 1);
        if (Collision.IsCollide)
        {
          if (w > h)
            dx = w / h;
          else
            dy = h / w;
          if ((Collision.Intersection.Location - PrevPoint).Length2D() < 1.5)
            glColor3d(1.0, 0.0, 0.0);
          else
            glColor3d(0.0, 1.0, 0.0);

          vec
            P0(PrevPoint.X / (Width / 2) - 1, 0, PrevPoint.Z / (Height / 2) - 1),
            P1(Collision.Intersection.Location.X / (Width / 2) - 1, 0,
               Collision.Intersection.Location.Z / (Height / 2) - 1),
            bn = vec(Collision.Intersection.Location.Z - PrevPoint.Z, 0,
                    PrevPoint.X - Collision.Intersection.Location.X).Normalize() *
                 RoadHalfWidth / (Width / 2),
            sn = vec(Collision.Intersection.Location.Z - PrevPoint.Z, 0,
                    PrevPoint.X - Collision.Intersection.Location.X).Normalize() *
                 (RoadHalfWidth + RoadShoulderWidth) / (Width / 2);

          glVertex2d(P0.X, -P0.Z);
          glVertex2d(P1.X, -P1.Z);
          // Borders.
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P0.X - bn.X, -P0.Z + bn.Z);
          glColor3d(0.9, 0.9, 0.9);
          glVertex2d((P0.X + P1.X) / 2 - bn.X, -(P0.Z + P1.Z) / 2 + bn.Z);
          glVertex2d((P0.X + P1.X) / 2 - bn.X, -(P0.Z + P1.Z) / 2 + bn.Z);
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P1.X - bn.X, -P1.Z + bn.Z);
          
          glVertex2d(P0.X + bn.X, -P0.Z - bn.Z);
          glColor3d(0.9, 0.9, 0.9);
          glVertex2d((P0.X + P1.X) / 2 + bn.X, -(P0.Z + P1.Z) / 2 - bn.Z);
          glVertex2d((P0.X + P1.X) / 2 + bn.X, -(P0.Z + P1.Z) / 2 - bn.Z);
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P1.X + bn.X, -P1.Z - bn.Z);
          // Shoulders.
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P0.X - sn.X, -P0.Z + sn.Z);
          glColor3d(0.9, 0.9, 0.9);
          glVertex2d((P0.X + P1.X) / 2 - sn.X, -(P0.Z + P1.Z) / 2 + sn.Z);
          glVertex2d((P0.X + P1.X) / 2 - sn.X, -(P0.Z + P1.Z) / 2 + sn.Z);
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P1.X - sn.X, -P1.Z + sn.Z);
          
          glVertex2d(P0.X + sn.X, -P0.Z - sn.Z);
          glColor3d(0.9, 0.9, 0.9);
          glVertex2d((P0.X + P1.X) / 2 + sn.X, -(P0.Z + P1.Z) / 2 - sn.Z);
          glVertex2d((P0.X + P1.X) / 2 + sn.X, -(P0.Z + P1.Z) / 2 - sn.Z);
          glColor3d(0.2, 0.2, 0.2);
          glVertex2d(P1.X + sn.X, -P1.Z - sn.Z);
        }
      }
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
      for (INT i = 0; i < Houses.size(); i++)
      {
        glColor3d(0.8, 0.0, 0.0);
        if (i == Houses.size() - 1 && Houses[i].size() > 0)
        {
          DOUBLE x = Ani->MsX, y = Ani->MsY, dx = 1, dy = 1;
          ray Ray;
          Ray.Dir = Ani->Camera.Dir * Ani->Camera.ProjDist +
                    Ani->Camera.Right * (x / w * Ani->Camera.Width - Ani->Camera.Width / 2) +
                    Ani->Camera.Up * (Ani->Camera.Height / 2 - y / h * Ani->Camera.Height);
          Ray.Org = Ani->Camera.Loc + Ray.Dir;
          Ray.Dir.Normalize();

          cd::collision Collision = Plane.Intersect(Ray, 0, 1);
          if (Collision.IsCollide)
          {
            if (w > h)
              dx = w / h;
            else
              dy = h / w;
            glVertex2d(Points[Houses[i].back()].X / (Width / 2) - 1, -Points[Houses[i].back()].Z / (Height / 2) + 1);
            glVertex2d(Collision.Intersection.Location.X / (Width / 2) - 1, -Collision.Intersection.Location.Z / (Height / 2) + 1);

            if (Houses[i].size() > 1)
            {
              glVertex2d(Collision.Intersection.Location.X / (Width / 2) - 1, -Collision.Intersection.Location.Z / (Height / 2) + 1);
              glColor3d(0.1, 0.0, 0.0);
              glVertex2d(Points[Houses[i][0]].X / (Width / 2) - 1, -Points[Houses[i][0]].Z / (Height / 2) + 1);
              glColor3d(0.8, 0.0, 0.0);
            }
          }
        }
        else if (Houses[i].size() > 2)
        {
          glVertex2d(Points[Houses[i].back()].X / (Width / 2) - 1, -Points[Houses[i].back()].Z / (Height / 2) + 1);
          glVertex2d(Points[Houses[i][0]].X / (Width / 2) - 1,     -Points[Houses[i][0]].Z / (Height / 2) + 1);
        }
        if (Houses[i].size() > 1)
        {
          for (INT j = 0; j < Houses[i].size() - 1; j++)
          {
            glVertex2d(Points[Houses[i][j]].X / (Width / 2) - 1,     -Points[Houses[i][j]].Z / (Height / 2) + 1);
            glVertex2d(Points[Houses[i][j + 1]].X / (Width / 2) - 1, -Points[Houses[i][j + 1]].Z / (Height / 2) + 1);
          }
        }
      }
    glEnd();

    glPopMatrix();

    glFinish();
  }
} /* End of 'tcg::unit_road::Render' function */

/* Add point function.
 * ARGUMENTS:
 *   - point:
 *       const vec &Point;
 * RETURNS: None.
 */
VOID tcg::unit_road::AddPoint( const vec &Point )
{
  for (INT i = 0; i < Points.size(); i++)
    if (fabs(Points[i].X - Point.X) < tsg::Threshold * 100 && fabs(Points[i].Z - Point.Z) < tsg::Threshold * 100)
      return;
  Points.push_back(Point);
} /* End of 'tcg::unit_road::AddPoint' function */

/* Add segment function.
 * ARGUMENTS:
 *   - segment points:
 *       const vec &P0, &P1;
 * RETURNS: None.
 */
VOID tcg::unit_road::AddSegment( const vec &P0, const vec &P1 )
{
  DOUBLE Scale = 5;
  INT I0 = -1, I1 = -1;
  for (INT i = 0; i < Segments.size(); i++)
  {
    if (sqrt((Points[Segments[i].P0].X - P0.X) * (Points[Segments[i].P0].X - P0.X) +
             (Points[Segments[i].P0].Z - P0.Z) * (Points[Segments[i].P0].Z - P0.Z)) < RoadHalfWidth * Scale)
      I0 = Segments[i].P0;
    if (sqrt((Points[Segments[i].P1].X - P0.X) * (Points[Segments[i].P1].X - P0.X) +
             (Points[Segments[i].P1].Z - P0.Z) * (Points[Segments[i].P1].Z - P0.Z)) < RoadHalfWidth * Scale)
      I0 = Segments[i].P1;
    if (sqrt((Points[Segments[i].P0].X - P1.X) * (Points[Segments[i].P0].X - P1.X) +
             (Points[Segments[i].P0].Z - P1.Z) * (Points[Segments[i].P0].Z - P1.Z)) < RoadHalfWidth * Scale)
      I1 = Segments[i].P0;
    if (sqrt((Points[Segments[i].P1].X - P1.X) * (Points[Segments[i].P1].X - P1.X) +
             (Points[Segments[i].P1].Z - P1.Z) * (Points[Segments[i].P1].Z - P1.Z)) < RoadHalfWidth * Scale)
      I1 = Segments[i].P1;
  }
  if (I0 == -1)
    Points.push_back(P0), I0 = Points.size() - 1;
  if (I1 == -1)
    Points.push_back(P1), I1 = Points.size() - 1;
  Segments.push_back(segment(I0, I1));
} /* End of 'tcg::unit_road::AddSegment' function */

/* Build houses function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::unit_road::BuildHouses( VOID )
{
  std::vector<triangle> HouseTriangles, TmpTriangles;
  std::vector<triangle> IDs;
  std::vector<INT> Heights;
  std::vector<tsg::TVec<uv>> TexCoords;

  std::vector<INT> RoofBorder, Ceil, Floor;

  DOUBLE RoofW = sqrt(0.2 * 0.2 + 0.35 * 0.35);

  srand((INT)Ani->Time);

  for (INT i = 0; i < Houses.size(); i++)
  {
    INT NoofFloors = ::rand() % 3 + 1;

    TmpTriangles.clear();
    RoofBorder.clear();
    Ceil.clear();
    Floor.clear();
    Triangulate(Points, Houses[i], TmpTriangles);
    vec Center(0);
    for (INT j = 0; j < Houses[i].size(); j++)
    {
      Center += Points[Houses[i][j]];
      Points[Houses[i][j]].Y = 0.4 + 0.7 * NoofFloors + 0.3;
    }
    INT CenterNo = Points.size();
    Points.push_back(Center / Houses[i].size());
    // Flat roof.
    for (INT j = 0; j < TmpTriangles.size(); j++)
    {
      HouseTriangles.push_back(TmpTriangles[j]);
      IDs.push_back(triangle(0, 0, 0));
      Heights.push_back(CenterNo);
      TexCoords.push_back(
        tsg::TVec<uv>(
          uv(Points[HouseTriangles.back().P[0]].X / Width, Points[HouseTriangles.back().P[0]].Z / Height),
          uv(Points[HouseTriangles.back().P[1]].X / Width, Points[HouseTriangles.back().P[1]].Z / Height),
          uv(Points[HouseTriangles.back().P[2]].X / Width, Points[HouseTriangles.back().P[2]].Z / Height)
        )
      );
    }
    for (INT j = 0; j < Houses[i].size(); j++)
    {
      vec
        Cur = Points[Houses[i][j]],
        PrevDir = Cur - Points[Houses[i][j == 0 ? Houses[i].size() - 1 : j - 1]],
        NextDir = Points[Houses[i][(j + 1) % Houses[i].size()]] - Cur,
        Dir = LineIntersectLine(vec(-PrevDir.Z, 0, PrevDir.X).Normalize(), PrevDir,
                                vec(-NextDir.Z, 0, NextDir.X).Normalize(), NextDir);
      RoofBorder.push_back(Points.size());
      Points.push_back(vec(Cur.X + Dir.X * 0.2, 0.4 + 0.7 * NoofFloors - 0.05, Cur.Z + Dir.Z * 0.2));
      Ceil.push_back(Points.size());
      Points.push_back(vec(Cur.X + Dir.X * 0.15, 0.4 + 0.7 * NoofFloors, Cur.Z + Dir.Z * 0.15));
      Floor.push_back(Points.size());
      Points.push_back(vec(Cur.X + Dir.X * 0.15, 0.4, Cur.Z + Dir.Z * 0.15));
    }

    TmpTriangles.clear();
    Triangulate(Points, Floor, TmpTriangles);
    for (INT j = 0; j < TmpTriangles.size(); j++)
    {
      HouseTriangles.push_back(triangle(TmpTriangles[j].P[2], TmpTriangles[j].P[1], TmpTriangles[j].P[0]));
      IDs.push_back(triangle(4, 4, 4));
      Heights.push_back(CenterNo);
      TexCoords.push_back(
        tsg::TVec<uv>(
          uv(Points[HouseTriangles.back().P[0]].X, Points[HouseTriangles.back().P[0]].Z),
          uv(Points[HouseTriangles.back().P[1]].X, Points[HouseTriangles.back().P[1]].Z),
          uv(Points[HouseTriangles.back().P[2]].X, Points[HouseTriangles.back().P[2]].Z)
        )
      );
    }
    for (INT j = 0; j < Houses[i].size(); j++)
    {
      // Roof.
      DOUBLE len =
        (LineIntersectLine(Points[Houses[i][j]],
                           vec(Points[Houses[i][(j + 1) % Houses[i].size()]].Z - Points[Houses[i][j]].Z, 0,
                               Points[Houses[i][j]].X - Points[Houses[i][(j + 1) % Houses[i].size()]].X),
                           Points[RoofBorder[j]],
                           Points[RoofBorder[(j + 1) % Houses[i].size()]] - Points[RoofBorder[j]]) -
         Points[RoofBorder[j]]).Length2D();
      if (((Points[RoofBorder[(j + 1) % Houses[i].size()]] - Points[RoofBorder[j]]).Normalize() &
          (Points[Houses[i][j]] - Points[RoofBorder[j]]).Normalize()) < 0)
        len = -len;

      HouseTriangles.push_back(triangle(RoofBorder[j],
                                        RoofBorder[(j + 1) % Houses[i].size()],
                                        Houses[i][(j + 1) % Houses[i].size()]));
      IDs.push_back(triangle(1, 1, 1));
      Heights.push_back(CenterNo);
      TexCoords.push_back(
        tsg::TVec<uv>(
          uv(0, 0),
          uv((Points[RoofBorder[(j + 1) % Houses[i].size()]] - Points[RoofBorder[j]]).Length2D() / RoofW, 0),
          uv((len + (Points[Houses[i][(j + 1) % Houses[i].size()]] - Points[Houses[i][j]]).Length2D()) / RoofW, 1)
        )
      );
      HouseTriangles.push_back(triangle(RoofBorder[j], Houses[i][(j + 1) % Houses[i].size()], Houses[i][j]));
      IDs.push_back(triangle(1, 1, 1));
      Heights.push_back(CenterNo);
      TexCoords.push_back(
        tsg::TVec<uv>(
          uv(0, 0),
          uv((len + (Points[Houses[i][(j + 1) % Houses[i].size()]] - Points[Houses[i][j]]).Length2D()) / RoofW, 1),
          uv(len / RoofW, 1)
        )
      );

      // Wall.
      vec WallDir = Points[Floor[(j + 1) % Houses[i].size()]] - Points[Floor[j]], WallDirNorm(WallDir.Normalizing());
      DOUBLE WallLength = WallDir.Length2D();

      HouseTriangles.push_back(triangle(Floor[j], Floor[(j + 1) % Houses[i].size()], Ceil[(j + 1) % Houses[i].size()]));
      IDs.push_back(triangle(2, 2, 2));
      Heights.push_back(CenterNo);
      TexCoords.push_back(tsg::TVec<uv>(uv(0, 0),
                                        uv(WallLength / 0.7 * 4 / 3, 0),
                                        uv(WallLength / 0.7 * 4 / 3, 2 * NoofFloors)));

      HouseTriangles.push_back(triangle(Floor[j], Ceil[(j + 1) % Houses[i].size()], Ceil[j]));
      IDs.push_back(triangle(2, 2, 2));
      Heights.push_back(CenterNo);
      TexCoords.push_back(tsg::TVec<uv>(uv(0, 0), uv(WallLength / 0.7 * 4 / 3, 2 * NoofFloors), uv(0, 2 * NoofFloors)));

      // Windows.
      INT NoofWindows = WallLength / 0.5;
      vec norm = vec(-WallDir.Z, 0, WallDir.X).Normalize() * 0.001;
      for (INT k = 0; k < NoofWindows; k++)
      {
        DOUBLE WindowCenter = (k + 0.5) / NoofWindows;
        for (INT n = 0; n < NoofFloors; n++)
        {
          Points.push_back(vec(Points[Floor[j]].X + WallDir.X * WindowCenter - WallDirNorm.X * 0.35 / 3,
                               0.4 + 0.2 + 0.7 * n,
                               Points[Floor[j]].Z + WallDir.Z * WindowCenter - WallDirNorm.Z * 0.35 / 3) + norm);
          Points.push_back(vec(Points[Floor[j]].X + WallDir.X * WindowCenter + WallDirNorm.X * 0.35 / 3,
                               0.4 + 0.2 + 0.7 * n,
                               Points[Floor[j]].Z + WallDir.Z * WindowCenter + WallDirNorm.Z * 0.35 / 3) + norm);
          Points.push_back(vec(Points[Floor[j]].X + WallDir.X * WindowCenter + WallDirNorm.X * 0.35 / 3,
                               0.4 + 0.55 + 0.7 * n,
                               Points[Floor[j]].Z + WallDir.Z * WindowCenter + WallDirNorm.Z * 0.35 / 3) + norm);
          Points.push_back(vec(Points[Floor[j]].X + WallDir.X * WindowCenter - WallDirNorm.X * 0.35 / 3,
                               0.4 + 0.55 + 0.7 * n,
                               Points[Floor[j]].Z + WallDir.Z * WindowCenter - WallDirNorm.Z * 0.35 / 3) + norm);

          HouseTriangles.push_back(triangle(Points.size() - 4, Points.size() - 3, Points.size() - 2));
          IDs.push_back(triangle(3, 3, 3));
          Heights.push_back(CenterNo);
          TexCoords.push_back(tsg::TVec<uv>(uv(0, 0), uv(1, 0), uv(1, 1)));

          HouseTriangles.push_back(triangle(Points.size() - 4, Points.size() - 2, Points.size() - 1));
          IDs.push_back(triangle(3, 3, 3));
          Heights.push_back(CenterNo);
          TexCoords.push_back(tsg::TVec<uv>(uv(0, 0), uv(1, 1), uv(0, 1)));
        }
      }
      // Pile.
      Points.push_back(vec(Points[Houses[i][j]].X - 0.05,  -4, Points[Houses[i][j]].Z + 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X + 0.05,  -4, Points[Houses[i][j]].Z + 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X + 0.05,  -4, Points[Houses[i][j]].Z - 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X - 0.05,  -4, Points[Houses[i][j]].Z - 0.05));

      Points.push_back(vec(Points[Houses[i][j]].X - 0.05, 0.4, Points[Houses[i][j]].Z + 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X + 0.05, 0.4, Points[Houses[i][j]].Z + 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X + 0.05, 0.4, Points[Houses[i][j]].Z - 0.05));
      Points.push_back(vec(Points[Houses[i][j]].X - 0.05, 0.4, Points[Houses[i][j]].Z - 0.05));

      for (INT k = 0; k < 8; k++)
        Heights.push_back(CenterNo);
      for (INT k = 0; k < 4; k++)
      {
        TexCoords.push_back(tsg::TVec<uv>(uv(0, 0), uv(0.25, 0), uv(0.25, 0)));
        TexCoords.push_back(tsg::TVec<uv>(uv(0, 0), uv(0.25, 0), uv(0, 0)));

        IDs.push_back(triangle(6, 6, 5));
        IDs.push_back(triangle(6, 5, 5));
      }
      HouseTriangles.push_back(triangle(Points.size() - 8, Points.size() - 7, Points.size() - 3));
      HouseTriangles.push_back(triangle(Points.size() - 8, Points.size() - 3, Points.size() - 4));

      HouseTriangles.push_back(triangle(Points.size() - 7, Points.size() - 6, Points.size() - 2));
      HouseTriangles.push_back(triangle(Points.size() - 7, Points.size() - 2, Points.size() - 3));

      HouseTriangles.push_back(triangle(Points.size() - 6, Points.size() - 5, Points.size() - 1));
      HouseTriangles.push_back(triangle(Points.size() - 6, Points.size() - 1, Points.size() - 2));

      HouseTriangles.push_back(triangle(Points.size() - 5, Points.size() - 8, Points.size() - 4));
      HouseTriangles.push_back(triangle(Points.size() - 5, Points.size() - 4, Points.size() - 1));
    }
  }
  CreateVillage(Village, Ani, Points, HouseTriangles, IDs, TexCoords, Heights);
} /* End of 'BuildHouses' function */

/* Create landscape function.
 * ARGUMENTS:
 *   - road width and shoulder width:
 *       DOUBLE HalfWidth, Shoulder;
 * RETURN: None.
 */
VOID tcg::unit_road::CreateLandscape( DOUBLE HalfWidth, DOUBLE Shoulder )
{
  std::vector<road_segment> RoadSegments;

  IntersectRoadSegments(RoadSegments);
  SetRoadSegments(RoadSegments, HalfWidth, Shoulder);
  InterpolateRoadSegments(RoadSegments, HalfWidth, Shoulder);
  SetRoadSegments(RoadSegments, HalfWidth, Shoulder );
  InsertRoad(RoadSegments);
  SetTextureCoordinates(RoadSegments, HalfWidth);
  TriangulateRoad(RoadSegments, HalfWidth);
  TriangulateRoadShoulder(RoadSegments);
  BuildHouses();
} /* End of 'CreateLandscape' function */

/* END OF 'unit_road.cpp' FILE */
