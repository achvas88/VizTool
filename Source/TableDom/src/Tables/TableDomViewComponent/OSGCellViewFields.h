/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCELLVIEWFIELDS_H_
#define _OSGCELLVIEWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTableDomDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class CellView;

OSG_GEN_CONTAINERPTR(CellView);

/*! \ingroup GrpContribTableDomFieldTraits
    \ingroup GrpLibOSGContribTableDom
 */
template <>
struct FieldTraits<CellView *> :
    public FieldTraitsFCPtrBase<CellView *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CellView *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTABLEDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFCellViewPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFCellViewPtr"; }
};

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCellViewPtr"; 
}

template<> inline
const Char8 *FieldTraits<CellView *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCellViewPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<CellView *,
                      RecordedRefCountPolicy  > SFRecCellViewPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<CellView *,
                      UnrecordedRefCountPolicy> SFUnrecCellViewPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<CellView *,
                      WeakRefCountPolicy      > SFWeakCellViewPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<CellView *,
                      NoRefCountPolicy        > SFUncountedCellViewPtr;


/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<CellView *,
                      RecordedRefCountPolicy  > MFRecCellViewPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<CellView *,
                      UnrecordedRefCountPolicy> MFUnrecCellViewPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<CellView *,
                      WeakRefCountPolicy      > MFWeakCellViewPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<CellView *,
                      NoRefCountPolicy        > MFUncountedCellViewPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFRecCellViewPtr : 
    public PointerSField<CellView *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUnrecCellViewPtr : 
    public PointerSField<CellView *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFWeakCellViewPtr :
    public PointerSField<CellView *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUncountedCellViewPtr :
    public PointerSField<CellView *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFRecCellViewPtr :
    public PointerMField<CellView *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUnrecCellViewPtr :
    public PointerMField<CellView *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFWeakCellViewPtr :
    public PointerMField<CellView *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUncountedCellViewPtr :
    public PointerMField<CellView *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCELLVIEWFIELDS_H_ */