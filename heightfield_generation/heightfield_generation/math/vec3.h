/* Reshetnyak Ivan */

#ifndef __vec3_h_
#define __vec3_h_

#include <cmath>

/* 3D vector class template */
template <class type>
  class vec3D
  {
  public:
    type X, Y, Z;  /* Vector coordinates */

    /* Class constructor.
     * ARGUMENTS:
     *   - coordinates:
     *       type X = 0, Y = 0, Z = 0;
     */
    explicit vec3D( type X = 0, type Y = 0, type Z = 0 ) : X(X), Y(Y), Z(Z)
    {
    } /* End of 'vec3D' constructor */

    /* Vector addition.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D) addition result - new vector.
     */
    vec3D operator+( const vec3D &rhs ) const
    {
      return vec3D(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
    } /* End of 'operator+' function */

    /* Vector subtraction.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D) subtraction result - new vector.
     */
    vec3D operator-( const vec3D &rhs ) const
    {
      return vec3D(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
    } /* End of 'operator-' function */

    /* Vector multiplication.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D) multiplication result - new vector.
     */
    vec3D operator*( const vec3D &rhs ) const
    {
      return vec3D(X * rhs.X, Y * rhs.Y, Z * rhs.Z);
    } /* End of 'operator*' function */

    /* Vector division.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D) division result - new vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec3D operator/( const vec3D &rhs ) const
    {
      if (rhs.X == 0 || rhs.Y == 0 || rhs.Z == 0)
        throw "Vector division failed - cannot divide on 0!";

      return vec3D(X / rhs.X, Y / rhs.Y, Z / rhs.Z);
    } /* End of 'operator/' function */

    /* Vector addition.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D &) addition result - this vector.
     */
    vec3D & operator+=( const vec3D &rhs )
    {
      X += rhs.X;
      Y += rhs.Y;
      Z += rhs.Z;
      return *this;
    } /* End of 'operator+=' function */

    /* Vector subtraction.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D &) subtraction result - this vector.
     */
    vec3D & operator-=( const vec3D &rhs )
    {
      X -= rhs.X;
      Y -= rhs.Y;
      Z -= rhs.Z;
      return *this;
    } /* End of 'operator-=' function */

    /* Vector multiplication.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D &) multiplication result - this vector.
     */
    vec3D & operator*=( const vec3D &rhs )
    {
      X *= rhs.X;
      Y *= rhs.Y;
      Z *= rhs.Z;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector division.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D &) division result - this vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec3D operator/=( const vec3D &rhs )
    {
      if (rhs.X == 0 || rhs.Y == 0 || rhs.Z == 0)
        throw "Vector division failed - cannot divide on 0!";

      X /= rhs.X;
      Y /= rhs.Y;
      Z /= rhs.Z;

      return *this;
    } /* End of 'operator/=' function */

    template <class m_type>
      /* Vector on scalar multiplication.
       * ARGUMENTS:
       *   - right-hand scalar:
       *       type rhs;
       * RETURNS:
       *   (vec3D) multiplication result - new vector.
       */
      vec3D operator*( m_type rhs ) const
      {
        return vec3D(X * (type)rhs, Y * (type)rhs, Z * (type)rhs);
      } /* End of 'operator*' function */

    /* Vector on scalar division.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec3D) division result - new vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec3D operator/( type rhs ) const
    {
      if (rhs == 0)
        throw "Vector division failed - cannot divide on 0!";
      return vec3D(X / rhs, Y / rhs, Z / rhs);
    } /* End of 'operator/' function */

    /* Vector on scalar multiplication.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec3D &) multiplication result - this vector.
     */
    vec3D & operator*=( type rhs )
    {
      X *= rhs;
      Y *= rhs;
      Z *= rhs;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector on scalar division.
     * ARGUMENTS:
     *   - right-hand scalar:
     *       type rhs;
     * RETURNS:
     *   (vec3D &) division result - this vector.
     * ERRORS:
     *   - "Vector division failed - cannot divide on 0!";
     */
    vec3D & operator/=( type rhs )
    {
      if (rhs == 0)
        throw "Vector division failed - cannot divide on 0!";
      X /= rhs;
      Y /= rhs;
      Z /= rhs;
      return *this;
    } /* End of 'operator/=' function */

    /* Vector dot production.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (type) dot product result.
     */
    type operator&( const vec3D &rhs ) const
    {
      return X * rhs.X + Y * rhs.Y + Z * rhs.Z;
    } /* End of 'operator&' function */

    /* Vector equation.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (bool) if vectors are equal.
     */
    bool operator==( const vec3D &rhs ) const
    {
      return X == rhs.X && Y == rhs.Y && Z == rhs.Z;
    } /* End of 'operator==' function */

    /* Vector non equation.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (bool) if vectors not are equal.
     */
    bool operator!=( const vec3D &rhs ) const
    {
      return X != rhs.X || Y != rhs.Y || Z != rhs.Z;
    } /* End of 'operator!=' function */

    /* Vector length count function:
     * ARGUMENTS: None.
     * RETURNS:
     *   (double) length;
     */
    double operator!( void )
    {
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator!' function */

    /* Normalized vector get function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3D) normalized vector.
     */
    vec3D Normalized( void )
    {
      return vec3D(*this) / (type)!(*this);
    } /* End of 'Normalized' function */

    /* Vector normalization function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3D &) self-reference.
     */
    vec3D & Normalize( void )
    {
      (*this) /= (type)!(*this);
      return *this;
    } /* End of 'Normalize' function */

    /* Cross product function.
     * ARGUMENTS:
     *   - right-hand vector:
     *       const vec3D &rhs;
     * RETURNS:
     *   (vec3D) cross product result.
     */
    vec3D operator%( const vec3D &rhs ) const
    {
      return vec3D(Y * rhs.Z - rhs.Y * Z, rhs.X * Z - X * rhs.Z, X * rhs.Y - rhs.X * Y);
    } /* End of 'operator%' function */

    vec3D operator-( void ) const
    {
      return vec3D(-X, -Y, -Z);
    }
  }; /* End of 'vec3D' class */

#endif /* __vec3_h_ */

/* END OF 'vec3.h' FILE */
