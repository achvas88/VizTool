/*---------------------------------------------------------------------------*\
 *                             VizTool		                                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define VT_COMPILEVIZTOOLLIB

#include <OpenSG/OSGConfig.h>

#include "VTColorChooserComboBoxComponentGenerator.h"

#include "OSGLabel.h"
#include "OSGFlowLayout.h"
#include "OSGColorLayer.h"
#include "OSGPanel.h"
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// VTColorChooserComboBoxComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (VTColorChooserComboBoxComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorChooserComboBoxComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr ColorChooserComboBoxComponentGenerator::getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

	PanelRefPtr TheComponent = Panel::create();//dynamic_pointer_cast<Component>(getDrawObjectPrototype()->shallowCopy());
	TheComponent->setLayout(LayoutRefPtr(FlowLayout::create()));

	LabelRefPtr theColorLabel = Label::create();
	//theColorLabel->setPreferredSize(Vec2f(50.0f,50.0f));
	theColorLabel->setBorders(NULL);

	try
	{
		Color4f theColor = boost::any_cast<Color4f>(Value);

		if(theColor != NULL)
		{
			ColorLayerRefPtr theColorLabelBackground = ColorLayer::create();
			theColorLabelBackground->setColor(theColor);
			theColorLabel->setBackgrounds(theColorLabelBackground);
		}
	}
	catch(boost::bad_any_cast &)
	{
		std::string ValueString;

		try
		{
			ValueString = lexical_cast(Value);
		}
		catch (boost::bad_lexical_cast &)
		{
			//Could not convert to string
			SWARNING << "ColorChooserComboBoxComponentGenerator::getComboBoxComponent - The elements should either be a Color4f value or a std::string\n";
		}

		theColorLabel->setText(ValueString);

		if(IsSelected && HasFocus)
		{
			if(getFocusedTextColorHasPriority())
			{
				theColorLabel->setTextColors(getFocusedTextColor());
			}
			else
			{
				theColorLabel->setTextColors(getSelectedTextColor());
			}
		}
		else if(IsSelected)
		{
				theColorLabel->setTextColors(getSelectedTextColor());
		}
		else if(HasFocus)
		{
				theColorLabel->setTextColors(getFocusedTextColor());
		}
	}

	TheComponent->pushToChildren(theColorLabel);
    
	if(IsSelected && HasFocus)
	{
			if(getFocusedBorderHasPriority())
			{
				TheComponent->setBorders(getFocusedBorder());
			}
			else
			{
				TheComponent->setBorders(getSelectedBorder());
			}
			if(getFocusedBackgroundHasPriority())
			{
				TheComponent->setBackgrounds(getFocusedBackground());
			    TheComponent->setForegrounds(getFocusedForeground());
			}
			else
			{
				TheComponent->setBackgrounds(getSelectedBackground());
			    TheComponent->setForegrounds(getSelectedForeground());
			}
	}
	else if(IsSelected)
	{
			TheComponent->setBorders(getSelectedBorder());
			TheComponent->setBackgrounds(getSelectedBackground());
			TheComponent->setForegrounds(getSelectedForeground());
	}
	else if(HasFocus)
	{
			TheComponent->setBorders(getFocusedBorder());
			TheComponent->setBackgrounds(getFocusedBackground());
			TheComponent->setForegrounds(getFocusedForeground());
	}
	return ComponentTransitPtr(TheComponent.get());
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ColorChooserComboBoxComponentGenerator::ColorChooserComboBoxComponentGenerator(void) :
    Inherited()
{
}

ColorChooserComboBoxComponentGenerator::ColorChooserComboBoxComponentGenerator(const ColorChooserComboBoxComponentGenerator &source) :
    Inherited(source)
{
}

ColorChooserComboBoxComponentGenerator::~ColorChooserComboBoxComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorChooserComboBoxComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ColorChooserComboBoxComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ColorChooserComboBoxComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
