/***************************************************************
 * Copyright (C) 2011
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGDEF.H
 * PURPOSE     : Tough Space Graphics library.
 *               Main declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006-2011.
 *               Vitaly A. Galinsky,
 *               Artemy Sergeev (assembly trigonometry inline).
 * LAST UPDATE : 05.04.2011 (from 04.12.2007, 18.04.2006)
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

#ifndef _TSGDEF_H_
#define _TSGDEF_H_

#include <math.h>

#include <commondf.h>

/* Define assemble usagemacroname */
#ifndef __TSG_NOASM__
#define __TSG_ASM__
#endif /* __TSG_NOASM__ */

namespace tsg
{
  /* Useful constants */
  const DOUBLE Degree2Radian = 0.01745329251994329576;
  const DOUBLE Radian2Degree = 57.29577951308232087684;
  const DOUBLE Pi = 3.14159265358979323846;
  const DOUBLE E = 2.71828182845904523536;
  const DOUBLE Sqrt2 = 1.41421356237309504880;
  const DOUBLE Threshold = 1e-6;

  /* Forward class references */
  template<class TYPE> class TVec;
  template<class TYPE> class TMatr;
  template<class TYPE> class TTrans;
  template<class TYPE> class TRay;
  template<class TYPE> class TPlane;
  template<class TYPE> class TQuat;
  template<class TYPE, UINT R> class TStock;

  /***
   * Helpful functions
   ***/

  /* Convert degrees to radians function.
   * ARGUMENTS:
   *   - angle values in degrees:
   *       TYPE AngleInDegree;
   * RETURNS:
   *   (TYPE) angle value in radians.
   */
  template<class TYPE> TYPE Deg2Rad( TYPE AngleInDegree )
  {
    return (TYPE)(AngleInDegree * Degree2Radian);
  } /* End of 'Deg2Rad' function */

  /* Convert radians to degrees function.
   * ARGUMENTS:
   *   - angle values in radians:
   *       TYPE AngleInRadian;
   * RETURNS:
   *   (TYPE) angle value in degrees.
   */
  template<class TYPE> TYPE Rad2Deg( TYPE AngleInRadian )
  {
    return (TYPE)(AngleInRadian * Radian2Degree);
  } /* End of 'Rad2Deg' function */

  /* Minimum of two elements function.
   * ARGUMENTS:
   *   - values to compare:
   *       TYPE X, Y;
   * RETURNS:
   *   (TYPE) minimum of input values.
   */
  template<class TYPE> TYPE Min( TYPE X, TYPE Y )
  {
    return X < Y ? X : Y;
  } /* End of 'Min' function */

  /* Minimum of three elements function.
   * ARGUMENTS:
   *   - values to compare:
   *       TYPE X, Y, Z;
   * RETURNS:
   *   (TYPE) minimum of input values.
   */
  template<class TYPE> TYPE Min3( TYPE X, TYPE Y, TYPE Z )
  {
    if (X < Y)
      if (X < Z)
        return X;
      else
        return Z;
    else
      if (Y < Z)
        return Y;
      else
        return Z;
  } /* End of 'Min3' function */

  /* Maximum of two elements function.
   * ARGUMENTS:
   *   - values to compare:
   *       TYPE X, Y;
   * RETURNS:
   *   (TYPE) minimum of input values.
   */
  template<class TYPE> TYPE Max( TYPE X, TYPE Y )
  {
    return X > Y ? X : Y;
  } /* End of 'Max' function */

  /* Maximum of three elements function.
   * ARGUMENTS:
   *   - values to compare:
   *       TYPE X, Y, Z;
   * RETURNS:
   *   (TYPE) minimum of input values.
   */
  template<class TYPE> TYPE Max3( TYPE X, TYPE Y, TYPE Z )
  {
    if (X > Y)
      if (X > Z)
        return X;
      else
        return Z;
    else
      if (Y > Z)
        return Y;
      else
        return Z;
  } /* End of 'Max3' function */

  /* Absolute value evaluation function.
   * ARGUMENTS:
   *   - values:
   *       TYPE X;
   * RETURNS:
   *   (TYPE) absolute value of argument.
   */
  template<class TYPE> TYPE Abs( TYPE X )
  {
    return X < 0 ? -X : X;
  } /* End of 'Abs' function */

  /* Swap two value function.
   * ARGUMENTS:
   *   - values to swap:
   *       TYPE &A, &B;
   * RETURNS: None.
   */
  template<class TYPE> VOID Swap( TYPE &A, TYPE &B )
  {
    TYPE tmp = A;

    A = B;
    B = tmp;
  } /* End of 'Swap' function */

  /* Linear interpolation function.
   * ARGUMENTS:
   *   - interpolated parameter value (usual in [0..1]):
   *       TYPE Val;
   *   - result interpolated range:
   *       TYPE_CLS Y0, Y1;
   * RETURNS:
   *   (TYPE_CLS) result interpolarted value.
   */
  template<class TYPE, class TYPE_CLS>
    TYPE_CLS Lerp( TYPE Val, TYPE_CLS Y0, TYPE_CLS Y1 )
  {
    return Y0 * (1 - Val) + Y1 * Val;
  } /* End of 'Lerp' function */

  /* Clamp value function.
   * ARGUMENTS:
   *   - interpolated parameter value:
   *       TYPE Val;
   *   - interpolated value range:
   *       TYPE X0, X1;
   *   - result interpolated range:
   *       TYPE_CLS Y0, Y1;
   * RETURNS:
   *   (TYPE_CLS) result interpolated value.
   */
  template<class TYPE, class TYPE_CLS>
    TYPE_CLS Clamp( TYPE Val, TYPE X0, TYPE X1, TYPE_CLS Y0, TYPE_CLS Y1 )
  {
    TYPE t;

    if (X0 <= X1)
    {
      if (Val <= X0)
        return Y0;
      if (Val >= X1)
        return Y1;

      t = (Val - X0) / (X1 - X0);
      return Y0 * (1 - t) + Y1 * t;
    }
    if (Val >= X0)
      return Y0;
    if (Val <= X1)
      return Y1;

    t = (Val - X1) / (X0 - X1);
    return Y0 * (1 - t) + Y1 * t;
  } /* End of 'Clamp' function */

  /* Matrix 3x3 determinant evaluation function.
   * ARGUMENTS:
   *   - all matrix 3x3 components:
   *       TYPE M00, M01, M02, M10, M11, M12, M20, M21, M22;
   * RETURNS: 
   *   (TYPE) matrix determinant.
   */
  template<class TYPE>
    TYPE Determinant3x3( const TYPE M11, const TYPE M12, const TYPE M13,
                         const TYPE M21, const TYPE M22, const TYPE M23,
                         const TYPE M31, const TYPE M32, const TYPE M33 )
  {
    return M11 * M22 * M33 + M12 * M23 * M31 + M13 * M21 * M32 -
      M11 * M23 * M32 - M12 * M21 * M33 - M13 * M22 * M31;
  } /* End of 'Determinant3x3' function */

  /* Construct 3x3 matrix of rotation around arbitrary axis function.
   * ARGUMENTS:
   *   - result 3x3 array with matrix:
   *       TYPE RotMatr[3][3];
   *   - rotation angle (in degrees):
   *       const TYPE AngleInDegree;
   *   - rotation vector components:
   *       const TYPE AxisX, AxisY, AxisZ;
   * RETURN: None.
   */
  template<class TYPE, INT N>
    VOID BuildRotateMatrix3x3( TYPE RotMatr[N][N], const TYPE AngleInDegree,
             const TYPE AxisX, const TYPE AxisY, const TYPE AxisZ )
  {
    TYPE
      s, h, vx, vy, vz, len, Angle;

    len = AxisX * AxisX + AxisY * AxisY + AxisZ * AxisZ;

    Angle = AngleInDegree / 2;

#ifdef __TSG_ASM__    
    _asm {
      /* FST(0) Angle (from degree to radian) */
      fld  Angle
      fmul Degree2Radian

      /* FST(0) - cos, FST(1) - sin */
      fsincos

      fstp s    /* cos -> cosine */
      fstp h    /* sin -> sine */
    }
#else /* __TSG_ASM__ */
    s = cos(AngleInDegree);
    h = sin(AngleInDegree);
#endif /* __TSG_ASM__ */

    if (COM_ABS(len) > Threshold && COM_ABS(len - 1) > Threshold)
    {
      len = sqrt(len);
      vx = AxisX * h / len;
      vy = AxisY * h / len;
      vz = AxisZ * h / len;
    }
    else
    {
      vx = h * AxisX;
      vy = h * AxisY;
      vz = h * AxisZ;
    }

    RotMatr[0][0] = 1 - 2 * (vy * vy + vz * vz);
    RotMatr[0][1] = 2 * vx * vy - 2 * s * vz;
    RotMatr[0][2] = 2 * s * vy + 2 * vx * vz;

    RotMatr[1][0] = 2 * vx * vy + 2 * s * vz;
    RotMatr[1][1] = 1 - 2 * (vx * vx + vz * vz);
    RotMatr[1][2] = -2 * s * vx + 2 * vy * vz;

    RotMatr[2][0] = -2 * s * vy + 2 * vx * vz;
    RotMatr[2][1] = 2 * s * vx + 2 * vy * vz;
    RotMatr[2][2] = 1 - 2 * (vx * vx + vy * vy);
  } /* End of 'BuildRotateMatrix3x3' function */

  /* Calculation inverse kinematics of two linked sticks by
   * specified length of every part and end position.
   * ARGUMENTS:
   *   - clockwise flag:
   *       BOOL IsAntiClockWise,
   *   - segment length:
   *       TYPE L1, L2;
   *   - end point coordinates:
   *       TYPE X, Y;
   *   - result angles sine/cosine values:
   *       TYPE *SinA1, *CosA1, *SinA2, *CosA2;
   * RETURNS:
   *   (BOOL) FALSE for abnormal cases, TRUE otherwise.
   */
  template<class TYPE>
    BOOL IK2( BOOL IsAntiClockWise,
             TYPE L1, TYPE L2, TYPE X, TYPE Y,
             TYPE *SinA1, TYPE *CosA1, TYPE *SinA2, TYPE *CosA2 )
  {
    TYPE
      d,
      x2_y2 = X * X + Y * Y,
      sqrt_x2_y2,
      l12_l22 = L1 * L1 + L2 * L2,
      A1, A2, A, B, P, G;
#ifdef __TSG_ASM__
    TYPE sin1, cos1, sin2, cos2;
#endif /* __TSG_ASM__ */

    /* If squared distance equal than sticks shortest length */
    if (x2_y2 == 0)
    {
      *SinA1 = 0;
      *CosA1 = 1;
      *SinA2 = 0;
      *CosA2 = -1;
      return FALSE;
    }
    /* If squared distance more than sticks longest length */
    if (x2_y2 > l12_l22 + 2 * L1 * L2)
    {
      *SinA1 = Y / (d = sqrt(x2_y2));
      *CosA1 = X / d;
      *SinA2 = 0;
      *CosA2 = 1;
      return FALSE;
    }
    /* If squared distance less than sticks shortest length */
    if (x2_y2 < l12_l22 - 2 * L1 * L2)
    {
      *SinA1 = Y / (d = sqrt(x2_y2));
      *CosA1 = X / d;
      *SinA2 = 0;
      *CosA2 = -1;
      return FALSE;
    }

    /* Common case */
    A = atan2(Y, X);
    B = acos((L1 * L1 - L2 * L2 + x2_y2) / (2.0 * L1 * (sqrt_x2_y2 = sqrt(x2_y2))));
    /* Check clockwise flag */
    if (IsAntiClockWise)
    {
      A1 = A + B;
      G = acos((L2 * L2 - L1 * L1 + x2_y2) / (2.0 * L2 * sqrt_x2_y2));
      P = Pi - G - B;
      A2 = Pi + P;
    }
    else
    {
      A1 = A - B;
      G = acos((L2 * L2 - L1 * L1 + x2_y2) / (2.0 * L2 * sqrt_x2_y2));
      P = Pi - G - B;
      A2 = Pi - P;
    }

#ifdef __TSG_ASM__
    _asm {
      fld A1

      fsincos
      
      fstp cos1
      fstp sin1

      fld A2

      fsincos
      
      fstp cos2
      fstp sin2
    }
    *CosA1 = cos1;
    *SinA1 = sin1;
    *CosA2 = cos2;
    *SinA2 = sin2;
#else /* __TSG_ASM__ */
    *SinA1 = sin(A1);
    *CosA1 = cos(A1);
    *SinA2 = sin(A2);
    *CosA2 = cos(A2); 
#endif /* __TSG_ASM__ */
    return TRUE;
  } /* End of 'TSG_IK2' function */

  /* Calculation inverse kinematics of two linked sticks by
   * specified length of every part and end position.
   * ARGUMENTS:
   *   - clockwise flag:
   *       BOOL IsAntiClockWise,
   *   - segment length:
   *       TYPE L1, L2;
   *   - end point coordinates:
   *       TYPE X, Y;
   *   - result angles in degrees:
   *       TYPE *A1, *A2;
   * RETURNS:
   *   (BOOL) FALSE for abnormal cases, TRUE otherwise.
   */
  template<class TYPE>
    BOOL IK2( BOOL IsAntiClockWise,
             TYPE L1, TYPE L2, TYPE X, TYPE Y, TYPE *A1, TYPE *A2 )
  {
    TYPE
      x2_y2 = X * X + Y * Y,
      sqrt_x2_y2,
      l12_l22 = L1 * L1 + L2 * L2,
      A, B, G;

    /* If squared distance equal than sticks shortest length */
    if (x2_y2 == 0)
    {
      *A1 = 0;
      *A2 = 180;
      return FALSE;
    }
    /* If squared distance more than sticks longest length */
    if (x2_y2 > l12_l22 + 2 * L1 * L2)
    {
      *A1 = atan2(Y, X) * Radian2Degree;
      *A2 = 0;
      return FALSE;
    }
    /* If squared distance less than sticks shortest length */
    if (x2_y2 < l12_l22 - 2 * L1 * L2)
    {
      *A1 = atan2(Y, X) * Radian2Degree;
      *A2 = 180;
      return FALSE;
    }

    /* Common case */
    A = atan2(Y, X);
    B = acos((L1 * L1 - L2 * L2 + x2_y2) / (2.0 * L1 * (sqrt_x2_y2 = sqrt(x2_y2))));
    /* Check clockwise flag */
    if (IsAntiClockWise)
    {
      *A1 = (A + B) * Radian2Degree;
      G = acos((L2 * L2 - L1 * L1 + x2_y2) / (2.0 * L2 * sqrt_x2_y2));
      *A2 = 360 - (G + B) * Radian2Degree;
    }
    else
    {
      *A1 = (A - B) * Radian2Degree;
      G = acos((L2 * L2 - L1 * L1 + x2_y2) / (2.0 * L2 * sqrt_x2_y2));
      *A2 = (G + B) * Radian2Degree;
    }

    return TRUE;
  } /* End of 'TSG_IK2' function */

  /* Min/max box handle class */
  template<class TYPE> class TMinMax
  {
  private:
    /* Initialization flag (first usage) */
    BOOL IsFirst;
  public:
    /* Minimum and maximum bound box points */
    TVec<TYPE> Min, Max;

    /* Default class constructor */
    TMinMax( VOID )
    {
      IsFirst = TRUE;
    } /* End of 'TMinMax' constructor */

    /* Reset min/max info function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      IsFirst = TRUE;
    } /* End of 'Reset' function */

    /* Account a new point function.
     * ARGUMENTS:
     *   - new point coordinates:
     *       const TVec<TYPE> &Point;
     * RETURNS: None.
     */
    VOID Add( const TVec<TYPE> &Point )
    {
      if (IsFirst)
      {
        IsFirst = FALSE;
        Min = Max = Point;
      }
      else
      {
        /* Account per coordinate info */
        if (Min.X > Point.X)
          Min.X = Point.X;
        if (Min.Y > Point.Y)
          Min.Y = Point.Y;
        if (Min.Z > Point.Z)
          Min.Z = Point.Z;
        if (Max.X < Point.X)
          Max.X = Point.X;
        if (Max.Y < Point.Y)
          Max.Y = Point.Y;
        if (Max.Z < Point.Z)
          Max.Z = Point.Z;
      }
    } /* End of 'Add' function */

    /* Account a new min/max info function.
     * ARGUMENTS:
     *   - MinMax object:
     *       const TMinMax &MinMax;
     * RETURNS: None.
     */
    VOID Add( const TMinMax &MinMax )
    {
      Add(MinMax.Min);
      Add(MinMax.Max);
    } /* End of 'Add' function */

    /* Account a new point function.
     * ARGUMENTS:
     *   - add points array:
     *       const TVec<TYPE> *Data;
     *   - add points length:
     *       INT N;
     * RETURNS: None.
     */
    template<class TYPE> VOID Add( const TVec<TYPE> *Data, INT N )
    {
      for (INT i = 0; i < N; i++)
        Add(Data[i]);
    } /* End of 'Add' function */
  }; /* End of 'TMinMax' class */
};

#endif /* _TSGDEF_H_ */

/* END OF 'TSGDEF.H' FILE */
