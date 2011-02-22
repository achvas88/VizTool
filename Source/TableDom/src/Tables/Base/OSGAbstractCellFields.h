/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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


#ifndef _OSGABSTRACTCELLFIELDS_H_
#define _OSGABSTRACTCELLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTableDomDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class AbstractCell;

OSG_GEN_CONTAINERPTR(AbstractCell);

/*! \ingroup GrpContribTableDomFieldTraits
    \ingroup GrpLibOSGContribTableDom
 */
template <>
struct FieldTraits<AbstractCell *> :
    public FieldTraitsFCPtrBase<AbstractCell *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<AbstractCell *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTABLEDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFAbstractCellPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFAbstractCellPtr"; }
};

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAbstractCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractCell *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAbstractCellPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractCell *,
                      RecordedRefCountPolicy  > SFRecAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractCell *,
                      UnrecordedRefCountPolicy> SFUnrecAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractCell *,
                      WeakRefCountPolicy      > SFWeakAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractCell *,
                      NoRefCountPolicy        > SFUncountedAbstractCellPtr;


/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractCell *,
                      RecordedRefCountPolicy  > MFRecAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractCell *,
                      UnrecordedRefCountPolicy> MFUnrecAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractCell *,
                      WeakRefCountPolicy      > MFWeakAbstractCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractCell *,
                      NoRefCountPolicy        > MFUncountedAbstractCellPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFRecAbstractCellPtr : 
    public PointerSField<AbstractCell *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUnrecAbstractCellPtr : 
    public PointerSField<AbstractCell *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFWeakAbstractCellPtr :
    public PointerSField<AbstractCell *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUncountedAbstractCellPtr :
    public PointerSField<AbstractCell *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFRecAbstractCellPtr :
    public PointerMField<AbstractCell *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUnrecAbstractCellPtr :
    public PointerMField<AbstractCell *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFWeakAbstractCellPtr :
    public PointerMField<AbstractCell *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUncountedAbstractCellPtr :
    public PointerMField<AbstractCell *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGABSTRACTCELLFIELDS_H_ */
