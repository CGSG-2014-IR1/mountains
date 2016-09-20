/* Reshetnyak Ivan */

#ifndef __shader_h_
#define __shader_h_

#include <cstdio>
#include <cstring>

#define GLEW_STATIC
#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#include <glew.h>
#include <glut.h>

#include "../../../def.h"

#include <vector>
#include <string>

/* Shader class */
class shader
{
private:
  static std::vector<shader> ShaderLibrary;                 /* Shaders library        */
  static int LastAppliedShader;                             /* Last applied shader id */
  char Name[200];                                           /* Shader name            */
  unsigned Program;                                         /* Compiled program id    */
  int ID;                                                   /* Shader library id      */
  unsigned Shaders[4];                                      /* Shader ids             */

  /* Shader initialization function.
   * ARGUMENTS:
   *   - shader name:
   *       CHAR *ShaderName;
   * RETURNS: None.
   */
  VOID Init( CHAR *ShaderName )
  {
    strncpy(Name, ShaderName, 199);
    std::string txt;                                          /* Text loaded from file    */
    memset(Shaders, 0, sizeof(UINT) * 4);                     /* Nullify shader ids       */
    unsigned ShTypes[] =
      { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,
        GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER };  /* Shader types             */
    char *Ext[] = {"vert", "frag", "tctrl", "teval"};         /* File extensions          */
    static char Buf[10000];                                   /* String buffer            */
    static char Buf1[1000];                                   /* String buffer            */

    /*** Loading shaders ***/
    int size = sizeof(ShTypes) / sizeof(unsigned);
    for (int i = 0; i < size; i++)
    {
      sprintf(Buf, "%s.%s", Name, Ext[i]);                    /* Creating full file name */

      /* Loading shader code */
      if ((txt = TextLoad(Buf)).length() == 0)
        continue;

      /* Creating shader */
      if ((Shaders[i] = glCreateShader(ShTypes[i])) == 0)
      {
        sprintf(Buf, "Error creating shader %s.%s", Name, Ext[i]);
        Log(Buf);
        RuntimeError(Buf);
      }

      /* Attaching text to shader */
      const char *p = txt.c_str();
      glShaderSource(Shaders[i], 1, &p, nullptr);

      /* Compiling shader */
      int res;                                              /* Shader compilation result code */
      glCompileShader(Shaders[i]);
      glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &res);
      if (res != 1)
      {
        /* Compilation error */
        sprintf(Buf, "Error creating shader %s.%s", Name, Ext[i]);
        Log(Buf);
        glGetShaderInfoLog(Shaders[i], sizeof(Buf), &res, Buf);
        Log(Buf);
        RuntimeError(Buf);
      }
    }

    /* Initializing program */
    if ((Program = glCreateProgram()) == 0)
      /* Error creating program */
      RuntimeError("Error creating shader program!");
    else
    {
      /* Attaching shaders to program */
      for (int i = 0; i < size; i++)
        if (Shaders[i] != 0)
          glAttachShader(Program, Shaders[i]);

      /* Linking program */
      INT res;                                            // program linking result code
      glLinkProgram(Program);
      glGetProgramiv(Program, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        /* Compilation error */
        glGetProgramInfoLog(Program, sizeof(Buf), &res, Buf);
        Log(Buf);
        RuntimeError(Buf);
      }
    }

    ID = ShaderLibrary.size();
    ShaderLibrary.push_back(*this);
  } /* End of 'Init' function */

public:
  /* Unit constructor.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  shader( void )
  {
  } /* End of 'shader' constructor */

  /* Shader text file load function.
   * ARGUMENTS:
   *   - file name:
   *       CHAR *FileName;
   * RETURNS:
   *   (int) created shader ID.
   */
  static int Create( CHAR *FileName )
  {
    shader NewShader;
    NewShader.Init(FileName);
    return NewShader.ID;
  } /* End of 'Create' function */

  /* Unit destructor.
   */
  ~shader( void )
  {
  } /* End of '~shader' destructor */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const float Data;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName, const float Data ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform1f(loc, Data);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const int Data;
   * RETURNS: None.
   */
  VOID SetUniform( const CHAR *UniformName, const int Data ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform1i(loc, Data);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const float Data1, Data2;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName, const float Data1, const float Data2 ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform2f(loc, Data1, Data2);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const int Data1, Data2;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName, const int Data1, const int Data2 ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform2i(loc, Data1, Data2);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const float Data1, Data2, Data3;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const float Data1, const float Data2, const float Data3 ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform3f(loc, Data1, Data2, Data3);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const int Data1, Data2, Data3;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const int Data1, const int Data2, const int Data3 ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform3f(loc, Data1, Data2, Data3);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const float Data1, Data2, Data3;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const float Data1, const float Data2, const float Data3, const float Data4 ) const
  {
    float loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform4f(loc, Data1, Data2, Data3, Data4);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const int Data1, Data2, Data3;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const int Data1, const int Data2, const int Data3, const int Data4 ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform4f(loc, Data1, Data2, Data3, Data4);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - 4x4 matrix to transfer:
   *       const float *Data;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const float *Data ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniformMatrix4fv(loc, 1, FALSE, Data);
  } /* End of 'SetUniform' function */

  /* Shader uniform set function.
   * ARGUMENTS:
   *   - uniform name:
   *       const char *UniformName;
   *   - data to transfer:
   *       const int *Data;
   *   - transfer array size:
   *       const int Count;
   * RETURNS: None.
   */
  VOID SetUniform( const char *UniformName,
                   const int *Data, const int Count ) const
  {
    int loc;  // uniform location
    if ((loc = glGetUniformLocation(Program, UniformName)) > -1)
      glUniform1iv(loc, Count, Data);
  } /* End of 'SetUniform' function */

  /* Shader program apply function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Apply( VOID )
  {
    if (ID != LastAppliedShader)
    {
      glUseProgram(Program);
      LastAppliedShader = ID;
    }
  } /* End of 'Apply' function */

  /* Shader programs disable function.
   * ARGUMENTS:
   *   - shader library id:
   *       int ShaderID
   * RETURNS:
   *   (shader *) shader pointer.
   */
  static shader * Get( int ShaderID )
  {
    if (ShaderID < 0 || (unsigned)ShaderID >= ShaderLibrary.size())
      RuntimeError("Error - shader id out of range!");
    return &ShaderLibrary[ShaderID];
  } /* End of 'Get' function */

  /* Shader programs disable function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  static void Disable( void )
  {
    LastAppliedShader = -1;
    glUseProgram(0);
  } /* End of 'Disable' function */

private:
  /* Text file log function.
   * ARGUMENTS:
   *   - error text:
   *       char *Text;
   * RETURNS: None.
   */
  void Log( char *Text )
  {
    FILE *F;                                            // file variable

    if ((F = fopen("bin/shader/shader.log", "a")) != nullptr)
    {
      fprintf(F, "Error in shader'%s':\n  - %s\n", Name, Text);
      fclose(F);
    }
  } /* End of 'Log' function */

  /* Text file load file.
   * ARGUMENTS:
   *   - file name:
   *       char *FileName;
   * RETURNS:
   *   (char *) loaded text.
   */
  static std::string TextLoad( char *FileName )
  {
    FILE *F;                                            /* File variable */
    std::string mem;

    if ((F = fopen(FileName, "r")) != nullptr)
    {
      long len;        /* file length */

      /* Counting length */
      fseek(F, 0, SEEK_END);
      len = ftell(F);
      fseek(F, 0, SEEK_SET);

      /* Reading file */
      char *txt = new char[len];
      len = fread(txt, 1, len, F);
      mem += txt;
      delete[] txt;
      mem[len] = 0;
      fclose(F);
    }
    return mem;
  } /* End of 'TextLoad' function */
}; /* End of 'shader' class */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */
