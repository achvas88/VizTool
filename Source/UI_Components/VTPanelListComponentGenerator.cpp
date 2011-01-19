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

#include "VTPanelListComponentGenerator.h"


#include "VTPanelListComponentGenerator.h"
#include "OSGGridLayout.h"
#include "OSGFlowLayout.h"
#include "OSGPanel.h"
#include "OSGComboBox.h"
#include "OSGDefaultMutableComboBoxModel.h"
#include "VTColorChooserComboBoxComponentGenerator.h"
#include "OSGTextField.h"
#include "OSGLabel.h"
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include "OSGStringUtils.h"
#include "OSGList.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// VTPanelListComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (VTPanelListComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PanelListComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentTransitPtr PanelListComponentGenerator::getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
		return ComponentTransitPtr(NULL);
	}

	std::string ValueString;

    try
    {
        ValueString = lexical_cast(Value);
		PanelRefPtr theComponent = Panel::create();
	
		GridLayoutRefPtr PanelLayout = OSG::GridLayout::create();
		PanelLayout->setRows(3);
		PanelLayout->setColumns(1);
		PanelLayout->setHorizontalGap(0);
		PanelLayout->setVerticalGap(2);

		

		std::stringstream is;
		is<<Index;
		std::string iss;
		is>>iss;
		TextFieldRefPtr theName = TextField::create();
		theName->setText("Group"+iss);
		theName->setPreferredSize(Vec2f(146,20));
		

		PanelRefPtr rangePanel = Panel::create();
		
		GridLayoutRefPtr rangePanelLayout = OSG::GridLayout::create();
		rangePanelLayout->setRows(1);
		rangePanelLayout->setColumns(4);
		rangePanelLayout->setHorizontalGap(2);
		rangePanelLayout->setVerticalGap(0);

		
		LabelRefPtr rangeLabel = Label::create();
		rangeLabel->setText("Range:");
		rangeLabel->setPreferredSize(Vec2f(35,20));

		TextFieldRefPtr from = TextField::create();
		from->setEmptyDescText("From");
		from->setPreferredSize(Vec2f(35,20));

		LabelRefPtr hiphenLabel = Label::create();
		hiphenLabel->setText(" - ");
		hiphenLabel->setPreferredSize(Vec2f(35,20));

		TextFieldRefPtr to = TextField::create();
		to->setPreferredSize(Vec2f(35,20));
		to->setEmptyDescText("To");

		rangePanel->pushToChildren(rangeLabel);
		rangePanel->pushToChildren(from);
		rangePanel->pushToChildren(hiphenLabel);
		rangePanel->pushToChildren(to);
		rangePanel->setLayout(rangePanelLayout);
		rangePanel->setPreferredSize(Vec2f(146,20));

		DefaultMutableComboBoxModelRefPtr TheComboBoxModel = DefaultMutableComboBoxModel::create();
		TheComboBoxModel->addElement(boost::any(Color4f(1.0,0.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,1.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,1.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,0.0,1.0)));
		TheComboBoxModel->addElement(boost::any(Color4f(1.0,1.0,1.0,1.0)));
		TheComboBoxModel->addElement(boost::any(std::string("More Colors")));

		ColorChooserComboBoxComponentGeneratorRefPtr TheColorChooserComboBoxComponentGenerator = ColorChooserComboBoxComponentGenerator::create();
		
		//Create the ComboBox
		ComboBoxRefPtr TheComboBox = ComboBox::create();
		TheComboBox->setModel(TheComboBoxModel);
		TheComboBox->setCellGenerator(TheColorChooserComboBoxComponentGenerator);
		TheComboBox->setEditable(false);
		TheComboBox->setSelectedIndex(0);
		TheComboBox->setPreferredSize(Vec2f(146,20));

		theComponent->pushToChildren(theName);
		theComponent->pushToChildren(rangePanel);
		theComponent->pushToChildren(TheComboBox);
		theComponent->setLayout(PanelLayout);
		theComponent->setPreferredSize(Vec2f(146,66));

		Parent->setCellMajorAxisLength(66);

		return ComponentTransitPtr(theComponent.get());

    }
    catch (boost::bad_lexical_cast &)
    {
        return ComponentTransitPtr(NULL);
    }

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PanelListComponentGenerator::PanelListComponentGenerator(void) :
    Inherited()
{
}

PanelListComponentGenerator::PanelListComponentGenerator(const PanelListComponentGenerator &source) :
    Inherited(source)
{
}

PanelListComponentGenerator::~PanelListComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PanelListComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PanelListComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PanelListComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
