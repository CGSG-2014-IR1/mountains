/* Reshetnyak Ivan */

#ifndef __anim_h_
#define __anim_h_

#include <cstdlib>

#include "../def.h"
#include "unit.h"
#include "timer.h"
#include "camera.h"

#define GLEW_STATIC
#pragma comment(lib, "glew32s")
#include <glew.h>
#include <glut.h>

#include <vector>

/* Animation structure class */
class anim
{
public:
  enum class coordinate_system
  {
    WORLD, SCREEN
  };

  static anim Anim;           /* Structure singletone */
  int WinW, WinH;             /* Window sizes */
  coordinate_system CS;
  camera Camera;
  timer Timer;
  bool Keys[256];

private:
  bool IsWireframe;
  std::vector<unit *> Units;  /* Unit stock */

  /* Keyboard callback function.
   * ARGUMENTS:
   *   - pressed key code:
   *       unsigned char Key;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  static void Keyboard( unsigned char Key, int X, int Y );

  /* Keyboard callback function.
   * ARGUMENTS:
   *   - pressed key code:
   *       unsigned char Key;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  static void KeyboardUp( unsigned char Key, int X, int Y );

  /* Display callback function.
   * ARGUMENTS: None. 
   * RETURNS: None.
   */
  static void Display( void );

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
  static void Mouse( int Button, int State, int X, int Y );

  /* Window resize callback.
   * ARGUMENTS:
   *   - new window sizes:
   *       int W, H;
   * RETURNS: None.
   */
  static void Resize( int W, int H );

public:
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
  void Init( int argc, char *argv[], char *WindowName = "" );

  /* Unit add fuction.
   * ARGUMENTS:
   *   - new unit pointer:
   *       unit *Unit;
   * RETURNS:
   *   (anim &) self-reference.
   */
  anim & operator<<( unit *Unit );

private:
  static const int DEFAULT_WINDOW_WIDTH = 1366;
  static const int DEFAULT_WINDOW_HEIGHT = 768;

  /* Class constructor.
   * ARGUMENTS: None.
   */
  anim( void );

  /* Class destructor.
   */
  ~anim( void )
  {
    for (auto &i : Units)
      delete i;
  } /* End of '~anim' destructor */

public:
  void Run( void )
  {
    glutMainLoop();
  }
}; /* End of 'anim' class */

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */
