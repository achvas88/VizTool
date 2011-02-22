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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define OSG_COMPILECONTRIBTABLEDOMLIB

#include "OSGConfig.h"

#include "OSGCellView.h"
#include "OSGGraphics.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCellViewBase.cpp file.
// To modify it, please change the .fcd file (OSGCellView.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CellView::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void CellView::drawView(Graphics * const TheGraphics, Real32 Opacity) const
{
	
	TheGraphics->drawRect(getCellPosition(),Pnt2f(getCellPosition().x()+getCellWidth(),getCellPosition().y()+getCellHeight()),Color4f(0.0,0.0,0.0,1.0),Opacity);
	TheGraphics->drawRect(getCellPosition(),Pnt2f(getCellPosition().x()+getCellWidth()-2,getCellPosition().y()+getCellHeight()-2),Color4f(1.0,1.0,1.0,1.0),Opacity);

	if(getCell())
	{
		TheGraphics->drawText(Pnt2f(getCellPosition().x()+1,getCellPosition().y()+getCellHeight()/3),boost::any_cast<std::string>(getCell()->getValue()),getFont(),Color4f(0.0,0.0,0.0,1.0),Opacity);
	}		
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CellView::CellView(void) :
    Inherited()
{
}

CellView::CellView(const CellView &source) :
    Inherited(source)
{
}

CellView::~CellView(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CellView::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CellView::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CellView NI" << std::endl;
}

OSG_END_NAMESPACE
