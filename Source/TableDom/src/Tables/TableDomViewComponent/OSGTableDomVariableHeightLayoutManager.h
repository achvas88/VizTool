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

#ifndef _OSGTABLEDOMVARIABLEHEIGHTLAYOUTMANAGER_H_
#define _OSGTABLEDOMVARIABLEHEIGHTLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableDomVariableHeightLayoutManagerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableDomVariableHeightLayoutManager class. See \ref
           PageContribTableDomTableDomVariableHeightLayoutManager for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableDomVariableHeightLayoutManager : public TableDomVariableHeightLayoutManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableDomVariableHeightLayoutManagerBase Inherited;
    typedef TableDomVariableHeightLayoutManager     Self;

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

	
	virtual void initializeRootCell();
	virtual Vec2f getContentRequestedSize(void) const;
	virtual void updateViews(void);
	virtual void calculatePreferredSize(void);
	

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableDomVariableHeightLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableDomVariableHeightLayoutManager(void);
    TableDomVariableHeightLayoutManager(const TableDomVariableHeightLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableDomVariableHeightLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableDomVariableHeightLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableDomVariableHeightLayoutManager &source);
};

typedef TableDomVariableHeightLayoutManager *TableDomVariableHeightLayoutManagerP;

OSG_END_NAMESPACE

#include "OSGTableDomVariableHeightLayoutManagerBase.inl"
#include "OSGTableDomVariableHeightLayoutManager.inl"

#endif /* _OSGTABLEDOMVARIABLEHEIGHTLAYOUTMANAGER_H_ */
