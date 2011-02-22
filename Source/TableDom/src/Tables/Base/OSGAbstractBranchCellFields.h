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


#ifndef _OSGABSTRACTBRANCHCELLFIELDS_H_
#define _OSGABSTRACTBRANCHCELLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTableDomDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class AbstractBranchCell;

OSG_GEN_CONTAINERPTR(AbstractBranchCell);

/*! \ingroup GrpContribTableDomFieldTraits
    \ingroup GrpLibOSGContribTableDom
 */
template <>
struct FieldTraits<AbstractBranchCell *> :
    public FieldTraitsFCPtrBase<AbstractBranchCell *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<AbstractBranchCell *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTABLEDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFAbstractBranchCellPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFAbstractBranchCellPtr"; }
};

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAbstractBranchCellPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractBranchCell *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAbstractBranchCellPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractBranchCell *,
                      RecordedRefCountPolicy  > SFRecAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractBranchCell *,
                      UnrecordedRefCountPolicy> SFUnrecAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractBranchCell *,
                      WeakRefCountPolicy      > SFWeakAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldSFields */
typedef PointerSField<AbstractBranchCell *,
                      NoRefCountPolicy        > SFUncountedAbstractBranchCellPtr;


/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractBranchCell *,
                      RecordedRefCountPolicy  > MFRecAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractBranchCell *,
                      UnrecordedRefCountPolicy> MFUnrecAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractBranchCell *,
                      WeakRefCountPolicy      > MFWeakAbstractBranchCellPtr;
/*! \ingroup GrpContribTableDomFieldMFields */
typedef PointerMField<AbstractBranchCell *,
                      NoRefCountPolicy        > MFUncountedAbstractBranchCellPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFRecAbstractBranchCellPtr : 
    public PointerSField<AbstractBranchCell *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUnrecAbstractBranchCellPtr : 
    public PointerSField<AbstractBranchCell *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFWeakAbstractBranchCellPtr :
    public PointerSField<AbstractBranchCell *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldSFields \ingroup GrpLibOSGContribTableDom */
struct SFUncountedAbstractBranchCellPtr :
    public PointerSField<AbstractBranchCell *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFRecAbstractBranchCellPtr :
    public PointerMField<AbstractBranchCell *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUnrecAbstractBranchCellPtr :
    public PointerMField<AbstractBranchCell *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFWeakAbstractBranchCellPtr :
    public PointerMField<AbstractBranchCell *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTableDomFieldMFields \ingroup GrpLibOSGContribTableDom */
struct MFUncountedAbstractBranchCellPtr :
    public PointerMField<AbstractBranchCell *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGABSTRACTBRANCHCELLFIELDS_H_ */