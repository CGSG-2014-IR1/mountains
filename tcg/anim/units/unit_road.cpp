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

#include "../../def.h"

#include "../animation.h"
#include "unit_road.h"

/* Create mountain function.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 *   - points:
 *       const std::vector<vec> &Points;
 *   - triangles:
 *       const std::vector<math::triangle> &Triangles;
 *   - IDs:
 *       const std::vector<math::triangle> &IDs;
 * RETURNS: None.
 */
VOID tcg::unit_road::CreateMountain( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
        const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs )
{
  Tri.DeleteBuffers();
  vertex *V = new vertex[Points.size()];
  INT *I = new INT[Triangles.size() * 3];

  for (INT i = 0; i < Points.size(); i++)
  {
    V[i].Pos = Points[i];
    V[i].UV = uv(V[i].Pos.X / 2, -V[i].Pos.Z / 2);
    V[i].ID = IDs[i];
  }
  for (INT i = 0; i < Triangles.size(); i++)
  {
    I[i * 3] =     Triangles[i].P[0];
    I[i * 3 + 1] = Triangles[i].P[1];
    I[i * 3 + 2] = Triangles[i].P[2];
  }

  Tri.SetBuffers(V, I, Points.size(), Triangles.size() * 3);

  Tri.Material = Ani->AddMaterial("mountain", "mountain");
  Tri.Material->AddUniform("Height", 4.0f);
  Tri.Material->AddTexture(Ani->AddTexture("TextureHeight", "heightmap1.float"));
  Tri.Material->AddTexture(Ani->AddTexture("Texture", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::unit_road::CreateMountain' function */

/* Create mountain function.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 *   - points:
 *       const std::vector<vec> &Points;
 *   - triangles:
 *       const std::vector<math::triangle> &Triangles;
 *   - IDs:
 *       const std::vector<math::triangle> &IDs;
 *   - height identifiers:
 *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
 * RETURNS: None.
 */
VOID tcg::unit_road::CreateMountain( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
  const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs,
  const std::vector<INT> &P0, const std::vector<INT> &P1, const std::vector<INT> &H0, const std::vector<INT> &H1 )
{
  Tri.DeleteBuffers();

  vertex *V = new vertex[Points.size()];
  INT *I = new INT[Triangles.size() * 3];

  for (INT i = 0; i < Points.size(); i++)
  {
    V[i].Pos = Points[i];
    V[i].UV = uv(V[i].Pos.X / 2, -V[i].Pos.Z / 2);
    V[i].ID = IDs[i];
    if (V[i].ID == 1)
    {
      V[i].P0 = uv(Points[P0[i]].X, Points[P0[i]].Z);
      V[i].P1 = uv(Points[P1[i]].X, Points[P1[i]].Z);
      V[i].H0 = uv(Points[H0[i]].X / 60, Points[H0[i]].Z / 60);
      V[i].H1 = uv(Points[H1[i]].X / 60, Points[H1[i]].Z / 60);
    }
  }
  for (INT i = 0; i < Triangles.size(); i++)
  {
    I[i * 3] =     Triangles[i].P[0];
    I[i * 3 + 1] = Triangles[i].P[1];
    I[i * 3 + 2] = Triangles[i].P[2];
  }

  Tri.SetBuffers(V, I, Points.size(), Triangles.size() * 3);

  Tri.Material = Ani->AddMaterial("mountain", "mountain");
  Tri.Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("light", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::unit_road::CreateMountain' function */

/* Create road function.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 *   - points:
 *       const std::vector<vec> &Points;
 *   - triangles:
 *       const std::vector<math::triangle> &Triangles;
 *   - texture coordinates:
 *       const std::vector<tsg::TVec<uv>> &TextureCoords;
 *   - heights:
 *       const std::vector<INT> &Heights;
 *   - height identifiers:
 *       const std::vector<math::triangle> &P0, &P1, &H0, &H1;
 * RETURNS: None.
 */
VOID tcg::unit_road::CreateRoad( tcg::primitive::trimesh &Tri, anim *Ani, const std::vector<vec> &Points, const std::vector<math::triangle> &Triangles,
  const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<math::triangle> &Heights,
  const std::vector<math::triangle> &P0, const std::vector<math::triangle> &P1,
  const std::vector<math::triangle> &H0, const std::vector<math::triangle> &H1 )
{
  Tri.DeleteBuffers();

  vertex *V = new vertex[Triangles.size() * 3];
  INT *I = new INT[Triangles.size() * 3];

  for (INT i = 0; i < Triangles.size(); i++)
  {
    V[i * 3].Pos =     Points[Triangles[i].P[0]];
    V[i * 3 + 1].Pos = Points[Triangles[i].P[1]];
    V[i * 3 + 2].Pos = Points[Triangles[i].P[2]];

    V[i * 3].Norm = V[i * 3 + 1].Norm = V[i * 3 + 2].Norm = vec(0, 1, 0);

    V[i * 3].UV =     TextureCoords[i].X;
    V[i * 3 + 1].UV = TextureCoords[i].Y;
    V[i * 3 + 2].UV = TextureCoords[i].Z;

    V[i * 3].Height =     uv(Points[Heights[i].P[0]].X / 60, Points[Heights[i].P[0]].Z / 60);
    V[i * 3 + 1].Height = uv(Points[Heights[i].P[1]].X / 60, Points[Heights[i].P[1]].Z / 60);
    V[i * 3 + 2].Height = uv(Points[Heights[i].P[2]].X / 60, Points[Heights[i].P[2]].Z / 60);

    V[i * 3].P0 =     uv(Points[P0[i].P[0]].X, Points[P0[i].P[0]].Z);
    V[i * 3 + 1].P0 = uv(Points[P0[i].P[1]].X, Points[P0[i].P[1]].Z);
    V[i * 3 + 2].P0 = uv(Points[P0[i].P[2]].X, Points[P0[i].P[2]].Z);

    V[i * 3].P1 =     uv(Points[P1[i].P[0]].X, Points[P1[i].P[0]].Z);
    V[i * 3 + 1].P1 = uv(Points[P1[i].P[1]].X, Points[P1[i].P[1]].Z);
    V[i * 3 + 2].P1 = uv(Points[P1[i].P[2]].X, Points[P1[i].P[2]].Z);

    V[i * 3].H0 =     uv(Points[H0[i].P[0]].X / 60, Points[H0[i].P[0]].Z / 60);
    V[i * 3 + 1].H0 = uv(Points[H0[i].P[1]].X / 60, Points[H0[i].P[1]].Z / 60);
    V[i * 3 + 2].H0 = uv(Points[H0[i].P[2]].X / 60, Points[H0[i].P[2]].Z / 60);

    V[i * 3].H1 =     uv(Points[H1[i].P[0]].X / 60, Points[H1[i].P[0]].Z / 60);
    V[i * 3 + 1].H1 = uv(Points[H1[i].P[1]].X / 60, Points[H1[i].P[1]].Z / 60);
    V[i * 3 + 2].H1 = uv(Points[H1[i].P[2]].X / 60, Points[H1[i].P[2]].Z / 60);

    I[i * 3] =     i * 3;
    I[i * 3 + 1] = i * 3 + 1;
    I[i * 3 + 2] = i * 3 + 2;
  }

  Tri.SetBuffers(V, I, Triangles.size() * 3, Triangles.size() * 3);

  Tri.Material = Ani->AddMaterial("road", "road");
  Tri.Material->AddTexture(Ani->AddTexture("road", "road.jpg"));
  Tri.Material->AddUniform("Height", 4.0f);
  Tri.Material->AddTexture(Ani->AddTexture("TextureHeight", "heightmap1.float"));
  Tri.Material->AddTexture(Ani->AddTexture("light", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::unit_road::CreateRoad' function */

/* Create village function.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 *   - points:
 *       const std::vector<vec> &Points;
 *   - triangles:
 *       const std::vector<math::triangle> &Triangles;
 *   - IDs:
 *       const std::vector<math::triangle> &IDs;
 *   - texture coordinates:
 *       const std::vector<tsg::TVec<uv>> &TextureCoords;
 *   - heights:
 *       const std::vector<INT> &Heights;
 * RETURNS: None.
 */
VOID tcg::unit_road::CreateVillage( tcg::primitive::patch3 &Tri, anim *Ani, const std::vector<vec> &Points,
  const std::vector<math::triangle> &Triangles, const std::vector<math::triangle> &IDs,
  const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<INT> &Heights )
{
  Tri.DeleteBuffers();

  vertex *V = new vertex[Triangles.size() * 3];
  INT *I = new INT[Triangles.size() * 3];

  for (INT i = 0; i < Triangles.size(); i++)
  {
    V[i * 3].Pos =     Points[Triangles[i].P[0]];
    V[i * 3 + 1].Pos = Points[Triangles[i].P[1]];
    V[i * 3 + 2].Pos = Points[Triangles[i].P[2]];

    V[i * 3].Norm = V[i * 3 + 1].Norm = V[i * 3 + 2].Norm =
      ((Points[Triangles[i].P[1]] - Points[Triangles[i].P[0]]) %
       (Points[Triangles[i].P[2]] - Points[Triangles[i].P[0]])).Normalize();

    V[i * 3].UV =     TextureCoords[i].X;
    V[i * 3 + 1].UV = TextureCoords[i].Y;
    V[i * 3 + 2].UV = TextureCoords[i].Z;

    V[i * 3].Height = V[i * 3 + 1].Height = V[i * 3 + 2].Height =
      uv(Points[Heights[i]].X / 60, Points[Heights[i]].Z / 60);

    V[i * 3].ID =     IDs[i].P[0];
    V[i * 3 + 1].ID = IDs[i].P[1];
    V[i * 3 + 2].ID = IDs[i].P[2];

    I[i * 3] =     i * 3;
    I[i * 3 + 1] = i * 3 + 1;
    I[i * 3 + 2] = i * 3 + 2;
  }

  Tri.SetBuffers(V, I, Triangles.size() * 3, Triangles.size() * 3);

  Tri.Material = Ani->AddMaterial("house", "house");
  Tri.Material->AddTexture(Ani->AddTexture("roof", "roof.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("flat_roof", "flat_roof.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("wall", "wall.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("window", "window.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("concrete", "concrete.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("concrete_panels", "concrete_panels.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::unit_road::CreateVillage' function */

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::unit_road::unit_road( anim *Ani ) :
  unit(Ani), Ani(Ani), Mountain(Ani), Road(Ani), Village(Ani), IsLandscape(FALSE), FirstPoint(TRUE),
  Plane(vec(1 - 4, 0, 1 - 4), vec(0, 0, 58 + 8), vec(58 + 8, 0, 0)), EditMode(EDIT_TRIANGLES), ScaleY(1)
{
  Houses.push_back(std::vector<INT>());

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
  //for (INT i = 0; i <= 32; i += 1)
  //  for (INT j = 0; j <= 32; j += 1)
  //    AddPoint(vec(i / 32.0 * Width, 0, j / 32.0 * Height));

  math::Triangulate(Points, Triangles);

  //AddSegment(vec(-10 + 30, 0, 0 + 30), vec(10 + 30, 0, 0 + 30));
  //AddSegment(vec(0 + 30, 0, -10 + 30), vec(0 + 30, 0, 10 + 30));

  std::vector<INT> IDs;
  for (INT i = 0; i < Points.size(); i++)
    IDs.push_back(0);

  CreateMountain(Mountain, Ani, Points, Triangles, IDs);
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
  static BOOL IsWireframe = FALSE, IsClick = FALSE, IsNoTranslate;
  static INT ClickMsX, ClickMsY;
  static vec LookAt;
  static DOUBLE Dist, Angle;

  if (!IsLandscape)
  {
    if (Ani->KeysClick[VK_LBUTTON] &&
        Ani->MsX >= 0 && Ani->MsX < Ani->GetW() &&
        Ani->MsY >= 0 && Ani->MsY < Ani->GetH())
      IsClick = TRUE, ClickMsX = Ani->MsX, ClickMsY = Ani->MsY, IsNoTranslate = TRUE;
    else if (IsClick)
    {
      if (Ani->Keys[VK_LBUTTON])
      {
        DOUBLE dx = 1, dy = 1, w = Ani->GetW(), h = Ani->GetH();
        if (w > h)
          dx = w / h;
        else
          dy = h / w;
        if (!IsNoTranslate)
          Ani->Camera.Translate(vecf(-Ani->MsDeltaX / w * dx * Ani->Camera.Loc.Y / 1.5, 0,
                                    -Ani->MsDeltaY / h * dy * Ani->Camera.Loc.Y / 1.5));
        else if (abs(ClickMsX - Ani->MsX) >= 3 && abs(ClickMsY - Ani->MsY) >= 3)
        {
          Ani->Camera.Translate(vecf((ClickMsX - Ani->MsX) / w * dx * Ani->Camera.Loc.Y / 1.5, 0,
                                    (ClickMsY - Ani->MsY) / h * dy * Ani->Camera.Loc.Y / 1.5));
          IsNoTranslate = FALSE;
        }
      }
      else
      {
        if (abs(ClickMsX - Ani->MsX) < 3 && abs(ClickMsY - Ani->MsY) < 3)
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
        IsClick = FALSE;
      }
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
    //if (Angle == 0)
    //{
    //  Angle += 5;
    //  Ani->Camera.SetLookAtLocUp(LookAt + vec(0, cos(tsg::Deg2Rad(Angle)) * Dist, sin(tsg::Deg2Rad(Angle)) * Dist),
    //    LookAt, vec(0.0, 1.0, 0.0));
    //}
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

    //if (EditMode == EDIT_TRIANGLES)
    //{
    //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //  glBegin(GL_TRIANGLES);
    //  glColor3d(1.0, 1.0, 1.0);
    //  for (INT i = 0; i < Triangles.size(); i++)
    //    for (INT j = 0; j < 3; j++)
    //      glVertex2d(Points[Triangles[i].P[j]].X / (Width / 2) - 1, -Points[Triangles[i].P[j]].Z / (Height / 2) + 1);
    //  glEnd();
    //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //}
    //glLineWidth(1);

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
  INT I0 = -1, I1 = -1;
  for (INT i = 0; i < Segments.size(); i++)
  {
    if (sqrt((Points[Segments[i].P0].X - P0.X) * (Points[Segments[i].P0].X - P0.X) +
             (Points[Segments[i].P0].Z - P0.Z) * (Points[Segments[i].P0].Z - P0.Z)) < RoadHalfWidth)
      I0 = Segments[i].P0;
    if (sqrt((Points[Segments[i].P1].X - P0.X) * (Points[Segments[i].P1].X - P0.X) +
             (Points[Segments[i].P1].Z - P0.Z) * (Points[Segments[i].P1].Z - P0.Z)) < RoadHalfWidth)
      I0 = Segments[i].P1;
    if (sqrt((Points[Segments[i].P0].X - P1.X) * (Points[Segments[i].P0].X - P1.X) +
             (Points[Segments[i].P0].Z - P1.Z) * (Points[Segments[i].P0].Z - P1.Z)) < RoadHalfWidth)
      I1 = Segments[i].P0;
    if (sqrt((Points[Segments[i].P1].X - P1.X) * (Points[Segments[i].P1].X - P1.X) +
             (Points[Segments[i].P1].Z - P1.Z) * (Points[Segments[i].P1].Z - P1.Z)) < RoadHalfWidth)
      I1 = Segments[i].P1;
  }
  if (I0 == -1)
    Points.push_back(P0), I0 = Points.size() - 1;
  if (I1 == -1)
    Points.push_back(P1), I1 = Points.size() - 1;
  Segments.push_back(segment(I0, I1));
} /* End of 'tcg::unit_road::AddSegment' function */

/* END OF 'unit_road.cpp' FILE */
