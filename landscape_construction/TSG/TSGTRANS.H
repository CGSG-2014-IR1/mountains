/***************************************************************
 * Copyright (C) 2011
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGTRANS.H
 * PURPOSE     : Tough Space Graphics library.
 *               Transformation class template declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006-2011.
 *               Vitaly A. Galinsky,
 *               Artemy Sergeev (assembly trigonometry inline).
 * LAST UPDATE : 05.04.2011 (from 13.08.2006, 21.05.2006)
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

#ifndef _TSGTRANS_H_
#define _TSGTRANS_H_

#include <string.h>

#include "tsgdef.h"

namespace tsg
{
  /* Base matrix class template declaration */
  template<class TYPE> class TTrans
  {
  public:

    /* Matrix and inverse matrix */
    TMatr<TYPE> M, InvM;

    /* Default constructor.
     * ARGUMENTS: None.
     */
    TTrans( VOID )
    {
    } /* End of 'TTrans' constructor */

    /* Identify constructor.
     * ARGUMENTS:
     *   - flag of identification (to do or not to do):
     *       BOOL Identify.
     */
    TTrans( BOOL Identify )
    {
      if (Identify)
      {
        M.SetUnit();
        InvM.SetUnit();
      }
    } /* End of 'TTrans' constructor */

    /* Transform by matrix constructor.
     * ARGUMENTS:
     *   - transformation matrix:
     *       const TMatr<TYPE> &Matr;
     */
    TTrans( const TMatr<TYPE> &Matr )
    {
      M = Matr;
      InvM = Matr.Inversing();
    } /* End of 'TTrans' constructor */

    /* Transform by both matrix constructor.
     * ARGUMENTS:
     *   - transformation matrix:
     *       const TMatr<TYPE> &Matr;
     *   - inverse transformation matrix:
     *       const TMatr<TYPE> &InvMatr;
     */
    TTrans( const TMatr<TYPE> &Matr, const TMatr<TYPE> &InvMatr )
    {
      M = Matr;
      InvM = InvMatr;
    } /* End of 'TTrans' constructor */

    /* Copying constructor.
     * ARGUMENTS:
     *   - transformation to copied:
     *       const TTrans &Trans;
     */
    TTrans( const TTrans &Trans )
    {
      memcpy(this, &Trans, sizeof(TTrans));
    } /* End of 'TTrans' constructor */

    /***
     * Transformation base object functions
     ***/

    /* Transform 3D point function.
     * ARGUMENT:
     *   - point (vector) to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed point.
     */
    TVec<TYPE> TransformPoint( const TVec<TYPE> &Vec ) const
    {
      return Vec.Transformation(*this);
    } /* End of 'TransformPoint' constructor */

    /* Transform 3D vector function.
     * ARGUMENT:
     *   - vector to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed vector.
     */
    TVec<TYPE> TransformVector( const TVec<TYPE> &Vec ) const
    {
      return
         TVec<TYPE>(Vec.X * M.A[0][0] + Vec.Y * M.A[1][0] + Vec.Z * M.A[2][0],
                    Vec.X * M.A[0][1] + Vec.Y * M.A[1][1] + Vec.Z * M.A[2][1],
                    Vec.X * M.A[0][2] + Vec.Y * M.A[1][2] + Vec.Z * M.A[2][2]);
    } /* End of 'TransformVector' constructor */

    /* Transform 3D normal (surface perpendicular) function.
     * ARGUMENT:
     *   - vector to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed vector.
     */
    TVec<TYPE> TransformNormal( const TVec<TYPE> &Vec ) const
    {
      return TVec<TYPE>(Vec.X * InvM.A[0][0] + Vec.Y * InvM.A[0][1] +
                          Vec.Z * InvM.A[0][2],
                        Vec.X * InvM.A[1][0] + Vec.Y * InvM.A[1][1] +
                          Vec.Z * InvM.A[1][2],
                        Vec.X * InvM.A[2][0] + Vec.Y * InvM.A[2][1] +
                          Vec.Z * InvM.A[2][2]).Normalize();
    } /* End of 'TransformNormal' constructor */

    /* Inverse transform 3D point function.
     * ARGUMENT:
     *   - point (vector) to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed point.
     */
    TVec<TYPE> InvTransformPoint( const TVec<TYPE> &Vec ) const
    {
      return Vec.InvTransformation(*this);
    } /* End of 'InvTransformPoint' constructor */

    /* Inverse transform 3D vector function.
     * ARGUMENT:
     *   - vector to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed vector.
     */
    TVec<TYPE> InvTransformVector( const TVec<TYPE> &Vec ) const
    {
      return
         TVec<TYPE>(Vec.X * InvM.A[0][0] + Vec.Y * InvM.A[1][0] +
                      Vec.Z * InvM.A[2][0],
                    Vec.X * InvM.A[0][1] + Vec.Y * InvM.A[1][1] +
                      Vec.Z * InvM.A[2][1],
                    Vec.X * InvM.A[0][2] + Vec.Y * InvM.A[1][2] +
                      Vec.Z * InvM.A[2][2]);
    } /* End of 'InvTransformVector' constructor */

    /* Inverse transform 3D normal (surface perpendicular) function.
     * ARGUMENT:
     *   - vector to be transformed:
     *       TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) result transformed vector.
     */
    TVec<TYPE> InvTransformNormal( const TVec<TYPE> &Vec ) const
    {
      return TVec<TYPE>(Vec.X * M.A[0][0] + Vec.Y * M.A[0][1] +
                          Vec.Z * M.A[0][2],
                        Vec.X * M.A[1][0] + Vec.Y * M.A[1][1] +
                          Vec.Z * M.A[1][2],
                        Vec.X * M.A[2][0] + Vec.Y * M.A[2][1] +
                          Vec.Z * M.A[2][2]).Normalize();
    } /* End of 'InvTransformNormal' constructor */

    /***
     * Set transform to specified transformation functions
     ***/

    /* Reset transformation transform data function.
     * ARGUMENTS: None.
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetUnit( VOID )
    {
      M.SetUnit();
      InvM.SetUnit();
      return *this;
    } /* End of 'SetUnit' function */

    /* Set translation transform function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetTranslate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      M.SetTranslate(Dx, Dy, Dz);
      InvM.SetTranslate(-Dx, -Dy, -Dz);
      return *this;
    } /* End of 'SetTranslate' function */

    /* Set translation transform function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetTranslate( const TVec<TYPE> &Shift )
    {
      return SetTranslate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'SetTranslate' function */

    /* Set rotation around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      M.SetRotateX(AngleSine, AngleCosine);
      InvM.SetRotateX(-AngleSine, AngleCosine);
      return *this;
    } /* End of 'SetRotateX' function */

    /* Set rotation around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateX( TYPE AngleInDegree )
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

      return SetRotateX(SinVal, CosVal);
    } /* End of 'SetRotateX' function */

    /* Set rotation around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      M.SetRotateY(AngleSine, AngleCosine);
      InvM.SetRotateY(-AngleSine, AngleCosine);
      return *this;
    } /* End of 'SetRotateY' function */

    /* Set rotation around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateY( TYPE AngleInDegree )
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

      return SetRotateY(SinVal, CosVal);
    } /* End of 'SetRotateY' function */

    /* Set rotation around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      M.SetRotateZ(AngleSine, AngleCosine);
      InvM.SetRotateZ(-AngleSine, AngleCosine);
      return *this;
    } /* End of 'SetRotateZ' function */

    /* Set rotation around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotateZ( TYPE AngleInDegree )
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

      return SetRotateZ(SinVal, CosVal);
    } /* End of 'SetRotateZ' function */

    /* Set rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotate( TYPE AngleInDegree,
                        TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      M.SetRotate(AngleInDegree, AxisX, AxisY, AxisZ);
      InvM.A[0][0] = M.A[0][0];
      InvM.A[0][1] = M.A[1][0];
      InvM.A[0][2] = M.A[2][0];
      InvM.A[0][3] = 0;
      InvM.A[1][0] = M.A[0][1];
      InvM.A[1][1] = M.A[1][1];
      InvM.A[1][2] = M.A[2][1];
      InvM.A[1][3] = 0;
      InvM.A[2][0] = M.A[0][2];
      InvM.A[2][1] = M.A[1][2];
      InvM.A[2][2] = M.A[2][2];
      InvM.A[2][3] = 0;
      InvM.A[3][0] = 0;
      InvM.A[3][1] = 0;
      InvM.A[3][2] = 0;
      InvM.A[3][3] = 1;
      return *this;
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotate( TYPE AngleSine, TYPE AngleCosine,
                        TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return
        SetRotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotate( TYPE AngleSine, TYPE AngleCosine,
                        const TVec<TYPE> &Vec )
    {
      return SetRotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'SetRotate' function */

    /* Set rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetRotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
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

      return SetRotate(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'SetRotate' function */

    /* Set scaling along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetScale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      M.SetScale(Sx, Sy, Sz);
      InvM.SetScale(1 / Sx, 1 / Sy, 1 / Sz);
      return *this;
    } /* End of 'SetScale' function */

    /* Set scaling along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & SetScale( const TVec<TYPE> &ScaleVec )
    {
      return SetScale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'SetScale' function */

    /***
     * Apply specified transformation to transform (self-transform) functions
     ***/

    /* Translate transform function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Translate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      M.Translate(Dx, Dy, Dz);

      InvM.A[3][0] -= Dx * InvM.A[0][0] + Dy * InvM.A[1][0] + Dz * InvM.A[2][0];
      InvM.A[3][1] -= Dx * InvM.A[0][1] + Dy * InvM.A[1][1] + Dz * InvM.A[2][1];
      InvM.A[3][2] -= Dx * InvM.A[0][2] + Dy * InvM.A[1][2] + Dz * InvM.A[2][2];
      return *this;
    } /* End of 'Translate' function */

    /* Translate transform function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Translate( const TVec<TYPE> &Shift )
    {
      return Translate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translate' function */

    /* Rotate around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE a, b, c;

      M.RotateX(AngleSine, AngleCosine);

      /* Pre- concatenating new inverse matrix before old one */
      a = AngleCosine * InvM.A[1][0] - AngleSine * InvM.A[2][0];
      b = AngleCosine * InvM.A[1][1] - AngleSine * InvM.A[2][1];
      c = AngleCosine * InvM.A[1][2] - AngleSine * InvM.A[2][2];

      InvM.A[2][0] = AngleCosine * InvM.A[2][0] + AngleSine * InvM.A[1][0];
      InvM.A[2][1] = AngleCosine * InvM.A[2][1] + AngleSine * InvM.A[1][1];
      InvM.A[2][2] = AngleCosine * InvM.A[2][2] + AngleSine * InvM.A[1][2];

      InvM.A[1][0] = a;
      InvM.A[1][1] = b;
      InvM.A[1][2] = c;

      return *this;
    } /* End of 'RotateX' function */

    /* Rotate around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateX( TYPE AngleInDegree )
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

    /* Rotate around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE a, b, c;

      M.RotateY(AngleSine, AngleCosine);

      /* Pre- concatenating new inverse matrix before old one */
      a = AngleCosine * InvM.A[0][0] + AngleSine * InvM.A[2][0];
      b = AngleCosine * InvM.A[0][1] + AngleSine * InvM.A[2][1];
      c = AngleCosine * InvM.A[0][2] + AngleSine * InvM.A[2][2];

      InvM.A[2][0] = AngleCosine * InvM.A[2][0] - AngleSine * InvM.A[0][0];
      InvM.A[2][1] = AngleCosine * InvM.A[2][1] - AngleSine * InvM.A[0][1];
      InvM.A[2][2] = AngleCosine * InvM.A[2][2] - AngleSine * InvM.A[0][2];

      InvM.A[0][0] = a;
      InvM.A[0][1] = b;
      InvM.A[0][2] = c;

      return *this;
    } /* End of 'RotateY' function */

    /* Rotate around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateY( TYPE AngleInDegree )
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

    /* Rotate around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      TYPE a, b, c;

      M.RotateZ(AngleSine, AngleCosine);

      /* Pre- concatenating new inverse matrix before old one */
      a = AngleCosine * InvM.A[0][0] - AngleSine * InvM.A[1][0];
      b = AngleCosine * InvM.A[0][1] - AngleSine * InvM.A[1][1];
      c = AngleCosine * InvM.A[0][2] - AngleSine * InvM.A[1][2];

      InvM.A[1][0] = AngleCosine * InvM.A[1][0] + AngleSine * InvM.A[0][0];
      InvM.A[1][1] = AngleCosine * InvM.A[1][1] + AngleSine * InvM.A[0][1];
      InvM.A[1][2] = AngleCosine * InvM.A[1][2] + AngleSine * InvM.A[0][2];

      InvM.A[0][0] = a;
      InvM.A[0][1] = b;
      InvM.A[0][2] = c;

      return *this;
    } /* End of 'RotateZ' function */

    /* Rotate around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & RotateZ( TYPE AngleInDegree )
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

    /* Rotate around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Rotate( TYPE AngleInDegree,
                     TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      TYPE Rm[3][3], Tm[4][4];

      BuildRotateMatrix3x3<TYPE, 3>(Rm, AngleInDegree, AxisX, AxisY, AxisZ);

      Tm[0][0] = M.A[0][0] * Rm[0][0] + M.A[0][1] * Rm[1][0] +
        M.A[0][2] * Rm[2][0];
      Tm[1][0] = M.A[1][0] * Rm[0][0] + M.A[1][1] * Rm[1][0] +
        M.A[1][2] * Rm[2][0];
      Tm[2][0] = M.A[2][0] * Rm[0][0] + M.A[2][1] * Rm[1][0] +
        M.A[2][2] * Rm[2][0];
      Tm[3][0] = M.A[3][0] * Rm[0][0] + M.A[3][1] * Rm[1][0] +
        M.A[3][2] * Rm[2][0];

      Tm[0][1] = M.A[0][0] * Rm[0][1] + M.A[0][1] * Rm[1][1] +
        M.A[0][2] * Rm[2][1];
      Tm[1][1] = M.A[1][0] * Rm[0][1] + M.A[1][1] * Rm[1][1] +
        M.A[1][2] * Rm[2][1];
      Tm[2][1] = M.A[2][0] * Rm[0][1] + M.A[2][1] * Rm[1][1] +
        M.A[2][2] * Rm[2][1];
      Tm[3][1] = M.A[3][0] * Rm[0][1] + M.A[3][1] * Rm[1][1] +
        M.A[3][2] * Rm[2][1];

      Tm[0][2] = M.A[0][0] * Rm[0][2] + M.A[0][1] * Rm[1][2] +
        M.A[0][2] * Rm[2][2];
      Tm[1][2] = M.A[1][0] * Rm[0][2] + M.A[1][1] * Rm[1][2] +
        M.A[1][2] * Rm[2][2];
      Tm[2][2] = M.A[2][0] * Rm[0][2] + M.A[2][1] * Rm[1][2] +
        M.A[2][2] * Rm[2][2];
      Tm[3][2] = M.A[3][0] * Rm[0][2] + M.A[3][1] * Rm[1][2] +
        M.A[3][2] * Rm[2][2];

      Tm[0][3] = 0;
      Tm[1][3] = 0;
      Tm[2][3] = 0;
      Tm[3][3] = 1;

      memcpy(M.A, Tm, sizeof(M));

      Tm[0][0] = Rm[0][0] * InvM.A[0][0] + Rm[0][1] * InvM.A[1][0] +
        Rm[0][2] * InvM.A[2][0];
      Tm[0][1] = Rm[0][0] * InvM.A[0][1] + Rm[0][1] * InvM.A[1][1] +
        Rm[0][2] * InvM.A[2][1];
      Tm[0][2] = Rm[0][0] * InvM.A[0][2] + Rm[0][1] * InvM.A[1][2] +
        Rm[0][2] * InvM.A[2][2];

      Tm[1][0] = Rm[1][0] * InvM.A[0][0] + Rm[1][1] * InvM.A[1][0] +
        Rm[1][2] * InvM.A[2][0];
      Tm[1][1] = Rm[1][0] * InvM.A[0][1] + Rm[1][1] * InvM.A[1][1] +
        Rm[1][2] * InvM.A[2][1];
      Tm[1][2] = Rm[1][0] * InvM.A[0][2] + Rm[1][1] * InvM.A[1][2] +
        Rm[1][2] * InvM.A[2][2];

      Tm[2][0] = Rm[2][0] * InvM.A[0][0] + Rm[2][1] * InvM.A[1][0] +
        Rm[2][2] * InvM.A[2][0];
      Tm[2][1] = Rm[2][0] * InvM.A[0][1] + Rm[2][1] * InvM.A[1][1] +
        Rm[2][2] * InvM.A[2][1];
      Tm[2][2] = Rm[2][0] * InvM.A[0][2] + Rm[2][1] * InvM.A[1][2] +
        Rm[2][2] * InvM.A[2][2];

      InvM.A[0][0] = Tm[0][0];
      InvM.A[0][1] = Tm[0][1];
      InvM.A[0][2] = Tm[0][2];

      InvM.A[1][0] = Tm[1][0];
      InvM.A[1][1] = Tm[1][1];
      InvM.A[1][2] = Tm[1][2];

      InvM.A[2][0] = Tm[2][0];
      InvM.A[2][1] = Tm[2][1];
      InvM.A[2][2] = Tm[2][2];

      return *this;
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Rotate( TYPE AngleSine, TYPE AngleCosine,
                     TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return
        Rotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Rotate( TYPE AngleSine, TYPE AngleCosine,
                     const TVec<TYPE> &Vec )
    {
      return Rotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Rotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
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

    /* Scale along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Scale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      M.Scale(Sx, Sy, Sz);
      
      InvM.A[0][0] /= Sx;
      InvM.A[0][1] /= Sx;
      InvM.A[0][2] /= Sx;

      InvM.A[1][0] /= Sy;
      InvM.A[1][1] /= Sy;
      InvM.A[1][2] /= Sy;

      InvM.A[2][0] /= Sz;
      InvM.A[2][1] /= Sz;
      InvM.A[2][2] /= Sz;

      return *this;
    } /* End of 'Scale' function */

    /* Scale along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Scale( const TVec<TYPE> &ScaleVec )
    {
      return Scale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scale' function */

    /* Transform transform by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & Transform( const TTrans<TYPE> &Trans )
    {
      M.Transform(Trans);
      InvM.InvTransform(Trans);
      return *this;
    } /* End of 'Transform' function */

    /* Inverse transform transform by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TTrans &) self-pointer to transform.
     */
    TTrans & InvTransform( const TTrans<TYPE> &Trans )
    {
      M.InvTransform(Trans);
      InvM.Transform(Trans);
      return *this;
    } /* End of 'InvTransform' function */

    /***
     * Apply specified transformation to transform functions
     ***/

    /* Translation transform function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Translation( TYPE Dx, TYPE Dy, TYPE Dz ) const
    {
      TTrans res(*this);

      return res.Translate(Dx, Dy, Dz);
    } /* End of 'Translation' function */

    /* Translation transform function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Translation( const TVec<TYPE> &Shift ) const
    {
      return Translation(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translation' function */

    /* Rotation around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationX( TYPE AngleSine, TYPE AngleCosine ) const
    {
      TTrans res(*this);

      return res.RotateX(AngleSine, AngleCosine);
    } /* End of 'RotationX' function */

    /* Rotation around 'X' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationX( TYPE AngleInDegree ) const
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

    /* Rotation around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationY( TYPE AngleSine, TYPE AngleCosine ) const
    {
      TTrans res(*this);

      return res.RotateY(AngleSine, AngleCosine);
    } /* End of 'RotationY' function */

    /* Rotation around 'Y' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationY( TYPE AngleInDegree ) const
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

    /* Rotation around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationZ( TYPE AngleSine, TYPE AngleCosine ) const
    {
      TTrans res(*this);

      return res.RotateZ(AngleSine, AngleCosine);
    } /* End of 'RotationZ' function */

    /* Rotation around 'Z' axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans RotationZ( TYPE AngleInDegree ) const
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

    /* Rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Rotation( TYPE AngleInDegree,
                     TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      TTrans res(*this);

      return res.Rotate(AngleInDegree, AxisX, AxisY, AxisZ);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Rotation( TYPE AngleSine, TYPE AngleCosine,
                     TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      return
        Rotation(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Rotation( TYPE AngleSine, TYPE AngleCosine, const TVec<TYPE> &Vec ) const
    {
      return Rotation(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis transform function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Rotation( TYPE AngleInDegree, const TVec<TYPE> &Vec ) const
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

      return Rotation(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Scaling along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Scaling( TYPE Sx, TYPE Sy, TYPE Sz ) const
    {
      TTrans res(*this);

      return res.Scale(Sx, Sy, Sz);
    } /* End of 'Scaling' function */

    /* Scaling along axes transform function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Scaling( const TVec<TYPE> &ScaleVec ) const
    {
      return Scaling(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scaling' function */

    /* Transformation transform by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans Transformation( const TTrans<TYPE> &Trans ) const
    {
      TTrans res(*this);

      return res.Transform(Trans);
    } /* End of 'Transformation' function */

    /* Inverse transformation transform by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TTrans) new transform (transformed) object.
     */
    TTrans InvTransformation( const TTrans<TYPE> &Trans ) const
    {
      TTrans res(*this);

      return res.InvTransform(Trans);
    } /* End of 'InvTransformation' function */

    /* Multiplication of two transformations function.
     * ARGUMENTS:
     *   - transformation to multiply:
     *       const TTrans &Trans;
     * RETURNS: 
     *   (TTrans) result of multiplication.
     */
    TTrans operator*( const TTrans &Trans ) const
    {
      return Transformation(Trans);
    } /* End of 'operator*' function */

    /* Multiplication of two transformations function.
     * ARGUMENTS:
     *   - transformation to multiply:
     *       const TTrans &Trans;
     * RETURNS: 
     *   (TTrans &) self-reference to transformation.
     */
    TTrans & operator*=( const TTrans &Trans )
    {
      return Transform(Trans);
    } /* End of 'operator*=' function */

    /* Vector transformation function.
     * ARGUMENTS:
     *   - vector to be multiplied:
     *       const TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) the tranformated vector.
     */
    TVec<TYPE> TransformationVec( const TVec<TYPE> &Vec ) const
    {
      return TVec<TYPE>(Vec.X * M.A[0][0] + Vec.Y * M.A[1][0] +
                          Vec.Z * M.A[2][0] + M.A[3][0],
                        Vec.X * M.A[0][1] + Vec.Y * M.A[1][1] + 
                          Vec.Z * M.A[2][1] + M.A[3][1],
                        Vec.X * M.A[0][2] + Vec.Y * M.A[1][2] + 
                          Vec.Z * M.A[2][2] + M.A[3][2]);
    } /* End of 'TransformationVec' function */

    /* Point transformation function.
     * ARGUMENTS:
     *   - point to be multiplied:
     *       const TVec<TYPE> &Vec;
     * RETURNS:
     *   (TVec<TYPE>) the tranformated point.
     */
    TVec<TYPE> TransformationPnt( const TVec<TYPE> &Vec ) const
    {
      TYPE w = Vec.X * M.A[0][3] + Vec.Y * M.A[1][3] + Vec.Z * M.A[2][3] + M.A[3][3];

      return TVec<TYPE>((Vec.X * M.A[0][0] + Vec.Y * M.A[1][0] +
                          Vec.Z * M.A[2][0] + M.A[3][0]) / w,
                        (Vec.X * M.A[0][1] + Vec.Y * M.A[1][1] + 
                          Vec.Z * M.A[2][1] + M.A[3][1]) / w,
                        (Vec.X * M.A[0][2] + Vec.Y * M.A[1][2] + 
                          Vec.Z * M.A[2][2] + M.A[3][2]) / w);
    } /* End of 'TransformationPnt' function */
  }; /* End of 'TTrans' class */
} /* End of 'tsg' namespace */

#endif /* _TSGTRANS_H_ */

/* END OF 'TSGTRANS.H' FILE */
