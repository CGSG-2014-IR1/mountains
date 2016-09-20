/***************************************************************
 * Copyright (C) 2011
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGVECT.H
 * PURPOSE     : Tough Space Graphics library.
 *               Main declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006-2011.
 *               Andrew Churinov,
 *               Artemy Sergeev (assembly trigonometry inline).
 * LAST UPDATE : 08.12.2012 (from 05.04.2011, 13.08.2006, 17.04.2006)
 * NOTE        : Templates namespace 'tsg'.
 *               Based on
 *                 Tatyana Marchukova (vector & matrices) &
 *                 Valeriya Nikolaenko (camera) code.
 *                 (last updates 25.03.2005 & 20.05.2005) 
 *               Based on TSGRAPH project from 'C' library.
 *                 (last updates 2004/2003/1999, original 1998)
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TSGVECT_H_
#define _TSGVECT_H_

#include <math.h>

#include "tsgdef.h"

namespace tsg
{
  /* Vector type basic template class */
  template <class TYPE> class TVec
  { 
  public:
    TYPE X, Y, Z; /* Coordinates of vector */

    /* Default constructor.
     * ARGUMENTS: None.
     */
    TVec( VOID )
    {
    } /* End of 'TVec' constructor */

    /* Constructor by equal components.
     * ARGUMENTS:
     *   - value of all components:
     *       TYPE Value;
     */
    explicit TVec( TYPE Value ): X(Value), Y(Value), Z(Value)
    {
    } /* End of 'TVec' constructor */

    /* Constructor by components.
     * ARGUMENTS:
     *   - values of components:
     *       TYPE A, B, C;
     */
    TVec( TYPE A, TYPE B, TYPE C ): X(A), Y(B), Z(C)
    {
    } /* End of 'TVec' constructor */

    /* Evaluation vector length function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) vector length.
     */
    TYPE operator!( VOID ) const
    {
      TYPE len = X * X + Y * Y + Z * Z;

      if (len > 0)
      {
        if (len != 1)
        {
          len = sqrt(len);
          return len;
        }
        return len;
      }
      return len;
    } /* End of 'operator!' function */

    /* Evaluation vector length 2D function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) vector length.
     */
    TYPE Length2D( VOID ) const
    {
      TYPE len = X * X + Z * Z;

      if (len > 0)
      {
        if (len != 1)
        {
          len = sqrt(len);
          return len;
        }
        return len;
      }
      return len;
    } /* End of 'Length2D' function */
   
    /* Evaluation vector squared length function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) vector length.
     */
    TYPE GetSquaredLength( VOID ) const
    {
      return X * X + Y * Y + Z * Z;
    } /* End of 'GetSquaredLength' function */

    /* Dot product of two vectors function.
     * ARGUMENTS:
     *   - vector to multiply by:
     *       const TVec &V;
     * RETURNS: 
     *   (TYPE) result of dot product.
     */
    TYPE operator&( const TVec &V ) const
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* End of 'operator&' function */

    /* Cross product of two vectors function. 
     * ARGUMENTS:
     *   - vector to multiply by:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec) result cross product of .
     */
    TVec operator%( const TVec &V ) const
    {
      return TVec(Y * V.Z - V.Y * Z, V.X * Z - X * V.Z, X * V.Y - V.X * Y);
    } /* End of 'operator%' function */

    /* Comparing of two vectors function. 
     * ARGUMENTS:
     *   - vector to compare:
     *       const TVec &V;
     * RETURNS: 
     *   (BOOL) result of comparing.
     */       
    BOOL operator==( const TVec &V ) const
    {
      return 
        Threshold > COM_ABS(X - V.X) &&
        Threshold > COM_ABS(Y - V.Y) &&
        Threshold > COM_ABS(Z - V.Z);
    } /* End of 'operator==' function */

    /* Comparing of two vectors function.
     * ARGUMENTS:
     *   - vector to compare:
     *       const TVec &V;
     * RETURNS: 
     *   (BOOL) result of comparing.
     */
    BOOL operator!=( const TVec &V ) const
    {
      return 
        Threshold < COM_ABS(X - V.X) ||
        Threshold < COM_ABS(Y - V.Y) ||
        Threshold < COM_ABS(Z - V.Z);
    } /* End of 'operator!=' function */

    /* Per components addition of two vectors function.
     * ARGUMENTS:
     *   - vector to add:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec) result of addition.
     */
    TVec operator+( const TVec &V ) const
    {
      return TVec(X + V.X, Y + V.Y, Z + V.Z);
    } /* End of 'operator+' function */

    /* Per components subtraction of two vectors function.
     * ARGUMENTS:
     *   - vector to subtract:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec) result of subtraction.
     */ 
    TVec operator-( const TVec &V ) const
    {
      return TVec(X - V.X, Y - V.Y, Z - V.Z);
    } /* End of 'operator-' function */

    /* Per components multiplication of two vectors function.
     * ARGUMENTS:
     *   - vector to multiply:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec) result of multiplication.
     */
    TVec operator*( const TVec &V ) const
    {
      return TVec(X * V.X, Y * V.Y, Z * V.Z);
    } /* End of 'operator*' function */

    /* Vector division by vector function.
     * ARGUMENTS:
     *   - vector to devise by:
     *       const TVec &V;             
     * RETURNS: 
     *   (TVec) result of devision.
     */
    TVec operator/( const TVec &V ) const
    {
      return TVec(X / V.X, Y / V.Y, Z / V.Z);
    } /* End of 'operator/' function */

    /* Vector multiplication by number function.
     * ARGUMENTS:
     *   - number to multiply by:
     *       TYPE A;             
     * RETURNS: 
     *   (TVec) result of multiplication.
     */
    TVec operator*( TYPE A ) const
    {
      return TVec(A * X, A * Y, A * Z);
    } /* End of 'operator*' function */

    /* Vector division by number function.
     * ARGUMENTS:
     *   - number to devise by:
     *       TYPE A;             
     * RETURNS: 
     *   (TVec) result of devision.
     */
    TVec operator/( TYPE A ) const
    {
      return TVec(X / A, Y / A, Z / A);
    } /* End of 'operator/' function */

    /* Inverse vector function.
     * ARGUMENTS: None.             
     * RETURNS:              
     *   (TVec) result of inverse.
     */
    TVec operator-( VOID ) const
    {
      return TVec(-X, -Y, -Z);
    } /* End of 'operator-' function */

    /* Negate vector (itself) function. 
     * ARGUMENTS: None.             
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & Negate( VOID )
    {
      X = -X;
      Y = -Y;
      Z = -Z;

      return *this;
    } /* End of 'Negate' function */

    /* Per components addition of vector with assignment function.
     * ARGUMENTS:
     *   - vector to add:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator+=( const TVec &V )
    {
      X += V.X;
      Y += V.Y;
      Z += V.Z;

      return *this;
    } /* End of 'operator+=' function */

    /* Per components subtraction of vector with assignment function.
     * ARGUMENTS:
     *   - vector to subtract:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator-=( const TVec &V )
    {
      X -= V.X;
      Y -= V.Y;
      Z -= V.Z;

      return *this;
    } /* End of 'operator-=' function */

    /* Multiplication with assignment by number function.
     * ARGUMENTS:
     *   - number to multiply by:
     *       TYPE A;             
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator*=( TYPE A ) 
    {
      X *= A;
      Y *= A;
      Z *= A;

      return *this;
    } /* End of 'operator*=' function */

    /* Per components multiplication with assignment by vector function.
     * ARGUMENTS:
     *   - vector to multiply by:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator*=( const TVec &V )
    {
      X *= V.X;
      Y *= V.Y;
      Z *= V.Z;

      return *this;
    } /* End of 'operator*=' function */

    /* Multiplication by matrix function.
     * ARGUMENTS:
     *   - matrix to multiply by:
     *       TMatr &Matr;             
     * RETURNS: 
     *   (TVec) Result of multiplying by matrix.
     */
    TVec operator*( const TMatr<TYPE> &Matr ) const
    {
      TVec ret(X * Matr.A[0][0] + Y * Matr.A[1][0] + Z * Matr.A[2][0] + Matr.A[3][0],
               X * Matr.A[0][1] + Y * Matr.A[1][1] + Z * Matr.A[2][1] + Matr.A[3][1],
               X * Matr.A[0][2] + Y * Matr.A[1][2] + Z * Matr.A[2][2] + Matr.A[3][2]);
      TYPE W = X * Matr.A[0][3] + Y * Matr.A[1][3] + Z * Matr.A[2][3] + Matr.A[3][3];
      ret /= W;
      return ret;
    } /* End of 'operator*' function */

    /* Multiplication by matrix with assignment function.
     * ARGUMENTS:
     *   - matrix to multiply by:
     *       TMatr &Matr;             
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator*=( const TMatr<TYPE> &Matr )
    {
      TYPE a, b;

      a = X * Matr.A[0][0] + Y * Matr.A[1][0] + Z * Matr.A[2][0] + Matr.A[3][0];
      b = X * Matr.A[0][1] + Y * Matr.A[1][1] + Z * Matr.A[2][1] + Matr.A[3][1];
      Z = X * Matr.A[0][2] + Y * Matr.A[1][2] + Z * Matr.A[2][2] + Matr.A[3][2];
      X = a;
      Y = b;

      return *this;
    } /* End of 'operator*=' function */

    /* Cross product with assignment function.
     * ARGUMENTS:
     *   - vector to multiply by:
     *       const TVec &V;
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator%=( const TVec &V ) 
    {
      TYPE a, b;

      a = Y * V.Z - V.Y * Z;
      b = V.X * Z - X * V.Z;
      Z = X * V.Y - V.X * Y;
      X = a;
      Y = b;

      return *this;
    } /* End of 'operator%=' function */

    /* Per components division with assignment by number 
     * ARGUMENTS:
     *   - number to devise by:
     *       TYPE A;             
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & operator/=( TYPE A ) 
    {
      X /= A;
      Y /= A;
      Z /= A;

      return *this;
    } /* End of 'operator/=' function */

    /* Get vector coordinate reference by index function
     * ARGUMENTS:
     *   - coordinate index:
     *       INT I;
     * RETURNS:
     *   (TYPE &) vector coordinate refernce.
     */
    TYPE & operator[]( INT I )
    {
      return *(&X + I);
    } /* End of 'operator[]' function */

    /* Normalize vector function. 
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TVec &) self-reference to vector.
     */
    TVec & Normalize( VOID )
    {
      TYPE len = X * X + Y * Y + Z * Z;

      if (len > 0)
      {
        if (len != 1)
        {
          len = sqrt(len);
          X /= len;
          Y /= len;
          Z /= len;
          return *this;
        }
        return *this;
      }
      return *this;
    } /* End of 'Normalize' function */

    /* Normalize vector function. 
     * ARGUMENTS: None.
     * RETURNS:
     *   (TVec) normalized vector.
     */
    TVec Normalizing( VOID ) const
    {
      TYPE len = X * X + Y * Y + Z * Z;
      
      if (len > 0)
      {
        if (len != 1)
        {
          len = sqrt(len);
          return TVec(X / len, Y / len, Z / len);
        }
        return *this;
      }
      return *this;
    } /* End of 'Normalizing' function */

    /* Clamp vector function
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TVec &) self-reference to vector.
     */
    TVec & Clamp( TYPE Min = 0, TYPE Max = 1 )
    {
      if (X < Min)
        X = Min;
      else
        if (X > Max)
          X = Max;
      if (Y < Min)
        Y = Min;
      else
        if (Y > Max)
          Y = Max;
      if (Z < Min)
        Z = Min;
      else
        if (Z > Max)
          Z = Max;
      return *this;
    } /* End of 'Clamp' function */

    /* Clamp vector function
     *   - minimal vector value:
     *       TYPE Min;
     *   - maximum vector value:
     *       TYPE Max;
     * RETURNS:
     *   (TVec) clamped vector.
     */
    TVec Clamping( TYPE Min = 0, TYPE Max = 1 ) const
    {
      return TVec(X < Min ? Min : X > Max ? Max : X,
                  Y < Min ? Min : Y > Max ? Max : Y,
                  Z < Min ? Min : Z > Max ? Max : Z);
    } /* End of 'Clamping' function */

    /*** Vector transformation functions ***/

    /***
     * Apply specified transformation to vector (self-transform) functions
     ***/

    /* Translate vector function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Translate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      X += Dx;
      Y += Dy;
      Z += Dz;

      return *this;
    } /* End of 'Translate' function */

    /* Translate vector function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Translate( const TVec<TYPE> &Shift )
    {
      return Translate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translate' function */

    /* Rotate around 'X' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE T;

      T = Y * AngleCosine - Z * AngleSine;
      Z = Y * AngleSine + Z * AngleCosine;
      Y = T;

      return *this;
    } /* End of 'RotateX' function */

    /* Rotate around 'X' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateX( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotateX(SinVal, CosVal);
    } /* End of 'RotateX' function */

    /* Rotate around 'Y' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE T;

      T = Z * AngleCosine - X * AngleSine;
      X = Z * AngleSine + X * AngleCosine;
      Z = T;

      return *this;
    } /* End of 'RotateY' function */

    /* Rotate around 'Y' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateY( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotateY(SinVal, CosVal);
    } /* End of 'RotateY' function */

    /* Rotate around 'Z' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE T;

      T = X * AngleCosine - Y * AngleSine;
      Y = X * AngleSine + Y * AngleCosine;
      X = T;

      return *this;
    } /* End of 'RotateZ' function */

    /* Rotate around 'Z' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & RotateZ( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotateZ(SinVal, CosVal);
    } /* End of 'RotateZ' function */

    /* Rotate around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Rotate( TYPE AngleSine, TYPE AngleCosine,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return Rotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Rotate( TYPE AngleInDegree,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      TYPE a, b, Rm[3][3];

      BuildRotateMatrix3x3<TYPE, 3>(Rm, AngleInDegree, AxisX, AxisY, AxisZ);

      a = X * Rm[0][0] + Y * Rm[1][0] + Z * Rm[2][0];
      b = X * Rm[0][1] + Y * Rm[1][1] + Z * Rm[2][1];
      Z = X * Rm[0][2] + Y * Rm[1][2] + Z * Rm[2][2];
      X = a;
      Y = b;

      return *this;
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Rotate( TYPE AngleSine, TYPE AngleCosine,
                   const TVec<TYPE> &Vec )
    {
      return Rotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Rotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return Rotate(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Scale along axes vector function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Scale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      X *= Sx;
      Y *= Sy;
      Z *= Sz;

      return *this;
    } /* End of 'Scale' function */

    /* Scale along axes vector function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Scale( const TVec<TYPE> &ScaleVec )
    {
      return Scale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scale' function */

    /* Transform vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & Transform( const TTrans<TYPE> &Trans )
    {
      TYPE a, b;

      a = X * Trans.M.A[0][0] + Y * Trans.M.A[1][0] + 
        Z * Trans.M.A[2][0] + Trans.M.A[3][0];
      b = X * Trans.M.A[0][1] + Y * Trans.M.A[1][1] + 
        Z * Trans.M.A[2][1] + Trans.M.A[3][1];
      Z = X * Trans.M.A[0][2] + Y * Trans.M.A[1][2] + 
        Z * Trans.M.A[2][2] + Trans.M.A[3][2];
      X = a;
      Y = b;
 
      return *this;
    } /* End of 'Transform' function */

    /* Inverse transform vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TVec &) self-pointer to vector.
     */
    TVec & InvTransform( const TTrans<TYPE> &Trans )
    {
      TYPE a, b;

      a = X * Trans.InvM.A[0][0] + Y * Trans.InvM.A[1][0] + 
        Z * Trans.InvM.A[2][0] + Trans.InvM.A[3][0];
      b = X * Trans.InvM.A[0][1] + Y * Trans.InvM.A[1][1] + 
        Z * Trans.InvM.A[2][1] + Trans.InvM.A[3][1];
      Z = X * Trans.InvM.A[0][2] + Y * Trans.InvM.A[1][2] + 
        Z * Trans.InvM.A[2][2] + Trans.InvM.A[3][2];
      X = a;
      Y = b;

      return *this;
    } /* End of 'InvTransform' function */

    /***
     * Apply specified transformation to vector functions
     ***/

    /* Translation vector function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Translation( TYPE Dx, TYPE Dy, TYPE Dz ) const
    {
      return TVec(X + Dx, Y + Dy, Z + Dz);
    } /* End of 'Translation' function */

    /* Translation vector function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Translation( const TVec<TYPE> &Shift ) const
    {
      return Translation(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translation' function */

    /* Rotation around 'X' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationX( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TVec(X,
                  Y * AngleCosine - Z * AngleSine,
                  Y * AngleSine + Z * AngleCosine);
    } /* End of 'RotationX' function */

    /* Rotation around 'X' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationX( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotationX(SinVal, CosVal);
    } /* End of 'RotationX' function */

    /* Rotation around 'Y' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationY( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TVec(Z * AngleSine + X * AngleCosine,
                  Y,
                  Z * AngleCosine - X * AngleSine);
    } /* End of 'RotationY' function */

    /* Rotation around 'Y' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationY( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotationY(SinVal, CosVal);
    } /* End of 'RotationY' function */

    /* Rotation around 'Z' axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationZ( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TVec(X * AngleCosine - Y * AngleSine,
                  X * AngleSine + Y * AngleCosine,
                  Z);
    } /* End of 'RotationZ' function */

    /* Rotation around 'Z' axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec RotationZ( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  AngleInRadians      

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */

      return RotationZ(SinVal, CosVal);
    } /* End of 'RotationZ' function */

    /* Rotation around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */              
    TVec Rotation( TYPE AngleSine, TYPE AngleCosine,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      return Rotation(Rad2Deg(atan2(AngleSine, AngleCosine)), X, Y, Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Rotation( TYPE AngleInDegree,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      TYPE Rm[3][3];

      BuildRotateMatrix3x3<TYPE, 3>(Rm, AngleInDegree, AxisX, AxisY, AxisZ);

      return TVec(X * Rm[0][0] + Y * Rm[1][0] + Z * Rm[2][0],
                  X * Rm[0][1] + Y * Rm[1][1] + Z * Rm[2][1],
                  X * Rm[0][2] + Y * Rm[1][2] + Z * Rm[2][2]);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Rotation( TYPE AngleSine, TYPE AngleCosine,
                   const TVec<TYPE> &Vec ) const
    {
      return Rotation(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis vector function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Rotation( TYPE AngleInDegree, const TVec<TYPE> &Vec ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal, CosVal;

//#ifdef __TSG_ASM__    
//    _asm {
//      /* FST(0) Angle (from degree to radian) */
//      fld  AngleInRadians      
//
//      /* FST(0) - cos, FST(1) - sin */
//      fsincos
//
//      fstp CosVal    /* cos -> CosVal */
//      fstp SinVal    /* sin -> SinVal */
//    }
//#else /* __TSG_ASM__ */
    SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
//#endif /* __TSG_ASM__ */

      return Rotation(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Scaling along axes vector function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Scaling( TYPE Sx, TYPE Sy, TYPE Sz ) const
    {
      return TVec(X * Sx, Y * Sy, Z * Sz);
    } /* End of 'Scaling' function */

    /* Scaling along axes vector function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Scaling( const TVec<TYPE> &ScaleVec ) const
    {
      return Scaling(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scaling' function */

    /* Transformation vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec Transformation( const TTrans<TYPE> &Trans ) const
    {
      return TVec(X * Trans.M.A[0][0] + Y * Trans.M.A[1][0] +
                    Z * Trans.M.A[2][0] + Trans.M.A[3][0],
                  X * Trans.M.A[0][1] + Y * Trans.M.A[1][1] + 
                    Z * Trans.M.A[2][1] + Trans.M.A[3][1],
                  X * Trans.M.A[0][2] + Y * Trans.M.A[1][2] + 
                    Z * Trans.M.A[2][2] + Trans.M.A[3][2]);
    } /* End of 'Transformation' function */

    /* Inverse transformation vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TVec) new vector (transformed) object.
     */
    TVec InvTransformation( const TTrans<TYPE> &Trans ) const
    {
      return TVec(X * Trans.InvM.A[0][0] + Y * Trans.InvM.A[1][0] + 
                    Z * Trans.InvM.A[2][0] + Trans.InvM.A[3][0],
                  X * Trans.InvM.A[0][1] + Y * Trans.InvM.A[1][1] + 
                    Z * Trans.InvM.A[2][1] + Trans.InvM.A[3][1],
                  X * Trans.InvM.A[0][2] + Y * Trans.InvM.A[1][2] + 
                    Z * Trans.InvM.A[2][2] + Trans.InvM.A[3][2]);
    } /* End of 'InvTransformation' function */

    /* Type cast function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TVec<FLOAT>) type cast result.
     */
    operator TVec<FLOAT>( VOID ) const
    {
      return TVec<FLOAT>(X, Y, Z);
    } /* End of 'operator TVec<FLOAT>' function */

    /* Type cast function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TVec<DOUBLE>) type cast result.
     */
    operator TVec<DOUBLE>( VOID ) const
    {
      return TVec<DOUBLE>(X, Y, Z);
    } /* End of 'operator TVec<DOUBLE>' function */
  }; /* End of 'TVec' class */
} /* End of 'tsg' namespace */

#endif /* _TSGVECT_H_ */
