#ifndef _VTVIZTOOLDEF_H_
#define _VTVIZTOOLDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(VT_BUILD_DLL)
#   ifdef VT_COMPILEVIZTOOLLIB
#       define VT_VIZTOOL_DLLMAPPING     __declspec(dllexport)
#       define VT_VIZTOOL_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define VT_VIZTOOL_DLLMAPPING     __declspec(dllimport)
#       define VT_VIZTOOL_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define VT_VIZTOOL_DLLMAPPING
#define VT_VIZTOOL_DLLTMPLMAPPING
#endif

#endif /* _VTVIZTOOLDEF_H_ */

