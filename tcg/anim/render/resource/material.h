/***************************************************************
 * Copyright (C) 2016
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : material.h
 * PURPOSE     : Computational geometry project.
 *               Material support declaration module.
 * PROGRAMMER  : MM5.
 * LAST UPDATE : 13.07.2016.
 * NOTE        : Namespace 'tcg'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __material_h_
#define __material_h_

#include "../../../def.h"

#include <vector>

#include "../render.h"

#include "shader.h"
#include "texture.h"

/* Computational geometry project namespace */
namespace tcg
{
  /* Material class */
  class material
  {
    friend class material_manager;
  private:
    CHAR Name[MAX_STR];
    color Ka, Kd, Ks;
    FLT Shininess;
    shader *Shader;
    std::vector<texture *> Textures;
  public:
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
    material( CHAR *Name, shader *Shader,
              const color &Ka = color(0.6, 0.6, 0.6, 1.0),
              const color &Kd = color(0.9, 0.9, 0.9, 1.0),
              const color &Ks = color(1.0, 1.0, 1.0, 1.0),
              FLT Shininess = 1 );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~material( VOID );

    /* Add texture function.
     * ARGUMENTS:
     *   - texture:
     *       texture *Texture;
     * RETURNS: None.
     */
    VOID AddTexture( texture *Texture );

    /* Apply material function.
     * ARGUMENTS:
     *   - animation:
     *       anim *Ani;
     */
    VOID Apply( anim *Ani );
  }; /* End of 'material' class */

  /* Material manager class */
  class material_manager : public shader_manager, public texture_manager
  {
  private:
    std::vector<material *> Materials;

  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    material_manager( VOID );

    /* Class destructor.
     * ARGUMENTS: None.
     */
    ~material_manager( VOID );

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
    material * AddMaterial( CHAR *Name, CHAR *ShaderName, 
                    const color &Ka = color(0.6, 0.6, 0.6, 1.0),
                    const color &Kd = color(0.9, 0.9, 0.9, 1.0),
                    const color &Ks = color(1.0, 1.0, 1.0, 1.0),
                    FLT Shininess = 1 );

    /* Get material function.
     * ARGUMENTS:
     *   - material name:
     *       CHAR *Name;
     * RETURNS:
     *   (material *) pointer to material.
     */
    material * GetMaterial( CHAR *Name );
  }; /* End of 'material_manager' class */
} /* end of 'tcg' namespace */

#endif /* __materrial_h_ */

/* END OF 'material.h' FILE */
