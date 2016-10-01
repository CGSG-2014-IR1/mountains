/* Reshetnyak Ivan */

#ifndef __matrix_h_
#define __matrix_h_

#include "math.h"

template<class type>
  /* 4x4 matrix class template
   * ARGUMENTS:
   *   - stored data type:
   *       class type;
   */
  class matrix4
  {
  private:
    type Data[4][4];  /* Stored matrix data */
  public:
    /* Array filling class constructor
     * ARGUMENTS:
     *   - data array:
     *       type *Matrix;
     */
    matrix4( type *NewData )
    {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        Data[i][j] = NewData[i * 4 + j];
    } /* End of 'matrix4' constructor */

    /* Filling class constructor
     * ARGUMENTS:
     *   - fill data:
     *       type &a0 = 1, &a1 = 0, &a2 = 0, &a3 = 0,
     *            &b0 = 0, &b1 = 1, &b2 = 0, &b3 = 0,
     *            &c0 = 0, &c1 = 0, &c2 = 1, &c3 = 0,
     *            &d0 = 0, &d1 = 0, &d2 = 0, &d3 = 1;
     */
    matrix4( type a0 = 1, type a1 = 0, type a2 = 0, type a3 = 0,
            type b0 = 0, type b1 = 1, type b2 = 0, type b3 = 0,
            type c0 = 0, type c1 = 0, type c2 = 1, type c3 = 0,
            type d0 = 0, type d1 = 0, type d2 = 0, type d3 = 1 )
    {
      Data[0][0] = a0;
      Data[0][1] = a1;
      Data[0][2] = a2;
      Data[0][3] = a3;

      Data[1][0] = b0;
      Data[1][1] = b1;
      Data[1][2] = b2;
      Data[1][3] = b3;

      Data[2][0] = c0;
      Data[2][1] = c1;
      Data[2][2] = c2;
      Data[2][3] = c3;

      Data[3][0] = d0;
      Data[3][1] = d1;
      Data[3][2] = d2;
      Data[3][3] = d3;
    } /* End of 'matrix4' constructor */

    /* Matrix class destructor */
    ~matrix4( void )
    {
    } /* End of '~matrix4' destructor */

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURNS:
     *   (matrix4) translate matrix.
     */
    matrix4 MatrTranslate( type Dx, type Dy, type Dz )
    {
      matrix4 res(MatrIdentity);
      res[3][0] = Dx;
      res[3][1] = Dy;
      res[3][2] = Dz;
      res[3][3] = 1;
      return res;
    } /* End of 'MatrTranslate' function */

    /* Set rotation around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle in degrees:
     *       double Angle;
     * RETURNS:
     *   (matrix4) translate matrix.
     */
    static matrix4 MatrRotateX( double Angle )
    {
      Angle = DegreesToRadians(Angle);
      matrix4 res = MatrIdentity;
      type sine = sin(Angle), cosine = cos(Angle);
      res[1][1] = cosine;
      res[1][2] = sine;
      res[2][1] = -sine;
      res[2][2] = cosine;
      return res;
    } /* End of 'SetRotateX' function */

    /* Set rotation around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle in degrees:
     *       double Angle;
     * RETURNS:
     *   (matrix4) translate matrix.
     */
    static matrix4 MatrRotateY( double Angle )
    {
      Angle = math::DegreesToRadians(Angle);
      matrix4 res;
      type sine = (type)sin(Angle), cosine = (type)cos(Angle);
      res[0][0] = (type)cosine;
      res[0][2] = (type)sine;
      res[2][0] = (type)-sine;
      res[2][2] = (type)cosine;
      return res;
    } /* End of 'SetRotateY' function */

    /* Set rotation around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle in degrees:
     *       double Angle;
     * RETURNS:
     *   (matrix4) translate matrix.
     */
    static matrix4 MatrRotateZ( double Angle )
    {
      Angle = DegreesToRadians(Angle);
      matrix4 res = MatrIdentity;
      type sine = sin(Angle), cosine = cos(Angle);
      res[0][0] = cosine;
      res[0][1] = sine;
      res[1][0] = -sine;
      res[1][1] = cosine;
      return res;
    } /* End of 'SetRotateZ' function */

    static matrix4 MatrRotate( vec Axis, double Angle )
    {
      Angle = math::DegreesToRadians(Angle);
      matrix4 res;
      double sine = sin(Angle), cosine = cos(Angle);

      res[0][0] = (type)(cosine + Axis.X * Axis.X * (1 - cosine));
      res[0][1] = (type)(Axis.X * Axis.Y * (1 - cosine) - Axis.Z * sine);
      res[0][2] = (type)(Axis.Z * Axis.X * (1 - cosine) + Axis.Y * sine);

      res[1][0] = (type)(Axis.Y * Axis.X * (1 - cosine) + Axis.Z * sine);
      res[1][1] = (type)(cosine + Axis.Y * Axis.Y * (1 - cosine));
      res[1][2] = (type)(Axis.Z * Axis.Y * (1 - cosine) - Axis.X * sine);

      res[2][0] = (type)(Axis.Z * Axis.X * (1 - cosine) - Axis.Y * sine);
      res[2][1] = (type)(Axis.Z * Axis.Y * (1 - cosine) + Axis.X * sine);
      res[2][2] = (type)(cosine + Axis.Z * Axis.Z * (1 - cosine));
      return res;
    }

    /* Matrix data access operator override
     * ARGUMENTS:
     *   - access index:
     *       int index;
     * RETURNS:
     *   (type *) matrix data row.
     */
    type * operator[]( int index )
    {
      return Data[index];
    } // End of 'operator[]' function

    /* Matrix data access operator override
     * ARGUMENTS:
     *   - access index:
     *       int index;
     * RETURNS:
     *   (type *) matrix data row.
     */
    const type * operator[]( int index ) const
    {
      return Data[index];
    } // End of 'operator[]' function

    /* Matrix data copy operator override
     * ARGUMENTS:
     *   - right matrix:
     *       matrix4 &RightM;
     * RETURNS:
     *   (matrix4 &) matrix self pointer.
     */
    matrix4 & operator=( const matrix4 &RightM )
    {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          Data[i][j] = RightM[i][j];
      return *this;
    } // End of 'operator=' function

    /* Matrix sum operator override
     * ARGUMENTS:
     *   - right matrix:
     *       matrix4 &RightM;
     * RETURNS:
     *   (matrix4) result matrix.
     */
    matrix4 operator+( matrix4 &RightM ) const
    {
      matrix4 res = *this;
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          res[i][j] += RightM[i][j];
      return res;
    } // End of 'operator+' function

    /* Matrix sum operator override
     * ARGUMENTS:
     *   - right matrix:
     *       matrix4 &RightM;
     * RETURNS:
     *   (matrix4 &) matrix self pointer.
     */
    matrix4 & operator+=( matrix4 &RightM )
    {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          Data[i][j] += RightM[i][j];
      return *this;
    } // End of 'operator+=' function

    /* Matrix subtraction operator override
     * ARGUMENTS:
     *   - right matrix:
     *       matrix4 &RightM;
     * RETURNS:
     *   (matrix4) result matrix.
     */
    matrix4 operator-( matrix4 &RightM ) const
    {
      matrix4 res = *this;
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          res[i][j] -= RightM[i][j];
      return res;
    } // End of 'operator-' function

    /* Matrix subtraction operator override
     * ARGUMENTS:
     *   - right matrix:
     *       matrix4 &RightM;
     * RETURNS:
     *   (matrix4 &) matrix self pointer.
     */
    matrix4 & operator-=( matrix4 &RightM )
    {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          Data[i][j] += RightM[i][j];
      return *this;
    } // End of 'operator-=' function

    /* Matrix multiplication operator override
     * ARGUMENTS:
     *   - matrix multiplicator:
     *       type &Multiplicator;
     * RETURNS:
     *   (matrix4) result matrix.
     */
    matrix4 operator*( type &Multiplicator ) const
    {
      matrix4 res = *this;
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          res[i][j] *= Multiplicator;
      return res;
    } // End of 'operator*' function

    /* Matrix multiplication operator override
     * ARGUMENTS:
     *   - matrix multiplicator:
     *       type &Multiplicator;
     * RETURNS:
     *   (matrix4 &) matrix self pointer.
     */
    matrix4 operator*=( type &Multiplicator )
    {
      *this = *this * Multiplicator;
      return *this;
    } // End of 'operator*=' function

    /* Matrix division operator override
     * ARGUMENTS:
     *   - matrix divisor:
     *       type &Divisor;
     * RETURNS:
     *   (matrix4) result matrix.
     */
    matrix4 operator/( type &Divisor ) const
    {
      assert(Divisor != (type)0);  // Checking [2]ero-division
      matrix4 res = *this;
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          res[i][j] /= Divisor;
      return res;
    } // End of 'operator/' function

    /* Matrix division operator override
     * ARGUMENTS:
     *   - matrix divisor:
     *       type &Divisor;
     * RETURNS:
     *   (matrix4 &) matrix self pointer.
     */
    matrix4 operator/=( type &Divisor )
    {
      *this = *this / Divisor;
      return *this;
    } // End of 'operator/=' function

    /* Two matrixes multiplication operator override
     * ARGUMENTS:
     *   - right matrix:
     *        matrix4 &RightM;
     * RETURNS:
     *   (matrix4) result matrix.
     */
    matrix4 operator*( matrix4 &RightM ) const
    {
      matrix4 res(0, 0, 0, 0,
                  0, 0, 0, 0,
                  0, 0, 0, 0,
                  0, 0, 0, 0);
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          for (int k = 0; k < 4; k++)
            res[i][j] += Data[i][k] * RightM[k][j];
      return res;
    } // End of 'operator*' function

    /* Two matrixes multiplication operator override
     * ARGUMENTS:
     *   - right matrix:
     *        matrix4 &RightM;
     * RETURNS:
     *   (matrix4 &) matrix self link.
     */
    matrix4 operator*=( matrix4 &RightM )
    {
      *this = *this * RightM;
      return *this;
    } // End of 'operator*=' function

    /* Matrix transpon function
     * ARGUMENTS: None.
     * RETURNS:
     *   (matrix4 &) matrix self link.
     */
    matrix4 & Transpone( void )
    {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          if (j > i)
            Swap(Data[i][j], Data[j][i]);
      return *this;
    } // End of 'Transpone' function

    /* Matrix transpon operator override
     * ARGUMENTS: None.
     * RETURNS:
     *   (matrix4 &) matrix self link.
     */
    matrix4 & operator!( void )
    {
      return Transpone();
    } // End of 'operator!' function

    /* Matrix determinator count function
     * ARGUMENTS: None.
     * RETURNS:
     *   (type) matrix determinator.
     */
    type Determinator( void )
    {
      type det = type(0);
      det += Data[0][0] * Data[1][1] * Data[2][2] * Data[3][3] * ( 1) +
             Data[0][0] * Data[1][1] * Data[2][3] * Data[3][2] * (-1) +

             Data[0][0] * Data[1][2] * Data[2][3] * Data[3][1] * ( 1) +
             Data[0][0] * Data[1][2] * Data[2][1] * Data[3][3] * (-1) +

             Data[0][0] * Data[1][3] * Data[2][1] * Data[3][2] * ( 1) +
             Data[0][0] * Data[1][3] * Data[2][2] * Data[3][1] * (-1) +

             //////////////////////////////////////////
             Data[0][1] * Data[1][0] * Data[2][2] * Data[3][3] * (-1) +
             Data[0][1] * Data[1][0] * Data[2][3] * Data[3][2] * ( 1) +

             Data[0][1] * Data[1][2] * Data[2][3] * Data[3][0] * (-1) +
             Data[0][1] * Data[1][2] * Data[2][0] * Data[3][3] * ( 1) +

             Data[0][1] * Data[1][3] * Data[2][0] * Data[3][2] * (-1) +
             Data[0][1] * Data[1][3] * Data[2][2] * Data[3][0] * ( 1) +

             //////////////////////////////////////////
             Data[0][2] * Data[1][0] * Data[2][1] * Data[3][3] * ( 1) +
             Data[0][2] * Data[1][0] * Data[2][3] * Data[3][1] * (-1) +

             Data[0][2] * Data[1][1] * Data[2][3] * Data[3][0] * ( 1) +
             Data[0][2] * Data[1][1] * Data[2][0] * Data[3][3] * (-1) +

             Data[0][2] * Data[1][3] * Data[2][0] * Data[3][1] * ( 1) +
             Data[0][2] * Data[1][3] * Data[2][0] * Data[3][1] * (-1) +

             //////////////////////////////////////////
             Data[0][3] * Data[1][0] * Data[2][1] * Data[3][2] * (-1) +
             Data[0][3] * Data[1][0] * Data[2][2] * Data[3][1] * ( 1) +

             Data[0][3] * Data[1][1] * Data[2][2] * Data[3][0] * (-1) +
             Data[0][3] * Data[1][1] * Data[2][0] * Data[3][2] * (-1) +

             Data[0][3] * Data[1][2] * Data[2][0] * Data[3][1] * (-1) +
             Data[0][3] * Data[1][2] * Data[2][1] * Data[3][0] * ( 1);
      return det;
    } /* End of 'Determinator' function */

    /* Algebraic joint count function
     * ARGUMENTS:
     *   - element indexes:
     *       int x, y;
     * RETURNS:
     *   (type) element algebraic joint.
     */
    matrix4 Joint( int x, int y )
    {
      matrix4 m = *this;
      for (int i = 0; i < 4; i++)
        m[i][x] = 0;
      for (int i = 0; i < 4; i++)
        m[y][i] = 1;
      m[y][x] = 1;
      return m.Determinator();
    } /* End of 'Joint' function */

    /* Inverse matrix count function
     * ARGUMENTS: None.
     * RETURNS:
     *   (matrix4) inversed matrix.
     */
    matrix4 Inverse( void )
    {
      matrix4 adjoint(Joint(0, 0), Joint(1, 0), Joint(2, 0), Joint(3, 0),
                      Joint(0, 1), Joint(1, 1), Joint(2, 1), Joint(3, 1),
                      Joint(0, 2), Joint(1, 2), Joint(2, 2), Joint(3, 2),
                      Joint(0, 3), Joint(1, 3), Joint(2, 3), Joint(3, 3));  // adjoint matrix
      adjoint *= (1.0) / Determinator();
      return adjoint;
    } /* End of 'Inverse' function */

    /* View matrix create function.
     * ARGUMENTS:
     *   - camera location:
     *       const vec &Loc;
     *   - camera direction:
     *       const vec &Dir;
     *   - camera up vector:
     *       const vec &Up;
     *   - camera right vector:
     *       const vec &Right;
     * RETURNS:
     *   (matrix4) view matrix.
     */
    static matrix4 View( const vec &Loc, const vec &Dir, const vec &Up, const vec &Right )
    {
      /*
      return matrix4(Right.X, Right.Y, Right.Z, -(Loc & Right),
                        Up.X,    Up.Y,    Up.Z,    -(Loc & Up),
                       Dir.X,   Dir.Y,   Dir.Z,     -Loc & Dir,
                           0,       0,       0,              1);*/

      return matrix4(Right.X,      Up.X,      Dir.X, 0,
                     Right.Y,      Up.Y,      Dir.Y, 0,
                     Right.Z,      Up.Z,      Dir.Z, 0,
                -Loc & Right, -Loc & Up, -Loc & Dir, 1);
    } /* End of 'view' function */

    static matrix4 Projection( type Left, type Right, type Top, type Bottom, type Near, type Far )
    {
      type
        Width = Right - Left,
        Height = Top - Bottom,
        Depth = Far - Near;

      return
        matrix4(2.0f * Near / Width,                    0.0f,                         0.0f,  0.0f,
                               0.0f,    2.0f * Near / Height,                         0.0f,  0.0f,
             (Right + Left) / Width, (Top + Bottom) / Height, -(Far + Near) / (Far - Near), -1.0f,
                               0.0f,                    0.0f,   2.0f * Far * Near / -Depth,  0.0f).Transpone();
    }

    vec3D<type> operator*( const vec3D<type> &rhs )
    {
        return vec3D<type>(
          (rhs.X * Data[0][0] + rhs.Y * Data[1][0] + rhs.Z * Data[2][0] + Data[3][0]),
          (rhs.X * Data[0][1] + rhs.Y * Data[1][1] + rhs.Z * Data[2][1] + Data[3][1]),
          (rhs.X * Data[0][2] + rhs.Y * Data[1][2] + rhs.Z * Data[2][2] + Data[3][2]));
    }
  }; /* End of 'matrix4' class template */

#endif /* __matrix_h_ */

/* END OF 'matrix.h' file */
