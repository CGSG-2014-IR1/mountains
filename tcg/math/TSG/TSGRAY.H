/***************************************************************
 * Copyright (C) 2006
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGRAY.H
 * PURPOSE     : Tough Space Graphics library.
 *               Main declaration module.
 * PROGRAMMER  : CGSG'2004-2005-2006.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 13.08.2006
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

#ifndef _TSGRAY_H_
#define _TSGRAY_H_

#include "tsgdef.h"

namespace tsg
{
  /* Ray type basic template class */
  template<class TYPE> class TRay
  { 
  public:
    TVec<TYPE> Org, Dir; /* Ray origin and direction */

    /* Default constructor.
     * ARGUMENTS: None.
     */
    TRay( VOID )
    {
    } /* End of 'TRay' constructor */

    /* Constructor by components.
     * ARGUMENTS:
     *   - values of components:
     *       const TVec<TYPE> &NewOrg, &NewDir;
     */
    TRay( const TVec<TYPE> &NewOrg, const TVec<TYPE> &NewDir ) : Org(NewOrg), Dir(NewDir)
    {
    } /* End of 'TRay' constructor */

    /* Evaluation ray direction length function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) ray direction length.
     */
    TYPE operator!( VOID ) const
    {
      TYPE len = Dir & Dir;

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
   
    /* Evaluation ray direction squared length function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TYPE) ray direction squared length.
     */
    TYPE GetSquaredLength( VOID ) const
    {
      return Dir & Dir;
    } /* End of 'GetSquaredLength' function */

    /* Ray point obtain (by distance) function.
     * ARGUMENTS:
     *   - ray distance:
     *       DBL Distance;
     * RETURNS: 
     *   (TVec<TYPE>) result of dot product.
     */
    TVec<TYPE> operator()( TYPE Distance ) const
    {
      return Org + Dir * Distance;
    } /* End of 'operator()' function */

    /* Comparing of two rays function. 
     * ARGUMENTS:
     *   - ray to compare:
     *       const TRay &R;
     * RETURNS: 
     *   (BOOL) result of comparing.
     */       
    BOOL operator==( const TRay &R ) const
    {
      return Org == R.Org && Dir == R.Dir;
    } /* End of 'operator==' function */

    /* Comparing of two rays function. 
     * ARGUMENTS:
     *   - ray to compare:
     *       const TRay &R;
     * RETURNS: 
     *   (BOOL) result of comparing.
     */       
    BOOL operator!=( const TRay &R ) const
    {
      return Org != R.Org || Dir != R.Dir;
    } /* End of 'operator!=' function */

    /* Inverse ray function.
     * ARGUMENTS: None.             
     * RETURNS:              
     *   (TRay) result of inverse.
     */
    TRay operator-( VOID ) const
    {
      return TRay(-Org, -Dir);
    } /* End of 'operator-' function */

    /* Negate ray (itself) function. 
     * ARGUMENTS: None.             
     * RETURNS: 
     *   (TRay &) self-reference to ray.
     */
    TRay & Negate( VOID )
    {
      Org = -Org;
      Dir = -Dir;

      return *this;
    } /* End of 'Negate' function */

    /* Normalize ray function. 
     * ARGUMENTS: None.
     * RETURNS: 
     *   (TRay &) self-reference to ray.
     */
    TRay & Normalize( VOID )
    {
      Dir.Normalize();
      return *this;
    } /* End of 'Normalize' function */

    /* Normalize ray function. 
     * ARGUMENTS: None.
     * RETURNS:
     *   (TRay) normalized vector.
     */
    TRay Normalizing( VOID ) const
    {
      return TRay(Org, Dir.Normalizing());
    } /* End of 'Normalizing' function */

    /*** Ray transformation functions ***/

    /***
     * Apply specified transformation to ray (self-transform) functions
     ***/

    /* Translate ray function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Translate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      Org.Translate(Dx, Dy, Dz);
      return *this;
    } /* End of 'Translate' function */

    /* Translate ray function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Translate( const TVec<TYPE> &Shift )
    {
      return Translate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translate' function */

    /* Rotate around 'X' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateX( TYPE AngleSine, TYPE AngleCosine )
    {
      Org.RotateX(AngleSine, AngleCosine);
      Dir.RotateX(AngleSine, AngleCosine);

      return *this;
    } /* End of 'RotateX' function */

    /* Rotate around 'X' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateX( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotateX(SinVal, CosVal);
    } /* End of 'RotateX' function */

    /* Rotate around 'Y' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateY( TYPE AngleSine, TYPE AngleCosine )
    {
      Org.RotateY(AngleSine, AngleCosine);
      Dir.RotateY(AngleSine, AngleCosine);

      return *this;
    } /* End of 'RotateY' function */

    /* Rotate around 'Y' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateY( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotateY(SinVal, CosVal);
    } /* End of 'RotateY' function */

    /* Rotate around 'Z' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateZ( TYPE AngleSine, TYPE AngleCosine )
    {
      Org.RotateZ(AngleSine, AngleCosine);
      Dir.RotateZ(AngleSine, AngleCosine);

      return *this;
    } /* End of 'RotateZ' function */

    /* Rotate around 'Z' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & RotateZ( TYPE AngleInDegree )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotateZ(SinVal, CosVal);
    } /* End of 'RotateZ' function */

    /* Rotate around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Rotate( TYPE AngleSine, TYPE AngleCosine,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      return Rotate(Rad2Deg(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Rotate( TYPE AngleInDegree,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ )
    {
      Org.Rotate(AngleSine, AngleInDegree, AxisX, AxisY, AxisZ);
      Dir.Rotate(AngleSine, AngleInDegree, AxisX, AxisY, AxisZ);

      return *this;
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Rotate( TYPE AngleSine, TYPE AngleCosine,
               const TVec<TYPE> &Vec )
    {
      return Rotate(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Rotate around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Rotate( TYPE AngleInDegree, const TVec<TYPE> &Vec )
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return Rotate(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotate' function */

    /* Scale along axes ray function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Scale( TYPE Sx, TYPE Sy, TYPE Sz )
    {
      Org.Scale(Sx, Sy, Sz);
      Dir.Scale(Sx, Sy, Sz);

      return *this;
    } /* End of 'Scale' function */

    /* Scale along axes ray function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Scale( const TVec<TYPE> &ScaleVec )
    {
      return Scale(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scale' function */

    /* Transform ray by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & Transform( const TTrans<TYPE> &Trans )
    {
      Trans.TransformPoint(Org);
      Trans.TransformVector(Dir);

      return *this;
    } /* End of 'Transform' function */

    /* Inverse transform vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TRay &) self-reference to ray.
     */
    TRay & InvTransform( const TTrans<TYPE> &Trans )
    {
      Trans.InvTransformPoint(Org);
      Trans.InvTransformVector(Dir);

      return *this;
    } /* End of 'InvTransform' function */

    /***
     * Apply specified transformation to ray functions
     ***/

    /* Translation ray function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       TYPE Dx, Dy, Dz;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Translation( TYPE Dx, TYPE Dy, TYPE Dz ) const
    {
      return TRay(Org.Translation(Dx, Dy, Dz), Dir);
    } /* End of 'Translation' function */

    /* Translation ray function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const TVec<TYPE> &Shift;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Translation( const TVec<TYPE> &Shift ) const
    {
      return Translation(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'Translation' function */

    /* Rotation around 'X' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationX( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TRay(Org.RotationX(AngleSine, AngleCosine),
                  Dir.RotationX(AngleSine, AngleCosine));
    } /* End of 'RotationX' function */

    /* Rotation around 'X' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationX( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationX(SinVal, CosVal);
    } /* End of 'RotationX' function */

    /* Rotation around 'Y' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationY( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TRay(Org.RotationY(AngleSine, AngleCosine),
                  Dir.RotationY(AngleSine, AngleCosine));
    } /* End of 'RotationY' function */

    /* Rotation around 'Y' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationY( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationY(SinVal, CosVal);
    } /* End of 'RotationY' function */

    /* Rotation around 'Z' axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationZ( TYPE AngleSine, TYPE AngleCosine ) const
    {
      return TRay(Org.RotationZ(AngleSine, AngleCosine),
                  Dir.RotationZ(AngleSine, AngleCosine));
    } /* End of 'RotationZ' function */

    /* Rotation around 'Z' axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay RotationZ( TYPE AngleInDegree ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationZ(SinVal, CosVal);
    } /* End of 'RotationZ' function */

    /* Rotation around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */              
    TRay Rotation( TYPE AngleSine, TYPE AngleCosine,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      return Rotation(Rad2Deg(atan2(AngleSine, AngleCosine)), X, Y, Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector components:
     *       TYPE AxisX, AxisY, AxisZ;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Rotation( TYPE AngleInDegree,
                   TYPE AxisX, TYPE AxisY, TYPE AxisZ ) const
    {
      return TRay(Org.Rotation(AngleInDegree, AxisX, AxisY, AxisZ),
                  Dir.Rotation(AngleInDegree, AxisX, AxisY, AxisZ));
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle sine and cosine function values:
     *       TYPE AngleSine, AngleCosine;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Rotation( TYPE AngleSine, TYPE AngleCosine,
                   const TVec<TYPE> &Vec ) const
    {
      return Rotation(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis ray function.
     * ARGUMENTS:
     *   - rotation angle (in degrees):
     *       TYPE AngleInDegree;
     *   - rotation vector:
     *       const TVec<TYPE> &Vec;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Rotation( TYPE AngleInDegree, const TVec<TYPE> &Vec ) const
    {
      DOUBLE AngleInRadians = Deg2Rad(AngleInDegree);
      TYPE SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return Rotation(SinVal, CosVal, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Scaling along axes ray function.
     * ARGUMENTS:
     *   - scaling axes coefficients:
     *       TYPE Sx, Sy, Sz;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Scaling( TYPE Sx, TYPE Sy, TYPE Sz ) const
    {
      return TRay(Org.Scaling(Sx, Sy, Sz),
                  Dir.Scaling(Sx, Sy, Sz));
    } /* End of 'Scaling' function */

    /* Scaling along axes ray function.
     * ARGUMENTS:
     *   - scaling axes coefficients in vector:
     *       const TVec<TYPE> &ScaleVec;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Scaling( const TVec<TYPE> &ScaleVec ) const
    {
      return Scaling(ScaleVec.X, ScaleVec.Y, ScaleVec.Z);
    } /* End of 'Scaling' function */

    /* Transformation vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay Transformation( const TTrans<TYPE> &Trans ) const
    {
      return TRay(Trans.TransformPoint(Org),
                  Trans.TransformVector(Dir));
    } /* End of 'Transformation' function */

    /* Inverse transformation vector by specified transformation function.
     * ARGUMENTS:
     *   - transformation to be applied:
     *       const TTrans<TYPE> &Trans;
     * RETURN:
     *   (TRay) new ray (transformed) object.
     */
    TRay InvTransformation( const TTrans<TYPE> &Trans ) const
    {
      return TRay(Trans.InvTransformPoint(Org),
                  Trans.InvTransformVector(Dir));
    } /* End of 'InvTransformation' function */
  }; /* End of 'TVec' class */
} /* End of 'tsg' namespace */

#endif /* _TSGRAY_H_ */
