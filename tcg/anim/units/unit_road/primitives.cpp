#include "unit_road.h"
#include "../../animation.h"
#include "../../../math/noise.h"

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
  Tri.Material->SetUniform("Height", 4.0f);
  Tri.Material->AddTexture(Ani->AddTexture("TextureHeight", "heightmap1.float"));
  Tri.Material->AddTexture(Ani->AddTexture("Texture", "mountain_light.jpg"));
  Tri.Material->AddTexture(Ani->AddTexture("ColorMap", "cm.g24"));
  Tri.Material->AddTexture(Ani->AddTexture("NormalMap", "normalmap1.short"));

  float
    octaves = 4,
    lacunarity = 4.5,
    H = 2.2;
  Tri.Material->SetUniform(         "H", H);
  Tri.Material->SetUniform(      "gain", 2.0f);
  Tri.Material->SetUniform("lacunarity", lacunarity);
  Tri.Material->SetUniform(   "octaves", octaves);
  Tri.Material->SetUniform(    "offset", 0.0f);
  float *exponent_array = new float[(int)octaves];
  float frequency = 1.0f;
  for (int i = 0; i < (int)octaves; i++)
  {
    exponent_array[i] = pow(frequency, -H);
    frequency *= lacunarity;
  }
  Tri.Material->AddTexture(Ani->AddTexture("ExponentArray", (int)octaves, 1, exponent_array));
  delete[] exponent_array;

  math::noise Noise;
  float *pix = new float[Noise.GetSize() * 2];
  for (int i = 0; i < Noise.GetSize(); i++)
  {
    pix[i] = Noise.GetTable(i);
    pix[i + Noise.GetSize()] = Noise.GetPerm(i);
  }
  Tri.Material->AddTexture(Ani->AddTexture("NoiseTex", Noise.GetSize(), 2, pix));
  delete[] pix;

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
      V[i].P0 = uv(Points[P0[i]].X / Width, Points[P0[i]].Z / Width);
      V[i].P1 = uv(Points[P1[i]].X / Width, Points[P1[i]].Z / Width);
      V[i].H0 = uv(Points[H0[i]].X / Width, Points[H0[i]].Z / Width);
      V[i].H1 = uv(Points[H1[i]].X / Width, Points[H1[i]].Z / Width);
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
  Tri.Material->AddTexture(Ani->AddTexture("ColorMap", "cm.g24"));

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

    V[i * 3].Height =     uv(Points[Heights[i].P[0]].X / Width, Points[Heights[i].P[0]].Z / Width);
    V[i * 3 + 1].Height = uv(Points[Heights[i].P[1]].X / Width, Points[Heights[i].P[1]].Z / Width);
    V[i * 3 + 2].Height = uv(Points[Heights[i].P[2]].X / Width, Points[Heights[i].P[2]].Z / Width);

    V[i * 3].P0 =     uv(Points[P0[i].P[0]].X / Width, Points[P0[i].P[0]].Z / Width);
    V[i * 3 + 1].P0 = uv(Points[P0[i].P[1]].X / Width, Points[P0[i].P[1]].Z / Width);
    V[i * 3 + 2].P0 = uv(Points[P0[i].P[2]].X / Width, Points[P0[i].P[2]].Z / Width);

    V[i * 3].P1 =     uv(Points[P1[i].P[0]].X / Width, Points[P1[i].P[0]].Z / Width);
    V[i * 3 + 1].P1 = uv(Points[P1[i].P[1]].X / Width, Points[P1[i].P[1]].Z / Width);
    V[i * 3 + 2].P1 = uv(Points[P1[i].P[2]].X / Width, Points[P1[i].P[2]].Z / Width);

    V[i * 3].H0 =     uv(Points[H0[i].P[0]].X / Width, Points[H0[i].P[0]].Z / Width);
    V[i * 3 + 1].H0 = uv(Points[H0[i].P[1]].X / Width, Points[H0[i].P[1]].Z / Width);
    V[i * 3 + 2].H0 = uv(Points[H0[i].P[2]].X / Width, Points[H0[i].P[2]].Z / Width);

    V[i * 3].H1 =     uv(Points[H1[i].P[0]].X / Width, Points[H1[i].P[0]].Z / Width);
    V[i * 3 + 1].H1 = uv(Points[H1[i].P[1]].X / Width, Points[H1[i].P[1]].Z / Width);
    V[i * 3 + 2].H1 = uv(Points[H1[i].P[2]].X / Width, Points[H1[i].P[2]].Z / Width);

    I[i * 3] =     i * 3;
    I[i * 3 + 1] = i * 3 + 1;
    I[i * 3 + 2] = i * 3 + 2;
  }

  Tri.SetBuffers(V, I, Triangles.size() * 3, Triangles.size() * 3);

  Tri.Material = Ani->AddMaterial("road", "road");
  Tri.Material->AddTexture(Ani->AddTexture("road", "road.jpg"));
  Tri.Material->SetUniform("Height", 4.0f);
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
