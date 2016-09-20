/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : shader.CPP
 * PURPOSE     : Computational geometry project.
 *               Shader support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstdio>
#include <cstring>

#include "shader.h"

#include "render.h"

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::shader::shader( VOID )
{
} /* End of 'tcg::shader::shader' function */

/* Class constructor.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       CHAR *FileNamePrefix;
 */
tcg::shader::shader( CHAR *FileNamePrefix )
{
  CHAR Path[MAX_STR] = "Shaders/";
  Load(strcat(Path, FileNamePrefix));
} /* End of 'tcg::shader::shader' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::shader::~shader( VOID )
{
} /* End of 'tcg::shader::~shader' function */

/* Load shader function.
 * ARGUMENTS:
 *   - shader file name prefix:
 *       CHAR *FileNamePrefix;
 */
VOID tcg::shader::Load( CHAR *FileNamePrefix )
{
  INT res, i;
  CHAR *txt;
  UINT
    Shaders[2] = {0},
    ShTypes[2] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
  CHAR *Suff[2] = {"vert", "frag"};
  BOOL isok = TRUE;
  static CHAR Buf[1000];

  for (i = 0; i < 2; i++)
  {
    sprintf(Buf, "%s.%s", FileNamePrefix, Suff[i]);
    if ((Shaders[i] = glCreateShader(ShTypes[i])) == 0)
    {
      isok = FALSE;
      SaveLog("Error create shader");
      break;
    }
    if ((txt = LoadText(Buf)) == NULL)
    {
      isok = FALSE;
      SaveLog("Error load file");
      SaveLog(Buf);
      break;
    }

    glShaderSource(Shaders[i], 1, &txt, NULL);
    free(txt);
    glCompileShader(Shaders[i]);
    glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(Shaders[i], sizeof(Buf), &res, Buf);
      SaveLog(Buf);
      isok = FALSE;
      break;
    }
  }

  if (isok)
    if ((Program = glCreateProgram()) == 0)
      isok = FALSE;
    else
    {
      for (i = 0; i < 2; i++)
        if (Shaders[i] != 0)
          glAttachShader(Program, Shaders[i]);
      glLinkProgram(Program);
      glGetProgramiv(Program, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(Program, sizeof(Buf), &res, Buf);
        SaveLog(Buf);
        isok = FALSE;
      }
    }
  if (!isok)
  {
    for (i = 0; i < 2; i++)
      if (Shaders[i] != 0)
      {
        if (Program != 0)
          glDetachShader(Program, Shaders[i]);
        glDeleteShader(Shaders[i]);
      }
    if (Program != 0)
      glDeleteProgram(Program);
    Program = 0;
    return;
  }
  strncpy(Name, FileNamePrefix, MAX_STR);
} /* End of 'tcg::shader::Load' function */

/* Save text in the log file function.
 * ARGUMENTS:
 *    - text:
 *        CHAR *Text;
 * RETURNS: None.
 */
VOID tcg::shader::SaveLog( CHAR *Text )
{
  FILE *F;

  if ((F = fopen("{_}SHD{30}.LOG", "a")) != NULL)
  {
    fprintf(F, "%s\n", Text);
    fclose(F);
  }
} /* End of 'tcg::shader::SaveLog' function */

/* Load text function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) text.
 */
CHAR * tcg::shader::LoadText( CHAR *FileName )
{
  FILE *F;
  CHAR *mem = NULL;

  if ((F = fopen(FileName, "r")) != NULL)
  {
    LONG len;

    fseek(F, 0, SEEK_END);
    len = ftell(F);

    if ((mem = (CHAR *)malloc(len + 1)) != NULL)
    {
      fseek(F, 0, SEEK_SET);
      len = fread(mem, 1, len, F);
      mem[len] = 0;
    }
    fclose(F);
  }
  return mem;
} /* End of 'tcg::shader::LoadText' function */

/* Enable shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::shader::Enable( VOID )
{
  glUseProgram(Program);
} /* End of 'tcg::shader::Enable' function */

/* Disable shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tcg::shader::Disable( VOID )
{
  glUseProgram(0);
} /* End of 'tcg::shader::Disable' function */

/* Class constructor.
 * ARGUMENTS: None.
 */
tcg::shader_manager::shader_manager( VOID )
{
} /* End of 'tcg::shader_manager::shader_manager' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tcg::shader_manager::~shader_manager( VOID )
{
  for (INT i = 0; i < Shaders.size(); i++)
    delete Shaders[i];
} /* End of 'tcg::shader_manager::~shader_manager' function */

/* Get shader function.
 * ARGUMENTS:
 *   - shader name:
 *       CHAR *Name;
 * RETURNS:
 *   (shader *) pointer to shader.
 */
tcg::shader * tcg::shader_manager::GetShader( CHAR *Name )
{
  for (INT i = 0; i < Shaders.size(); i++)
    if (!strcmp(Name, Shaders[i]->Name))
      return Shaders[i];

  Shaders.push_back(new shader(Name));
  
  return Shaders.back();
} /* End of 'tcg::shader_manager::GetShader' function */

/* END OF 'shader.cpp' FILE */
