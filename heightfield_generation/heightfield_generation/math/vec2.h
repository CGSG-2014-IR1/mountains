/* Reshetnyak Ivan */

#ifndef __vec2_h_
#define __vec2_h_

#include <cmath>

/* 2D vector class template */
template <class type>
  class vec2D
  {
  public:
    type X, Y;  /* Vector coordinates */

    /* Class constructor.
     * ARGUMENTS:
     *   - coordinates:
     *       type X = 0, Y = 0;
     */
    vec2D( type X = 0, type Y = 0 ) : X(X), Y(Y)
    {
    } /* End of 'vec2D' constructor */

    /* Vector addition.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D) addition result - new vector.
     */
    vec2D operator+( const vec2D &rhs ) const
    {
      return vec2D(X + rhs.X, Y + rhs.Y);
    } /* End of 'operator+' function */

    /* Vector subtraction.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D) subtraction result - new vector.
     */
    vec2D operator-( const vec2D &rhs ) const
    {
      return vec2D(X - rhs.X, Y - rhs.Y);
    } /* End of 'operator-' function */

    /* Vector multiplication.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D) multiplication result - new vector.
     */
    vec2D operator*( const vec2D &rhs ) const
    {
      return vec2D(X * rhs.X, Y * rhs.Y);
    } /* End of 'operator*' function */

    /* Vector division.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D) division result - new vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec2D operator/( const vec2D &rhs ) const
    {
      if (rhs.X == 0 || rhs.Y == 0)
        throw "Vector division failed - cannot divide on 0!";

      return vec2D(X / rhs.X, Y / rhs.Y);
    } /* End of 'operator/' function */

    /* Vector addition.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D &) addition result - this vector.
     */
    vec2D & operator+=( const vec2D &rhs )
    {
      X += rhs.X;
      Y += rhs.Y;
      return *this;
    } /* End of 'operator+=' function */

    /* Vector subtraction.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D &) subtraction result - this vector.
     */
    vec2D & operator-=( const vec2D &rhs )
    {
      X -= rhs.X;
      Y -= rhs.Y;
      return *this;
    } /* End of 'operator-=' function */

    /* Vector multiplication.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D &) multiplication result - this vector.
     */
    vec2D & operator*=( const vec2D &rhs )
    {
      X *= rhs.X;
      Y *= rhs.Y;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector division.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (vec2D &) division result - this vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec2D operator/=( const vec2D &rhs )
    {
      if (rhs.X == 0 || rhs.Y == 0)
        throw "Vector division failed - cannot divide on 0!";

      X /= rhs.X;
      Y /= rhs.Y;

      return *this;
    } /* End of 'operator/=' function */

    /* Vector on scalar multiplication.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec2D) multiplication result - new vector.
     */
    vec2D operator*( type rhs ) const
    {
      return vec2D(X * rhs, Y * rhs);
    } /* End of 'operator*' function */

    /* Vector on scalar division.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec2D) division result - new vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec2D operator/( type rhs ) const
    {
      if (rhs == 0)
        throw "Vector division failed - cannot divide on 0!";
      return vec2D(X / rhs, Y / rhs);
    } /* End of 'operator/' function */

    /* Vector on scalar multiplication.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec2D &) multiplication result - this vector.
     */
    vec2D & operator*=( type rhs )
    {
      X *= rhs;
      Y *= rhs;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector on scalar division.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec2D &) division result - this vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec2D operator/=( type rhs ) const
    {
      if (rhs == 0)
        throw "Vector division failed - cannot divide on 0!";
      X /= rhs;
      Y /= rhs;
      return *this;
    } /* End of 'operator/=' function */

    /* Vector dot production.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (type) dot product result.
     */
    type operator&( const vec2D &rhs ) const
    {
      return X * rhs.X + Y * rhs.Y;
    } /* End of 'operator&' function */

    /* Vector cross production.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (double) cross product Z.
     */
    double operator%( const vec2D &rhs ) const
    {
      return X * rhs.Y - rhs.X * Y;
    } /* End of 'operator%' function */

    /* Vector equation.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (bool) if vectors are equal.
     */
    bool operator==( const vec2D &rhs ) const
    {
#ifdef APPROXIMATE_EQUATION
      return fabs(X - rhs.X) + fabs(Y - rhs.Y) > 0.00001;
#else /* APPROXIMATE_EQUATION */
      return X == rhs.X && Y == rhs.Y;
#endif /* APPROXIMATE_EQUATION */
    } /* End of 'operator==' function */

    /* Vector non equation.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec2D &rhs;
     * RETURNS:
     *   (bool) if vectors not are equal.
     */
    bool operator!=( const vec2D &rhs ) const
    {
      return X != rhs.X || Y != rhs.Y;
    } /* End of 'operator!=' function */

    double operator!( void ) const
    {
      return sqrt(X * X + Y * Y);
    }

    static double Distance( const vec2D &v1, const vec2D &v2 )
    {
      return !(v1 - v2);
    }

    vec2D Normalized( void ) const
    {
      double l = !(*this);
      if (l == 0)
        throw "ERROR";
      return (*this) / (type)l;
    }

    vec2D operator-( void ) const
    {
      return (*this) * -1;
    }

    static bool NearEqual( const vec2D &lhs, const vec2D &rhs )
    {
      return fabs(lhs.X - rhs.X) + fabs(lhs.Y - rhs.Y) < math::Threshold;
    }
  }; /* End of 'vec2D' class */

#endif /* __vec2_h_ */

/* END OF 'vec2.h' FILE */
