/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : material.cpp
 * PURPOSE     : Computational geometry project.
 *               Material support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 15.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstring>

#include "../../animation.h"

#include "material.h"

/* Class constructor.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 *   - shader:
 *       shader *Shader;
 *   - ambient, diffuse and specular coefficients:
 *       const color &Ka, &Kd, &Ks;
 *   - shininess:
 *       FLT Shininess;
 */
tcg::material::material( CHAR *Name, shader *Shader, const color &Ka, const color &Kd, const color &Ks, FLT Shininess ) :
  Ka(Ka), Kd(Kd), Ks(Ks), Shininess(Shininess), Shader(Shader)
{
  strncpy(material::Name, Name, MAX_STR);
} /* End of 'tcg::material::material' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::material::~material( VOID )
{
} /* End of 'tcg::material::~material' function */

/* Add texture function.
 * ARGUMENTS:
 *   - texture:
 *       texture *Texture;
 * RETURNS: None.
 */
VOID tcg::material::AddTexture( texture *Texture )
{
  Textures.push_back(Texture);
} /* End of 'tcg::material::AddTexture' function */

/* Apply material function.
 * ARGUMENTS:
 *   - animation:
 *       anim *Ani;
 */
VOID tcg::material::Apply( anim *Ani )
{
  INT loc;
  matr MatrWVP = Ani->World * Ani->Camera.Matr.M * Ani->Camera.Proj.M;
  matr MatrNW = Ani->World.Inversing();

  Shader->Enable();

  loc = glGetUniformLocation(Shader->Program, "MatrWVP");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)MatrWVP);
  loc = glGetUniformLocation(Shader->Program, "MatrWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->World);
  loc = glGetUniformLocation(Shader->Program, "MatrView");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->Camera.Matr.M);
  loc = glGetUniformLocation(Shader->Program, "MatrProj");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)Ani->Camera.Proj.M);
  loc = glGetUniformLocation(Shader->Program, "MatrNWorld");
  if (loc != -1)
    glUniformMatrix4fv(loc, 1, FALSE, (FLT *)MatrNW);

  /* Animation time */
  loc = glGetUniformLocation(Shader->Program, "Time");
  if (loc != -1)
    glUniform1f(loc, Ani->Time);

  /* Setup illumination coefficients */
  loc = glGetUniformLocation(Shader->Program, "CameraPos");
  if (loc != -1)
    glUniform3fv(loc, 1, &Ani->Camera.Loc.X);

  /* Setup general uniforms */
  for (auto &i : UnifFloat)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifInt)
    Shader->SetUniform(i.first.c_str(), i.second);
  for (auto &i : UnifMatr)
    Shader->SetUniform(i.first.c_str(), i.second);

  for (INT i = 0; i < Textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, Textures[i]->GetNo());
    loc = glGetUniformLocation(Shader->Program, Textures[i]->Name);
    if (loc != -1)
      glUniform1i(loc, i);
  }
} /* End of 'tcg::material::Apply' function */

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::material_manager::material_manager( VOID )
{
} /* End of 'tcg::material_manager::material_manager' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::material_manager::~material_manager( VOID )
{
  for (INT i = 0; i < Materials.size(); i++)
    delete Materials[i];
} /* End of 'tcg::material_manager::~material_manager' function */

/* Add material function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 *   - shader name:
 *       CHAR *ShaderName;
 *   - ambient, diffuse and specular coefficients:
 *       const color &Ka, &Kd, &Ks;
 *   - shininess:
 *       FLT Shininess;
 * RETURNS:
 *   (material *) pointer to added material.
 */
tcg::material * tcg::material_manager::AddMaterial( CHAR *Name, CHAR *ShaderName, const color &Ka, const color &Kd, const color &Ks, FLT Shininess )
{
  for (INT i = 0; i < Materials.size(); i++)
    if (!strcmp(Name, Materials[i]->Name))
      return Materials[i];

  Materials.push_back(new material(Name, GetShader(ShaderName), Ka, Kd, Ks, Shininess));
  return Materials.back();
} /* End of 'tcg::material_manager::AddMaterial' function */

/* Get material function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 * RETURNS:
 *   (material *) pointer to material.
 */
tcg::material * tcg::material_manager::GetMaterial( CHAR *Name )
{
  for (INT i = 0; i < Materials.size(); i++)
    if (!strcmp(Name, Materials[i]->Name))
      return Materials[i];
  return NULL;
} /* End of 'tcg::material_manager::GetMaterial' function */

/* Float uniform add function.
 * ARGUMENTS:
 *   - uniform name:
 *       const char *Name;
 *   - uniform value:
 *       float Val.
 * RETURNS: None.
 */
VOID tcg::material::SetUniform( const char *Name, float Val )
{
  UnifFloat[std::string(Name)] = Val;
} /* End of 'tcg::material::SetUniform function */

/* Integer uniform add function.
 * ARGUMENTS:
 *   - uniform name:
 *       const char *Name;
 *   - uniform value:
 *       int Val.
 * RETURNS: None.
 */
VOID tcg::material::SetUniform( const char *Name, int Val )
{
  UnifInt[std::string(Name)] = Val;
} /* End of 'tcg::material::SetUniform function */

/* Matrix uniform add function.
 * ARGUMENTS:
 *   - uniform name:
 *       const char *Name;
 *   - uniform value:
 *       const matr &Val.
 * RETURNS: None.
 */
VOID tcg::material::SetUniform( const char *Name, const matr &Val )
{
  UnifMatr[std::string(Name)] = Val;
} /* End of 'tcg::material::SetUniform function */

/* END OF 'material.cpp' FILE */
