//
// i_sound.cpp
//
// This is just the crap code I dropped in from the old sound.cpp, it's all
// currently #ifdef(ed) out, so don't mind it too much...

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#ifdef USE_DSOUND
#include <dsound.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "resource.h"
#include "ddutil.h"
#ifdef USE_DSOUND
#include "dsutil.h"
#endif



#ifdef USE_DSOUND
LPDIRECTSOUND           lpDS;
HSNDOBJ                 hsoBeginLevel     = NULL;
HSNDOBJ                 hsoEngineIdle     = NULL;
HSNDOBJ                 hsoEngineRev      = NULL;
HSNDOBJ                 hsoSkidToStop     = NULL;
HSNDOBJ                 hsoShieldBuzz     = NULL;
HSNDOBJ                 hsoShipExplode    = NULL;
HSNDOBJ                 hsoFireBullet     = NULL;
HSNDOBJ                 hsoShipBounce     = NULL;
HSNDOBJ                 hsoDonutExplode   = NULL;
HSNDOBJ                 hsoPyramidExplode = NULL;
HSNDOBJ                 hsoCubeExplode    = NULL;
HSNDOBJ                 hsoSphereExplode  = NULL;
#endif





#ifdef USE_DSOUND
void InitializeSound( void )
{
        if(!bWantSound)
                return; // out of here
    bSoundEnabled = FALSE;
    if (SUCCEEDED(DirectSoundCreate(NULL, &lpDS, NULL)))
    {
        if (SUCCEEDED(lpDS->lpVtbl->SetCooperativeLevel(lpDS, hWndMain,
            DSSCL_NORMAL)))
        {
            hsoBeginLevel     = SndObjCreate(lpDS, "BeginLevel",      1);
            hsoEngineIdle     = SndObjCreate(lpDS, "EngineIdle",      1);
            hsoEngineRev      = SndObjCreate(lpDS, "EngineRev",       1);
            hsoSkidToStop     = SndObjCreate(lpDS, "SkidToStop",      1);
            hsoShieldBuzz     = SndObjCreate(lpDS, "ShieldBuzz",      1);
            hsoShipExplode    = SndObjCreate(lpDS, "ShipExplode",     1);
            hsoFireBullet     = SndObjCreate(lpDS, "Gunfire",        25);
            hsoShipBounce     = SndObjCreate(lpDS, "ShipBounce",      4);
            hsoDonutExplode   = SndObjCreate(lpDS, "DonutExplode",   10);
            hsoPyramidExplode = SndObjCreate(lpDS, "PyramidExplode", 12);
            hsoCubeExplode    = SndObjCreate(lpDS, "CubeExplode",    15);
            hsoSphereExplode  = SndObjCreate(lpDS, "SphereExplode",  10);
            bSoundEnabled = TRUE;

//#ifdef USE_DSOUND   this should be dead code Josephc
            if( bPlayIdle )
                SndObjPlay(hsoEngineIdle, DSBPLAY_LOOPING);

            if( bPlayBuzz )
                SndObjPlay(hsoShieldBuzz, DSBPLAY_LOOPING);

            if( bPlayRev )
                SndObjPlay(hsoEngineRev, DSBPLAY_LOOPING);
//#endif
        }
        else
        {
            lpDS->lpVtbl->Release(lpDS);
            lpDS = NULL;
        }
    }
}

void DestroySound( void )
{
        if(!bWantSound)
                return; //No work to be done
    bSoundEnabled = FALSE;
    if (lpDS)
    {
        SndObjDestroy(hsoBeginLevel);
        hsoBeginLevel = NULL;
        SndObjDestroy(hsoEngineIdle);
        hsoEngineIdle = NULL;
        SndObjDestroy(hsoEngineRev);
        hsoEngineRev = NULL;
        SndObjDestroy(hsoSkidToStop);
        hsoSkidToStop = NULL;
        SndObjDestroy(hsoShieldBuzz);
        hsoShieldBuzz = NULL;
        SndObjDestroy(hsoShipExplode);
        hsoShipExplode = NULL;
        SndObjDestroy(hsoFireBullet);
        hsoFireBullet = NULL;
        SndObjDestroy(hsoShipBounce);
        hsoShipBounce = NULL;
        SndObjDestroy(hsoDonutExplode);
        hsoDonutExplode = NULL;
        SndObjDestroy(hsoPyramidExplode);
        hsoPyramidExplode = NULL;
        SndObjDestroy(hsoCubeExplode);
        hsoCubeExplode = NULL;
        SndObjDestroy(hsoSphereExplode);
        hsoSphereExplode = NULL;

        lpDS->lpVtbl->Release(lpDS);
        lpDS = NULL;
    }
}
#endif


#ifdef USE_DSOUND
//
// play a sound, but first set the panning according to where the
// object is on the screen.  fake 3D sound.
//
void playPanned(HSNDOBJ hSO, DBLNODE *object)
{
    IDirectSoundBuffer *pDSB = SndObjGetFreeBuffer(hSO);

        if(!bWantSound)
                return;   // No sound our Work is done

    if (pDSB)
    {
        switch(ScreenX)
        {
        case 320:
            IDirectSoundBuffer_SetPan(pDSB, (LONG)((20000.0 *
                ((object->dst.right + object->dst.left) / 2) / 320.0) - 10000.0));
            break;
        case 640:
            IDirectSoundBuffer_SetPan(pDSB, (LONG)((20000.0 *
                ((object->dst.right + object->dst.left) / 2) / 640.0) - 10000.0));
            break;
        case 1024:
            IDirectSoundBuffer_SetPan(pDSB, (LONG)((20000.0 *
                ((object->dst.right + object->dst.left) / 2) / 1024.0) - 10000.0));
            break;
        case 1280:
            IDirectSoundBuffer_SetPan(pDSB, (LONG)((20000.0 *
                ((object->dst.right + object->dst.left) / 2) / 1280.0) - 10000.0));
            break;
        }

        IDirectSoundBuffer_Play(pDSB, 0, 0, 0);
    }
}
#endif