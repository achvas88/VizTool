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

#ifndef _OSGTABLEDOMLAYOUTMANAGER_H_
#define _OSGTABLEDOMLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableDomLayoutManagerBase.h"
#include "OSGTableDomAreaFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableDomLayoutManager class. See \ref
           PageContribTableDomTableDomLayoutManager for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableDomLayoutManager : public TableDomLayoutManagerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableDomLayoutManagerBase Inherited;
    typedef TableDomLayoutManager     Self;


	virtual void initializeRootCell() = 0;
	virtual Vec2f getContentRequestedSize(void) const = 0;
	virtual void updateViews(void) = 0;
	virtual void calculatePreferredSize(void) = 0;

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

	TableDomArea* getParentTableDomArea(void) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableDomLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableDomLayoutManager(void);
    TableDomLayoutManager(const TableDomLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableDomLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableDomLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableDomLayoutManager &source);
};

typedef TableDomLayoutManager *TableDomLayoutManagerP;

OSG_END_NAMESPACE

#include "OSGTableDomLayoutManagerBase.inl"
#include "OSGTableDomLayoutManager.inl"

#endif /* _OSGTABLEDOMLAYOUTMANAGER_H_ */
