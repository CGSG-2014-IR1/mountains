/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : shader.h
 * PURPOSE     : Computational geometry project.
 *               Shader support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __shader_h_
#define __shader_h_

#include "../../../def.h"

#include <vector>

/* Computational geometry project namespace */
namespace tcg
{
  /* Shader class */
  class shader
  {
    friend class shader_manager;
    friend class material;
  private:
    INT Program;
    CHAR Name[MAX_STR];
    
    /* Class constructor.
     * ARGUMENTS: None.
     */
    shader( VOID );

    /* Class constructor.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       CHAR *Name;
     */
    shader( CHAR *FileNamePrefix );

    /* Load shader function.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       CHAR *FileNamePrefix;
     */
    VOID Load( CHAR *FileNamePrefix );

    /* Save text in the log file function.
     * ARGUMENTS:
     *    - text:
     *        CHAR *Text;
     * RETURNS: None.
     */
    static VOID SaveLog( CHAR *Text );

    /* Load text function.
     * ARGUMENTS:
     *   - file name:
     *       CHAR *FileName;
     * RETURNS:
     *   (CHAR *) text.
     */
    static CHAR * LoadText( CHAR *FileName );

  public:
    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~shader( VOID );

    /* Enable shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Enable( VOID );

    /* Disable shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Disable( VOID );
  }; /* End of 'shader' class */

  /* Shader manager class */
  class shader_manager
  {
  private:
    std::vector<shader *> Shaders;
  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    shader_manager( VOID );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~shader_manager( VOID );

    /* Get shader function.
     * ARGUMENTS:
     *   - shader name:
     *       CHAR *Name;
     * RETURNS:
     *   (shader *) pointer to shader.
     */
    shader * GetShader( CHAR *Name );
  }; /* End of 'shader_manager' class */
} /* end of 'tcg' namespace */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */
