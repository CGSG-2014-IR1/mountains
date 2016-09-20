/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : primitive_trimesh.cpp
 * PURPOSE     : Computational geometry project.
 *               Primitive trimesh module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 16.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "animation.h"

#include "primitive_samples.h"

/* Class constructor.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
tcg::primitive::trimesh::trimesh( anim *Ani ) : prim(Ani)
{
} /* End of 'tcg::primitive::trimesh::trimesh' function */

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
VOID tcg::primitive::trimesh::CreateMountain( anim *Ani, const std::vector<vec> &Points,
        const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs )
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (VABuf != -1)
    glDeleteVertexArrays(1, (GLuint *)&VABuf);
  if (VBuf != -1)
    glDeleteBuffers(1, (GLuint *)&VBuf);
  if (IBuf != -1)
    glDeleteBuffers(1, (GLuint *)&IBuf);

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

  SetBuffers(V, I, Points.size(), Triangles.size() * 3);

  Material = Ani->AddMaterial("mountain", "mountain");
  Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));
  Material->AddTexture(Ani->AddTexture("light", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::primitive::trimesh::CreateMountain' function */

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
VOID tcg::primitive::trimesh::CreateMountain( anim *Ani, const std::vector<vec> &Points,
  const std::vector<math::triangle> &Triangles, const std::vector<INT> &IDs,
  const std::vector<INT> &P0, const std::vector<INT> &P1, const std::vector<INT> &H0, const std::vector<INT> &H1 )
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (VABuf != -1)
    glDeleteVertexArrays(1, (GLuint *)&VABuf);
  if (VBuf != -1)
    glDeleteBuffers(1, (GLuint *)&VBuf);
  if (IBuf != -1)
    glDeleteBuffers(1, (GLuint *)&IBuf);

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

  SetBuffers(V, I, Points.size(), Triangles.size() * 3);

  Material = Ani->AddMaterial("mountain", "mountain");
  Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));
  Material->AddTexture(Ani->AddTexture("light", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::primitive::trimesh::CreateMountain' function */

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
VOID tcg::primitive::trimesh::CreateRoad( anim *Ani, const std::vector<vec> &Points, const std::vector<math::triangle> &Triangles,
  const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<math::triangle> &Heights,
  const std::vector<math::triangle> &P0, const std::vector<math::triangle> &P1,
  const std::vector<math::triangle> &H0, const std::vector<math::triangle> &H1 )
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (VABuf != -1)
    glDeleteVertexArrays(1, (GLuint *)&VABuf);
  if (VBuf != -1)
    glDeleteBuffers(1, (GLuint *)&VBuf);
  if (IBuf != -1)
    glDeleteBuffers(1, (GLuint *)&IBuf);

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

  SetBuffers(V, I, Triangles.size() * 3, Triangles.size() * 3);

  Material = Ani->AddMaterial("road", "road");
  Material->AddTexture(Ani->AddTexture("road", "road.jpg"));
  Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));
  Material->AddTexture(Ani->AddTexture("light", "mountain_light.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::primitive::trimesh::CreateRoad' function */

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
VOID tcg::primitive::trimesh::CreateVillage( anim *Ani, const std::vector<vec> &Points,
  const std::vector<math::triangle> &Triangles, const std::vector<math::triangle> &IDs,
  const std::vector<tsg::TVec<uv>> &TextureCoords, const std::vector<INT> &Heights )
{
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (VABuf != -1)
    glDeleteVertexArrays(1, (GLuint *)&VABuf);
  if (VBuf != -1)
    glDeleteBuffers(1, (GLuint *)&VBuf);
  if (IBuf != -1)
    glDeleteBuffers(1, (GLuint *)&IBuf);

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

  SetBuffers(V, I, Triangles.size() * 3, Triangles.size() * 3);

  Material = Ani->AddMaterial("house", "house");
  Material->AddTexture(Ani->AddTexture("roof", "roof.jpg"));
  Material->AddTexture(Ani->AddTexture("flat_roof", "flat_roof.jpg"));
  Material->AddTexture(Ani->AddTexture("wall", "wall.jpg"));
  Material->AddTexture(Ani->AddTexture("window", "window.jpg"));
  Material->AddTexture(Ani->AddTexture("concrete", "concrete.jpg"));
  Material->AddTexture(Ani->AddTexture("concrete_panels", "concrete_panels.jpg"));
  Material->AddTexture(Ani->AddTexture("height", "mountain_height.jpg"));

  delete V;
  delete I;
} /* End of 'tcg::primitive::trimesh::CreateVillage' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::primitive::trimesh::~trimesh( VOID )
{
} /* End of 'tcg::primitive::trimesh::~trimesh' function */

/* END OF 'primitive_trimesh' FILE */
