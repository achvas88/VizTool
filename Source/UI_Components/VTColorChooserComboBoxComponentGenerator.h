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

#ifndef _VTCOLORCHOOSERCOMBOBOXCOMPONENTGENERATOR_H_
#define _VTCOLORCHOOSERCOMBOBOXCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "VTColorChooserComboBoxComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ColorChooserComboBoxComponentGenerator class. See \ref
           PageVizToolColorChooserComboBoxComponentGenerator for a description.
*/

class VT_VIZTOOL_DLLMAPPING ColorChooserComboBoxComponentGenerator : public ColorChooserComboBoxComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorChooserComboBoxComponentGeneratorBase Inherited;
    typedef ColorChooserComboBoxComponentGenerator     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}  
                                                               */
															   
	virtual ComponentTransitPtr getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);
	
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorChooserComboBoxComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorChooserComboBoxComponentGenerator(void);
    ColorChooserComboBoxComponentGenerator(const ColorChooserComboBoxComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorChooserComboBoxComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorChooserComboBoxComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorChooserComboBoxComponentGenerator &source);
};

typedef ColorChooserComboBoxComponentGenerator *ColorChooserComboBoxComponentGeneratorP;

OSG_END_NAMESPACE

#include "VTColorChooserComboBoxComponentGeneratorBase.inl"
#include "VTColorChooserComboBoxComponentGenerator.inl"

#endif /* _VTCOLORCHOOSERCOMBOBOXCOMPONENTGENERATOR_H_ */
