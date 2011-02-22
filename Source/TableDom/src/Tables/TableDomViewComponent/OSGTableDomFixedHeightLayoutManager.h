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

#ifndef _OSGTABLEDOMFIXEDHEIGHTLAYOUTMANAGER_H_
#define _OSGTABLEDOMFIXEDHEIGHTLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableDomFixedHeightLayoutManagerBase.h"
#include "OSGCell.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableDomFixedHeightLayoutManager class. See \ref
           PageContribTableDomTableDomFixedHeightLayoutManager for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableDomFixedHeightLayoutManager : public TableDomFixedHeightLayoutManagerBase
{
  protected:

	Cell* rootCell;
	Real32 _preferredHeight;
	Real32 _preferredWidth; 
	Real32 heightOfRow;
	Real32 widthOfColumn;

	virtual UInt32 getTopmostVisibleRowNumber(void) const;
	virtual UInt32 getRowsToBeDisplayed(void) const;
	virtual UInt32 getLeftmostVisibleColNumber(void) const;
	virtual UInt32 getColsToBeDisplayed(void) const;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableDomFixedHeightLayoutManagerBase Inherited;
    typedef TableDomFixedHeightLayoutManager     Self;

	virtual void initializeRootCell();
	virtual Vec2f getContentRequestedSize(void) const;
	virtual void updateViews(void);
	virtual void calculatePreferredSize(void);
	

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableDomFixedHeightLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableDomFixedHeightLayoutManager(void);
    TableDomFixedHeightLayoutManager(const TableDomFixedHeightLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableDomFixedHeightLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableDomFixedHeightLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableDomFixedHeightLayoutManager &source);
};

typedef TableDomFixedHeightLayoutManager *TableDomFixedHeightLayoutManagerP;

OSG_END_NAMESPACE

#include "OSGTableDomFixedHeightLayoutManagerBase.inl"
#include "OSGTableDomFixedHeightLayoutManager.inl"

#endif /* _OSGTABLEDOMFIXEDHEIGHTLAYOUTMANAGER_H_ */
