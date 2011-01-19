/*---------------------------------------------------------------------------*\
 *                             VizTool                                 		 *
 *                                                                           *
 *               Copyright (C) 2010-2011 by Achyuthan Vasanth                *
 *                                                                           *
 *   authors:  Achyuthan Vasanth (achvas88@gmail.com)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
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
 **     class ColorChooserComboBoxComponentGenerator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OpenSG/OSGConfig.h"




#include "VTColorChooserComboBoxComponentGeneratorBase.h"
#include "VTColorChooserComboBoxComponentGenerator.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ColorChooserComboBoxComponentGenerator
    A ColorChooserComboBoxComponentGenerator.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<ColorChooserComboBoxComponentGenerator *>::_type("ColorChooserComboBoxComponentGeneratorPtr", "DefaultComboBoxComponentGeneratorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(ColorChooserComboBoxComponentGenerator *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           ColorChooserComboBoxComponentGenerator *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           ColorChooserComboBoxComponentGenerator *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void ColorChooserComboBoxComponentGeneratorBase::classDescInserter(TypeObject &oType)
{
}


ColorChooserComboBoxComponentGeneratorBase::TypeObject ColorChooserComboBoxComponentGeneratorBase::_type(
    ColorChooserComboBoxComponentGeneratorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ColorChooserComboBoxComponentGeneratorBase::createEmptyLocal),
    ColorChooserComboBoxComponentGenerator::initMethod,
    ColorChooserComboBoxComponentGenerator::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&ColorChooserComboBoxComponentGenerator::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"ColorChooserComboBoxComponentGenerator\"\n"
    "\tparent=\"DefaultComboBoxComponentGenerator\"\n"
    "    library=\"VizTool\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "    systemcomponent=\"false\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"true\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"Achyuthan Vasanth (achvas88@gmail.com)                        \"\n"
    ">\n"
    "A ColorChooserComboBoxComponentGenerator.\n"
    "\n"
    "</FieldContainer>\n",
    "A ColorChooserComboBoxComponentGenerator.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &ColorChooserComboBoxComponentGeneratorBase::getType(void)
{
    return _type;
}

const FieldContainerType &ColorChooserComboBoxComponentGeneratorBase::getType(void) const
{
    return _type;
}

UInt32 ColorChooserComboBoxComponentGeneratorBase::getContainerSize(void) const
{
    return sizeof(ColorChooserComboBoxComponentGenerator);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 ColorChooserComboBoxComponentGeneratorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void ColorChooserComboBoxComponentGeneratorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void ColorChooserComboBoxComponentGeneratorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
ColorChooserComboBoxComponentGeneratorTransitPtr ColorChooserComboBoxComponentGeneratorBase::createLocal(BitVector bFlags)
{
    ColorChooserComboBoxComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<ColorChooserComboBoxComponentGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
ColorChooserComboBoxComponentGeneratorTransitPtr ColorChooserComboBoxComponentGeneratorBase::createDependent(BitVector bFlags)
{
    ColorChooserComboBoxComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<ColorChooserComboBoxComponentGenerator>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
ColorChooserComboBoxComponentGeneratorTransitPtr ColorChooserComboBoxComponentGeneratorBase::create(void)
{
    ColorChooserComboBoxComponentGeneratorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<ColorChooserComboBoxComponentGenerator>(tmpPtr);
    }

    return fc;
}

ColorChooserComboBoxComponentGenerator *ColorChooserComboBoxComponentGeneratorBase::createEmptyLocal(BitVector bFlags)
{
    ColorChooserComboBoxComponentGenerator *returnValue;

    newPtr<ColorChooserComboBoxComponentGenerator>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
ColorChooserComboBoxComponentGenerator *ColorChooserComboBoxComponentGeneratorBase::createEmpty(void)
{
    ColorChooserComboBoxComponentGenerator *returnValue;

    newPtr<ColorChooserComboBoxComponentGenerator>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr ColorChooserComboBoxComponentGeneratorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    ColorChooserComboBoxComponentGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ColorChooserComboBoxComponentGenerator *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr ColorChooserComboBoxComponentGeneratorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    ColorChooserComboBoxComponentGenerator *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const ColorChooserComboBoxComponentGenerator *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr ColorChooserComboBoxComponentGeneratorBase::shallowCopy(void) const
{
    ColorChooserComboBoxComponentGenerator *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const ColorChooserComboBoxComponentGenerator *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}



/*------------------------- constructors ----------------------------------*/

ColorChooserComboBoxComponentGeneratorBase::ColorChooserComboBoxComponentGeneratorBase(void) :
    Inherited()
{
}

ColorChooserComboBoxComponentGeneratorBase::ColorChooserComboBoxComponentGeneratorBase(const ColorChooserComboBoxComponentGeneratorBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

ColorChooserComboBoxComponentGeneratorBase::~ColorChooserComboBoxComponentGeneratorBase(void)
{
}




#ifdef OSG_MT_CPTR_ASPECT
void ColorChooserComboBoxComponentGeneratorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    ColorChooserComboBoxComponentGenerator *pThis = static_cast<ColorChooserComboBoxComponentGenerator *>(this);

    pThis->execSync(static_cast<ColorChooserComboBoxComponentGenerator *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *ColorChooserComboBoxComponentGeneratorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    ColorChooserComboBoxComponentGenerator *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const ColorChooserComboBoxComponentGenerator *>(pRefAspect),
                  dynamic_cast<const ColorChooserComboBoxComponentGenerator *>(this));

    return returnValue;
}
#endif

void ColorChooserComboBoxComponentGeneratorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
