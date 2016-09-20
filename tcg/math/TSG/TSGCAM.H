/***************************************************************
 * Copyright (C) 2006-2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TSGCAM.H
 * PURPOSE     : Tough space graphics sub-library.
 *               Main declaration module for template TCam class.
 * PROGRAMMER  : CGSG'2005-2006-2013-2014-2015.
 *               Maxim Gridnev,
 *               Yaroslav Drugov.
 * LAST UPDATE : 03.11.2015 (from 05.03.2015)
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

#ifndef _TSGCAM_H_
#define _TSGCAM_H_

#include <math.h>

#include "tsgdef.h"

namespace tsg
{
  /* Basic template class of camera */
  template<class TYPE> class TCam
  {
  public:
    /*** Camera parameters ***/
    TVec<TYPE> Loc;      /* Position of camera */
    TVec<TYPE> LookAt;   /* Look at point of camera */
    TVec<TYPE> Dir;      /* Direction of camera */
    TVec<TYPE> Up;       /* Identity vector of camera, which direction is up */
    TVec<TYPE> SaveUp;   /* Identity vector of camera, which direction is up */
    TVec<TYPE> Right;    /* Identity vector of camera, which direction is right */

    /*** Camera project plane parameters ***/
    TYPE ProjDist;         /* Project plane distance */
    TYPE Width;            /* Width of project plane */
    TYPE Height;           /* Height of project plane */
    TYPE SavePPH;          /* Saved width of project plane */
    TYPE SavePPW;          /* Saved height of project plane */
    TYPE FarClip;          /* FarClip distance */
    TYPE Aspect;           /* Ration aspect of project plane */
    INT ScreenWidth;       /* Screen width */
    INT ScreenHeight;      /* Screen height */
    
    /*** Camera matrices ***/
    TTrans<TYPE> Matr;       /* Camera coordinate system translate */
    TTrans<TYPE> Proj;        /* Perspective projection matrix */

    /*** Camera constructors ***/
    
    /* Empty constructor */
    TCam( VOID )
    { 
    } /* End of 'TCam' constructor */
    
    /* Camera constructor
     * ARGUMENTS:
     *   - camera position vector:
     *       TVec<TYPE> Pos;
     *   - camera direction vector or look at point:
     *       TVec<TYPE> At;
     *   - camera up vector:
     *       TVec<TYPE> UpVec;
     *   - Flag(TRUE - At - look at point; FALSE - At - direction):
     *       BOOL IsLookAt;
     *   - project plane width:
     *       TYPE SaveW;
     *   - project plane height:
     *       TYPE SaveH;
     *   - project plane distance:
     *       TYPE ProjD;
     *   - near distance:
     *       TYPE N;
     *   - far distance:
     *       TYPE F;
     *   - size of orthogonal parallelepiped 
     *       TYPE WVolume, HVolume; 
     *   - size of screen:
     *       TYPE ScrW, ScrH;  
     */
    TCam( TVec<TYPE> Pos, TVec<TYPE> At, TVec<TYPE> UpVec, BOOL IsLookAt,
        TYPE SaveW = 1.0, TYPE SaveH = 1.0,
        TYPE ProjD = 1.0, TYPE F = 10000.0,
        TYPE ScrW = 320, TYPE ScrH = 240) :
      Loc(Pos), Up(UpVec), SaveUp(UpVec),
      FarClip(F),
      ScreenWidth(ScrW), ScreenHeight(ScrH)
    {
      SavePPW = Width = SaveW;
      SavePPH = Height = SaveH;

      Dir = At;
      LookAt = At;
      if (IsLookAt)
        Dir = At - Pos;
      else
        LookAt += Loc;
      
      Dir.Normalize();
      Right = Dir % Up;
      Up = Right % Dir;
      Up.Normalize();
      Right.Normalize();

      UpdateMatr();

      ProjDist = ProjD;
      UpdateProjData();
    } /* End of 'TCam' constructor */

    /*** Camera methods ***/

    /***
    * Updations camera methods.
    ***/

    /* Update camera position function.
     * ARGUMENTS:
     *   - position vector:
     *       TVec<TYPE> Pos;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& UpdatePos( TVec<TYPE> Pos )
    {
      Loc = Pos;
      UpdateMatr(); 
                 
      return *this;
    } /* End of 'CameraUpgatePos' function */

    /* Update camera direction by look at point function.
     * ARGUMENTS:
     *   - point to look vector:
     *       TVec<TYPE> At;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& UpgateDir( TVec<TYPE> At )
    {
      LookAt = At;
      UpdateLookAtLocUp();

      return *this;
    } /* End of 'CameraUpgatePos' function */

    /* Update camera direction position up vectors function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& UpdateDirLocUp( VOID )
    {
      Dir.Normalize();
      Right = Dir % Up;
      Right.Normalize();
      Up = Right % Dir;

      UpdateMatr();

      return *this;
    } /* End of 'CameraUpgatePos' function */

    /* Update camera look at point position up vectors function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam & UpdateLookAtLocUp( VOID )
    {
      Dir = LookAt - Loc;
      UpdateDirLocUp();

      return *this;
    } /* End of 'UpdateLookAtLocUp' function */

    /* Update camera matrices function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& UpdateMatr( VOID )
    {
      /* Make view transformation matrix */
      Matr.M = TMatr<TYPE>(Right.X,      Up.X,      Dir.X,
                           Right.Y,      Up.Y,      Dir.Y,
                           Right.Z,      Up.Z,      Dir.Z,
                       -Loc & Right, -Loc & Up, -Loc & Dir);

      /* Make inverse transformation matrix */
      Matr.InvM = TMatr<TYPE>(Right.X, Right.Y, Right.Z,
                                 Up.X,    Up.Y,    Up.Z,
                                Dir.X,   Dir.Y,   Dir.Z,
                                Loc.X,   Loc.Y,   Loc.Z);

      return *this;
    } /* End of 'CameraUpgatePos' function */

    /* Update projection data of camera function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateProjData( VOID )
    {
      TYPE xScale, yScale, Scale;

      /* Rescale project plane size for keep proportional aspect ratio */
      xScale = SavePPW / ScreenWidth;
      yScale = SavePPH / ScreenHeight;
      if (xScale > yScale)
        Scale = xScale;
      else
        Scale = yScale;
      Width = Scale * ScreenWidth;
      Height = Scale * ScreenHeight;

      Aspect = Width / Height;

      /* Evaluate perspective projection matrix */
      Proj =
        TMatr<TYPE>(2.0 * ProjDist / Width, 0,                       0,                                         0,
                    0,                      2.0 * ProjDist / Height, 0,                                         0,
                    0,                      0,                       FarClip / (FarClip - ProjDist),            1,
                    0,                      0,                       FarClip * ProjDist / (ProjDist - FarClip), 0);
    } /* End of 'UpdateProjData' function */

    /* Set project plane parameters function.
     * ARGUMENTS:
     *   - project plane width:
     *       TYPE W;
     *   - project plane height:
     *       TYPE H;
     *   - project plane distance:
     *       TYPE ProjD;
     *   - near distance:
     *       TYPE N;
     *   - far distance:
     *       TYPE F;
     *   - size orthogonal parallelepiped 
     *       TYPE WV, HV; 
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& SetProjParams( TYPE W, TYPE H,
              TYPE ProjD = 1, TYPE F = 10000 )
    {
      SavePPW = W;
      SavePPH = H;
      ProjDist = ProjD;
      FarClip = F;
      UpdateProjData();

      return *this;
    } /* End of 'SetProjParams' function */

    /* Set camera parameters constructor
     * ARGUMENTS:
     *   - camera position vector:
     *       TVec<TYPE> Pos;
     *   - camera direction vector or look at point:
     *       TVec<TYPE> At;
     *   - camera up vector:
     *       TVec<TYPE> UpVec;
     *   - Flag(TRUE - At - look at point; FALSE - At - direction):
     *       BOOL IsLookAt;
     *   - project plane width:
     *       TYPE SaveW;
     *   - project plane height:
     *       TYPE SaveH;
     *   - project plane distance:
     *       TYPE ProjD;
     *   - near distance:
     *       TYPE N;
     *   - far distance:
     *       TYPE F;
     *   - size of orthogonal parallelepiped 
     *       TYPE WVolume, HVolume; 
     *   - size of screen:
     *       TYPE ScrW, ScrH;  
     * RETURNS: None.
     */
    VOID SetCamera( TVec<TYPE> Pos, TVec<TYPE> At, TVec<TYPE> UpVec, BOOL IsLookAt,
        TYPE SaveW = 0.4, TYPE SaveH = 0.3,
        TYPE ProjD = 1.0, TYPE F = 10000.0,
        TYPE ScrW = 320, TYPE ScrH = 240)
      {
        *this = TCam(Pos, At, UpVec, IsLookAt, SaveW, SaveH, ProjD, F, ScrW, ScrH);
      } /* End of 'SetCamera' function */

    /***
     * Camera transformations.
     ***/

    /* Move forward camera function.
     * ARGUMENTS: 
     *   - distance to move:
     *       TYPE Distance;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& MoveForward( TYPE Distance )
    {
      Loc += Dir * Distance;
      LookAt += Dir * Distance;
      UpdateMatr();

      return *this;
    } /* End of 'MoveForward' function */

    /* Translate camera function.
     * ARGUMENTS: 
     *   - translation vector:
     *       TVec &TransDir;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& Translate( TVec<TYPE> &TransDir )
    {
      Loc += TransDir;
      LookAt += TransDir;
      UpdateMatr();

      return *this;
    } /* End of 'Translate' function */

    /* Translate camera function.
     * ARGUMENTS: 
     *   - translation vector coordinates:
     *       TYPE Dx, TYPE Dy, TYPE Dz;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& Translate( TYPE Dx, TYPE Dy, TYPE Dz )
    {
      TVec<TYPE> TransDir(Dx, Dy, Dz);

      Translate(TVec<TYPE>(TransDir.X, TransDir.Y, TransDir.Z));

      return *this;
    } /* End of 'Translate' function */

    /* Move right camera function.
     * ARGUMENTS: 
     *   - distance to move:
     *       TYPE Distance;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& MoveRight( TYPE Distance )
    {
      Loc += Right * Distance;
      LookAt += Right * Distance;
      UpdateMatr();

      return *this;
    } /* End of 'MoveForward' function */

    /* Move up camera function.
     * ARGUMENTS: 
     *   - distance to move:
     *       TYPE Distance;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& MoveUp( TYPE Distance )
    {
      Loc += Up * Distance;
      LookAt += Up * Distance;
      UpdateMatr();

      return *this;
    } /* End of 'MoveForward' function */

    /* Set camera params (location, look at, up) function.
     * ARGUMENTS: 
     *   - new params:
     *       TVec<TYPE> NewLoc, NewLookAt, NewUpVec;
     * RETURNS:
     *   (TCam&) camera.
     */
    VOID SetLookAtLocUp( TVec<TYPE> NewLoc, TVec<TYPE> NewLookAt, TVec<TYPE> NewUpVec )
    {
      Loc = NewLoc;
      LookAt = NewLookAt;
      Up = NewUpVec;
      UpdateLookAtLocUp();
    } /* End of 'SetLookAtLocUp' function */

    /* Set camera params (location, direction, up) function.
     * ARGUMENTS: 
     *   - new params:
     *       TVec<TYPE> NewLoc, NewDir, NewUpVec;
     * RETURNS:
     *   (TCam&) camera.
     */
    VOID SetDirLocUp( TVec<TYPE> NewLoc, TVec<TYPE> NewDir, TVec<TYPE> NewUpVec )
    {
      Loc = NewLoc;
      Dir = NewDir;
      Up = NewUpVec;
      UpdateDirLocUp();
    } /* End of 'SetDirLocUp' function */

    /* Rotate camera right function.
     * ARGUMENTS: 
     *   - angle to rotate:
     *       TYPE Angle;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& RotateRight( TYPE Angle )
    {
      TTrans<TYPE> RotX;
      TYPE Dist = !(Loc - LookAt);

      RotX.SetRotate(Angle, Right);

      Dir = RotX.TransformVector(Dir);
      Up = RotX.TransformVector(Up);
      UpdateDirLocUp();
      LookAt = Loc + Dir * Dist;

      return *this;
    } /* End of 'RotateRight' function */

    /* Rotate camera dir function.
     * ARGUMENTS: 
     *   - angle to rotate:
     *       TYPE Angle;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& RotateDir( TYPE Angle )
    {
      TTrans<TYPE> RotZ;
      TYPE Dist = !(Loc - LookAt);

      RotZ.SetRotate(Angle, Dir);

      Right = RotZ.TransformVector(Right);
      Up = RotZ.TransformVector(Up);
      UpdateDirLocUp();
      LookAt = Loc + Dir * Dist;

      return *this;
    } /* End of 'RotateDir' function */

    /* Rotate camera function. 
     * ARGUMENTS: 
     *   - angle to rotate:
     *       TYPE Angle;
     * RETURNS:
     *   (TCam&) camera.
     */
    TCam& RotateUp( TYPE Angle )
    {
      TTrans<TYPE> RotY;
      TYPE Dist = !(Loc - LookAt);

      //RotY.SetRotate(Angle, SaveUp);
      RotY.SetRotate(Angle, Up);

      Up = RotY.TransformVector(Up);
      Dir = RotY.TransformVector(Dir);
      Right = RotY.TransformVector(Right);
      UpdateDirLocUp();
      LookAt = Loc + Dir * Dist;

      return *this;
    } /* End of 'RotateUp' function */

    /* Rotation camera view round up direction vector.
     * ARGUMENTS:
     *   - Angle of rotation:
     *       TYPE Angle;
     * RETURNS: None.
     */
    VOID HorizontalRotRoundLookAt( TYPE Angle )
    {
      TTrans<TYPE> Trans;
      TYPE Length;

      /* Getting matrix of rotation round right vector */
      Trans.SetUnit();
      Trans.RotateY(Angle);

      /* Rotating camera vectors, multiplying them on rotation matrix */
      Dir = Trans.TransformVector(Dir);
      Up = Trans.TransformVector(Up);
      Length = !(LookAt - Loc);
      Loc = LookAt - Dir * Length;
      UpdateDirLocUp();
    } /* End of 'HorizontalRotRoundLookAt' function */

    /* Rotation camera view round right direction vector.
     * ARGUMENTS:
     *   - Angle of rotation:
     *       TYPE Angle;
     * RETURNS: None.
     */
    VOID VerticalRotRoundLookAt( TYPE Angle )
    {
      TTrans<TYPE> Trans;
      TYPE Length;

      /* Getting matrix of rotation round right vector */
      Trans.SetUnit();
      Trans.Rotate(Angle, Right);

      /* Rotating camera vectors, multiplying them on rotation matrix */
      Dir = Trans.TransformVector(Dir);
      Right = Trans.TransformVector(Right);

      /* Updating camera right, direction, up vectors */
      Length = !(LookAt - Loc);

      /* Recounting location vector */
      Loc = LookAt - Dir * Length;
      UpdateDirLocUp();
    } /* End of 'VerticalRotRoundLookAt' function */
  }; /* End of 'TCam' class */
} /* End of 'tsg' namespace */

#endif /* _TSGCAM_H_ */

/* END OF 'TSGCAM.H' FILE */
