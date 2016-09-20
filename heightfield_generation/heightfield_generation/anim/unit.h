/* Reshetnyak Ivan */

#ifndef __unit_h_
#define __unit_h_

#include "../def.h"

/* Animation unit class */
class unit
{
public:
  /* Class constructor.
   * ARGUMENTS: None.
   */
  unit( void )
  {
  } /* End of 'unit' constructor */

  /* Unit render function.
   * ARGUMENTS:
   *   - animation structure reference.
   *       anim &Ani;
   * RETURNS: None.
   */
  virtual void Render( anim &Ani )
  {
  } /* End of 'Render' function */

  /* Unit response function.
   * ARGUMENTS:
   *   - animation structure reference.
   *       anim &Ani;
   * RETURNS: None.
   */
  virtual void Response( anim &Ani )
  {
  } /* End of 'Response' function */

  /* Unit keyboard callback function.
   * ARGUMENTS:
   *   - animation structure reference.
   *       anim &Ani;
   *   - pressed key code:
   *       unsigned char Key;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  virtual void Keyboard( anim &Ani, unsigned char Key, int X, int Y )
  {
  } /* End of 'Keyboard' function */

  /* Unit mouse callback function.
   * ARGUMENTS:
   *   - animation structure reference.
   *       anim &Ani;
   *   - pressed button:
   *       int Button;
   *   - pressed button state:
   *       int State;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  virtual void Mouse( anim &Ani, int Button, int State, int X, int Y )
  {
  } /* End of 'Mouse' function */

  /* Class destructor
   */
  virtual ~unit()
  {
  } /* End of '~unit' destructor */
}; /* End of 'unit' class */

#endif /* __unit_h_ */
