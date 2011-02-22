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

#include "OSGTableDomArea.h"
#include "OSGTableFileHandler.h"
#include "OSGTableDOM.h"
#include "OSGColorLayer.h"
#include "OSGTableDomFixedHeightLayoutManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableDomAreaBase.cpp file.
// To modify it, please change the .fcd file (OSGTableDomArea.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TableDomArea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

///////////////////// DocumentChange Handling Stuff //////////////////////

void TableDomArea::handleTableChanged(TableDOMEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TableDomArea::handleTableInsert(TableDOMEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TableDomArea::handleTableRemove(TableDOMEventDetails* const details)
{
	getLayoutManager()->updateViews();
	getLayoutManager()->calculatePreferredSize();
	updatePreferredSize();
}

void TableDomArea::handleTableModelChanged(void)
{
	setPosition(Pnt2f(0,0));
	getLayoutManager()->initializeRootCell();
	getLayoutManager()->calculatePreferredSize();

    _TableChangedConnection.disconnect();
    _TableInsertConnection.disconnect();
    _TableRemoveConnection.disconnect();
	
    _TableChangedConnection = getTableDOMModel()->connectChanged(boost::bind(&TableDomArea::handleTableChanged, this, _1));
    _TableInsertConnection = getTableDOMModel()->connectInsert(boost::bind(&TableDomArea::handleTableInsert, this, _1));
    _TableRemoveConnection = getTableDOMModel()->connectRemove(boost::bind(&TableDomArea::handleTableRemove, this, _1));
	
	updatePreferredSize();
	getLayoutManager()->updateViews();
}


///////////////////// Input Handling Stuff //////////////////////

void TableDomArea::focusGained(FocusEventDetails* const details)
{
    Inherited::focusGained(details);
}

void TableDomArea::focusLost(FocusEventDetails* const details)
{
	Inherited::focusLost(details);
}

void TableDomArea::mouseDragged(MouseEventDetails* const details)
{
}

void TableDomArea::keyTyped(KeyEventDetails* const details)
{
}

void TableDomArea::mouseClicked(MouseEventDetails* const details)
{
	Inherited::mouseClicked(details);
}

void TableDomArea::mouseReleased(MouseEventDetails* const details)
{
	Inherited::mouseReleased(details);
}

void TableDomArea::mousePressed(MouseEventDetails* const details)
{
	Inherited::mousePressed(details);
}

///////////////////// Size Handling Stuff //////////////////////

void TableDomArea::updatePreferredSize(void)
{
	setPreferredSize(getRequestedSize());
}

Vec2f TableDomArea::getContentRequestedSize(void) const
{

	if(getLayoutManager())
	{
		return getLayoutManager()->getContentRequestedSize();
	}
	else
	{
		return getSize();
	}
}

///////////////////// Scroll Handling Stuff //////////////////////

Vec2f TableDomArea::getPreferredScrollableViewportSize(void)
{
	if(getLayoutManager())
	{
		return getLayoutManager()->getContentRequestedSize();
	}
	else
	{
		return Vec2f(0.0,0.0);
	}
}

Int32 TableDomArea::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
	return 1;
}

bool TableDomArea::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool TableDomArea::getScrollableTracksViewportWidth(void)
{
    return false;
}


bool TableDomArea::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool TableDomArea::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

Int32 TableDomArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    return Inherited::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation, direction);
}

///////////////////// File Handling Stuff //////////////////////

void TableDomArea::loadFile(const BoostPath& pathOfFile)
{
	TableDOMRefPtr theTableModel=TableFileHandler::the()->read(pathOfFile);
	if(theTableModel)
	{
		setTableDOMModel(theTableModel);
		if(!getLayoutManager())
		{
			// create the appropriate type of LayoutManager based on the type of file loaded here.As of now, its just FixedHeightLayoutManager.
			TableDomFixedHeightLayoutManagerRefPtr Manager= TableDomFixedHeightLayoutManager::create();
			setLayoutManager(Manager);
		}
		handleTableModelChanged();
	}
}

void TableDomArea::saveFile(const BoostPath& pathOfFile)
{
	TableFileHandler::the()->write(getTableDOMModel(),pathOfFile);
}

///////////////////// Default Creation Stuff //////////////////////

void TableDomArea::createDefaultFont(void)
{
	UIFontRefPtr _Font = UIFont::create();
    _Font->setFamily("SANS");
    _Font->setGap(3);
    _Font->setGlyphPixelSize(46);
    _Font->setSize(12);
    _Font->setTextureWidth(0);
    _Font->setStyle(TextFace::STYLE_PLAIN);

	this->setFont(_Font);
}

void TableDomArea::createDefaultLayer(void)
{
	ColorLayerRefPtr theBackground = ColorLayer::create();
	setBackgrounds(theBackground);
	if(getEditable() && getEnabled())
	{
		theBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		setBackgroundColor(Color4f(1.0, 1.0, 1.0, 1.0));	// should change it to BackgroundColor
	}
	else
	{
		theBackground->setColor(Color4f(0.5, 0.5, 0.5, 1.0));
		setBackgroundColor(Color4f(0.5, 0.5, 0.5, 1.0));
	}
	
}

///////////////////// Drawing Stuff //////////////////////

void TableDomArea::drawInternal(Graphics * const TheGraphics, Real32 Opacity) const
{
	
	if(getLayoutManager() && getLayoutManager()->getMFVisibleViews()->size()>0)	// draw the view by calling the view's draw function
	{
		
		for(UInt32 i=0;i<getLayoutManager()->getMFVisibleViews()->size();i++)
		{
			getLayoutManager()->getVisibleViews(i)->drawView(TheGraphics,Opacity);
		}
	}
	
}


void TableDomArea::resolveLinks(void)
{
    Inherited::resolveLinks();

    _TableChangedConnection.disconnect();
    _TableInsertConnection.disconnect();
    _TableRemoveConnection.disconnect();
  
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TableDomArea::TableDomArea(void) :
    Inherited()
{
	createDefaultFont();
	createDefaultLayer();
}

TableDomArea::TableDomArea(const TableDomArea &source) :
    Inherited(source)
{
}

TableDomArea::~TableDomArea(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TableDomArea::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & TableDomArea::ClipBoundsFieldMask)
	{
		if(getLayoutManager())getLayoutManager()->updateViews();
	}

	if(whichField & TableDomArea::FontFieldMask)
	{
		if(getLayoutManager())
		{
			getLayoutManager()->updateViews();
			updatePreferredSize();
		}
	}

	if(whichField & TableDomArea::EditableFieldMask)
	{
		if(getEditable() && getEnabled())
		{
			setBackgroundColor(Color4f(1.0, 1.0, 1.0, 1.0));	// should change it to BackgroundColor
		}
		else
		{
			setBackgroundColor(Color4f(0.5, 0.5, 0.5, 1.0));
		}	
	}

	if(whichField & TableDomArea::BackgroundColorFieldMask)
	{
		ColorLayerRefPtr theBackground = ColorLayer::create();
		theBackground->setColor(getBackgroundColor());
		setBackgrounds(theBackground);
	}

}

void TableDomArea::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TableDomArea NI" << std::endl;
}

OSG_END_NAMESPACE
