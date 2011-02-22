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

#include "OSGPlainTableDOM.h"
#include "OSGPlainTableDOMBranchCell.h"
#include "OSGPlainTableDOMLeafCell.h"

#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPlainTableDOMBase.cpp file.
// To modify it, please change the .fcd file (OSGPlainTableDOM.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PlainTableDOM::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PlainTableDOM::insertValue(UInt32 row,UInt32 column,const boost::any value)
{
	PlainTableDOMBranchCellRefPtr rootCell;

	if(getRootCell())
	{
		rootCell=dynamic_cast<PlainTableDOMBranchCell*>(getRootCell());
	}
	else
	{
		rootCell = PlainTableDOMBranchCell::create();	
		setRootCell(rootCell);
	}

	PlainTableDOMBranchCellRefPtr rowCell;

	rowCell = dynamic_cast<PlainTableDOMBranchCell*>(rootCell->getCell(row));

	if(!rowCell)
	{
		rowCell = dynamic_cast<PlainTableDOMBranchCell*>(rootCell->createRow(row));
	}

	PlainTableDOMLeafCellRefPtr columnCell;

	columnCell = dynamic_cast<PlainTableDOMLeafCell*>(rowCell->getCell(column));

	if(!columnCell)
	{
		columnCell = dynamic_cast<PlainTableDOMLeafCell*>(rowCell->createColumn(column));
	}

	columnCell->setValue(value);

	TableDOMEventDetailsUnrecPtr TableEventDetails(TableDOMEventDetails::create(this, getTimeStamp(), this, 0 , 0));
	this->produceInsert(TableEventDetails);

}

void PlainTableDOM::print(void) const
{
	 //boost::any_cast<std::string>();

	if(getRootCell())
	{
		getRootCell()->print();
	}
	else
	{
		SWARNING<<"void PlainTableDOM::print(void) const -> Root is NULL\n";
	}

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PlainTableDOM::PlainTableDOM(void) :
    Inherited()
{
}

PlainTableDOM::PlainTableDOM(const PlainTableDOM &source) :
    Inherited(source)
{
}

PlainTableDOM::~PlainTableDOM(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PlainTableDOM::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PlainTableDOM::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PlainTableDOM NI" << std::endl;
}

OSG_END_NAMESPACE
