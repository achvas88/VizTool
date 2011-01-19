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

#ifndef _VTPANELLISTCOMPONENTGENERATOR_H_
#define _VTPANELLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "VTPanelListComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PanelListComponentGenerator class. See \ref
           PageVizToolPanelListComponentGenerator for a description.
*/

class VT_VIZTOOL_DLLMAPPING PanelListComponentGenerator : public PanelListComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PanelListComponentGeneratorBase Inherited;
    typedef PanelListComponentGenerator     Self;

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

    /*! \}                                                                 */
	
	virtual ComponentTransitPtr getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);
	
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PanelListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PanelListComponentGenerator(void);
    PanelListComponentGenerator(const PanelListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PanelListComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PanelListComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PanelListComponentGenerator &source);
};

typedef PanelListComponentGenerator *PanelListComponentGeneratorP;

OSG_END_NAMESPACE

#include "VTPanelListComponentGeneratorBase.inl"
#include "VTPanelListComponentGenerator.inl"

#endif /* _VTPANELLISTCOMPONENTGENERATOR_H_ */
