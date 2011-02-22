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
 **     Do not change this file, changes should be done in the derived      **
 **     class TableDomLayoutManager!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"



#include "OSGCellView.h"                // VisibleViews Class
#include "OSGFieldContainer.h"          // ParentTableDomArea Class

#include "OSGTableDomLayoutManagerBase.h"
#include "OSGTableDomLayoutManager.h"
#include "OSGCell.h"
#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TableDomLayoutManager
    A UI TableDomLayoutManager
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var CellView *      TableDomLayoutManagerBase::_mfVisibleViews
    
*/

/*! \var FieldContainer * TableDomLayoutManagerBase::_sfParentTableDomArea
    The TableDomArea this TableDomLayoutManager is contained in.
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<TableDomLayoutManager *>::_type("TableDomLayoutManagerPtr", "FieldContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(TableDomLayoutManager *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           TableDomLayoutManager *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           TableDomLayoutManager *,
                           0);

DataType &FieldTraits< TableDomLayoutManager *, 1 >::getType(void)
{
    return FieldTraits<TableDomLayoutManager *, 0>::getType();
}


OSG_EXPORT_PTR_SFIELD(ChildPointerSField,
                      TableDomLayoutManager *,
                      UnrecordedRefCountPolicy,
                      1);


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void TableDomLayoutManagerBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecCellViewPtr::Description(
        MFUnrecCellViewPtr::getClassType(),
        "VisibleViews",
        "",
        VisibleViewsFieldId, VisibleViewsFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableDomLayoutManager::editHandleVisibleViews),
        static_cast<FieldGetMethodSig >(&TableDomLayoutManager::getHandleVisibleViews));

    oType.addInitialDesc(pDesc);

    pDesc = new SFParentFieldContainerPtr::Description(
        SFParentFieldContainerPtr::getClassType(),
        "ParentTableDomArea",
        "The TableDomArea this TableDomLayoutManager is contained in.\n",
        ParentTableDomAreaFieldId, ParentTableDomAreaFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast     <FieldEditMethodSig>(&TableDomLayoutManager::invalidEditField),
        static_cast     <FieldGetMethodSig >(&TableDomLayoutManager::invalidGetField));

    oType.addInitialDesc(pDesc);
}


TableDomLayoutManagerBase::TypeObject TableDomLayoutManagerBase::_type(
    TableDomLayoutManagerBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    NULL,
    TableDomLayoutManager::initMethod,
    TableDomLayoutManager::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&TableDomLayoutManager::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"TableDomLayoutManager\"\n"
    "\tparent=\"FieldContainer\"\n"
    "\tlibrary=\"ContribTableDom\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"abstract\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    "\tuseLocalIncludes=\"true\"\n"
    "\tisNodeCore=\"false\"\n"
    "    childFields=\"single\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "\n"
    "A UI TableDomLayoutManager\n"
    "\n"
    "\t<Field\n"
    "\t\tname=\"VisibleViews\"\n"
    "\t\ttype=\"CellView\"\n"
    "\t\tcategory=\"pointer\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"NULL\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\n"
    "\t<Field\n"
    "\t   name=\"ParentTableDomArea\"\n"
    "\t   type=\"FieldContainer\"\n"
    "\t   cardinality=\"single\"\n"
    "\t   visibility=\"external\"\n"
    "\t   access=\"none\"\n"
    "       doRefCount=\"false\"\n"
    "       passFieldMask=\"true\"\n"
    "       category=\"parentpointer\"\n"
    "\t   >\n"
    "\t  The TableDomArea this TableDomLayoutManager is contained in.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "A UI TableDomLayoutManager\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &TableDomLayoutManagerBase::getType(void)
{
    return _type;
}

const FieldContainerType &TableDomLayoutManagerBase::getType(void) const
{
    return _type;
}

UInt32 TableDomLayoutManagerBase::getContainerSize(void) const
{
    return sizeof(TableDomLayoutManager);
}

/*------------------------- decorator get ------------------------------*/


//! Get the TableDomLayoutManager::_mfVisibleViews field.
const MFUnrecCellViewPtr *TableDomLayoutManagerBase::getMFVisibleViews(void) const
{
    return &_mfVisibleViews;
}

MFUnrecCellViewPtr  *TableDomLayoutManagerBase::editMFVisibleViews   (void)
{
    editMField(VisibleViewsFieldMask, _mfVisibleViews);

    return &_mfVisibleViews;
}




void TableDomLayoutManagerBase::pushToVisibleViews(CellView * const value)
{
    editMField(VisibleViewsFieldMask, _mfVisibleViews);

    _mfVisibleViews.push_back(value);
}

void TableDomLayoutManagerBase::assignVisibleViews(const MFUnrecCellViewPtr &value)
{
    MFUnrecCellViewPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecCellViewPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<TableDomLayoutManager *>(this)->clearVisibleViews();

    while(elemIt != elemEnd)
    {
        this->pushToVisibleViews(*elemIt);

        ++elemIt;
    }
}

void TableDomLayoutManagerBase::removeFromVisibleViews(UInt32 uiIndex)
{
    if(uiIndex < _mfVisibleViews.size())
    {
        editMField(VisibleViewsFieldMask, _mfVisibleViews);

        _mfVisibleViews.erase(uiIndex);
    }
}

void TableDomLayoutManagerBase::removeObjFromVisibleViews(CellView * const value)
{
    Int32 iElemIdx = _mfVisibleViews.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(VisibleViewsFieldMask, _mfVisibleViews);

        _mfVisibleViews.erase(iElemIdx);
    }
}
void TableDomLayoutManagerBase::clearVisibleViews(void)
{
    editMField(VisibleViewsFieldMask, _mfVisibleViews);


    _mfVisibleViews.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 TableDomLayoutManagerBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (VisibleViewsFieldMask & whichField))
    {
        returnValue += _mfVisibleViews.getBinSize();
    }
    if(FieldBits::NoField != (ParentTableDomAreaFieldMask & whichField))
    {
        returnValue += _sfParentTableDomArea.getBinSize();
    }

    return returnValue;
}

void TableDomLayoutManagerBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (VisibleViewsFieldMask & whichField))
    {
        _mfVisibleViews.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ParentTableDomAreaFieldMask & whichField))
    {
        _sfParentTableDomArea.copyToBin(pMem);
    }
}

void TableDomLayoutManagerBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (VisibleViewsFieldMask & whichField))
    {
        _mfVisibleViews.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ParentTableDomAreaFieldMask & whichField))
    {
        _sfParentTableDomArea.copyFromBin(pMem);
    }
}



/*------------------------- constructors ----------------------------------*/

TableDomLayoutManagerBase::TableDomLayoutManagerBase(void) :
    Inherited(),
    _mfVisibleViews           (),
    _sfParentTableDomArea     (NULL)
{
}

TableDomLayoutManagerBase::TableDomLayoutManagerBase(const TableDomLayoutManagerBase &source) :
    Inherited(source),
    _mfVisibleViews           (),
    _sfParentTableDomArea     (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

TableDomLayoutManagerBase::~TableDomLayoutManagerBase(void)
{
}
/*-------------------------------------------------------------------------*/
/* Parent linking                                                          */

bool TableDomLayoutManagerBase::linkParent(
    FieldContainer * const pParent,
    UInt16           const childFieldId,
    UInt16           const parentFieldId )
{
    if(parentFieldId == ParentTableDomAreaFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            FieldContainer *pOldParent =
                _sfParentTableDomArea.getValue         ();

            UInt16 oldChildFieldId =
                _sfParentTableDomArea.getParentFieldPos();

            if(pOldParent != NULL)
            {
                pOldParent->unlinkChild(this, oldChildFieldId);
            }

            editSField(ParentTableDomAreaFieldMask);

            _sfParentTableDomArea.setValue(static_cast<FieldContainer *>(pParent), childFieldId);

            return true;
        }

        return false;
    }

    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool TableDomLayoutManagerBase::unlinkParent(
    FieldContainer * const pParent,
    UInt16           const parentFieldId)
{
    if(parentFieldId == ParentTableDomAreaFieldId)
    {
        FieldContainer * pTypedParent =
            dynamic_cast< FieldContainer * >(pParent);

        if(pTypedParent != NULL)
        {
            if(_sfParentTableDomArea.getValue() == pParent)
            {
                editSField(ParentTableDomAreaFieldMask);

                _sfParentTableDomArea.setValue(NULL, 0xFFFF);

                return true;
            }

            FWARNING(("TableDomLayoutManagerBase::unlinkParent: "
                      "Child <-> Parent link inconsistent.\n"));

            return false;
        }

        return false;
    }

    return Inherited::unlinkParent(pParent, parentFieldId);
}


void TableDomLayoutManagerBase::onCreate(const TableDomLayoutManager *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        TableDomLayoutManager *pThis = static_cast<TableDomLayoutManager *>(this);

        MFUnrecCellViewPtr::const_iterator VisibleViewsIt  =
            source->_mfVisibleViews.begin();
        MFUnrecCellViewPtr::const_iterator VisibleViewsEnd =
            source->_mfVisibleViews.end  ();

        while(VisibleViewsIt != VisibleViewsEnd)
        {
            pThis->pushToVisibleViews(*VisibleViewsIt);

            ++VisibleViewsIt;
        }
    }
}

GetFieldHandlePtr TableDomLayoutManagerBase::getHandleVisibleViews    (void) const
{
    MFUnrecCellViewPtr::GetHandlePtr returnValue(
        new  MFUnrecCellViewPtr::GetHandle(
             &_mfVisibleViews,
             this->getType().getFieldDesc(VisibleViewsFieldId),
             const_cast<TableDomLayoutManagerBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableDomLayoutManagerBase::editHandleVisibleViews   (void)
{
    MFUnrecCellViewPtr::EditHandlePtr returnValue(
        new  MFUnrecCellViewPtr::EditHandle(
             &_mfVisibleViews,
             this->getType().getFieldDesc(VisibleViewsFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&TableDomLayoutManager::pushToVisibleViews,
                    static_cast<TableDomLayoutManager *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&TableDomLayoutManager::removeFromVisibleViews,
                    static_cast<TableDomLayoutManager *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&TableDomLayoutManager::removeObjFromVisibleViews,
                    static_cast<TableDomLayoutManager *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&TableDomLayoutManager::clearVisibleViews,
                    static_cast<TableDomLayoutManager *>(this)));

    editMField(VisibleViewsFieldMask, _mfVisibleViews);

    return returnValue;
}

GetFieldHandlePtr TableDomLayoutManagerBase::getHandleParentTableDomArea (void) const
{
    SFParentFieldContainerPtr::GetHandlePtr returnValue;

    return returnValue;
}

EditFieldHandlePtr TableDomLayoutManagerBase::editHandleParentTableDomArea(void)
{
    EditFieldHandlePtr returnValue;

    return returnValue;
}



#ifdef OSG_MT_CPTR_ASPECT
void TableDomLayoutManagerBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    TableDomLayoutManager *pThis = static_cast<TableDomLayoutManager *>(this);

    pThis->execSync(static_cast<TableDomLayoutManager *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif



void TableDomLayoutManagerBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<TableDomLayoutManager *>(this)->clearVisibleViews();


}


OSG_END_NAMESPACE