/* Reshetnyak Ivan */

#ifndef __material_h_
#define __material_h_

#include "../../../def.h"
#include "../../anim.h"
#include "texture.h"
#include "shader.h"

#include <vector>
#include <map>
#include <string>

/* Primitive material representation class */
class material
{
private:
  //static material DefaultMaterial;               /* Default material  */
  char *Name;                                      /* Material name     */
  std::map<std::string, float> MapFloat;
  std::map<std::string, matrix> MapMatrix;
  std::map<std::string, int> MapInt;

public:
  color
    Ka,                                            /* Ambient  Phong coefficient */
    Kd,                                            /* Diffuse  Phong coefficient */
    Ks;                                            /* Specular Phong coefficient */
  int ID;                                          /* Material library id        */
  int Shader;                                      /* Material shader            */
  std::vector<texture> Textures;                   /* Material textures */
  static std::vector<material> MaterialLibrary;    /* Materials library */

  material & AddUniform( const std::string &Name, int Val )
  {
    MapInt.insert(std::pair<std::string, int>(Name, Val));
    return *this;
  }

  material & AddUniform( const std::string &Name, float Val )
  {
    MapFloat.insert(std::pair<std::string, float>(Name, Val));
    return *this;
  }

  material & AddUniform( const std::string &Name, const matrix &Val )
  {
    MapMatrix.insert(std::pair<std::string, matrix>(Name, Val));
    return *this;
  }

  material & SetUniform( const std::string &Name, float Val )
  {
    MapFloat[Name] = Val;
    return *this;
  }

  /* Class constructor
   * ARGUMENTS:
   *   - material name:
   *       CHAR *MaterialName;
   */
  material( CHAR *MaterialName,
            color nKa = color(),
            color nKd = color(),
            color nKs = color(),
            CHAR *Tex0 = NULL, CHAR *Tex1 = NULL,
            CHAR *Tex2 = NULL, CHAR *Tex3 = NULL ) : Name(MaterialName),
                                                     Ka(nKa), Kd(nKd), Ks(nKs)
  {
    CHAR Buf[250];
    sprintf(Buf, "bin/shader/%s/", MaterialName);
    Shader = shader::Create(Buf);
    ID = MaterialLibrary.size();
    MaterialLibrary.push_back(*this);
  } /* End of 'material' constructor */

  /* Material apply function.
   * ARGUMENTS:
   *   - override shader id:
   *       INT ShaderOv;
   */
  VOID Apply( INT ShaderOv = -1 )
  {
    shader *Sh;                              // work shader link
    if (ShaderOv == -1)
      Sh = shader::Get(Shader);
    else
      Sh = shader::Get(ShaderOv);

    Sh->Apply();                                                            // apply shader

    /* Transformations */
    Sh->SetUniform("View", (float *)(anim::Anim.Camera.View[0]));           // set view matrix
    Sh->SetUniform("Proj", (float *)(anim::Anim.Camera.Projection[0]));     // set projection matrix
    Sh->SetUniform("VP", (float *)(anim::Anim.Camera.VP[0]));               // set view-projection matrix

    /* Phong */
    Sh->SetUniform("Ka", (float)Ka.R, (float)Ka.G, (float)Ka.B);            // set ambient  coeciffient
    Sh->SetUniform("Kd", (float)Kd.R, (float)Kd.G, (float)Kd.B);            // set diffuse  coeciffient
    Sh->SetUniform("Ks", (float)Ks.R, (float)Ks.G, (float)Ks.B);            // set specular coeciffient

    Sh->SetUniform("CameraDir", (float)-anim::Anim.Camera.Dir.X, (float)-anim::Anim.Camera.Dir.Y, (float)-anim::Anim.Camera.Dir.Z);
    Sh->SetUniform("CameraUp", (float)anim::Anim.Camera.Up.X, (float)anim::Anim.Camera.Up.Y, (float)anim::Anim.Camera.Up.Z);
    Sh->SetUniform("CameraRight", (float)anim::Anim.Camera.Right.X, (float)anim::Anim.Camera.Right.Y, (float)anim::Anim.Camera.Right.Z);
    Sh->SetUniform("CameraPos", (float)anim::Anim.Camera.Loc.X, (float)anim::Anim.Camera.Loc.Y, (float)anim::Anim.Camera.Loc.Z);
    Sh->SetUniform("CameraRatio", (float)(anim::Anim.WinW / anim::Anim.WinH));

    for (auto &i : MapInt)
      Sh->SetUniform(i.first.c_str(), i.second);
    for (auto &i : MapFloat)
      Sh->SetUniform(i.first.c_str(), i.second);
    for (auto &i : MapMatrix)
      Sh->SetUniform(i.first.c_str(), i.second[0]);

    /* Textures */
    for (int i = 0, size = Textures.size(); i < size; i++)
    {
      char Buf[12];
      Textures[i].Apply();
      sprintf(Buf, "Texture%d", i);
      Sh->SetUniform(Buf, i);
    }

    /* Time */
    Sh->SetUniform("Time", (FLOAT)anim::Anim.Timer.Time);                       // set animation time
  } /* End of 'Apply' function */

  /* Material programs disable function.
   * ARGUMENTS:
   *   - material library id:
   *       INT MaterialID
   * RETURNS:
   *   (shader *) shader pointer.
   */
  static material * GetMaterial( INT MaterialID )
  {
    return &MaterialLibrary[MaterialID];
  }

  /* Class destructor
   * ARGUMENTS: None.
   */
  ~material( VOID )
  {
  } /* End of '~material' destructor */
}; /* End of 'material' class */

#endif /* __material_h_ */

/* END OF 'material.h' FILE */
