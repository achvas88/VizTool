/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala*
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

#define OSG_COMPILECONTRIBTABLEDOMLIB

#include <OSGConfig.h>

#include "OSGTableDomVariableHeightLayoutManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableDomVariableHeightLayoutManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGTableDomVariableHeightLayoutManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableDomVariableHeightLayoutManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


void TableDomVariableHeightLayoutManager::initializeRootCell() 
{
	return;
}

void TableDomVariableHeightLayoutManager::calculatePreferredSize(void)
{
	return;
}

Vec2f  TableDomVariableHeightLayoutManager::getContentRequestedSize(void) const
{
	return Vec2f(0.0,0.0);
}


void TableDomVariableHeightLayoutManager::updateViews(void)
{
	return;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableDomVariableHeightLayoutManager::TableDomVariableHeightLayoutManager(void) :
    Inherited()
{
}

TableDomVariableHeightLayoutManager::TableDomVariableHeightLayoutManager(const TableDomVariableHeightLayoutManager &source) :
    Inherited(source)
{
}

TableDomVariableHeightLayoutManager::~TableDomVariableHeightLayoutManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TableDomVariableHeightLayoutManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TableDomVariableHeightLayoutManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableDomVariableHeightLayoutManager NI" << std::endl;
}

OSG_END_NAMESPACE
