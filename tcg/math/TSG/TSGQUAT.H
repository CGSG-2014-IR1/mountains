/***************************************************************
 * Copyright (C) 2014
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGQUAT.H
 * PURPOSE     : Tough Space Graphics library.
 *               Quaternion support declaration module.
 * PROGRAMMER  : CGSG'2012-2014.
 *               Dmitry Rozplohas
 *               Poletaev Vsevolod.
 * LAST UPDATE : 28.04.2014
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

#ifndef _TSGQUAT_H_
#define _TSGQUAT_H_

#include "tsgdef.h"

namespace tsg
{
  /* Quaternion type basic template class */
  template<class TYPE> class TQuat
  {
  public:
    TVec<TYPE> V; /* Vector (imaginary) part */
    TYPE       S; /* Scalar (real) part */

    /* Default constructor.
     * ARGUMENTS: None.
     */
    TQuat( VOID )
    {
    } /* End of 'TQuat' constructor */

    /* Constructor by parts.
     * ARGUMENTS:
     *   - vector part:
     *       const TVec<TYPE> &NewV;
     *   - scalar part:
     *       TYPE NewS;
     */
    TQuat( const TVec<TYPE> &NewV, TYPE NewS ) : V(NewV), S(NewS)
    {
    } /* End of 'TQuat' constructor */

    /* Constructor by rotation axis and angle.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation axis:
     *       const TVec<TYPE> &Axis;
     */
    TQuat( TYPE AngleInDegree, const TVec<TYPE> &Axis )
    {
      DOUBLE HalfAngleInRadians = Deg2Rad(AngleInDegree / 2);
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  HalfAngleInRadians

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp CosVal    /* cos -> CosVal */
      fstp SinVal    /* sin -> SinVal */
    }
#else /* __TSG_ASM__ */
    SinVal = sin(HalfAngleInRadians), CosVal = cos(HalfAngleInRadians);
#endif /* __TSG_ASM__ */

      S = CosVal;
      V = Axis.Normalizing() * SinVal;
    } /* End of 'TQuat' constructor */

    /* Evaluation quaternion square function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TYPE) quaternion square.
     */
    TYPE GetSquare( VOID ) const
    {
      return S * S + V.GetSquaredLength();
    } /* End of 'GetSquare' function */

    /* Comparing of two quaternions function.
     * ARGUMENTS:
     *   - quaternion to compare:
     *       const TQuat &Q;
     * RETURNS:
     *   (BOOL) result of comparing.
     */
    BOOL operator==( const TQuat &Q ) const
    {
      return
        Threshold > COM_ABS(S - Q.S) &&
        Threshold > COM_ABS(!(V - Q.V));
    } /* End of 'operator==' function */

    /* Comparing of two vectors function.
     * ARGUMENTS:
     *   - vector to compare:
     *       const TQuat &V;
     * RETURNS:
     *   (BOOL) result of comparing.
     */
    BOOL operator!=( const TQuat &Q ) const
    {
      return
        Threshold < COM_ABS(S - Q.S) ||
        Threshold < COM_ABS(!(V - Q.V));
    }/* End of 'operator!=' function */

    /* Per components addition of two quaternions function.
     * ARGUMENTS:
     *   - quaternion to add:
     *       const TQuat &Q;
     * RETURNS: 
     *   (TQuat) result of addition.
     */
    TQuat operator+( const TQuat &Q ) const
    {
      return TQuat(V + Q.V, S + Q.S);
    } /* End of 'operator+' function */

    /* Per components subtraction of two quaternions function.
     * ARGUMENTS:
     *   - quaternion to subtract:
     *       const TQuat &Q;
     * RETURNS:
     *   (TQuat) result of subtraction.
     */
    TQuat operator-( const TQuat &Q ) const
    {
      return TQuat(V - Q.V, S - Q.S);
    } /* End of 'operator-' function */

    /* Quaternion multiplication by number function.
     * ARGUMENTS:
     *   - number to multiply by:
     *       TYPE A;
     * RETURNS:
     *   (TQuat) result of multiplication.
     */
    TQuat operator*( TYPE A ) const
    {
      return TQuat(V * A, S * A);
    } /* End of 'operator*' function */

    /* Multiplication of two quaternions function.
     * ARGUMENTS:
     *   - quaternion to multiply:
     *       const TQuat &Q;
     * RETURNS: 
     *   (TQuat) result of multiplication.
     */
    TQuat operator*( const TQuat &Q ) const
    {
      return TQuat(V * Q.S + Q.V * S + (V % Q.V), S * Q.S - (V & Q.V));
    } /* End of 'operator*' function */

    /* Per components addition of quaternion with assignment function.
     * ARGUMENTS:
     *   - quaternion to add:
     *       const TQuat &Q;
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & operator+=( const TQuat &Q )
    {
      S += Q.S;
      V += Q.V;

      return *this;
    } /* End of 'operator+=' function */

    /* Per components subtraction of quaternion with assignment function.
     * ARGUMENTS:
     *   - quaternion to subtract:
     *       const TQuat &Q;
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & operator-=( const TQuat &Q )
    {
      S -= Q.S;
      V -= Q.V;

      return *this;
    } /* End of 'operator-=' function */

    /* Multiplication with assignment by number function.
     * ARGUMENTS:
     *   - number to multiply by:
     *       TYPE A;
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & operator*=( TYPE A )
    {
      S *= A;
      V *= A;

      return *this;
    } /* End of 'operator*=' function */

    /* Multiplication of quaternion with assignment function.
     * ARGUMENTS:
     *   - quaternion to multiply:
     *       const TQuat &Q;
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & operator*=( const TQuat &Q )
    {
      TYPE Tmp = S;
      S = S * Q.S - (V & Q.V);
      V = V * Q.S + Q.V * Tmp + (V % Q.V);

      return *this;
    } /* End of 'operator*=' function */

    /* Normalize quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & Normalize( VOID )
    {
      TYPE Len = sqrt(GetSquare());
      if (Len != 0)
        V /= Len, S /= Len;
      return *this;
    } /* End of 'Normalize' function */

    /* Normalize quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat) Normalize quaternion.
     */
    TQuat Normalizing( VOID ) const
    {
      TYPE Len = sqrt(V.GetSquare() + S * S);
      if (Len == 0)
        Len = 1;
      return TQuat(V / Len , S / Len);
    } /* End of 'Normalizing' function */

    /* Conjugate quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & Conjugate( VOID )
    {
      V = -V;

      return *this;
    } /* End of 'Conjugate' function */

    /* Conjugate quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat) conjugate quaternion.
     */
    TQuat Conjugating( VOID ) const
    {
      return TQuat(-V, S);
    } /* End of 'Conjugating' function */

    /* Inverse quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat &) self-reference to quaternion.
     */
    TQuat & Inverse( VOID )
    {
      return this->Conjugating() * (1 / this->GetSquare());
    } /* End of 'Inverse' function */

    /* Inverse quaternion function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TQuat) inverse quaternion.
     */
    TQuat Inversing( VOID ) const
    {
      return TQuat(-V * (1 / this->GetSquare()),
                   S * (1 / this->GetSquare()));
    } /* End of 'Inversing' function */

    /* Reset transformation quaternion data function.
     * ARGUMENTS: None.
     * RETURN:
     *   (TQuat &) self-pointer to quaternion.
     */
    TQuat & SetUnit( VOID )
    {
      S = 1;
      V = TVec<TYPE>(0);

      return *this;
    } /* End of 'SetUnit' function */

    /* Transform quaternion to matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TMatr<TYPE>) quaternion in matrix form.
     */
    TMatr<TYPE> ToMatr( VOID ) const
    {
      return TMatr<TYPE>(1 - 2 * V.Y * V.Y - 2 * V.Z * V.Z, 2 * V.X * V.Y - 2 * S * V.Z,       2 * V.X * V.Z + 2 * S * V.Y,
                         2 * V.X * V.Y + 2 * S * V.Z,       1 - 2 * V.X * V.X - 2 * V.Z * V.Z, 2 * V.Y * V.Z - 2 * S * V.X,
                         2 * V.X * V.Z - 2 * S * V.Y,       2 * V.Y * V.Z + 2 * S * V.X,       1 - 2 * V.X * V.X - 2 * V.Y * V.Y);
    } /* End of 'ToMatr' function */

    /* Vector rotate with quaternion function.
     * ARGUMENTS:
     *   - vector to be rotate:
     *       const TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) new (rotated) vector.
     */
    TVec<TYPE> RotateVector( TVec<TYPE> &Vec ) const
    {
      return Vec = (Inversing() * TQuat(Vec, 0) * (*this)).V;
    } /* End of 'RotateVector' function */

    /* Sperical linear interpolation.
     * ARGUMENTS:
     *   - interpolating quaternions:
     *       const TQuat &Q1, &Q2;
     *   - interpolation coefficient:
     *       TYPE t;
     * RETURNS:
     *   (TQuat) interpolating quaternion.
     */
    static TQuat SLerp( const TQuat &Q1, const TQuat &Q2, TYPE t )
    {
      TYPE Phi = acos(COM_ABS(Q1.S * Q2.S + (Q1.V & Q2.V))),
        SinPhi = sqrt(1 - COM_ABS(Q1.S * Q2.S + (Q1.V & Q2.V)) * COM_ABS(Q1.S * Q2.S + (Q1.V & Q2.V))),
        SinPhiT = sin(Phi * t), SinPhi1T = sin(Phi * (1 - t));

      return Q1 * (SinPhi1T / SinPhi) + Q2 * (SinPhiT / SinPhi);
    } /* End of 'SLerp' function */
  }; /* End of 'TQuat' class */
} /* End of 'tsg' namespace */

#endif /* _TSGQUAT_H_ */
