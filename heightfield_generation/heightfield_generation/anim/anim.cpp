/* Reshetnyak Ivan */

#include "anim.h"

anim anim::Anim;  /* Animation singletone */

#include "render/resource/shader.h"

std::vector<shader> shader::ShaderLibrary;
int shader::LastAppliedShader = -1;

#include "render/resource/material.h"

std::vector<material> material::MaterialLibrary;  /* Materials library */
//material material::DefaultMaterial("def");

/* Keyboard callback function.
 * ARGUMENTS:
 *   - pressed key code:
 *       unsigned char Key;
 *   - mouse coordinates:
 *       int X, Y;
 * RETURNS: None.
 */
void anim::Keyboard( unsigned char Key, int X, int Y )
{
  for (auto &i : Anim.Units)
    i->Keyboard(Anim, Key, X, Y);
  Anim.Keys[Key] = true;
  switch (Key)
  {
  case 27:
    exit(0);
  case 'W':
    if (Anim.IsWireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Anim.IsWireframe = !Anim.IsWireframe;
    break;
  };
} /* End of 'anim::Keyboard' function */

/* Keyboard callback function.
 * ARGUMENTS:
 *   - pressed key code:
 *       unsigned char Key;
 *   - mouse coordinates:
 *       int X, Y;
 * RETURNS: None.
 */
void anim::KeyboardUp( unsigned char Key, int X, int Y )
{
  Anim.Keys[Key] = false;
}

/* Display callback function.
 * ARGUMENTS: None. 
 * RETURNS: None.
 */
void anim::Display( void )
{
  Anim.Timer.Update();
  glClearColor(0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  printf("%2.5lf\r", Anim.Timer.FPS);

  for (auto &i : Anim.Units)
    i->Response(Anim);

  for (auto &i : Anim.Units)
    i->Render(Anim);

  glutSwapBuffers();
  glutPostRedisplay();
  glFinish();
} /* End of 'anim::Display' function */

/* Mouse callback function.
 * ARGUMENTS:
 *   - pressed button:
 *       int Button;
 *   - button state:
 *       int State;
 *   - mouse coordinates:
 *       int X, Y;
 * RETURNS: None.
 */
void anim::Mouse( int Button, int State, int X, int Y )
{
  for (auto &i : Anim.Units)
    i->Mouse(Anim, Button, State, X, Y);
} /* End of 'anim::Mouse' function */

/* Window resize callback.
 * ARGUMENTS:
 *   - new window sizes:
 *       int W, H;
 * RETURNS: None.
 */
void anim::Resize( int W, int H )
{
  Anim.WinW = W;
  Anim.WinH = H;
  glViewport(0, 0, W, H);
  float ratio = (float)Anim.WinW / Anim.WinH;
  float scale = 1;
  Anim.Camera.Set(3, 500, -1 / 2.0 * scale, 1 / 2.0 * scale, -ratio / 2.0 * scale, ratio / 2.0 * scale);
} /* End of 'anim::Resize' function */

/* Class constructor.
 * ARGUMENTS: None.
 */
anim::anim( void ) : CS(coordinate_system::WORLD),
  Camera(0.001, 500, -1, 1, -1, 1, vec(0.0, 0.0, 0.0), vec(1.0, 1.0, 1.0), vec(0, 1, 0)),
  IsWireframe(false)
{
  WinW = DEFAULT_WINDOW_WIDTH;
  WinH = DEFAULT_WINDOW_HEIGHT;

  float ratio = (float)WinW / WinH;
  Camera.Set(0.00001, 500, -1, 1, -ratio, ratio);
} /* End of 'anim::anim' constructor */

/* Initialization function.
 * ARGUMENTS:
 *   - number of command line arguments:
 *       int argc;
 *   - command line arguments:
 *       char *argv[];
 *   - window caption:
 *       char *WindowName = "";
 * RETURNS: None.
 */
void anim::Init( int argc, char *argv[], char *WindowName)
{
  glutInit(&argc, argv);

  glutInitWindowSize(WinW, WinH);
  glutCreateWindow(WindowName);

  if (glewInit() != GLEW_OK)
    RuntimeError("Failed to initialize GLEW!");
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    RuntimeError("Failed to initialize GLEW! - shaders are not supported.");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEPTH_CLAMP);

  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  glutReshapeFunc(Resize);
} /* End of 'anim::Init' function */

/* Unit add fuction.
  * ARGUMENTS:
  *   - new unit pointer:
  *       unit *Unit;
  * RETURNS:
  *   (anim &) self-reference.
  */
anim & anim::operator<<( unit *Unit )
{
  Units.push_back(Unit);
  return *this;
} /* End of 'anim::operator<<' function */

/* END OF 'anim.cpp' FILE */
