// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef COMMON_H
#define COMMON_H

/*********Begin here**********************/

#ifdef WIN32 // Win32 specific stuff here

// These from Winsock.h. We don't include that unless necessary.
typedef unsigned int    u_int;
typedef unsigned long   u_long;

// These from SVID XOpen, haven't found them on Windows anywhere
/*
 * SVID & X/Open
 */
#define M_E             2.7182818284590452354
#define M_LOG2E         1.4426950408889634074
#define M_LOG10E        0.43429448190325182765
#define M_LN2           0.69314718055994530942
#define M_LN10          2.30258509299404568402
#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923
#define M_PI_4          0.78539816339744830962
#define M_1_PI          0.31830988618379067154
#define M_2_PI          0.63661977236758134308
#define M_2_SQRTPI      1.12837916709551257390
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.70710678118654752440


// From http://www.osl.iu.edu/MailArchives/mtl-devel/msg00331.php
// The MTL mailing list
// <disable4886.h>
#if defined(_MSC_VER) && _MSC_VER <= 1200

#pragma warning(disable:4786)
// http://support.microsoft.com/support/kb/articles/Q167/3/55.ASP
// states that yes, it's a compiler bug that
// #pragma warning(disable: 4786) doesn't always work.
// They don't, however, list a workaround.
// I found that, very strangely, #including <iostream> made the 
// remaining 4786 warnings go away!
// Of course, #including <iostream> is inefficient and
// slows compilation - so I whittled away most of what's in
// <iostream> and discovered that the "active ingredient" in
// <iostream> appears to be a declaration of a static class,
// complete with default constructor.
// For some reason, this works around the bug!
// Why does this work? Beats me, ask those smart guys at MS who // wrote the compiler.
class msVC6_4786WorkAround {
    public:
        msVC6_4786WorkAround() {}
};

    static msVC6_4786WorkAround WowIWonderWhatCrapCodeMustBeInTheCompilerToMakeThisWorkaroundWork;

#endif //(_MSC_VER) && _MSC_VER <= 1200



#else // Non-win32 here




#endif


/************EOF**********************/

#endif 


