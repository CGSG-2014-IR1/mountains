/* Reshetnyak Ivan */

#include "../def.h"

/* Camera representation class */
class camera
{
public:
  vec
    Loc,                    /* Camera position */
    At,                     /* Camera view point */
    Dir,                    /* Camera view direction */
    Up,                     /* Up direction */
    Right;                  /* Right direction */

  matrix
    View,                   /* Camera view matrix */
    Projection,             /* Camera projection matrix */
    VP;                     /* Camera view-projection matrix */

  float
    Near, Far, Top,
    Bottom, LeftP, RightP;  /* Frustum planes */

  /* Camera constructor.
   * ARGUMENTS:
   *   - projection planes:
   *       float Near, Far, Bottom, Top, LeftP, RightP;
   *   - camera location:
   *       const vec &Loc = vec(0, 1, -1);
   *   - camera view point:
   *       const vec &At = vec(0, 0, 0);
   *   - camera up vector (approx.):
   *       const vec &Up0;
   */
  camera( float Near, float Far, float Bottom,
          float Top, float LeftP, float RightP,
          const vec &Loc = vec(0, 1, -1), const vec &At = vec(0, 0, 0),
          const vec &Up0 = vec(0, 1, 0) ) :
    Loc(Loc), At(At), Near(Near), Far(Far), LeftP(LeftP), RightP(RightP), Up(Up0), Bottom(Bottom), Top(Top)
  {
    Dir = (Loc - At).Normalized();
    Right = (Dir % Up).Normalized();
    Up = (Right % Dir).Normalized();

    View = matrix::View(Loc, Dir, Up, Right);
    Projection = matrix::Projection(LeftP, RightP, Top, Bottom, Near, Far);
    VP = View * Projection;
  } /* End of 'camera' constructor */

  /* Camera matrixes update.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void Update( void )
  {
    View = matrix::View(Loc, Dir, Up, Right);
    Projection = matrix::Projection(LeftP, RightP, Top, Bottom, Near, Far);
    VP = View * Projection;
  } /* End of 'Update' function */

  /* Projection parameters set function.
   * ARGUMENTS:
   *   - projection parameters:
   *       float Near, Far, Bottom, Top, LeftP, RightP;
   * RETURNS: None.
   */
  void Set( float Near, float Far, float Bottom,
            float Top, float LeftP, float RightP )
  {
    this->Near = Near;
    this->Far = Far;
    this->Bottom = Bottom;
    this->Top = Top;
    this->LeftP = LeftP;
    this->RightP = RightP;
    Update();
  } /* End of 'Set' function */

  /* Projection parameters set function.
   * ARGUMENTS:
   *   - projection parameters:
   *       float Near, Far, Bottom, Top, LeftP, RightP;
   * RETURNS: None.
   */
  void Set( const vec &Loc, const vec &At, const vec &Up )
  {
    this->Loc = Loc;
    this->At = At;
    this->Up = Up;
    Dir = (Loc - At).Normalized();
    Right = (Dir % Up).Normalized();
    this->Up = (Right % Dir).Normalized();

    Update();
  } /* End of 'Set' function */

  /* Camera move function.
   * ARGUMENTS:
   *   - shift vector:
   *       const vec &Shift.
   * RETURNS: None.
   */
  void Move( const vec &Shift )
  {
    Loc += Shift;
    At += Shift;

    Dir = (Loc - At).Normalized();
    Right = (Dir % Up).Normalized();
    Up = (Right % Dir).Normalized();

    Update();
  } /* End of 'Move' function */

  void RotateY( double Angle )
  {
    matrix m = matrix::MatrRotateY(Angle);

    At = (m * (At - Loc)) + Loc;

    Dir = (Loc - At).Normalized();
    Right = (Dir % Up).Normalized();
    Up = (Right % Dir).Normalized();

    Update();
  }

  void Rotate( vec Axis, double Angle )
  {
    matrix m = matrix::MatrRotate(Axis, Angle);

    At = (m * (At - Loc)) + Loc;

    Dir = (Loc - At).Normalized();
    Right = (Dir % Up).Normalized();
    Up = (Right % Dir).Normalized();

    Update();
  }
}; /* End of 'camera' class */

/* END OF 'camera.h' FILE */
