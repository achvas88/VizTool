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

#include "OSGTableDomFixedHeightLayoutManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableDomFixedHeightLayoutManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGTableDomFixedHeightLayoutManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableDomFixedHeightLayoutManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void TableDomFixedHeightLayoutManager::initializeRootCell() 
{
	if(getParentTableDomArea())
	{
		if(getParentTableDomArea()->getTableDOMModel())
		{
			rootCell = getParentTableDomArea()->getTableDOMModel()->getRootCell();
			//rootCell = dynamic_cast<PlainTableDOMBranchElement*>(defaultRoot);
		}
	}
}

void TableDomFixedHeightLayoutManager::calculatePreferredSize(void)
{
	if(getParentTableDomArea()->getTableDOMModel())
	{
		CellRefPtr rootCell=getParentTableDomArea()->getTableDOMModel()->getRootCell();

		_preferredWidth = rootCell->getMaximumColumn() * widthOfColumn;
		_preferredHeight =  rootCell->getMaximumRow() * heightOfRow;
	}
	else 
	{
		_preferredWidth = getParentTableDomArea()->getSize().x();
		_preferredHeight =  getParentTableDomArea()->getSize().y();
	}
}

Vec2f  TableDomFixedHeightLayoutManager::getContentRequestedSize(void) const
{
	return Vec2f(_preferredWidth,_preferredHeight);
}


void TableDomFixedHeightLayoutManager::updateViews(void)
{
	if(rootCell)
	{
		Pnt2f init = getParentTableDomArea()->getPosition();

		UInt32 rowNumber = getTopmostVisibleRowNumber();
		UInt32 rowsToBeDisplayed = getRowsToBeDisplayed()+1;

		UInt32 colNumber = getLeftmostVisibleColNumber();
		UInt32 colsToBeDisplayed = getColsToBeDisplayed()+1;

		clearVisibleViews();
					
		for(UInt32 i=0;i<rowsToBeDisplayed;i++)
		{
			for(UInt32 j=0;j<colsToBeDisplayed;j++)
			{
				CellViewRefPtr view = CellView::create();
				view->setFont(getParentTableDomArea()->getFont());
				view->setCellPosition(Pnt2f((colNumber+j)*widthOfColumn,(rowNumber+i)*heightOfRow));
				view->setCellWidth(widthOfColumn);
				view->setCellHeight(heightOfRow);
				CellRefPtr theRow = rootCell->getCell(rowNumber+i);
				view->setCell(NULL);
				if(theRow)
				{	
					CellRefPtr theCell = theRow->getCell(colNumber+j);
					if(theCell)
					{
						view->setCell(theCell);
					}
				}
				
				pushToVisibleViews(view);
			}
		}
	}
}


UInt32 TableDomFixedHeightLayoutManager::getLeftmostVisibleColNumber() const
{
	Pnt2f topLeft,bottomRight;
	getParentTableDomArea()->getClipBounds(topLeft,bottomRight);
	UInt32 leftmostVisibleColNumber = UInt32(floor((topLeft.x()) / widthOfColumn));
	return leftmostVisibleColNumber; 
}

UInt32 TableDomFixedHeightLayoutManager::getColsToBeDisplayed() const
{
	Pnt2f topLeft,bottomRight;
	getParentTableDomArea()->getClipBounds(topLeft,bottomRight);
	
	UInt32 colsToBeDisplayed = 0;
	if(bottomRight.x() == 0 && bottomRight.y() == 0 )
		colsToBeDisplayed = (UInt32(ceil(getParentTableDomArea()->getPreferredSize().x()/ widthOfColumn)));
	else
		colsToBeDisplayed = (UInt32(ceil(abs(bottomRight.x() - topLeft.x())/widthOfColumn)));

	return colsToBeDisplayed;
}


UInt32 TableDomFixedHeightLayoutManager::getTopmostVisibleRowNumber() const
{
	Pnt2f topLeft,bottomRight;
	getParentTableDomArea()->getClipBounds(topLeft,bottomRight);
	UInt32 topmostVisibleRowNumber = UInt32(floor((topLeft.y()) / heightOfRow));
	return topmostVisibleRowNumber; 
}


UInt32 TableDomFixedHeightLayoutManager::getRowsToBeDisplayed() const
{
	Pnt2f topLeft,bottomRight;
	getParentTableDomArea()->getClipBounds(topLeft,bottomRight);
	
	UInt32 rowsToBeDisplayed = 0;
	if(bottomRight.x() == 0 && bottomRight.y() == 0 )
		rowsToBeDisplayed = (UInt32(ceil(getParentTableDomArea()->getPreferredSize().y()/ heightOfRow)));
	else
		rowsToBeDisplayed = (UInt32(ceil(abs(bottomRight.y() - topLeft.y())/heightOfRow)));

	return rowsToBeDisplayed;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableDomFixedHeightLayoutManager::TableDomFixedHeightLayoutManager(void) :
    Inherited(),
	rootCell(NULL),
	_preferredHeight(0),
	_preferredWidth(0), 
	heightOfRow(20), 
	widthOfColumn(60)
{
}

TableDomFixedHeightLayoutManager::TableDomFixedHeightLayoutManager(const TableDomFixedHeightLayoutManager &source) :
    Inherited(source)
{
	rootCell = source.rootCell;
	_preferredHeight = source._preferredHeight;
	_preferredWidth =  source._preferredWidth;
	heightOfRow = source.heightOfRow;
	widthOfColumn = source.widthOfColumn;
}

TableDomFixedHeightLayoutManager::~TableDomFixedHeightLayoutManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TableDomFixedHeightLayoutManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TableDomFixedHeightLayoutManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableDomFixedHeightLayoutManager NI" << std::endl;
}

OSG_END_NAMESPACE
