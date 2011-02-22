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

#include "OSGAbstractBranchCell.h"
#include "boost/any.hpp"
#include <map>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractBranchCellBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractBranchCell.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractBranchCell::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbstractBranchCell::setValue(const boost::any theValue)
{
}

boost::any AbstractBranchCell::getValue(void) const
{
	return 0;
}


Cell* AbstractBranchCell::getCell(UInt32 value) const
{
	std::map<UInt32,CellRefPtr>::const_iterator FindItor(childrenMap.find(value));
    if(FindItor != childrenMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        //SWARNING << "Cell* PlainTableDOMBranchCell::getCell(UInt32 value) const -> No Such Cell Exists: " << std::endl;
        return NULL;
    }
}


void AbstractBranchCell::print(void) const
{
	for(std::map<UInt32,CellRefPtr>::const_iterator Itr(childrenMap.begin()) ; Itr!=childrenMap.end() ; Itr++)
	{
		std::cout <<"Index:"<<Itr->first<<std::endl;
		std::cout <<"________________________________________________\n";
		Itr->second->print();
	}
}


std::map<UInt32,CellRefPtr>& AbstractBranchCell::getChildrenMap(void)
{
	return childrenMap;
}


UInt32 AbstractBranchCell::getMaximumColumn(void) const
{
	return maxCol;
}

UInt32 AbstractBranchCell::getMaximumRow(void) const
{
	return maxRow;
}

void AbstractBranchCell::setMaximumColumn(UInt32 value)
{
	maxCol = value;
}

void AbstractBranchCell::setMaximumRow(UInt32 value) 
{
	maxRow = value;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractBranchCell::AbstractBranchCell(void) :
    Inherited(),
	maxRow(0),
	maxCol(0)
{
}

AbstractBranchCell::AbstractBranchCell(const AbstractBranchCell &source) :
    Inherited(source)
{
	maxRow = source.maxRow;
	maxCol = source.maxCol;
}

AbstractBranchCell::~AbstractBranchCell(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractBranchCell::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractBranchCell::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractBranchCell NI" << std::endl;
}

OSG_END_NAMESPACE
