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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGAbstractLeafCell.h"

#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractLeafCellBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractLeafCell.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractLeafCell::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void AbstractLeafCell::setValue(const boost::any theValue)
{
	value = theValue;
}

boost::any AbstractLeafCell::getValue(void) const
{
	return value;
}

Cell* AbstractLeafCell::getCell(UInt32 value) const
{
	return NULL;
}


Cell* AbstractLeafCell::createRow(UInt32 row)
{
	return NULL;
}

Cell* AbstractLeafCell::createColumn(UInt32 column)
{
	return NULL;
}

void AbstractLeafCell::print(void) const
{
	std::cout<<"Value:"<<boost::any_cast<std::string>(getValue())<<std::endl;
}

UInt32 AbstractLeafCell::getMaximumColumn(void) const
{
	return 0;
}

UInt32 AbstractLeafCell::getMaximumRow(void) const
{
	return 0;
}

void AbstractLeafCell::setMaximumColumn(UInt32 value)
{
	return;
}

void AbstractLeafCell::setMaximumRow(UInt32 value) 
{
	return;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractLeafCell::AbstractLeafCell(void) :
    Inherited()
{
}

AbstractLeafCell::AbstractLeafCell(const AbstractLeafCell &source) :
    Inherited(source)
{
}

AbstractLeafCell::~AbstractLeafCell(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractLeafCell::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractLeafCell::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractLeafCell NI" << std::endl;
}

OSG_END_NAMESPACE
