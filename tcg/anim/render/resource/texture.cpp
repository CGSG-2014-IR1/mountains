/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : texture.cpp
 * PURPOSE     : Computational geometry project.
 *               Texture support module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 15.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstring>

#include "../../animation.h"

#include "texture.h"

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::texture_manager::texture_manager( VOID )
{
} /* End of 'tcg::texture_manager::texture_manager' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::texture_manager::~texture_manager( VOID )
{
  for (INT i = 0; i < Textures.size(); i++)
    delete Textures[i];
} /* End of 'tcg::texture_manager::~texture_manager' function */

/* Add texture function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 * RETURNS:
 *   (texture *) pointer to added texture.
 */
tcg::texture * tcg::texture_manager::AddTexture( CHAR *Name, CHAR *FileName )
{
  for (INT i = 0; i < Textures.size(); i++)
    if (!strcmp(Name,Textures[i]->Name))
      return Textures[i];

  Textures.push_back(new texture(Name, FileName));
  return Textures.back();
} /* End of 'tcg::texture_manager::AddTexture' function */

/* Add texture function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture dimensions:
 *       INT W, H;
 *   - texture pixels:
 *       FLOAT *Data.
 * RETURNS:
 *   (texture *) pointer to added texture.
 */
tcg::texture * tcg::texture_manager::AddTexture( CHAR *Name, INT W, INT H, FLOAT *Data )
{
  for (INT i = 0; i < Textures.size(); i++)
    if (!strcmp(Name,Textures[i]->Name))
    {
      Textures[i]->Update(W, H, Data);
      return Textures[i];
    }

  Textures.push_back(new texture(Name, W, H, Data));
  return Textures.back();
} /* End of 'tcg::texture_manager::AddTexture' function */

/* Get texture function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 * RETURNS:
 *   (texture *) pointer to texture.
 */
tcg::texture * tcg::texture_manager::GetTexture( CHAR *Name )
{
  for (INT i = 0; i < Textures.size(); i++)
    if (!strcmp(Name, Textures[i]->Name))
      return Textures[i];
  return NULL;
} /* End of 'tcg::texture_manager::GetTexture' function */

/* END OF 'texture.cpp' FILE */
