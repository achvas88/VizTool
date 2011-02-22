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
 **     class TableDOMEventDetails!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"


#include "OSGTableDOM.h"                // TableDOM Class

#include "OSGTableDOMEventDetailsBase.h"
#include "OSGTableDOMEventDetails.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TableDOMEventDetails
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var TableDOM *      TableDOMEventDetailsBase::_sfTableDOM
    
*/

/*! \var UInt32          TableDOMEventDetailsBase::_sfRow
    
*/

/*! \var UInt32          TableDOMEventDetailsBase::_sfColumn
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<TableDOMEventDetails *>::_type("TableDOMEventDetailsPtr", "EventDetailsPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(TableDOMEventDetails *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           TableDOMEventDetails *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           TableDOMEventDetails *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void TableDOMEventDetailsBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecTableDOMPtr::Description(
        SFUnrecTableDOMPtr::getClassType(),
        "TableDOM",
        "",
        TableDOMFieldId, TableDOMFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableDOMEventDetails::editHandleTableDOM),
        static_cast<FieldGetMethodSig >(&TableDOMEventDetails::getHandleTableDOM));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "Row",
        "",
        RowFieldId, RowFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableDOMEventDetails::editHandleRow),
        static_cast<FieldGetMethodSig >(&TableDOMEventDetails::getHandleRow));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "Column",
        "",
        ColumnFieldId, ColumnFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&TableDOMEventDetails::editHandleColumn),
        static_cast<FieldGetMethodSig >(&TableDOMEventDetails::getHandleColumn));

    oType.addInitialDesc(pDesc);
}


TableDOMEventDetailsBase::TypeObject TableDOMEventDetailsBase::_type(
    TableDOMEventDetailsBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&TableDOMEventDetailsBase::createEmptyLocal),
    TableDOMEventDetails::initMethod,
    TableDOMEventDetails::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&TableDOMEventDetails::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"TableDOMEventDetails\"\n"
    "\tparent=\"EventDetails\"\n"
    "    library=\"ContribTableDom\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "\tsupportUnregisteredCreate=\"true\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"TableDOM\"\n"
    "\t\ttype=\"TableDOM\"\n"
    "\t\tcategory=\"pointer\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"NULL\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Row\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcategory=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"Column\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcategory=\"data\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"protected\"\n"
    "\t\tdefaultValue=\"0\"\n"
    "        publicRead=\"true\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &TableDOMEventDetailsBase::getType(void)
{
    return _type;
}

const FieldContainerType &TableDOMEventDetailsBase::getType(void) const
{
    return _type;
}

UInt32 TableDOMEventDetailsBase::getContainerSize(void) const
{
    return sizeof(TableDOMEventDetails);
}

/*------------------------- decorator get ------------------------------*/


//! Get the TableDOMEventDetails::_sfTableDOM field.
const SFUnrecTableDOMPtr *TableDOMEventDetailsBase::getSFTableDOM(void) const
{
    return &_sfTableDOM;
}

SFUnrecTableDOMPtr  *TableDOMEventDetailsBase::editSFTableDOM       (void)
{
    editSField(TableDOMFieldMask);

    return &_sfTableDOM;
}

SFUInt32 *TableDOMEventDetailsBase::editSFRow(void)
{
    editSField(RowFieldMask);

    return &_sfRow;
}

const SFUInt32 *TableDOMEventDetailsBase::getSFRow(void) const
{
    return &_sfRow;
}


SFUInt32 *TableDOMEventDetailsBase::editSFColumn(void)
{
    editSField(ColumnFieldMask);

    return &_sfColumn;
}

const SFUInt32 *TableDOMEventDetailsBase::getSFColumn(void) const
{
    return &_sfColumn;
}






/*------------------------------ access -----------------------------------*/

UInt32 TableDOMEventDetailsBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TableDOMFieldMask & whichField))
    {
        returnValue += _sfTableDOM.getBinSize();
    }
    if(FieldBits::NoField != (RowFieldMask & whichField))
    {
        returnValue += _sfRow.getBinSize();
    }
    if(FieldBits::NoField != (ColumnFieldMask & whichField))
    {
        returnValue += _sfColumn.getBinSize();
    }

    return returnValue;
}

void TableDOMEventDetailsBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TableDOMFieldMask & whichField))
    {
        _sfTableDOM.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RowFieldMask & whichField))
    {
        _sfRow.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ColumnFieldMask & whichField))
    {
        _sfColumn.copyToBin(pMem);
    }
}

void TableDOMEventDetailsBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TableDOMFieldMask & whichField))
    {
        _sfTableDOM.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RowFieldMask & whichField))
    {
        _sfRow.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ColumnFieldMask & whichField))
    {
        _sfColumn.copyFromBin(pMem);
    }
}

//! create a new instance of the class
TableDOMEventDetailsTransitPtr TableDOMEventDetailsBase::createLocal(BitVector bFlags)
{
    TableDOMEventDetailsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<TableDOMEventDetails>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
TableDOMEventDetailsTransitPtr TableDOMEventDetailsBase::createDependent(BitVector bFlags)
{
    TableDOMEventDetailsTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<TableDOMEventDetails>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
TableDOMEventDetailsTransitPtr TableDOMEventDetailsBase::create(void)
{
    return createLocal();
}

TableDOMEventDetails *TableDOMEventDetailsBase::createEmptyLocal(BitVector bFlags)
{
    TableDOMEventDetails *returnValue;

    newPtr<TableDOMEventDetails>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
TableDOMEventDetails *TableDOMEventDetailsBase::createEmpty(void)
{
    return createEmptyLocal();
}

TableDOMEventDetails *TableDOMEventDetailsBase::createUnregistered(void)
{
    TableDOMEventDetails *returnValue = new TableDOMEventDetails;

#ifdef OSG_MT_CPTR_ASPECT
    returnValue->setupAspectStore();
#endif
    //Do not register with the FieldContainer Factory

    returnValue->onCreate      (      );
    returnValue->onCreateAspect(returnValue);
    
    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();
    
    return returnValue;
}

FieldContainerTransitPtr TableDOMEventDetailsBase::shallowCopyLocal(
    BitVector bFlags) const
{
    TableDOMEventDetails *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TableDOMEventDetails *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr TableDOMEventDetailsBase::shallowCopyDependent(
    BitVector bFlags) const
{
    TableDOMEventDetails *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TableDOMEventDetails *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr TableDOMEventDetailsBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}



/*------------------------- constructors ----------------------------------*/

TableDOMEventDetailsBase::TableDOMEventDetailsBase(void) :
    Inherited(),
    _sfTableDOM               (NULL),
    _sfRow                    (UInt32(0)),
    _sfColumn                 (UInt32(0))
{
}

TableDOMEventDetailsBase::TableDOMEventDetailsBase(const TableDOMEventDetailsBase &source) :
    Inherited(source),
    _sfTableDOM               (NULL),
    _sfRow                    (source._sfRow                    ),
    _sfColumn                 (source._sfColumn                 )
{
}


/*-------------------------- destructors ----------------------------------*/

TableDOMEventDetailsBase::~TableDOMEventDetailsBase(void)
{
}

void TableDOMEventDetailsBase::onCreate(const TableDOMEventDetails *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        TableDOMEventDetails *pThis = static_cast<TableDOMEventDetails *>(this);

        pThis->setTableDOM(source->getTableDOM());
    }
}

GetFieldHandlePtr TableDOMEventDetailsBase::getHandleTableDOM        (void) const
{
    SFUnrecTableDOMPtr::GetHandlePtr returnValue(
        new  SFUnrecTableDOMPtr::GetHandle(
             &_sfTableDOM,
             this->getType().getFieldDesc(TableDOMFieldId),
             const_cast<TableDOMEventDetailsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableDOMEventDetailsBase::editHandleTableDOM       (void)
{
    SFUnrecTableDOMPtr::EditHandlePtr returnValue(
        new  SFUnrecTableDOMPtr::EditHandle(
             &_sfTableDOM,
             this->getType().getFieldDesc(TableDOMFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&TableDOMEventDetails::setTableDOM,
                    static_cast<TableDOMEventDetails *>(this), _1));

    editSField(TableDOMFieldMask);

    return returnValue;
}

GetFieldHandlePtr TableDOMEventDetailsBase::getHandleRow             (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfRow,
             this->getType().getFieldDesc(RowFieldId),
             const_cast<TableDOMEventDetailsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableDOMEventDetailsBase::editHandleRow            (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfRow,
             this->getType().getFieldDesc(RowFieldId),
             this));


    editSField(RowFieldMask);

    return returnValue;
}

GetFieldHandlePtr TableDOMEventDetailsBase::getHandleColumn          (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfColumn,
             this->getType().getFieldDesc(ColumnFieldId),
             const_cast<TableDOMEventDetailsBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TableDOMEventDetailsBase::editHandleColumn         (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfColumn,
             this->getType().getFieldDesc(ColumnFieldId),
             this));


    editSField(ColumnFieldMask);

    return returnValue;
}



#ifdef OSG_MT_CPTR_ASPECT
void TableDOMEventDetailsBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    TableDOMEventDetails *pThis = static_cast<TableDOMEventDetails *>(this);

    pThis->execSync(static_cast<TableDOMEventDetails *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *TableDOMEventDetailsBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    TableDOMEventDetails *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const TableDOMEventDetails *>(pRefAspect),
                  dynamic_cast<const TableDOMEventDetails *>(this));

    return returnValue;
}
#endif

void TableDOMEventDetailsBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<TableDOMEventDetails *>(this)->setTableDOM(NULL);


}


OSG_END_NAMESPACE