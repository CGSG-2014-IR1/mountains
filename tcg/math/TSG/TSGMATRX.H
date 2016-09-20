/***************************************************************
 * Copyright (C) 2006-2014
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGMATRX.H
 * PURPOSE     : Tough Space Graphics library.
 *               Matrix class template declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006-2007-2011-2012-2015.
 *               Vitaly A. Galinsky,
 *               Yaroslav Drugov (matrices constructors).
 *               Artemy Sergeev (assembly trigonometry inline).
 *               Kirill Lopatin (added some functions).
 *               Makar Solomatin (added some functions).
 * LAST UPDATE : 06.11.2015 (from 07.01.2013, 28.12.12, 14.12.2012, 05.04.2011, 08.04.2007, 13.08.2006, 21.05.2006)
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

#ifndef _TSGMATRX_H_
#define _TSGMATRX_H_

#include <string.h>
#include <math.h>

#include "tsgdef.h"

namespace tsg
{
  /* Base matrix of affine transformation class template declaration */
  template<class TYPE> class TMatr
  {
  public:
    /* Global unit (identity) matrix for optimization */
    static const TYPE UnitMatrix[4][4];

    /* Matrix 4x4 data array
     * Matrix view (always affine transformation representation):
     *   a11 a12 a13 0
     *   a21 a22 a23 0
     *   a31 a32 a33 0
     *   a41 a42 a43 1
     */
    TYPE A[4][4];

    /* Default constructor.
     * ARGUMENTS: None.
     */
    TMatr( VOID )
    {
    } /* End of 'TMatr' constructor */

    /* Constructor by matrix.
     * ARGUMENTS: 
     *   - matrix to construct by:
     *       const TMatr &Matr;
     */
    TMatr( const TMatr &Matr )
    {
      memcpy(A, &Matr.A, sizeof(A));
    } /* End of 'TMatr' constructor */

    /* Constructor by components.
     * ARGUMENTS:
     *   - value of all components:
     *       TYPE
     *         M00, M01, M02,
     *         M10, M11, M12,
     *         M20, M21, M22,
     *         M30, M31, M32;
     */
    TMatr( TYPE M00, TYPE M01, TYPE M02,
           TYPE M10, TYPE M11, TYPE M12,
           TYPE M20, TYPE M21, TYPE M22,
           TYPE M30 = 0, TYPE M31 = 0, TYPE M32 = 0)
    {
      A[0][0] = M00;
      A[0][1] = M01;
      A[0][2] = M02;
      A[0][3] = 0;

      A[1][0] = M10;
      A[1][1] = M11;
      A[1][2] = M12;
      A[1][3] = 0;

      A[2][0] = M20;
      A[2][1] = M21;
      A[2][2] = M22;
      A[2][3] = 0;

      A[3][0] = M30;
      A[3][1] = M31;
      A[3][2] = M32;
      A[3][3] = 1;
    } /* End of 'TMatr' constructor */

    /* Constructor by components.
     * ARGUMENTS:
     *   - value of all components:
     *       TYPE
     *         M00, M01, M02, M03,
     *         M10, M11, M12, M13,
     *         M20, M21, M22, M23,
     *         M30, M31, M32, M33;
     */
    TMatr( TYPE M00, TYPE M01, TYPE M02, TYPE M03,
           TYPE M10, TYPE M11, TYPE M12, TYPE M13,
           TYPE M20, TYPE M21, TYPE M22, TYPE M23,
           TYPE M30, TYPE M31, TYPE M32, TYPE M33)
    {
      A[0][0] = M00;
      A[0][1] = M01;
      A[0][2] = M02;
      A[0][3] = M03;

      A[1][0] = M10;
      A[1][1] = M11;
      A[1][2] = M12;
      A[1][3] = M13;

      A[2][0] = M20;
      A[2][1] = M21;
      A[2][2] = M22;
      A[2][3] = M23;

      A[3][0] = M30;
      A[3][1] = M31;
      A[3][2] = M32;
      A[3][3] = M33;
    } /* End of 'TMatr' constructor */

    /* Per components multiplication of two matrices function.
     * ARGUMENTS:
     *   - matrix to multiply:
     *       const TMatr &Matr;
     * RETURNS: 
     *   (TMatr) result of multiplication.
     */
    TMatr operator*( const TMatr &M ) const
    {
      return TMatr<TYPE>(A[0][0] * M.A[0][0] + A[0][1] * M.A[1][0] + A[0][2] * M.A[2][0] + A[0][3] * M.A[3][0],
                         A[0][0] * M.A[0][1] + A[0][1] * M.A[1][1] + A[0][2] * M.A[2][1] + A[0][3] * M.A[3][1],
                         A[0][0] * M.A[0][2] + A[0][1] * M.A[1][2] + A[0][2] * M.A[2][2] + A[0][3] * M.A[3][2],
                         A[0][0] * M.A[0][3] + A[0][1] * M.A[1][3] + A[0][2] * M.A[2][3] + A[0][3] * M.A[3][3],

                         A[1][0] * M.A[0][0] + A[1][1] * M.A[1][0] + A[1][2] * M.A[2][0] + A[1][3] * M.A[3][0],
                         A[1][0] * M.A[0][1] + A[1][1] * M.A[1][1] + A[1][2] * M.A[2][1] + A[1][3] * M.A[3][1],
                         A[1][0] * M.A[0][2] + A[1][1] * M.A[1][2] + A[1][2] * M.A[2][2] + A[1][3] * M.A[3][2],
                         A[1][0] * M.A[0][3] + A[1][1] * M.A[1][3] + A[1][2] * M.A[2][3] + A[1][3] * M.A[3][3],

                         A[2][0] * M.A[0][0] + A[2][1] * M.A[1][0] + A[2][2] * M.A[2][0] + A[2][3] * M.A[3][0],
                         A[2][0] * M.A[0][1] + A[2][1] * M.A[1][1] + A[2][2] * M.A[2][1] + A[2][3] * M.A[3][1],
                         A[2][0] * M.A[0][2] + A[2][1] * M.A[1][2] + A[2][2] * M.A[2][2] + A[2][3] * M.A[3][2],
                         A[2][0] * M.A[0][3] + A[2][1] * M.A[1][3] + A[2][2] * M.A[2][3] + A[2][3] * M.A[3][3],

                         A[3][0] * M.A[0][0] + A[3][1] * M.A[1][0] + A[3][2] * M.A[2][0] + A[3][3] * M.A[3][0],
                         A[3][0] * M.A[0][1] + A[3][1] * M.A[1][1] + A[3][2] * M.A[2][1] + A[3][3] * M.A[3][1],
                         A[3][0] * M.A[0][2] + A[3][1] * M.A[1][2] + A[3][2] * M.A[2][2] + A[3][3] * M.A[3][2],
                         A[3][0] * M.A[0][3] + A[3][1] * M.A[1][3] + A[3][2] * M.A[2][3] + A[3][3] * M.A[3][3]);
    } /* End of 'operator*' function */

    /* Per components multiplication of two matrices with assignment function.
     * ARGUMENTS:
     *   - matrix to multiply:
     *       const TMatr &Matr;
     * RETURNS: 
     *   (TMatr &) self-reference to matrix.
     */
    TMatr & operator*=( const TMatr &Matr )
    {
      TMatr ResMatr;

      ResMatr.A[0][0] = A[0][0] * Matr.A[0][0] + A[0][1] * Matr.A[1][0] +
        A[0][2] * Matr.A[2][0];
      ResMatr.A[1][0] = A[1][0] * Matr.A[0][0] + A[1][1] * Matr.A[1][0] +
        A[1][2] * Matr.A[2][0];
      ResMatr.A[2][0] = A[2][0] * Matr.A[0][0] + A[2][1] * Matr.A[1][0] +
        A[2][2] * Matr.A[2][0];
      ResMatr.A[3][0] = A[3][0] * Matr.A[0][0] + A[3][1] * Matr.A[1][0] +
        A[3][2] * Matr.A[2][0] + Matr.A[3][0];

      ResMatr.A[0][1] = A[0][0] * Matr.A[0][1] + A[0][1] * Matr.A[1][1] +
        A[0][2] * Matr.A[2][1];
      ResMatr.A[1][1] = A[1][0] * Matr.A[0][1] + A[1][1] * Matr.A[1][1] +
        A[1][2] * Matr.A[2][1];
      ResMatr.A[2][1] = A[2][0] * Matr.A[0][1] + A[2][1] * Matr.A[1][1] +
        A[2][2] * Matr.A[2][1];
      ResMatr.A[3][1] = A[3][0] * Matr.A[0][1] + A[3][1] * Matr.A[1][1] +
        A[3][2] * Matr.A[2][1] + Matr.A[3][1];

      ResMatr.A[0][2] = A[0][0] * Matr.A[0][2] + A[0][1] * Matr.A[1][2] +
        A[0][2] * Matr.A[2][2];
      ResMatr.A[1][2] = A[1][0] * Matr.A[0][2] + A[1][1] * Matr.A[1][2] +
        A[1][2] * Matr.A[2][2];
      ResMatr.A[2][2] = A[2][0] * Matr.A[0][2] + A[2][1] * Matr.A[1][2] +
        A[2][2] * Matr.A[2][2];
      ResMatr.A[3][2] = A[3][0] * Matr.A[0][2] + A[3][1] * Matr.A[1][2] +
        A[3][2] * Matr.A[2][2] + Matr.A[3][2];

      ResMatr.A[0][3] = 0;
      ResMatr.A[1][3] = 0;
      ResMatr.A[2][3] = 0;
      ResMatr.A[3][3] = 1;

      *this = ResMatr;
      return *this;
    } /* End of 'operator*=' function */

    /* Inverse matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) TRUE if inverse matrix exists and FALSE otherwise.
     */
    BOOL Inverse( VOID )
    {
      TMatr Tmp;
      TYPE Determinant;

      /* Obtain inverse matrix by Cramer 's rule */

      /* Get adjoint matrix */
      Tmp.A[0][0] = A[1][1] * A[2][2] - A[1][2] * A[2][1];
      Tmp.A[0][1] = A[0][2] * A[2][1] - A[0][1] * A[2][2];
      Tmp.A[0][2] = A[0][1] * A[1][2] - A[0][2] * A[1][1];
      Tmp.A[1][0] = A[1][2] * A[2][0] - A[1][0] * A[2][2];
      Tmp.A[1][1] = A[0][0] * A[2][2] - A[0][2] * A[2][0];
      Tmp.A[1][2] = A[0][2] * A[1][0] - A[0][0] * A[1][2];
      Tmp.A[2][0] = A[1][0] * A[2][1] - A[1][1] * A[2][0];
      Tmp.A[2][1] = A[0][1] * A[2][0] - A[0][0] * A[2][1];
      Tmp.A[2][2] = A[0][0] * A[1][1] - A[0][1] * A[1][0];
      Tmp.A[3][0] =
        -Determinant3x3(A[1][0], A[2][0], A[3][0], A[1][1], A[2][1],
          A[3][1], A[1][2], A[2][2], A[3][2]);
      Tmp.A[3][1] =
        Determinant3x3(A[0][0], A[2][0], A[3][0], A[0][1], A[2][1], A[3][1],
          A[0][2], A[2][2], A[3][2]);
      Tmp.A[3][2] =
        -Determinant3x3(A[0][0], A[1][0], A[3][0], A[0][1], A[1][1],
          A[3][1], A[0][2], A[1][2], A[3][2]);

      /* Obtain determinant of source left-top 3x3 matrix */
      Determinant =
        Determinant3x3(A[0][0], A[0][1], A[0][2], A[1][0], A[1][1], A[1][2],
          A[2][0], A[2][1], A[2][2]);

      /* Check determinant value */
      if (Determinant == 0)
        return FALSE;
      /* Copy result matrix */
      *this = Tmp;
      if (Determinant == 1.0)
        return TRUE;
      A[0][0] /= Determinant;
      A[0][1] /= Determinant;
      A[0][2] /= Determinant;
      A[1][0] /= Determinant;
      A[1][1] /= Determinant;
      A[1][2] /= Determinant;
      A[2][0] /= Determinant;
      A[2][1] /= Determinant;
      A[2][2] /= Determinant;
      A[3][0] /= Determinant;
      A[3][1] /= Determinant;
      A[3][2] /= Determinant;
      return TRUE;
    } /* End of 'Inverse' function */

    /* Inversing matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TMatr) result inverse matrix.
     */
    TMatr Inversing( VOID ) const
    {
      TMatr Tmp;
      TYPE Determinant;

      /* Obtain inverse matrix by Cramer 's rule */

      /* Get adjoint matrix */
      Tmp.A[0][0] = A[1][1] * A[2][2] - A[1][2] * A[2][1];
      Tmp.A[0][1] = A[0][2] * A[2][1] - A[0][1] * A[2][2];
      Tmp.A[0][2] = A[0][1] * A[1][2] - A[0][2] * A[1][1];
      Tmp.A[1][0] = A[1][2] * A[2][0] - A[1][0] * A[2][2];
      Tmp.A[1][1] = A[0][0] * A[2][2] - A[0][2] * A[2][0];
      Tmp.A[1][2] = A[0][2] * A[1][0] - A[0][0] * A[1][2];
      Tmp.A[2][0] = A[1][0] * A[2][1] - A[1][1] * A[2][0];
      Tmp.A[2][1] = A[0][1] * A[2][0] - A[0][0] * A[2][1];
      Tmp.A[2][2] = A[0][0] * A[1][1] - A[0][1] * A[1][0];
      Tmp.A[3][0] =
        -Determinant3x3(A[1][0], A[2][0], A[3][0], A[1][1], A[2][1],
          A[3][1], A[1][2], A[2][2], A[3][2]);
      Tmp.A[3][1] =
        Determinant3x3(A[0][0], A[2][0], A[3][0], A[0][1], A[2][1], A[3][1],
          A[0][2], A[2][2], A[3][2]);
      Tmp.A[3][2] =
        -Determinant3x3(A[0][0], A[1][0], A[3][0], A[0][1], A[1][1],
          A[3][1], A[0][2], A[1][2], A[3][2]);

      Tmp.A[0][3] = 0;
      Tmp.A[1][3] = 0;
      Tmp.A[2][3] = 0;
      Tmp.A[3][3] = 1;

      /* Obtain determinant of source left-top 3x3 matrix */
      Determinant =
        Determinant3x3(A[0][0], A[0][1], A[0][2], A[1][0], A[1][1], A[1][2],
          A[2][0], A[2][1], A[2][2]);

      /* Check determinant value */
      if (Determinant != 0 && Determinant != 1.0)
      {
        Tmp.A[0][0] /= Determinant;
        Tmp.A[0][1] /= Determinant;
        Tmp.A[0][2] /= Determinant;
        Tmp.A[1][0] /= Determinant;
        Tmp.A[1][1] /= Determinant;
        Tmp.A[1][2] /= Determinant;
        Tmp.A[2][0] /= Determinant;
        Tmp.A[2][1] /= Determinant;
        Tmp.A[2][2] /= Determinant;
        Tmp.A[3][0] /= Determinant;
        Tmp.A[3][1] /= Determinant;
        Tmp.A[3][2] /= Determinant;
      }
      return Tmp;
    } /* End of 'Inversing' function */

    /***
     * Set matrix to specified transformation functions
     ***/

    /* Reset transformation matrix data function.
     * ARGUMENTS: None.
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetUnit( VOID )
    {
      memcpy(A, UnitMatrix, sizeof(A));
      return *this;
    } /* End of 'SetUnit' function */

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetTranslate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      memcpy(A, UnitMatrix, sizeof(A) - 4 * sizeof(TYPE));
      A[3][0] = Dx;
      A[3][1] = Dy;
      A[3][2] = Dz;
      A[3][3] = 1;
      return *this;
    } /* End of 'SetTranslate' function */

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetTranslate( const TVec<TYPE> &Shift )
    {
      return SetTranslate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'SetTranslate' function */

    /* Set rotation around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      memcpy(A, UnitMatrix, sizeof(A));
      A[1][1] = AngleCosine;
      A[1][2] = AngleSine;
      A[2][1] = -AngleSine;
      A[2][2] = AngleCosine;
      return *this;
    } /* End of 'SetRotateX' function */

    /* Set rotation around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateX( TYPE AngleInDegree )
    {
#ifdef __TSG_ASM__
      memcpy(A, UnitMatrix, sizeof(A));
      _asm {
        /* [EBX] is a pointer to 'this' */
        mov  EBX, this

        /* FST(0) Angle (from degree to radian) */
        fld  AngleInDegree
        fmul Degree2Radian

        /* FST(0) - cos, FST(1) - sin */
        fsincos

        fld  st(0)
        //fstp A[1][1] /* cos -> a11 */
        fstp [EBX]TMatr.A[1 * 16 + 1 * 4]
        //fstp A[2][2] /* cos -> a22 */
        fstp [EBX]TMatr.A[2 * 16 + 2 * 4]

        fld  st(0)     /* duplicate st(0) */
        //fstp A[1][2] /* sin -> a12 */
        fstp [EBX]TMatr.A[1 * 16 + 2 * 4]
        fldz           /* push 0 (st(0) = 0) */
        fsubr          /* st(0) = 0 - sin() */
        //fstp A[2][1] /* -sin -> a21 */
        fstp [EBX]TMatr.A[2 * 16 + 1 * 4]
      }
      return *this;
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return SetRotateX(SinVal, CosVal);
#endif /* __TSG_ASM__ */
    } /* End of 'SetRotateX' function */

    /* Set rotation around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      memcpy(A, UnitMatrix, sizeof(A));
      A[0][0] = AngleCosine;
      A[0][2] = -AngleSine;
      A[2][0] = AngleSine;
      A[2][2] = AngleCosine;
      return *this;
    } /* End of 'SetRotateY' function */

    /* Set rotation around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateY( TYPE AngleInDegree )
    {
#ifdef __TSG_ASM__
      memcpy(A, UnitMatrix, sizeof(A));
      _asm {
        /* [EBX] is a pointer to 'this' */
        mov  EBX, this

        /* FST(0) Angle (from degree to radian) */
        fld  AngleInDegree
        fmul Degree2Radian

        /* FST(0) - cos, FST(1) - sin */
        fsincos

        fld  st(0)
        //fstp A[1][1] /* cos -> a00 */
        fstp [EBX]TMatr.A[0 * 16 + 0 * 4]
        //fstp A[2][2] /* cos -> a22 */
        fstp [EBX]TMatr.A[2 * 16 + 2 * 4]

        fld  st(0)     /* duplicate st(0) */
        //fstp A[1][2] /* sin -> a20 */
        fstp [EBX]TMatr.A[2 * 16 + 0 * 4]
        fldz           /* push 0 (st(0) = 0) */
        fsubr          /* st(0) = 0 - sin() */
        //fstp A[2][1] /* -sin -> a02 */
        fstp [EBX]TMatr.A[0 * 16 + 2 * 4]
      }
      return *this;
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return SetRotateY(SinVal, CosVal);
#endif /* __TSG_ASM__ */
    } /* End of 'SetRotateY' function */

    /* Set rotation around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      memcpy(A, UnitMatrix, sizeof(A));
      A[0][0] = AngleCosine;
      A[0][1] = AngleSine;
      A[1][0] = -AngleSine;
      A[1][1] = AngleCosine;
      return *this;
    } /* End of 'SetRotateZ' function */

    /* Set rotation around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotateZ( TYPE AngleInDegree )
    {
#ifdef __TSG_ASM__
      memcpy(A, UnitMatrix, sizeof(A));

      _asm {
        /* [EBX] is a pointer to 'this' */
        mov  EBX, this

        /* FST(0) Angle (from degree to radian) */
        fld  AngleInDegree
        fmul Degree2Radian

        /* FST(0) - cos, FST(1) - sin */
        fsincos

        fld  st(0)
        //fstp A[1][1] /* cos -> a00 */
        fstp [EBX]TMatr.A[0 * 16 + 0 * 4]
        //fstp A[2][2] /* cos -> a11 */
        fstp [EBX]TMatr.A[1 * 16 + 1 * 4]

        fld  st(0)     /* duplicate st(0) */
        //fstp A[1][2] /* sin -> a01 */
        fstp [EBX]TMatr.A[0 * 16 + 1 * 4]
        fldz           /* push 0 (st(0) = 0) */
        fsubr          /* st(0) = 0 - sin() */
        //fstp A[2][1] /* -sin -> a10 */
        fstp [EBX]TMatr.A[1 * 16 + 0 * 4]
      }
      return *this;
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return SetRotateX(SinVal, CosVal);
#endif /* __TSG_ASM__ */
    } /* End of 'SetRotateZ' function */

    /* Set rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotate( TYPE AngleInDegree,
                       TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      BuildRotateMatrix3x3<TYPE, 4>(A, AngleInDegree, AxisX, AxisY, AxisZ);

      A[0][3] = 0;
      A[1][3] = 0;
      A[2][3] = 0;
      A[3][0] = 0;
      A[3][1] = 0;
      A[3][2] = 0;
      A[3][3] = 1;

      return *this;
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotate( TYPE AngleSine, TYPE AngleCosine,
                       TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return
        SetRotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotate( TYPE AngleSine, TYPE AngleCosine,
                       const TVec<TYPE> &Vec )
    {
      return SetRotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetRotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
    {
      return SetRotate(AngleInDegree, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'SetRotate' function */

    /* Set scaling along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetScale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      memcpy(A, UnitMatrix, sizeof(A));
      A[0][0] = Sx;
      A[1][1] = Sy;
      A[2][2] = Sz;
      return *this;
    } /* End of 'SetScale' function */

    /* Set scaling along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & SetScale( const TVec<TYPE> &ScaleVec )
    {
      return SetScale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'SetScale' function */

    /***
     * Apply specified transformation to matrix (self-transform) functions
     ***/

    /* Translate matrix function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Translate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      A[3][0] += Dx;
      A[3][1] += Dy;
      A[3][2] += Dz;
      return *this;
    } /* End of 'Translate' function */

    /* Translate matrix function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Translate( const TVec<TYPE> &Shift )
    {
      return Translate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translate' function */

    /* Rotate around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE RM01, RM11, RM21, RM31, RM02, RM12, RM22, RM32;

      /* Calculate changing matrix elements */
      RM01 = A[0][1] * AngleCosine - A[0][2] * AngleSine;
      RM11 = A[1][1] * AngleCosine - A[1][2] * AngleSine;
      RM21 = A[2][1] * AngleCosine - A[2][2] * AngleSine;
      RM31 = A[3][1] * AngleCosine - A[3][2] * AngleSine;

      RM02 = A[0][1] * AngleSine + A[0][2] * AngleCosine;
      RM12 = A[1][1] * AngleSine + A[1][2] * AngleCosine;
      RM22 = A[2][1] * AngleSine + A[2][2] * AngleCosine;
      RM32 = A[3][1] * AngleSine + A[3][2] * AngleCosine;

      /* Store changed elements to matrix */
      A[0][1] = RM01;
      A[1][1] = RM11;
      A[2][1] = RM21;
      A[3][1] = RM31;

      A[0][2] = RM02;
      A[1][2] = RM12;
      A[2][2] = RM22;
      A[3][2] = RM32;

      return *this;
    } /* End of 'RotateX' function */

    /* Rotate around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateX( TYPE AngleInDegree )
    { 
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotateX(SinVal, CosVal);
    } /* End of 'RotateX' function */

    /* Rotate around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE RM00, RM10, RM20, RM30, RM02, RM12, RM22, RM32;
        
      /* Calculate changing matrix elements */
      RM00 = A[0][2] * AngleSine + A[0][0] * AngleCosine;
      RM10 = A[1][2] * AngleSine + A[1][0] * AngleCosine;
      RM20 = A[2][2] * AngleSine + A[2][0] * AngleCosine;
      RM30 = A[3][2] * AngleSine + A[3][0] * AngleCosine;

      RM02 = A[0][2] * AngleCosine - A[0][0] * AngleSine;
      RM12 = A[1][2] * AngleCosine - A[1][0] * AngleSine;
      RM22 = A[2][2] * AngleCosine - A[2][0] * AngleSine;
      RM32 = A[3][2] * AngleCosine - A[3][0] * AngleSine;
      
      /* Store changed elements to matrix */
      A[0][0] = RM00;
      A[1][0] = RM10;
      A[2][0] = RM20;
      A[3][0] = RM30;

      A[0][2] = RM02;
      A[1][2] = RM12;
      A[2][2] = RM22;
      A[3][2] = RM32;
      
      return *this;
    } /* End of 'RotateY' function */

    /* Rotate around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateY( TYPE AngleInDegree )
    {
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotateY(SinVal, CosVal);
    } /* End of 'RotateY' function */

    /* Rotate around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE RM00, RM10, RM20, RM30, RM01, RM11, RM21, RM31;

      /* Calculate changing matrix elements */
      RM00 = A[0][0] * AngleCosine - A[0][1] * AngleSine;
      RM10 = A[1][0] * AngleCosine - A[1][1] * AngleSine;
      RM20 = A[2][0] * AngleCosine - A[2][1] * AngleSine;
      RM30 = A[3][0] * AngleCosine - A[3][1] * AngleSine;

      RM01 = A[0][0] * AngleSine + A[0][1] * AngleCosine;
      RM11 = A[1][0] * AngleSine + A[1][1] * AngleCosine;
      RM21 = A[2][0] * AngleSine + A[2][1] * AngleCosine;
      RM31 = A[3][0] * AngleSine + A[3][1] * AngleCosine;

      /* Store changed elements to matrix */
      A[0][0] = RM00;
      A[1][0] = RM10;
      A[2][0] = RM20;
      A[3][0] = RM30;

      A[0][1] = RM01;
      A[1][1] = RM11;
      A[2][1] = RM21;
      A[3][1] = RM31;

      return *this;
    } /* End of 'RotateZ' function */

    /* Rotate around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & RotateZ( TYPE AngleInDegree )
    {
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotateZ(SinVal, CosVal);
    } /* End of 'RotateZ' function */

    /* Rotate around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Rotate( TYPE AngleInDegree,
                    TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      TYPE Rm[3][3], Tm[4][4];

      BuildRotateMatrix3x3<TYPE, 3>(Rm, AngleInDegree, AxisX, AxisY, AxisZ);

      Tm[0][0] = A[0][0] * Rm[0][0] + A[0][1] * Rm[1][0] + A[0][2] * Rm[2][0];
      Tm[1][0] = A[1][0] * Rm[0][0] + A[1][1] * Rm[1][0] + A[1][2] * Rm[2][0];
      Tm[2][0] = A[2][0] * Rm[0][0] + A[2][1] * Rm[1][0] + A[2][2] * Rm[2][0];
      Tm[3][0] = A[3][0] * Rm[0][0] + A[3][1] * Rm[1][0] + A[3][2] * Rm[2][0];

      Tm[0][1] = A[0][0] * Rm[0][1] + A[0][1] * Rm[1][1] + A[0][2] * Rm[2][1];
      Tm[1][1] = A[1][0] * Rm[0][1] + A[1][1] * Rm[1][1] + A[1][2] * Rm[2][1];
      Tm[2][1] = A[2][0] * Rm[0][1] + A[2][1] * Rm[1][1] + A[2][2] * Rm[2][1];
      Tm[3][1] = A[3][0] * Rm[0][1] + A[3][1] * Rm[1][1] + A[3][2] * Rm[2][1];

      Tm[0][2] = A[0][0] * Rm[0][2] + A[0][1] * Rm[1][2] + A[0][2] * Rm[2][2];
      Tm[1][2] = A[1][0] * Rm[0][2] + A[1][1] * Rm[1][2] + A[1][2] * Rm[2][2];
      Tm[2][2] = A[2][0] * Rm[0][2] + A[2][1] * Rm[1][2] + A[2][2] * Rm[2][2];
      Tm[3][2] = A[3][0] * Rm[0][2] + A[3][1] * Rm[1][2] + A[3][2] * Rm[2][2];

      Tm[0][3] = 0;
      Tm[1][3] = 0;
      Tm[2][3] = 0;
      Tm[3][3] = 1;

      memcpy(A, Tm, sizeof(A));
      return *this;
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Rotate( TYPE AngleSine, TYPE AngleCosine,
                    TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return
        Rotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Rotate( TYPE AngleSine, TYPE AngleCosine,
                    const TVec<TYPE> &Vec )
    {
      return Rotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Rotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
    {
      return Rotate(AngleInDegree, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Scale along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Scale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      A[0][0] *= Sx;
      A[1][0] *= Sx;
      A[2][0] *= Sx;
      A[3][0] *= Sx;

      A[0][1] *= Sy;
      A[1][1] *= Sy;
      A[2][1] *= Sy;
      A[3][1] *= Sy;

      A[0][2] *= Sz;
      A[1][2] *= Sz;
      A[2][2] *= Sz;
      A[3][2] *= Sz;
      return *this;
    } /* End of 'Scale' function */

    /* Scale along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Scale( const TVec<TYPE> &ScaleVec )
    {
      return Scale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scale' function */

    /* Transform matrix by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & Transform( const TTrans<TYPE> &Trans )
    {
      *this *= Trans.M;
      return *this;
    } /* End of 'Transform' function */

    /* Inverse transform matrix by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TMatr &) self-pointer to matrix.
     */
    TMatr & InvTransform( const TTrans<TYPE> &Trans )
    {
      *this = Trans.InvM * *this;
      return *this;
    } /* End of 'InvTransform' function */

    /***
     * Apply specified transformation to matrix functions
     ***/

    /* Translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Translation( TYPE Dx, TYPE Dy, TYPE Dz ) const
    {
      TMatr res;

      memcpy(&res, this, sizeof(A) - 4 * sizeof(TYPE));
      res.A[3][0] = A[3][0] + Dx;
      res.A[3][1] = A[3][1] + Dy;
      res.A[3][2] = A[3][2] + Dz;
      res.A[3][3] = 1;
      return res;
    } /* End of 'Translation' function */

    /* Translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Translation( const TVec<TYPE> &Shift ) const
    {
      return Translation(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translation' function */

    /* Rotation around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationX( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return
        TMatr(A[0][0], 
              A[0][1] * AngleCosine - A[0][2] * AngleSine,
              A[0][1] * AngleSine + A[0][2] * AngleCosine,
              A[1][0],
              A[1][1] * AngleCosine - A[1][2] * AngleSine,
              A[1][1] * AngleSine + A[1][2] * AngleCosine,
              A[2][0],
              A[2][1] * AngleCosine - A[2][2] * AngleSine,
              A[2][1] * AngleSine + A[2][2] * AngleCosine,
              A[3][0],
              A[3][1] * AngleCosine - A[3][2] * AngleSine,
              A[3][1] * AngleSine + A[3][2] * AngleCosine);
    } /* End of 'RotationX' function */

    /* Rotation around 'X' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationX( TYPE AngleInDegree ) const
    {
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotationX(SinVal, CosVal);
    } /* End of 'RotationX' function */

    /* Rotation around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationY( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return
        TMatr(A[0][2] * AngleSine + A[0][0] * AngleCosine,
              A[0][1],
              A[0][2] * AngleCosine - A[0][0] * AngleSine,
              A[1][2] * AngleSine + A[1][0] * AngleCosine,
              A[1][1],
              A[1][2] * AngleCosine - A[1][0] * AngleSine,
              A[2][2] * AngleSine + A[2][0] * AngleCosine,
              A[2][1],
              A[2][2] * AngleCosine - A[2][0] * AngleSine,
              A[3][2] * AngleSine + A[3][0] * AngleCosine,
              A[3][1],
              A[3][2] * AngleCosine - A[3][0] * AngleSine);
    } /* End of 'RotationY' function */

    /* Rotation around 'Y' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationY( TYPE AngleInDegree ) const
    {
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotationY(SinVal, CosVal);
    } /* End of 'RotationY' function */

    /* Rotation around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationZ( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return
        TMatr(A[0][0] * AngleCosine - A[0][1] * AngleSine,
              A[0][0] * AngleSine + A[0][1] * AngleCosine,
              A[0][2],
              A[1][0] * AngleCosine - A[1][1] * AngleSine,
              A[1][0] * AngleSine + A[1][1] * AngleCosine,
              A[1][2],
              A[2][0] * AngleCosine - A[2][1] * AngleSine,
              A[2][0] * AngleSine + A[2][1] * AngleCosine,
              A[2][2],
              A[3][0] * AngleCosine - A[3][1] * AngleSine,
              A[3][0] * AngleSine + A[3][1] * AngleCosine,
              A[3][2]);
    } /* End of 'RotationZ' function */

    /* Rotation around 'Z' axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr RotationZ( TYPE AngleInDegree ) const
    {
      TYPE SinVal, CosVal;

#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld AngleInDegree
        fmul Degree2Radian

        fsincos

        fstp CosVal
        fstp SinVal
      }
#else /* __TSG_ASM__ */
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree); 

      SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);
#endif /* __TSG_ASM__ */
      return RotationZ(SinVal, CosVal);
    } /* End of 'RotationZ' function */

    /* Rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Rotation( TYPE AngleInDegree,
                    TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      TYPE
        angle, s, h,
        vx, vy, vz, len,
        Rm[3][3];

      TYPE SinVal, CosVal;

      angle /= 2;
#ifdef __TSG_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld angle
        fmul Degree2Radian

        fsincos

        fstp s
        fstp h
      }
#else /* __TSG_ASM__ */
      DOUBLE angle = Deg2Rad(AngleInDegree); 

      h = sin(AngleInRadians), s = cos(AngleInRadians);
#endif /* __TSG_ASM__ */ 

      len = AxisX * AxisX + AxisY * AxisY + AxisZ * AxisZ;
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

      Rm[0][0] = 1 - 2 * (vy * vy + vz * vz);
      Rm[0][1] = 2 * vx * vy - 2 * s * vz;
      Rm[0][2] = 2 * s * vy + 2 * vx * vz;

      Rm[1][0] = 2 * vx * vy + 2 * s * vz;
      Rm[1][1] = 1 - 2 * (vx * vx + vz * vz);
      Rm[1][2] = -2 * s * vx + 2 * vy * vz;

      Rm[2][0] = -2 * s * vy + 2 * vx * vz;
      Rm[2][1] = 2 * s * vx + 2 * vy * vz;
      Rm[2][2] = 1 - 2 * (vx * vx + vy * vy);

      return
        TMatr(A[0][0] * Rm[0][0] + A[0][1] * Rm[1][0] + A[0][2] * Rm[2][0],
              A[0][0] * Rm[0][1] + A[0][1] * Rm[1][1] + A[0][2] * Rm[2][1],
              A[0][0] * Rm[0][2] + A[0][1] * Rm[1][2] + A[0][2] * Rm[2][2],
              A[1][0] * Rm[0][0] + A[1][1] * Rm[1][0] + A[1][2] * Rm[2][0],
              A[1][0] * Rm[0][1] + A[1][1] * Rm[1][1] + A[1][2] * Rm[2][1],
              A[1][0] * Rm[0][2] + A[1][1] * Rm[1][2] + A[1][2] * Rm[2][2],
              A[2][0] * Rm[0][0] + A[2][1] * Rm[1][0] + A[2][2] * Rm[2][0],
              A[2][0] * Rm[0][1] + A[2][1] * Rm[1][1] + A[2][2] * Rm[2][1],
              A[2][0] * Rm[0][2] + A[2][1] * Rm[1][2] + A[2][2] * Rm[2][2],
              A[3][0] * Rm[0][0] + A[3][1] * Rm[1][0] + A[3][2] * Rm[2][0],
              A[3][0] * Rm[0][1] + A[3][1] * Rm[1][1] + A[3][2] * Rm[2][1],
              A[3][0] * Rm[0][2] + A[3][1] * Rm[1][2] + A[3][2] * Rm[2][2]);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Rotation( TYPE AngleSine, TYPE AngleCosine,
                    TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      return
        Rotation(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Rotation( TYPE AngleSine, TYPE AngleCosine,
                    const TVec<TYPE> &Vec ) const
    {
      return Rotation(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Rotation( TYPE AngleInDegree, const TVec<TYPE> &Vec ) const
    {
      return Rotation(AngleInDegree, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Scaling along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Scaling( TYPE Sx, TYPE Sy, TYPE Sz ) const
    {
      return
        TMatr(A[0][0] * Sx, A[0][1] * Sy, A[0][2] * Sz, 
              A[1][0] * Sx, A[1][1] * Sy, A[1][2] * Sz, 
              A[2][0] * Sx, A[2][1] * Sy, A[2][2] * Sz,
              A[3][0] * Sx, A[3][1] * Sy, A[3][2] * Sz);
    } /* End of 'Scaling' function */

    /* Scaling along axes matrix function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Scaling( const TVec<TYPE> &ScaleVec ) const
    {
      return Scaling(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scaling' function */

    /* Transformation matrix by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr Transformation( const TTrans<TYPE> &Trans ) const
    {
      return *this * Trans.A;
    } /* End of 'Transformation' function */

    /* Inverse transformation matrix by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TMatr) new matrix (transformed) object.
     */
    TMatr InvTransformation( const TTrans<TYPE> &Trans )
    {
      return Trans.InvM * *this;
    } /* End of 'InvTransformation' function */

    /* Transpose 3x3 part of matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TMatr &) self-reference.
     */
    TMatr & Transpose3x3( VOID )
    {
      TYPE m[4][4];
      memcpy(m, &A, sizeof(TYPE) * 16);
      A[0][1] = m[1][0];
      A[0][2] = m[2][0];
      
      A[1][0] = m[0][1];
      A[1][2] = m[2][1];
      
      A[2][0] = m[0][2];
      A[2][1] = m[1][2];
      return *this;
    } /* End of 'Transpose3x3' function */

    /* Transpose 4x4 part of matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TMatr &) self-reference.
     */
    TMatr & Transpose4x4( VOID )
    {
      TYPE Tmp;

      for (INT i = 0; i < 2; i++)
        for (INT j = i; j < 4; j++)
          COM_SWAP(A[i][j], A[j][i], Tmp);
      COM_SWAP(A[3][2], A[2][3], Tmp);    
      return *this;
    } /* End of 'Transpose4x4' function */

    /* Obtain perspective projection matrix function.
     * ARGUMENTS:
     *   - 3D frustum bound coordinates:
     *       TYPE Left, Right, Bottom, Top, Near, Far;
     * RETURNS:
     *   (TMatr &) self-reference.
     */
    TMatr & Frustum( TYPE Left,   TYPE Right,
                     TYPE Bottom, TYPE Top,
                     TYPE Near,   TYPE Far )
    {
      A[0][0] = 2 * Near / (Right - Left);
      A[0][1] = 0;
      A[0][2] = 0;
      A[0][3] = 0;
      A[1][0] = 0;
      A[1][1] = 2 * Near / (Top - Bottom);
      A[1][2] = 0;
      A[1][3] = 0;
      A[2][0] = (Right + Left) / (Right - Left);
      A[2][1] = (Top + Bottom) / (Top - Bottom);
      A[2][2] = -(Far + Near) / (Far - Near);
      A[2][3] = -1;
      A[3][0] = 0;
      A[3][1] = 0;
      A[3][2] = -2 * Near * Far / (Far - Near);
      A[3][3] = 0;
      return *this;
    } /* End of 'Frustum' function */

    /* Obtain view matrix (by location, look-at and up vectors) function.
     * ARGUMENTS:
     *   - view camera location:
     *       const TVec<TYPE> &Loc;
     *   - look-at point:
     *       const TVec<TYPE> &LookAt;
     *   - approximate up direction:
     *       const TVec<TYPE> &Up1;
     * RETURNS:
     *   (TMatr &) self-reference.
     */
    TMatr & LookAt( const TVec<TYPE> &Loc, const TVec<TYPE> &LookAt, const TVec<TYPE> &Up1 )
    {
      TVec<TYPE>
        Dir = (LookAt - Loc).Normalizing(),
        Right = (Dir % Up1).Normalizing(),
        Up = Right % Dir;

      A[0][0] = Right.X;
      A[0][1] = Up.X;
      A[0][2] = -Dir.X;
      A[0][3] = 0;
      A[1][0] = Right.Y;
      A[1][1] = Up.Y;
      A[1][2] = -Dir.Y;
      A[1][3] = 0;
      A[2][0] = Right.Z;
      A[2][1] = Up.Z;
      A[2][2] = -Dir.Z;
      A[2][3] = 0;
      A[3][0] = -(Right & Loc);
      A[3][1] = -(Up & Loc);
      A[3][2] = Dir & Loc;
      A[3][3] = 1;
      return *this;
    } /* End of 'LookAt' function */

    /* Cast matrix to first element pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type *) pointer to first row first column element.
     */
    operator TYPE *( VOID )
    {
      return A[0];
    } /* End of 'operator TYPE *' function */
  }; /* End of 'TMatr' class */

  /* Static class unit (identity) matrix */
  template<class TYPE> const TYPE TMatr<TYPE>::UnitMatrix[4][4] =
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
} /* End of 'tsg' namespace */

#endif /* _TSGMATRX_H_ */

/* END OF 'TSGMATRX.H' FILE */
